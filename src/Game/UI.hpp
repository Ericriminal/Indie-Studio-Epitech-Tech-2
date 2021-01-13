/*
** EPITECH PROJECT, 2020
** UI.hpp
** File description:
** UI
*/

#ifndef UI_HPP
#define UI_HPP

#include <irrlicht.h>
#include <vector>
#include "Player.hpp"

/**
* @class UI
* @brief class that print stat of player
*/
class UI
{
private:
    irr::IrrlichtDevice *device;
    irr::video::IVideoDriver *driver;
    irr::scene::ISceneManager *smgr;
    irr::gui::IGUIEnvironment *guienv;
    /**
    * @brief font of text
    */
    irr::gui::IGUIFont *font;
    /**
    * @brief texture of bomb image
    */
    irr::video::ITexture *bomb;
    /**
    * @brief  texture of fire image
    */
    irr::video::ITexture *fire;
    /**
    * @brief  texture of skate image
    */
    irr::video::ITexture *skate;

public:
    UI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr, irr::gui::IGUIEnvironment *guienv);
    ~UI();
    /**
    * @param none
    * @brief function that load default font
    * @return null
    */
    void loadFont();
    /**
    * @param filename font path
    * @brief function that load a font
    * @return null
    */
    void loadFont(const irr::io::path &filename);
    /**
    * @param image texture that we want to load
    * @param filename path of the image
    * @brief function that load a 2d image
    * @return image (ITexture)
    */
    irr::video::ITexture *load2dImage(irr::video::ITexture* images, const irr::io::path &filename);
    /**
    * @param image to display
    * @param posx position X
    * @param posy position Y
    * @param scale size
    * @brief function that draw image
    * @return null
    */
    void draw2DImage(irr::video::ITexture* images, int posX, int posY, int scale);
    /**
    * @param player pointer to player object
    * @param posX position X of the screen
    * @param posY position Y of the screen
    * @brief function that print info of player
    * @return null
    */
    void printPlayerInfo(Player *player, int posX, int posY);
};

#endif
