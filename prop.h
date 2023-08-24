#include "raylib.h"

class prop
{

public:
    prop(Vector2 pos, Texture2D tex);
    void render(Vector2 knightpos);
    Rectangle GetCollisionRec(Vector2 knightpos);

private:
    Texture2D texture{};
    Vector2 worldpos{};
    float scale{4.f};
};