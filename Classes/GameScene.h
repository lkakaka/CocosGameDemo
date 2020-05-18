#pragma once

#include "SceneBase.h"
#include "2d/CCLabel.h"

class GameScene : public SceneBase
{
private:
public:

    static cocos2d::Scene* createScene();

    virtual void regMsgHandler();
    virtual void unregMsgHandler();

    virtual bool init();
    void updateUI();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

