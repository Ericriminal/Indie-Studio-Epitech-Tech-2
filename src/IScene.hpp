/*
** EPITECH PROJECT, 2020
** IScene.hpp
** File description:
** Interface IScene for bomberman
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include <irrlicht.h>
#include <memory>

/**
* @class IScene
* @brief Interface class of SCene
*/
class IScene {
    public:
        virtual ~IScene() = default;
        /**
        * @brief Funtion to print scene
        */
        virtual int doScene() = 0;
};

#endif /* !ISCENE_HPP_ */
