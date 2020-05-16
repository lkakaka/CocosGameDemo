#include "MessageMgr.h"
#include "cocos2d.h"
#include "Network.h"

#define _HANDER_MAP std::map<std::string, MsgHandler>

std::map<int, _HANDER_MAP*> m_msgHanders;

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
	auto iter = m_msgHanders.find(msgId);
	if (iter == m_msgHanders.end()) return;
	_HANDER_MAP* handers = iter->second;
	for (auto handerIter = handers->begin(); handerIter != handers->end(); handerIter++) {
		(handerIter->second)(msgId, msg);
	}
}

void MessageMgr::regMsgHandler(std::string tag, int msgId, MsgHandler msgHandler) {
	if (m_msgHanders.find(msgId) == m_msgHanders.end()) {
		_HANDER_MAP* newHanders = new _HANDER_MAP();
		m_msgHanders.emplace(std::make_pair(msgId, newHanders));
	}
	_HANDER_MAP* handers = m_msgHanders.find(msgId)->second;
	if (handers->find(tag) != handers->end()) {
		CCLOGWARN("msg_id(%d) handler repeated!!!", msgId);
	}
	handers->emplace(tag, msgHandler);
}

void MessageMgr::unregMsgHandler(std::string tag, int msgId) {
	if (m_msgHanders.find(msgId) == m_msgHanders.end()) return;
	_HANDER_MAP* handers = m_msgHanders.find(msgId)->second;
	handers->erase(tag);
}