#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "EntityStat.h"
#include "EntityInfo.h"
#include "IDamageable.h"

USING_NS_CC;

class Entity : public Node
{
public:
    static Entity* create(EntityInfo* info, EntityStat* entityStat);
    virtual bool init(EntityInfo* info, EntityStat* entityStat);

    EntityStat* getEntityStat() { return _entityStat; }

protected:
    Sprite* _model;

protected:
    EntityStat* _entityStat;
    EntityInfo* _info;
};

#endif // !__ENTITY_H__
