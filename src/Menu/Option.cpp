/*
** EPITECH PROJECT, 2020
** Option
** File description:
** class Option for bomberman
*/

#include <iostream>
#include "Option.hpp"

void Option::checkMouseButton()
{
    for (int i = 0; i < Button_list.size(); i++) {
        if ( _device->getCursorControl()->getPosition().X >= Button_list[i].getPosition().X && _device->getCursorControl()->getPosition().X <= Button_list[i].getPositionWithSize().X
        && _device->getCursorControl()->getPosition().Y >= Button_list[i].getPosition().Y && _device->getCursorControl()->getPosition().Y <= Button_list[i].getPositionWithSize().Y)
            Button_list[i].changeImage(0);
        else
            Button_list[i].changeImage(1);
    }
}

void Option::changeKeyBinding(int player, int command)
{
    irr::EKEY_CODE code = irr::EKEY_CODE::KEY_KEY_A;
    bool _check = false;

    bool *getKey = _event->getKey();
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
        if (getKey[i] == true &&  irr::EKEY_CODE(i) >= irr::EKEY_CODE::KEY_KEY_A && irr::EKEY_CODE(i) <= irr::EKEY_CODE::KEY_KEY_Z) {
            code = irr::EKEY_CODE(i);
            _check == true;
            check[0] = 84;
            check[1] = 84;
        }
        if (getKey[i] == true &&  irr::EKEY_CODE(i) >= irr::EKEY_CODE::KEY_LEFT && irr::EKEY_CODE(i) <= irr::EKEY_CODE::KEY_DOWN) {
            code = irr::EKEY_CODE(i);
            _check == true;
            check[0] = 84;
            check[1] = 84;
        }
    }
    if (command == 0)
        _keybinding->at(player).up = code;
    if (command == 1)
        _keybinding->at(player).down = code;
    if (command == 2)
        _keybinding->at(player).left = code;
    if (command == 3)
        _keybinding->at(player).right = code;
    if (command == 4)
        _keybinding->at(player).put = code;
}

