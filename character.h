#pragma once

#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"
class character : public BaseCharacter
{

public:
    character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float gethealth() const { return health; };
    void takedamage(float damage);

private:
    int windowwidth{};
    int windowheight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};