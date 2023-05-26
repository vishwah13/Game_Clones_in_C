#include "raylib.h"

typedef struct CrossHair {
    Vector2 pos;
    Texture2D crossHairTex;
}CrossHair;

typedef struct Enemy {
    //Vector2 pos;
    Texture2D enemyTexture;
    Rectangle rect;
    bool isActive;
}Enemy;

typedef struct Animal
{
    Texture2D animalTexture[10];
    Rectangle rect[10];
    bool isActive[10];
}Animal;

typedef struct Timer {
    float lifeTime;
}Timer;

Texture2D enemyTexture = { NULL };
Texture2D animalTextures[10] = { NULL };
void StartTimer(Timer* timer, float lifeTime);
void UpdateTimer(Timer* timer);
bool IsTimesUp(Timer* timer);
Enemy CreateAnEnemy();
Animal CreateAnAnimals();

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    int score = 0;
    bool cursoreOnEnemyTexture = false;
    bool cursoreOnAnimalTexture = false;
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


    Enemy enemy;
    Animal animals = CreateAnAnimals();


    Timer enemySpawnTime = { 0 };
    StartTimer(&enemySpawnTime, 4.0f);
    enemy = CreateAnEnemy();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLUE);
        cross.crossHairTex.width = 40;
        cross.crossHairTex.height = 40;
        
        //StartTimer(&enemySpawnTime, 2.0f);
        UpdateTimer(&enemySpawnTime);

        if (!IsTimesUp(&enemySpawnTime)) {
           
            DrawTexture(enemy.enemyTexture, enemy.rect.x, enemy.rect.y, WHITE);
            cursoreOnEnemyTexture = CheckCollisionPointRec(GetMousePosition(), enemy.rect);
            if (cursoreOnEnemyTexture) {
                score++;
                enemy.isActive = false;
                //enemy[i].rect = {0,0,0,0};
            }
            //StartTimer(&enemySpawnTime, 2.0f);
        }
        
        for (int i = 0; i < 10; i++)
        {
            /*if(enemy[i].isActive)
                DrawTexture(enemy[i].enemyTexture, enemy[i].rect.x, enemy[i].rect.y, WHITE);*/
           
           if(animals.isActive[i])
               DrawTexture(animals.animalTexture[i], animals.rect[i].x, animals.rect[i].y, WHITE);
        }

        DrawTexture(cross.crossHairTex, GetMousePosition().x, GetMousePosition().y, WHITE);
        DrawText(TextFormat("Score: %d ",score), 5, 5, 20, WHITE);

        EndDrawing();
       
    }
    CloseWindow();

    return 0;
}

void StartTimer(Timer* timer, float lifeTime)
{
    if (timer != NULL) {
        timer->lifeTime = lifeTime;
    }
}

void UpdateTimer(Timer* timer)
{
    if (timer != NULL) {
        timer->lifeTime -= GetFrameTime();
    }
}

bool IsTimesUp(Timer* timer)
{
    if(timer != NULL)
        return timer->lifeTime <= 0;

    return false;
   
}

Enemy CreateAnEnemy() {
    Enemy enemy;
    enemy.enemyTexture = enemyTexture;
    enemy.rect.x  = GetRandomValue(50,700);
    enemy.rect.y  = GetRandomValue(50,400);
    enemy.isActive = true;

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
        animals.isActive[i] = true;
    }

    return animals;
   
}