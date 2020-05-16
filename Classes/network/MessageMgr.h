#pragma once
#include "proto/proto.h"
#include <functional>
#include <list>

#define PB_MSG std::shared_ptr<google::protobuf::Message>

typedef std::function<void(int, PB_MSG)> MsgHandler;

#define REG_MSG_HANDLER(tag, msgId, msgHander) MessageMgr::regMsgHandler(tag, msgId, msgHander)
#define UNREG_MSG_HANDLER(tag, msgId) MessageMgr::unregMsgHandler(tag, msgId)

class MessageMgr
{
private:
	//static std::map<int, std::list<MsgHandler>> m_msgHanders;
public:
	static void onRecvMsg(int msgId, char* data, int len);
	static void dispatchMsg(int msgId, std::shared_ptr<google::protobuf::Message> msg);
	static void regMsgHandler(std::string tag, int msgId, MsgHandler msgHandler);
	static void unregMsgHandler(std::string tag, int msgId);
};

