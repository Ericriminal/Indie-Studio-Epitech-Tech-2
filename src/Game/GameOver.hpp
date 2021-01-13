/*
** EPITECH PROJECT, 2020
** GameOver.hpp
** File description:
** GameOver
*/

#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_

#include "../AScene.hpp"

class GameOver : public AScene {
    public:
        GameOver(irr::IrrlichtDevice *device);
        ~GameOver();
        int doScene();

    private:
        //Background_image
        irr::video::ITexture *background;
        irr::IrrlichtDevice *_device;
        irr::u32 waitTime;
};

#endif /* !GAMEOVER_HPP_ */