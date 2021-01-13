/*
** EPITECH PROJECT, 2020
** t
** File description:
** t
*/

#include "Path.hpp"

// constructor
PathFinder::PathFinder(irr::IrrlichtDevice *device, bombHandler *bombs
    ,Map *map, int aiNb, int position)
{
    this->device = device;
    this->bombs = bombs;
    this->map = map;
    this->aiNb = aiNb;
    this->looping = true;
    this->isMoving = false;
    this->lockMove = false;
    this->bombFire = 2;
    this->bombNb = 1;
    this->speed = 60;
    this->quit = false;
    mod = 0;
    _alive = true;
    this->aiMesh = this->device->getSceneManager()->getMesh("../ressources/images/character/ninja.b3d");
    this->animModel = this->device->getSceneManager()->addAnimatedMeshSceneNode(this->aiMesh);
    this->animModel->setMaterialTexture(0, this->device->getVideoDriver()->getTexture("../ressources/images/character/nskinbl.jpg"));
    this->animModel->setScale(irr::core::vector3df(3.f,3.f,3.f));
    this->animModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->animModel->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
    if (position == 2) {
        this->_x = map->getMapSize()[0]-2;
        this->_y = 1;
        this->animModel->setPosition(irr::core::vector3df(20 * this->_y,1,20 * this->_x));
    }
    else if (position == 3) {
        this->_x = 1;
        this->_y = map->getMapSize()[1]-2;
        this->animModel->setPosition(irr::core::vector3df(20 * this->_y,1,20 * this->_x));
    }
    else if (position == 4) {
        this->_x = map->getMapSize()[0]-2;
        this->_y = map->getMapSize()[1]-2;
        this->animModel->setPosition(irr::core::vector3df(20 * this->_y,1,20 * this->_x));
    }
    this->pos = this->animModel->getPosition();
}

//destructor
PathFinder::~PathFinder()
{
}

//setDirection si il court pas il veut juste casser des murs
void PathFinder::setPointToGo(int x, int y)
{
    if (mod != 2)
        invertedTrump();
    else {
        XToGo = x;
        YToGo = y;
    }
}

//setPos set la position actuelle du bot
void PathFinder::setCurrentPos(int x, int y)
{
    _x = x;
    _y = y;
}

//Etat actuel de la map
void PathFinder::setCurrentMapState(const std::vector<std::vector<int>> &map)
{
    if (_originalMap.empty()) {
        _originalMap = map;
        _map = map;
    } else
        for (int m = 0; m < map.size(); m++)
            for (int i = 0; i < map.size(); i++)
                if ((map[m][i] == 0 || (map[m][i] >= 6 && map[m][i] <= 8)) &&( _originalMap[m][i] >= 2 && _originalMap[m][i] <= 5)) {
                    _originalMap = map;
                    _map = map;
                    return;
                }
}

//récupére la map de danger
void PathFinder::setDangerMap()
{
    _dangerMap = this->bombs->getDangerZone();
}

void PathFinder::setQuit()
{
    this->quit = true;
}

//vérifie si un point est marchable
bool PathFinder::isPointWalkable(int x, int y)
{
    if (y < 0 || x < 0 || _map.empty()) // hors limites
        return false;
    else if (_map.size() < y || _map[y].size() < x) // hors limites
        return false;
    else if (_map[y][x] == 1 || (_map[y][x] >= 2 && _map[y][x] <= 5) || _map[y][x] == -2) // si case occupée
        return false;
    return true;
}

//vérifie si un point est destructible
bool PathFinder::isWallBreakable(int x, int y)
{
    if (y < 0 || x < 0 || _map.empty()) // hors limites
        return false;
    else if (_map.size() < y || _map[y].size() < x) // hors limites
        return false;
    else if (_map[y][x] >= 2 && _map[y][x] <= 5) // si case occupée
        return true;
    return false;
}

//compte le nombre de mouvements possible a partir d'une case
int PathFinder::countAction()
{
    int count = 0;
    (isPointWalkable(_x - 1, _y)) ? count++ : count;
    (isPointWalkable(_x + 1, _y)) ? count++ : count;
    (isPointWalkable(_x, _y - 1)) ? count++ : count;
    (isPointWalkable(_x, _y + 1)) ? count++ : count;
    return (count);
}

