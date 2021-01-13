/*
** EPITECH PROJECT, 2020
** Menu.cpp
** File description:
** File for the class Menu
*/

#include "Menu.hpp"

Menu::~Menu()
{
    guienv->clear();
}

void Menu::checkMouseButton()
{
    for (int i = 0; i < Button_list.size(); i++) {
        if ( _device->getCursorControl()->getPosition().X >= Button_list[i].getPosition().X && _device->getCursorControl()->getPosition().X <= Button_list[i].getPositionWithSize().X
        && _device->getCursorControl()->getPosition().Y >= Button_list[i].getPosition().Y && _device->getCursorControl()->getPosition().Y <= Button_list[i].getPositionWithSize().Y)
            Button_list[i].changeImage(0);
        else
            Button_list[i].changeImage(1);
    }
}

int Menu::doScene()
{
    driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    checkMouseButton();
    driver->draw2DImage(background, irr::core::position2d<irr::s32>(0,0),
                irr::core::rect<irr::s32>(0,0,background->getSize().Width,background->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    driver->draw2DImage(title, irr::core::position2d<irr::s32>(160, 80),
                irr::core::rect<irr::s32>(0,0,title->getSize().Width, title->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    guienv->drawAll();
    driver->endScene();
    if (Button_list[0].isclicked() == 1) {
        Button_list[3].setVisible(1);
        Button_list[4].setVisible(1);
    }
    if (Button_list[1].isclicked() == 1)
        return (2);
    if (Button_list[2].isclicked() == 1)
        return (84);
    if (Button_list[3].isclicked() == 1)
        return (4);
    if (Button_list[4].isclicked() == 1)
        return (3);
    return (0);
}

Menu::Menu(irr::IrrlichtDevice *device, MyEventReceiver *receiver) : _receiver(receiver), _device(device)
{
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = smgr->getGUIEnvironment();

    //background
    background = driver->getTexture("../ressources/Menu/Bomberman_wallpaper.jpeg");

    //title
    title = driver->getTexture("../ressources/Menu/Title.png");

    //Play_button
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(270, 350), std::vector<std::string>{"../ressources/Menu/Play.png", "../ressources/Menu/Play_pressed.png", "../ressources/Menu/Play_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(230, 500), std::vector<std::string>{"../ressources/Menu/Option.png", "../ressources/Menu/Option_pressed.png", "../ressources/Menu/Option_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(280, 650), std::vector<std::string>{"../ressources/Menu/Exit.png", "../ressources/Menu/Exit_pressed.png", "../ressources/Menu/Exit_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(520, 300), std::vector<std::string>{"../ressources/Menu/Adventure.png", "../ressources/Menu/Adventure_pressed.png", "../ressources/Menu/Adventure_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(520, 400), std::vector<std::string>{"../ressources/Menu/Arcade.png", "../ressources/Menu/Arcade_pressed.png", "../ressources/Menu/Arcade_clicked.png"}));

    Button_list[3].setVisible(0);
    Button_list[4].setVisible(0);
}
