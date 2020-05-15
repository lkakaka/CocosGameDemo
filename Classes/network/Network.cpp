#include "Network.h"
#include "cocos2d.h"

Network* Network::g_network = new Network();


Network::Network()
{
	read_buf.resize(1024);
}

void Network::run() {
	asio::io_context::work worker(io_context);
	io_context.run();
}

void Network::connect() {
	m_socket.reset(new tcp::socket(io_context));
	try {
		std::string ip = "127.0.0.1";
		//std::string ip = "111.229.80.201";
		tcp::endpoint target(asio::ip::make_address(ip), 20000);
		m_socket->connect(target);
		doRead();

		/*LoginReq loginReq;
		loginReq.set_account("cocos");
		loginReq.set_pwd("");
		sendMsg(MSG_ID_LOGIN_REQ, loginReq);*/
	}
	catch (std::exception e) {
		CCLOG("connect failed, %s", e.what());
	}
}

void Network::doRead() {
	auto buf = asio::buffer(read_buf, read_buf.size());
	m_socket->async_receive(buf, [this, buf](const asio::error_code error, size_t datLen) {
		if (error.value())
		{
			const std::string err_str = error.message();
			CCLOG("$close connection, %s", err_str.data());
			return;
		}
		if (datLen > 0)
		{
			CCLOG("$receive data, len:%d, %s", datLen, buf.data());
			m_recvBuf.append(read_buf);
			doParse();
		}
	});
}

void Network::doParse() {
	int size = m_recvBuf.size();
	if (size < 4) return;
	int iPacketLen = m_recvBuf.readInt(false);
	if (iPacketLen < 8) {
		CCLOG("$receive data error, packet len(%d) is too short", iPacketLen);
		disConnect();
		return;
	}
	if (size < iPacketLen) return;
	m_recvBuf.readInt(true);
	int iMsgId = m_recvBuf.readInt(true);
	int iMsgLen = iPacketLen - 8;
	MessageMgr::onRecvMsg(iMsgId, m_recvBuf.data(), iMsgLen);
	m_recvBuf.remove(iMsgLen);
	doParse();
}

void Network::sendMsg(int msgId, google::protobuf::Message& msg) {
	MyBuffer buffer;
	std::string strMsg = msg.SerializeAsString();
	buffer.writeInt(strMsg.size() + 8);
	buffer.writeInt(msgId);
	buffer.writeString(strMsg.data(), strMsg.size());
	std::copy(buffer.data(), buffer.data() + buffer.size(), std::back_inserter(m_sendBuf));
	doSend();
}

void Network::sendData(std::vector<char> msg) {
	std::copy(msg.begin(), msg.end(), std::back_inserter(m_sendBuf));
	doSend();
}

void Network::doSend() {
	if (m_sendBuf.size() == 0) return;
	asio::const_buffer buf(&m_sendBuf.front(), m_sendBuf.size());
	m_socket->async_write_some(buf, [this](const asio::error_code err_code, size_t datLen) {
		if (err_code)
		{
			const std::string err_str = err_code.message();
			CCLOG("send data error, %s", err_str.data());
			return;
		}
		
		if (datLen > 0) {
			m_sendBuf.erase(m_sendBuf.begin(), m_sendBuf.begin() + datLen);
			doSend();
		}
	});
}

void Network::disConnect() {
	m_socket->shutdown(asio::socket_base::shutdown_type::shutdown_both);
}

void Network::startNetwork() {
	/*SocketEventHander* eventHandler = new SocketEventHander();
	SIOClient* client = network::SocketIO::connect("127.0.0.1:20000", *eventHandler);*/

	//std::thread* t = new std::thread(std::bind(&Network::loop, this));
	//t->join();


	connect();
	m_workThread.reset(new std::thread(std::bind(&Network::run, this)));

}

Network* Network::getNetwork() {
	return Network::g_network;
}
