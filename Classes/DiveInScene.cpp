#include "DiveInScene.h"

USING_NS_CC;

Scene* DiveInScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DiveInScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DiveInScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(DiveInScene::menuCloseCallback, this));
    
    closeItem->setAnchorPoint(Vec2(0,0));
    closeItem->setPosition(Vec2(0,0));
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                //origin.y + closeItem->getContentSize().height/2));

    auto openItem = MenuItemImage::create(
                                          "CloseNormal.png",
                                          "CloseSelected.png",
                                          CC_CALLBACK_1(DiveInScene::menuCloseCallback,this));
    openItem->setPosition(visibleSize.width/2,openItem->getContentSize().height/2);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,openItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Dive In to Swim", "Arial", 112);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto bg = Sprite::create("gamebg_00.png");
    sprite = Sprite::create("samso.png");
    
    Shaky3D *shaky = Shaky3D::create(100.0f, Size(15,10), 5, false);
    auto gridNode = NodeGrid::create();
    gridNode->runAction(shaky);
    gridNode->setAnchorPoint(Vec2(0,0));
    gridNode->setPosition(Vec2(0,0));
    
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition(Vec2(0,0));
    
    bg->setAnchorPoint(Vec2(0,0));
    bg->setScale(0.5f);
    bg->setPosition(Vec2(0,0));
    
    gridNode->addChild(bg);
    bg->addChild(sprite);
    this->addChild(gridNode);
    
    auto action = MoveBy::create(2, Point(700,700));
    sprite->runAction(action);
    

    return true;
}

void DiveInScene::run(float deltaTime)
{
    //float ypos = sprite->getPosition().y;
    //ypos++;
   // auto pt = sprite->getPosition();
    //pt.y++;
    //sprite->setPosition(pt);
    
}


void DiveInScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
