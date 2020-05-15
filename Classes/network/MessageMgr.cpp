#include "MessageMgr.h"
#include "cocos2d.h"

void MessageMgr::onRecvMsg(int msgId, char* data, int len) {
	std::shared_ptr<google::protobuf::Message> msg = CreateMsgById(msgId);
	if (msg == NULL) {
		CCLOG("msg id(%d) error", msgId);
		return;
	}
	msg->ParseFromArray(data, len);
	MessageMgr::dispatchMsg(msgId, msg);
}

void MessageMgr::dispatchMsg(int msgId, std::shared_ptr<google::protobuf::Message> msg) {
	switch (msgId)
	{
	case MSG_ID_LOGIN_RSP:
		{
			LoginRsp* rsp = (LoginRsp*)msg.get();
			CCLOG("recv login rsp, account=%d", rsp->err_code());
			break;
		}
	default:
		break;
	}
}