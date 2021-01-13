/*
** EPITECH PROJECT, 2020
** Music.hpp
** File description:
** Music
*/

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <irrlicht.h>
#include <SFML/Audio.hpp>

enum SOUND
{
    EXPLOSION,
    PICKUP,
    CLICK,
    PUTBOMB,
    TOUCHED
};


class Music
{
private:
    float volumeMusic;
    float volumeSound;
    sf::SoundBuffer explosion;
    sf::SoundBuffer pickup;
    sf::SoundBuffer click;
    sf::SoundBuffer putBomb;
    sf::Sound sound;
    sf::Sound sound1;
    sf::Sound sound2;

    sf::Music music;

public:
    Music();
    ~Music();
    void loadMusic(const std::string &filename);
    void playMusic();
    void playSound(SOUND type);
    void setSoundVolume(float sound);
    void setMusicVolume(float sound);
    float getMusicVolume();

};

#endif
