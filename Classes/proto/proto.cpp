
// Generated by tool.  DO NOT EDIT!

#include "proto.h"

std::shared_ptr<google::protobuf::Message> CreateMsgById(int msgId)
{
	switch (msgId)
	{
		case MSG_ID_ACTOR_BORN:
		return std::shared_ptr<google::protobuf::Message>(new ActorBorn());
		case MSG_ID_ACTOR_DISSOLVE:
		return std::shared_ptr<google::protobuf::Message>(new ActorDissolve());
		case MSG_ID_CREATE_ROLE_REQ:
		return std::shared_ptr<google::protobuf::Message>(new CreateRoleReq());
		case MSG_ID_CREATE_ROLE_RSP:
		return std::shared_ptr<google::protobuf::Message>(new CreateRoleRsp());
		case MSG_ID_DISCONNECT_REQ:
		return std::shared_ptr<google::protobuf::Message>(new DisconnectReq());
		case MSG_ID_DISCONNECT_RSP:
		return std::shared_ptr<google::protobuf::Message>(new DisconnectRsp());
		case MSG_ID_ENTER_GAME:
		return std::shared_ptr<google::protobuf::Message>(new EnterGame());
		case MSG_ID_ENTER_GAME_RSP:
		return std::shared_ptr<google::protobuf::Message>(new EnterGameRsp());
		case MSG_ID_ENTER_SCENE_REQ:
		return std::shared_ptr<google::protobuf::Message>(new EnterSceneReq());
		case MSG_ID_ENTER_SCENE_RSP:
		return std::shared_ptr<google::protobuf::Message>(new EnterSceneRsp());
		case MSG_ID_GM_CMD:
		return std::shared_ptr<google::protobuf::Message>(new GmCmd());
		case MSG_ID_GM_CMD_RSP:
		return std::shared_ptr<google::protobuf::Message>(new GmCmdRsp());
		case MSG_ID_LOAD_ROLE_LIST_RSP:
		return std::shared_ptr<google::protobuf::Message>(new LoadRoleListRsp());
		case MSG_ID_LOGIN_REQ:
		return std::shared_ptr<google::protobuf::Message>(new LoginReq());
		case MSG_ID_LOGIN_RSP:
		return std::shared_ptr<google::protobuf::Message>(new LoginRsp());
		case MSG_ID_MOVE_TO:
		return std::shared_ptr<google::protobuf::Message>(new MoveTo());
		case MSG_ID_SYNC_POS:
		return std::shared_ptr<google::protobuf::Message>(new SyncPos());
		case MSG_ID_TEST_REQ:
		return std::shared_ptr<google::protobuf::Message>(new TestReq());
	}
	return NULL;
}

std::shared_ptr<google::protobuf::Message> createMessage(int msgId, char* data, int dataLen)
{
	std::shared_ptr<google::protobuf::Message> msg = CreateMsgById(msgId);
	if (msg == NULL) {
		// Logger::logError("$create proto msg error, msgId:%d", msgId);
		return msg;
	}
	msg->ParseFromArray(data, dataLen);
	return msg;
}