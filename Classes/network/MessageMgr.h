#pragma once
#include "proto/proto.h"
#include <functional>
#include <list>

#include "cocos2d.h"

#define PB_MSG std::shared_ptr<google::protobuf::Message>

typedef std::function<void(int, PB_MSG)> MsgHandler;

#define REG_MSG_HANDLER(tag, msgId, msgHander) MessageMgr::getInstance()->regMsgHandler(tag, msgId, msgHander)
#define UNREG_MSG_HANDLER(tag, msgId) MessageMgr::getInstance()->unregMsgHandler(tag, msgId)

#define _HANDER_MAP std::map<std::string, MsgHandler>

class _Message
{
public:
	_Message(int msgId, std::shared_ptr<google::protobuf::Message> msg) {
		this->msgId = msgId;
		this->msg = msg;
	}
	int msgId;
	std::shared_ptr<google::protobuf::Message> msg;
};

class MessageMgr : public cocos2d::Node
{
private:
	static MessageMgr* g_msgInstance;

	std::map<int, _HANDER_MAP*> m_msgHanders;
	std::vector<std::shared_ptr<_Message>> msg_buffer;
	std::mutex msg_mutex;
public:
	static MessageMgr* getInstance();

	void onRecvMsg(int msgId, char* data, int len);
	void dispatchMsg(int msgId, std::shared_ptr<google::protobuf::Message> msg);
	void regMsgHandler(std::string tag, int msgId, MsgHandler msgHandler);
	void unregMsgHandler(std::string tag, int msgId);
	void onSchdule(float t);
};

