#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class LoginScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void btnLoginTouchEventListener(cocos2d::Ref* pSender, Widget::TouchEventType eventType);

    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);
};

