/*
** EPITECH PROJECT, 2019
**
** File description:
**
*/

#ifndef IA_HPP_
#define IA_HPP_

#include <unordered_map>
#include <string>
#include "../../include/client/CommandManager.hpp"
#include "../../include/client/Parseur.hpp"

namespace IA {
    enum MoveEnum {
    FORWARD,
    RIGHT,
    LEFT,
    LOOK,
    BROADCAST_EVOLVE,
    EVOLVE,
    INVENTORY,
    GET,
    SET
    };

    class IA {
        public:
            IA();
            ~IA();

            void Lock();
            bool Need_Ressource();
            bool Can_LevelupInv();
            bool compare(std::unordered_map<std::string, int>);
            void find_need();
            bool need_object_inView(std::vector<std::vector<std::string>>);

            bool Ressource_needed(std::string);
            bool isNeeded(std::string);

            void Evolve();
            void Level_up();

            void update(std::string);

            void set_down_evolve();

            void update_inventory(std::vector<std::vector<std::string>>);
            void dump_inventory();

            std::string next_move();

            int getX(int);
            int getY(int);
        private:

            // stat
            int _level = 1;

            //info stock for integration
            std::unordered_map<std::string, int> _inventory = {{"linemate", 0}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}};
             std::unordered_map<std::string, int> _put_down = {{"linemate", 0}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}};
            std::unordered_map<std::string, int> _needs = {{"linemate", 0}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}};
            int _need = 0;
            
            bool _is_evolving = false;
            bool _locked = false;
            bool _turned = false;
            int _x = 0;
            int _y = 0;

            std::string _receive;
            Commands::Objects _obj_lock;

            ParseurClass _parsemanager;
            Commands::CommandManager _cmdmanager;

            //IA Engine
            MoveEnum _next_move = MoveEnum::LOOK;

            std::unordered_map<std::string, int> level2 = {{"linemate", 1}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}, {"player", 1}};
            std::unordered_map<std::string, int> level3 = {{"linemate", 1}, {"deraumere", 1}, {"sibur", 1}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}, {"player", 2}};
            std::unordered_map<std::string, int> level4 = {{"linemate", 2}, {"deraumere", 0}, {"sibur", 1}, {"mendiane", 0}, {"phiras", 2}, {"thystame", 0}, {"player", 2}};
            std::unordered_map<std::string, int> level5 = {{"linemate", 1}, {"deraumere", 1}, {"sibur", 2}, {"mendiane", 0}, {"phiras", 1}, {"thystame", 0}, {"player", 4}};
            std::unordered_map<std::string, int> level6 = {{"linemate", 1}, {"deraumere", 2}, {"sibur", 1}, {"mendiane", 3}, {"phiras", 0}, {"thystame", 0}, {"player", 4}};
            std::unordered_map<std::string, int> level7 = {{"linemate", 1}, {"deraumere", 2}, {"sibur", 3}, {"mendiane", 0}, {"phiras", 1}, {"thystame", 0}, {"player", 6}};
            std::unordered_map<std::string, int> level8 = {{"linemate", 2}, {"deraumere", 2}, {"sibur", 2}, {"mendiane", 2}, {"phiras", 2}, {"thystame", 1}, {"player", 6}};
            std::vector<std::pair<int, int>> _vision = {{0, 0}, {1, 3}, {4, 8}, {9, 15}, {16, 24}, {25, 36}, {37, 51}, {52, 69}, {70, 90}};
    };
}
/*
std::unordered_map<std::string, int> level2 = {{"linemate", 1}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}, {"player", 1}};
std::unordered_map<std::string, int> level3 = {{"linemate", 1}, {"deraumere", 1}, {"sibur", 1}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}, {"player", 2}};
std::unordered_map<std::string, int> level4 = {{"linemate", 2}, {"deraumere", 0}, {"sibur", 1}, {"mendiane", 0}, {"phiras", 2}, {"thystame", 0}, {"player", 2}};
std::unordered_map<std::string, int> level5 = {{"linemate", 1}, {"deraumere", 1}, {"sibur", 2}, {"mendiane", 0}, {"phiras", 1}, {"thystame", 0}, {"player", 4}};
std::unordered_map<std::string, int> level6 = {{"linemate", 1}, {"deraumere", 2}, {"sibur", 1}, {"mendiane", 3}, {"phiras", 0}, {"thystame", 0}, {"player", 4}};
std::unordered_map<std::string, int> level7 = {{"linemate", 1}, {"deraumere", 2}, {"sibur", 3}, {"mendiane", 0}, {"phiras", 1}, {"thystame", 0}, {"player", 6}};
std::unordered_map<std::string, int> level8 = {{"linemate", 2}, {"deraumere", 2}, {"sibur", 2}, {"mendiane", 2}, {"phiras", 2}, {"thystame", 1}, {"player", 6}};
*/
#endif /* !IA_HPP_ */
