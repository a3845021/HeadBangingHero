#include "MenuScene.h"
#include "GlobalDef.h"
#include "cocos-ext.h"
#include "GameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

CMenuScene::CMenuScene() : m_fFireAnimTime(0), m_iFireAnimIndex(1)
{
}


CMenuScene::~CMenuScene()
{
}

Scene* CMenuScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = CMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool CMenuScene::init()
{
	CC_RETURN_FALSE_IF(!LayerColor::initWithColor(Color4B::WHITE));

	InitUI();

	InitMenu();

	return true;
}


void CMenuScene::InitUI()
{
	Size visibleSize = GET_VISIBLESIZE();

	//背景
	/*
	auto pBg = Sprite::create("Images/menubg1.png");
	Size BgSize = GET_CONTENTSIZE(pBg);
	pBg->setScale(visibleSize.width / BgSize.width, visibleSize.height / BgSize.height);*/

	Scale9Sprite* pBg = Scale9Sprite::create("Images/menubg1.png");
	pBg->setPreferredSize(visibleSize);
	pBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pBg);

	//Logo
	auto pLogo = Sprite::create("Images/logo.png");
	Size logoSize = GET_CONTENTSIZE(pLogo);
	pLogo->setPosition(logoSize.width * 0.5f, visibleSize.height - logoSize.height * 0.7f);
	this->addChild(pLogo);

	//手
	auto pHand = Sprite::create("Images/hand.png");
	Size handSize = GET_CONTENTSIZE(pHand);
	pHand->setPosition(visibleSize.width / 4, handSize.height / 2);
	this->addChild(pHand);

	//火焰
	m_pFireSprite = Sprite::createWithSpriteFrameName("fire_1.png");
	Size fireSize = GET_CONTENTSIZE(m_pFireSprite);
	m_pFireSprite->setScale(visibleSize.width * 1.1f / fireSize.width);
	m_pFireSprite->setPosition(visibleSize.width / 2, fireSize.height / 2);
	this->addChild(m_pFireSprite);

	//火焰动画更新
	this->scheduleUpdate();

	//背景音乐
	LOOP_PLAY_BGMUSIC(BGM_MENU);
}


//初始化菜单
void CMenuScene::InitMenu()
{
	Size visibleSize = GET_VISIBLESIZE();

	//开始按钮
	auto playBtn = MenuItemSprite::create(
		Sprite::create("Play/play.png"),
		Sprite::create("Play/play.png"),
		CC_CALLBACK_1(CMenuScene::OnMenuClick, this)
		);
	Size playBtnSize = GET_CONTENTSIZE(playBtn);
	playBtn->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	auto menu = Menu::create(playBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//选择图片
	auto pSelect = CREATE_SPRITEWITHNAME("select_10.png");
	Size selectSize = GET_CONTENTSIZE(pSelect);
	pSelect->setPosition(visibleSize.width / 2 - playBtnSize.width / 2 - selectSize.width / 2, visibleSize.height / 2);
	this->addChild(pSelect);
	//动作
	pSelect->runAction(RepeatForever::create(Animate::create(GET_ANIM("SelectAnim"))));
}


//菜单点击
void CMenuScene::OnMenuClick(Ref* pSender)
{
	PLAY_EFFECT(BGM_CLICK);
	auto scene = CGameScene::CreateScene();
	REPLACE_SCENE(scene);
}


void CMenuScene::update(float dt)
{
	m_fFireAnimTime += dt;
	if (FLOAT_GE(m_fFireAnimTime, 0.1f))
	{
		m_fFireAnimTime = 0;

		//设置索引
		if (++m_iFireAnimIndex > FIRE_INDEX_MAX)
		{
			m_iFireAnimIndex = 1;
		}

		//切换下一帧火焰图片
		m_pFireSprite->setSpriteFrame(GET_SPRITEFRAME(StringUtils::format("fire_%d.png", m_iFireAnimIndex)));
	}
}