void Option::change_text()
{
    //P1_command
    if (_keybinding->at(0).up == irr::EKEY_CODE::KEY_UP)
        P1_UP->setText(L"UP");
    else if (_keybinding->at(0).up == irr::EKEY_CODE::KEY_DOWN)
        P1_UP->setText(L"DOWN");
    else if (_keybinding->at(0).up == irr::EKEY_CODE::KEY_LEFT)
        P1_UP->setText(L"LEFT");
    else if (_keybinding->at(0).up == irr::EKEY_CODE::KEY_RIGHT)
        P1_UP->setText(L"RIGHT");
    else
        P1_UP->setText(std::wstring(1, static_cast<char>(_keybinding->at(0).up)).c_str());

    if (_keybinding->at(0).down == irr::EKEY_CODE::KEY_UP)
        P1_DOWN->setText(L"UP");
    else if (_keybinding->at(0).down == irr::EKEY_CODE::KEY_DOWN)
        P1_DOWN->setText(L"DOWN");
    else if (_keybinding->at(0).down == irr::EKEY_CODE::KEY_LEFT)
        P1_DOWN->setText(L"LEFT");
    else if (_keybinding->at(0).down == irr::EKEY_CODE::KEY_RIGHT)
        P1_DOWN->setText(L"RIGHT");
    else
        P1_DOWN->setText(std::wstring(1, static_cast<char>(_keybinding->at(0).down)).c_str());
    
    if (_keybinding->at(0).left == irr::EKEY_CODE::KEY_UP)
        P1_LEFT->setText(L"UP");
    else if (_keybinding->at(0).left == irr::EKEY_CODE::KEY_DOWN)
        P1_LEFT->setText(L"DOWN");
    else if (_keybinding->at(0).left == irr::EKEY_CODE::KEY_LEFT)
        P1_LEFT->setText(L"LEFT");
    else if (_keybinding->at(0).left == irr::EKEY_CODE::KEY_RIGHT)
        P1_LEFT->setText(L"RIGHT");
    else
        P1_LEFT->setText(std::wstring(1, static_cast<char>(_keybinding->at(0).left)).c_str());

    if (_keybinding->at(0).right == irr::EKEY_CODE::KEY_UP)
        P1_RIGHT->setText(L"UP");
    else if (_keybinding->at(0).right == irr::EKEY_CODE::KEY_DOWN)
        P1_RIGHT->setText(L"DOWN");
    else if (_keybinding->at(0).right == irr::EKEY_CODE::KEY_LEFT)
        P1_RIGHT->setText(L"LEFT");
    else if (_keybinding->at(0).right == irr::EKEY_CODE::KEY_RIGHT)
        P1_RIGHT->setText(L"RIGHT");
    else
        P1_RIGHT->setText(std::wstring(1, static_cast<char>(_keybinding->at(0).right)).c_str());
    
    if (_keybinding->at(0).put == irr::EKEY_CODE::KEY_UP)
        P1_BOMB->setText(L"UP");
    else if (_keybinding->at(0).put == irr::EKEY_CODE::KEY_DOWN)
        P1_BOMB->setText(L"DOWN");
    else if (_keybinding->at(0).put == irr::EKEY_CODE::KEY_LEFT)
        P1_BOMB->setText(L"LEFT");
    else if (_keybinding->at(0).put == irr::EKEY_CODE::KEY_RIGHT)
        P1_BOMB->setText(L"RIGHT");
    else
        P1_BOMB->setText(std::wstring(1, static_cast<char>(_keybinding->at(0).put)).c_str());

    //P2_command
    if (_keybinding->at(1).up == irr::EKEY_CODE::KEY_UP)
        P2_UP->setText(L"UP");
    else if (_keybinding->at(1).up == irr::EKEY_CODE::KEY_DOWN)
        P2_UP->setText(L"DOWN");
    else if (_keybinding->at(1).up == irr::EKEY_CODE::KEY_LEFT)
        P2_UP->setText(L"LEFT");
    else if (_keybinding->at(1).up == irr::EKEY_CODE::KEY_RIGHT)
        P2_UP->setText(L"RIGHT");
    else
        P2_UP->setText(std::wstring(1, static_cast<char>(_keybinding->at(1).up)).c_str());

    if (_keybinding->at(1).down == irr::EKEY_CODE::KEY_UP)
        P2_DOWN->setText(L"UP");
    else if (_keybinding->at(1).down == irr::EKEY_CODE::KEY_DOWN)
        P2_DOWN->setText(L"DOWN");
    else if (_keybinding->at(1).down == irr::EKEY_CODE::KEY_LEFT)
        P2_DOWN->setText(L"LEFT");
    else if (_keybinding->at(1).down == irr::EKEY_CODE::KEY_RIGHT)
        P2_DOWN->setText(L"RIGHT");
    else
        P2_DOWN->setText(std::wstring(1, static_cast<char>(_keybinding->at(1).down)).c_str());
    
    if (_keybinding->at(1).left == irr::EKEY_CODE::KEY_UP)
        P2_LEFT->setText(L"UP");
    else if (_keybinding->at(1).left == irr::EKEY_CODE::KEY_DOWN)
        P2_LEFT->setText(L"DOWN");
    else if (_keybinding->at(1).left == irr::EKEY_CODE::KEY_LEFT)
        P2_LEFT->setText(L"LEFT");
    else if (_keybinding->at(1).left == irr::EKEY_CODE::KEY_RIGHT)
        P2_LEFT->setText(L"RIGHT");
    else
        P2_LEFT->setText(std::wstring(1, static_cast<char>(_keybinding->at(1).left)).c_str());

    if (_keybinding->at(1).right == irr::EKEY_CODE::KEY_UP)
        P2_RIGHT->setText(L"UP");
    else if (_keybinding->at(1).right == irr::EKEY_CODE::KEY_DOWN)
        P2_RIGHT->setText(L"DOWN");
    else if (_keybinding->at(1).right == irr::EKEY_CODE::KEY_LEFT)
        P2_RIGHT->setText(L"LEFT");
    else if (_keybinding->at(1).right == irr::EKEY_CODE::KEY_RIGHT)
        P2_RIGHT->setText(L"RIGHT");
    else
        P2_RIGHT->setText(std::wstring(1, static_cast<char>(_keybinding->at(1).right)).c_str());
    
    if (_keybinding->at(1).put == irr::EKEY_CODE::KEY_UP)
        P2_BOMB->setText(L"UP");
    else if (_keybinding->at(1).put == irr::EKEY_CODE::KEY_DOWN)
        P2_BOMB->setText(L"DOWN");
    else if (_keybinding->at(1).put == irr::EKEY_CODE::KEY_LEFT)
        P2_BOMB->setText(L"LEFT");
    else if (_keybinding->at(1).put == irr::EKEY_CODE::KEY_RIGHT)
        P2_BOMB->setText(L"RIGHT");
    else
        P2_BOMB->setText(std::wstring(1, static_cast<char>(_keybinding->at(1).put)).c_str());

}

