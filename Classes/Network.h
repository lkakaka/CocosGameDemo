#pragma once
#include "network/SocketIO.h"
#include "asio.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/system_error.hpp"

USING_NS_CC;

using namespace network;
using namespace asio::ip;

class SocketEventInterface {
	virtual void onConnect() = 0;
	virtual void onMessage() = 0;
	virtual void onClose() = 0;
};

class Network
{
	private:
		static Network* g_network;
		SocketEventInterface* m_eventHandler;

		std::shared_ptr<std::thread> m_workThread;
		asio::io_context io_context;
		std::shared_ptr<tcp::socket> m_socket;
		std::vector<unsigned char> read_buf;

		std::vector<unsigned char> send_buf;

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



class SocketEventHander : public network::SocketIO::SIODelegate {
	virtual void onConnect(network::SIOClient* client);
	virtual void onMessage(SIOClient* client, const std::string& data);
	void onClose(SIOClient* client) {};
	void onError(SIOClient* client, const std::string& data) {};
};
 
