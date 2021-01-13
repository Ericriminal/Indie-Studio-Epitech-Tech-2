/*
** EPITECH PROJECT, 2020
** Button
** File description:
** class Button for irrlicht
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <string>
#include <vector>
#include <irrlicht.h>

/**
* @class Button
* @brief function to check if cursor is on the button
*/
class Button {
    public:
        Button(irr::gui::IGUIEnvironment* guienv, irr::video::IVideoDriver* driver, irr::core::position2d<irr::s32> position, std::vector<std::string> path);
        ~Button();
        /**
        * @brief change the image of the button
        */
        void changeImage(int state);
        /**
        * @brief check if clicked return 1 / else 0
        */
        int isclicked();
        /**
        * @brief position of the button
        */
        irr::core::position2d<irr::s32> getPosition();
        /**
        * @brief position with the size of the button
        */
        irr::core::position2d<irr::s32> getPositionWithSize();
        /**
        * @brief change the state of the button visible or not
        */
        void setVisible(int state);

    private:
        /**
        * @brief pointer to guienv of irrlicht window
        */
        irr::gui::IGUIEnvironment* guienv;
        /**
        * @brief pointer to guienv of driver window
        */
        irr::video::IVideoDriver* _driver;
        /**
        * @brief pointer to guienv of igui window
        */
        irr::gui::IGUIButton *_button;
        /**
        * @brief path to the button image
        */
        std::string initial;
        /**
        * @brief path to the button image
        */
        std::string pressed;
        /**
        * @brief position of button
        */
        irr::core::position2d<irr::s32> _position;
        /**
        * @brief position with the size of the button
        */
        irr::core::position2d<irr::s32> _positionWithSize;
};

#endif /* !BUTTON_HPP_ */