int Option::doScene()
{
    //Key_binding
    if (check[0] != 84 && check[1] != 84)
        changeKeyBinding(check[0], check[1]);

    //Volume
    texte->setText(std::to_wstring(static_cast<int>(_music->getMusicVolume())).c_str());

    //Change_Key_Text
    change_text();

    driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    checkMouseButton();
    driver->draw2DImage(background, irr::core::position2d<irr::s32>(0,0),
                irr::core::rect<irr::s32>(0,0,background->getSize().Width,background->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    guienv->drawAll();
    driver->endScene();
    if (Button_list[0].isclicked() == 1)
        if (_music->getMusicVolume() < 100)
            _music->setMusicVolume((_music->getMusicVolume() + 10));
    if (Button_list[1].isclicked() == 1)
        if (_music->getMusicVolume() > 0)
            _music->setMusicVolume((_music->getMusicVolume() - 10));
    if (Button_list[2].isclicked() == 1)
        return (1);
    if (Button_list[3].isclicked() == 1) {
        check[0] = 0;
        check[1] = 0;
    }
    if (Button_list[4].isclicked() == 1) {
        check[0] = 0;
        check[1] = 1;
    }
    if (Button_list[5].isclicked() == 1) {
        check[0] = 0;
        check[1] = 2;
    }
    if (Button_list[6].isclicked() == 1) {
        check[0] = 0;
        check[1] = 3;
    }
    if (Button_list[7].isclicked() == 1) {
        check[0] = 0;
        check[1] = 4;
    }
    if (Button_list[8].isclicked() == 1) {
        check[0] = 1;
        check[1] = 0;
    }
    if (Button_list[9].isclicked() == 1) {
        check[0] = 1;
        check[1] = 1;
    }
    if (Button_list[10].isclicked() == 1) {
        check[0] = 1;
        check[1] = 2;
    }
    if (Button_list[11].isclicked() == 1) {
        check[0] = 1;
        check[1] = 3;
    }
    if (Button_list[12].isclicked() == 1) {
        check[0] = 1;
        check[1] = 4;
    }
    return (0);
}

Option::Option(irr::IrrlichtDevice *device, MyEventReceiver *event, Music *music, std::vector<Bomberman::Controle> *keybinding) : _device(device), _music(music), _keybinding(keybinding), _event(event)
{
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = smgr->getGUIEnvironment();

    //Check for key_binding
    check[0] = 84;
    check[1] = 84;

    //background
    background = driver->getTexture("../ressources/Option/Option.jpeg");

    //Button
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(500, 250), std::vector<std::string>{"../ressources/Option/+.png", "../ressources/Option/+_pressed.png", "../ressources/Option/+_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(250, 260), std::vector<std::string>{"../ressources/Option/-.png", "../ressources/Option/-_pressed.png", "../ressources/Option/-_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(0, 860), std::vector<std::string>{"../ressources/Option/Back.png", "../ressources/Option/Back.png", "../ressources/Option/Back_clicked.png"}));

    //Player 1 Commande
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(50, 550), std::vector<std::string>{"../ressources/Option/UP.png", "../ressources/Option/UP.png", "../ressources/Option/UP_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(50, 600), std::vector<std::string>{"../ressources/Option/DOWN.png", "../ressources/Option/DOWN.png", "../ressources/Option/DOWN_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(50, 650), std::vector<std::string>{"../ressources/Option/LEFT.png", "../ressources/Option/LEFT.png", "../ressources/Option/LEFT_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(50, 700), std::vector<std::string>{"../ressources/Option/RIGHT.png", "../ressources/Option/RIGHT.png", "../ressources/Option/RIGHT_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(50, 750), std::vector<std::string>{"../ressources/Option/BOMB.png", "../ressources/Option/BOMB.png", "../ressources/Option/BOMB_clicked.png"}));

    //Player 2 Commande
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(550, 550), std::vector<std::string>{"../ressources/Option/UP.png", "../ressources/Option/UP.png", "../ressources/Option/UP_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(550, 600), std::vector<std::string>{"../ressources/Option/DOWN.png", "../ressources/Option/DOWN.png", "../ressources/Option/DOWN_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(550, 650), std::vector<std::string>{"../ressources/Option/LEFT.png", "../ressources/Option/LEFT.png", "../ressources/Option/LEFT_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(550, 700), std::vector<std::string>{"../ressources/Option/RIGHT.png", "../ressources/Option/RIGHT.png", "../ressources/Option/RIGHT_clicked.png"}));
    Button_list.push_back(Button(guienv, driver, irr::core::position2d<irr::s32>(550, 750), std::vector<std::string>{"../ressources/Option/BOMB.png", "../ressources/Option/BOMB.png", "../ressources/Option/BOMB_clicked.png"}));

    texte = guienv->addStaticText(std::to_wstring(static_cast<int>(_music->getMusicVolume())).c_str(),
    irr::core::rect<irr::s32>(380,280, 405,295), true, true, 0, -1, false);
    irr::gui::IGUIFont *font = guienv->getFont("../ressources/font/fonthaettenschweiler.bmp");
    texte->setOverrideFont(font);

    //P1_command;
    P1_UP = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(0).up)).c_str(),
    irr::core::rect<irr::s32>(180,550, 205, 565), true, true, 0, -1, false);
    P1_UP->setOverrideFont(font);

    P1_DOWN = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(0).down)).c_str(),
    irr::core::rect<irr::s32>(180,600, 205, 615), true, true, 0, -1, false);
    P1_DOWN->setOverrideFont(font);

    P1_LEFT = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(0).left)).c_str(),
    irr::core::rect<irr::s32>(180,650, 205, 665), true, true, 0, -1, false);
    P1_LEFT->setOverrideFont(font);

    P1_RIGHT = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(0).right)).c_str(),
    irr::core::rect<irr::s32>(180,700, 205, 715), true, true, 0, -1, false);
    P1_RIGHT->setOverrideFont(font);

    P1_BOMB = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(0).put)).c_str(),
    irr::core::rect<irr::s32>(180, 750, 205, 765), true, true, 0, -1, false);
    P1_BOMB->setOverrideFont(font);

    //P2_command
    P2_UP = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(1).up)).c_str(),
    irr::core::rect<irr::s32>(680,550, 705, 575), true, true, 0, -1, false);
    P2_UP->setOverrideFont(font);

    P2_DOWN = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(1).down)).c_str(),
    irr::core::rect<irr::s32>(680,600, 705, 615), true, true, 0, -1, false);
    P2_DOWN->setOverrideFont(font);

    P2_LEFT = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(1).left)).c_str(),
    irr::core::rect<irr::s32>(680,650, 705, 665), true, true, 0, -1, false);
    P2_LEFT->setOverrideFont(font);

    P2_RIGHT = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(1).right)).c_str(),
    irr::core::rect<irr::s32>(680,700, 705, 715), true, true, 0, -1, false);
    P2_RIGHT->setOverrideFont(font);

    P2_BOMB = guienv->addStaticText(std::wstring(1, static_cast<char>(_keybinding->at(1).put)).c_str(),
    irr::core::rect<irr::s32>(680, 750, 705, 765), true, true, 0, -1, false);
    P2_BOMB->setOverrideFont(font);
}

Option::~Option()
{
    guienv->clear();
}