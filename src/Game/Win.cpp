/*
** EPITECH PROJECT, 2020
** class Win 
** File description:
** Win class
*/

#include <iostream>
#include "Win.hpp"

int Win::doScene()
{
    driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    driver->draw2DImage(background, irr::core::position2d<irr::s32>(0,0),
                irr::core::rect<irr::s32>(0,0,background->getSize().Width,background->getSize().Height), 0,
                irr::video::SColor(255, 255, 255, 255), true);
    driver->endScene();
    if (_device->getTimer()->getTime() >= waitTime)
        return (1);
    return (0);
}

Win::Win(irr::IrrlichtDevice *device) : _device(device)
{
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();

    //background
    background = driver->getTexture("../ressources/End/Win.jpg");
    waitTime = _device->getTimer()->getTime() + 12000;
}

Win::~Win()
{
}
