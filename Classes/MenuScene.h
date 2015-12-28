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
	enum 
	{
		FIRE_INDEX_MAX = 11,			//����ͼƬ�������ֵ
	};
	

	const float FIRE_ANIM_TIME = 0.1f;	//ÿ��0.1���л�һ�λ���

	float m_fFireAnimTime;				//���涯��ʱ��

	int m_iFireAnimIndex;				//����Frame����

	cocos2d::Sprite* m_pFireSprite;		//����ͼƬ
};

