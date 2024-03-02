#include "Player.h"

Player::Player() 
{
    PlayerLives = 3;
    PlayerScore = 0;
}


void Player::SetLives(int Lives)
{
    PlayerLives = Lives;
}

void Player::SetScore(int Score) {
    PlayerScore = Score;
}