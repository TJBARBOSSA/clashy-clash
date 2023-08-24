#pragma once

#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"
#include "character.h"
class enemy : public BaseCharacter
{

public:
    enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    void setPointer(character *ptr) { target = ptr; };
    virtual Vector2 getScreenPos() override;

private:
    character *target{};
    float damagepersec{10.f};
    float radius{25.f};
};