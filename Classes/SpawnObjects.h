#ifndef __SPAWN_OBJECTS_H__
#define __SPAWN_OBJECTS_H__

#include "cocos2d.h"
#include "AnimationUtils.h"

class SpawnObjects {
public:
    SpawnObjects(cocos2d::Node* parentNode); // Khởi tạo với node cha
    // Vehicle
    void spawnCarsFromTiled(cocos2d::TMXTiledMap* map);

    // Building & Elements
    void spawn_Building_Industrial_Normal(cocos2d::TMXTiledMap* map);
    void spawn_Building_Industrial_Broken(cocos2d::TMXTiledMap* map);
    void spawn_Industrial_Elements_Broken(cocos2d::TMXTiledMap* map);

    // Static Decoration
    void spawnFiresFromTiled(cocos2d::TMXTiledMap* map);

private:
    cocos2d::Node* _parentNode; // Node cha để thêm các đối tượng
};

#endif // __SPAWN_OBJECTS_H__
