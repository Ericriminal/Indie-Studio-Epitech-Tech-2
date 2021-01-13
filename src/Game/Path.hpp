/*
** EPITECH PROJECT, 2020
** t
** File description:
** t
*/

#ifndef _PATH_
#define _PATH_

#include <irrlicht.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <list>
#include <iostream>
#include <tuple>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include "bomb.hpp"

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UNDEFINED
};

/**
* @class PathFinder
* @brief class which create and manages ais
*/
class PathFinder
{
public:
    PathFinder(irr::IrrlichtDevice *device, bombHandler *bombs
        ,Map *map, int aiNb, int position);
    ~PathFinder();
    /**
    * @param x and y are the coordinates
    * @brief function to tell the ai where to go
    * @return null
    */
    void setPointToGo(int x, int y);
    /**
    * @param x and y are the coordinates
    * @brief function to tell the ai where it is
    * @return null
    */
    void setCurrentPos(int x, int y);
    /**
    * @param map is the game map
    * @brief function to refresh the map
    * @return null
    */
    void setCurrentMapState(const std::vector<std::vector<int>> &map);
    /**
    * @param null
    * @brief function to refresh the map of dangers
    * @return null
    */
    void setDangerMap();
    /**
    * @param mutex
    * @brief function to make the ai take decisions
    * @return true if bot alive false if not
    */
    bool cycle(std::mutex &mutex);
    /**
    * @param boolean
    * @brief function to set the value of looping
    * @return null
    */
    void setLooping(bool looping);
    /**
    * @param null
    * @brief animate the running of the ai
    * @return null
    */
    void setQuit();
    /**
    * @param null
    * @brief function to verify if the ai arrived at it's designated spot
    * @return true if bot arrived false if not
    */
    const bool arrived() const;
    /**
    * @param null
    * @brief function to verify if ai is alive
    * @return true if bot alive false if not
    */
    const bool &alive() const;
    /**
    * @param null
    * @brief function to give the current position of the ai
    * @return position of the ai
    */
    const std::tuple<int, int> imHere() const;
    /**
    * @param mutex
    * @brief function
    * @return thread
    */
    std::thread runThread(std::mutex &mutex);
//    std::thread getThread() const;

private:
    /**
    * @param direction to move to
    * @brief modify coordinates of ai in map
    * @return null
    */
    void modifyPosAccordingToDirection(Direction way);
    /**
    * @param null
    * @brief print the map
    * @return null
    */
    void printMap();
    /**
    * @param mutex
    * @brief decide wether or not to place a bomb
    * @return null
    */
    void breakShit(std::mutex &mutex);
    /**
    * @param mutex
    * @brief place a bomb
    * @return null
    */
    void bombIt(std::mutex &mutex);
    /**
    * @param null
    * @brief check if the ai is stuck (according to it's own logic) in a corner
    * @return null
    */
    void stuck();
    /**
    * @param null
    * @brief set direction to a breakable wall
    * @return null
    */
    void invertedTrump();
    /**
    * @param Direction where to go
    * @brief keep track of the ai's last movements and forbid it to repeat one
    * @return if the current desired movement is allowed
    */

    bool updateFormerPos(Direction way);
    /**
    * @param x and y are the coordinates
    * @brief verify if point is walkable (= 0 or > 5
    * @return success or failure
    */
    bool isPointWalkable(int y, int x);
    /**
    * @param Direction where to go
    * @brief Verify if the current movement is allowed
    * @return success or failure
    */
    bool lastAction(Direction way);
    /**
    * @param x and y are the coordinates
    * @brief verify if ai already went here
    * @return success or failure
    */
    bool checkAction(int x, int y);
    /**
    * @param null
    * @brief verify if a wall nearby is breakable (= 2)
    * @return success or failure
    */
    bool checkBreakable();
   /**
    * @param x and y are the coordinates
    * @brief verify if wall at coordinates is breakable (= 2)
    * @return success or failure
    */
    bool isWallBreakable(int x, int y);
    /**
    * @param null
    * @brief verify if the ai is in danger of death
    * @return success or failure
    */
    bool chuckleImInDanger();
    /**
    * @param null
    * @brief count the number of movement option disponible to ai
    * @return number of possible path
    */

    int countAction();
    /**
    * @param null
    * @brief decide where direction the ai should go
    * @return Direction where to go
    */
    Direction findDirection();
    /**
    * @param x and y are the coordinates
    * @brief verify if player walked into a bonus
    * @return null
    */
    void checkBonnus(int posY, int posX);
    /**
    * @param null
    * @brief animate the running of the ai
    * @return null
    */
    void moveAnimation();
    /**
    * @brief copy of the game map
    */
    std::vector<std::vector<int>> _originalMap;
    /**
    * @brief map of danger, only bombs are represented
    */
    std::vector<std::vector<int>> _dangerMap;
    /**
    * @brief personal map of the ai, it ads dead end to it
    */
    std::vector<std::vector<int>> _map;
    /**
    * @brief list of y coordinate of already walked points
    */
    std::vector<int> YMap;
    /**
    * @brief list of x coordinate of already walked points
    */
    std::vector<int> XMap;
    /**
    * @brief animated mesh of ai
    */
    irr::scene::IAnimatedMesh *aiMesh;
    /**
    * @brief animated mesh of ai
    */
    irr::scene::IAnimatedMeshSceneNode *animModel;
    /**
    * @brief
    */
    irr::IrrlichtDevice *device;
    /**
    * @brief
    */
    irr::core::vector3df pos;
    /**
    * @brief point to bomb object
    */
    bombHandler *bombs;
    /**
    * @brief pointer to map object
    */
    Map *map;
    /**
    * @brief number of ai
    */
    int aiNb;
    /**
    * @brief state of ai
    */
    bool _alive;
    /**
    * @brief state of ai
    */
    bool quit;
    /**
    * @brief ?
    */
    bool looping;
    /**
    * @brief speed of ai
    */
    int speed;
    /**
    * @brief range of exposion
    */
    int bombFire;
    /**
    * @brief number bomb
    */
    int bombNb;
    /**
    * @brief ai x coordinate
    */
    int _x;
    /**
    * @brief ai y coordinate
    */
    int _y;
    /**
    * @brief ai x destination
    */
    int XToGo;
    /**
    * @brief ai y destination
    */
    int YToGo;
    /**
    * @brief ai mod of thinking (0 for running, 1 for destruction, 2 for flight)
    */
    int mod;
    /**
    * @brief is ai moving
    */
    bool isMoving;
    /**
    * @brief locked move
    */
    bool lockMove;
};

#endif /* _PATH_ */
