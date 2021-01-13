/*
** EPITECH PROJECT, 2020
** AScene.hpp
** File description:
** Abstract AScene for bomberman
*/

#ifndef ASCENE_HPP_
#define ASCENE_HPP_

#include "IScene.hpp"

/**
* @class AScene
* @brief Abstract class of SCene
*/
class AScene : public IScene {
    protected:
        /**
        * @brief pointer to ISceneManager of irrlicht
        */
        irr::scene::ISceneManager* smgr;
        /**
        * @brief pointer to IVideoDriver 
        */
        irr::video::IVideoDriver* driver;
};

#endif /* !ASCENE_HPP_ */
