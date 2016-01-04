#include "GameScene.h"
#include "GlobalDef.h"

USING_NS_CC;

CGameScene::CGameScene() : m_pPersonSpr(nullptr), m_pLeftBtn(nullptr), m_pRightBtn(nullptr), m_pUpBtn(nullptr), m_pDownBtn(nullptr)
{
	for (int i = 0; i < 5; ++i)
	{
		m_pArrScore[i] = nullptr;
	}

	for (int i = 0; i < 5; ++i)
	{
		m_pArrRate[i] = nullptr;
	}
}


CGameScene::~CGameScene()
{
}


Scene* CGameScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = CGameScene::create();
	scene->addChild(layer);
	return scene;
}


bool CGameScene::init()
{
	CC_RETURN_FALSE_IF(!Layer::init());

	InitUI();

	CreateTouchListener();

	return true;
}


void CGameScene::InitUI()
{
	Size visibleSize = GET_VISIBLESIZE();

	auto pBg = Sprite::create("Images/menubg.png");
	Size BgSize = GET_CONTENTSIZE(pBg);
	pBg->setScale(visibleSize.width / BgSize.width, visibleSize.height / BgSize.height);
	pBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pBg);

	//初始化人物
	UpdatePerson(DIRECTION::NORMAL);

	//初始化分数
	auto pScore = Sprite::create("Images/score.png");
	pScore->setPosition(40, visibleSize.height - 44);
	this->addChild(pScore);
	UpdateScore(0);

	//初始化倍率
	auto pRate = CREATE_SPRITEWITHNAME("num_10.png");
	pRate->setPosition(40, visibleSize.height - 110);
	pRate->setScale(0.7f);
	this->addChild(pRate);
	UpdateRate(10);

	//创建按钮
	m_pUpBtn = CREATE_SPRITEWITHNAME("up_normal.png");
	m_pLeftBtn = CREATE_SPRITEWITHNAME("left_normal.png");
	m_pDownBtn = CREATE_SPRITEWITHNAME("down_normal.png");
	m_pRightBtn = CREATE_SPRITEWITHNAME("right_normal.png");

	//计算间距
	Size btnSize = GET_CONTENTSIZE(m_pUpBtn);
	float fBtnPadding = (visibleSize.width - btnSize.width * 4) / 5;

	//设置位置
	float fCurX = fBtnPadding;
	m_pUpBtn->setPosition(fCurX + btnSize.width / 2, btnSize.height);
	this->addChild(m_pUpBtn);

	fCurX += btnSize.width + fBtnPadding;
	m_pLeftBtn->setPosition(fCurX + btnSize.width / 2, btnSize.height);
	this->addChild(m_pLeftBtn);

	fCurX += btnSize.width + fBtnPadding;
	m_pDownBtn->setPosition(fCurX + btnSize.width / 2, btnSize.height);
	this->addChild(m_pDownBtn);

	fCurX += btnSize.width + fBtnPadding;
	m_pRightBtn->setPosition(fCurX + btnSize.width / 2, btnSize.height);
	this->addChild(m_pRightBtn);
}


//更新人物
void CGameScene::UpdatePerson(int iDirection)
{
	Size visibleSize = GET_VISIBLESIZE();

	//获取选择的性别
	int iSex = GET_INTVALUE("Sex");

	const char* arrSexList[2] = { "male", "female" };
	std::string strName = StringUtils::format("%s_%d.png", arrSexList[iSex], iDirection);
	if (m_pPersonSpr != nullptr)
	{
		m_pPersonSpr->setSpriteFrame(GET_SPRITEFRAME(strName));
		return;
	}

	m_pPersonSpr = CREATE_SPRITEWITHNAME(strName);
	m_pPersonSpr->setPosition(visibleSize.width / 2, visibleSize.height / 3.5f);
	this->addChild(m_pPersonSpr);
}


