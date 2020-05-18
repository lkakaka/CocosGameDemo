#include "RoleListScene.h"
#include "GameScene.h"

USING_NS_CC;

#define MSG_HANDER_TAG_ROLE_LIST "RoleListScene"
#define MAX_ROLE_NUM 6

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

    auto label = Label::create();
    label->setString("Role List:");
    label->setPosition(Vec2(x, y));
    this->addChild(label);

    y -= (label->getContentSize().height + 15);

    for (int i = 0; i < MAX_ROLE_NUM; i++) {
        auto roleBtn = ui::Button::create();
        m_roleItems.push_back(roleBtn);
        /*roleBtn->ignoreContentAdaptWithSize(true);
        roleBtn->setContentSize(Size(50, 10));*/
        roleBtn->setPosition(Vec2(x, y));
        roleBtn->setColor(Color3B::RED);
        this->addChild(roleBtn);
        y -= (roleBtn->getContentSize().height + 15);
        roleBtn->addTouchEventListener(std::bind(&RoleListScene::btnEnterGameTouchEventListener, this, i, std::placeholders::_1, std::placeholders::_2));
    }

    //auto enterBtn = ui::Button::create(); // ("normal_image.png", "selected_image.png", "disabled_image.png");
    //enterBtn->setTitleText("ENTERGAME");
    //enterBtn->addTouchEventListener(std::bind(&RoleListScene::btnEnterGameTouchEventListener, this, 0, std::placeholders::_1, std::placeholders::_2));

    //enterBtn->setPosition(Vec2(x, y));
    //this->addChild(enterBtn);

    /*auto label = Label::create();
    label->setPosition(Vec2(x, y));
    label->setString("hello");
    this->addChild(label);*/

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
            m_roleItems[i]->setVisible(true);
        }
        else {
            m_roleItems[i]->setTitleText("");
            m_roleItems[i]->setVisible(false);
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
         enterGameReq.set_account(GAME_INSTACNE->masterRole.account);
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
    EnterGameRsp* rsp = (EnterGameRsp*)msg.get();
    CCLOG("recv enter game rsp, err_code=%d", rsp->err_code());

    if (rsp->err_code() == 0) {
        GAME_INSTACNE->masterRole.role_id = rsp->role_info().role_id();
        GAME_INSTACNE->masterRole.role_name = rsp->role_info().role_name();
        auto scene = GameScene::create();
        Director::getInstance()->replaceScene(scene);
    }
}


