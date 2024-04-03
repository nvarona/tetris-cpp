//
// ooooooooooooo               .             o8o           
// 8'   888   `8             .o8             `"'           
//      888       .ooooo.  .o888oo oooo d8b oooo   .oooo.o 
//      888      d88' `88b   888   `888""8P `888  d88(  "8 
//      888      888ooo888   888    888      888  `"Y88b.  
//      888      888    .o   888 .  888      888  o.  )88b 
//     o888o     `Y8bod8P'   "888" d888b    o888o 8""888P' 
//
// Version del template para el Juego TETRIS en estilo RETRO con libreria RAYLIB ---------
// Date 2024
// Desarrollo de Natxo Varona
//
// Nota: Lista de los bloques del indice del taller de juegos retros
//  1. Setup The Game Loop
//  2. Creating the Grid
//  3. Create the blocks
//  4. Move de Blocks
//  5. Rotate the blocks
//  6. Checking for colisions
//  7. Check for completed rows
//  8. Game Over
//  9. Create User Interface
// 10. Add Score
// 11. Add Next Block
// 12. Add Sounds
//--------------------------------------------------------------------------------------

#include <iostream>
#include <raylib.h>
#include <vector>
#include "game.h"
#include "colors.h"

// Definicion de variables y constantes para el juego -----------------
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};
Color Grey = Color{29, 29, 29, 255};

double lastUpdateTime = 0;

// Función para calcular el nivel actual basado en el número de líneas eliminadas
int calculateLevel(int lineDelete) {
  // Nivel inicial que comienza el juego 
  int nivel = 1;

  // Tabla de niveles y lineas requeridas para pasar de nivel
  int lineasRequeridas[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

  // Recorrer la tabla de niveles
  for (int i = 0; i < sizeof(lineasRequeridas) / sizeof(lineasRequeridas[0]); ++i) {
    // Si el número de líneas borradas es mayor o igual que las líneas requeridas para el nivel actual, 
    //aumentar el nivel
    if (lineDelete >= lineasRequeridas[i]) {
      nivel = i + 1;
    } else {
      break;
    }
  }

  // Devolver el nivel calculado
  return nivel;
}

// Función para calcular la velocidad de caída de los bloques
float calculateSpeed(int nivel) {
  // Velocidad inicial
  float velocidad = 0.2f;

  // Incremento de velocidad por nivel
  float incrementoVelocidad = 0.1f;

  // Calcular la velocidad de caída
  velocidad += (nivel - 1) * incrementoVelocidad;

  // Limitar la velocidad máxima
  if (velocidad > 2.0f) {
    velocidad = 2.0f;
  }

  // Devolver la velocidad calculada
  return velocidad;
}

bool EventTriggered(double interval){
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {
    // Comenzamos el programa ------------------------------------------
    std::cout << std::endl;
    std::cout << "Starting the game ..." << std::endl;
    std::cout << std::endl;

    const int screen_width = 500;       // Sin interface entero seria 300
    const int screen_height = 620;      // Sin interface entero seria 600
    int FPS = 12;
    int Cell_Size = 25;
    float speedLevel = 0.2;

    InitWindow(screen_width, screen_height, "Mi Retro - Game of Tetris!");
    SetTargetFPS(FPS); 
    
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    // Iniciamos la clase Game que ira creando el restos de clases para inciar el juego
    Game game = Game();

    // Loop del juego de simulacion -------------------------------------
    while (WindowShouldClose() == false) {
    
        UpdateMusicStream(game.music);  // Activamos la musica cuando comenzamos el juego
        // 1. Event Handing ---------------------------------------------
        game.HandleInput();
        if (EventTriggered(speedLevel)){
            game.MoveBlockDown();  
        }
        // 2. Updating State --------------------------------------------
        game.level = calculateLevel(game.lines);
        speedLevel = calculateSpeed(game.level);

        // 3. Drawing Objects -------------------------------------------
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Lines", {365, 135}, 38, 2, WHITE);
        DrawTextEx(font, "Level", {365, 250}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 390}, 38, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);    // Rectangulo para Score
        DrawRectangleRounded({320, 175, 170, 60}, 0.3, 6, lightBlue);    // Rectangulo para Lines
        DrawRectangleRounded({320, 290, 170, 60}, 0.3, 6, lightBlue);    // Rectangulo para Level
        DrawRectangleRounded({320, 430, 170, 180}, 0.3, 6, lightBlue);  // Rectangulo para Next Block
        if (game.gameOver){
            DrawRectangleRounded({20, 220, 170, 180}, 0.3, 6, lightBlue);    // Rectangulo para GameOver
            DrawTextEx(font, "GAME", {100, 250}, 38, 2, WHITE);
            DrawTextEx(font, "OVER", {120, 280}, 38, 2, WHITE);
            DrawTextEx(font, "Plase Try Again", {100,305}, 20, 2, WHITE);
            int keyPressed = GetKeyPressed();
            if (keyPressed == KEY_ESCAPE){
                break;
            }
        }
        char scoreText[10];
        Vector2 textSize;           // Declarar textSize una sola vez
        snprintf(scoreText, sizeof(scoreText), "%d", game.score);
        textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        scoreText[0] = '\0';        // Limpiar la cadena
        snprintf(scoreText, sizeof(scoreText), "%d", game.lines);
        textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 185}, 38, 2, WHITE);
        scoreText[0] = '\0';        // Limpiar la cadena
        snprintf(scoreText, sizeof(scoreText), "%d", game.level);
        textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 300}, 38, 2, WHITE);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
