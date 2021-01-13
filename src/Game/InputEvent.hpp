/*
** EPITECH PROJECT, 2020
** Event.hpp
** File description:
** Event
*/

#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP
#include <irrlicht.h>
#include <iostream>
#include "driverChoice.h"

class MyEventReceiver : public irr::IEventReceiver
{
public:
    // This is the one method that we have to implement
    bool OnEvent(const irr::SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    }

    // This is used to check whether a key is being held down
    bool IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    bool *getKey(void)
    {
        return KeyIsDown;
    }

    MyEventReceiver()
    {
        for (irr::u32 i=0; i< irr::KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};
#endif
