/*
** EPITECH PROJECT, 2020
** Controle
** File description:
** enum Control for bomberman
*/

#ifndef CONTROLE_HPP_
#define CONTROLE_HPP_

#include <irrlicht.h>

namespace Bomberman {
    struct Controle {
            irr::EKEY_CODE up;
            irr::EKEY_CODE down;
            irr::EKEY_CODE left;
            irr::EKEY_CODE right;
            irr::EKEY_CODE put;
    };
}

#endif /* !CONTROLE_HPP_ */
