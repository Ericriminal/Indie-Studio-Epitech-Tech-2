/*
** EPITECH PROJECT, 2020
** Adventure.cpp
** File description:
** File for the class Adventure
*/

#include <iostream>
#include "Adventure.hpp"

Adventure::~Adventure()
{
    guienv->clear();
}

void Adventure::checkMouseButton()
{
    for (int i = 0; i < Button_list.size(); i++) {
        if ( _device->getCursorControl()->getPosition().X >= Button_list[i].getPosition().X && _device->getCursorControl()->getPosition().X <= Button_list[i].getPositionWithSize().X
        && _device->getCursorControl()->getPosition().Y >= Button_list[i].getPosition().Y && _device->getCursorControl()->getPosition().Y <= Button_list[i].getPositionWithSize().Y)
            Button_list[i].changeImage(0);
        else
            Button_list[i].changeImage(1);
    }
}

void Adventure::setDefaultSave()
{
    std::ofstream ofs("save.bomberman");
    ofs << "1" << "\n"; // progression
    ofs << "1" << "\n"; // nb bomb
    ofs << "1" << "\n"; // puissance
    ofs << "60" << "\n"; // vitesse
}

int Adventure::doScene()
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
    this->font->draw(irr::core::stringw(progress).c_str(),irr::core::rect<irr::s32>(930,400,0,0),irr::video::SColor(255,255,255,255));
    this->font->draw(" /3",irr::core::rect<irr::s32>(932,400,0,0),irr::video::SColor(255,255,255,255));

    driver->endScene();
    std::ifstream f("save.bomberman");
    if (Button_list[0].isclicked() == 1) {
        this->setDefaultSave(); // NEW GAME
        return (7);
    }
    if (Button_list[1].isclicked() == 1) {
        if (f.good()) // CONTINUE
            return (7);
    }
    if (Button_list[2].isclicked() == 1)
        return (1); // RETURN TO MENU
    return (0);
}

int Adventure::getProgress()
{
    FILE *file;
    if (file = fopen("save.bomberman", "r")) {
       std::ifstream ifs("save.bomberman");
       char read[100];
       ifs.getline(read, 100);

       return std::stoi(read);
    }
    return 1;
}

Adventure::Adventure(irr::IrrlichtDevice *device, MyEventReceiver *receiver) : _receiver(receiver), _device(device)
{
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = smgr->getGUIEnvironment();
    this->font = guienv->getFont("../ressources/font/fonthaettenschweiler.bmp");
    this->progress = this->getProgress();

    //background
    background = driver->getTexture("../ressources/Menu/Bomberman_wallpaper.jpeg");

    //title
    title = driver->getTexture("../ressources/Menu/Title.png");

    //Play_button
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(200, 450), std::vector<std::string>{"../ressources/Menu/New-game.png", "../ressources/Menu/New-game_pressed.png", "../ressources/Menu/New-game_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(700, 450), std::vector<std::string>{"../ressources/Menu/Continue.png", "../ressources/Menu/Continue_pressed.png", "../ressources/Menu/Continue_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(300, 650), std::vector<std::string>{"../ressources/Menu/Back-to-menu.png", "../ressources/Menu/Back-to-menu_pressed.png", "../ressources/Menu/Back-to-menu_clicked.png"}));
}
