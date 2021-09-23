/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "point.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
#include <fstream>
using namespace std;




/*********************************************
* Constructor
* Initializes the game
*********************************************/
Game::Game(Point tl, Point br)
{
    topLeft = tl;
    bottomRight = br;
    score = 0;
    level = 1;
    gameOver = false;
    levelCompleted = false;
    starCaptured = false;
    startLevel(level);
    ship.setTopLeft(tl);
    ship.setBottomRight(br);
    highestScore = 0;
    ifstream fin("highest_score.txt");
    
    if(fin.fail())
    {
        ofstream fout("highest_score.txt");
                    //("/Users/nayade/Documents/Nefi/School/CS65/Projects/Asteroids/Asteroids/highest_score.txt");
      fout << highestScore;
      fout.close();
    }
    else
    {
      fin >> highestScore;
      fin.close();
    }
    
}

/*********************************************
* Deconstructor
* Initializes the game
*********************************************/
Game::~Game()
{
    //Nothinng
}

/*********************************************
* Function: handleInput
* Description: Takes actions according to whatever
*  keys the user has pressed.
*********************************************/
void Game::handleInput(const Interface & ui)
{
   if(!gameOver && !levelCompleted)
   {
      // Change the direction of the rifle
      if (ui.isLeft())
      {
          ship.turnLeft();
      }
      if (ui.isRight())
      {
          ship.turnRight();
      }
       
      if (ui.isUp())
      {
          ship.applyThrust();
      }
       
      if (ui.isDown())
      {
          
      }
      // Check for "Spacebar
      if (ui.isSpace())
      {
         Bullet * newBullet = new Bullet;
         newBullet->fire(ship.getPoint(), ship.getAngle());
         newBullet->setTopLeft(topLeft);
         newBullet->setBottomRight(bottomRight);
         newBullet->setDy(newBullet->getDy() + ship.getDy());
         newBullet->setDx(newBullet->getDx() + ship.getDx());
         bullets.push_back(newBullet);
      }
   }
   else if (gameOver)
   {
      if (ui.isQ())
      {
        quitGame();
      }
          
      if (ui.isR())
      {
        restartGame();
      }
   }
   else if (levelCompleted)
   {
      if (ui.isC())
      {
          nextLevel();
      }
      if (ui.isQ())
      {
        quitGame();
      }
   }
}

/*********************************************
 * Function: advance
 * Description: Move everything forward one
 *  step in time.
 *********************************************/
void Game::advance()
{
   if(!gameOver && !levelCompleted)
   {
      advanceBullets();
      advanceAsteroids();
      ship.advance();
      handleCollisions();
      cleanUpZombies();
      isLevelCompleted();
   }
}

void Game::setHighScore()
{
    if(score > highestScore)
    {
       highestScore = score;
       ofstream fout("highest_score.txt");
       fout << highestScore;
       fout.close();
       std::cout << "This is happenign " << std::endl;
    }
}

void Game::quitGame()
{
    setHighScore();
    cleanGame();
    exit(0);
}

void Game::restartGame()
{
    cleanGame();
    score = 0;
    level = 1;
    gameOver = false;
    startLevel(level);
}

void Game::isLevelCompleted()
{
   if(rocks.size() == 0 && starCaptured)
   {
       levelCompleted = true;
       setHighScore();
   }
}

void Game::nextLevel()
{
    level++;
    cleanGame();
    startLevel(level);
}

