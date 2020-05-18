#include "GameScene.h"

USING_NS_CC;

#define MSG_HANDER_TAG_GAMESCENE "GameScene"
#define MAX_ROLE_NUM 6

Scene* GameScene::createScene()
{
    return GameScene::create();
}

void GameScene::regMsgHandler() {
    
}

void GameScene::unregMsgHandler()
{
   
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!SceneBase::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.


    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height * 2 / 3;

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

    // create menu, it's an autorelease object
   /* auto menu = Menu::create(loginBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    return true;
}

void GameScene::updateUI()
{
   
}



