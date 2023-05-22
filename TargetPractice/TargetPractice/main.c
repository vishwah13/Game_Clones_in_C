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

typedef struct Animal
{
    Texture2D animalTexture[10];
    Rectangle rect[10];
}Animal;

Texture2D enemyTexture = { NULL };
Texture2D animalTextures[10] = { NULL };

Enemy CreateAnEnemy();
Animal CreateAnAnimals();

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "TargetPractice");
    SetTargetFPS(60);
    HideCursor();
    CrossHair cross = { 0 };
    
    cross.crossHairTex = LoadTexture("Resources/crosshair061.png");
    enemyTexture = LoadTexture("Resources/snake.png");
    animalTextures[1] = LoadTexture("Resources/bear.png");
    animalTextures[2] = LoadTexture("Resources/buffalo.png");
    animalTextures[3] = LoadTexture("Resources/chick.png");
    animalTextures[4] = LoadTexture("Resources/chicken.png");
    animalTextures[5] = LoadTexture("Resources/cow.png");
    animalTextures[6] = LoadTexture("Resources/crocodile.png");
    animalTextures[7] = LoadTexture("Resources/dog.png");
    animalTextures[8] = LoadTexture("Resources/duck.png");
    animalTextures[9] = LoadTexture("Resources/elephant.png");


    Enemy enemy[10];
    Animal animals = CreateAnAnimals();

    for (int i = 0; i < 10; i++)
    {
        enemy[i] = CreateAnEnemy();
    }
    
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLUE);
        cross.crossHairTex.width = 40;
        cross.crossHairTex.height = 40;
        
        
        for (int i = 0; i < 10; i++)
        {
            DrawTexture(enemy[i].enemyTexture, enemy[i].rect.x, enemy[i].rect.y, WHITE);
            DrawTexture(animals.animalTexture[i], animals.rect[i].x, animals.rect[i].y,WHITE);
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

Animal CreateAnAnimals() {
    Animal animals;
    for (int i = 0; i < 10; i++)
    {
        animals.animalTexture[i] = animalTextures[i];
        animals.animalTexture[i].width = 40;
        animals.animalTexture[i].height = 40;
        animals.rect[i].x = GetRandomValue(0, 700);
        animals.rect[i].y = GetRandomValue(0, 400);
    }

    return animals;
   
}