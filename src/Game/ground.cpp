/*
** EPITECH PROJECT, 2020
**
** File description:
**
*/

#include "ground.hpp"

ground::ground(irr::scene::ISceneManager *smgr, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
{
    this->smgr = smgr;
    // The Quake mesh is pickable, but doesn't get highlighted.
    this->smgr->getParameters()->setAttribute(irr::scene::COLLADA_CREATE_SCENE_INSTANCES, true);
    this->groundMesh = this->smgr->getMesh("../ressources/ground/Untitled 1.obj");
    irr::scene::IAnimatedMeshSceneNode* groundAnim = smgr->addAnimatedMeshSceneNode(this->groundMesh);
    groundAnim->setMaterialTexture(0, driver->getTexture("../ressources/ground/yy.png"));
///    groundAnim->setAnimationSpeed(30);
    groundAnim->setScale(irr::core::vector3df(1.f,1.f,1.f));
    groundAnim->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //groundAnim->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    groundAnim->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
    if (this->groundMesh)
        this->groundNode = smgr->addOctreeSceneNode(this->groundMesh->getMesh(0), 0, 1);
//    groundAnim->drop();
}

ground::~ground()
{
}

irr::scene::ITriangleSelector* ground::getSelector()
{
    return (this->smgr->createOctreeTriangleSelector(
                    this->groundNode->getMesh(), this->groundNode, 128));
}
