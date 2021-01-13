/*
** EPITECH PROJECT, 2020
** map
** File description:
** map.hpp
*/

#ifndef MAP_HPP
#define MAP_HPP
#include <ostream>
#include <iostream>
#include <irrlicht.h>
#include <fstream>
#include <vector>
#include <random>
#include "Wall.hpp"

/**
* @class Map
* @brief class which is used to build a map
*/
class Map
{
private:
    int x;
    int y;
    /**
    * @brief device of the game
    */
    irr::IrrlichtDevice *device;
    /**
    * @brief the map of the game
    */
    std::vector<std::vector<int>> game_map;
    /**
    * @brief the procedural generatated map of the game
    */
    std::vector<std::vector<int>> new_game_map;
    /**
    * @brief the vector of destructible wall
    */
    std::vector<Wall> destructible_wall;
    /**
    * @brief the vector of bonus
    */
    std::vector<Wall> bonnus;
    /**
    * @brief the vector of every players
    */
    std::vector<irr::scene::ISceneNode*> allEntityChar;
    /**
    * @brief the vector of every collisison
    */
    std::vector<std::vector<irr::scene::ISceneNodeAnimator*>> wallAnimator;
public:
    //Map(irr::IrrlichtDevice *device);
    Map(irr::IrrlichtDevice *device, int lvl);

    ~Map();
    /**
    * @brief
    *
    * @param width the map's width
    * @param height the map's height
    * @param x the value of the abscissa X for a block
    * @param y the value of the abscissa Y for a block
    * @return true if the block is a protected place
    * @return false if the block isn't a protected place
    */
    bool is_protected_place(unsigned short width, unsigned short height, unsigned short x, unsigned short y);
    /**
    * @brief generate a block id using given probabilities list
    *
    * @param bonus_probabilities list of probabilities for bonus blocks (each must be between 0 and 1)
    * @return unsigned short the generated block id
    */
    unsigned short generate_block(std::vector<float> &bonus_probabilities);
    /**
    * @brief generate a random map
    *
    * @param width map width
    * @param height map height
    * @param bonus_probabilities list of probabilities for bonus blocks (each must be between 0 and 1)
    * @return std::vector<std::vector<unsigned short>>
    */
    std::vector<std::vector<int>> generate_map(
        unsigned short width, unsigned short height, std::vector<float> &bonus_probabilities
    );
    /**
    * @brief dump map in console using block's ids
    *
    * @param map the two-dimensionnal vector representing the map
    */
    void dump_map(std::vector<std::vector<int>> map);
    /**
    * @param path_name the path of a file(txt)
    * @brief function that fill a 2d vector of int
    * @return the game map (std::vector<std::vector<int>>)
    */
    std::vector<std::vector<int>> loadMap(const char *path_name);
    /**
    * @param game_map the map in vector 2d(int)
    * @param allEntityChar the player to prevend the collision
    * @brief function that create the map
    * @return a vector of destructible wall
    */
    void createMap(std::vector<std::vector<int>> game_map, std::vector<irr::scene::ISceneNode*> allEntityChar);
    /**
    * @param wall the wall that we want to make collision
    * @brief function that will make a collision between the slector(wall_selector) and object(player_node)
    * @return null
    */
    void collision(Wall wall);
    /**
    * @param none
    * @brief getter of the vector map
    * @return map vector (int)
    */
    std::vector<std::vector<int>> getMap();
    /**
    * @param none
    * @brief getter of the vector destructible_wall
    * @return destructible wall vector (int)
    */
    std::vector<Wall> getDestructibleWall() const;
    /**
    * @param none
    * @brief getter of the vector bonus
    * @return bonus vector (Wall)
    */
    std::vector<Wall> getBonnus() const;
    /**
    * @param wallX size x of map
    * @param wallY size y of map
    * @brief function that remove wall after explosion of the bomb
    * @return null
    */
    void removeWall(int wallX, int wallY);
    /**
    * @param none
    * @brief get the size of the current map
    * @return vector of length and width (int)
    */
    std::vector<int> getMapSize();
    /**
    * @param x position x in the map
    * @param y position y in the map
    * @param block new block to put int the map
    * @brief function that will set a new block of the position x and y
    * @return null
    */
    void setMap(int x, int y, int block);
    /**
    * @param count used to be the index of the bonus vector
    * @brief function that remove the bonus after collision with player
    * @return null
    */
    void removeMeshBonnus(int count);
    /**
    * @brief get progress from save
    * @return int of actual progress
    */
    int getProgress();
};

#endif
