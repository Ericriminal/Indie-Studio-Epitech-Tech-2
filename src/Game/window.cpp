/*
** EPITECH PROJECT, 2020
** window.cpp
** File description:
** window
*/

#include "window.hpp"

window::window(irr::IrrlichtDevice *device, MyEventReceiver *receiver,
    std::vector<Bomberman::Controle> _keybinding, Music *music, int mode,
    std::vector<int> _color)
: _ground(device->getSceneManager(), device, device->getVideoDriver()),
map(device, mode),
ui(device, device->getVideoDriver(), device->getSceneManager(), device->getGUIEnvironment())
, music(),
bombs(device->getSceneManager(), device->getVideoDriver(), device->getTimer(), &this->map, &this->music)
,mutex(), keybinding(_keybinding)
{
    this->receiver = receiver;
    this->device = device;
    this->driver = device->getVideoDriver();
    this->guienv = device->getGUIEnvironment();
    this->smgr = device->getSceneManager();
    if (mode == 3)
        this->saveMode = true;
    else
        this->saveMode = false;
    for (int count = 0; mode != 3 && count < mode; count++) {
        if (count == 0)
            this->player.push_back(Player(device, device->getVideoDriver(), device->getSceneManager(),
            &this->map, &this->music, &this->bombs, device->getTimer(), 1, 1,1, _color[count], keybinding, false));
        if (count == 1)
            this->player.push_back(Player(device, device->getVideoDriver(), device->getSceneManager(),
            &this->map, &this->music, &this->bombs, device->getTimer(), 2, map.getMapSize()[0]-2, 1, _color[count], keybinding, false));
        this->allEntityChar.push_back(this->player[count].getAnimeModel()); // to update
    }
    if (mode == 3) {
        this->player.push_back(Player(device, device->getVideoDriver(), device->getSceneManager(),
        &this->map, &this->music, &this->bombs, device->getTimer(), 1, 1,1, _color[0], keybinding, true));
        this->allEntityChar.push_back(this->player[0].getAnimeModel()); // to update
    }
    this->smgr->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));
    if (mode == 3) {
        for (int count = 1; count < 4; count++)
            this->ai.push_back(PathFinder(device, &this->bombs, &this->map, count, count + 1));
    } else {
        for (int count = mode; count < 4; count++)
            this->ai.push_back(PathFinder(device, &this->bombs, &this->map, count, count + 1));
    }

    //loadfont
    ui.loadFont("../ressources/font/fonthaettenschweiler.bmp");
    // create map
    this->map.createMap(this->map.getMap(), this->allEntityChar);
    destructible_wall = map.getDestructibleWall();
    irr::scene::IMeshSceneNode *cubemesh = destructible_wall[0].getcubeMesh();

    //music.loadMusic("../ressources/Music/test.ogg");

    //music.playMusic();
    irr::scene::ICameraSceneNode* fpsCamera = this->smgr->addCameraSceneNode();
    fpsCamera->setPosition(irr::core::vector3df(((map.getMapSize()[0]*20)/2),(map.getMapSize()[0]+map.getMapSize()[1])*10,((map.getMapSize()[1]*20)/2)));
    fpsCamera->setTarget(irr::core::vector3df(((map.getMapSize()[0]*20)/2)-(map.getMapSize()[0]*2.5),0,((map.getMapSize()[1]*20)/2)));

    //ground collision
    irr::scene::ITriangleSelector* selector = 0;
    selector = _ground.getSelector();
    if (selector) {
        irr::scene::ISceneNodeAnimator* anim;
        for (int count = 0; count != this->allEntityChar.size(); count++) {
            anim = this->smgr->createCollisionResponseAnimator(
                selector, this->allEntityChar[count], irr::core::vector3df(1,1,1),
                irr::core::vector3df(0,-20,0), irr::core::vector3df(0,0,0));
            selector->drop(); // As soon as we're done with the selector, drop it.
            this->allEntityChar[count]->addAnimator(anim);
        }
        anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }
    for (int count = 0; count < this->ai.size(); count++)
        allThread.push_back(this->ai[count].runThread(std::ref(this->mutex)));
}

