/*
** EPITECH PROJECT, 2020
** Wall.hpp
** File description:
** Wall
*/

#ifndef WALL_HPP
#define WALL_HPP
#include <ostream>
#include <iostream>
#include <irrlicht.h>
#include <vector>

/**
* @enum WALL_TYPE
* @brief enum that recognize the type of block
*/
enum WALL_TYPE
{
    BLOCK,
    NORMAL,
    DESTRUCTIBLE,
    SPEED,
    POWER,
    BOMB_NB,
    LIFE
};

/**
* @class Wall
* @brief class which is used to build a single wall
*/
class Wall
{
private:
    int posX;
    int posY;
    bool destructible;
    /**
    * @brief device of the game
    */
    irr::IrrlichtDevice *device;
    /**
    * @brief mesh of cube
    */
    irr::scene::IMeshSceneNode *cube;
    /**
    * @brief mesh of cube
    */
    irr::scene::IMeshSceneNode *bonnus;

    /**
    * @brief selector of player
    */
    irr::scene::ITriangleSelector *selector;
    std::vector<int> wall_pos;
    irr::scene::ISceneNodeAnimator* anim;
public:
    Wall(irr::IrrlichtDevice *device, WALL_TYPE type, int i, int y);
    ~Wall();
    /**
    * @param none
    * @brief function that get the position of the cube
    * @return position of cube (vector3df)
    */
    bool isDestructible() const;
    /**
    * @param none
    * @brief function that get the type of wall
    * @return boolean
    */
    irr::core::vector3df const &getCubePos() const;
    /**
    * @param none
    * @brief function that get the selector of the cube
    * @return the selector of the cube (irr::scene::ITriangleSelector *)
    */
    irr::scene::ITriangleSelector* getSelector();
    /**
    * @param none
    * @brief function that get the pos osition of the wall(cube) in the map of int
    * @return the vecor of position in X and Y of the wall
    */
    std::vector<int> getWallPosition();
    /**
    * @param none
    * @brief function that get the mesh of the cube
    * @return the mesh of cube (irr::scene::IMeshSceneNode *)
    */
    irr::scene::IMeshSceneNode *getcubeMesh() const;
    /**
    * @param none
    * @brief function to remove destructible walls
    * @return nothing
    */
    void removeWall();
    irr::scene::IMeshSceneNode *getBonnusMesh() const;
};
#endif
