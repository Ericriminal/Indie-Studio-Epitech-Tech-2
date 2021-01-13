/*
** EPITECH PROJECT, 2020
** ground.hpp
** File description:
** ground
*/

#ifndef GROUND_HPP
#define GROUND_HPP

#include <irrlicht.h>

/**
* @class ground
* @brief class to create the ground
*/
class ground {
public:
    ground(irr::scene::ISceneManager *smgr, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver);
    ~ground();
    /**
    * @brief function to get a selector of the ground
    * @return irr::scene::ITriangleSelector*
    */
    irr::scene::ITriangleSelector *getSelector();
private:
    irr::scene::IAnimatedMesh* groundMesh;
    irr::scene::IMeshSceneNode* groundNode;
    irr::scene::ISceneManager* smgr;
    irr::scene::IAnimatedMeshSceneNode* groundAnim;
};

#endif
