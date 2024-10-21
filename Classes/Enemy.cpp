#include "Enemy.h"

Enemy* Enemy::create(EntityInfo* info, EntityStat* entityStat)
{
	auto character = new Enemy();
	if (character != nullptr && character->init(info, entityStat)) {
		character->autorelease();
		return character;
	}

	CC_SAFE_DELETE(character);
	return nullptr;
}

bool Enemy::init(EntityInfo* info, EntityStat* entityStat)
{
	if (!Entity::init(info, entityStat))
	{
		return false;
	}

	auto material = PhysicsMaterial(1, 0, 1);
	auto body = PhysicsBody::createCircle(_model->getContentSize().width / 2);
	body->setContactTestBitmask(2);
	this->setPhysicsBody(body);

	this->scheduleUpdate();
	return true;
}

void Enemy::takeDame(int dame)
{
	_entityStat->_hp -= dame;
	CCLOG("Enemy took %d damage, remaining HP: %f", dame, _entityStat->_hp);

	if (_entityStat->_hp <= 0) {
		die(); 
	}
}

void Enemy::die()
{ 
	CCLOG("Enemy has died!");
	if (this->getPhysicsBody()) {
		this->removeComponent(this->getPhysicsBody());
	}
	this->removeChild(_model);

	AnimationUtils::loadSpriteFrameCache("Entity/" + _info->_type + "/", _info->_name + "_Death");

	auto deathAnimation = AnimationUtils::createAnimation(_info->_name + "_Death", 1.0f);
	auto animateDeath = Animate::create(deathAnimation.first);

	auto deathSprite = Sprite::createWithSpriteFrameName("./" + _info->_name + "_Death" + " (1)");
	this->addChild(deathSprite);

	auto sequence = Sequence::create(
		animateDeath,
		FadeOut::create(2.0f),
		CallFunc::create([this]() {
			this->removeFromParentAndCleanup(true);
			}),
		nullptr
	);
	deathSprite->runAction(sequence);
}

void Enemy::update(float dt)
{

}