/*
** EPITECH PROJECT, 2020
** bomb.cpp
** File description:
** bomb
*/

#include "bomb.hpp"

bombHandler::bombHandler(irr::scene::ISceneManager *smgr,
    irr::video::IVideoDriver *driver, irr::ITimer *clock, Map *map, Music *music)
{
    this->map = map;
    this->smgr = smgr;
    this->driver = driver;
    this->bombMesh = this->smgr->getMesh("../ressources/images/Bomb.obj");
    this->pause = false;
    this->music = music;
    this->clock = clock;
    this->clock->setTime(0);
    this->clock->start();
    std::vector<std::vector<int>> gameMap = map->getMap();
    for (int y = 0; y < gameMap.size(); y++) {
        this->mapEffectZone.push_back({});
        for (int x = 0; x < gameMap[y].size(); x++) {
            this->mapEffectZone[y].push_back(0);
        }
    }
}

bombHandler::~bombHandler()
{
}

int bombHandler::bombRadiusVertical(std::vector<std::vector<int>> actualMap,
    int force, int startPos, int incrementor, std::vector<int> *wallExplosedTmp)
{
    for (int forceCount = 0; forceCount < force; forceCount++) {
        if (actualMap[startPos + incrementor][this->bombPos.back().front()] == 0
        || (actualMap[startPos + incrementor][this->bombPos.back().front()] >= 6
        && actualMap[startPos + incrementor][this->bombPos.back().front()] <= 8))
            startPos += incrementor;
        else {
            if (actualMap[startPos + incrementor][this->bombPos.back().front()] != 1) {
                wallExplosedTmp->push_back(this->bombPos.back().front());
                wallExplosedTmp->push_back(startPos + incrementor);
                startPos += incrementor;
            }
            forceCount = force;
        }
    }
    return startPos;
}

int bombHandler::bombRadiusHorizontal(std::vector<std::vector<int>> actualMap,
    int force, int startPos, int incrementor, std::vector<int> *wallExplosedTmp)
{
    for (int forceCount = 0; forceCount < force; forceCount++) {
        if (actualMap[this->bombPos.back().back()][startPos + incrementor] == 0
        || (actualMap[this->bombPos.back().back()][startPos + incrementor] >= 6
        && actualMap[this->bombPos.back().back()][startPos + incrementor] <= 8))
            startPos += incrementor;
        else {
            if (actualMap[this->bombPos.back().back()][startPos + incrementor] != 1) {
                wallExplosedTmp->push_back(startPos + incrementor);
                wallExplosedTmp->push_back(this->bombPos.back().back());
                startPos += incrementor;
            }
            forceCount = force;
        }
    }
    return startPos;
}

int bombHandler::getBombRadius(std::vector<std::vector<int>> actualMap,
    int direction, int force, std::vector<int> *allWallDestroyed)
{
    int startPos = 0;

    switch (direction) {
        case 0 :
            startPos = this->bombPos.back().back();
            startPos = this->bombRadiusVertical(actualMap, force, startPos,
                -1, allWallDestroyed);
            break;
        case 1 :
            startPos = this->bombPos.back().back();
            startPos = this->bombRadiusVertical(actualMap, force, startPos,
                1, allWallDestroyed);
            break;
        case 2 :
            startPos = this->bombPos.back().front();
            startPos = this->bombRadiusHorizontal(actualMap, force, startPos,
                -1, allWallDestroyed);
            break;
        case 3 :
            startPos = this->bombPos.back().front();
            startPos = this->bombRadiusHorizontal(actualMap, force, startPos,
                1, allWallDestroyed);
            break;
    }
    return startPos;
}

void bombHandler::setDangerZone(int force)
{
    std::vector<std::vector<int>> actualMap = map->getMap();
    std::vector<int> allWallDestroyed;
    std::vector<int> dangerZone;

    dangerZone.push_back(1); // type of danger of the bomb
    dangerZone.push_back(this->bombPos.back().front()); // top X
    dangerZone.push_back(this->getBombRadius(actualMap, 0, force, &allWallDestroyed)); // top Y
    dangerZone.push_back(this->bombPos.back().front()); // down X
    dangerZone.push_back(this->getBombRadius(actualMap, 1, force, &allWallDestroyed)); // down Y
    dangerZone.push_back(this->getBombRadius(actualMap, 2, force, &allWallDestroyed)); // left X
    dangerZone.push_back(this->bombPos.back().back()); // left Y
    dangerZone.push_back(this->getBombRadius(actualMap, 3, force, &allWallDestroyed)); // right X
    dangerZone.push_back(this->bombPos.back().back()); // right Y
    this->wallExplosed.push_back(allWallDestroyed);
    this->bombEffectZone.push_back(dangerZone);
}

