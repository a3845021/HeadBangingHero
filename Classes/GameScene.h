#pragma once
#include "cocos2d.h"
class CGameScene : public cocos2d::Layer
{
public:
	CGameScene();
	~CGameScene();

	static cocos2d::Scene* CreateScene();

	bool init();

	//��ʼ��UI
	void InitUI();

	//��������
	void UpdatePerson(int iDirection);

	//������������
	void CreateTouchListener();

	//���·���
	void UpdateScore(int iScore, bool bUpdate = true);

	//���±���
	void UpdateRate(int iRate, bool bUpdate = true);

	//������ͷ
	void CreateArrow(int iDirection);


	void update(float dt);


	CREATE_FUNC(CGameScene);

private:
	typedef cocos2d::Vector<cocos2d::Sprite*> VECTOR_SPRITE;
	typedef VECTOR_SPRITE::iterator VECTOR_SPRITE_ITER;

private:
	cocos2d::Sprite* m_pPersonSpr;				//����Sprite

	cocos2d::Sprite* m_pArrScore[5];			//��������

	cocos2d::Sprite* m_pArrRate[3];				//��������

	cocos2d::Sprite* m_pLeftBtn;				//��ť

	cocos2d::Sprite* m_pRightBtn;				//�Ұ�ť

	cocos2d::Sprite* m_pUpBtn;					//�ϰ�ť

	cocos2d::Sprite* m_pDownBtn;				//�°�ť

	int m_iScore;								//����

	int m_iRate;								//����

	cocos2d::Vec2 m_arrTouchPos[4];				//������ʼλ�ã�֧��4����ͬʱ����

	VECTOR_SPRITE m_vecValidArrow;				//��Ч��ͷ����

	VECTOR_SPRITE m_vecRecycleArrow;			//��ͷ��������

	enum SEX
	{
		MALE,
		FEMALE,
	};

	enum PERSON_DIRECTION
	{
		NORMAL,
		UP_RIGHT,
		RIGHT,
		RIGHT_BOTTOM,
		BOTTOM,
		BOTTOM_LEFT,
		LEFT,
		LEFT_UP,
		UP,
	};

	enum BUTTON_DIRECTION
	{
		BTN_UP,
		BTN_LEFT,
		BTN_DOWN,
		BTN_RIGHT,
	};
};

