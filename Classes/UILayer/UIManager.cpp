#include "UIManager.h"

UIManager* UIManager::_instance = nullptr;

UIManager* UIManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new UIManager();
        _instance->init();
        _instance->retain();
    }
    return _instance;
}

bool UIManager::init() {
    if (!Node::init()) {
        return false;
    }

    _ammoLabel = Label::createWithTTF("Ammo: 0 / 0", "fonts/Marker Felt.ttf", 24);
    _ammoLabel->setPosition(Vec2(50, 50)); // Set the position in the bottom left corner
    this->addChild(_ammoLabel, 100);

    this->scheduleUpdate();
    return true;
}

void UIManager::setCharacterNode(Node* characterNode) {
    _characterNode = characterNode;
}

void UIManager::update(float dt) {
    if (_characterNode) {
        Vec2 characterPosition = _characterNode->getPosition();
        this->setPosition(characterPosition.x + 50, characterPosition.y + 50);
    }

    auto weaponManager = WeaponManager::getInstance();
    float currentAmmo = weaponManager->getCurrentWeaponStats()->_currentAmmo;
    float totalAmmo = weaponManager->getCurrentWeaponStats()->_totalAmmo;

    updateAmmoDisplay(currentAmmo, totalAmmo);
}

void UIManager::updateAmmoDisplay(float currentAmmo, float totalAmmo) {
    // Assuming you have a label to display the ammo
    if (_ammoLabel) { // Check if the label exists
        std::string ammoText = std::to_string(static_cast<int>(currentAmmo)) + " / " + std::to_string(static_cast<int>(totalAmmo));
        _ammoLabel->setString(ammoText); // Update the label text
    }
}