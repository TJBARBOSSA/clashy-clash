#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>

class BaseCharacter
{

public:
    BaseCharacter();
    Vector2 getworldPos() { return worldPos; }
    void undoMovement();
    Rectangle GetCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getalive() { return alive; };
    void setalive(bool isAlive) { alive = isAlive; };

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float rightLeft{1.f};
    Vector2 worldPos{};
    float speed{10.f};
    float width{};
    float height{};
    Vector2 worldPosLastFrame{};
    float scale{4.0f};
    Vector2 velocity{};

private:
    bool alive{true};
};
