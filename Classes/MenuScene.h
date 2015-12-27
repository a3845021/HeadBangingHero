#pragma once
#include "cocos2d.h"

class CMenuScene : public cocos2d::Layer
{
public:
	CMenuScene();
	~CMenuScene();

	static cocos2d::Scene* CreateScene();

	bool init();

	//��ʼ���˵�
	void InitMenu();

	//��ʼ������
	void InitUI();

	void update(float dt);

	CREATE_FUNC(CMenuScene);

private:
	cocos2d::Size m_visibleSize;

	float m_iBGMPlayTime;			//��ǰ�������ֲ���ʱ��

	const float BGM1_TIME = 28;		//��һ�ױ������ֳ���ʱ��
};

