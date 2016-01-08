#ifndef __GLOBAL_DEFINE_H_
#define __GLOBAL_DEFINE_H_

// ---- 全局头文件 ----
#include <string>
#include <vector>


#define CC_RETURN_FALSE_IF(exp) if(exp){return false;}

#define FLOAT_EQ(a, b) (fabs(a - b) < 1e-6)

#define FLOAT_GT(a, b) (a - b > 1e-6)

#define FLOAT_GE(a, b) (FLOAT_GT(a, b) || FLOAT_EQ(a, b))

#define CHECK_VEC2_DISTANCE(a, b, max) ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) <= max * max)


// ---- cocos 常用函数宏定义 ----
#define DIRECTOR_INSTANCE Director::getInstance

#define GET_VISIBLESIZE Director::getInstance()->getVisibleSize

#define REPLACE_SCENE Director::getInstance()->replaceScene

#define PAUSE_SCENE Director::getInstance()->pause

#define RESUME_SCENE Director::getInstance()->resume

#define ADD_ANIM(anim, name) AnimationCache::getInstance()->addAnimation(anim, name)

#define GET_ANIM(name) AnimationCache::getInstance()->getAnimation(name)

#define GET_SPRITEFRAME(name) SpriteFrameCache::getInstance()->getSpriteFrameByName(name)

#define ADD_SPRITEFRAME(name) SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name)

#define CREATE_SPRITEWITHNAME(name) Sprite::createWithSpriteFrameName(name)

#define CREATE_SPRITE(name) Sprite::create(name)

#define AUDIO_INSTANCE CocosDenshion::SimpleAudioEngine::getInstance

#define PRELOAD_BGMUSIC(name) CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(name)

#define PLAY_BGMUSIC(name) CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(name)

#define LOOP_PLAY_BGMUSIC(name) CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(name, true)

#define STOP_BGMUSIC CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic

#define PRELOAD_EFFECT(name) CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(name)

#define PLAY_EFFECT(name) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(name)

#define GET_CONTENTSIZE(sprite) sprite->getContentSize()

#define USERDEFAULT_INSTANCE UserDefault::getInstance

#define GET_INTVALUE(key) UserDefault::getInstance()->getIntegerForKey(key)

#define SET_INTVALUE(key, value) UserDefault::getInstance()->setIntegerForKey(key, value)

#define GET_BOOLVALUE(key) UserDefault::getInstance()->getBoolForKey(key)

#define SET_BOOLVALUE(key, value) UserDefault::getInstance()->setBoolForKey(key, value)



// ---- 背景音乐 ----

#define BGM_MENU "Sounds/menubgm.mp3"
#define BGM_CLICK "Sounds/click.mp3"



// ---- 数据 ----
#define SONG_CONFIG_PATH "Config/songs.json"


// ---- 结构体 ---- 
struct ArrowData
{
	int arrArrow[4];
};


struct StageData
{
	double fDelay;	//阶段延迟
	std::vector<ArrowData> vecArrowData;
};

struct SongData
{
	int iSongID;
	std::string strSongName;
	std::string strAuthor;
	std::vector<StageData> vecStageData;
};

#endif //__GLOBAL_DEFINE_H_