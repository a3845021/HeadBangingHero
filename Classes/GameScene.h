#pragma once
#include "cocos2d.h"
class CGameScene : public cocos2d::Layer
{
public:
	CGameScene();
	~CGameScene();

	static cocos2d::Scene* CreateScene();

	bool init();

	//初始化UI
	void InitUI();

	//更新人物
	void UpdatePerson(int iDirection);

	//创建触摸监听
	void CreateTouchListener();

	//更新分数
	void UpdateScore(int iScore, bool bUpdate = true);

	//更新倍率
	void UpdateRate(int iRate, bool bUpdate = true);

	//创建箭头
	void CreateArrow(int iDirection);


	void update(float dt);


	CREATE_FUNC(CGameScene);

private:
	typedef cocos2d::Vector<cocos2d::Sprite*> VECTOR_SPRITE;
	typedef VECTOR_SPRITE::iterator VECTOR_SPRITE_ITER;

private:
	cocos2d::Sprite* m_pPersonSpr;				//人物Sprite

	cocos2d::Sprite* m_pArrScore[5];			//分数序列

	cocos2d::Sprite* m_pArrRate[3];				//倍率序列

	cocos2d::Sprite* m_pLeftBtn;				//左按钮

	cocos2d::Sprite* m_pRightBtn;				//右按钮

	cocos2d::Sprite* m_pUpBtn;					//上按钮

	cocos2d::Sprite* m_pDownBtn;				//下按钮

	int m_iScore;								//分数

	int m_iRate;								//倍率

	cocos2d::Vec2 m_arrTouchPos[4];				//触摸开始位置，支持4个点同时触摸

	VECTOR_SPRITE m_vecValidArrow;				//有效箭头序列

	VECTOR_SPRITE m_vecRecycleArrow;			//箭头回收序列

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

