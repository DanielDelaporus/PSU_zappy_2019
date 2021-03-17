/*
** EPITECH PROJECT, 2020
** 
** File description:
** 
*/

#include "../../include/client/IA.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

IA::IA::IA(): _cmdmanager(Commands::CommandManager())
{}

IA::IA::~IA()
{}

void IA::IA::IA::update(std::string receive)
{
    if (receive[0] == 'o' && receive[1] == 'k') {
        if (_next_move == GET) {
            _next_move = INVENTORY;
            return;
        }
    }
    if (receive[0] == 'k' && receive[1] == 'o') {
        _next_move = LOOK;
        return;
    }
    if (_is_evolving) {
        set_down_evolve();
        return;
    }
    if (_next_move == MoveEnum::EVOLVE) {
        _next_move = LOOK;
        return;
    }
    if (_next_move == MoveEnum::INVENTORY) {
        update_inventory(_parsemanager.parse(receive));
        if (Can_LevelupInv()) {
            _is_evolving = true;
            return;
        }
        _next_move = LOOK;
        return;
    }
    if ((_next_move == MoveEnum::FORWARD || _next_move == MoveEnum::RIGHT || _next_move == MoveEnum::LEFT) && _locked == false) {
        _next_move = LOOK;
        return;
    }
    if (_next_move == MoveEnum::LOOK) {
        find_need();
        if (need_object_inView(_parsemanager.parse(receive))) {
            _locked = true;
            std::cout << "\033[1;33mDebug    >> \033[0m" << "Locked on tile with dx = " << _x << " and dy = " << _y << std::endl;
        }
        else {
            srand(time(NULL));
            int r = rand() % 5 + 1;
            if (r == 1)
                _next_move = RIGHT;
            else if (r == 2)
                _next_move = LEFT;
            else
                _next_move = FORWARD;
            return;
        }
    }
    if (_locked && _x == 0 && _y == 0) {
        _locked = false;
        _next_move = GET;
        return;
    }
    if (_locked) {
        if (_x != 0) {
            _next_move = FORWARD;
            _x--;
            return;
        }
        if (_y != 0 && _turned == false) {
            if (_y > 0) {
                _next_move = RIGHT;
                _turned = true;
            }
            else {
                _next_move = LEFT;
                _turned = true;
            }
        }
        _x = abs(_y);
        _y = 0;
        _turned = false;
        return;
    }
}
void IA::IA::set_down_evolve()
{
    std::unordered_map<std::string, int> level;

    if (_level == 1)
        level = level2;
    if (_level == 2)
        level = level3;
    if (_level == 3)
        level = level4;
    if (_level == 4)
        level = level5;
    if (_level == 5)
        level = level6;
    if (_level == 6)
        level = level7;
    if (_level == 7)
        level = level8;
    
    if (level["linemate"] > _put_down["linemate"]) {
        _next_move = SET;
        _obj_lock = Commands::linemate;
        _inventory["linemate"] -= 1;
        _put_down["linemate"] += 1;
        return;
    } else if (level["deraumere"] > _put_down["deraumere"]) {
        _next_move = SET;
        _obj_lock = Commands::deraumere;
        _inventory["deraumere"] -= 1;
        _put_down["deraumere"] += 1;
        return;
    } else if (level["sibur"] > _put_down["sibur"]) {
        _next_move = SET;
        _obj_lock = Commands::sibur;
        _inventory["sibur"] -= 1;
        _put_down["sibur"] += 1;
        return;
    } else if (level["mendiane"] > _put_down["mendiane"]) {
        _next_move = SET;
        _obj_lock = Commands::mendiane;
        _inventory["mendiane"] -= 1;
        _put_down["sibur"] += 1;
        return;
    } else if (level["phiras"] > _put_down["phiras"]) {
        _next_move = SET;
        _obj_lock = Commands::phiras;
        _inventory["phiras"] -= 1;
        _put_down["sibur"] += 1;
        return;
    } else if (level["thystame"] > _put_down["thystame"]) {
        _next_move = SET;
        _obj_lock = Commands::thystame;
        _inventory["thystame"] -= 1;
        _put_down["thystame"] += 1;
        return;
    } else {
        _next_move = EVOLVE;
        _is_evolving = false;
        return;
    }
}

