/*
** EPITECH PROJECT, 2020
** core
** File description:
** core for bomberman
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <irrlicht.h>
#include "AScene.hpp"
#include "Game/InputEvent.hpp"
#include "Controle.hpp"
#include "Game/Music.hpp"

/**
* @class core
* @brief Core class for bomberman
*/
class core {
    private:
        /**
        * @brief pointer to device of irrlicht
        */
        irr::IrrlichtDevice *device;
        /**
        * @brief Pointer to the actual scene show
        */
        std::unique_ptr<IScene> my_scene;
        /**
        * @brief Receiver to device of irrlicht
        */
        MyEventReceiver *receiver;
        /**
        * @brief Music class for the music and sound
        */
        Music music;

        /**
        * @brief fucntion to manage core usage
        */
        int coreManager(int status);
        /**
        * @brief function to change scene
        */
        void changeScene(int scene);
        /**
        * @brief function to go menu
        */
        void goMenu();
        /**
        * @brief function to launch the game solo
        */
        void goGameSolo();
        /**
        * @brief function to launch the adventure
        */
        void goGameAdventure();
        /**
        * @brief function to launch a game on multiplayer
        */
        void goGameMulti();
        /**
        * @brief function to go to option
        */
        void goOption();
        /**
        * @brief function to go to gameover screen
        */
        void goGameOver();
        /**
        * @brief function to go to win screen
        */
        void goWin();

        /**
        * @brief vector that store the key binding of the 2 player
        */
        std::vector<Bomberman::Controle> _keybinding;
        /**
        * @brief function to go to adventure
        */
        void goAdventure();
        /**
        * @brief function to go to arcade mode
        */
        void goArcade();

        /**
        * @brief function that store the skin of the 2 player
        */
        std::vector<int> _color;

    public:
        core();
        /**
        * @brief function to launch the core
        */
        void start();
};

#endif /* !CORE_HPP_ */
