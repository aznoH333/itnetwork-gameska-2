/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//------------------------------------------------------------------------------------
// VARIABLE INITIALIZATION
//------------------------------------------------------------------------------------
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const float CAMERA_ZOOM = 3.0f;

const int IN_GAME_WIDTH = SCREEN_WIDTH / CAMERA_ZOOM;
const int IN_GAME_HEIGHT = SCREEN_HEIGHT / CAMERA_ZOOM;
Camera2D cam;
#define MAX_OBJECTS 40
#define NULLPTR 0
int gameTimer = 0;

const int TAG_NONE = 0;
const int TAG_PLAYER = 1;
const int TAG_PLAYER_ATTACK = 2;
const int TAG_ENEMY = 3;
const int TAG_ENEMY_ATTACK = 4;
const int TAG_INTERACTABLE = 5;


#define PROJECTILE_SWORD 0
#define PROJECTILE_ARROW 1
#define PROJECTILE_MAGIC 2
#define PROJECTILE_SWORD_2 3
#define PROJECTILE_SPEAR 4

#define FLOOR_WIDTH 27
#define FLOOR_HEIGHT 15

#define ITEM_EMPTY -1
#define ITEM_SWORD 0
#define ITEM_BOW 1
#define ITEM_WAND 2
#define ITEM_ARROW 3
#define ITEM_POTION 4
#define ITEM_GOLD 5
#define ITEM_MANA_POTION 6
#define ITEM_WAND_2 7
#define ITEM_BOW_2 8
#define ITEM_BOW_3 9
#define ITEM_SWORD_2 10
#define ITEM_SPEAR 11
#define ITEM_COUNT 12

#define ENEMY_RETARD 0
#define ENEMY_TROLL 1
#define ENEMY_SKELETON 2

int playerHp = 100;
int playerMana = 100;
int arrowCount = 5;
int playerMoney = 0;
int selectedSlot = 0;
int inventory[3];
bool playerHasTarget = false;
int exitX = 0;
int exitY = 0;
int enemiesInRoom = 0;
int screenTransitionTimer = 60;
int score = 0;



//------------------------------------------------------------------------------------
// LOADING & DISPOSING
//------------------------------------------------------------------------------------

RenderTexture2D renderTexture;
Texture2D playerIdle;
Texture2D playerWalk1;
Texture2D playerWalk2;
Texture2D playerUse;
Texture2D targetUi;
Texture2D trollIdle;
Texture2D trollWalk1;
Texture2D trollWalk2;
Texture2D trollUse;
Texture2D swordSprite;
Texture2D arrowSprite;
Texture2D magicSprite;
Texture2D floorSprite;
Texture2D wallSprite;
Texture2D bowSprite;
Texture2D wandSprite;
Texture2D potionSprite;
Texture2D manaPotionSprite;
Texture2D coinSprite;
Texture2D uiSelected;
Texture2D uiUnselected;
Texture2D uiHp;
Texture2D uiMana;
Texture2D exitTexture;
Texture2D closedExitTexture;
Texture2D shopKeeper;
Texture2D blackSprite;
Texture2D wand2Sprite;
Texture2D spearSprite;
Texture2D bow2Sprite;
Texture2D bow3Sprite;
Texture2D sword2Sprite;
Texture2D retardIdle;
Texture2D retardWalk1;
Texture2D retardWalk2;
Texture2D retardUse;
Texture2D skeletonIdle;
Texture2D skeletonWalk1;
Texture2D skeletonWalk2;
Texture2D skeletonUse;

void loadTextures(){

    renderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    // textures
    playerIdle = LoadTexture("sprites/player_0001.png");
    playerWalk1 = LoadTexture("sprites/player_0003.png");
    playerWalk2 = LoadTexture("sprites/player_0004.png");
    playerUse = LoadTexture("sprites/player_0002.png");
    targetUi = LoadTexture("sprites/target.png");
    trollIdle = LoadTexture("sprites/troll_0001.png");
    trollWalk1 = LoadTexture("sprites/troll_0003.png");
    trollWalk2 = LoadTexture("sprites/troll_0004.png");
    trollUse = LoadTexture("sprites/troll_0002.png");
    swordSprite = LoadTexture("sprites/projectiles_0001.png");
    arrowSprite = LoadTexture("sprites/projectiles_0002.png");
    magicSprite = LoadTexture("sprites/projectiles_0003.png");
    wallSprite = LoadTexture("sprites/wall.png");
    floorSprite = LoadTexture("sprites/floor.png");
    bowSprite = LoadTexture("sprites/projectiles_0004.png");
    wandSprite = LoadTexture("sprites/projectiles_0005.png");
    potionSprite = LoadTexture("sprites/projectiles_0006.png");
    manaPotionSprite = LoadTexture("sprites/projectiles_0007.png");
    coinSprite = LoadTexture("sprites/projectiles_0008.png");
    uiSelected = LoadTexture("sprites/ui_0001.png");
    uiUnselected = LoadTexture("sprites/ui_0002.png");
    uiHp = LoadTexture("sprites/icons_0001.png");
    uiMana = LoadTexture("sprites/icons_0002.png");
    exitTexture = LoadTexture("sprites/exit.png");
    closedExitTexture = LoadTexture("sprites/exit_closed.png");
    shopKeeper = LoadTexture("sprites/shopKeeper.png");
    blackSprite = LoadTexture("sprites/black.png");
    wand2Sprite = LoadTexture("sprites/weapons_0001.png");
    spearSprite = LoadTexture("sprites/weapons_0002.png");
    bow2Sprite = LoadTexture("sprites/weapons_0003.png");
    bow3Sprite = LoadTexture("sprites/weapons_0004.png");
    sword2Sprite = LoadTexture("sprites/weapons_0005.png");
    retardIdle = LoadTexture("sprites/enemies_0001.png");
    retardUse = LoadTexture("sprites/enemies_0002.png");
    retardWalk1 = LoadTexture("sprites/enemies_0003.png");
    retardWalk2 = LoadTexture("sprites/enemies_0004.png");
    skeletonIdle = LoadTexture("sprites/enemies_0005.png");
    skeletonUse = LoadTexture("sprites/enemies_0006.png");
    skeletonWalk1 = LoadTexture("sprites/enemies_0007.png");
    skeletonWalk2 = LoadTexture("sprites/enemies_0008.png");
}

