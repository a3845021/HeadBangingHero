#pragma once
#include "cocos2d.h"

class CLoadScene : public cocos2d::LayerColor
{
private:
	typedef std::set<std::string> TSET_STRING;
	typedef TSET_STRING::iterator TSET_STRINGITER;

public:
	CLoadScene();
	~CLoadScene();
	
	static cocos2d::Scene* CreateScene();

	bool init();

	//初始化界面
	void InitUI();

	//加载资源
	void LoadResources();

	//预创建动画
	void PrecreateAnim(const TSET_STRING& setSpriteFrame, const std::string& strAnimName, float fDelay);

	void OnEnterMenuScene(float dt);

	CREATE_FUNC(CLoadScene);
};

