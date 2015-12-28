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
	enum 
	{
		FIRE_INDEX_MAX = 11,			//火焰图片索引最大值
	};
	

	const float FIRE_ANIM_TIME = 0.1f;	//每隔0.1秒切换一次火焰

	float m_fFireAnimTime;				//火焰动画时间

	int m_iFireAnimIndex;				//火焰Frame索引

	cocos2d::Sprite* m_pFireSprite;		//火焰图片
};

