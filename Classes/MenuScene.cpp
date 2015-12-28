#include "MenuScene.h"
#include "GlobalDef.h"
#include "cocos-ext.h"

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
	CC_RETURN_FALSE_IF(!Layer::init());

	InitUI();

	InitMenu();

	return true;
}


void CMenuScene::InitUI()
{
	Size visibleSize = GET_VISIBLESIZE();

	Scale9Sprite* pBg = Scale9Sprite::create("Images/menubg1.png");
	pBg->setPreferredSize(visibleSize);
	pBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pBg);

	auto pLogo = Sprite::create("Images/logo.png");
	Size logoSize = GET_CONTENTSIZE(pLogo);
	pLogo->setPosition(logoSize.width * 0.5f, visibleSize.height - logoSize.height * 0.6f);
	this->addChild(pLogo);

	auto pHand = Sprite::create("Images/hand.png");
	Size handSize = GET_CONTENTSIZE(pHand);
	pHand->setPosition(visibleSize.width / 4, handSize.height / 2);
	this->addChild(pHand);

	m_pFireSprite = Sprite::createWithSpriteFrameName("fire1.png");
	Size fireSize = GET_CONTENTSIZE(m_pFireSprite);
	m_pFireSprite->setScale(visibleSize.width * 1.1f / fireSize.width);
	m_pFireSprite->setPosition(visibleSize.width / 2, fireSize.height / 2);
	this->addChild(m_pFireSprite);
	
	//»ðÑæ¶¯»­¸üÐÂ
	this->scheduleUpdate();

	//±³¾°ÒôÀÖ
	LOOP_PLAY_BGMUSIC(BGM_MENU1);
}


//³õÊ¼»¯²Ëµ¥
void CMenuScene::InitMenu()
{

}



void CMenuScene::update(float dt)
{
	m_fFireAnimTime += dt;
	if (FLOAT_GE(m_fFireAnimTime, 0.1f))
	{
		m_fFireAnimTime = 0;

		//ÉèÖÃË÷Òý
		if (++m_iFireAnimIndex > FIRE_INDEX_MAX)
		{
			m_iFireAnimIndex = 1;
		}

		//ÇÐ»»ÏÂÒ»Ö¡»ðÑæÍ¼Æ¬
		m_pFireSprite->setSpriteFrame(GET_SPRITEFRAME(StringUtils::format("fire%d.png", m_iFireAnimIndex)));
	}
}