/*
** EPITECH PROJECT, 2020
** Wall
** File description:
** Wall.cpp
*/

#include "Wall.hpp"

Wall::Wall(irr::IrrlichtDevice *device, WALL_TYPE type, int y, int x)
{
    this->posX = x;
    this->posY = y;
    if (type == WALL_TYPE::BLOCK) {
        // Z = X / X = Y
        this->cube = device->getSceneManager()->addCubeSceneNode(20);
        cube->setPosition(irr::core::vector3df((y*20),-9,(x*20)));
        // //cube->setRotation(irr::core::vector3df(200,200,200));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        cube->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        cube->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/wall.bmp"));
        this->destructible = false;
    }
    else if (type == WALL_TYPE::NORMAL) {
        // Z = X / X = Y
        this->cube = device->getSceneManager()->addCubeSceneNode(20);
        cube->setPosition(irr::core::vector3df((y*20),10,(x*20)));
        // //cube->setRotation(irr::core::vector3df(200,200,200));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        cube->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        cube->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/stone.png"));
        this->destructible = false;
    }
    else if (type == WALL_TYPE::DESTRUCTIBLE) {
        this->cube = device->getSceneManager()->addCubeSceneNode(20);
        cube->setPosition(irr::core::vector3df((y*20),10,(x*20)));
        // //cube->setRotation(irr::core::vector3df(200,200,200));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        cube->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        cube->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/bedrock.png"));
        this->destructible = true;
    }
    else if (type == WALL_TYPE::SPEED) {
        this->bonnus = device->getSceneManager()->addCubeSceneNode(10);
        bonnus->setPosition(irr::core::vector3df((y*20),10,(x*20)));
        bonnus->setRotation(irr::core::vector3df(200,200,200));
        bonnus->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        bonnus->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        bonnus->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/diamond.png"));

        this->cube = device->getSceneManager()->addCubeSceneNode(20);
        cube->setPosition(irr::core::vector3df((y*20),10,(x*20)));
        //cube->setRotation(irr::core::vector3df(200,200,200));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        cube->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        cube->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/bedrock.png"));
        this->destructible = true;
    }
    else if (type == WALL_TYPE::POWER) {
        this->bonnus = device->getSceneManager()->addCubeSceneNode(10);
        bonnus->setPosition(irr::core::vector3df((y*20),10,(x*20)));
        bonnus->setRotation(irr::core::vector3df(200,200,200));
        bonnus->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        bonnus->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        bonnus->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/redstone.png"));

        this->cube = device->getSceneManager()->addCubeSceneNode(20);
        cube->setPosition(irr::core::vector3df((y*20),10,(x*20)));
        //cube->setRotation(irr::core::vector3df(200,200,200));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        cube->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        cube->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/bedrock.png"));
        this->destructible = true;
    }
    else if (type == WALL_TYPE::BOMB_NB) {
        this->bonnus = device->getSceneManager()->addCubeSceneNode(10);
        bonnus->setPosition(irr::core::vector3df((y*20),10,(x*20)));
        bonnus->setRotation(irr::core::vector3df(200,200,200));
        bonnus->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        bonnus->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        bonnus->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/gold.png"));

        this->cube = device->getSceneManager()->addCubeSceneNode(20);
        cube->setPosition(irr::core::vector3df((y*20),10,(x*20)));
        //cube->setRotation(irr::core::vector3df(200,200,200));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        cube->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
        cube->setMaterialTexture(0, device->getVideoDriver()->getTexture("../ressources/images/bedrock.png"));
        this->destructible = true;
    }
    this->selector = device->getSceneManager()->createOctreeTriangleSelector(cube->getMesh(), cube, 128);
    wall_pos.push_back(this->posX);
    wall_pos.push_back(this->posY);
}

Wall::~Wall()
{
}

irr::core::vector3df const	&Wall::getCubePos() const
{
    return (this->cube->getPosition());
}

irr::scene::ITriangleSelector* Wall::getSelector()
{
    return (this->selector);
}

std::vector<int> Wall::getWallPosition()
{
    this->wall_pos[1] = this->posX;
    this->wall_pos[0] = this->posY;

    return (wall_pos);
}

irr::scene::IMeshSceneNode *Wall::getcubeMesh() const
{
    return (this->cube);
}

irr::scene::IMeshSceneNode *Wall::getBonnusMesh() const
{
    //std::cout << "here" << std::endl;
    return (this->bonnus);
}

bool Wall::isDestructible() const
{
    return this->destructible;
}
