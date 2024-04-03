#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;
    int level;
    int lines;
    Music music;

private:
    bool IsBlockOutside();
    void RotateBlock();
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Grid grid;
    std::vector<Block> GetAllBlocks();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
    Sound gameSound;
};