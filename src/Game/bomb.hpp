/*
** EPITECH PROJECT, 2020
** bomb.hpp
** File description:
** bomb
*/

#ifndef BOMB_HPP
#define BOMB_HPP

#include <irrlicht.h>
#include <vector>
#include "map.hpp"
#include "Music.hpp"

/**
* @class bombHandler
* @brief class that handle all bombs
*/

enum BOMB_STATUS
{
    NONE,
    EXPLODING,
    EXPLODED
};

class bombHandler {
public:
    bombHandler(irr::scene::ISceneManager *smgr,
        irr::video::IVideoDriver *driver, irr::ITimer *clock, Map *map,
        Music *music);
    ~bombHandler();
    /**
    * @param position of the bomb (x,y)
    * @brief function that add a bomb on the map
    * @return null
    */
    bool addBomb(std::vector<int> bombPos, int force);
    /**
    * @param boolean of the status of the game
    * @brief function to pause the handling of bombs
    * @return null
    */
    void SetPause(bool pause);
    /**
    * @brief function to check bombs
    * @return null
    */
    void checkBomb();
    /**
    * @param none
    * @brief getter of the vector 2d dangerzone
    * @return dangerZone (vector 2d)
    */
    std::vector<std::vector<int>> getDangerZone();
private:
    /**
    * @param bombCounter index of the bomb vector
    * @param actualTime timer of the game
    * @brief wait 3 sec to make explosion
    * @return null
    */
    void checkWaitTime(int bombCounter, irr::u32 actualTime);
    /**
    * @param bombCounter index the bomb vector
    * @brief make the explosion of the bomb and remove explosed wall
    * @return null
    */
    void setBombExplosion(int bombCounter);
    /**
    * @param bombCounter index the bomb vector
    * @brief add explosion particles in the danger zone
    * @return null
    */
    void addParticles(int bombCounter);
    /**
    * @param none
    * @brief remove the particlue after 3 sec
    * @return null
    */
    void removeParticles();
    /**
    * @param actualMap vector2d (int) map of the game
    * @param force the power of the bomb
    * @param startPos position y of the bomb
    * @param incrementor direction of the explosion
    * @param wallExplosedTmp explosed wall in one direction (here Y)
    * @brief get the Y explosion range
    * @return explosion range
    */
    int bombRadiusVertical(std::vector<std::vector<int>> actualMap, int force,
        int startPos, int incrementor, std::vector<int> *wallExplosedTmp);
    /**
    * @param actualMap vecot2d (int) map of the game
    * @param force the power of the bomb
    * @param startPos position x of the bomb
    * @param incrementor direction of the explosion
    * @param wallExplosedTmp explosed wall in one direction (here X)
    * @brief get the X explosion range
    * @return explosion range
    */
    int bombRadiusHorizontal(std::vector<std::vector<int>> actualMap, int force,
        int startPos, int incrementor, std::vector<int> *wallExplosedTmp);
    /**
    * @param actualMap vecot2d (int) map of the game
    * @param direction of explosion
    * @param force the power of the bomb
    * @param wallExplosedTmp explosed wall in one direction
    * @brief get the explosion range
    * @return explosion range
    */
    int getBombRadius(std::vector<std::vector<int>> actualMap, int direction,
        int force, std::vector<int> *allWallDestroyed);
    /**
    * @param force power of explosion
    * @brief set the explosion range in the vector danger zone
    * @return null
    */
    void setDangerZone(int force);
    /**
    * @param none
    * @brief update all the vector 2d bombEffectZone
    * @return null
    */
    void updateDangerZone();
    /**
    * @param dangerType the type of danger (predictable and imminent)
    * @param leftX position horizontal X
    * @param leftY position horizontal Y
    * @param rightX position horizontal X
    * @brief add danger in the axe X
    * @return null
    */
    void addHorizontalDangerZone(int dangerType, int leftX, int leftY,
        int rightX);
    /**
    * @param dangerType the type of danger (predictable and imminent)
    * @param topX position verticale X axe
    * @param topY position verticale Y axe
    * @param downX position verticale Y axe
    * @brief add danger in the axe Y
    * @return null
    */
    void addVerticalDangerZone(int dangerType, int topX, int topY,
        int downY);
    /**
    * @param none
    * @brief function that remove old element of all vector
    * @return null
    */
    void removeOldPointer();
    /**
    * @brief map object
    */
    Map *map;
    irr::scene::ISceneManager* smgr;
    irr::video::IVideoDriver *driver;
    /**
    * @brief music object
    */
    Music *music;
    /**
    * @brief vector to save each bomb position
    */
    std::vector<std::vector<int>> bombPos;
    /**
    * @brief vector to save each bomb effect zone
    */
    std::vector<std::vector<int>> bombEffectZone;
    /**
    * @brief vector to save each wall that has been explosed by a bomb
    */
    std::vector<std::vector<int>> wallExplosed;
    /**
    * @brief vector to have each particle
    */
    std::vector<std::vector<irr::scene::IParticleSystemSceneNode *>> bombParticles;
    /**
    * @brief vector to have explosion zone
    */
    std::vector<std::vector<int>> mapEffectZone;
    /**
    * @brief vector to have each status of the bomb
    */
    std::vector<BOMB_STATUS> bombStatus;
    /**
    * @brief vector to have each timer of bomb
    */
    std::vector<irr::u32> remainingTime;
    /**
    * @brief time clock of bomb
    */
    irr::ITimer *clock;
    /**
    * @brief mesh of  the bomb
    */
    irr::scene::IAnimatedMesh *bombMesh;
    /**
    * @brief vector of each meshnode
    */
    std::vector<irr::scene::IAnimatedMeshSceneNode*> bombMeshSceneNode;
    /**
    * @brief boolean pause
    */
    bool pause;
};

#endif
