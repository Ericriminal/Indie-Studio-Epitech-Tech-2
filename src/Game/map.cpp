/*
** EPITECH PROJECT, 2020
** map
** File description:
** map.cpp
*/

#include "map.hpp"
#include <string>

Map::Map(irr::IrrlichtDevice *device, int mode)
{
    this->device = device;
    if (mode == 1 || mode == 2) {
        this->x = 17;
        this->y = 11;
        std::vector<float> bonus_probabilities = {0.5, 0.1, 0.1, 0.1};
        this->game_map = generate_map(x, y, bonus_probabilities);
    }
    else {
        int lvl = this->getProgress();
        if (lvl == 1) {
            this->x = 17;
            this->y = 11;
            this->game_map = loadMap("../ressources/map/map1.txt");
        }
        else if (lvl == 2) {
            this->x = 17;
            this->y = 11;
            this->game_map = loadMap("../ressources/map/map2.txt");
        }
        else if (lvl == 3) {
            this->x = 17;
            this->y = 17;
            this->game_map = loadMap("../ressources/map/map3.txt");
        }
    }
    if (mode == 3)
        this->wallAnimator = {{}};
    else
        for (int count = 0; count < mode; count++)
            this->wallAnimator.push_back({});
}

Map::~Map()
{
}

bool Map::is_protected_place(unsigned short width, unsigned short height, unsigned short x, unsigned short y)
{
    if (y == 1 || y == height - 2) {
        if (x == 1 || x == 2 || x == width - 3 || x == width - 2)
            return (true);
        return (false);
    } else if (y == 2 || y == height - 3) {
        if (x == 1 || x == width - 2)
            return (true);
        return (false);
    }
    return (false);
}

unsigned short Map::generate_block(std::vector<float> &bonus_probabilities)
{
    if (bonus_probabilities.size() == 0)
        return (0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    float first = 0;
    float second = 0;
    float random_number = dis(gen);

    for (int i = 0; i < bonus_probabilities.size(); i++) {
        second += bonus_probabilities[i];

        if (random_number >= first && random_number < second)
            return (i + 2);

        first = second;
    }
    return (0);
}

std::vector<std::vector<int>> Map::generate_map(
    unsigned short width, unsigned short height, std::vector<float> &bonus_probabilities
)
{
    std::vector<std::vector<int>> map;

    for (unsigned short y = 0; y < height; y++) {
        map.push_back({});
        for (unsigned short x = 0; x < width; x++) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                map[y].push_back(1);
            else if (is_protected_place(width, height, x, y))
                map[y].push_back(0);
            else if (x % 2 == 0 && y % 2 == 0)
                map[y].push_back(1);
            else
                map[y].push_back(generate_block(bonus_probabilities));
        }
    }
    return (map);
}

