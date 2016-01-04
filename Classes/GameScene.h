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

	CREATE_FUNC(CGameScene);

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

	enum SEX
	{
		MALE,
		FEMALE,
	};

	enum DIRECTION
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
};

