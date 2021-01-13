/*
** EPITECH PROJECT, 2020
** main
** File description:
** main for bomberman
*/

#include <iostream>
#include <string>
#include "Core.hpp"

int main()
{
    core Bomberman;

    try {
        Bomberman.start();
    }
    catch (const std::string msg) {
        std::cout << msg << std::endl;
        return (84);
    }
    return (0);
}