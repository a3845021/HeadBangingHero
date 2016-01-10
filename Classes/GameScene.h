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

	//��ʼ��UI
	void InitUI();

	//��������
	void UpdatePerson(int iDirection);

	//������������
	void CreateTouchListener();

	//���·���
	void UpdateScore(int iScore, bool bUpdate = true);

	//���±���
	void UpdateRate(int iRate);

	//������ͷ
	void CreateArrow(int iDirection);

	//����һ���ͷ
	void CreateArrowGroup(int* arrArrow);

	//��鰴�����ĸ���ť
	int CheckButtonPressed(cocos2d::Vec2 pos);

	//��ť����
	void OnButtonPressed(int iDirection);

	//��ȡָ������ťλ��
	cocos2d::Sprite* GetButtonByDirection(int iDirection);

	//�����õķ���
	int CalcScore(float fMaxDistance, float fCurDistance);

	//�������λ�õľ���
	bool CheckDistanceWithTwoPos(cocos2d::Vec2 srcPos, cocos2d::Vec2 destPos);

	//������ť����ת��Ϊ���﷽��
	int TwoBtnDirConvToPersonDir(int iFirstDir, int iSecDir);

	//��ȡ����λ��ƫ��
	cocos2d::Vec2 GetPersonPosOffset(int iSex, int iDirection);

private:
	typedef cocos2d::Vector<cocos2d::Sprite*> VECTOR_SPRITE;
	typedef VECTOR_SPRITE::iterator VECTOR_SPRITE_ITER;

private:
	cocos2d::Sprite* m_pPersonSpr;				//����Sprite

	cocos2d::Sprite* m_pArrScore[5];			//��������

	cocos2d::Sprite* m_pArrRate[2];				//��������

	cocos2d::Sprite* m_pLeftBtn;				//��ť

	cocos2d::Sprite* m_pRightBtn;				//�Ұ�ť

	cocos2d::Sprite* m_pUpBtn;					//�ϰ�ť

	cocos2d::Sprite* m_pDownBtn;				//�°�ť

	cocos2d::Vec2 m_arrTouchPos[4];				//������ʼλ�ã�֧��4����ͬʱ����

	VECTOR_SPRITE m_vecValidArrow;				//��Ч��ͷ����

	VECTOR_SPRITE m_vecRecycleArrow;			//��ͷ��������

	int m_iScore;								//����

	int m_iRate;								//����

	int m_iPersonDir;							//���﷽��

	int m_iCurStageIdx;							//��ǰ�׶�����

	int m_iLineIndex;							//��ǰ����ڼ���

	float m_iCurTime;							//��ǰ����ʱ��

	bool m_bStageStarted;						//�׶��Ƿ�ʼ

	bool bGameStarted;							//��Ϸ��ʼ��־

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
		LINE_INTERVAL = 350,		//ÿ350�������һ���ͷ
		LINE_SPEED = 230,			//�ٶ�
	};
};

