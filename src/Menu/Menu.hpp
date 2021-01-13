/*
** EPITECH PROJECT, 2020
** Menu
** File description:
** header for the class Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <vector>
#include <memory>
#include "../Game/InputEvent.hpp"
#include "Button.hpp"
#include "../AScene.hpp"

class Menu : public AScene {
    public:
        Menu(irr::IrrlichtDevice *device, MyEventReceiver *receiver);
        int doScene();
        ~Menu();

    private:
        void checkMouseButton();

        //Guienv for Menu
        irr::gui::IGUIEnvironment* guienv;

        //Background_image
        irr::video::ITexture *background;

        //Title_image
        irr::video::ITexture *title;

        //Button
        std::vector<Button> Button_list; 

        //EventReceiver
        MyEventReceiver *_receiver;

        //Device
        irr::IrrlichtDevice *_device;
};

#endif /* !MENU_HPP_ */
