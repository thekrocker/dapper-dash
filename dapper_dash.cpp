#include "raylib.h"

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
    Rectangle characterRect;
    characterRect.width = characterTexture.width / spriteCount; // Since we have 6 sprites in texture
    characterRect.height = characterTexture.height;
    characterRect.x = 0;
    characterRect.y = 0;
    Vector2 characterPos;
    characterPos.x = windowWidth / 2 - characterRect.width / 2;
    characterPos.y = windowHeight - characterRect.height;
    int currentSpriteFrame{};
    float elapsed{};
    float total{1.0 / 12.0};

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
        isGrounded = characterPos.y >= (windowHeight - characterRect.height);

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

        characterPos.y += velocity * GetFrameTime();
        nebulaPosition.x += nebulaVelocity * GetFrameTime();

        // Draw Texture and set animation
        DrawTextureRec(characterTexture, characterRect, characterPos, WHITE);

        // Set player animation only if we are grounded
        if (isGrounded)
        {
            elapsed += GetFrameTime();
            if (elapsed >= total)
            {
                elapsed = 0;
                currentSpriteFrame++;
                characterRect.x = currentSpriteFrame * characterRect.width;

                if (currentSpriteFrame >= spriteCount)
                {
                    currentSpriteFrame = 0;
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