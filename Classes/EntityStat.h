#ifndef __ENTITY_STAT_H__
#define __ENTITY_STAT_H__

// Forward declaration of WeaponManager
class WeaponManager;

class EntityStat
{
public:
    // Weapon Stat
    float _atk;  // Weapon Damage
    float _acc;  // Weapon Accuracy (add later)
    float _rof;  // Weapon Rate of Fire (add later)

    // Ammo
    float _currentAmmo;  // Current weapon ammo
    float _currentMag;   // Total ammo of the mag 
    float _totalAmmo;    // Total ammo of current weapon
    std::string _shootSFX;

    // Use an int to represent the current weapon type
    int _currentWeapon; // Instead of WeaponManager::WeaponType
    EntityStat* _weaponStats; // Pointer to the weapon stats

    EntityStat()
        : _hp(0), _armor(0), _spd(0), _atk(0),
        _currentAmmo(0), _currentMag(0), _totalAmmo(0),
        _currentWeapon(0), _weaponStats(nullptr) {}

    ~EntityStat() { delete _weaponStats; }

    // Character stats
    float _hp;  // Health Point of an Entity
    float _armor;  // Armor point of an Entity
    float _spd; // Speed of an Entity
};

#endif // __ENTITY_STAT_H__
