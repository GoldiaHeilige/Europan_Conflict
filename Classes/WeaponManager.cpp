#include "WeaponManager.h"
#include "Bullet.h"

WeaponManager::WeaponManager() {
    initializeWeapons();
}

void WeaponManager::initializeWeapons() {

    switch (_currentWeapon) {
    case WeaponType::PISTOL:
        _currentWeaponStats = new EntityStat();
        _currentWeaponStats->_atk = 10;
        _currentWeaponStats->_currentAmmo = 12;
        _currentWeaponStats->_currentMag = 12;
        _currentWeaponStats->_totalAmmo = 100;
        break;
    case WeaponType::ASSAULT_RIFLE:
        _currentWeaponStats = new EntityStat();
        _currentWeaponStats->_atk = 30;
        _currentWeaponStats->_currentAmmo = 30;
        _currentWeaponStats->_currentMag = 30;
        _currentWeaponStats->_totalAmmo = 360;
        break;
        // case WeaponType::ASSAULT_RIFLE:
    }
}

void WeaponManager::setCurrentWeapon(WeaponType weaponType) {
    _currentWeapon = weaponType;
    initializeWeapons(); // Update weapon stats
}

EntityStat* WeaponManager::getCurrentWeaponStats() {
    return _currentWeaponStats;
}

void WeaponManager::shoot(Node* characterNode, Vec2 direction) {
    CCLOG("Current Ammo Before Shooting: %lf", _currentWeaponStats->_currentAmmo);
    if (_currentWeaponStats->_currentAmmo > 0) {
        Bullet* bullet = Bullet::create(static_cast<Entity*>(characterNode), 550.0f, "pistol1");

        if (bullet) {
            Vec2 spawnOffset = direction * 10;
            Vec2 spawnPosition = characterNode->getPosition() + spawnOffset;
            float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));

            bullet->setPosition(spawnPosition);
            bullet->fire(direction);
            bullet->setName("Hero Bullet");
            bullet->setRotation(-angle + 90);

            characterNode->getParent()->addChild(bullet);
            _currentWeaponStats->_currentAmmo--;  // Decrement ammo here
            UIManager::getInstance()->updateAmmoDisplay(_currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);
            CCLOG("Bullet fired! Current Ammo: %lf", _currentWeaponStats->_currentAmmo);
        }
        else {
            CCLOG("Failed to create bullet.");
        }
    }
    else {
        CCLOG("Out of ammo!");
    }
}

void WeaponManager::reload() {
    CCLOG("Attempting to reload...");
    CCLOG("Current Ammo: %f, Total Ammo: %f, Magazine Size: %f", _currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo, _currentWeaponStats->_currentMag);
    if (_currentWeaponStats->_currentAmmo < _currentWeaponStats->_currentMag && _currentWeaponStats->_totalAmmo > 0) {
        float ammoToReload = std::min(_currentWeaponStats->_currentMag - _currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);

        _currentWeaponStats->_totalAmmo -= ammoToReload;
        _currentWeaponStats->_currentAmmo += ammoToReload;

        CCLOG("Reloading... Current Ammo: %lf, Total Ammo: %lf", _currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);
        UIManager::getInstance()->updateAmmoDisplay(_currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);
    }
    else {
        CCLOG("Cannot reload: Either the magazine is full or no ammo left.");
    }
}

//void WeaponManager::reload() {
//    CCLOG("Attempting to reload...");
//    CCLOG("Current Ammo: %f, Total Ammo: %f, Magazine Size: %f", _currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo, _currentWeaponStats->_currentMag);
//
//    if (_currentWeaponStats->_currentAmmo < _currentWeaponStats->_currentMag &&
//        _currentWeaponStats->_totalAmmo > 0) {
//
//        CCLOG("Ammo reload allowed.");
//        float ammoToReload = std::min(_currentWeaponStats->_currentMag - _currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);
//
//        _currentWeaponStats->_totalAmmo -= ammoToReload;
//        _currentWeaponStats->_currentAmmo += ammoToReload;
//
//        CCLOG("Reload successful! Current Ammo: %f, Total Ammo: %f", _currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);
//
//        UIManager::getInstance()->updateAmmoDisplay(_currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);
//    }
//    else {
//        CCLOG("Cannot reload: Either the magazine is full or no ammo left.");
//    }
//}

//void WeaponManager::reload() {
//    if (_currentWeaponStats->_currentAmmo < _currentWeaponStats->_currentMag && _currentWeaponStats->_totalAmmo > 0) {
//        auto reloadDuration = 2.0f;
//
//        float ammoToReload = std::min(_currentWeaponStats->_currentMag - _currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);
//
//        _currentWeaponStats->_totalAmmo -= ammoToReload;
//        _currentWeaponStats->_currentAmmo += ammoToReload;
//
//        CCLOG("Reloading... Current Ammo: %f, Total Ammo: %f", _currentWeaponStats->_currentAmmo, _currentWeaponStats->_totalAmmo);
//    }
//    else {
//        CCLOG("Cannot reload: Either the magazine is full or no ammo left.");
//    }
//}

WeaponManager* WeaponManager::_instance = nullptr; // Initialize static instance

WeaponManager* WeaponManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new WeaponManager(); // Create a new instance if it doesn't exist
    }
    return _instance;
}

//int WeaponTypeToInt(WeaponManager::WeaponType type) {
//    return static_cast<int>(type); // Convert to int
//}

//WeaponManager::WeaponType IntToWeaponType(int type) {
//    return static_cast<WeaponManager::WeaponType>(type); // Convert back to enum
//}

WeaponManager::WeaponType WeaponManager::getCurrentWeapon() {
    return _currentWeapon;
}