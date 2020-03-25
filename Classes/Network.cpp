#include "Network.h"

Network* Network::g_network = new Network();

Network::Network() : m_eventHandler(NULL)
{
	read_buf.resize(1024);
}

void Network::loop()
{
	asio::io_context io_context;
	std::shared_ptr<tcp::socket> s(new tcp::socket(io_context));
	tcp::endpoint target(asio::ip::make_address("127.0.0.1"), 20000);
	s->connect(target);

	std::vector<unsigned char> read_buf(1024);
	auto buf = asio::buffer(read_buf, read_buf.size());
	s->async_receive(buf, [buf](const asio::error_code error, size_t datLen) {
		if (error.value())
		{
			const std::string err_str = error.message();
			CCLOG("$close connection, %s", err_str.data());
			return;
		}
		if (datLen > 0)
		{
			CCLOG("$receive data, len:%d, %s", datLen, buf.data());
			/*auto iter = read_buf.begin();
			std::advance(iter, datLen);
			std::copy(read_buf.begin(), iter, std::back_inserter(read_buf));*/
		}
		});
	asio::io_context::work worker(io_context);
	io_context.run();
	//std::thread t([&io_context]() {io_context.run(); });
	//t.join();
}

void Network::run() {
	asio::io_context::work worker(io_context);
	io_context.run();
}

void Network::connect() {
	m_socket.reset(new tcp::socket(io_context));
	try {
		tcp::endpoint target(asio::ip::make_address("127.0.0.1"), 20000);
		m_socket->connect(target);
		doRead();
	}
	catch (std::exception e) {
		CCLOG("connect failed, %s", e.what());
	}
}

void Network::doRead() {
	auto buf = asio::buffer(read_buf, read_buf.size());
	m_socket->async_receive(buf, [buf](const asio::error_code error, size_t datLen) {
		if (error.value())
		{
			const std::string err_str = error.message();
			CCLOG("$close connection, %s", err_str.data());
			return;
		}
		if (datLen > 0)
		{
			CCLOG("$receive data, len:%d, %s", datLen, buf.data());
			/*auto iter = read_buf.begin();
			std::advance(iter, datLen);
			std::copy(read_buf.begin(), iter, std::back_inserter(read_buf));*/
		}
	});
}

void Network::sendData(std::vector<char> msg) {
	std::copy(msg.begin(), msg.end(), std::back_inserter(send_buf));
	doSend();
}

void Network::doSend() {
	if (send_buf.size() == 0) return;
	asio::const_buffer buf(&send_buf.front(), send_buf.size());
	m_socket->async_write_some(buf, [this](const asio::error_code err_code, size_t datLen) {
		if (err_code)
		{
			const std::string err_str = err_code.message();
			CCLOG("send data error, %s", err_str.data());
			return;
		}
		
		if (datLen > 0) {
			send_buf.erase(send_buf.begin(), send_buf.begin() + datLen);
			doSend();
		}
	});
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


void SocketEventHander::onConnect(network::SIOClient* client) {
	printf("socket on connect-------\n");
}

void SocketEventHander::onMessage(SIOClient* client, const std::string& data) {
	printf("socket on onMessage-------\n");
}