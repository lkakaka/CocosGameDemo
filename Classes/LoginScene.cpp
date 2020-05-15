#include "LoginScene.h"
#include "network/Network.h"

USING_NS_CC;

Scene* LoginScene::createScene()
{
    return LoginScene::create();
}

bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto loginBtn = ui::Button::create(); // ("normal_image.png", "selected_image.png", "disabled_image.png");
    loginBtn->setTitleText("login");
    loginBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED: 
        {
            std::cout << "Button 1 clicked" << std::endl;
            LoginReq loginReq;
            loginReq.set_account("cocos");
            loginReq.set_pwd("");
            Network::getNetwork()->sendMsg(MSG_ID_LOGIN_REQ, loginReq);
            break;
        }
        default:
            break;
        }
        });

    float x = origin.x + visibleSize.width / 2 - loginBtn->getContentSize().width / 2;
    float y = origin.y + visibleSize.height / 2 - loginBtn->getContentSize().height / 2;
    loginBtn->setPosition(Vec2(x, y));
    this->addChild(loginBtn);

    // create menu, it's an autorelease object
   /* auto menu = Menu::create(loginBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    return true;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoginScene.cpp\n");
}

void LoginScene::btnLoginTouchEventListener(Ref* pSender, ui::Widget::TouchEventType eventType)
{
    //Close the cocos2d-x game scene and quit the application
    //Director::getInstance()->end();

    LoginReq loginReq;
    loginReq.set_account("cocos");
    loginReq.set_pwd("");
    Network::getNetwork()->sendMsg(MSG_ID_LOGIN_REQ, loginReq);

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