void Map::dump_map(std::vector<std::vector<int>> map)
{
    for (auto &line : map) {
        for (unsigned short bloc : line) {
            std::cout << bloc;
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> Map::loadMap(const char *path_name)
{
    std::ifstream file(path_name);

    if (file.is_open() == false)
        std::cerr << "Can't find the file\n";

    std::vector<std::vector<int>> map;
    std::vector<int> map_line;
    char stock;
    int line = 0;

    while ((stock = file.get()) != EOF) {
        if (stock == '\n') {
            map.push_back(map_line);
            line++;
            map_line.clear();
        }
        else
            map_line.push_back(stock - 48);
    }
    map.push_back(map_line);
    map.pop_back();
    file.close();
    return (map);
}

void Map::collision(Wall wall)
{
    irr::scene::ITriangleSelector *wallSelector = wall.getSelector();

    if (wallSelector) {
        for (int count = 0; count != this->allEntityChar.size(); count++) {
            irr::scene::ISceneNodeAnimator* anim = device->getSceneManager()->createCollisionResponseAnimator(
                    wallSelector, this->allEntityChar[count], irr::core::vector3df(6,6,6), //TODO la taille des collisions
                    irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0));
            wallSelector->drop();
            this->allEntityChar[count]->addAnimator(anim);
            if (wall.isDestructible())
                this->wallAnimator[count].push_back(anim);
        }
    }
}

void Map::createMap(std::vector<std::vector<int>> game_map,
    std::vector<irr::scene::ISceneNode*> allEntityChar)
{
    this->allEntityChar = allEntityChar;
    for (int y = 0; y < game_map.size(); y++) {
        for (int x = 0; x < game_map[y].size(); x++) {
            Wall test(device, WALL_TYPE::BLOCK, y, x);
            if (game_map[y][x] == WALL_TYPE::NORMAL) {
                Wall test1(device, WALL_TYPE::NORMAL, y, x);
                collision(test1);
            }
            if (game_map[y][x] == WALL_TYPE::DESTRUCTIBLE) {
                Wall test2(device, WALL_TYPE::DESTRUCTIBLE, y, x);
                collision(test2);
                this->destructible_wall.push_back(test2);
            }
            if (game_map[y][x] == WALL_TYPE::SPEED) {
                Wall test3(device, WALL_TYPE::SPEED, y, x);
                collision(test3);
                this->destructible_wall.push_back(test3);
                this->bonnus.push_back(test3);
            }
            if (game_map[y][x] == WALL_TYPE::POWER) {
                Wall test4(device, WALL_TYPE::POWER, y, x);
                collision(test4);
                this->destructible_wall.push_back(test4);
                this->bonnus.push_back(test4);
            }
            if (game_map[y][x] == WALL_TYPE::BOMB_NB) {
                Wall test5(device, WALL_TYPE::BOMB_NB, y, x);
                collision(test5);
                this->destructible_wall.push_back(test5);
                this->bonnus.push_back(test5);

            }
        }
    }
    //dump_map(this->game_map);
    y = game_map.size();
    x = game_map[0].size();
}

std::vector<std::vector<int>> Map::getMap()
{
    return (this->game_map);
}

std::vector<Wall> Map::getDestructibleWall() const
{
    return (this->destructible_wall);
}

std::vector<Wall> Map::getBonnus() const
{
    return (this->bonnus);
}

void Map::removeWall(int wallX, int wallY)
{
    for (int count = 0; count != this->destructible_wall.size(); count++) {
        if (this->destructible_wall[count].getWallPosition().front() == wallX
        && this->destructible_wall[count].getWallPosition().back() == wallY) {
            for (int entityCount = 0; entityCount < this->allEntityChar.size(); entityCount++) {
                this->allEntityChar[entityCount]->removeAnimator(this->wallAnimator[entityCount][count]);
                this->wallAnimator[entityCount].erase(this->wallAnimator[entityCount].begin() + count);
            }
            this->destructible_wall[count].getcubeMesh()->remove();
            if (this->game_map[wallX][wallY] == 2)
                this->game_map[wallX][wallY] = 0;
            else if (this->game_map[wallX][wallY] == 3)
                this->game_map[wallX][wallY] = 6;
            else if (this->game_map[wallX][wallY] == 4)
                this->game_map[wallX][wallY] = 7;
            else if (this->game_map[wallX][wallY] == 5)
                this->game_map[wallX][wallY] = 8;
            this->destructible_wall.erase(this->destructible_wall.begin() + count);
            return;
        }
    }
}

void Map::setMap(int y, int x, int block)
{
    this->game_map[y][x] = block;
}

void Map::removeMeshBonnus(int count)
{
    this->bonnus[count].getBonnusMesh()->remove();
    this->bonnus.erase(this->bonnus.begin() + count);
}

std::vector<int> Map::getMapSize()
{
    std::vector<int> size;
    size.push_back(x);
    size.push_back(y);
    return (size);
}

int Map::getProgress()
{
    std::ifstream ifs("save.bomberman");
    char read[100];

    ifs.getline(read, 100);
    return std::stoi(read);
}
