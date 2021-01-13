/*
** EPITECH PROJECT, 2020
** Player.hpp
** File description:
** Player
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <irrlicht.h>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include "InputEvent.hpp"
#include "map.hpp"
#include "Music.hpp"
#include "bomb.hpp"
#include "../Controle.hpp"

// struct Controle
// {
//     irr::EKEY_CODE up;
//     irr::EKEY_CODE down;
//     irr::EKEY_CODE left;
//     irr::EKEY_CODE right;
//     irr::EKEY_CODE put;
// };

// enum TEXTURE
// {
//     TEXTURE_WHITE,
//     TEXTURE_BLUE,
//     TEXTURE_GREEN,
//     TEXTURE_RED,
// };

/**
* @class Player
* @brief class which allows access to all player information
*/
class Player
{
private:
    /**
    * @brief music pointer
    */
    Music *music;
    /**
    * @brief number to diffenciate players
    */
    int playerNb;
    /**
    * @brief position x of player
    */
    int posX;
    /**
    * @brief position y of player
    */
    int posY;
    /**
    * @brief Movement key binding
    */
    std::vector<Bomberman::Controle> key;
    Bomberman::Controle Movement;
    /**
    * @brief vector of position
    */
    std::vector<int> playerPos;
    /**
    * @brief number of life
    */
    int life;
    /**
    * @brief speed of player
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
    * @brief number bomb
    */
    int bombNbFix;
    /**
    * @brief progress of adventure
    */
    int progress;
    /**
    * @brief boolean to check if the player is alive
    */
    bool isAlive;
    irr::scene::ISceneManager *_smgr;
    irr::video::IVideoDriver *_driver;
    irr::IrrlichtDevice *_device;
    irr::scene::IAnimatedMesh* _player;
    /**
    * @brief animated mesh of player
    */
    irr::scene::IAnimatedMeshSceneNode *animModel;
    /**
    * @brief boolean if the player is moving
    */
    bool isMoving;
    /**
    * @brief boolean status
    */
    bool test;
    /**
    * @brief Input receiver
    */
    MyEventReceiver receiver;
    /**
    * @brief pointer to map object
    */
    Map *map;
    /**
    * @brief pointer to bomb object
    */
    bombHandler *bombs;
    /**
    * @brief timer clock
    */
    irr::ITimer *clock;
    /**
    * @brief vector of each timer
    */
    std::vector<irr::u32> remainingTime;
    /**
    * @brief pos of bomb
    */
    std::vector<int> pos;
    /**
    * @brief boolean to now if we can put a bomb
    */
    bool AllowBomb;
public:
    Player(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
    irr::scene::ISceneManager *smgr, Map *map, Music *music, bombHandler *bombs,
    irr::ITimer *clock, int playerNb, int posX, int posY, int type,
    std::vector<Bomberman::Controle> _keybinding, bool useSave);
    ~Player();
    /**
    * @param receiver is the object that receive any key input
    * @brief function that allow the movement and the rotation of player
    * @return null
    */
    void move(MyEventReceiver *receiver);
    /**
    * @param none
    * @brief function that get the model of player
    * @return the model of player (irr::scene::IAnimatedMeshSceneNode)
    */
    irr::scene::IAnimatedMeshSceneNode *getAnimeModel() const;
    /**
    * @param none
    * @brief getter of pos x and y
    * @return vector of posX and PosY
    */
    std::vector<int> getPlayerPos();
    /**
    * @param receiver Input receiver
    * @brief function that animate the player
    * @return none
    */
    void moveAnimation(MyEventReceiver *receiver);
    /**
    * @param none
    * @brief function that check if there is collision between player and bonus itme
    * @return none
    */
    void checkBonnus();
    /**
    * @param receiver Input receiver
    * @brief function that put a bomb to the map
    * @return none
    */
    void action(MyEventReceiver *receiver);
    /**
    * @param none
    * @brief function that detect if the player got hit by a bomb
    * @return none
    */
    void checkPlayerHit();
    /**
    * @param none
    * @brief function anime the player when he got hit by a bomb
    * @return none
    */
    void updatePlayerDeathAnimation();
    /**
    * @param none
    * @brief function anime the player when he got hit by a bomb
    * @return none
    */
    int getLife() const;
    /**
    * @param none
    * @brief getter of the nb life
    * @return nb of life (int)
    */
    int getSpeed() const;
    /**
    * @param none
    * @brief getter of the speed
    * @return the speed value (int)
    */
    int getPower() const;
    /**
    * @param none
    * @brief getter of the bomb power
    * @return the bomb power value (int)
    */
    int getNbBomb() const;
    /**
    * @param none
    * @brief getter of the checker if the player is alive
    * @return checker of isalive (bool)
    */
    bool getIsAlive() const;
    /**
    * @param nb new number max of bomb
    * @brief setter of the number max of bomb
    * @return null
    */
    void setNbBomb(int nb);
    /**
    * @param count the index of the vector remainingTime
    * @brief counter of the explosion time increment bomb number after 3 sec
    * @return none
    */
    void waitTime(int count);
    /**
    * @param none
    * @brief function that loop on the vector of all timer (remainingTime)
    * @return null
    */
    void timehandler();
    /**
    * @param none
    * @brief function that set the key binding of the player
    * @return null
    */
    void setMovement();
    /**
    * @param TEXTURE type type of texture we want to load
    * @brief function that allow the player to load a texture
    * @return null
    */
    void setTexture(int type);
    /**
    * @brief use Save file to get stats for player
    * @return vector of ints of all saved data
    */
    void useSave();
    /**
    * @brief save progress in save file
    * @return null
    */
    void saveProgress();
};

#endif