bool IA::IA::need_object_inView(std::vector<std::vector<std::string>> view)
{
    for (size_t f = 0; f < view[0].size(); f++) {
        if (view[0][f] == "food") {
            _obj_lock = Commands::food;
            _x = getX(0);
            _y = getY(0);
            return (true);
        }
    }
    for (size_t i = 0; i < view.size(); i++) {
        for (size_t j = 0; j < view[i].size(); j++) {
            if (isNeeded(view[i][j])) {
                _x = getX(i);
                _y = getY(i);
                return (true);
            }
        }
    }
    return (false);
}

int IA::IA::getX(int pos)
{
    size_t i = 0;

    for (; i < _vision.size(); i++) {
        if (pos <= _vision[i].second)
            return (i);
    }
    std::cout << "ERROR" << std::endl;
    return (i);
}

int IA::IA::getY(int pos)
{
    pos -= _vision[_x].first;

    return (pos - _x);
}

bool IA::IA::isNeeded(std::string obj)
{
    int _dif = _need;

    if (_dif >= 32) {
        if (obj.compare("thystame") == 0) {
            _obj_lock = Commands::thystame;
            return (true);
        }
        _dif -= 32;
    }
    if (_dif >= 16) {
        if (obj.compare("phiras") == 0) {
            _obj_lock = Commands::phiras;
            return (true);
        }
        _dif -= 16;
    }
    if (_dif >= 8) {
        if (obj.compare("mendiane") == 0) {
            _obj_lock = Commands::mendiane;
            return (true);
        }
        _dif -= 8;
    }
    if (_dif >= 4) {
        if (obj.compare("sibur") == 0) {
            _obj_lock = Commands::sibur;
            return (true);
        }
        _dif -= 4;
    }
    if (_dif >= 2) {
        if (obj.compare("deraumere") == 0) {
            _obj_lock = Commands::deraumere;
            return (true);
        }
        _dif -= 2;
    }
    if (_dif >= 1) {
        if (obj.compare("linemate") == 0) {
            _obj_lock = Commands::linemate;
            return (true);
        }
        _dif -= 1;
    }
    return false;
}

void IA::IA::Lock()
{
    if (_x > 0)
        _next_move = MoveEnum::FORWARD;
    else if (_y > 0) {
        _next_move = MoveEnum::RIGHT;
        _x = _y;
    } else if (_y < 0) {
        _next_move = MoveEnum::LEFT;
        _x = abs(_y);
    }
}

std::string IA::IA::next_move()
{
    if (_next_move == MoveEnum::FORWARD)
        return _cmdmanager.command(Commands::FORWARD);
    if (_next_move == MoveEnum::RIGHT)
        return _cmdmanager.command(Commands::RIGHT);
    if (_next_move == MoveEnum::LEFT)
        return _cmdmanager.command(Commands::LEFT);
    if (_next_move == MoveEnum::LOOK)
        return _cmdmanager.command(Commands::LOOK);
    if (_next_move == MoveEnum::BROADCAST_EVOLVE)
        return _cmdmanager.command(Commands::BROADCAST_EVOLVE);
    if (_next_move == MoveEnum::EVOLVE)
        return _cmdmanager.command(Commands::START_LEVEL_UP);
    if (_next_move == MoveEnum::GET)
        return _cmdmanager.command(Commands::TAKE, _obj_lock);
    if (_next_move == MoveEnum::SET)
        return _cmdmanager.command(Commands::SET, _obj_lock);
    if (_next_move == MoveEnum::INVENTORY)
        return _cmdmanager.command(Commands::INVENTORY);
    return "ERROR";
}

bool IA::IA::Need_Ressource()
{
    if (_need != 0)
        return (true);
    return (false);
}

bool IA::IA::Can_LevelupInv()
{
    if (_level == 1) {
        return (compare(level2));
    } else if (_level == 2) {
        return (compare(level3));
    } else if (_level == 3) {
        return (compare(level4));
    } else if (_level == 4) {
        return (compare(level5));
    } else if (_level == 5) {
        return (compare(level6));
    } else if (_level == 6) {
        return (compare(level7));
    } else if (_level == 7) {
        return (compare(level8));
    }
    return false;
}

