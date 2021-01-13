/*
** EPITECH PROJECT, 2020
** Button
** File description:
** class to create button in irrlicht
*/

#include <iostream>
#include "Button.hpp"

void Button::setVisible(int state)
{
    if (state == 0)
        _button->setVisible(false);
    else
        _button->setVisible(true);
}

irr::core::position2d<irr::s32> Button::getPosition()
{
    return (_position);
}

irr::core::position2d<irr::s32> Button::getPositionWithSize()
{
    return (_positionWithSize);
}
int Button::isclicked()
{
    if (_button->isPressed() == true)
        return (1);
    return (0);
}

void Button::changeImage(int state)
{
    if (state == 0)
        _button->setImage(_driver->getTexture(pressed.c_str()));
    else
        _button->setImage(_driver->getTexture(initial.c_str()));
}

Button::Button(irr::gui::IGUIEnvironment* guienv, irr::video::IVideoDriver* driver,
irr::core::position2d<irr::s32> position, std::vector<std::string> path) : _driver(driver), pressed(path[1]), _position(position), initial(path[0])
{
    _button = guienv->addButton(irr::core::rect<irr::s32>(0,0,driver->getTexture(path[1].c_str())->getSize().Width ,driver->getTexture(path[1].c_str())->getSize().Height), 0, -1);
    _button->setUseAlphaChannel(true);
    _button->setDrawBorder(0);
    _button->setImage(driver->getTexture(path[0].c_str()));
    _button->setPressedImage(driver->getTexture(path[2].c_str()));
    _button->setRelativePosition(position);
    _positionWithSize = position;
    _positionWithSize.X = _positionWithSize.X + driver->getTexture(path[0].c_str())->getSize().Width;
    _positionWithSize.Y = _positionWithSize.Y + driver->getTexture(path[0].c_str())->getSize().Height;
}

Button::~Button()
{
}