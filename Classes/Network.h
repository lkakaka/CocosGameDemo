#pragma once
#include "network/SocketIO.h"

USING_NS_CC;

using namespace network;

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

		Network();
		void loop();
	public:
		void startNetwork();
		static Network* getNetwork();
};



class SocketEventHander : public network::SocketIO::SIODelegate {
	virtual void onConnect(network::SIOClient* client);
	virtual void onMessage(SIOClient* client, const std::string& data);
	void onClose(SIOClient* client) {};
	void onError(SIOClient* client, const std::string& data) {};
};
 
