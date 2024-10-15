#include "Bullet.h"
#include "Enemy.h"
#include "IDamageable.h"
#include <typeinfo>	

Bullet* Bullet::create(Entity* entity, float spd, std::string bulletName)
{
	auto newObj = new Bullet();
	if (newObj != nullptr && newObj->init(entity, spd, bulletName))
	{
		newObj->autorelease();
		return newObj;
	}

	CC_SAFE_DELETE(newObj);
	return nullptr;
}

bool Bullet::init(Entity* entity, float spd, std::string bulletName)
{
	if (!Node::init())
	{
		return false;
	}

	_spd = spd;
	_entity = entity;

	_model = Sprite::create("Bullet/" + bulletName + ".png");
	auto material = PhysicsMaterial(1, 0, 1);
	auto body = PhysicsBody::createCircle(_model->getContentSize().width / 4);
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);

	auto physicListenner = EventListenerPhysicsContact::create();
	physicListenner->onContactBegin = CC_CALLBACK_1(Bullet::onContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicListenner, this);

	this->scheduleOnce([this](float) {
		this->removeFromParentAndCleanup(true);
		}, 10.0f, "remove_bullet_after_10_seconds");

	this->addChild(_model);
	return true;
}

void Bullet::fire(Vec2 direction)
{
	getPhysicsBody()->setVelocity(direction * _spd);
}

bool Bullet::onContactBegin(PhysicsContact& contact)
{
	// Get the nodes involved in the collision
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	// Identify which node is the bullet
	auto bullet = (nodeA == this) ? nodeA : (nodeB == this) ? nodeB : nullptr;
	auto target = (nodeA == this) ? nodeB : nodeA;

	// Proceed only if the bullet is valid and target is present
	if (bullet && target) {
		CCLOG("Bullet collided with target: %s", typeid(*target).name());

		// If the target is damageable (like an enemy), apply damage
		if (auto damageable = dynamic_cast<IDamageable*>(target)) {
			CCLOG("Enemy hit! Dealing damage: %d", _entity->getEntityStat()->_atk);
			damageable->takeDame(_entity->getEntityStat()->_atk);
		}

		this->removeFromParentAndCleanup(true);
	}

	return true;
}


//bool Bullet::onContactBegin(PhysicsContact& contact)
//{
//	auto nodeA = contact.getShapeA()->getBody()->getNode();
//	auto nodeB = contact.getShapeB()->getBody()->getNode();
//
//	auto bullet = (nodeA == this) ? this : (nodeB == this) ? this : nullptr;
//	auto target = (nodeA == this) ? nodeB : nodeA;
//
//	if (target) {
//		CCLOG("Target type: %s", typeid(*target).name());
//	}
//	else {
//		CCLOG("Target is null");
//	}
//
//	//auto damageable = dynamic_cast<IDamageable*>(target);
//	//if (damageable != nullptr) {
//	//	CCLOG("Target is damageable");
//	//	damageable->takeDame(_entity->getEntityStat()->_atk);
//	//}
//	//else {
//	//	CCLOG("Target is NOT damageable: %s", typeid(*target).name());
//	//}
//
//	if (bullet && target) {
//		if (auto damageable = dynamic_cast<IDamageable*>(target)) {
//			CCLOG("Enemy hit! Dealing damage: %d", _entity->getEntityStat()->_atk);
//			damageable->takeDame(_entity->getEntityStat()->_atk);
//		}
//		else {
//			CCLOG("Target is NOT damageable or is a game object.");
//		}
//	}
//	else {
//		CCLOG("No valid bullet-target interaction.");
//	}
//
//	this->removeFromParentAndCleanup(true);
//	return true;
//}