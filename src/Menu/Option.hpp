/*
** EPITECH PROJECT, 2020
** Option
** File description:
** Option class for Bomberman
*/

#ifndef OPTION_HPP_
#define OPTION_HPP_

#include "Button.hpp"
#include "../Game/UI.hpp"
#include "../Controle.hpp"
#include "../Game/Music.hpp"
#include "../AScene.hpp"
#include "../Game/InputEvent.hpp"

class Option : public AScene {
    public:
        Option(irr::IrrlichtDevice *device, MyEventReceiver *event, Music *music, std::vector<Bomberman::Controle> *_keybinding);
        int doScene();
        ~Option();

    private:
        void checkMouseButton();
        void changeKeyBinding(int player, int command);
        void change_text();

        //Guienv for Menu
        irr::gui::IGUIEnvironment* guienv;

        //Background_image
        irr::video::ITexture *background;

        //Title_image
        irr::video::ITexture *logo;

        //Button
        std::vector<Button> Button_list; 

        //Device
        irr::IrrlichtDevice *_device;

        //Music
        Music *_music;

        //Volume
        irr::gui::IGUIStaticText *texte;

        //Controle
        std::vector<Bomberman::Controle> *_keybinding;

        //Event
        MyEventReceiver *_event;

        //KEY texte
        //Player1
        irr::gui::IGUIStaticText *P1_UP;
        irr::gui::IGUIStaticText *P1_DOWN;
        irr::gui::IGUIStaticText *P1_LEFT;
        irr::gui::IGUIStaticText *P1_RIGHT;
        irr::gui::IGUIStaticText *P1_BOMB;

        //Player2
        irr::gui::IGUIStaticText *P2_UP;
        irr::gui::IGUIStaticText *P2_DOWN;
        irr::gui::IGUIStaticText *P2_LEFT;
        irr::gui::IGUIStaticText *P2_RIGHT;
        irr::gui::IGUIStaticText *P2_BOMB;

        //Checker for key_binding
        int check[2];
};

#endif /* !OPTION_HPP_ */
