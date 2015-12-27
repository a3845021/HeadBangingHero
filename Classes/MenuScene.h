#pragma once
#include "cocos2d.h"

class CMenuScene : public cocos2d::Layer
{
public:
	CMenuScene();
	~CMenuScene();

	static cocos2d::Scene* CreateScene();

	bool init();

	//初始化菜单
	void InitMenu();

	//初始化界面
	void InitUI();

	void update(float dt);

	CREATE_FUNC(CMenuScene);

private:
	cocos2d::Size m_visibleSize;

	float m_iBGMPlayTime;			//当前背景音乐播放时间

	const float BGM1_TIME = 28;		//第一首背景音乐持续时间
};

