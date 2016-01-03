#pragma once
#include "cocos2d.h"
class CGameScene : public cocos2d::Layer
{
public:
	CGameScene();
	~CGameScene();

	static cocos2d::Scene* CreateScene();

	bool init();

	void InitUI();

	//���·���
	void UpdateScore(int iScore, bool bUpdate = true);

	//���±���
	void UpdateRate(int iRate, bool bUpdate = true);

	//��������
	void CreatePerson();

	CREATE_FUNC(CGameScene);

private:
	cocos2d::Sprite* m_pPersonSpr;		//����Sprite

	cocos2d::Sprite* m_pArrScore[5];	//��������

	cocos2d::Sprite* m_pArrRate[3];		//��������

	int m_iSex;							//�Ա�

	int m_iDirection;					//����

	int m_iScore;						//����

	int m_iRate;						//����

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

