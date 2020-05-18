#pragma once

#include "SceneBase.h"

class LoginScene : public SceneBase
{
private:
    ui::TextField* m_textAccout;
public:
    static cocos2d::Scene* createScene();

    virtual void regMsgHandler();
    virtual void unregMsgHandler();

    virtual bool init();

    // a selector callback
    void btnLoginTouchEventListener(cocos2d::Ref* pSender, Widget::TouchEventType eventType);

    void onRecvLoginRsp(int msgId, PB_MSG msg);
    void onRecvLoadRoleList(int msgId, PB_MSG msg);


    void onGlobalSchedule(float t);

    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);
};

