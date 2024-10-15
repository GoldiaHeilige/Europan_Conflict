#include "Entity.h"
#include "AnimationUtils.h"

Entity* Entity::create(EntityInfo* info, EntityStat* entityStat)
{
    auto newObj = new Entity();
    if (newObj != nullptr && newObj->init(info, entityStat)) {
        newObj->autorelease();
        return newObj;
    }

    CC_SAFE_DELETE(newObj);
    return nullptr;
}

bool Entity::init(EntityInfo* info, EntityStat* entityStat)
{
    if (!Node::init()) {
        return false;
    }
    _entityStat = entityStat;
    _info = info;

    AnimationUtils::loadSpriteFrameCache("Entity/" + _info->_type + "/", _info->_name);
    auto idle = AnimationUtils::createAnimation(_info->_name, 0.5f);
    Animate* animateIdle = Animate::create(idle.first);
    auto idleLoop = RepeatForever::create(animateIdle);

    _model = Sprite::createWithSpriteFrameName("./" + _info->_name + " (1)");
    this->addChild(_model, 2);
    _model->runAction(idleLoop);

    _model->setAnchorPoint(Vec2(0.5, 0.5));

    return true;
}