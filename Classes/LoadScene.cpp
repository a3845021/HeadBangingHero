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

	//2秒后加载资源
	this->scheduleOnce(schedule_selector(CLoadScene::OnEnterMenuScene), 2.0f);
}

void CLoadScene::LoadResources()
{
	//加载Plist图集
	const char* arrPlistPath[1] = 
	{
		"Plist/fire.plist",
	};
	for (int i = 0; i < 1; ++i)
	{
		ADD_SPRITEFRAME(arrPlistPath[i]);
	}

	//预加载背景音乐、音效
	PRELOAD_BGMUSIC(BGM_MENU1);
	PRELOAD_BGMUSIC(BGM_MENU2);

	//创建动画
	TSET_STRING setSpriteFrame;
	for (int i = 1; i <= 11;++i)
	{
		setSpriteFrame.insert(StringUtils::format("fire%d.png", i));
	}
	PrecreateAnim(setSpriteFrame, "FireAnim", 0.1f);
}


//预创建动画
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
	//加载资源
	LoadResources();

	//菜单界面
	auto menuScene = CMenuScene::CreateScene();
	REPLACE_SCENE(menuScene);
}
