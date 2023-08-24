#include "raylib.h"
#include "raymath.h"
#include "enemy.h"
#include "character.h"
// #include "BaseCharacter.h"

enemy::enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 7.f;
}

void enemy::tick(float deltaTime)
{
    if (!getalive())
    {
        return;
    }

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);
    if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec())){

        target -> takedamage(damagepersec *  deltaTime);

    }
}

Vector2 enemy::getScreenPos()
{
    return Vector2Subtract(enemy::worldPos, target->getworldPos());
}