void unloadTextures(){
    UnloadRenderTexture(renderTexture);

    // textures
    UnloadTexture(playerIdle);
    UnloadTexture(playerWalk1);
    UnloadTexture(playerWalk2);
    UnloadTexture(playerUse);
    UnloadTexture(targetUi);
    UnloadTexture(trollIdle);
    UnloadTexture(trollWalk1);
    UnloadTexture(trollWalk2);
    UnloadTexture(trollUse);
    UnloadTexture(swordSprite);
    UnloadTexture(arrowSprite);
    UnloadTexture(magicSprite);
    UnloadTexture(wallSprite);
    UnloadTexture(floorSprite);
    UnloadTexture(bowSprite);
    UnloadTexture(wallSprite);
    UnloadTexture(potionSprite);
    UnloadTexture(manaPotionSprite);
    UnloadTexture(coinSprite);
    UnloadTexture(uiSelected);
    UnloadTexture(uiUnselected);
    UnloadTexture(uiHp);
    UnloadTexture(uiMana);
    UnloadTexture(exitTexture);
    UnloadTexture(closedExitTexture);
    UnloadTexture(shopKeeper);
    UnloadTexture(blackSprite);
    UnloadTexture(wand2Sprite);
    UnloadTexture(bow2Sprite);
    UnloadTexture(spearSprite);
    UnloadTexture(bow3Sprite);
    UnloadTexture(sword2Sprite);
    UnloadTexture(retardIdle);
    UnloadTexture(retardUse);
    UnloadTexture(retardWalk1);
    UnloadTexture(retardWalk2);
    UnloadTexture(skeletonIdle);
    UnloadTexture(skeletonUse);
    UnloadTexture(skeletonWalk1);
    UnloadTexture(skeletonWalk2);
}

//------------------------------------------------------------------------------------
// UTILITY
//------------------------------------------------------------------------------------
bool checkBoxCollisions(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
    return x1 + w1 > x2 &&
           x1 < x2 + w2 &&
           y1 + h1 > y2 &&
           y1 < y2 + h2;
}

float lerp(float a, float b, float w){
    return a * (1.0 - w) + (b * w);
}

