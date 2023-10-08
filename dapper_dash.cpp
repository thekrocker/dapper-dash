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
    
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    const int gravity = 1'000; // Acceleration dude to gravity (pixels/frame)/ frame
    int velocity{};
    int jumpPower{550};
    bool isGrounded{false};

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dash");
    SetTargetFPS(60);

    // Character properties
    const int spriteCount = 6;
    Texture2D characterTexture = LoadTexture("textures/scarfy.png");

    AnimData chAnimData{
        {0,0,characterTexture.width / spriteCount, characterTexture.height}, // rect
        {windowWidth / 2 - chAnimData.rect.width / 2, windowHeight - chAnimData.rect.height}, // vector
           0,
           0.0,
           1.0/12.0
           };


    // Nebula Properties
    const int spriteCountPerCell = 8;
    Texture2D nebulaTexture = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData nebulaAnimData{{0.0, 0.0, nebulaTexture.width / spriteCountPerCell, nebulaTexture.height / spriteCountPerCell}, 
    {windowWidth, windowHeight - nebulaAnimData.rect.height},
    0,
    0.0,
    1.0/12.0
    };

    float nebulaVelocity {-50.0};

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
        nebulaAnimData.pos.x += nebulaVelocity * GetFrameTime();

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
        nebulaAnimData.elapsedTime += GetFrameTime();
        if (nebulaAnimData.elapsedTime >= nebulaAnimData.totalTime)
        {
            nebulaAnimData.elapsedTime = 0;
            nebulaAnimData.rect.x = nebulaAnimData.frame * nebulaAnimData.rect.width;
            nebulaAnimData.frame++;
            if (nebulaAnimData.frame >= spriteCountPerCell)
            {
                nebulaAnimData.frame = 0;
            }
        }

        DrawTextureRec(nebulaTexture, nebulaAnimData.rect, nebulaAnimData.pos, WHITE);

        EndDrawing();
    }

    UnloadTexture(characterTexture);
    UnloadTexture(nebulaTexture);
    CloseWindow();
}