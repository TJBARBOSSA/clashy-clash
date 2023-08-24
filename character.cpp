#include "character.h"
#include "raylib.h"
#include "raymath.h"
// #include "BaseCharacter.h"

character::character(int winWidth, int winHeight) : windowwidth{winWidth},
                                                    windowheight{winHeight}
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowheight) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowwidth) / 2.0f - scale * (0.5f * height)};
}

void character::tick(float deltaTime)
{
    if (!getalive())
    {
        return;
    }

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;
    BaseCharacter::tick(deltaTime);
    float rotation{};
    Vector2 offset{};
    Vector2 origin{};
    if (rightLeft > 0.f)
    {
        origin = {0.0f,
                  weapon.height * scale};
        offset = {
            35.f,
            55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {

        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    // dRAW THE SWORD
    Rectangle source{
        0.0f,
        0.0f,
        static_cast<float>(weapon.width) * rightLeft,
        static_cast<float>(weapon.height)};

    Rectangle dest{
        getScreenPos().x + offset.x,
        getScreenPos().y + offset.y,
        weapon.width * scale,
        weapon.height * scale};

    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
    // DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}
void character::takedamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setalive(false);
    }
}