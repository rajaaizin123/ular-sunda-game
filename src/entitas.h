#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define MAX_LENGTH 100
#define FONT_SIZE 20
#define CELL_COUNT 33
#define CELL_SIZE 15

const int offset = 50; // garis luar
const int cell_size = 15;   // satu grid dengan 15 pixel
const int cell_count = 33;  // untuk iterasi

Color green_neon = {57, 255, 20, 255}; 
Color red_food = {255, 59, 48, 255};
Color black_background = {20, 14, 38, 255};  
Color yellow_text = {255, 223, 0, 255};

typedef struct{
    int posisi_x; 
    int posisi_y;
    Texture2D tekstur;
}Makanan;

typedef struct{
    int posisi_x;
    int posisi_y;
}Ular;


// fungsinya punya entitas makanan

int randomX(){
    return GetRandomValue(0, CELL_COUNT - 1);
}

int randomY(){
    return GetRandomValue(0, CELL_COUNT - 1);
}

void loadMakanan(Makanan *makanan){
    Image gambar = LoadImage("D:/raylib/snake-game-c/src/assets/food4.png");
    makanan->tekstur = LoadTextureFromImage(gambar);
    UnloadImage(gambar);
    makanan->posisi_x = randomX() * CELL_SIZE;
    makanan->posisi_y = randomY() * CELL_SIZE;
}

void unloadgambar(Makanan *makanan){
    UnloadTexture(makanan->tekstur);
}

void drawMakanan(Makanan *makanan){
    DrawTexture(makanan->tekstur, offset + makanan->posisi_x, offset + makanan->posisi_y, red_food);
}

// fungsinya punya entitas ular

void updateMakanan(Ular *ular, Makanan *makanan, int *score, Sound suaraMakan, int *panjangUlar){
    if ((ular[0].posisi_x) == makanan->posisi_x && (ular[0].posisi_y) == makanan->posisi_y){
        *score += 5;

        PlaySound(suaraMakan);

        if (*panjangUlar < MAX_LENGTH){
            *panjangUlar += 1;
        }

        // update makanan dengan posisi baru di grid
        makanan->posisi_x = randomX() * CELL_SIZE;
        makanan->posisi_y = randomY() * CELL_SIZE;
    }
}

void reset(Ular *ular, int *panjangUlar, int *move_x, int *move_y, int *score){
    *move_x = 0;
    *move_y = 0;
    *score = 0;
    *panjangUlar = 3;

    ular[0].posisi_x = 10 * CELL_SIZE; //ular[0]  --> kepala ular
    ular[0].posisi_y = 8 * CELL_SIZE;
    ular[1].posisi_x = 9 * CELL_SIZE;
    ular[1].posisi_y = 8 * CELL_SIZE;
    ular[2].posisi_x = 8 * CELL_SIZE; 
    ular[2].posisi_y = 8 * CELL_SIZE;
}

bool apakahKenaEkor(Ular *ular, int panjangUlar) {
    for (int i = 1; i < panjangUlar; i++) {
        if (ular[0].posisi_x == ular[i].posisi_x && ular[0].posisi_y == ular[i].posisi_y) {
            return true;
        }
    }
    return false;
}

void updateMove(Ular *ular, int move_x, int move_y, int panjangUlar){
    // tubuh mengikuti kepala
    if ((move_x == 0 && move_y != 0) || (move_y == 0 && move_x != 0)){  // deklarasi saat diam (baru mulai..)
        for (int i = panjangUlar; i > 0; i--){
            ular[i] = ular[i - 1];
        }
    }
}