//创建触摸监听
void CGameScene::CreateTouchListener()
{
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event)
	{
		//获取的当前触摸的目标
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		typedef std::vector<Touch*>::const_iterator VECTOR_TOUCH_ITER;
		for (VECTOR_TOUCH_ITER pIter = touches.begin(); pIter != touches.end(); ++pIter)
		{
			int iID = (*pIter)->getID();
			if (iID < 4)
			{
				//获取触摸点位置
				m_arrTouchPos[iID] = target->convertToNodeSpace((*pIter)->getLocation());
				log("onTouchesBegan iID=%d touchPos:%f, %f", iID, m_arrTouchPos[iID].x, m_arrTouchPos[iID].y);
			}
		}
	};

	touchListener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		//获取的当前触摸的目标
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		typedef std::vector<Touch*>::const_iterator VECTOR_TOUCH_ITER;
		for (VECTOR_TOUCH_ITER pIter = touches.begin(); pIter != touches.end(); ++pIter)
		{
			int iID = (*pIter)->getID();
			if (iID < 4)
			{
				//获取触摸点位置
				Vec2 touchEndPos = target->convertToNodeSpace((*pIter)->getLocation());
				log("onTouchEnded iID=%d touchPos:%f, %f", iID, touchEndPos.x, touchEndPos.y);
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}


//更新分数
void CGameScene::UpdateScore(int iScore, bool bUpdate)
{
	m_iScore = iScore;
	if (!bUpdate)
	{
		return;
	}

	Size visibleSize = GET_VISIBLESIZE();
	int iSprIndex = 0;
	if (m_iScore == 0)
	{
		m_pArrScore[iSprIndex] = CREATE_SPRITEWITHNAME("num_0.png");
		this->addChild(m_pArrScore[iSprIndex]);
		++iSprIndex;
	}
	else
	{
		int iTempScore = m_iScore;
		while (iTempScore > 0)
		{
			int iTempNum = iTempScore % 10;
			iTempScore /= 10;

			std::string strName = StringUtils::format("num_%d.png", iTempNum);
			if (m_pArrScore[iSprIndex] != nullptr)
			{
				m_pArrScore[iSprIndex]->setSpriteFrame(GET_SPRITEFRAME(strName));
			}
			else
			{
				m_pArrScore[iSprIndex] = CREATE_SPRITEWITHNAME(strName);
				this->addChild(m_pArrScore[iSprIndex]);
			}

			++iSprIndex;
		}
	}

	float fCurWidth = 80;
	float fNumMaxHeight = 44;
	for (int i = iSprIndex - 1; i >= 0; --i)
	{
		Size numSize = GET_CONTENTSIZE(m_pArrScore[i]) * 0.7f;
		fCurWidth += numSize.width;
		m_pArrScore[i]->setScale(0.7f);
		m_pArrScore[i]->setPosition(fCurWidth - numSize.width / 2, visibleSize.height - fNumMaxHeight);
	}
}


//更新倍数
void CGameScene::UpdateRate(int iRate, bool bUpdate)
{
	m_iRate = iRate < 1 ? 1 : iRate;

	Size visibleSize = GET_VISIBLESIZE();
	int iSprIndex = 0;
	
	int iTempRate = m_iRate;
	while (iTempRate > 0)
	{
		int iTempNum = iTempRate % 10;
		iTempRate /= 10;

		std::string strName = StringUtils::format("num_%d.png", iTempNum);

		if (m_pArrRate[iSprIndex] != nullptr)
		{
			m_pArrRate[iSprIndex]->setSpriteFrame(GET_SPRITEFRAME(strName));
		}
		else
		{
			m_pArrRate[iSprIndex] = CREATE_SPRITEWITHNAME(strName);
			this->addChild(m_pArrRate[iSprIndex]);
		}
		m_pArrRate[iSprIndex]->setScale(0.7f + (m_iRate - 1) * 0.05f);


		++iSprIndex;
	}

	//设置位置
	float fCurWidth = 80;
	float fNumMaxHeight = 45 * 1.15f;
	float fCurHeight = visibleSize.height - 58 - fNumMaxHeight;
	for (int i = iSprIndex - 1; i >= 0; --i)
	{
		Size numSize = GET_CONTENTSIZE(m_pArrRate[i]) * (0.7f + (m_iRate - 1) * 0.05f);
		fCurWidth += numSize.width;
		m_pArrRate[i]->setPosition(fCurWidth - numSize.width / 2, fCurHeight);
	}
}
