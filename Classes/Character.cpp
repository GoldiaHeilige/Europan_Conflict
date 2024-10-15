#include "Character.h"

Character* Character::create(EntityInfo* info, EntityStat* entityStat)
{
    auto character = new Character();
    if (character != nullptr && character->init(info, entityStat)) {
        character->autorelease();
        return character;
    }

    CC_SAFE_DELETE(character);
    return nullptr;
}

bool Character::init(EntityInfo* info, EntityStat* entityStat)
{
    if (!Entity::init(info, entityStat))
    {
        return false;
    }

    auto characterBody = PhysicsBody::createBox(this->getContentSize());
    characterBody->setDynamic(true); 
    characterBody->setContactTestBitmask(true);
    this->addComponent(characterBody);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    _ammoLabel = Label::createWithTTF("0 / 0", "fonts/Marker Felt.ttf", 24);
    //_ammoLabel->setPosition(visibleSize.width - _ammoLabel->getContentSize().width / 2 - 10, 20); // Bottom-right corner
    _ammoLabel->setPosition(visibleSize / 2);
    this->addChild(_ammoLabel, 100);

    this->scheduleUpdate();
    return true;
}

void Character::takeDame(int dame)
{
	_entityStat->_hp -= dame;
	CCLOG("Hero took %d damage, remaining HP: %f", dame, _entityStat->_hp);

	if (_entityStat->_hp <= 0) {
		die();
	}
}

void Character::die()
{
	CCLOG("Hero has died!");
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
        CallFunc::create([this]() {
            // Chuyển cảnh về MainMenuScene
            auto mainMenuScene = MainMenuScene::create();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, mainMenuScene));
            }),
        nullptr
	);
	deathSprite->runAction(sequence);
}

void Character::shoot(Vec2 direction) {
    _weaponManager.shoot(this, direction);
}

void Character::switchWeapon(WeaponManager::WeaponType newWeaponType) {
    WeaponManager::getInstance()->setCurrentWeapon(newWeaponType);
    _stat->_weaponStats = WeaponManager::getInstance()->getCurrentWeaponStats(); // Update weapon stats
    updateAmmoDisplay();
}

void Character::attack() {
    float attackDamage = _stat->_weaponStats->_atk; // Use weapon's attack damage
    // Logic for attacking with the damage...
}

void Character::move(Vec2 direction)
{
    if (direction.isZero()) {
        return;
    }

    this->setPosition(this->getPosition() + direction * _entityStat->_spd);
}

void Character::rotateBody(float angle)
{
    float correctionAngle = -90.0f; 
    _model->setRotation(-CC_RADIANS_TO_DEGREES(angle) + correctionAngle);
}

void Character::onEnter()
{
    Node::onEnter();
}

void Character::update(float dt)
{

}

void Character::updateAmmoDisplay() {
    if (_stat && _stat->_weaponStats) {
        // Update the label text with current ammo and total ammo
        std::string ammoText = StringUtils::format("%d / %d", static_cast<int>(_stat->_weaponStats->_currentAmmo), static_cast<int>(_stat->_weaponStats->_totalAmmo));
        _ammoLabel->setString(ammoText);
    }
}