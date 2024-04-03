#include "game.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    level = 1;
    lines = 0;
    // Ponemos sonido a nuestro juego de tetris
    InitAudioDevice();
    music = LoadMusicStream("Sounds/original-tetris-theme.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    gameSound = LoadSound("Sounds/game-over-tetris.mp3");
}

Game::~Game(){
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    UnloadSound(gameSound);
    CloseAudioDevice();
}

Block Game::GetRandomBlock(){
    if (blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(){
    grid.Draw();
    currentBlock.Draw(11, 11);  // Para darle la posicion de los bloques normales
    switch (nextBlock.id){
    case 3:
        nextBlock.Draw(255, 505);   // Bloque OBloque
        break;
    case 4:
        nextBlock.Draw(255, 495);   // Bloque IBlock
        break;
    default:
        nextBlock.Draw(270, 485);   // Pintar el proximo bloque en pantalla
        break;
    }
}

void Game::HandleInput(){
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0){
        gameOver = false;
        Reset();
    }
    switch (keyPressed){
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0, 1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft(){
    if (!gameOver){
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight(){
    if (!gameOver){
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown(){
    if (!gameOver){
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles){
        if (grid.IsCellOutside(item.row, item.column)){
            return true;
        }
    }
    return false;
}

void Game::RotateBlock(){
    if (!gameOver){
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.UndoRotation();
        } else {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles){
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits() == false){
        gameOver = true;
        PlaySound(gameSound);
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0){
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
        lines += rowsCleared; 
    }
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles){
        if (grid.IsCellEmpty(item.row, item.column) == false){
            return false;
        }
    }
    return true;
}

void Game::Reset(){
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints){
    switch (linesCleared){
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }
    score += moveDownPoints;
}
