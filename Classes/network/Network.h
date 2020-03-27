#pragma once
#include "asio.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/system_error.hpp"

using namespace asio::ip;

class Network
{
	private:
		static Network* g_network;

		std::shared_ptr<std::thread> m_workThread;
		asio::io_context io_context;
		std::shared_ptr<tcp::socket> m_socket;
		std::vector<unsigned char> read_buf;

		std::vector<unsigned char> m_sendBuf;

		Network();
		void loop();
		void run();
		void doRead();
		void doSend();
	public:

		void connect();
		void sendData(std::vector<char> msg);
		void startNetwork();
		static Network* getNetwork();
};

 
