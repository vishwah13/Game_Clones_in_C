#include "raylib.h"
#include <string.h>

typedef struct CrossHair {
    Vector2 pos;
    Texture2D crossHairTex;
}CrossHair;

typedef struct Enemy {
    //Vector2 pos;
    Texture2D enemyTexture;
    Rectangle rect;
}Enemy;

Texture2D enemyTexture = { NULL };
Texture2D animalTextures[10] = { NULL };

Enemy CreateAnEnemy();

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "TargetPractice");
    SetTargetFPS(60);
    HideCursor();
    CrossHair cross = { 0 };
    //Enemy enemy = { 0 };
    cross.crossHairTex = LoadTexture("Resources/crosshair061.png");
    enemyTexture = LoadTexture("Resources/snake.png");
    //Rectangle rect[10];

   /* for (int i = 0; i < 10; i++)
    {
        Rectangle tempRect = { GetRandomValue(100, 700),GetRandomValue(100, 350), enemy.enemyTexture.width , enemy.enemyTexture.height };
        rect[i] = tempRect;
    }
    enemy.rect = rect[1];*/

    Enemy enemy[10];

    for (int i = 0; i < 7; i++)
    {
        enemy[i] = CreateAnEnemy();
    }
    
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLUE);
        cross.crossHairTex.width = 40;
        cross.crossHairTex.height = 40;
        
        
        for (int i = 0; i < 7; i++)
        {
            DrawTexture(enemy[i].enemyTexture, enemy[i].rect.x, enemy[i].rect.y, WHITE);
        }

        for (int i = 0; i < 7; i++)
        {
            bool cursoreOnTexture = CheckCollisionPointRec(GetMousePosition(), enemy[i].rect);

            if (cursoreOnTexture)
                return 0;
        }
       
        DrawTexture(cross.crossHairTex, GetMousePosition().x, GetMousePosition().y, WHITE);

       

        EndDrawing();
       
    }
    CloseWindow();

    return 0;
}

Enemy CreateAnEnemy() {
    Enemy enemy;
    enemy.enemyTexture = enemyTexture;
    enemy.rect.x  = GetRandomValue(50,700);
    enemy.rect.y  = GetRandomValue(50,400);

    enemy.enemyTexture.width = 40;
    enemy.enemyTexture.height = 40;

    return enemy;
}