bool bombHandler::addBomb(std::vector<int> actualBomb, int force)
{
    irr::scene::IAnimatedMeshSceneNode *animModel = this->smgr->addAnimatedMeshSceneNode(this->bombMesh);
    animModel->setMaterialTexture(0, driver->getTexture("../ressources/images/texture.png"));
    animModel->setPosition(irr::core::vector3df((20 * actualBomb[0]), 0, (20 * actualBomb[1])));
    animModel->setScale(irr::core::vector3df(1.f,1.f,1.f));
    animModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    animModel->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
    this->bombMeshSceneNode.push_back(animModel);
    this->bombPos.push_back({actualBomb.back(), actualBomb.front()});
    this->bombStatus.push_back(BOMB_STATUS::EXPLODING);
    this->setDangerZone(force);
    this->remainingTime.push_back((this->clock->getTime() + 3000) % 100000);
    return true;
}

void bombHandler::setBombExplosion(int bombCounter)
{
    std::vector<int> actualWallDestroyed = this->wallExplosed[bombCounter];
    int wallX = 0;
    int wallY = 0;

    this->music->playSound(SOUND::EXPLOSION);
    while (actualWallDestroyed.size() != 0) {
        wallX = actualWallDestroyed.back();
        actualWallDestroyed.pop_back();
        wallY = actualWallDestroyed.back();
        actualWallDestroyed.pop_back();
        this->map->removeWall(wallX, wallY);
    }
    this->bombEffectZone[bombCounter].front() = 2;
}

void bombHandler::addParticles(int bombCounter)
{
    int lengthExplosionY = this->bombEffectZone[bombCounter][4] - this->bombEffectZone[bombCounter][2];
    int lengthExplosionX = this->bombEffectZone[bombCounter][7] - this->bombEffectZone[bombCounter][5];

    irr::scene::IParticleSystemSceneNode* horizontalParticles =
        this->smgr->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* horizontalEm = horizontalParticles->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-5, 0, -5  + (-10 * lengthExplosionX), 5, 1, 5), // emitter size
        irr::core::vector3df(0.0f, 0.06f, 0.0f),   // initial direction
        80 * lengthExplosionX, 100 * lengthExplosionX,                             // emit rate
        irr::video::SColor(0,255,255,255),       // darkest color
        irr::video::SColor(0,255,255,255),       // brightest color
        500,600,0,                         // min and max age, angle
        irr::core::dimension2df(10.f,10.f),         // min size
        irr::core::dimension2df(11.f,11.f));        // max size

    horizontalParticles->setEmitter(horizontalEm); // this grabs the emitter
    horizontalEm->drop(); // so we can drop it here without deleting it

    irr::scene::IParticleAffector* horizontalAff = horizontalParticles->createFadeOutParticleAffector();

    horizontalParticles->addAffector(horizontalAff); // same goes for the affector
    horizontalAff->drop();

    horizontalParticles->setPosition(irr::core::vector3df(20 * (this->bombEffectZone[bombCounter][8]),0,20 * ((this->bombEffectZone[bombCounter][7]))));
    horizontalParticles->setScale(irr::core::vector3df(2,2,2));
    horizontalParticles->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    horizontalParticles->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    horizontalParticles->setMaterialTexture(0, driver->getTexture("../ressources/images/fireball.bmp"));
    horizontalParticles->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

    irr::scene::IParticleSystemSceneNode* verticalParticles =
        this->smgr->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* verticalEm = verticalParticles->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-5 + (-10 * lengthExplosionY), 0, -5, 5, 1, 5), // emitter size
        irr::core::vector3df(0.0f,0.06f,0.0f),   // initial direction
        80 * lengthExplosionY,100 * lengthExplosionY,                             // emit rate
        irr::video::SColor(0,255,255,255),       // darkest color
        irr::video::SColor(0,255,255,255),       // brightest color
        500,600,0,                         // min and max age, angle
        irr::core::dimension2df(10.f,10.f),         // min size
        irr::core::dimension2df(11.f,11.f));        // max size

    verticalParticles->setEmitter(verticalEm); // this grabs the emitter
    verticalEm->drop(); // so we can drop it here without deleting it

    irr::scene::IParticleAffector* veritcalAff = verticalParticles->createFadeOutParticleAffector();

    verticalParticles->addAffector(veritcalAff); // same goes for the affector
    veritcalAff->drop();

    verticalParticles->setPosition(irr::core::vector3df(20 * (this->bombEffectZone[bombCounter][4]),0,20 * ((this->bombEffectZone[bombCounter][3]))));
    verticalParticles->setScale(irr::core::vector3df(2,2,2));
    verticalParticles->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    verticalParticles->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    verticalParticles->setMaterialTexture(0, driver->getTexture("../ressources/images/fireball.bmp"));
    verticalParticles->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    this->bombParticles.push_back(std::vector<irr::scene::IParticleSystemSceneNode *> {horizontalParticles, verticalParticles});
}

