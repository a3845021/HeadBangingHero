#ifndef __GLOBAL_DEFINE_H_
#define __GLOBAL_DEFINE_H_

// ---- 全局头文件 ----


// ---- cocos 常用函数宏定义 ----
#define CC_RETURN_FALSE_IF(exp) if(exp){return false;}

#define DIRECTOR_INSTANCE Director::getInstance

#define GET_VISIBLESIZE Director::getInstance()->getVisibleSize

#define REPLACE_SCENE Director::getInstance()->replaceScene

#define PAUSE_SCENE Director::getInstance()->pause

#define RESUME_SCENE Director::getInstance()->resume

#define GET_SPRITEFRAME(name) SpriteFrameCache::getInstance()->getSpriteFrameByName(name)

#define ADD_SPRITEFRAME(name) SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name)

#define AUDIO_INSTANCE CocosDenshion::SimpleAudioEngine::getInstance

#define PRELOAD_BGMUSIC(name) CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(name)

#define PLAY_BGMUSIC(name) CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(name)

#define LOOP_PLAY_BGMUSIC(name) CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(name, true)

#define STOP_BGMUSIC CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic

#define PRELOAD_EFFECT(name) CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(name)

#define PLAY_EFFECT(name) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(name)

#define CREATE_SPRITE(name) Sprite::createWithSpriteFrameName(name)

#define GET_CONTENTSIZE(sprite) sprite->getContentSize()

#define USERDEFAULT_INSTANCE UserDefault::getInstance

#define GET_INTVALUE(key) UserDefault::getInstance()->getIntegerForKey(key)

#define SET_INTVALUE(key, value) UserDefault::getInstance()->setIntegerForKey(key, value)

#define GET_BOOLVALUE(key) UserDefault::getInstance()->getBoolForKey(key)

#define SET_BOOLVALUE(key, value) UserDefault::getInstance()->setBoolForKey(key, value)



// ---- 背景音乐 ----

#define BGM_MENU1 "Sounds/menubgm.mp3"

#define BGM_MENU2 "Sounds/menubgm2.mp3"




#endif //__GLOBAL_DEFINE_H_