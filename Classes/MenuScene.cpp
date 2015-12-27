#include "MenuScene.h"
#include "GlobalDef.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

CMenuScene::CMenuScene() : m_iBGMPlayTime(0)
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
	CC_RETURN_FALSE_IF(!Layer::init());

	m_visibleSize = GET_VISIBLESIZE();

	InitUI();

	return true;
}


void CMenuScene::InitUI()
{
	Scale9Sprite* bg = Scale9Sprite::create("Images/menubg1.png");
	bg->setPreferredSize(m_visibleSize);
	bg->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	this->addChild(bg);

	auto logo = Sprite::create("Images/logo.png");
	Size logoSize = GET_CONTENTSIZE(logo);
	logo->setPosition(logoSize.width * 0.5f, m_visibleSize.height - logoSize.height * 2 / 3);
	this->addChild(logo);

	auto hand = Sprite::create("Images/hand.png");
	Size handSize = GET_CONTENTSIZE(hand);
	hand->setPosition(m_visibleSize.width / 4, handSize.height / 2);
	this->addChild(hand);

	//背景音乐
	PLAY_BGMUSIC(BGM_MENU1);
	this->scheduleUpdate();
}


//第一首背景音乐播放完时第二首重复播放
void CMenuScene::update(float dt)
{
	m_iBGMPlayTime += dt;
	if (m_iBGMPlayTime >= BGM1_TIME)
	{
		STOP_BGMUSIC();
		LOOP_PLAY_BGMUSIC(BGM_MENU2);
		this->unscheduleUpdate();
	}
}