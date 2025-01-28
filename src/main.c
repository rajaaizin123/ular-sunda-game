#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "entitas.h"

void unloadResource(Makanan *makanan, Sound suaraMakan, Sound suaraNabrak, Sound suaraKemenangan){
    unloadgambar(makanan);
    UnloadSound(suaraMakan);
    UnloadSound(suaraNabrak);
    UnloadSound(suaraKemenangan);
    CloseAudioDevice();
}

int main(void) {
    InitWindow(2 * offset + SCREEN_WIDTH, 2 * offset + SCREEN_HEIGHT, "Aizin - Dev");
    SetTargetFPS(10); // set disini untuk kecepatan ular (masih perlu pengembangan kedepan) karena masih dalam bentuk fps (buruk)

    // Deklarasi Makanan
    Makanan makanan;
    loadMakanan(&makanan);

    // Deklarasi Ular
    Ular ular[MAX_LENGTH];
    int panjangUlar = 3;  // panjang awal 
    int move_x = 0;
    int move_y = 0;
    int score = 0;
    int score_win = 180;
    
    // mulai game
    reset(ular, &panjangUlar, &move_x, &move_y, &score);

    // suara
    Sound suaraMakan;
    Sound suaraNabrak;
    Sound suaraKemenangan;
    InitAudioDevice();
    // sesuaikan path absolut dengan folder anda
    suaraMakan = LoadSound("D:/raylib/snake-game-c/src/assets/eat.mp3");
    suaraNabrak = LoadSound("D:/raylib/snake-game-c/src/assets/wall.mp3");
    suaraKemenangan = LoadSound("D:/raylib/snake-game-c/src/assets/victory.mp3");

    while (!WindowShouldClose()) {
        BeginDrawing();

        // 1 grid bukan 1 pixel
        if (IsKeyPressed(KEY_RIGHT) && move_x != -1){
            move_x = 1;   
            move_y = 0;
        }
        if (IsKeyPressed(KEY_LEFT) && move_x != 1){
            move_x = -1;
            move_y = 0;
        }  
        if (IsKeyPressed(KEY_UP) && move_y != 1){
            move_x = 0;
            move_y = -1;
        }   
        if (IsKeyPressed(KEY_DOWN) && move_y != -1){
            move_x = 0;
            move_y = 1;
        }

        // update gerakan ular
        updateMove(ular, move_x, move_y, panjangUlar);

        // pergerakan ular
        ular[0].posisi_x += move_x * CELL_SIZE;
        ular[0].posisi_y += move_y * CELL_SIZE;
   

        // cek ketabrak dinding
        if (ular[0].posisi_x >= SCREEN_WIDTH - CELL_SIZE
            || ular[0].posisi_x < 0
            || ular[0].posisi_y > SCREEN_HEIGHT - CELL_SIZE
            || ular[0].posisi_y < 0){
            PlaySound(suaraNabrak);

            reset(ular, &panjangUlar, &move_x, &move_y, &score); // reset ulang
        }

        if (apakahKenaEkor(ular, panjangUlar))
            reset(ular, &panjangUlar, &move_x, &move_y, &score);

        if (score == score_win){
            reset(ular, &panjangUlar, &move_x, &move_y, &score);
            PlaySound(suaraKemenangan);
        }

        // update posisi makanan
        updateMakanan(ular, &makanan, &score, suaraMakan, &panjangUlar);

        ClearBackground(black_background);
        // frame
        Rectangle rect = {(float)offset - 5, (float)offset - 5, (float)cell_size * cell_count + 10, (float)cell_size * cell_count + 10};
        DrawRectangleLinesEx(rect, 5, WHITE);

        // tubuh ular
        for (int i = 0; i < panjangUlar; i++) {
            Rectangle tubuh_ular = { offset + (float)ular[i].posisi_x,offset + (float)ular[i].posisi_y, (float)cell_size, (float)cell_size};
            DrawRectangleRounded(tubuh_ular, 0.6, 6, green_neon);
        }

        // makanan
        drawMakanan(&makanan);

        // teks
        DrawText("Ular Sunda", offset, CELL_SIZE, FONT_SIZE, WHITE);
        DrawText(TextFormat("Poin: %d", score), SCREEN_WIDTH - CELL_SIZE, offset + SCREEN_HEIGHT, FONT_SIZE, yellow_text);

        EndDrawing();
    }
    
    unloadResource(&makanan, suaraMakan, suaraNabrak, suaraKemenangan);
    CloseWindow();
    return 0;
}
