/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Header for the class Arcade
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <vector>
#include "Button.hpp"
#include "../AScene.hpp"

/**
* @class Arcade
* @brief function to check if cursor is on the button
*/
class Arcade : public AScene {
    public:
        Arcade(irr::IrrlichtDevice *device, std::vector<int> *color);
        int doScene();
        ~Arcade();

    protected:
    private:
        /**
        * @brief function to check if cursor is on the button
        */
        void checkMouseButton();
        /**
        * @brief backgorund_image
        */
        irr::video::ITexture *background;

        /**
        * @brief Title_image
        */
        irr::video::ITexture *title;

        /**
        * @brief Launch_game_image
        */
        irr::video::ITexture *launch;

        /**
        * @brief pointer to guienv class in irrlicht
        */
        irr::gui::IGUIEnvironment* guienv;

        /**
        * @brief Texture for P1_image
        */
        irr::video::ITexture *P1;
        /**
        * @brief String for P1
        */
        std::string P1_color;
        /**
        * @brief Text that show P1 skin
        */
        irr::gui::IGUIStaticText *P1_text;

        /**
        * @brief Texture for P2_image
        */
        irr::video::ITexture *P2;
        /**
        * @brief String for P2
        */
        std::string P2_color;
        /**
        * @brief Text that show P2 skin
        */
        irr::gui::IGUIStaticText *P2_text;

        /**
        * @brief vector of button
        */
        std::vector<Button> Button_list;

        /**
        * @brief pointer to device of irrlicht
        */
        irr::IrrlichtDevice *_device;

        /**
        * @brief Color of player
        */
        std::vector<int> *_color;
};

#endif /* !ARCADE_HPP_ */
