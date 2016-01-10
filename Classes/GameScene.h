#pragma once
#include "cocos2d.h"

class CGameScene : public cocos2d::Layer
{
public:
	CGameScene();
	~CGameScene();

	static cocos2d::Scene* CreateScene();

	bool init();

	void update(float dt);


	CREATE_FUNC(CGameScene);


private:

	//初始化UI
	void InitUI();

	//更新人物
	void UpdatePerson(int iDirection);

	//创建触摸监听
	void CreateTouchListener();

	//更新分数
	void UpdateScore(int iScore, bool bUpdate = true);

	//更新倍率
	void UpdateRate(int iRate);

	//创建箭头
	void CreateArrow(int iDirection);

	//创建一组箭头
	void CreateArrowGroup(int* arrArrow);

	//检查按下了哪个按钮
	int CheckButtonPressed(cocos2d::Vec2 pos);

	//按钮按下
	void OnButtonPressed(int iDirection);

	//获取指定方向按钮位置
	cocos2d::Sprite* GetButtonByDirection(int iDirection);

	//计算获得的分数
	int CalcScore(float fMaxDistance, float fCurDistance);

	//检查两个位置的距离
	bool CheckDistanceWithTwoPos(cocos2d::Vec2 srcPos, cocos2d::Vec2 destPos);

	//两个按钮方向转换为人物方向
	int TwoBtnDirConvToPersonDir(int iFirstDir, int iSecDir);

	//获取人物位置偏移
	cocos2d::Vec2 GetPersonPosOffset(int iSex, int iDirection);

private:
	typedef cocos2d::Vector<cocos2d::Sprite*> VECTOR_SPRITE;
	typedef VECTOR_SPRITE::iterator VECTOR_SPRITE_ITER;

private:
	cocos2d::Sprite* m_pPersonSpr;				//人物Sprite

	cocos2d::Sprite* m_pArrScore[5];			//分数序列

	cocos2d::Sprite* m_pArrRate[2];				//倍率序列

	cocos2d::Sprite* m_pLeftBtn;				//左按钮

	cocos2d::Sprite* m_pRightBtn;				//右按钮

	cocos2d::Sprite* m_pUpBtn;					//上按钮

	cocos2d::Sprite* m_pDownBtn;				//下按钮

	cocos2d::Vec2 m_arrTouchPos[4];				//触摸开始位置，支持4个点同时触摸

	VECTOR_SPRITE m_vecValidArrow;				//有效箭头序列

	VECTOR_SPRITE m_vecRecycleArrow;			//箭头回收序列

	int m_iScore;								//分数

	int m_iRate;								//倍率

	int m_iPersonDir;							//人物方向

	int m_iCurStageIdx;							//当前阶段索引

	int m_iLineIndex;							//当前到达第几行

	float m_iCurTime;							//当前经过时间

	bool m_bStageStarted;						//阶段是否开始

	bool bGameStarted;							//游戏开始标志

	enum SEX
	{
		MALE,
		FEMALE,
	};

	enum PERSON_DIRECTION
	{
		INVALID = -1,
		NORMAL,
		UP_RIGHT,
		RIGHT,
		RIGHT_DOWN,
		DOWN,
		DOWN_LEFT,
		LEFT,
		LEFT_UP,
		UP,
	};

	enum BUTTON_DIRECTION
	{
		BTN_INVALID = 0,
		BTN_UP,
		BTN_LEFT,
		BTN_DOWN,
		BTN_RIGHT,
	};

	enum 
	{
		CLICK_MAX_DISTANCE = 20,
		LINE_INTERVAL = 350,		//每350毫秒产生一组箭头
		LINE_SPEED = 230,			//速度
	};
};

