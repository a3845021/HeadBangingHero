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

	//更新分数
	void UpdateScore(int iScore, bool bUpdate = true);

	//更新倍率
	void UpdateRate(int iRate, bool bUpdate = true);

	//创建人物
	void CreatePerson();

	CREATE_FUNC(CGameScene);

private:
	cocos2d::Sprite* m_pPersonSpr;		//人物Sprite

	cocos2d::Sprite* m_pArrScore[5];	//分数序列

	cocos2d::Sprite* m_pArrRate[3];		//倍率序列

	int m_iSex;							//性别

	int m_iDirection;					//方向

	int m_iScore;						//分数

	int m_iRate;						//倍率

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