bool IA::IA::compare(std::unordered_map<std::string, int> level)
{
    if ((_inventory["linemate"] >= level["linemate"]) &&
        (_inventory["deraumere"] >= level["deraumere"]) &&
        (_inventory["sibur"] >= level["sibur"]) &&
        (_inventory["mendiane"] >= level["mendiane"]) &&
        (_inventory["phiras"] >= level["phiras"]) &&
        (_inventory["thystame"] >= level["thystame"]))
            return true;
    return (false);
}

void IA::IA::find_need()
{
    std::unordered_map<std::string, int> level;
    _need = 0;

    if (_level == 1)
        level = level2;
    else if (_level == 2)
        level = level3;
    else if (_level == 3)
        level = level4;
    else if (_level == 4)
        level = level5;
    else if (_level == 5)
        level = level6;
    else if (_level == 6)
        level = level7;
    else if (_level == 7)
        level = level8;

    if (_inventory["linemate"] < level["linemate"])
        _need += 1;
    if (_inventory["deraumere"] < level["deraumere"])
        _need += 2;
    if (_inventory["sibur"] < level["sibur"]) 
        _need += 4;
    if (_inventory["mendiane"] < level["mendiane"])
        _need += 8;
    if (_inventory["phiras"] < level["phiras"])
        _need += 16;
    if (_inventory["thystame"] < level["thystame"])
        _need += 32;
}

void IA::IA::Evolve()
{
    _receive = _cmdmanager.command(Commands::ClientCommands(5), _level);
}

std::unordered_map<std::string, int> sub(std::unordered_map<std::string, int> inv, std::unordered_map<std::string, int> level)
{
    inv["linemate"] -= level["linemate"];
    inv["deraumere"] -= level["deraumere"];
    inv["sibur"] -= level["sibur"];
    inv["mendiane"] -= level["mendiane"];
    inv["phiras"] -= level["phiras"];
    inv["thystame"] -= level["thystame"];
    return (inv);
}

void IA::IA::Level_up()
{
    if (_level == 1) {
        //send level up if ok
        _receive = _cmdmanager.command(Commands::ClientCommands(8));
        _inventory = sub(_inventory, level2);
    } else if (_level == 2) {
        //send level up if ok
        _receive = _cmdmanager.command(Commands::ClientCommands(8));
        _inventory = sub(_inventory, level3);
    } else if (_level == 3) {
        //send level up if ok
        _receive = _cmdmanager.command(Commands::ClientCommands(8));
        _inventory = sub(_inventory, level4);
    } else if (_level == 4) {
        //send level up if ok
        _receive = _cmdmanager.command(Commands::ClientCommands(8));
        _inventory = sub(_inventory, level5);
    } else if (_level == 5) {
        //send level up if ok
        _receive = _cmdmanager.command(Commands::ClientCommands(8));
        _inventory = sub(_inventory, level6);
    } else if (_level == 6) {
        //send level up if ok
        _receive = _cmdmanager.command(Commands::ClientCommands(8));
        _inventory = sub(_inventory, level7);
    } else if (_level == 7){
        //send level up if ok
        _receive = _cmdmanager.command(Commands::ClientCommands(8));
        _inventory = sub(_inventory, level8);
    } else {
        std::cout << "already level max" << std::endl;
    }
}

void IA::IA::update_inventory(std::vector<std::vector<std::string>> inv) 
{
    _inventory["linemate"] = std::stoi(inv[1][1]);
    _inventory["deraumere"] = std::stoi(inv[2][1]);
    _inventory["sibur"] = std::stoi(inv[3][1]);
    _inventory["mendiane"] = std::stoi(inv[4][1]);
    _inventory["phiras"] = std::stoi(inv[5][1]);
    _inventory["thystame"] = std::stoi(inv[6][1]);
}

void IA::IA::dump_inventory()
{
    std::cout << "inventory contain :" << std::endl;

    for (auto it = _inventory.begin(); it != _inventory.end(); ++it)
        std::cout << it->first << " " << it->second << std::endl;
}