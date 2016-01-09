#include "GameScene.h"
#include "DataManager.h"
#include "GlobalDef.h"

USING_NS_CC;

CGameScene::CGameScene() : m_pPersonSpr(nullptr), m_pLeftBtn(nullptr), m_pRightBtn(nullptr), 
m_pUpBtn(nullptr), m_pDownBtn(nullptr), m_iScore(0), m_iCurStageIdx(0), m_iLineIndex(0), m_iRate(0),
m_iPersonDir(PERSON_DIRECTION::INVALID), m_bStageStarted(false), m_iCurTime(0), bGameStarted(true)
{
	
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

	//��ʼ������
	UpdatePerson(PERSON_DIRECTION::NORMAL);

	//��ʼ������
	auto pScore = Sprite::create("Images/score.png");
	pScore->setPosition(40, visibleSize.height - 44);
	this->addChild(pScore);

	//��ʼ������
	auto pRate = CREATE_SPRITEWITHNAME("num_10.png");
	pRate->setPosition(40, visibleSize.height - 110);
	pRate->setScale(0.7f);
	this->addChild(pRate);

	//��ʼ������Sprite�б�
	for (int i = 0; i < 5; ++i)
	{
		m_pArrScore[i] = Sprite::create();
		this->addChild(m_pArrScore[i]);
	}
	UpdateScore(0);

	//��ʼ�������б�
	for (int i = 0; i < 2; ++i)
	{
		m_pArrRate[i] = Sprite::create();
		this->addChild(m_pArrRate[i]);
	}
	UpdateRate(1);


	//������ť
	m_pUpBtn = CREATE_SPRITEWITHNAME("up_normal.png");
	m_pLeftBtn = CREATE_SPRITEWITHNAME("left_normal.png");
	log("%d", m_pLeftBtn);
	m_pDownBtn = CREATE_SPRITEWITHNAME("down_normal.png");
	m_pRightBtn = CREATE_SPRITEWITHNAME("right_normal.png");

	//������
	Size btnSize = GET_CONTENTSIZE(m_pUpBtn);
	float fBtnPadding = (visibleSize.width - btnSize.width * 4) / 5;

	//����λ��
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


	//��������
	PLAY_BGMUSIC("Sounds/song_0.mp3");
}


