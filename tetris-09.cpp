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
// 1. Setup The Game Loop -> Ok
// 2. Creating the Grid -> Ok
// 3. Create the blocks -> Ok
// 4. Move de Blocks -> Ok
// 5. Rotate the blocks -> Ok
// 6. Checking for colisions -> Ok
// 7. Check for completed rows -> Ok
// 8. Game Over -> Ok
// 9. Create User Interface -> Ok
//10. Add Score -> OK
//11. Add Next Block
//12. Add Sounds
//
#include <iostream>
#include <raylib.h>
#include "game.h"
#include "colors.h"

// Definicion de variables y constantes para el juego -----------------
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};
Color Grey = Color{29, 29, 29, 255};

double lastUpdateTime = 0;

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

    InitWindow(screen_width, screen_height, "Mi Retro - Game of Tetris!");
    SetTargetFPS(FPS); 
    
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    // Iniciamos la clase Game que ira creando el restos de clases para inciar el juego
    Game game = Game();

    //Grid grid = Grid();
    //grid.Print();
    //LBlock block = LBlock();
    //block.Move(8, 5);

    // Loop del juego de simulacion -------------------------------------
  while (WindowShouldClose() == false) {
  
    // 1. Event Handing
    game.HandleInput();
    if(EventTriggered(0.2)){        //tenporalmente podemos cambiar este valor para depuracion y mas lento a 0.002
      game.MoveBlockDown();  
    }
    // 2. Updating State
    // 3. Drawing Objects
    BeginDrawing();
    ClearBackground(darkBlue);
    DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
    if (game.gameOver){
        DrawTextEx(font, "GAME", {320, 450}, 38, 2, WHITE);
        DrawTextEx(font, "OVER", {375, 480}, 38, 2, WHITE);
    }
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

    char scoreText[10];
    sprintf(scoreText, "%d", game.score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
