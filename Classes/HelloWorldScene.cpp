#include "HelloWorldScene.h"

USING_NS_CC;

// レイヤーの大きさ
#define LAYER_WIDTH 480
#define LAYER_HEIGHT 1800

// ビューの大きさ
#define VIEW_WIDTH 480
#define VIEW_HEIGHT 320

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	// ----- レイヤーを生成する
    CCLayerGradient* pLayerView = CCLayerGradient::create();
	pLayerView->setAnchorPoint(CCPointZero);
	pLayerView->setPosition(CCPointZero);
	pLayerView->initWithColor(ccc4(170,250,120,225), ccc4(70,145,15,255), ccp(0.0f,1.0f));
	pLayerView->setContentSize(CCSizeMake(LAYER_WIDTH, LAYER_HEIGHT));

	// ----- ボタンメニューを生成する
	CCSprite* pBtnSprite = CCSprite::create("button.png");
	CCMenuItemSprite* pBackMenuBtn = CCMenuItemSprite::create(pBtnSprite, pBtnSprite, this, menu_selector(HelloWorld::buttonCallback));
	pBackMenuBtn->setPosition(CCPointZero);

	CCMenu* pMenu = CCMenu::create(pBackMenuBtn, NULL);
	pMenu->setPosition(ccp(pLayerView->getContentSize().width / 2, pLayerView->getContentSize().height / 2));
	pLayerView->addChild(pMenu);

	// ----- スクロールビューを配置する
	CCScrollView* pScrollView = CCScrollView::create(CCSizeMake(VIEW_WIDTH, VIEW_HEIGHT));						// 見えてるサイズ
	pScrollView->setAnchorPoint(CCPointZero);
	pScrollView->setPosition(CCPointZero);
	pScrollView->setContentSize(pLayerView->getContentSize());													// スクロールできる範囲
	pScrollView->setContainer(pLayerView);
	pScrollView->setContentOffset(ccp(0, VIEW_HEIGHT - pLayerView->getContentSize().height), false);			// スクロールの初期位置
	pScrollView->setDirection(kCCScrollViewDirectionVertical);
	pScrollView->setDelegate(this);
    this->addChild(pScrollView);

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::buttonCallback(cocos2d::CCNode *pSender)
{
	CCLog("ボタンがクリックされました");
}

void HelloWorld::scrollViewDidScroll(cocos2d::extension::CCScrollView *view)
{
}

void HelloWorld::scrollViewDidZoom(cocos2d::extension::CCScrollView *view)
{
}