// window::window(irr::IrrlichtDevice *device, MyEventReceiver *receiver,
//     std::vector<Bomberman::Controle> _keybinding, Music *music, int nbPlayer)
// : _ground(device->getSceneManager(), device, device->getVideoDriver()),
// map(device),
// ui(device, device->getVideoDriver(), device->getSceneManager(), device->getGUIEnvironment())
// , music(),
// bombs(device->getSceneManager(), device->getVideoDriver(), device->getTimer(), &this->map, &this->music)
// ,mutex(), keybinding(_keybinding)
// {
//     this->receiver = receiver;
//     this->device = device;
//     this->driver = device->getVideoDriver();
//     this->guienv = device->getGUIEnvironment();
//     this->smgr = device->getSceneManager();
//     this->player.push_back(Player(device, device->getVideoDriver(), device->getSceneManager(),
//     &this->map, &this->music, &this->bombs, device->getTimer(), 1, 1,1, TEXTURE::TEXTURE_RED, keybinding));
//     this->player.push_back(Player(device, device->getVideoDriver(), device->getSceneManager(),
//     &this->map, &this->music, &this->bombs, device->getTimer(), 2, map.getMapSize()[0]-2,map.getMapSize()[1]-2, TEXTURE::TEXTURE_BLUE, keybinding));
//     this->smgr->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));
//     this->allEntityChar.push_back(this->player[0].getAnimeModel()); // to update
//     this->allEntityChar.push_back(this->player[1].getAnimeModel()); // to update
//     this->ai.push_back(PathFinder(device, &this->bombs, &this->map, 1, 3));
//
//     //loadfont
//     ui.loadFont("../ressources/font/fonthaettenschweiler.bmp");
//     // create map
//     this->map.createMap(this->map.getMap(), this->allEntityChar);
//     destructible_wall = map.getDestructibleWall();
//     irr::scene::IMeshSceneNode *cubemesh = destructible_wall[0].getcubeMesh();
//
//     //music.loadMusic("../ressources/Music/test.ogg");
//
//     //music.playMusic();
//     irr::scene::ICameraSceneNode* fpsCamera = this->smgr->addCameraSceneNode();
//     fpsCamera->setPosition(irr::core::vector3df(((map.getMapSize()[0]*20)/2),(map.getMapSize()[0]+map.getMapSize()[1])*10,((map.getMapSize()[1]*20)/2)));
//     fpsCamera->setTarget(irr::core::vector3df(((map.getMapSize()[0]*20)/2)-(map.getMapSize()[0]*2.5),0,((map.getMapSize()[1]*20)/2)));
//
//     //ground collision
//     irr::scene::ITriangleSelector* selector = 0;
//     selector = _ground.getSelector();
//     if (selector) {
//         irr::scene::ISceneNodeAnimator* anim;
//         for (int count = 0; count != this->allEntityChar.size(); count++) {
//             anim = this->smgr->createCollisionResponseAnimator(
//                 selector, this->allEntityChar[count], irr::core::vector3df(1,1,1),
//                 irr::core::vector3df(0,-20,0), irr::core::vector3df(0,0,0));
//             selector->drop(); // As soon as we're done with the selector, drop it.
//             this->allEntityChar[count]->addAnimator(anim);
//         }
//         anim->drop();  // And likewise, drop the animator when we're done referring to it.
//     }
//     allThread.push_back(this->ai[0].runThread(std::ref(this->mutex)));
// }

window::~window()
{
    guienv->clear();
    smgr->clear();
}

int window::nbPlayersAlive()
{
    int totalPlayer = this->player.size();
    int totalPlayerAlive = 0;

    for (int count = 0; count < totalPlayer; count++) {
        if (this->player[count].getIsAlive())
            totalPlayerAlive++;
    }
    return totalPlayerAlive;
}

int window::nbAisAlive()
{
    int totalAis = this->ai.size();
    int totalAiAlive = 0;

    for (int count = 0; count < totalAis; count++) {
        if (this->ai[count].alive())
            totalAiAlive++;
    }
    return totalAiAlive;
}

int window::doScene()
{
    // player movement
    int nbPlayersAlive = this->nbPlayersAlive();
    int nbAisAlive = this->nbAisAlive();
    if (nbPlayersAlive == 1 && nbAisAlive == 0) {
        for (int count = 0; count < allThread.size(); count++) {
            ai[count].setQuit();
            allThread[count].join();
        }
        if (this->saveMode)
            this->player[0].saveProgress();
        return 9;//YOU WIN;
    } else if (nbPlayersAlive == 0) {
        for (int count = 0; count < allThread.size(); count++) {
            ai[count].setQuit();
            allThread[count].join();
        }
        return 8; //YOU LOSE;
    }
    this->bombs.checkBomb();
    for (int count = 0; count < this->player.size(); count++) {
        if (this->player[count].getIsAlive()) {
            this->player[count].checkBonnus();
            this->player[count].checkPlayerHit();
            this->player[count].moveAnimation(this->receiver);
            this->player[count].move(this->receiver);
            this->player[count].timehandler();
            this->player[count].action(this->receiver);
        } else {
            player[count].updatePlayerDeathAnimation();
        }
    }
    for (int count = 0; count < this->ai.size(); count++) {
        this->ai[count].setLooping(true);
    }

    this->driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    this->smgr->drawAll();
    this->guienv->drawAll();
    ui.printPlayerInfo(&player[0], 150, 0);
    if (this->player.size() == 2)
        ui.printPlayerInfo(&player[1], 1700, 0);
    this->driver->endScene();
    return (0);
}
