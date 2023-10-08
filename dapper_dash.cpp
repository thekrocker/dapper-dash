#include "raylib.h"

struct AnimData
{
    Rectangle rect;
    Vector2 pos;
    int frame;
    float elapsedTime;
    float totalTime;
};

int main()
{
    // Newton's second law: Force = Mass * Acceleration
    const int windowWidth = 512;
    const int windowHeight = 380;

    const int gravity = 1'000; // Acceleration dude to gravity (pixels/frame)/ frame
    int velocity{};
    int jumpPower{550};
    bool isGrounded{false};

    InitWindow(windowWidth, windowHeight, "Dapper Dash");
    SetTargetFPS(60);

    // Character properties
    const int spriteCount = 6;
    Texture2D characterTexture = LoadTexture("textures/scarfy.png");

    AnimData chAnimData{
        {0,0,characterTexture.width / spriteCount, characterTexture.height},
           {windowWidth / 2 - chAnimData.rect.width / 2,
            windowHeight - chAnimData.rect.height},
           0,
           0.0,
           1.0/12.0
           };


    // Nebula Properties
    const int spriteCountPerCell = 8;
    Texture2D nebulaTexture = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRect{0.0, 0.0, nebulaTexture.width / spriteCountPerCell, nebulaTexture.height / spriteCountPerCell};
    Vector2 nebulaPosition{windowWidth, windowHeight - nebulaRect.height};
    int nebulaVelocity{-50};
    float elapsedNebulaAnimTime{0};
    float totalNebulaAnimTime{1.0 / 12.0};
    int nebulaSpriteFrame{0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // JUMP MECHANICS
        isGrounded = chAnimData.pos.y >= (windowHeight - chAnimData.rect.height);

        if (isGrounded)
        {
            velocity = 0;
        }
        else
        {
            // Rectangle is in the air.. Apply gravity
            velocity += gravity * GetFrameTime();
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            if (isGrounded)
                velocity -= jumpPower;
        }

        chAnimData.pos.y += velocity * GetFrameTime();
        nebulaPosition.x += nebulaVelocity * GetFrameTime();

        // Draw Texture and set animation
        DrawTextureRec(characterTexture, chAnimData.rect, chAnimData.pos, WHITE);

        // Set player animation only if we are grounded
        if (isGrounded)
        {
            chAnimData.elapsedTime += GetFrameTime();
            if (chAnimData.elapsedTime >= chAnimData.totalTime)
            {
                chAnimData.elapsedTime = 0;
                chAnimData.frame++;
                chAnimData.rect.x = chAnimData.frame * chAnimData.rect.width;

                if (chAnimData.frame >= spriteCount)
                {
                    chAnimData.frame = 0;
                }
            }
        }

        // Update nebula animation intervally.
        elapsedNebulaAnimTime += GetFrameTime();
        if (elapsedNebulaAnimTime >= totalNebulaAnimTime)
        {
            elapsedNebulaAnimTime = 0;
            nebulaRect.x = nebulaSpriteFrame * nebulaRect.width;
            nebulaSpriteFrame++;
            if (nebulaSpriteFrame >= spriteCountPerCell)
            {
                nebulaSpriteFrame = 0;
            }
        }

        DrawTextureRec(nebulaTexture, nebulaRect, nebulaPosition, WHITE);

        EndDrawing();
    }

    UnloadTexture(characterTexture);
    UnloadTexture(nebulaTexture);
    CloseWindow();
}