float pythagoras(float x1, float y1, float x2, float y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

float dirTowards(int x1, int y1, int x2, int y2){
    return atan2(x1 - x2, y1 - y2);
}
void DrawTextureRotated(Texture2D texture, int x, int y, float rotation, Color tint){
    Vector2 origin = {texture.width >> 1, texture.width >> 1};

    Rectangle r1 = {0,0, texture.width, texture.height};
    Rectangle r2 = {x + origin.x, y + origin.y, texture.width, texture.height};
    DrawTexturePro(texture, r1, r2, origin, rotation, tint);
}

int min(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

//------------------------------------------------------------------------------------
// OBJECTS
//------------------------------------------------------------------------------------
struct Object{
    float x;
    float y;
    int w;
    int h;
    bool exists;
    void (*update)(struct Object*);
    void (*collide)(struct Object*, struct Object*);
    float rotation;
    int tag;
    float moveSpeed;
    int useCooldown;
    int internalType;
    int internalTimer;
    int health;
    bool internalBool1;
    int internalValue1;
    int internalValue2;
    int damage;
    int retardTimer;
};
typedef struct Object Object;

Object initDefaultObject(){
    Object output = {
        .x=0,
        .y=0,
        .w=0,
        .h=0,
        .exists=true,.update=NULLPTR,
        .collide=NULLPTR,
        .rotation = 0,
        .tag = TAG_NONE,
        .moveSpeed = 0,
        .useCooldown = 0,
        .internalTimer = 0,
        .internalType = 0,
        .health = 0,
        .internalBool1 = false,
        .internalValue1 = 0,
        .internalValue2 = 0,
        .damage = 0,
        .retardTimer = 0,
    };
    return output;
}

Object objects[MAX_OBJECTS];
void updateObjects(){
    for (int i = 0; i < MAX_OBJECTS; i++){
        Object* obj = &objects[i];

        if (obj->exists){

            if (obj->update != NULLPTR){
                obj->update(obj);
            }

            if (obj->collide != NULLPTR){
                for (int j = 0; j < MAX_OBJECTS; j++){
                    Object* obj2 = &objects[j];

                    if (obj != obj2 && obj2->exists && checkBoxCollisions(obj->x, obj->y, obj->w, obj->h, obj2->x, obj2->y, obj2->w, obj2->h)){

                        obj->collide(obj, obj2);

                    }
                }
            }
        }
    }
}

int nextObjectIndex = 0;
void addObject(Object object){
    while (objects[nextObjectIndex].exists){
        nextObjectIndex++;
        nextObjectIndex%= MAX_OBJECTS;
    }
    objects[nextObjectIndex] = object;
}

Object* getClosestObject(Object* caster, int objectTag){

    Object* output = NULLPTR;
    float dist = 999999999.0f;
    for (int i = 0; i < MAX_OBJECTS; i++){
        Object* obj = &objects[i];

        if (obj != caster && obj->exists && obj->tag == objectTag){
            float temp = pythagoras(caster->x, caster->y, obj->x, obj->y);

            if (temp < dist){
                dist = temp;
                output = obj;
            }

        }
    }

    return output;
}

void clearObjects(){
    for (int i = 0; i < MAX_OBJECTS; i++){
        objects[i].exists = false;
    }
}


//------------------------------------------------------------------------------------
// PREDECLARATIONS
//------------------------------------------------------------------------------------
void initProjectile(int x, int y, float direction, int tag, int type, int damage, float speed);
bool canMoveTo(int x, int y);
int useItem();
void equipItem(int);
void generateFloor();
void initShop(int x, int y);
void updateShopItem(Object*);
void activateTransition(void (*)());
//------------------------------------------------------------------------------------
// PLAYER
//------------------------------------------------------------------------------------
Object* playerRef = NULLPTR;
bool playerMovementUpdate(Object* this){
    // movement
    bool isMoving = false;
    if (IsKeyDown(KEY_A) && canMoveTo(this->x - 1, this->y)){
        this->x -= 1;
        isMoving = true;
    }else if (IsKeyDown(KEY_D) && canMoveTo(this->x + 1, this->y)){
        this->x += 1;
        isMoving = true;
    }

    if (IsKeyDown(KEY_W) && canMoveTo(this->x, this->y - 1)){
        this->y -= 1;
        isMoving = true;
    }else if (IsKeyDown(KEY_S) && canMoveTo(this->x, this->y + 1)){
        this->y += 1;
        isMoving = true;
    }

    // mana
    if (playerMana < 100 && gameTimer % 10 == 0){
        playerMana++;
    }

    // targeting
    Object* target = getClosestObject(this, TAG_ENEMY);
    playerHasTarget = target != NULLPTR;
    if (playerHasTarget){
        this->rotation = dirTowards(this->x, this->y, target->x, target->y);
    }


    // attacking
    if (this->useCooldown == 0 && IsKeyDown(KEY_SPACE)){
        this->useCooldown = useItem();
        this->internalValue1 = 10;
    }


    // interacting
    Object* interactable = getClosestObject(this, TAG_INTERACTABLE);
    if (interactable != NULLPTR && pythagoras(this->x, this->y, interactable->x, interactable->y) < 10){
        if (IsKeyPressed(KEY_E)){
            if (interactable->update == &updateShopItem){
                if (playerMoney > interactable->internalValue1){
                    interactable->exists = false;
                    equipItem(interactable->internalType);
                    playerMoney -= interactable->internalValue1;
                }
            }else {
                equipItem(interactable->internalType);
                interactable->exists = false;
            }


        }
    }else if (pythagoras(this->x, this->y, exitX, exitY) < 10 && enemiesInRoom == 0){
        if (IsKeyPressed(KEY_E)){
            activateTransition(&generateFloor);
        }
    }
    return isMoving;
}
void updatePlayer(Object* this){
    playerRef = this;
    if (playerHp == 0){
        return;
    }
    bool isMoving = false;
    if (screenTransitionTimer == 0){
        isMoving = playerMovementUpdate(this);
    }


    this->useCooldown -= this->useCooldown > 0;
    this->internalValue1 -= this->internalValue1 > 0;
    this->internalValue2 -= this->internalValue2 > 0;



    // drawing
    Texture2D* spr = &playerIdle;
    Color c = WHITE;
    c.r = (unsigned char)lerp(WHITE.r, RED.r, this->internalValue2 / 20.0f);
    c.g = (unsigned char)lerp(WHITE.g, RED.g, this->internalValue2 / 20.0f);
    c.b = (unsigned char)lerp(WHITE.b, RED.b, this->internalValue2 / 20.0f);

    if (this->internalValue1 > 0){
        spr = &playerUse;
    }else if (isMoving){
        if (gameTimer % 20 > 10){
            spr = &playerWalk1;
        }else {
            spr = &playerWalk2;
        }
    }

    DrawTexture(*spr, this->x, this->y, c);

    if (playerHasTarget){
        DrawTexture(targetUi, this->x + (-sin(this->rotation) * 14.0f), this->y + (-cos(this->rotation) * 14.0f), WHITE);
    }
}


void initPlayer(int x, int y){
    Object player = initDefaultObject();

    player.x = x;
    player.y = y;
    player.w = 16;
    player.h = 16;
    player.tag = TAG_PLAYER;
    player.update = &updatePlayer;

    addObject(player);

}

//------------------------------------------------------------------------------------
// ENEMY
//------------------------------------------------------------------------------------
bool updateEnemyMovement(Object* this){


    bool isMoving = false;
    if (this->retardTimer == 0 || this->internalValue2 != 0){
        // targeting

        Object* target = getClosestObject(this, TAG_PLAYER);
        bool hasTarget = target != NULLPTR;
        if (hasTarget){
            this->rotation = dirTowards(this->x, this->y, target->x, target->y);
            if (gameTimer % 230 == 0){
                initProjectile(this->x, this->y, this->rotation, TAG_ENEMY_ATTACK, PROJECTILE_ARROW, 20, 1.2);
            }
        }
        // moving
        isMoving = hasTarget;
        if (hasTarget && this->internalValue2 == 0){
            float targetX = this->x - sin(this->rotation) * this->moveSpeed;
            float targetY = this->y - cos(this->rotation) * this->moveSpeed;

            if (canMoveTo(targetX, targetY)){
                this->x = targetX;
                this->y = targetY;
            }else {
                this->retardTimer = 10;
                this->rotation = GetRandomValue(0, 360) * DEG2RAD;
            }
        }
        else if (this->internalValue2 > 0){
            float targetX = this->x + sin(this->rotation) * (this->internalValue2 >> 3);
            float targetY = this->y + cos(this->rotation) * (this->internalValue2 >> 3);

            if (canMoveTo(targetX, targetY)){
                this->x = targetX;
                this->y = targetY;
            }
            this->internalValue2--;

        }
    }else{
        this->retardTimer -= this->retardTimer > 0 && this->internalType != ENEMY_RETARD;
        // retardation
        this->rotation += GetRandomValue(-1, 1) * 20 * DEG2RAD;

        float targetX = this->x - sin(this->rotation) * this->moveSpeed;
        float targetY = this->y - cos(this->rotation) * this->moveSpeed;

        if (canMoveTo(targetX, targetY)){
            this->x = targetX;
            this->y = targetY;
        }
        isMoving = true;
    }





    return isMoving;

}

void updateEnemy(Object* this){
    // death
    if (this->health <= 0){
        this->exists = false;
        enemiesInRoom--;
    }

    bool isMoving = false;
    if (screenTransitionTimer == 0){
        isMoving = updateEnemyMovement(this);
    }

    // drawing
    Texture2D* spr = &trollIdle;
    Color c = WHITE;


    if (isMoving){
        if (gameTimer % 20 > 10){
            switch (this->internalType){
                case ENEMY_RETARD:
                    spr = &retardWalk1;
                    break;
                case ENEMY_TROLL:
                    spr = &trollWalk1;
                    break;
                case ENEMY_SKELETON:
                    spr = &skeletonWalk1;
                    break;
            }
        }else {
            switch (this->internalType){
                case ENEMY_RETARD:
                    spr = &retardWalk2;
                    break;
                case ENEMY_TROLL:
                    spr = &trollWalk2;
                    break;
                case ENEMY_SKELETON:
                    spr = &skeletonWalk2;
                    break;
            }
        }
    }else {
        switch (this->internalType){
                case ENEMY_RETARD:
                    spr = &retardIdle;
                    break;
                case ENEMY_TROLL:
                    spr = &trollIdle;
                    break;
                case ENEMY_SKELETON:
                    spr = &skeletonIdle;
                    break;
        }
    }


    if (this->internalValue1 > 0){
        float val = this->internalValue1 / 10.0f;
        this->internalValue1--;
        c.r = (unsigned char)lerp(WHITE.r, RED.r, val);
        c.g = (unsigned char)lerp(WHITE.g, RED.g, val);
        c.b = (unsigned char)lerp(WHITE.b, RED.b, val);


    }

    DrawTexture(*spr, this->x, this->y, c);
}

void collideEnemy(Object* this, Object* other){
    if (other->tag == TAG_ENEMY){
        float angle = dirTowards(this->x, this->y, other->x, other->y);

        float nextX = this->x + (sin(angle) * 3 * this->moveSpeed);
        float nextY = this->y + (cos(angle) * 3 * this->moveSpeed);

        if (canMoveTo(nextX, nextY)){

            this->x = nextX;
            this->y = nextY;

        }
    }else if (other->tag == TAG_PLAYER && playerHp > 0 && other->internalValue2 == 0){
        this->internalValue2 = 20;
        this->rotation = this->rotation;
        playerHp -= this->damage;
        other->internalValue2 = 20;
        if (playerHp < 0){
            playerHp = 0;
        }
    }
}

int getEnemyType(){

    if (score < 3){
        return ENEMY_RETARD;
    }else if (score < 10){
        return GetRandomValue(ENEMY_RETARD, ENEMY_TROLL);
    }
    return GetRandomValue(ENEMY_TROLL, ENEMY_SKELETON);

}

void initTroll(int x, int y){
    Object troll = initDefaultObject();
    troll.x = x;
    troll.y = y;
    troll.w = 16;
    troll.h = 16;
    troll.internalType = getEnemyType();

    troll.tag = TAG_ENEMY;
    troll.update = &updateEnemy;
    troll.collide = &collideEnemy;
    troll.moveSpeed = 0.5f;
    switch(troll.internalType){
        case ENEMY_RETARD:troll.health = 40; break;
        case ENEMY_TROLL: troll.health = 60; break;
        case ENEMY_SKELETON: troll.health = 50; break;
    }
    troll.damage = 20;
    if (troll.internalType == ENEMY_RETARD){
        troll.retardTimer = 99999999;

    }
    enemiesInRoom++;
    addObject(troll);

}
//------------------------------------------------------------------------------------
// ITEM SCHEMA
//------------------------------------------------------------------------------------
struct Item{
    Texture2D* texture;
    int (*use) (void);
};
typedef struct Item Item;

int useSword(){
    if (!playerHasTarget){
        return 10;
    }
    initProjectile(playerRef->x, playerRef->y, playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_SWORD, 10, 1);
    return 30;
}

int useBow(){
    if (arrowCount <= 0 || !playerHasTarget){
        return 10;
    }
    arrowCount--;
    initProjectile(playerRef->x, playerRef->y, playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_ARROW, 20, 2.5f);
    return 40;
}

int useWand(){
    if (playerMana <= 20 || !playerHasTarget){
        return 10;
    }
    playerMana -= 20;
    initProjectile(playerRef->x, playerRef->y, playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_MAGIC, 30, 1.2f);
    return 45;
}

int usePotion(){
    inventory[selectedSlot] = ITEM_EMPTY;
    playerHp += 50;
    if (playerHp > 100){
        playerHp = 100;
    }
    return 10;
}

int useManaPotion(){
    inventory[selectedSlot] = ITEM_EMPTY;
    playerMana += 50;
    if (playerMana > 100){
        playerMana = 100;
    }
    return 10;
}

int useWand2(){
    if (playerMana <= 10 || !playerHasTarget){
        return 10;
    }
    playerMana -= 10;
    initProjectile(playerRef->x, playerRef->y, playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_MAGIC, 12, 0.8f);
    return 5;
}

int useSpear(){
    if (!playerHasTarget){
        return 10;
    }
    initProjectile(playerRef->x, playerRef->y, playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_SPEAR, 15, 1.5f);
    return 35;
}

int useBow2(){
    if (arrowCount <= 0 || !playerHasTarget){
        return 10;
    }
    arrowCount--;
    initProjectile(playerRef->x, playerRef->y, playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_ARROW, 50, 5.5f);
    return 40;
}

int useBow3(){
    if (arrowCount <= 1 || !playerHasTarget){
        return 10;
    }
    arrowCount -= 2;
    initProjectile(playerRef->x + (sin(playerRef->rotation) * 4), playerRef->y + (cos(playerRef->rotation) * 4), playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_ARROW, 20, 2.5f);
    initProjectile(playerRef->x - (sin(playerRef->rotation) * 4), playerRef->y - (cos(playerRef->rotation) * 4), playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_ARROW, 20, 2.5f);

    return 50;
}

int useSword2(){
    if (!playerHasTarget){
        return 10;
    }
    initProjectile(playerRef->x, playerRef->y, playerRef->rotation, TAG_PLAYER_ATTACK, PROJECTILE_SWORD_2, 20, 1.2f);
    return 30;
}

const Item itemSchema[ITEM_COUNT] = {
    {&swordSprite, &useSword},
    {&bowSprite, &useBow},
    {&wandSprite, &useWand},
    {&arrowSprite, NULLPTR},
    {&potionSprite, &usePotion},
    {&coinSprite, NULLPTR},
    {&manaPotionSprite, &useManaPotion},
    {&wand2Sprite, &useWand2},
    {&spearSprite, &useSpear},
    {&bow2Sprite, &useBow2},
    {&bow3Sprite, &useBow3},
    {&sword2Sprite, &useSword2}
};

//------------------------------------------------------------------------------------
// ITEM
//------------------------------------------------------------------------------------
void updateItem(Object* this){
    float yOffset = 0;

    // draw
    Object* player = getClosestObject(this, TAG_PLAYER);
    if (player != NULLPTR){
        float dist = pythagoras(this->x, this->y, player->x, player->y);
        yOffset = (fmax(60 - dist, 0) / 10) * (sin(gameTimer / 20.0f) + 1.0f);
    }

    Texture2D* spr = itemSchema[this->internalType].texture;
    DrawTexture(*spr, this->x, this->y - yOffset, WHITE);

}

void initItem(int x, int y, int internalType){

    Object item = initDefaultObject();
    item.x = x;
    item.y = y;
    item.tag = TAG_INTERACTABLE;
    item.internalType = internalType;
    item.update = &updateItem;

    addObject(item);
}

int getNewItemId(){
    int rng = GetRandomValue(0, 9);

    if (rng < 3){
        return ITEM_GOLD;
    }else if (rng < 6){
        return ITEM_ARROW;
    }else {
        int result = GetRandomValue(0, ITEM_COUNT - 2);
        if (result > ITEM_GOLD) result++;
        if (result > ITEM_ARROW) result++;
        return result;
    }
}


//------------------------------------------------------------------------------------
// PROJECTILES
//------------------------------------------------------------------------------------
void updateProjectile(Object* this){

    // move
    if (this->internalValue1 == 0){
        this->x -= sin(this->rotation) * this->moveSpeed;
        this->y -= cos(this->rotation) * this->moveSpeed;
    }else {
        this->internalValue1++;
        if (this->internalValue1 >= 10){
            this->exists = false;
        }

    }


    if (!canMoveTo(this->x, this->y)){

        this->internalValue1++;

    }

    // update vals
    this->internalTimer -= this->internalTimer > 0;
    if (this->internalTimer == 0){
        this->internalValue1++;
    }

    // draw
    Texture2D* spr;
    Color c = WHITE;

    c.a = (unsigned char)(lerp(255, 0, this->internalValue1 / 10.0f));

    switch (this->internalType){
        case PROJECTILE_SWORD:
        default:
            spr = &swordSprite;
            break;
        case PROJECTILE_ARROW:
            spr = &arrowSprite;
            break;
        case PROJECTILE_MAGIC:
            spr = &magicSprite;
            break;
        case PROJECTILE_SWORD_2:
            spr = &sword2Sprite;
            break;
        case PROJECTILE_SPEAR:
            spr = &spearSprite;
            break;
    }
    DrawTextureRotated(*spr, this->x, this->y, -this->rotation * RAD2DEG - 45, c);
}

void collideProjectile(Object* this, Object* other){
    if (other->tag == TAG_ENEMY && this->internalBool1 && this->tag == TAG_PLAYER_ATTACK){
        other->health -= this->damage;
        other->internalValue1 = 10;
        other->internalValue2 = 20;
        other->rotation = this->rotation;
        this->internalBool1 = false;
        this->internalTimer = 0;
    }else if (other->tag == TAG_PLAYER && this->tag == TAG_ENEMY_ATTACK && this->internalBool1){
        playerHp -= this->damage;
        other->internalValue2 = 20;
        this->internalBool1 = false;
        this->internalTimer = 0;
    }
}

void initProjectile(int x, int y, float direction, int tag, int type, int damage, float speed){
    Object projectile = initDefaultObject();
    projectile.x = x;
    projectile.y = y;
    projectile.w = 16;
    projectile.h = 16;
    projectile.rotation = direction;
    projectile.tag = tag;
    projectile.internalType = type;
    projectile.update = &updateProjectile;
    projectile.collide = &collideProjectile;
    projectile.internalBool1 = true; // can deal damage
    projectile.moveSpeed = speed;
    projectile.damage = damage;
    if (type == PROJECTILE_SWORD || type == PROJECTILE_SWORD_2){
        projectile.internalTimer = 30;
    }else if (type == PROJECTILE_SPEAR){
        projectile.internalTimer = 45;
    }else {
        projectile.internalTimer = 400;
    }

    addObject(projectile);

}
//------------------------------------------------------------------------------------
// FLOOR
//------------------------------------------------------------------------------------
bool floorData[FLOOR_WIDTH][FLOOR_HEIGHT];
void updateFloor(){
    for (int x = 0; x < FLOOR_WIDTH; x++){
        for (int y = 0; y < FLOOR_HEIGHT; y++){
            Texture2D* spr = &floorSprite;
            if (floorData[x][y]){
                spr = &wallSprite;
            }
            DrawTexture(*spr, x * 16, y * 16, WHITE);
        }
    }

    // draw exit
    Texture2D* texture;
    if (enemiesInRoom > 0)  texture = &closedExitTexture;
    else                    texture = &exitTexture;
    DrawTexture(*texture , exitX, exitY, WHITE);
}

void resetFloor(){
    for (int x = 0; x < FLOOR_WIDTH; x++){
        for (int y = 0; y < FLOOR_HEIGHT; y++){
            floorData[x][y] = true;
        }
    }
}

bool doesSquareOverlapOtherSquares(int startX, int startY, int w, int h){
    int connections = 0;
    int iterations = 0;
    for (int x = startX; x < w; x++){
        for (int y = startY; y < h; y++){
            iterations++;
            if (canMoveTo(x * 16, y * 16)){
                connections++;
            }
        }
    }
    return connections > 1 && connections < iterations >> 1;
}

void generateFloorSquare(bool connectsToOthers){
    int startX = 0;
    int startY = 0;
    int width = 0;
    int height = 0;
    const int MIN_SQUARE_WIDTH = 4;
    const int MAX_SQUARE_WIDTH = 10;

    do {
        startX = GetRandomValue(1, FLOOR_WIDTH - MIN_SQUARE_WIDTH - 1);
        startY = GetRandomValue(1, FLOOR_HEIGHT - MIN_SQUARE_WIDTH - 1);
        width = GetRandomValue(startX + MIN_SQUARE_WIDTH, min(FLOOR_WIDTH - 1, startX + MAX_SQUARE_WIDTH));
        height = GetRandomValue(startY + MIN_SQUARE_WIDTH, min(FLOOR_HEIGHT - 1, startY + MAX_SQUARE_WIDTH));

    }while(connectsToOthers == true && !doesSquareOverlapOtherSquares(startX, startY, width, height));

    // write square
    for (int x = startX; x < width; x++){
        for (int y = startY; y < height; y++){
            floorData[x][y] = false;
        }
    }

}

void generateFloor(){
    enemiesInRoom = 0;
    // generate layout
    resetFloor();
    generateFloorSquare(false);
    for (int i = 0; i < 5; i++){
        generateFloorSquare(true);
    }
    // objects
    clearObjects();
    int startX = 0;
    int startY = 0;
    score++;


    do{
       startX = GetRandomValue(2, FLOOR_WIDTH - 2) * 16;
       startY = GetRandomValue(2, FLOOR_HEIGHT - 2) * 16;
    }while (!canMoveTo(startX, startY));
    initPlayer(startX, startY);


    // enemies
    for (int i = 0; i < GetRandomValue(4, 7); i++){
        int spawnX;
        int spawnY;
        do{
            spawnX = GetRandomValue(1, FLOOR_WIDTH - 1) * 16;
            spawnY = GetRandomValue(1, FLOOR_HEIGHT - 1) * 16;
        }while (!canMoveTo(spawnX, spawnY) || pythagoras(spawnX, spawnY, startX, startY) < 80.0f);
        initTroll(spawnX, spawnY);
    }

    // items
    for (int i = 0; i < GetRandomValue(1, 3); i++){
        int spawnX;
        int spawnY;
        do{
            spawnX = GetRandomValue(1, FLOOR_WIDTH - 1) * 16;
            spawnY = GetRandomValue(1, FLOOR_HEIGHT - 1) * 16;
        }while (!canMoveTo(spawnX, spawnY) || pythagoras(spawnX, spawnY, startX, startY) < 80.0f);
        initItem(spawnX, spawnY, getNewItemId());
    }

    if (playerMoney > 20 && GetRandomValue(0, 3) == 0){
        // generate shop
        int shopX = 0;
        int shopY = 0;
        do {
            shopX = GetRandomValue(1, FLOOR_WIDTH - 1) * 16;
            shopY = GetRandomValue(1, FLOOR_HEIGHT - 1) * 16;
        }while(!canMoveTo(shopX, shopY) || !canMoveTo(shopX, shopY + 32));
        initShop(shopX, shopY);
    }

    // generate exit
    do {
        exitX = GetRandomValue(1, FLOOR_WIDTH - 1) * 16;
        exitY = GetRandomValue(1, FLOOR_HEIGHT - 1) * 16;
    }while(!canMoveTo(exitX, exitY));

}

bool canMoveTo(int x, int y){
    int xT = x / 16;
    int yT = y / 16;
    if (xT > FLOOR_WIDTH - 1){
        return false;
    }else if (yT > FLOOR_HEIGHT - 1){
        return false;
    }

    for (int i = 0; i <= 1; i++){
        for (int j = 0; j <= 1; j++){
            if (floorData[xT + i][yT + j]){
                return false;
            }
        }
    }

    return true;
}

//------------------------------------------------------------------------------------
// UI
//------------------------------------------------------------------------------------
void updateUi(){
    if (IsKeyDown(KEY_ONE)){
        selectedSlot = 0;
    }else if (IsKeyDown(KEY_TWO)){
        selectedSlot = 1;
    }else if (IsKeyDown(KEY_THREE)){
        selectedSlot = 2;
    }

    const int inventoryStart = (IN_GAME_WIDTH >> 1) - 48;

    // draw inventory
    for (int i = 0; i < 3; i++){
        Texture2D* spr = &uiUnselected;

        if (i == selectedSlot){
            spr = &uiSelected;
        }

        DrawTexture(*spr, i * 32 + inventoryStart, IN_GAME_HEIGHT - 32, WHITE);

        int item = inventory[i];

        if (item != ITEM_EMPTY){
            DrawTexture(*itemSchema[item].texture, i * 32 + 8 + inventoryStart, IN_GAME_HEIGHT - 32 + 8, WHITE);
        }
    }

    #define HUD_COUNTER_SIZE 4
    // hud and counters
    DrawTexture(uiHp, inventoryStart - 32, IN_GAME_HEIGHT - 32, WHITE);
    DrawTexture(uiMana, inventoryStart - 32, IN_GAME_HEIGHT - 16, WHITE);
    char hpDisplay[HUD_COUNTER_SIZE];
    char manaDisplay[HUD_COUNTER_SIZE];
    sprintf(hpDisplay, "%i", playerHp);
    sprintf(manaDisplay, "%i", playerMana);
    DrawText(hpDisplay, inventoryStart - 16, IN_GAME_HEIGHT - 28, 1, WHITE);
    DrawText(manaDisplay, inventoryStart - 16, IN_GAME_HEIGHT - 12, 1, WHITE);
    DrawTexture(arrowSprite, inventoryStart + 96, IN_GAME_HEIGHT - 32, WHITE);
    DrawTexture(coinSprite, inventoryStart + 96, IN_GAME_HEIGHT - 16, WHITE);
    char moneyDisplay[HUD_COUNTER_SIZE];
    char arrowDisplay[HUD_COUNTER_SIZE];
    sprintf(moneyDisplay, "%i", playerMoney);
    sprintf(arrowDisplay, "%i", arrowCount);
    DrawText(arrowDisplay, inventoryStart + 112, IN_GAME_HEIGHT - 28, 1, WHITE);
    DrawText(moneyDisplay, inventoryStart + 112, IN_GAME_HEIGHT - 12, 1, WHITE);

    // score
    char scoreDisplay[HUD_COUNTER_SIZE];
    sprintf(scoreDisplay, "%i", score);
    DrawText(scoreDisplay, (IN_GAME_WIDTH >> 1), 20, 20, WHITE);
}


//------------------------------------------------------------------------------------
// INVENTORY
//------------------------------------------------------------------------------------
void equipItem(int item){
    if (item == ITEM_GOLD){
        playerMoney += GetRandomValue(15, 45);
        if (playerMoney > 999){
            playerMoney = 999;
        }
        return;
    }else if (item == ITEM_ARROW){
        arrowCount += GetRandomValue(1,3) * 5;
        if (arrowCount > 999){
            arrowCount = 999;
        }
        return;
    }

    for (int i = 0; i < 3; i++){
        if (inventory[i] == ITEM_EMPTY){
            inventory[i] = item;
            return;
        }
    }
    // drop current item
    initItem(playerRef->x, playerRef->y, inventory[selectedSlot]);
    inventory[selectedSlot] = item;
}

void resetInventory(){
    for (int i = 0; i < 3; i++){
        inventory[i] = ITEM_EMPTY;
    }
}

int useItem(){
    if (inventory[selectedSlot] != ITEM_EMPTY){
        return itemSchema[inventory[selectedSlot]].use();
    }
    return 10;
}

//------------------------------------------------------------------------------------
// SHOP
//------------------------------------------------------------------------------------
#define PRICE_SIZE 4
void updateShopItem(Object* this){
    DrawTexture(*itemSchema[this->internalType].texture, this->x, this->y, WHITE);
    char price[PRICE_SIZE];
    sprintf(price, "%i$", this->internalValue1);
    DrawText(price, this->x + 2, this->y + 16, 1, WHITE);
}

void initShopItem(int x, int y){
    if (!canMoveTo(x, y)){
        return;
    }

    Object shopItem = initDefaultObject();

    shopItem.x = x;
    shopItem.y = y;
    shopItem.internalType = GetRandomValue(0, ITEM_COUNT);
    if (shopItem.internalType == ITEM_GOLD) shopItem.internalType = ITEM_ARROW;
    if (shopItem.internalType == ITEM_POTION || shopItem.internalType == ITEM_MANA_POTION || shopItem.internalType == ITEM_ARROW){
        shopItem.internalValue1 = GetRandomValue(10, 20);
    }else{
        shopItem.internalValue1 = GetRandomValue(30, 50);
    }
    shopItem.update = &updateShopItem;
    shopItem.tag = TAG_INTERACTABLE;
    addObject(shopItem);

}



void updateShopKeeper(Object* this){
    DrawTexture(shopKeeper, this->x, this->y, WHITE);
}

void initShop(int x, int y){

    Object shopKeeper = initDefaultObject();
    shopKeeper.x = x;
    shopKeeper.y = y;
    shopKeeper.update = &updateShopKeeper;

    addObject(shopKeeper);

    int rng = GetRandomValue(1, 2);

    if (rng == 1){
        initShopItem(x - 16, y + 16);
        initShopItem(x + 16, y + 16);

    }else {
        initShopItem(x - 32, y + 16);
        initShopItem(x + 32, y + 16);
        initShopItem(x, y + 16);
    }
}

//------------------------------------------------------------------------------------
// SCREEN TRANSITION
//------------------------------------------------------------------------------------
void (*transitionFunction)() = NULLPTR;
void updateScreenTransition(){
    screenTransitionTimer -= screenTransitionTimer > 0;
    Color c = WHITE;
    c.a = (unsigned char)(1.0f - ((abs(screenTransitionTimer - 60) * 0.016666667f)) * 255);

    if (screenTransitionTimer == 60 && transitionFunction != NULLPTR){
        transitionFunction();
    }

    for (int i = 0; i < FLOOR_WIDTH; i++){
        for (int j = 0; j < FLOOR_HEIGHT; j++){

            DrawTexture(blackSprite, i * 16, j * 16, c);

        }
    }
}

void activateTransition(void (*fun)()){
    transitionFunction = fun;
    screenTransitionTimer = 120;
}

//------------------------------------------------------------------------------------
// RESET
//------------------------------------------------------------------------------------
void reset(){
    playerHp = 100;
    playerMana = 100;
    selectedSlot = 0;
    arrowCount = 5;
    playerMoney = 0;
    resetInventory();
    enemiesInRoom = 0;
    equipItem(ITEM_SWORD);
    score = 0;
}

//------------------------------------------------------------------------------------
// GAMEOVER
//------------------------------------------------------------------------------------
void restartGame(){
    reset();
    generateFloor();
}
void gameOver(){
    DrawText("KONEC GAMESKY", (IN_GAME_WIDTH >> 1) - 30, (IN_GAME_HEIGHT >> 1) - 13, 10, WHITE);

    if (IsKeyDown(KEY_R)){
        activateTransition(&restartGame);
    }
}

//------------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------------
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
    ToggleFullscreen();
    HideCursor();
    SetTargetFPS(60);
    loadTextures();

    float scalingFactor = SCREEN_WIDTH /(float)(GetScreenWidth());
    int renderTextureOffset = ((GetScreenWidth()) / 2) - (SCREEN_WIDTH / 2);
    cam.zoom = CAMERA_ZOOM;
    reset();
    generateFloor();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginTextureMode(renderTexture);
            BeginMode2D(cam);
                ClearBackground(WHITE);

                updateFloor();
                updateObjects();
                updateUi();
                updateScreenTransition();

                if (playerHp == 0){
                    gameOver();
                }
            EndMode2D();
        EndTextureMode();
        BeginDrawing();
            ClearBackground(BLACK);
            Rectangle r = { 0, 0, (float)(renderTexture.texture.width), (float)(-renderTexture.texture.height) };
            Rectangle r2 = { renderTextureOffset, 0, (float)(GetScreenWidth()) * scalingFactor, (float)(GetScreenHeight()) };
            Vector2 v = {0, 0};
            DrawTexturePro(renderTexture.texture,r,r2,v,0,WHITE);

        EndDrawing();

        gameTimer++;
    }

    CloseWindow();        // Close window and OpenGL context
    unloadTextures();
    return 0;
}
