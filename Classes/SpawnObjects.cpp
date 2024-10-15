#include "SpawnObjects.h"

SpawnObjects::SpawnObjects(cocos2d::Node* parentNode) : _parentNode(parentNode) {}

void SpawnObjects::spawnCarsFromTiled(cocos2d::TMXTiledMap* map) {
    auto objectCarLayer = map->getObjectGroup("Car Normal");
    auto _objectsCar = objectCarLayer->getObjects();

    if (_objectsCar.empty()) {
        CCLOG("Khong co object nao trong object layer 'Car'.");
        return;
    }
    else {
        CCLOG("So luong object: %lu", _objectsCar.size());
    }

    for (auto& obj : _objectsCar) {
        auto objectInfo = obj.asValueMap();

        if (objectInfo["type"].asString() == "car") {
            float x = objectInfo["x"].asFloat();
            float y = objectInfo["y"].asFloat();
            float collisionWidth = objectInfo["collision_width"].asFloat();
            float collisionHeight = objectInfo["collision_height"].asFloat();

            std::string imageName = objectInfo["name"].asString();
            std::string imagePath = "Vehicle/Civil Vehicle/Civil Normal/" + imageName + ".png";

            if (cocos2d::FileUtils::getInstance()->isFileExist(imagePath)) {
                auto carSprite = cocos2d::Sprite::create(imagePath);
                if (carSprite != nullptr) {
                    carSprite->setPosition(cocos2d::Vec2(x, y));

                    if (collisionWidth > 0 && collisionHeight > 0) {
                        auto carBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(collisionWidth, collisionHeight));
                        carBody->setDynamic(false);
                        carBody->setContactTestBitmask(3);
                        carSprite->addComponent(carBody);
                    }
                    else {
                        CCLOG("Custom collision size not found, using default.");
                    }

                    float scale = objectInfo.find("scale") != objectInfo.end() ? objectInfo["scale"].asFloat() : 1.0f;
                    carSprite->setScale(scale);

                    float rotation = objectInfo.find("rotation") != objectInfo.end() ? objectInfo["rotation"].asFloat() : 0.0f;
                    carSprite->setRotation(rotation);
                    
                    _parentNode->addChild(carSprite);
                }
            }
        }
    }
}

// -------------------------- Builing & Objects -------------------------- //

void SpawnObjects::spawn_Building_Industrial_Normal(cocos2d::TMXTiledMap* map) {
    auto objects_Industrial_Building_Normal_Layer = map->getObjectGroup("Building Industrial Normal");
    auto _objects_Industrial_Building_Normal = objects_Industrial_Building_Normal_Layer->getObjects();

    if (_objects_Industrial_Building_Normal.empty()) {
        CCLOG("Khong co object nao trong object layer 'Building'.");
        return;
    }
    else {
        CCLOG("So luong object: %lu", _objects_Industrial_Building_Normal.size());
    }

    for (auto& obj : _objects_Industrial_Building_Normal) {
        auto objectInfo = obj.asValueMap();

        if (objectInfo["type"].asString() == "building") {
            float x = objectInfo["x"].asFloat();
            float y = objectInfo["y"].asFloat();
            float width = objectInfo["width"].asFloat();
            float height = objectInfo["height"].asFloat();

            std::string imageName = objectInfo["name"].asString();
            std::string imagePath = "Building/building_industrial/" + imageName + ".png";

            if (cocos2d::FileUtils::getInstance()->isFileExist(imagePath)) {
                auto _building_Industrial_Normal_Sprite = cocos2d::Sprite::create(imagePath);
                if (_building_Industrial_Normal_Sprite != nullptr) {
                    /*_building_Industrial_Normal_Sprite->setPosition(cocos2d::Vec2(x, y));*/
                    _building_Industrial_Normal_Sprite->setPosition(cocos2d::Vec2(x + width / 2, y + height / 0.675));

                    if (objectInfo.find("width") != objectInfo.end() && objectInfo.find("height") != objectInfo.end()) {
                        float width = objectInfo["width"].asFloat();
                        float height = objectInfo["height"].asFloat();

                        auto _building_Industrial_Normal_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(width,height));
                        _building_Industrial_Normal_Body->setDynamic(false);
                        _building_Industrial_Normal_Body->setContactTestBitmask(3);
                        _building_Industrial_Normal_Sprite->addComponent(_building_Industrial_Normal_Body);
                    }
                    else {
                        CCLOG("Rectangle shape data not found for building object.");
                    }

                    float scale = objectInfo.find("scale") != objectInfo.end() ? objectInfo["scale"].asFloat() : 1.0f;
                    _building_Industrial_Normal_Sprite->setScale(scale);

                    float rotation = objectInfo.find("rotation") != objectInfo.end() ? objectInfo["rotation"].asFloat() : 0.0f;
                    _building_Industrial_Normal_Sprite->setRotation(rotation);

                    _parentNode->addChild(_building_Industrial_Normal_Sprite);
                }
            }
        }
    }
}

