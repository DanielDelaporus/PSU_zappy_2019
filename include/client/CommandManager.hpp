/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** CommandManager hpp file
*/

#include <vector>
#include <string>
#include <iostream>

#ifndef COMMANDMANAGER_HPP_
#define COMMANDMANAGER_HPP_

namespace Commands {
    enum ClientCommands {
        FORWARD,
        RIGHT,
        LEFT,
        LOOK,
        INVENTORY,
        BROADCAST_EVOLVE,
        TAKE,
        SET,
        START_LEVEL_UP
    };

    enum Objects {
        NOTHING = -1,
        linemate = 0,
        deraumere = 1,
        sibur = 2,
        mendiane = 3,
        phiras = 4,
        thystame = 5,
        food = 6
    };

    class CommandManager {
        public:
            CommandManager();
            ~CommandManager();
            std::string command(ClientCommands, Objects = Objects::NOTHING) const;
            std::string command(ClientCommands, int) const;
            void set_Obj(Objects);
            std::string get_Obj();

        private:
            std::vector<std::string> _object_strings = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"};
    };
}

#endif