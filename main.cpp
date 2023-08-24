#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <cstdint>
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include<string.h>

using namespace std;

int main()
{
    const float mapScale{4.0f};
    const int windowWidth{384};
    const int windowHieght{384};
    InitWindow(windowWidth, windowHieght, "TjBarbossa's Clashy Clash");
    InitAudioDevice();

    Music music = LoadMusicStream("ost/ost.mp3");
    SetMusicVolume(music, 0.4f);
    character knight{windowWidth, windowHieght};
    PlayMusicStream(music);
    enemy slime{
        Vector2{1500.f, 1700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    enemy goblin{Vector2{2000,1500}, Texture2D{LoadTexture("characters/goblin_idle_spritesheet.png")}, Texture2D{LoadTexture("characters/goblin_run_spritesheet.png")}};
    enemy* enemies[2]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies)
    {
        enemy->setPointer(&knight);
    }

    
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    prop props[2]{
        prop{Vector2{600.0f, 300.f}, Texture2D{LoadTexture("nature_tileset/Rock.png")}},
        prop{Vector2{400.0f, 500.f}, Texture2D{LoadTexture("nature_tileset/Log.png")}}};
        
    goblin.setPointer(&knight);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        
        BeginDrawing();
        ClearBackground(WHITE);
        mapPos = Vector2Scale(knight.getworldPos(), -1);
        // draw map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // draw the props

        for (auto prop : props)
        {
            prop.render(knight.getworldPos());
        }

        if (!knight.getalive()) // Character is not alive
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.gethealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());

        if (knight.getworldPos().x < 0.f ||
            knight.getworldPos().y < 0.f ||
            knight.getworldPos().x + windowWidth > map.width * mapScale ||
            knight.getworldPos().y + windowHieght > map.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(knight.getworldPos()), knight.GetCollisionRec()))
            {
                knight.undoMovement();
            }
        }


        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {

            if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setalive(false);
                }

        }
        }
        EndDrawing();
    }
    StopMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}