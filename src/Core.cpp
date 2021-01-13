/*
** EPITECH PROJECT, 2020
** core
** File description:
** core for bombermam
*/

#include <iostream>
#include "Core.hpp"
#include "Game/Win.hpp"
#include "Game/GameOver.hpp"
#include "Menu/Arcade.hpp"
#include "Menu/Option.hpp"
#include "Menu/Menu.hpp"
#include "Menu/Adventure.hpp"
#include "Game/window.hpp"
#include "Menu/Adventure.hpp"

core::core()
{
    this->receiver = new MyEventReceiver();
    device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, true, receiver);
    music.loadMusic("../ressources/Music/test.ogg");
    music.setMusicVolume(50.0);
    music.playMusic();
    _keybinding.push_back(Bomberman::Controle { irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D, irr::KEY_KEY_B });
    _keybinding.push_back(Bomberman::Controle { irr::KEY_UP, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_RIGHT, irr::KEY_KEY_P });
    _color.push_back({0});
    _color.push_back({0});
}

void core ::goOption()
{
    my_scene.reset();
    my_scene = std::make_unique<Option>(device, receiver, &music, &_keybinding);
}

void core::goArcade()
{
    my_scene.reset();
    my_scene = std::make_unique<Arcade>(device, &_color);
}

void core::goMenu()
{
    my_scene.reset();
    music.loadMusic("../ressources/Music/test.ogg");
    music.playMusic();
    my_scene = std::make_unique<Menu>(device, receiver);
}

void core::goGameSolo()
{
    my_scene.reset();
    music.loadMusic("../ressources/Music/Battle.ogg");
    music.playMusic();
    my_scene = std::make_unique<window>(device, receiver, _keybinding, &music, 1, _color);
}

void core::goGameMulti()
{
    my_scene.reset();
    music.loadMusic("../ressources/Music/Battle.ogg");
    music.playMusic();
    my_scene = std::make_unique<window>(device, receiver, _keybinding, &music, 2, _color);
}

void core::goGameAdventure()
{
    my_scene.reset();
    music.loadMusic("../ressources/Music/Battle.ogg");
    music.playMusic();
    my_scene = std::make_unique<window>(device, receiver, _keybinding, &music, 3, _color);
}

void core::goAdventure()
{
    my_scene.reset();
    my_scene = std::make_unique<Adventure>(device, receiver);
}

void core::goGameOver()
{
    my_scene.reset();
    music.loadMusic("../ressources/Music/Gameover.ogg");
    music.playMusic();
    my_scene = std::make_unique<GameOver>(device);
}

void core::goWin()
{
    my_scene.reset();
    music.loadMusic("../ressources/Music/Win.ogg");
    music.playMusic();
    my_scene = std::make_unique<Win>(device);
}

void core::changeScene(int scene)
{
    if (scene == 1)
        goMenu();
    if (scene == 2)
        goOption();
    if (scene == 4)
        goAdventure();
    if (scene == 3)
        goArcade();
    if (scene == 5)
        goGameSolo();
    if (scene == 6)
        goGameMulti();
    if (scene == 7)
        goGameAdventure();
    if (scene == 8)
        goGameOver();
    if (scene == 9)
        goWin();
}

int core::coreManager(int status)
{
    if (status == 84)
        return (84);
    if (status != 0)
        changeScene(status);
    return (0);
}

void core::start()
{
    my_scene = std::make_unique<Menu>(device, receiver);

    while (device->run()) {
        if (coreManager(my_scene->doScene()) == 84)
            break;
    }
    my_scene.reset();
    device->drop();
}
