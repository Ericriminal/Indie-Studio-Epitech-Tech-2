/*
** EPITECH PROJECT, 2020
** UI.cpp
** File description:
** UI
*/

#include "UI.hpp"

UI::UI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr, irr::gui::IGUIEnvironment *guienv)
{
    this->device = device;
    this->driver = driver;
    this->smgr = smgr;
    this->guienv = guienv;
    this->bomb = load2dImage(this->bomb, "../ressources/images/Bombupsprite.PNG.png");
    this->fire = load2dImage(this->fire, "../ressources/images/Fireupsprite.PNG.png");
    this->skate = load2dImage(this->skate, "../ressources/images/Skatesprite.PNG.png");
}

UI::~UI()
{
}

void UI::loadFont()
{
    this->font = guienv->getBuiltInFont();
}

void UI::loadFont(const irr::io::path &filename)
{
    this->font = guienv->getFont(filename);
}

irr::video::ITexture *UI::load2dImage(irr::video::ITexture* images, const irr::io::path &filename)
{
    return (images = driver->getTexture(filename));
}

void UI::draw2DImage(irr::video::ITexture* images, int posX, int posY, int scale)
{
    //driver->draw2DImage(images, irr::core::rect<irr::s32>(posX, posY, scale, scale), irr::core::rect<irr::s32>(0, 0, 300, 300), 0, 0, true);
    driver->draw2DImage(images, irr::core::position2d<irr::s32>(posX,posY), irr::core::rect<irr::s32>(0,0,scale,scale),0, irr::video::SColor (255,255,255,255), true);
}

void UI::printPlayerInfo(Player *player, int posX, int posY)
{
    this->font->draw("Player life: ",irr::core::rect<irr::s32>(posX,posY+10,0,0),irr::video::SColor(255,250,250,250));
    this->font->draw(irr::core::stringw(player->getLife()).c_str(),irr::core::rect<irr::s32>(posX+80,posY+10,0,0),irr::video::SColor(255,250,250,250));
    draw2DImage(this->fire, posX-50, posY+50, 32);
    this->font->draw("Player power: ",irr::core::rect<irr::s32>(posX,posY+60,0,0),irr::video::SColor(255,250,250,250));
    this->font->draw(irr::core::stringw(player->getPower()).c_str(),irr::core::rect<irr::s32>(posX+80,posY+60,0,0),irr::video::SColor(255,250,250,250));
    draw2DImage(this->skate, posX-50, posY+100, 32);
    this->font->draw("Player speed: ",irr::core::rect<irr::s32>(posX,posY+110,0,0),irr::video::SColor(255,250,250,250));
    this->font->draw(irr::core::stringw(player->getSpeed()).c_str(),irr::core::rect<irr::s32>(posX+80,posY+110,0,0),irr::video::SColor(255,250,250,250));
    draw2DImage(this->bomb, posX-50, posY+150, 32);
    this->font->draw("Player nb of bomb: ",irr::core::rect<irr::s32>(posX,posY+160,0,0),irr::video::SColor(255,250,250,250));
    this->font->draw(irr::core::stringw(player->getNbBomb()).c_str(),irr::core::rect<irr::s32>(posX+100,posY+160,0,0),irr::video::SColor(255,250,250,250));

}
