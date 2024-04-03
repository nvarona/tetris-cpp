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
// 1. Setup The Game Loop -> OK
// 2. Creating the Grid -> OK
// 3. Create the blocks -> OK 
//
#include <iostream>
#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"


// Definicion de variables y constantes para el juego -----------------
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};
Color Grey = Color{29, 29, 29, 255};
Color darkBlue = {44, 44, 127, 255};

int main() {
    // Comenzamos el programa ------------------------------------------
    std::cout << std::endl;
    std::cout << "Starting the game ..." << std::endl;
    std::cout << std::endl;

    const int screen_width = 300;
    const int screen_height = 600;
    int FPS = 12;
    int Cell_Size = 25;

    InitWindow(screen_width, screen_height, "Mi Retro - Game of Tetris!");
    SetTargetFPS(FPS); 

    Grid grid = Grid();
    grid.Print();
    
    LBlock block = LBlock();

    // Loop del juego de simulacion -------------------------------------
  while (WindowShouldClose() == false) {
  
    // 1. Event Handing
    // 2. Updating State
    // 3. Drawing Objects
    grid.Draw();
    block.Draw();
    BeginDrawing();
    ClearBackground(darkBlue);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
