#include "LoginScene.h"
#include "RoleListScene.h"

USING_NS_CC;

#define MSG_HANDER_TAG_LOGIN "LoginScene"

Scene* LoginScene::createScene()
{
    return LoginScene::create();
}

void LoginScene::regMsgHandler() {
    REG_MSG_HANDLER(MSG_HANDER_TAG_LOGIN, MSG_ID_LOGIN_RSP, CC_CALLBACK_2(LoginScene::onRecvLoginRsp, this));
    REG_MSG_HANDLER(MSG_HANDER_TAG_LOGIN, MSG_ID_LOAD_ROLE_LIST_RSP, CC_CALLBACK_2(LoginScene::onRecvLoadRoleList, this));
}

void LoginScene::unregMsgHandler()
{
    UNREG_MSG_HANDLER(MSG_HANDER_TAG_LOGIN, MSG_ID_LOGIN_RSP);
    UNREG_MSG_HANDLER(MSG_HANDER_TAG_LOGIN, MSG_ID_LOAD_ROLE_LIST_RSP);
}

bool LoginScene::init()
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

    // add a "close" icon to exit the progress. it's an autorelease object
    auto loginBtn = ui::Button::create(); // ("normal_image.png", "selected_image.png", "disabled_image.png");
    loginBtn->setTitleText("login");
    loginBtn->addTouchEventListener(CC_CALLBACK_2(LoginScene::btnLoginTouchEventListener, this));
    /*loginBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
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
        });*/

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
    switch (eventType)
    {
    case ui::Widget::TouchEventType::BEGAN:
        break;
    case ui::Widget::TouchEventType::ENDED:
    {
        std::cout << "Button 1 clicked" << std::endl;
        LoginReq loginReq;
        loginReq.set_account("cocos");
        loginReq.set_pwd("");
        SEND_MSG(MSG_ID_LOGIN_REQ, loginReq);
        break;
    }
    default:
        break;
    }

}

void LoginScene::onRecvLoginRsp(int msgId, PB_MSG msg)
{
    LoginRsp* rsp = (LoginRsp*)msg.get();
    CCLOG("recv login rsp, err_code=%d", rsp->err_code());
}

void LoginScene::onRecvLoadRoleList(int msgId, PB_MSG msg)
{
    LoadRoleListRsp* rsp = (LoadRoleListRsp*)msg.get();
    int roleCount = rsp->role_list_size();
    CCLOG("recv role list rsp, roleCount=%d", roleCount);
    if (roleCount == 0) {
        CreateRoleReq req;
        req.set_account("cocos");
        req.set_role_name("cocos");
        SEND_MSG(MSG_ID_CREATE_ROLE_REQ, req);
    }
    else {

        RoleListScene* scene = (RoleListScene*)RoleListScene::createScene();
        for (int i = 0; i < rsp->role_list_size(); i++) {
            scene->roleList.push_back(rsp->role_list(i));
        }

        scene->updateUI();
        Director::getInstance()->replaceScene(scene);

       /* _RoleInfo roleInfo = rsp->role_list(0);
        EnterGame enterGameReq;
        enterGameReq.set_account("cocos");
        enterGameReq.set_role_id(roleInfo.role_id());
        SEND_MSG(MSG_ID_ENTER_GAME, enterGameReq);*/
    }
}

