/*
** EPITECH PROJECT, 2020
** Adventure
** File description:
** header for the class Adventure
*/

#ifndef ADVENTURE_HPP_
#define ADVENTURE_HPP_

#include <vector>
#include <memory>
#include <fstream>
#include "../Game/InputEvent.hpp"
#include "Button.hpp"
#include "../AScene.hpp"

class Adventure : public AScene {
    public:
        Adventure(irr::IrrlichtDevice *device, MyEventReceiver *receiver);
        int doScene();
        ~Adventure();

    private:
        void checkMouseButton();
        void setDefaultSave();
        int getProgress();
        int progress;
        irr::gui::IGUIFont *font;
        //Guienv for Adventure
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

        // std::ostream& operator<<(std::ostream& os, std::string text)
        //     {
        //         // write out individual members of s with an end of line between each one
        //         os << text << '\n';
        //         return os;
        //     }
};


#endif /* !ASVENTURE_HPP_ */