//vérifie si un mur est destructible
bool PathFinder::checkBreakable()
{
    for (int i = 1; i < this->bombFire; i++) {
        if (isWallBreakable(_x - i, _y) || isWallBreakable(_x + i, _y) ||
            isWallBreakable(_x, _y - i) || isWallBreakable(_x, _y + i))
            return true;
    }
    return false;
}

//vérifie si le bot est déja passé par la
bool PathFinder::checkAction(int x, int y)
{
    for (int i = 0; i < XMap.size(); i++)
        if (XMap[i] == x && YMap[i] == y)
            return false;
    return true;
}

//vérifie si le bot est déja allé par la
bool PathFinder::lastAction(Direction way)
{
    if (XMap.empty())
        return true;
    if (way == Direction::LEFT && !checkAction(_x - 1, _y))
        return false;
    if (way == Direction::RIGHT && !checkAction(_x + 1, _y))
        return false;
    if (way == Direction::UP && !checkAction(_x, _y - 1))
        return false;
    if (way == Direction::DOWN && !checkAction(_x, _y + 1))
        return false;
    return true;
}

//décide dans quelle direction aller
Direction PathFinder::findDirection()
{
    int vertical = YToGo - _y;
    int horizontal = XToGo - _x;
    int lweight = 0;
    int rweight = 0;
    int uweight = 0;
    int dweight = 0;
//calcul le "poids" des directions
    if (horizontal < 0 && isPointWalkable(_x - 1, _y))
        lweight = (-horizontal) * 10;
    else if (isPointWalkable(_x - 1, _y))
        (horizontal > 0) ? lweight = horizontal : lweight = 1;
    else
        lweight = 0;

    if (horizontal > 0 && isPointWalkable(_x + 1, _y))
        rweight = horizontal * 10;
    else if (isPointWalkable(_x + 1, _y))
        (horizontal < 0) ? rweight = -horizontal : rweight = 1;
    else
        rweight = 0;

    if (vertical < 0 && isPointWalkable(_x, _y - 1))
        uweight = (-vertical) * 10;
    else if (isPointWalkable(_x, _y - 1))
        (vertical > 0) ? uweight = vertical : uweight = 1;
    else
        uweight = 0;

    if (vertical > 0 && isPointWalkable(_x, _y + 1))
        dweight = vertical * 10;
    else if (isPointWalkable(_x, _y + 1))
        (vertical < 0) ? dweight = -vertical : dweight = 1;
    else
        dweight = 0;

//vérifie si la direction est valide ou si c'est un cul de sac
    std::vector<int> tmp;
    int i = 0;
    if (!lastAction(Direction::LEFT))
        tmp.push_back(-1);
    else
        tmp.push_back(lweight);
    if (!lastAction(Direction::RIGHT))
        tmp.push_back(-1);
    else
        tmp.push_back(rweight);
    if (!lastAction(Direction::UP))
        tmp.push_back(-1);
    else
        tmp.push_back(uweight);
    if (!lastAction(Direction::DOWN))
        tmp.push_back(-1);
    else
        tmp.push_back(dweight);

//calcul le "poids" le plus lourd
    while (i + 1 < tmp.size())
        if (tmp[i] > tmp[i + 1]) {
            tmp.erase(tmp.begin() + i + 1);
            i = 0;
        } else if (tmp[i] < tmp[i + 1]) {
            tmp.erase(tmp.begin() + i);
            i = 0;
        } else
            i++;

//Met en relation poids et direction
    if (tmp.front() == 0)
        return Direction::UNDEFINED;
    if (tmp.front() == lweight)
        return Direction::LEFT;
    else if (tmp.front() == rweight)
        return Direction::RIGHT;
    else if (tmp.front() == uweight)
        return Direction::UP;
    else if (tmp.front() == dweight)
    return Direction::DOWN;
    return (Direction::UNDEFINED);
}

//met a jour la map des cul-de-sac
bool PathFinder::updateFormerPos(Direction way)
{
    bool ret = true;

    if (way == Direction::UNDEFINED)
        if (isPointWalkable(_x - 1, _y) || isPointWalkable(_x + 1, _y) ||
            isPointWalkable(_x, _y - 1) || isPointWalkable(_x, _y + 1))
            ret = false;
    if (ret == false) {
        YMap.clear();
        XMap.clear();
        _map[_y][_x] = -2;
    }
    if (countAction() <= 1)
        _map[_y][_x] = -2;
    YMap.push_back(_y);
    XMap.push_back(_x);
    return (ret);
}

