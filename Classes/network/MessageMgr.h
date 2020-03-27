#pragma once
#include "proto/proto.h"

class MessageMgr
{
	public:
		static void onRecvMsg(int msgId, char* data, int len);
		static void dispatchMsg(int msgId, std::shared_ptr<google::protobuf::Message> msg);
};

