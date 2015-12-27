#include "LoadScene.h"
#include "GlobalDef.h"
#include "MenuScene.h"

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
	PRELOAD_BGMUSIC(BGM_MENU1);
	PRELOAD_BGMUSIC(BGM_MENU2);
}


void CLoadScene::OnEnterMenuScene(float dt)
{
	//加载资源
	LoadResources();
	
	//菜单界面
	auto menuScene = CMenuScene::CreateScene();
	REPLACE_SCENE(menuScene);
}
