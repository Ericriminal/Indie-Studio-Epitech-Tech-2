/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Class Arcade
*/

#include "Arcade.hpp"

void Arcade::checkMouseButton()
{
    for (int i = 0; i < Button_list.size(); i++) {
        if ( _device->getCursorControl()->getPosition().X >= Button_list[i].getPosition().X && _device->getCursorControl()->getPosition().X <= Button_list[i].getPositionWithSize().X
        && _device->getCursorControl()->getPosition().Y >= Button_list[i].getPosition().Y && _device->getCursorControl()->getPosition().Y <= Button_list[i].getPositionWithSize().Y)
            Button_list[i].changeImage(0);
        else
            Button_list[i].changeImage(1);
    }
}

int Arcade::doScene()
{
    P1_text->setText(std::wstring(P1_color.begin(), P1_color.end()).c_str());
    P2_text->setText(std::wstring(P2_color.begin(), P2_color.end()).c_str());

    driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    checkMouseButton();
    driver->draw2DImage(background, irr::core::position2d<irr::s32>(0,0),
                irr::core::rect<irr::s32>(0,0,background->getSize().Width,background->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    driver->draw2DImage(title, irr::core::position2d<irr::s32>(160, 80),
                irr::core::rect<irr::s32>(0,0,title->getSize().Width, title->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    driver->draw2DImage(P1, irr::core::position2d<irr::s32>(80, 180),
                irr::core::rect<irr::s32>(0,0,P1->getSize().Width, P1->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    driver->draw2DImage(P2, irr::core::position2d<irr::s32>(480, 180),
                irr::core::rect<irr::s32>(0,0,P2->getSize().Width, P2->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    driver->draw2DImage(launch, irr::core::position2d<irr::s32>(50, 500),
                irr::core::rect<irr::s32>(0,0,launch->getSize().Width, launch->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    guienv->drawAll();
    driver->endScene();
    if (Button_list[0].isclicked() == 1)
        return (1);
    if (Button_list[1].isclicked() == 1) {
        P1_color = "W";
        _color->at(0) = 0;
    }
    if (Button_list[2].isclicked() == 1) {
        P1_color = "B";
        _color->at(0) = 1;
    }
    if (Button_list[3].isclicked() == 1) {
        P1_color = "G";
        _color->at(0) = 2;
    }
    if (Button_list[4].isclicked() == 1) {
        P1_color = "R";
        _color->at(0) = 3;
    }

    if (Button_list[5].isclicked() == 1) {
        P2_color = "W";
        _color->at(1) = 0;
    }
    if (Button_list[6].isclicked() == 1) {
        P2_color = "B";
        _color->at(1) = 1;
    }
    if (Button_list[7].isclicked() == 1) {
        P2_color = "G";
        _color->at(1) = 2;
    }
    if (Button_list[8].isclicked() == 1) {
        P2_color = "R";
        _color->at(1) = 3;
    }

    if (Button_list[9].isclicked() == 1)
        return (5);
    if (Button_list[10].isclicked() == 1)
        return (6);
    return (0);
}

Arcade::Arcade(irr::IrrlichtDevice *device, std::vector<int> *color) : _device(device), _color(color)
{
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = smgr->getGUIEnvironment();

    //background
    background = driver->getTexture("../ressources/Menu/Bomberman_wallpaper.jpeg");

    //title
    title = driver->getTexture("../ressources/Menu/Arcade.png");

    //Launch
    launch = driver->getTexture("../ressources/Menu/LAUNCH_GAME.png");
    //Font
    irr::gui::IGUIFont *font = guienv->getFont("../ressources/font/fonthaettenschweiler.bmp");

    P1 = driver->getTexture("../ressources/Menu/P1.png");
    P1_color = "W";
    P1_text = guienv->addStaticText(std::wstring(P1_color.begin(), P1_color.end()).c_str(),
    irr::core::rect<irr::s32>(125 ,260, 145, 285), true, true, 0, -1, false);
    P1_text->setOverrideFont(font);

    P2 = driver->getTexture("../ressources/Menu/P2.png");
    P2_color = "W";
    P2_text = guienv->addStaticText(std::wstring(P2_color.begin(), P2_color.end()).c_str(),
    irr::core::rect<irr::s32>(520,260, 545, 285), true, true, 0, -1, false);
    P2_text->setOverrideFont(font);

    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(0, 860), std::vector<std::string>{"../ressources/Option/Back.png", "../ressources/Option/Back.png", "../ressources/Option/Back_clicked.png"}));

    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(50, 300), std::vector<std::string>{"../ressources/Menu/W.png", "../ressources/Menu/W_pressed.png", "../ressources/Menu/W_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(150, 300), std::vector<std::string>{"../ressources/Menu/B.png", "../ressources/Menu/B_pressed.png", "../ressources/Menu/B_clicked.png"}));

    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(50, 400), std::vector<std::string>{"../ressources/Menu/G.png", "../ressources/Menu/G_pressed.png", "../ressources/Menu/G_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(150, 400), std::vector<std::string>{"../ressources/Menu/R.png", "../ressources/Menu/R_pressed.png", "../ressources/Menu/R_clicked.png"}));

    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(450, 300), std::vector<std::string>{"../ressources/Menu/W.png", "../ressources/Menu/W_pressed.png", "../ressources/Menu/W_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(550, 300), std::vector<std::string>{"../ressources/Menu/B.png", "../ressources/Menu/B_pressed.png", "../ressources/Menu/B_clicked.png"}));

    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(450, 400), std::vector<std::string>{"../ressources/Menu/G.png", "../ressources/Menu/G_pressed.png", "../ressources/Menu/G_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(550, 400), std::vector<std::string>{"../ressources/Menu/R.png", "../ressources/Menu/R_pressed.png", "../ressources/Menu/R_clicked.png"}));

    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(120, 580), std::vector<std::string>{"../ressources/Menu/P1.png", "../ressources/Menu/P1_pressed.png", "../ressources/Menu/P1_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(520, 580), std::vector<std::string>{"../ressources/Menu/P2.png", "../ressources/Menu/P2_pressed.png", "../ressources/Menu/P2_clicked.png"}));
}

Arcade::~Arcade()
{
    guienv->clear();
}
