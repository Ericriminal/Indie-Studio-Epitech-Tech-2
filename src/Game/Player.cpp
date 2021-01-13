/*
** EPITECH PROJECT, 2020
** Player.cpp
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
irr::scene::ISceneManager *smgr, Map *map, Music *music, bombHandler *bombs,
irr::ITimer *clock, int playerNb, int posX, int posY, int type, std::vector<Bomberman::Controle> _keybinding, bool useSave)
: _device(device), _driver(driver), _smgr(smgr)
{
    this->playerNb = playerNb;
    //std::cout << posX << " " << posY << std::endl;
    this->posX = posX;
    this->posY = posY;
    this->bombs = bombs;
    this->music = music;
    this->map = map;
    this->receiver = receiver;
    this->_player = this->_device->getSceneManager()->getMesh("../ressources/images/character/ninja.b3d");
    this->animModel = this->_device->getSceneManager()->addAnimatedMeshSceneNode(this->_player);
    setTexture(type);
    this->animModel->setScale(irr::core::vector3df(3.f,3.f,3.f));
    this->animModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->animModel->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
    this->animModel->setPosition(irr::core::vector3df(this->posY*20,10,this->posX*20));
    this->life = 1;
    if (useSave) {
        this->useSave();
    } else {
        this->progress = 0;
        this->speed = 60;
        this->bombFire = 1;
        this->bombNb = 1;
        this->bombNbFix = 1;
    }
    this->isMoving = false;
    this->test = true;
    this->playerPos.push_back(this->posX-1);
    this->playerPos.push_back(this->posY-1);
    this->AllowBomb = true;
    this->isAlive = true;
    this->clock = clock;
    this->clock->setTime(0);
    this->clock->start();
    this->key = _keybinding;
    setMovement();
}

Player::~Player()
{

}

irr::scene::IAnimatedMeshSceneNode *Player::getAnimeModel() const
{
    return (this->animModel);
}

void Player::useSave()
{
    std::ifstream ifs("save.bomberman");
    char read[100];

    ifs.getline(read, 100);
    this->progress = std::stoi(read);
    ifs.getline(read, 100);
    this->bombNb = std::stoi(read);
    this->bombNbFix = std::stoi(read);
    ifs.getline(read, 100);
    this->bombFire = std::stoi(read);
    ifs.getline(read, 100);
    this->speed = std::stoi(read);

}

void Player::setTexture(int type)
{
    switch (type) {
        case 0:
            this->animModel->setMaterialTexture(0, _driver->getTexture("../ressources/images/character/nskinbl.jpg"));
            break;
        case 1:
            this->animModel->setMaterialTexture(0, _driver->getTexture("../ressources/images/character/nskinbl2.jpg"));
            break;
        case 2:
            this->animModel->setMaterialTexture(0, _driver->getTexture("../ressources/images/character/nskinbl3.jpg"));
            break;
        case 3:
            this->animModel->setMaterialTexture(0, _driver->getTexture("../ressources/images/character/nskinbl4.jpg"));
            break;
    }
}

void Player::setMovement()
{
    if (this->playerNb == 1) {
        this->Movement.up = key[0].up;
        this->Movement.down = key[0].down;
        this->Movement.left = key[0].left;
        this->Movement.right = key[0].right;
        this->Movement.put = key[0].put;
    }
    else {
        this->Movement.up = key[1].up;
        this->Movement.down = key[1].down;
        this->Movement.left = key[1].left;
        this->Movement.right = key[1].right;
        this->Movement.put = key[1].put;
    }
}

void Player::move(MyEventReceiver *receiver)
{
    irr::core::vector3df pos = this->animModel->getPosition();
    if(receiver->IsKeyDown(this->Movement.up)) {
        this->isMoving = true;
        this->animModel->setRotation(irr::core::vector3df(0.0, 270.0, 0.0));
        pos.X -= speed * 0.015;
    }
    else if(receiver->IsKeyDown(this->Movement.down)) {
        this->isMoving = true;
        this->animModel->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
        pos.X += speed * 0.015;
    }
    else if(receiver->IsKeyDown(this->Movement.left)) {
        this->isMoving = true;
        this->animModel->setRotation(irr::core::vector3df(0.0, 180.0, 0.0));
        pos.Z -= speed * 0.015;
    }
    else if(receiver->IsKeyDown(this->Movement.right)) {
        this->isMoving = true;
        this->animModel->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));
        pos.Z += speed * 0.015;
    }
    else
        this->isMoving = false;
    this->posX = ((pos.Z + 10) / 20);
    this->posY = ((pos.X + 10) / 20);
    this->animModel->setPosition(pos);
}

void Player::moveAnimation(MyEventReceiver *receiver)
{
    if (this->isMoving == true && this->test == false) {
        this->animModel->setFrameLoop(15, 30);
        this->animModel->setAnimationSpeed(this->speed / 2);
        this->test = true;
    }
    else if (this->isMoving == false && this->test == true) {
        this->animModel->setFrameLoop(184, 205);
        this->animModel->setAnimationSpeed(this->speed / 2);
        this->test = false;
    }
}

void Player::action(MyEventReceiver *receiver)
{
    if (this->AllowBomb && receiver->IsKeyDown(this->Movement.put) && this->bombNb > 0) {
        music->playSound(SOUND::PUTBOMB);
        this->bombs->addBomb(std::vector<int> {this->getPlayerPos()[0], this->getPlayerPos()[1]}, this->getPower());
        this->bombNb -= 1;
        this->remainingTime.push_back((this->clock->getTime() + 3000) % 100000);
        this->pos.push_back(this->posX);
        this->pos.push_back(this->posY);
        this->AllowBomb = false;
    }
}

void Player::timehandler()
{
    for (int bombCounter = 0; bombCounter < this->remainingTime.size(); bombCounter++) {
        this->waitTime(bombCounter);
    }
    for (int bombCounter = 0; bombCounter < this->pos.size(); bombCounter+=2) {
        if (this->pos[bombCounter] == this->posX && this->pos[bombCounter+1] == this->posY) {
            this->AllowBomb = false;
        }
        else
            this->AllowBomb = true;
    }
}

void Player::waitTime(int count)
{
    irr::u32 actualTime = this->clock->getTime();
    bool isOnRightTiming = true;

    if (actualTime >= 100000) {
        this->clock->setTime(irr::u32(0));
        actualTime = this->clock->getTime();
    }
    if (actualTime > 97000 && this->remainingTime[count] < 3000) {
        isOnRightTiming = false;
    }
    if (isOnRightTiming && actualTime > this->remainingTime[count]) {
        this->bombNb +=1;
        this->remainingTime.erase(this->remainingTime.begin());
        this->pos.erase(this->pos.begin());
        this->pos.erase(this->pos.begin());
    }
}

void Player::checkBonnus()
{
    std::vector<Wall> bonnus = map->getBonnus();
    for (int count = 0; count != bonnus.size(); count++) {
        if (bonnus[count].getWallPosition().front() == this->posY
        && bonnus[count].getWallPosition().back() == this->posX) {
            music->playSound(SOUND::PICKUP);
            if (map->getMap()[this->posY][this->posX] == 6) {
                this->speed += 10;
            }
            else if (map->getMap()[this->posY][this->posX] == 7) {
                this->bombFire += 1;
            }
            else if (map->getMap()[this->posY][this->posX] == 8) {
                this->bombNb += 1;
                this->bombNbFix += 1;
            }
            map->setMap(this->posY, this->posX, 0);
            map->removeMeshBonnus(count);
            return;
        }
    }
}

void Player::checkPlayerHit()
{
    std::vector<std::vector<int>> mapDangerZone = bombs->getDangerZone();

    if (mapDangerZone[this->posY][this->posX] == 2) {
        this->life -= 1;
        this->isAlive = false;
        this->animModel->setFrameLoop(166, 173);
        this->animModel->setAnimationSpeed(5);
    }
}

void Player::updatePlayerDeathAnimation()
{
    if (this->animModel->getFrameNr() >= 172) {
        this->animModel->setFrameLoop(172, 173);
        this->animModel->setAnimationSpeed(0);
    }
}

std::vector<int> Player::getPlayerPos()
{
    this->playerPos[0] = this->posY;
    this->playerPos[1] = this->posX;
    return (this->playerPos);
}

int Player::getLife() const
{
    return (this->life);
}

int Player::getSpeed() const
{
    return (this->speed);
}

int Player::getPower() const
{
    return (this->bombFire);
}

int Player::getNbBomb() const
{
    return (this->bombNb);
}

bool Player::getIsAlive() const
{
    return (this->isAlive);
}

void Player::setNbBomb(int nb)
{
    this->bombNb += nb;
}

void Player::saveProgress()
{
    std::ofstream ofs("save.bomberman");

    if (progress != 3)
        ofs << std::to_string(this->progress + 1) << "\n"; // progression
    else
        ofs << std::to_string(this->progress) << "\n"; // progression
    ofs << std::to_string(this->bombNbFix) << "\n"; // nb bomb
    ofs << std::to_string(this->bombFire) << "\n"; // puissance
    ofs << std::to_string(this->speed) << "\n"; // vitesse
}
