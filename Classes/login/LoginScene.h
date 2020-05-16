#pragma once

#include "SceneBase.h"

class LoginScene : public SceneBase
{
public:
    static cocos2d::Scene* createScene();

    virtual void regMsgHandler();
    virtual void unregMsgHandler();

    virtual bool init();

    // a selector callback
    void btnLoginTouchEventListener(cocos2d::Ref* pSender, Widget::TouchEventType eventType);

    void onRecvLoginRsp(int msgId, PB_MSG msg);
    void onRecvLoadRoleList(int msgId, PB_MSG msg);

    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);
};

