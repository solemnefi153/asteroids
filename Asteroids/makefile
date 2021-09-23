###############################################################
# Program:
#     Project 13, Asteroids
#     Brother Comeau, CS165
# Author:
#     Nefi Aguilar
# Summary:
#   This program will run an asteroids game using OPEN GL and GLUT libraries.
# Above and Beyond
#   Changed the life span of the bullets to 80 frames.
#   Changed the size of the screen to 500 each side
#   Changed the default speed of the the bullets to 10
#   Bullets will be continually shoot while pressing space
#   If all asteroids are distroid the user can advance to the next level or quit the game
#   If the ship dies, the user can reset or quit the game
#   Highest scores are saved in a file called highest_score.txt
#   To make the game more challenging... I added an object (blue star) that needs to be captured by the ship. To pass a level the ship needs to capture the star and destroy all asteroids. If the user shoots the star, it will lose the game.

###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o ship.o star.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o star.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rocks.o        Contains all of the Rock classes
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

driver.o: driver.cpp game.h uiInteract.h
	g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rocks.h ship.h star.h
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bullet.cpp

rocks.o: rocks.cpp rocks.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c rocks.cpp

star.o: star.cpp star.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c star.cpp


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
