/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** CommandManager cpp file
*/

#include "../../include/client/CommandManager.hpp"

Commands::CommandManager::CommandManager()
{
    std::vector<std::string> object_strings {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"};
    _object_strings = object_strings;

    std::cout << std::endl;
}

Commands::CommandManager::~CommandManager() {}

std::string Commands::CommandManager::command(ClientCommands cmd, Objects obj) const
{
    if (cmd == FORWARD)
        return std::string("Forward");
    if (cmd == RIGHT)
        return std::string("Right");
    if (cmd == LEFT)
        return std::string("Left");
    if (cmd == LOOK)
        return std::string("Look");
    if (cmd == INVENTORY)
        return std::string("Inventory");
    if (cmd == TAKE)
        return std::string("Take " + _object_strings[obj]);
    if (cmd == SET)
        return std::string("Set " + _object_strings[obj]);
    if (cmd == START_LEVEL_UP)
        return std::string("Incantation");
    return std::string("FAILED");
}

std::string Commands::CommandManager::command(ClientCommands cmd, int level) const
{
    if (cmd == BROADCAST_EVOLVE)
        return std::string("Broadcast " + std::to_string(level));
    return std::string("FAILED");
}