void Game::cleanGame()
{
    vector<Bullet*>::iterator bulletIt = bullets.begin();
    while (bulletIt != bullets.end())
    {
          delete (*bulletIt);
          *bulletIt = NULL;
          bulletIt = bullets.erase(bulletIt);
    }
    
    list<Rock*>::iterator rocksIt = rocks.begin();
     for(rocksIt = rocks.begin(); rocksIt != rocks.end();)
     {
            delete *rocksIt;
            *rocksIt = NULL;
            // remove from list and advance
            rocksIt = rocks.erase(rocksIt);
     }
}
/*********************************************
* Function: draw
* Description: draws everything for the game.
*********************************************/
void Game::draw(const Interface & ui)
{
    if(star.isAlive())
    {
       star.draw();
    }
    
    list<Rock*>::iterator it;
    for(it = rocks.begin(); it != rocks.end(); ++it)
    {
        (*it)->draw();
        if(gameOver)
        {
           (*it)->setConstRotation(0);
        }
    }
    ship.draw();
    vector<Bullet*>::iterator it2;
    for(it2 = bullets.begin(); it2 != bullets.end(); ++it2)
    {
        (*it2)->draw();
    }
    Point highestScoreTextLocation;
    highestScoreTextLocation.setX(topLeft.getX() + 5);
    highestScoreTextLocation.setY(topLeft.getY() - 20);
      
    Point highestScoreLocation;
    highestScoreLocation.setX(topLeft.getX() + 5);
    highestScoreLocation.setY(topLeft.getY() - 25);
     
     
    Point scoreTextLocation;
    scoreTextLocation.setX(topLeft.getX() + 5);
    scoreTextLocation.setY(topLeft.getY() - 55);
    
    Point scoreLocation;
    scoreLocation.setX(topLeft.getX() + 5);
    scoreLocation.setY(topLeft.getY() - 60);
     
    Point currentLevelTextLocation;
    currentLevelTextLocation.setX(bottomRight.getX() - 60);
    currentLevelTextLocation.setY(topLeft.getY() - 20);
    
    Point currentLevelLocation;
    currentLevelLocation.setX(bottomRight.getX() - 60);
    currentLevelLocation.setY(topLeft.getY() - 25);
    
    
    drawText(highestScoreTextLocation, "HIGHEST SCORE");
    drawNumber(highestScoreLocation, highestScore);
    drawText(scoreTextLocation, "CURRENT SCORE");
    drawNumber(scoreLocation, score);
    drawText(currentLevelTextLocation, "LEVEL");
    drawNumber(currentLevelLocation, level);
    if(gameOver)
    {
       Point gameOverTextLocation (-50, 60);
       drawText(gameOverTextLocation, "GAME OVER");
       Point restartTextLocation (-60, 40);
       drawText(restartTextLocation, "To restart press 'R'");
       Point quitTextLocation (-70, 20);
       drawText(quitTextLocation, "To quit game press 'Q'");
    }
    if(levelCompleted)
    {
        Point levelCompletedTextLocation (-55, 60);
        drawText(levelCompletedTextLocation, "LEVEL COMPLETED");
        Point continueTextLocation (-57, 40);
        drawText(continueTextLocation, "To continue press 'C'");
        Point quitTextLocation (-70, 20);
        drawText(quitTextLocation, "To quit the  game press 'Q'");
        
    }
}


void Game::advanceBullets()
{
    vector<Bullet*>::iterator it2;
    for(it2 = bullets.begin(); it2 != bullets.end(); ++it2)
    {
        (*it2)->advance();
    }
}

void Game::advanceAsteroids()
{
    list <Rock*> :: iterator it;
    for (it = rocks.begin(); it != rocks.end(); ++it)
    {
        (*it)->advance();
    }
        
}