void SpawnObjects::spawn_Building_Industrial_Broken(cocos2d::TMXTiledMap* map) {
    auto objects_Industrial_Building_Broken_Layer = map->getObjectGroup("Building Industrial Broken");
    auto _object_Industrial_Building_Broken = objects_Industrial_Building_Broken_Layer->getObjects();

    if (_object_Industrial_Building_Broken.empty()) {
        CCLOG("Khong co object nao trong object layer 'Building'.");
        return;
    }
    else {
        CCLOG("So luong object: %lu", _object_Industrial_Building_Broken.size());
    }

    for (auto& obj : _object_Industrial_Building_Broken) {
        auto objectInfo = obj.asValueMap();

        if (objectInfo["type"].asString() == "building") {
            float x = objectInfo["x"].asFloat();
            float y = objectInfo["y"].asFloat();

            std::string imageName = objectInfo["name"].asString();
            std::string imagePath = "Building/building_industrial/" + imageName + ".png";

            if (cocos2d::FileUtils::getInstance()->isFileExist(imagePath)) {
                auto _Elements_Industrial_Broken_Sprite = cocos2d::Sprite::create(imagePath);
                if (_Elements_Industrial_Broken_Sprite != nullptr) {
                    _Elements_Industrial_Broken_Sprite->setPosition(cocos2d::Vec2(x, y));

                    if (objectInfo.find("width") != objectInfo.end() && objectInfo.find("height") != objectInfo.end()) {
                        float width = objectInfo["width"].asFloat();
                        float height = objectInfo["height"].asFloat();

                        auto _building_Industrial_Broken_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(width, height));
                        _building_Industrial_Broken_Body->setDynamic(false);
                        _building_Industrial_Broken_Body->setContactTestBitmask(3);
                        _Elements_Industrial_Broken_Sprite->addComponent(_building_Industrial_Broken_Body);
                    }
                    else {
                        CCLOG("Rectangle shape data not found for building object.");
                    }

                    float scale = objectInfo.find("scale") != objectInfo.end() ? objectInfo["scale"].asFloat() : 1.0f;
                    _Elements_Industrial_Broken_Sprite->setScale(scale);

                    float rotation = objectInfo.find("rotation") != objectInfo.end() ? objectInfo["rotation"].asFloat() : 0.0f;
                    _Elements_Industrial_Broken_Sprite->setRotation(rotation);

                    _parentNode->addChild(_Elements_Industrial_Broken_Sprite);
                }
            }
        }
    }
}

void SpawnObjects::spawn_Industrial_Elements_Broken(cocos2d::TMXTiledMap* map) {
    auto objects_Industrial_Elements_Broken_Layer = map->getObjectGroup("Elements Industrial Broken");
    auto _object_Industrial_Elements_Broken = objects_Industrial_Elements_Broken_Layer->getObjects();

    if (_object_Industrial_Elements_Broken.empty()) {
        CCLOG("Khong co object nao trong object layer 'element'.");
        return;
    }
    else {
        CCLOG("So luong object: %lu", _object_Industrial_Elements_Broken.size());
    }

    for (auto& obj : _object_Industrial_Elements_Broken) {
        auto objectInfo = obj.asValueMap();

        if (objectInfo["type"].asString() == "element") {
            float x = objectInfo["x"].asFloat();
            float y = objectInfo["y"].asFloat();

            std::string imageName = objectInfo["name"].asString();
            std::string imagePath = "Building/building_industrial/Elements/" + imageName + ".png";

            if (cocos2d::FileUtils::getInstance()->isFileExist(imagePath)) {
                auto _Elements_Industrial_Broken_Sprite = cocos2d::Sprite::create(imagePath);
                if (_Elements_Industrial_Broken_Sprite != nullptr) {
                    _Elements_Industrial_Broken_Sprite->setPosition(cocos2d::Vec2(x, y));

                    if (objectInfo.find("width") != objectInfo.end() && objectInfo.find("height") != objectInfo.end()) {
                        float width = objectInfo["width"].asFloat();
                        float height = objectInfo["height"].asFloat();

                        auto _Elements_Industrial_Broken_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(width, height));
                        _Elements_Industrial_Broken_Body->setDynamic(false);
                        _Elements_Industrial_Broken_Body->setContactTestBitmask(3);
                        _Elements_Industrial_Broken_Sprite->addComponent(_Elements_Industrial_Broken_Body);
                    }
                    else {
                        CCLOG("Rectangle shape data not found for car object.");
                    }

                    float scale = objectInfo.find("scale") != objectInfo.end() ? objectInfo["scale"].asFloat() : 1.0f;
                    _Elements_Industrial_Broken_Sprite->setScale(scale);

                    float rotation = objectInfo.find("rotation") != objectInfo.end() ? objectInfo["rotation"].asFloat() : 0.0f;
                    _Elements_Industrial_Broken_Sprite->setRotation(rotation);

                    _parentNode->addChild(_Elements_Industrial_Broken_Sprite);
                }
            }
        }
    }
}

// -------------------------- Static Decoration -------------------------- //

void SpawnObjects::spawnFiresFromTiled(cocos2d::TMXTiledMap* map) {
    auto objectFireLayer = map->getObjectGroup("Fire Cycle Test");
    auto _objectsFire = objectFireLayer->getObjects();

    if (_objectsFire.empty()) {
        CCLOG("No objects found in the object layer 'Fire Cycle Test'.");
        return;
    }

    for (auto& obj : _objectsFire) {
        auto objectInfo = obj.asValueMap();

        std::string fireName = objectInfo["name"].asString(); 
        float x = objectInfo["x"].asFloat();
        float y = objectInfo["y"].asFloat();

        AnimationUtils::loadSpriteFrameCache("Effects/Roof_fire/", fireName); 
        auto fireAnimation = AnimationUtils::createAnimation(fireName, 0.5f);  
        auto animateFire = Animate::create(fireAnimation.first);
        auto fireLoop = RepeatForever::create(animateFire);

        auto fireSprite = Sprite::createWithSpriteFrameName("./" + fireName + " (1)");
        fireSprite->setPosition(Vec2(x, y));
        fireSprite->runAction(fireLoop);

        _parentNode->addChild(fireSprite);
    }
}