/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include <fstream>
#include "uiInteract.h"
#include "point.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"
#include "star.h"

using namespace std;




/*****************************************
* GAME
* The main game class containing all the state
*****************************************/
class Game
{
private:
    // The coordinates of the screen
    Point topLeft;
    Point bottomRight;
    int score;
    int highestScore;
    std::vector<Bullet*> bullets;
    std::list<Rock*> rocks;
    Ship ship;
    Star star;
    bool starCaptured;
    bool gameOver;
    bool levelCompleted;
    int level;
    

private:
/*************************************************
* Private methods to help with the game logic.
*************************************************/
    void advanceBullets();
    void advanceAsteroids();
    void handleCollisions();
    void cleanUpZombies();
    void isLevelCompleted();
    void nextLevel();
    void quitGame();
    void restartGame();
    void cleanGame();
    void setHighScore();
    Rock* createRock(string type, Point p = {0, 0}, int dy = 0, int dx = 0);
    void startLevel(int level);
    float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
    bool closeEnough(Point obj1, Point obj2, int radius1, int radius2);
    
    
public:
/*********************************************
* Constructor
* Initializes the game
*********************************************/
    Game(Point tl, Point br);
    ~Game();

/*********************************************
* Function: handleInput
* Description: Takes actions according to whatever
*  keys the user has pressed.
*********************************************/
void handleInput(const Interface & ui);
    
/*********************************************
 * Function: advance
 * Description: Move everything forward one
 *  step in time.
 *********************************************/
void advance();

/*********************************************
* Function: draw
* Description: draws everything for the game.
*********************************************/
void draw(const Interface & ui);


};



#endif /* GAME_H */