//��������
void CGameScene::UpdatePerson(int iDirection)
{
	if (m_iPersonDir == iDirection)
	{
		return;
	}
	m_iPersonDir = iDirection;

	Size visibleSize = GET_VISIBLESIZE();

	//��ȡѡ����Ա�
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


//������������
void CGameScene::CreateTouchListener()
{
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event)
	{
		//��ȡ�ĵ�ǰ������Ŀ��
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		int arrDirection[2] = { BTN_INVALID, BTN_INVALID };

		typedef std::vector<Touch*>::const_iterator VECTOR_TOUCH_ITER;
		for (VECTOR_TOUCH_ITER pIter = touches.begin(); pIter != touches.end(); ++pIter)
		{
			int iID = (*pIter)->getID();
			if (iID < 4)
			{
				//��ȡ������λ��
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

		//��������
		int iPersonDirection = TwoBtnDirConvToPersonDir(arrDirection[0], arrDirection[1]);
		UpdatePerson(iPersonDirection);
	};

	touchListener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event)
	{
		//��ȡ�ĵ�ǰ������Ŀ��
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		int iDirectionIndex = 0;

		typedef std::vector<Touch*>::const_iterator VECTOR_TOUCH_ITER;
		for (VECTOR_TOUCH_ITER pIter = touches.begin(); pIter != touches.end(); ++pIter)
		{
			int iID = (*pIter)->getID();
			if (iID < 4)
			{
				//��ȡ������λ��
				Vec2 touchEndPos = target->convertToNodeSpace((*pIter)->getLocation());
				//log("onTouchEnded iID=%d touchPos:%f, %f", iID, touchEndPos.x, touchEndPos.y);

				//С��20�����������
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


//������ť����ת��Ϊ���﷽��
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


//���·���
void CGameScene::UpdateScore(int iScore, bool bUpdate)
{
	m_iScore += iScore;

	Size visibleSize = GET_VISIBLESIZE();

	char arrNum[5] = { '\0' };
	sprintf(arrNum, "%d", m_iScore);

	int iSprIndex = 0;
	float fCurWidth = 80;
	float fNumMaxHeight = 44;
	float fPadding = 3;

	while (iSprIndex < 5)
	{
		std::string strName = StringUtils::format("num_%d.png", arrNum[iSprIndex] - 48);
		m_pArrScore[iSprIndex]->setSpriteFrame(GET_SPRITEFRAME(strName));
		
		//����λ��
		Size numSize = GET_CONTENTSIZE(m_pArrScore[iSprIndex]) * 0.7f;
		fCurWidth += numSize.width + fPadding;
		m_pArrScore[iSprIndex]->setScale(0.7f);
		m_pArrScore[iSprIndex]->setPosition(fCurWidth - numSize.width / 2, visibleSize.height - fNumMaxHeight);
		
		++iSprIndex;
		if (arrNum[iSprIndex] == 0)
		{
			break;
		}
	}
}


//���±���
void CGameScene::UpdateRate(int iRate)
{
	if (m_iRate == iRate)
	{
		return;
	}

	m_iRate = iRate < 1 ? 1 : (iRate > 10 ? 10 : iRate);

	Size visibleSize = GET_VISIBLESIZE();

	//λ��
	float fCurWidth = 80;
	float fNumMaxHeight = 45 * 1.15f;
	float fCurHeight = visibleSize.height - 58 - fNumMaxHeight;

	char arrNum[2] = { '\0' };
	sprintf(arrNum, "%d", m_iRate);

	int iSprIndex = 0;
	while (iSprIndex < 2)
	{
		std::string strName = StringUtils::format("num_%d.png", arrNum[iSprIndex] - 48);
		m_pArrRate[iSprIndex]->setSpriteFrame(GET_SPRITEFRAME(strName));
		m_pArrRate[iSprIndex]->setScale(0.7f + (m_iRate - 1) * 0.05f);

		//����λ��
		Size numSize = GET_CONTENTSIZE(m_pArrRate[iSprIndex]) * (0.7f + (m_iRate - 1) * 0.05f);
		fCurWidth += numSize.width;
		m_pArrRate[iSprIndex]->setPosition(fCurWidth - numSize.width / 2, fCurHeight);
		m_pArrRate[iSprIndex]->setVisible(true);

		++iSprIndex;
		if (arrNum[iSprIndex] == 0)
		{
			break;
		}
	}

	for (int i = iSprIndex; i < 2; ++i)
	{
		m_pArrRate[i]->setVisible(false);
	}
}


//������ͷ
void CGameScene::CreateArrow(int iDirection)
{
	Sprite* pArrow = nullptr;
	std::string strName = StringUtils::format("arrow_%d.png", iDirection);

	//�ȼ���ͷ�����������Ƿ��п��ü�ͷ
	if (m_vecRecycleArrow.size() > 0)
	{
		pArrow = m_vecRecycleArrow.back();
		m_vecRecycleArrow.popBack();

		pArrow->setSpriteFrame(GET_SPRITEFRAME(strName));
	}
	else
	{
		//����
		pArrow = Sprite::createWithSpriteFrameName(strName);
		this->addChild(pArrow);
	}

	//���ü�ͷλ��
	Sprite* pBtn = GetButtonByDirection(iDirection);
	assert(pBtn != nullptr);
	float fCurX = pBtn->getPositionX();
	float fCurY = GET_VISIBLESIZE().height + GET_CONTENTSIZE(pArrow).height / 2;
	pArrow->setPosition(fCurX, fCurY);

	//������Ч������
	m_vecValidArrow.pushBack(pArrow);
}


//����һ���ͷ
void CGameScene::CreateArrowGroup(int* arrArrow)
{
	for (int i = 0; i < 4; ++i)
	{
		if (arrArrow[i] == 1)
		{
			CreateArrow(i + 1);
		}
	}
}


//��鰴�����ĸ���ť
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


//��ť����
void CGameScene::OnButtonPressed(int iDirection)
{
	//��ȡ���µİ�ťλ�úʹ�С
	Sprite* pBtn = GetButtonByDirection(iDirection);
	assert(pBtn != nullptr);
	Vec2 btnPos = pBtn->getPosition();
	Size btnSize = GET_CONTENTSIZE(pBtn);

	//����������Ч�ļ�ͷ�����λ��
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

		//���Y��λ�ò�࣬������ֵС�ڼ�ͷ�Ͱ�ť�߶�һ��֮�ͼ���Ч
		Size arrowSize = GET_CONTENTSIZE(pArrow);
		float fMaxDistance = (btnSize.height + arrowSize.height) / 2;
		float fCurDistance = fabs(arrowPos.y - btnPos.y);
		if (FLOAT_GE(fMaxDistance, fCurDistance))
		{
			//���ü�ͷλ��
			pArrow->setPositionY(-arrowSize.height);

			//���յ�ǰ��ͷ
			pIter = m_vecValidArrow.erase(pIter);
			m_vecRecycleArrow.pushBack(pArrow);

			//���㱾�λ�õķ���
			int iScore = CalcScore(fMaxDistance, fCurDistance);
			log("iScore=%d", iScore);
			UpdateScore(iScore);

			UpdateRate(m_iRate + 1);
			continue;
		}

		++pIter;
	}
}


//��ȡָ������ťλ��
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


//�����õķ���
int CGameScene::CalcScore(float fMaxDistance, float fCurDistance)
{
	float fPercent = fCurDistance / fMaxDistance;
	int iScore = 10.0f / fPercent * m_iRate;
	return (iScore > 200 ? 200 : iScore);
}


//�������λ�õľ���
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


void CGameScene::update(float dt)
{
	m_iCurTime += dt;

	if (bGameStarted)
	{
		//�׶�����
		StageData* pStageData = CDataManager::getInstance()->GetStageData(0, m_iCurStageIdx);
		if (m_bStageStarted)
		{
			if (FLOAT_GE(m_iCurTime, LINE_INTERVAL * 0.001))
			{
				m_iCurTime = 0;
				ArrowData* pArrowData = &pStageData->mapArrowData[m_iLineIndex];
				CreateArrowGroup(pArrowData->arrArrow);

				//�л���һ��
				++m_iLineIndex;
				if (m_iLineIndex >= pStageData->mapArrowData.size())
				{
					//�л���һ���׶�
					++m_iCurStageIdx;
					if (m_iCurStageIdx >= CDataManager::getInstance()->GetStageCount(0))
					{
						bGameStarted = false;
					}

					//����δ��ʼ
					m_bStageStarted = false;
				}
			}
		}
		else
		{
			if (m_iCurTime >= pStageData->fDelay)
			{
				m_iCurTime = 0;

				//���õ�ǰ��
				m_iLineIndex = 0;

				//���ÿ�ʼ
				m_bStageStarted = true;
			}
		}
	}
	else if(m_vecValidArrow.empty())
	{
		log("Game over");
		this->unscheduleUpdate();
		return;
	}

	
	//�������м�ͷλ��
	VECTOR_SPRITE_ITER pIter = m_vecValidArrow.begin();
	while (pIter != m_vecValidArrow.end())
	{
		//����λ��
		Sprite* pArrow = *pIter;
		float fPosY = pArrow->getPositionY();
		fPosY -= dt * 200;
		pArrow->setPositionY(fPosY);

		//���߽�
		if (fPosY < -GET_CONTENTSIZE(pArrow).height / 2)
		{
			pIter = m_vecValidArrow.erase(pIter);
			m_vecRecycleArrow.pushBack(pArrow);

			UpdateRate(1);
		}
		else
		{
			++pIter;
		}
	}
}

