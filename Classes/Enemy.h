#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "IDamageable.h"
#include "AnimationUtils.h"

class Enemy : public Entity, public IDamageable
{
public:
    static Enemy* create(EntityInfo* info, EntityStat* entityStat);
    virtual bool init(EntityInfo* info, EntityStat* entityStat);
    void takeDame(int dame) override;
private:
    void die();
	void update(float dt);
};

#endif // !__ENEMY_H__