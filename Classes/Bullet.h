#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Entity.h"
#include "WeaponManager.h"	

using namespace cocos2d;

class Bullet : public Node
{
public:
	static Bullet* create(Entity* entity, float spd, std::string bulletName);
	virtual bool init(Entity* entity, float spd, std::string bulletName);

	void fire(Vec2 direction);
protected:
	Sprite* _model;
	Entity* _entity;
protected:
	float _spd;
	bool onContactBegin(PhysicsContact& contact);
};

#endif // !__BULLET_H__