void PathFinder::printMap()
{
    for (int m = 0; m < _map.size(); m++) {
        for (int i = 0; i < _map[m].size(); i++) {
            if (m == _y && i == _x)
                std::cout << 'p';
            else if (_map[m][i] == 1)
                std::cout << 'x';
            else if (_map[m][i] == -2)
                std::cout << 'o';
            else if (_map[m][i] >= 2 && _map[m][i] <= 5)
                std::cout << 'm';
            else
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
    for (int m = 0; m < _dangerMap.size(); m++) {
        for (int i = 0; i < _dangerMap[m].size(); i++) {
            if (_dangerMap[m][i] == 1)
                std::cout << 'x';
            else if (_dangerMap[m][i] == -2)
                std::cout << 'o';
            else if (_dangerMap[m][i] == 2)
                std::cout << 'm';
            else
                std::cout << '@';
        }
        std::cout << std::endl;
    }
}

//pose une bombe
void PathFinder::bombIt(std::mutex &mutex)
{
    // Drop a bomb
    if (isWallBreakable(_x - 1, _y) || isWallBreakable(_x + 1, _y)
        || isWallBreakable(_x, _y - 1) || isWallBreakable(_x, _y + 1)) {
        this->bombs->addBomb(std::vector<int> {_y, _x}, this->bombFire);
        this->bombs->checkBomb();

//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void PathFinder::moveAnimation()
{
    if (this->isMoving == true && this->lockMove == false) {
        this->animModel->setFrameLoop(15, 30);
        this->animModel->setAnimationSpeed(this->speed / 2);
        this->lockMove = true;
    }
    else if (this->isMoving == false && this->lockMove == true) {
        this->animModel->setFrameLoop(184, 205);
        this->animModel->setAnimationSpeed(this->speed / 2);
        this->lockMove = false;
    }
}

//modifie la position du bot
void PathFinder::modifyPosAccordingToDirection(Direction way)
{
    if (way == Direction::LEFT && isPointWalkable(_x - 1, _y)) {
        this->animModel->setRotation(irr::core::vector3df(0.0, 180.0, 0.0));
        this->isMoving = true;
        this->pos.Z -= this->speed * 0.015;
    }
    else if (way == Direction::RIGHT && isPointWalkable(_x + 1, _y)) {
        this->animModel->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));
        this->isMoving = true;
        this->pos.Z += this->speed * 0.015;
    }
    else if (way == Direction::UP && isPointWalkable(_x, _y - 1)) {
        this->animModel->setRotation(irr::core::vector3df(0.0, 270.0, 0.0));
        this->isMoving = true;
        this->pos.X -= this->speed * 0.015;
    }
    else if (way == Direction::DOWN && isPointWalkable(_x, _y + 1)) {
        this->animModel->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
        this->isMoving = true;
        this->pos.X += this->speed * 0.015;
    }
    this->_x = ((this->pos.Z + 10) / 20);
    this->_y = ((this->pos.X + 10) / 20);
    this->animModel->setPosition(this->pos);
}

//breakShit
void PathFinder::breakShit(std::mutex &mutex)
{
    if (checkBreakable()) {
        bombIt(std::ref(mutex));
        _map = _originalMap;
        mod = 2;
        setPointToGo(_x, _y);
    }
}

//coincé dans un cul de sac
void PathFinder::stuck()
{
    if (countAction() == 0) {
        _map = _originalMap;
        mod = 1;
    }
}

//ralph
bool PathFinder::chuckleImInDanger()
{
    if ( _dangerMap[_y][_x] == 2)
        this->_alive = false;
    if (_dangerMap.empty() || _dangerMap[_y][_x] == 0)
        return false;
    return true;
}

//I WILL DESTROY WALLS
void PathFinder::invertedTrump()
{
    for (int m = 0; m < _map.size(); m++)
        for (int i = 0; i < _map[m].size(); i++)
            if (_map[m][i] >= 2) {
                XToGo = i;
                YToGo = m;
                return;
            }
}

void PathFinder::checkBonnus(int posX, int posY)
{
    std::vector<Wall> bonnus = map->getBonnus();
    for (int count = 0; count != bonnus.size(); count++) {
        if (bonnus[count].getWallPosition().front() == posX
        && bonnus[count].getWallPosition().back() == posY) {
            if (map->getMap()[posX][posY] == 6) {
                this->speed += 10;
            }
            else if (map->getMap()[posX][posY] == 7) {
                this->bombFire += 1;
            }
            else if (map->getMap()[posX][posY] == 8) {
                this->bombNb += 1;
            }
            map->setMap(posX, posY, 0);
            map->removeMeshBonnus(count);
            return;
        }
    }
}

/*
cycle de jeu
cur = findDirection(); trouve une direction
updateFormerPos(cur);  met a jour la position
modifyPosAccordingToDirection(cur); déplace le bot
 */
bool PathFinder::cycle(std::mutex &mutex)
{
    Direction cur;
    int x = 0;
    irr::u32 sleepTime = this->device->getTimer()->getTime();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    while (!this->quit && this->_alive) {
        mutex.lock();
        if (this->looping) {
            this->setDangerMap();
            this->setCurrentMapState(this->map->getMap());
            this->checkBonnus(_y, _x);
            if (x == 0)
                setPointToGo(-1, -1);
            x++;
            if (dis(gen) < 0.005 && mod != 2) {
                this->bombs->addBomb(std::vector<int> {_y, _x}, this->bombFire);
                this->bombs->checkBomb();
                _map = _originalMap;
                mod = 2;
                this->setDangerMap();
                setPointToGo(_x, _y);
            }
            if (arrived() && mod == 0)
                setPointToGo(_x, _y);
            if (chuckleImInDanger() && mod != 2) {
                mod = 2;
                setPointToGo(_x, _y);
                _map = _originalMap;
            } else if (!chuckleImInDanger() && mod == 2) {
                updateFormerPos(cur);
                modifyPosAccordingToDirection(cur);
                this->isMoving = false;
                this->moveAnimation();
                sleepTime = (this->device->getTimer()->getTime() + 5000) % 100000;
                mutex.unlock();
                while (this->device->getTimer()->getTime() > 95000) {
                    if (this->quit)
                        return alive();
                    this->setDangerMap();
                    chuckleImInDanger();
                }
                while (this->device->getTimer()->getTime() < sleepTime) {
                    if (this->quit)
                        return alive();
                    this->setDangerMap();
                    chuckleImInDanger();
                }
                mutex.lock();
                mod = 0;
                setPointToGo(_x, _y);
            }

            if (mod == 0) {
                cur = findDirection();
                updateFormerPos(cur);
                modifyPosAccordingToDirection(cur);
                this->moveAnimation();
                stuck();
            } else if (mod == 1) {
                breakShit(std::ref(mutex));
                cur = findDirection();
                updateFormerPos(cur);
                modifyPosAccordingToDirection(cur);
                this->moveAnimation();
            } else if (mod == 2) {
                cur = findDirection();
                updateFormerPos(cur);
                modifyPosAccordingToDirection(cur);
                this->moveAnimation();
            }
            this->looping = false;
        }
//        std::cout << _x << " " << _y << std::endl;
        mutex.unlock();
    }
    if (this->quit) {
        return alive();
    }
    this->animModel->setFrameLoop(166, 173);
    this->animModel->setAnimationSpeed(5);
    while (this->animModel->getFrameNr() < 172) {
        while (!this->looping && !this->quit);
        if (this->quit) {
            return alive();
        }
        this->looping = false;
    }
    this->animModel->setFrameLoop(172, 173);
    this->animModel->setAnimationSpeed(0);

    return alive();
}

//arrivé?
const bool PathFinder::arrived() const
{
    if (_x == XToGo && _y == YToGo)
        return (true);
    return (false);
}

//vivant?
const bool &PathFinder::alive() const
{
    return _alive;
}

//renvoi position
const std::tuple<int, int> PathFinder::imHere() const
{
    return std::make_tuple(_y, _x);
}

std::thread PathFinder::runThread(std::mutex &mutex)
{
    std::thread thread(&PathFinder::cycle, this, std::ref(mutex));

    return thread;
}

void PathFinder::setLooping(bool looping)
{
    this->looping = looping;
}
