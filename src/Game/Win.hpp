/*
** EPITECH PROJECT, 2020
** Win
** File description:
** header for win class
*/

#ifndef WIN_HPP_
#define WIN_HPP_

#include "../AScene.hpp"

class Win : public AScene {
    public:
        Win(irr::IrrlichtDevice *device);
        ~Win();
        int doScene();

    protected:
    private:
        //Background_image
        irr::video::ITexture *background;
        irr::IrrlichtDevice *_device;
        irr::u32 waitTime;
};

#endif /* !WIN_HPP_ */
