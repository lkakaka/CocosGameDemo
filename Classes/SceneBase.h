#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "network/Network.h"
#include "Game.h"

USING_NS_CC;
using namespace cocos2d::ui;

class SceneBase : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void problemLoading(const char* filename);

    virtual void regMsgHandler()=0;
    virtual void unregMsgHandler()=0;

    // implement the "static create()" method manually
    //CREATE_FUNC(LoginScene);
};

