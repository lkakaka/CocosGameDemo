#pragma once
#include "asio.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/system_error.hpp"
#include "MyBuffer.h"
#include "MessageMgr.h"

using namespace asio::ip;

class Network
{
	private:
		static Network* g_network;

		std::shared_ptr<std::thread> m_workThread;
		asio::io_context io_context;
		std::shared_ptr<tcp::socket> m_socket;
		std::vector<char> read_buf;
		MyBuffer m_recvBuf;

		std::vector<unsigned char> m_sendBuf;

		Network();
		void run();
		void doRead();
		void doSend();
	public:
		void startNetwork();
		static Network* getNetwork();

		void connect();
		void doParse();
		void sendData(std::vector<char> msg);
		void sendMsg(int msgId, google::protobuf::Message& msg);
};

 
