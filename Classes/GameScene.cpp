#include "GameScene.h"
#include "GlobalDef.h"
#include "DataManager.h"

USING_NS_CC;

CGameScene::CGameScene() : m_pPersonSpr(nullptr), m_pLeftBtn(nullptr), m_pRightBtn(nullptr), 
m_pUpBtn(nullptr), m_pDownBtn(nullptr), m_iScore(0), 
m_iPersonDir(PERSON_DIRECTION::INVALID), m_iCurStageIdx(0), m_iLineIndex(-1)
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

	UpdateStageData();

	this->scheduleUpdate();

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
	UpdatePerson(PERSON_DIRECTION::NORMAL);

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
	UpdateRate(1);

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


//更新Stage数据
void CGameScene::UpdateStageData()
{
	m_pStageData = CDataManager::getInstance()->GetArrowData(0, m_iCurStageIdx);
}


//更新人物
void CGameScene::UpdatePerson(int iDirection)
{
	if (m_iPersonDir == iDirection)
	{
		return;
	}
	m_iPersonDir = iDirection;

	Size visibleSize = GET_VISIBLESIZE();

	//获取选择的性别
	int iSex = GET_INTVALUE("Sex");
	iSex = 1;

	const char* arrSexList[2] = { "male", "female" };
	std::string strName = StringUtils::format("%s_%d.png", arrSexList[iSex], m_iPersonDir);
	if (m_pPersonSpr != nullptr)
	{
		m_pPersonSpr->setSpriteFrame(GET_SPRITEFRAME(strName));
	}
	else
	{
		m_pPersonSpr = CREATE_SPRITEWITHNAME(strName);
		m_pPersonSpr->setScale(1.3f);
		this->addChild(m_pPersonSpr);
	}

	Vec2 pos = Vec2(visibleSize.width / 2, visibleSize.height / 4) + GetPersonPosOffset(iSex, m_iPersonDir);
	m_pPersonSpr->setPosition(pos);
}


//创建触摸监听
void CGameScene::CreateTouchListener()
{
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event)
	{
		//获取的当前触摸的目标
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		int arrDirection[2] = { BTN_INVALID, BTN_INVALID };

		typedef std::vector<Touch*>::const_iterator VECTOR_TOUCH_ITER;
		for (VECTOR_TOUCH_ITER pIter = touches.begin(); pIter != touches.end(); ++pIter)
		{
			int iID = (*pIter)->getID();
			if (iID < 4)
			{
				//获取触摸点位置
				m_arrTouchPos[iID] = target->convertToNodeSpace((*pIter)->getLocation());
				//log("onTouchesBegan iID=%d touchPos:%f, %f", iID, m_arrTouchPos[iID].x, m_arrTouchPos[iID].y);

				int iDirection = CheckButtonPressed(m_arrTouchPos[iID]);
				if (iDirection > BTN_INVALID)
				{
					arrDirection[0] = arrDirection[1];
					arrDirection[1] = iDirection;
				}
			}
		}

		//更新人物
		int iPersonDirection = TwoBtnDirConvToPersonDir(arrDirection[0], arrDirection[1]);
		UpdatePerson(iPersonDirection);
	};

	touchListener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		//获取的当前触摸的目标
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		int iDirectionIndex = 0;

		typedef std::vector<Touch*>::const_iterator VECTOR_TOUCH_ITER;
		for (VECTOR_TOUCH_ITER pIter = touches.begin(); pIter != touches.end(); ++pIter)
		{
			int iID = (*pIter)->getID();
			if (iID < 4)
			{
				//获取触摸点位置
				Vec2 touchEndPos = target->convertToNodeSpace((*pIter)->getLocation());
				//log("onTouchEnded iID=%d touchPos:%f, %f", iID, touchEndPos.x, touchEndPos.y);

				//小于20像素算作点击
				if (CheckDistanceWithTwoPos(m_arrTouchPos[iID], touchEndPos))
				{
					int iDirection = CheckButtonPressed(m_arrTouchPos[iID]);
					if (iDirection > BTN_INVALID)
					{
						OnButtonPressed(iDirection);
					}
				}
			}
		}

		UpdatePerson(PERSON_DIRECTION::NORMAL);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}


