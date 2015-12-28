#include "LoadScene.h"
#include "MenuScene.h"
#include "GlobalDef.h"

USING_NS_CC;

CLoadScene::CLoadScene()
{
}


CLoadScene::~CLoadScene()
{
}


Scene* CLoadScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = CLoadScene::create();
	scene->addChild(layer);
	return scene;
}

bool CLoadScene::init()
{
	CC_RETURN_FALSE_IF(!LayerColor::initWithColor(Color4B::WHITE));

	InitUI();

	return true;
}

void CLoadScene::InitUI()
{
	Size visibleSize = GET_VISIBLESIZE();

	auto bg = Sprite::create("Images/loadbg.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg);

	//2��������Դ
	this->scheduleOnce(schedule_selector(CLoadScene::OnEnterMenuScene), 2.0f);
}

void CLoadScene::LoadResources()
{
	//����Plistͼ��
	const char* arrPlistPath[1] = 
	{
		"Plist/fire.plist",
	};
	for (int i = 0; i < 1; ++i)
	{
		ADD_SPRITEFRAME(arrPlistPath[i]);
	}

	//Ԥ���ر������֡���Ч
	PRELOAD_BGMUSIC(BGM_MENU1);
	PRELOAD_BGMUSIC(BGM_MENU2);

	//��������
	TSET_STRING setSpriteFrame;
	for (int i = 1; i <= 11;++i)
	{
		setSpriteFrame.insert(StringUtils::format("fire%d.png", i));
	}
	PrecreateAnim(setSpriteFrame, "FireAnim", 0.1f);
}


//Ԥ��������
void CLoadScene::PrecreateAnim(const TSET_STRING& setSpriteFrame, const std::string& strAnimName, float fDelay)
{
	auto anim = Animation::create();
	anim->setDelayPerUnit(fDelay);
	TSET_STRINGITER pIter = setSpriteFrame.begin();
	for (; pIter != setSpriteFrame.end(); ++pIter)
	{
		anim->addSpriteFrame(GET_SPRITEFRAME(*pIter));
	}

	ADD_ANIM(anim, strAnimName);
}


void CLoadScene::OnEnterMenuScene(float dt)
{
	//������Դ
	LoadResources();

	//�˵�����
	auto menuScene = CMenuScene::CreateScene();
	REPLACE_SCENE(menuScene);
}
