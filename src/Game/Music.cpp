/*
** EPITECH PROJECT, 2020
** Music.cpp
** File description:
** Music
*/

#include <iostream>
#include "Music.hpp"

Music::Music()
{
    this->volumeMusic = 00.f;
    this->volumeSound = 20.f;
    this->explosion.loadFromFile("../ressources/Music/bomb-02.ogg");
    this->pickup.loadFromFile("../ressources/Music/Powerup.ogg");
    this->putBomb.loadFromFile("../ressources/Music/putBomb.ogg");
    setSoundVolume(this->volumeSound);
    setMusicVolume(this->volumeMusic);
    this->music.setLoop(true);

}

Music::~Music()
{
}

float Music::getMusicVolume()
{
    return (volumeMusic);
}

void Music::loadMusic(const std::string &filename)
{
    music.openFromFile(filename);
}

void Music::playMusic()
{
    music.play();
}

void Music::playSound(SOUND type)
{
    switch (type) {
        case SOUND::EXPLOSION:
            this->sound.setBuffer(this->explosion);
            this->sound.play();
            break;
        case SOUND::PICKUP:
            this->sound1.setBuffer(this->pickup);
            this->sound1.play();
            break;
        case SOUND::CLICK:
            this->sound.setBuffer(this->click);
            this->sound.play();
            break;
        case SOUND::PUTBOMB:
            this->sound2.setBuffer(this->putBomb);
            this->sound2.play();
            break;
    }
}

void Music::setSoundVolume(float volume)
{
    this->sound.setVolume(volume);
    this->sound1.setVolume(volume);
    this->sound2.setVolume(volume*5);
    volumeSound = volume;
}

void Music::setMusicVolume(float volume)
{
    this->music.setVolume(volume);
    volumeMusic = volume;
}
