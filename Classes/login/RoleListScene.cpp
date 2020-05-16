#include "RoleListScene.h"

USING_NS_CC;

#define MSG_HANDER_TAG_ROLE_LIST "RoleListScene"
#define MAX_ROLE_NUM 5

Scene* RoleListScene::createScene()
{
    return RoleListScene::create();
}

void RoleListScene::regMsgHandler() {
    REG_MSG_HANDLER(MSG_HANDER_TAG_ROLE_LIST, MSG_ID_ENTER_GAME_RSP, CC_CALLBACK_2(RoleListScene::onRecvEnterGameRsp, this));
}

void RoleListScene::unregMsgHandler()
{
    UNREG_MSG_HANDLER(MSG_HANDER_TAG_ROLE_LIST, MSG_ID_LOAD_ROLE_LIST_RSP);
}

bool RoleListScene::init()
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

    for (int i = 0; i < MAX_ROLE_NUM; i++) {
        auto roleBtn = ui::Button::create();
        m_roleItems.push_back(roleBtn);
        roleBtn->setPosition(Vec2(x, y));
        roleBtn->setColor(Color3B::RED);
        roleBtn->setVisible(true);
        this->addChild(roleBtn);
        y -= (roleBtn->getContentSize().height + 15);
        roleBtn->addTouchEventListener(std::bind(&RoleListScene::btnEnterGameTouchEventListener, this, i, std::placeholders::_1, std::placeholders::_2));
    }

    //auto enterBtn = ui::Button::create(); // ("normal_image.png", "selected_image.png", "disabled_image.png");
    //enterBtn->setTitleText("ENTERGAME");
    //enterBtn->addTouchEventListener(CC_CALLBACK_2(RoleListScene::btnEnterGameTouchEventListener, this));

    //enterBtn->setPosition(Vec2(x, y));
    //this->addChild(enterBtn);

    // create menu, it's an autorelease object
   /* auto menu = Menu::create(loginBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    return true;
}

void RoleListScene::updateUI()
{
    for (int i = 0; i < MAX_ROLE_NUM; i++) {
        if (roleList.size() > i) {
            std::string name = roleList[i].role_name();
            m_roleItems[i]->setTitleText(name);
        }
        else {
            m_roleItems[i]->setTitleText("");
        }
    }
}

void RoleListScene::btnEnterGameTouchEventListener(int index, Ref* pSender, ui::Widget::TouchEventType eventType)
{
    switch (eventType)
    {
    case ui::Widget::TouchEventType::BEGAN:
        break;
    case ui::Widget::TouchEventType::ENDED:
    {
        std::cout << "Button 1 clicked" << std::endl;
        if (roleList.size() <= index) {
            std::cout << "role list size < index" << std::endl;
            return;
        }
         _RoleInfo roleInfo = roleList[index];
         EnterGame enterGameReq;
         enterGameReq.set_account("cocos");
         enterGameReq.set_role_id(roleInfo.role_id());
         SEND_MSG(MSG_ID_ENTER_GAME, enterGameReq);
        break;
    }
    default:
        break;
    }

}

void RoleListScene::onRecvEnterGameRsp(int msgId, PB_MSG msg)
{
    LoginRsp* rsp = (LoginRsp*)msg.get();
    CCLOG("recv login rsp, err_code=%d", rsp->err_code());
}