//两个按钮方向转换为人物方向
int CGameScene::TwoBtnDirConvToPersonDir(int iFirstDir, int iSecDir)
{
	const int arrRelation[5][5] =
	{
		//{ NORMAL, UP, LEFT, DOWN, RIGHT },
		{ NORMAL, LEFT_UP, DOWN_LEFT, RIGHT_DOWN, UP_RIGHT },
		{ UP, UP, LEFT_UP, DOWN, UP_RIGHT },
		{ LEFT, LEFT_UP, LEFT, DOWN_LEFT, RIGHT },
		{ DOWN, UP, DOWN_LEFT, DOWN, RIGHT_DOWN },
		{ RIGHT, UP_RIGHT, LEFT, RIGHT_DOWN, RIGHT },
	};

	return arrRelation[iFirstDir][iSecDir];
}


//更新分数
void CGameScene::UpdateScore(int iScore, bool bUpdate)
{
	m_iScore += iScore;
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
	float fPadding = 3;
	for (int i = iSprIndex - 1; i >= 0; --i)
	{
		Size numSize = GET_CONTENTSIZE(m_pArrScore[i]) * 0.7f;
		fCurWidth += numSize.width + fPadding;
		m_pArrScore[i]->setScale(0.7f);
		m_pArrScore[i]->setPosition(fCurWidth - numSize.width / 2, visibleSize.height - fNumMaxHeight);
	}
}


