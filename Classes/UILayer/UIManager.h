#ifndef __UIManager_H__
#define __UIManager_H__

#include "cocos2d.h"
#include "WeaponManager.h"

USING_NS_CC;

class UIManager : public Node {
public:
    static UIManager* getInstance();

    virtual bool init() override;
    void updateAmmoDisplay(float currentAmmo, float totalAmmo);
    void setCharacterNode(Node* characterNode);

private:
    static UIManager* _instance;
    Node* _characterNode;
    Label* _ammoLabel;

    void update(float dt) override; // Schedule to update UI
};

#endif // __UIManager_H__
