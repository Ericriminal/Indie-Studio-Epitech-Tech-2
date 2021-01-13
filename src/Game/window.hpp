/*
** EPITECH PROJECT, 2020
** window.hpp
** File description:
** window
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <irrlicht.h>
#include <mutex>
#include <thread>
#include <iostream>
#include "InputEvent.hpp"
#include "window.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "ground.hpp"
#include "map.hpp"
#include "bomb.hpp"
#include "UI.hpp"
#include "../AScene.hpp"
#include "Music.hpp"
#include "Path.hpp"
#include "../Controle.hpp"

/**
* @class window
* @brief class containing all the logic of the bomberman game
*/
class window : public AScene {
public:
    window(irr::IrrlichtDevice *device, MyEventReceiver *receiver,
        std::vector<Bomberman::Controle> _keybinding, Music *music, int mode,
        std::vector<int> _color);
    ~window();
    /**
    * @brief function to make one loop of the game
    * @return null
    */
    int doScene();

private:
    /**
    * @brief vector of controle
    */
    bool saveMode;
    /**
    * @brief vector of controle
    */
    std::vector<Bomberman::Controle> keybinding;
    /**
    * @brief object creating ground
    */
    ground _ground;
    /**
    * @brief vector of all player object
    */
    std::vector<Player> player;
    /**
    * @brief vector of all ai object
    */
    std::vector<PathFinder> ai;
    /**
    * @brief vector of all thread from ai
    */
    std::vector<std::thread> allThread;
    /**
    * @brief mutex of the thread
    */
    std::mutex mutex;
    /**
    * @brief object creating map
    */
    Map map;
    /**
    * @brief object creating user interface
    */
    UI ui;
    /**
    * @brief object creating the bomb handler
    */
    bombHandler bombs;
    /**
    * @brief vector of destructible wall object
    */
    std::vector<Wall> destructible_wall;
    /**
    * @brief vector of irrlicht object of each player
    */
    std::vector<irr::scene::ISceneNode*> allEntityChar;
    /**
    * @brief object for the music
    */
    Music music;

    /**
    * @brief object to receive keyboard info
    */
    MyEventReceiver *receiver;
    /**
    * @brief main object to use irrlicht
    */
    irr::IrrlichtDevice *device;
    /**
    * @brief object to have the device used by irrlicht
    */
    irr::video::IVideoDriver *driver;
    /**
    * @brief object to create ui based in irrlicht
    */
    irr::gui::IGUIEnvironment *guienv;
    /**
    * @brief object to create any object in a scene
    */
    irr::scene::ISceneManager *smgr;
    /**
    * @brief function to make one loop of the game
    * @return null
    */
    int nbPlayersAlive();
    /**
    * @brief function to make one loop of the game
    * @return null
    */
    int nbAisAlive();
};

#endif