//更新倍数
void CGameScene::UpdateRate(int iRate)
{
	m_iRate = iRate < 1 ? 1 : (iRate > 10 ? 10 : iRate);

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


//创建箭头
void CGameScene::CreateArrow(int iDirection)
{
	Sprite* pArrow = nullptr;
	std::string strName = StringUtils::format("arrow_%d.png", iDirection);

	//先检查箭头回收序列中是否有可用箭头
	if (m_vecRecycleArrow.size() > 0)
	{
		pArrow = m_vecRecycleArrow.back();
		m_vecRecycleArrow.popBack();

		pArrow->setSpriteFrame(GET_SPRITEFRAME(strName));
		pArrow->setVisible(true);
	}
	else
	{
		//创建
		pArrow = Sprite::createWithSpriteFrameName(strName);
	}

	//设置箭头位置
	Sprite* pBtn = GetButtonByDirection(iDirection);
	assert(pBtn != nullptr);
	float fCurX = pBtn->getPositionX();
	float fCurY = GET_VISIBLESIZE().height + GET_CONTENTSIZE(pArrow).height / 2;
	pArrow->setPosition(fCurX, fCurY);
	this->addChild(pArrow);

	//放入有效序列中
	m_vecValidArrow.pushBack(pArrow);
}


void CGameScene::update(float dt)
{
	m_iCurTime += dt;

	//更新所有箭头位置
	VECTOR_SPRITE_ITER pIter = m_vecValidArrow.begin();
	while (pIter != m_vecValidArrow.end())
	{
		//更新位置
		Sprite* pArrow = *pIter;
		float fPosY = pArrow->getPositionY();
		fPosY -= dt * 200;
		pArrow->setPositionY(fPosY);
		//log("fPosY=%f", fPosY);

		//检查边界
		if (fPosY < -GET_CONTENTSIZE(pArrow).height / 2)
		{
			pIter = m_vecValidArrow.erase(pIter);
			m_vecRecycleArrow.pushBack(pArrow);
		}
		else
		{
			++pIter;
		}
	}
}


//检查按下了哪个按钮
int CGameScene::CheckButtonPressed(Vec2 pos)
{
	for (int i = BTN_UP; i <= BTN_RIGHT; ++i)
	{
		Sprite* pBtn = GetButtonByDirection(i);
		if (pBtn->getBoundingBox().containsPoint(pos))
		{
			return i;
		}
	}

	return BTN_INVALID;
}


//按钮按下
void CGameScene::OnButtonPressed(int iDirection)
{
	//获取按下的按钮位置和大小
	Sprite* pBtn = GetButtonByDirection(iDirection);
	assert(pBtn != nullptr);
	Vec2 btnPos = pBtn->getPosition();
	Size btnSize = GET_CONTENTSIZE(pBtn);

	//遍历所有有效的箭头，检查位置
	bool bArrowFlag = false;
	VECTOR_SPRITE_ITER pIter = m_vecValidArrow.begin();
	while (pIter != m_vecValidArrow.end())
	{
		Sprite* pArrow = (Sprite*)(*pIter);
		Vec2 arrowPos = pArrow->getPosition();
		if (!FLOAT_EQ(arrowPos.x, btnPos.x))
		{
			++pIter;
			continue;
		}

		//检查Y轴位置差距，差距绝对值小于箭头和按钮高度一半之和即有效
		Size arrowSize = GET_CONTENTSIZE(pArrow);
		float fMaxDistance = (btnSize.height + arrowSize.height) / 2;
		float fCurDistance = fabs(arrowPos.y - btnPos.y);
		if (!FLOAT_GE(fMaxDistance, fCurDistance))
		{
			++pIter;
			continue;
		}
		
		//隐藏箭头
		pArrow->setVisible(false);

		//回收当前箭头
		pIter = m_vecValidArrow.erase(pIter);
		m_vecRecycleArrow.pushBack(pArrow);

		//计算本次获得的分数
		int iScore = CalcScore(fMaxDistance, fCurDistance);
		log("iScore=%d", iScore);
		UpdateScore(iScore);

		bArrowFlag = true;
	}

	UpdateRate(bArrowFlag ? (m_iRate + 1) : 1);
}


//获取指定方向按钮位置
Sprite* CGameScene::GetButtonByDirection(int iDirection)
{
	switch (iDirection)
	{
	case BTN_UP:
		return m_pUpBtn;
		break;
	case BTN_LEFT:
		return m_pLeftBtn;
		break;
	case BTN_RIGHT:
		return m_pRightBtn;
		break;
	case BTN_DOWN:
		return m_pDownBtn;
		break;
	}

	return nullptr;
}


//计算获得的分数
int CGameScene::CalcScore(float fMaxDistance, float fCurDistance)
{
	float fPercent = fCurDistance / fMaxDistance;
	int iScore = 10.0f / fPercent * m_iRate;
	return (iScore > 200 ? 200 : iScore);
}


//检查两个位置的距离
bool CGameScene::CheckDistanceWithTwoPos(Vec2 srcPos, Vec2 destPos)
{
	float fDistance = (destPos.x - srcPos.x) * (destPos.x - srcPos.x) + (destPos.y - srcPos.y) * (destPos.y - srcPos.y);
	return FLOAT_GE(CLICK_MAX_DISTANCE * CLICK_MAX_DISTANCE, fDistance);
}


Vec2 CGameScene::GetPersonPosOffset(int iSex, int iDirection)
{
	if (iDirection == PERSON_DIRECTION::INVALID)
	{
		return Vec2::ZERO;
	}

	const Vec2 arrPosList[9][2] =
	{
		{ Vec2(-18, -0.5f), Vec2(-16.5f, 6.5f) },
		{ Vec2(-18.5f, 7), Vec2(-16.5f, 13.5f) },
		{ Vec2(-3, 0),	Vec2(0.5f, 6) },
		{ Vec2(-18.5f, 0), Vec2(-16.5f, 6.5f) },
		{ Vec2(-18.5f, 0), Vec2(-16.5f, 6.5f) },
		{ Vec2(-18, 0.5f), Vec2(-16.5f, 6.5f) },
		{ Vec2(-18.5f, 0), Vec2(-16.5f, 6.5f) },
		{ Vec2(-18.5f, 11), Vec2(-16.5f, 13.5f) },
		{ Vec2(-18.5f, 23.5f), Vec2(-16, 32) },
	};

	return arrPosList[iDirection][iSex];
}