bool Game::closeEnough(Point obj1, Point obj2, int radius1, int radius2)
{
    //Hypothenus distance
    float xDiff =  fabs(obj1.getX() - obj2.getX());
    float yDiff = fabs(obj1.getY() - obj2.getY());
    double hy = sqrt((xDiff * xDiff) + (yDiff * yDiff));
    double radius = radius1 + radius2;
    return hy < radius;
}
/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a bird and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{
   //Check if the ship has captured the star
   if(closeEnough(star.getPoint(), ship.getPoint(), star.getRadius(), ship.getRadius()))
   {
       starCaptured = true;
       star.kill();
   }
   //Check if the star has been destroyed
   if(star.isAlive())
   {
       vector<Bullet*>::iterator it;
       for (it = bullets.begin(); it != bullets.end(); it++)
       {
           if((closeEnough((*it)->getPoint(), star.getPoint(), (*it)->getRadius(), star.getRadius())))
           {
               star.kill();
               setHighScore();
               gameOver = true;
           }
        }
   }
    
   //Check if the ship has crashed
   list< Rock * >::iterator it;
   for (it = rocks.begin(); it != rocks.end(); it++)
   {
       if((*it)->isAlive() && (closeEnough((*it)->getPoint(), ship.getPoint(), (*it)->getRadius(), ship.getRadius())))
       {
           ship.kill();
           gameOver = true;
           if (highestScore < score)
           {
               highestScore = score;
               ofstream fout("highest_score.txt");
               fout << highestScore;
               fout.close();
           }
           break;
       }
   }
   if(ship.isAlive())
   {
   // now check for a hit (if it is close enough to any live bullets
   for (int i = 0; i < bullets.size(); i++)
   {
       if (bullets[i]->isAlive())
       {
         // this bullet is alive, see if its too close from each rock
          
          for (it = rocks.begin(); it != rocks.end(); it++)
          {
            if((*it)->isAlive() && (closeEnough((*it)->getPoint(), bullets[i]->getPoint(), (*it)->getRadius(), bullets[i]->getRadius())))
            {
               
               score += (*it)->hit();
               bullets[i]->kill();
               switch((*it)->hit())
               {
                   case 1:
                      for(int i = 0; i < 1; i++)
                      {
                           Rock * mediumRock1 = createMediumRock((*it)->getPoint());
                           mediumRock1->setDx((*it)->getVelocity().getDx());
                           mediumRock1->setDy(((*it)->getVelocity().getDy() + 1));
                           rocks.push_back(mediumRock1);
                    
                           Rock * mediumRock2 = createMediumRock((*it)->getPoint());
                           mediumRock2->setDx((*it)->getVelocity().getDx());
                           mediumRock2->setDy(((*it)->getVelocity().getDy() - 1));
                           rocks.push_back(mediumRock2);
            
                           Rock * smallRock = createSmallRock ((*it)->getPoint());
                           smallRock->setDx(((*it)->getVelocity().getDx() + 2));
                           smallRock->setDy((*it)->getVelocity().getDy());
                           rocks.push_back(smallRock);
                       }
                       
                       break;
                   case 2:
                       for(int i = 0; i < 1; i++)
                       {
                           Rock * smallRock1 = createSmallRock ((*it)->getPoint());
                           smallRock1->setDx(((*it)->getVelocity().getDx()) + 3);
                           smallRock1->setDy((*it)->getVelocity().getDy());
                           rocks.push_back(smallRock1);
                           
                           Rock * smallRock2 = createSmallRock ((*it)->getPoint());
                           smallRock2->setDx(((*it)->getVelocity().getDx()) - 3);
                           smallRock2->setDy((*it)->getVelocity().getDy());
                           rocks.push_back(smallRock2);
                       }
                       break;
               }
               break;
           }
         }
       }
    }
}
}



void Game::cleanUpZombies()
{
   vector<Bullet*>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      //Bullet* pBullet = *bulletIt;
      
      if (!(*bulletIt)->isAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         
         delete (*bulletIt);
         *bulletIt = NULL;
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }
   list<Rock*>::iterator rocksIt = rocks.begin();
    for(rocksIt = rocks.begin(); rocksIt != rocks.end();)
    {
       if (!(*rocksIt)->isAlive())
       {
           delete *rocksIt;
           *rocksIt = NULL;
           // remove from list and advance
           rocksIt = rocks.erase(rocksIt);
       }
       else
       {
           ++rocksIt;
       }
    }
}

Rock * Game::createBigRock()
{
    Rock * rock = new BigRock(topLeft, bottomRight);
    return rock;
}

Rock * Game::createMediumRock(Point center)
{
    Rock * rock = new MediumRock(topLeft,  bottomRight, center);
    return rock;
}

Rock * Game::createSmallRock(Point center)
{
    Rock * rock = new SmallRock(topLeft,  bottomRight, center);
    return rock;

}

void Game::startLevel(int level)
{
    ship.setDy(0);
    ship.setDx(0);
    Point p(0,0);
    ship.setPoint(p);
    ship.setAngle(90);
    ship.setAlive(true);
    star.setAlive(true);
    starCaptured = false;
    star.initiateStar(topLeft, bottomRight);
    levelCompleted = false;
    for(int i = 0; i < ((level * 2) + 2);i++)
    {
        rocks.push_back(createBigRock());
    }
}
// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
    return 0.0;
}



/*
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}
*/

