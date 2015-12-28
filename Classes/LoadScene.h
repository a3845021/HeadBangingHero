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

	//��ʼ������
	void InitUI();

	//������Դ
	void LoadResources();

	//Ԥ��������
	void PrecreateAnim(const TSET_STRING& setSpriteFrame, const std::string& strAnimName, float fDelay);

	void OnEnterMenuScene(float dt);

	CREATE_FUNC(CLoadScene);
};