void bombHandler::removeParticles()
{

}

void bombHandler::checkWaitTime(int bombCounter, irr::u32 actualTime)
{
    bool isOnRightTiming = true;

    if (actualTime > 97000 && this->remainingTime[bombCounter] < 3000) {
        isOnRightTiming = false;
    }
    if (this->bombStatus[bombCounter] == BOMB_STATUS::NONE)
        return;
    if (isOnRightTiming && this->bombStatus[bombCounter] == BOMB_STATUS::EXPLODING
        && actualTime > this->remainingTime[bombCounter]) {
        this->setBombExplosion(bombCounter);
        this->addParticles(bombCounter);
        this->bombMeshSceneNode[bombCounter]->remove();
        this->remainingTime[bombCounter] = (this->clock->getTime() + 1000) % 100000;
        this->bombStatus[bombCounter] = BOMB_STATUS::EXPLODED;
    } else if (this->bombStatus[bombCounter] == BOMB_STATUS::EXPLODED
        && actualTime > this->remainingTime[bombCounter]) {
        this->bombStatus[bombCounter] = BOMB_STATUS::NONE;
    }
}

void bombHandler::addVerticalDangerZone(int dangerType, int topX, int topY,
    int downY)
{
    for (; topY <= downY; topY++) {
        this->mapEffectZone[topY][topX] = dangerType;
    }
}

void bombHandler::addHorizontalDangerZone(int dangerType, int leftX, int leftY,
    int rightX)
{
    for (; leftX <= rightX; leftX++) {
        this->mapEffectZone[leftY][leftX] = dangerType;
    }
}

void bombHandler::updateDangerZone()
{
    int totalBombEffectZone = this->bombEffectZone.size();

    for (int y = 0; y < this->mapEffectZone.size(); y++) {
        for (int x = 0; x < this->mapEffectZone[y].size(); x++) {
            this->mapEffectZone[y][x] = 0;
        }
    }
    for (int count = 0; count < totalBombEffectZone; count++) {
        this->addVerticalDangerZone(this->bombEffectZone[count][0],
            this->bombEffectZone[count][1], this->bombEffectZone[count][2],
            this->bombEffectZone[count][4]);
        this->addHorizontalDangerZone(this->bombEffectZone[count][0],
            this->bombEffectZone[count][5], this->bombEffectZone[count][6],
            this->bombEffectZone[count][7]);
    }
}

void bombHandler::removeOldPointer()
{
    for (int count = 0; count < this->bombStatus.size(); count++) {
        if (this->bombStatus[count] == BOMB_STATUS::NONE) {
            this->bombPos.erase(this->bombPos.begin());
            this->bombMeshSceneNode.erase(this->bombMeshSceneNode.begin());
            this->wallExplosed.erase(this->wallExplosed.begin());
            this->bombEffectZone.erase(this->bombEffectZone.begin());
            this->remainingTime.erase(this->remainingTime.begin());
            this->bombStatus.erase(this->bombStatus.begin());
            this->bombParticles.front().front()->remove();
            this->bombParticles.front().back()->remove();
            this->bombParticles.erase(this->bombParticles.begin());
            count = -1;
        }
    }
}

std::vector<std::vector<int>> bombHandler::getDangerZone()
{
    return this->mapEffectZone;
}

void bombHandler::SetPause(bool pause)
{
    this->pause = pause;
    if (pause)
        this->clock->stop();
    else
        this->clock->start();
}

void bombHandler::checkBomb()
{
    irr::u32 actualTime = this->clock->getTime();

    if (actualTime >= 100000) {
        this->clock->setTime(irr::u32(0));
        actualTime = this->clock->getTime();
    }
    for (int bombCounter = 0; !pause && bombCounter < this->bombStatus.size(); bombCounter++)
        this->checkWaitTime(bombCounter, actualTime);
    this->removeOldPointer();
    this->updateDangerZone();
    //this->map->dump_map(this->mapEffectZone);
}
