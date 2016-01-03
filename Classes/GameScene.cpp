#include "GameScene.h"
#include "GlobalDef.h"

USING_NS_CC;

CGameScene::CGameScene() : m_iSex(SEX::MALE), m_iDirection(DIRECTION::NORMAL), m_pPersonSpr(NULL)
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

	CreatePerson();

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


void CGameScene::CreatePerson()
{
	Size visibleSize = GET_VISIBLESIZE();

	//获取选择的性别
	int iSex = GET_INTVALUE("Sex");

	const char* arrSexList[2] = {"male", "female"};
	std::string strName = StringUtils::format("%s_%d.png", arrSexList[iSex], m_iDirection);
	if (m_pPersonSpr != nullptr)
	{
		m_pPersonSpr->setSpriteFrame(GET_SPRITEFRAME(strName));
		return;
	}

	m_pPersonSpr = CREATE_SPRITEWITHNAME(strName);
	m_pPersonSpr->setPosition(visibleSize.width / 2, visibleSize.height / 3.5f);
	this->addChild(m_pPersonSpr);
}


