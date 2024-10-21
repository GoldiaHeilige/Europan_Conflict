// IntroScene.h
#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "WeaponManager.h"
#include "UILayer/UIManager.h"
#include "MainMenuScene.h"
#include "KeyboardInput.h"
#include "Enemy.h"
#include "Bullet.h"
#include "SpawnObjects.h"
#include "IDamageable.h"

using namespace cocos2d;

class IntroScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createIntroScene();
    virtual bool init() override;
    void update(float dt) override;

private:
    void onMouseMove(Event* event);
    void onMouseDown(Event* event);

    cocos2d::TMXTiledMap* _map;
    cocos2d::TMXObjectGroup* _objectsCar;
    cocos2d::TMXObjectGroup* _objects_Industrial_Building_Normal;
    cocos2d::TMXObjectGroup* _objects_Industrial_Building_Broken;
    cocos2d::TMXObjectGroup* _object_Industrial_Elements_Broken;

    Sprite* addSpriteAtPosition(Vec2 position, int zOrder);
    Character* _character;
    cocos2d::Vec2 _direction;
    Vec2 _currentMousePos = Vec2::ZERO;

    CREATE_FUNC(IntroScene);
};

#endif // __INTROSCENE_H__
