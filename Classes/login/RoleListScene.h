#pragma once

#include "SceneBase.h"
#include "2d/CCLabel.h"

class RoleListScene : public SceneBase
{
private:
    std::vector<ui::Button*> m_roleItems;
public:

    std::vector<_RoleInfo> roleList;

    static cocos2d::Scene* createScene();

    virtual void regMsgHandler();
    virtual void unregMsgHandler();

    virtual bool init();
    void updateUI();

    // a selector callback
    void btnEnterGameTouchEventListener(int index, cocos2d::Ref* pSender, Widget::TouchEventType eventType);

    void onRecvEnterGameRsp(int msgId, PB_MSG msg);

    // implement the "static create()" method manually
    CREATE_FUNC(RoleListScene);
};

