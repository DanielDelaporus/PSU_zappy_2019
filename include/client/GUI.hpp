/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** GUI
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include <queue>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "SocketHandle.hpp"

namespace gui
{
    const std::string ORIENTATION[5] = { "NULL", "NORTH", "EAST", "SOUTH", "WEST" };

    struct Resources
    {
        unsigned int food, linemate, deraumere, sibur, mendiane, phiras, thystame;
        std::unordered_map<unsigned int, sf::Sprite> sprite_map;
    };

    struct Tile
    {
        unsigned int x, y;
        Resources resources;
        unsigned int egg;

        sf::Sprite sprite;
    };

    struct Map
    {
        unsigned int width, height;
        std::vector<Tile> tiles;
    };

    struct Player
    {
        unsigned int number;
        unsigned int x, y;
        unsigned int orientation;
        unsigned int level;
        std::string team;
        Resources resources;

        sf::Sprite sprite;
    };

    struct InfoBubble
    {
        sf::Sprite sprite;
        sf::Text text;
    };

    class GUI
    {
    public:
        GUI(unsigned int width, unsigned int height, SocketHandle &socket);
        ~GUI();

        void initialize() const;
        void update();
        void readServerResponse(std::string &serv_resp);
        void sendServerRequest(std::string request) const;

        bool isOpen() const;

    private:
        void handleWindowEvent();

        void displayInfo(const sf::Vector2f cursor_pos);
        void displayInfo(const sf::Vector2f cursor_pos, Player &player);

        void setMapSize(std::vector<unsigned int> argv, unsigned int argc);
        void setTileContent(std::vector<unsigned int> argv, unsigned int argc);
        void addNewPlayer(std::vector<unsigned int> argv, unsigned int argc, std::string &team);
        void setPlayerPosition(std::vector<unsigned int> argv, unsigned int argc);
        void killPlayer(std::vector<unsigned int> argv, unsigned int argc);

        std::queue<std::string> split_str(std::string &str, std::string delimiter = "\0") const;
        const std::vector<unsigned int> getCmdArg(std::queue<std::string> &argq, unsigned int expected_argc) const;


    private:
        SocketHandle &_sock;
        sf::RenderWindow _window;

        sf::Texture _background_texture;
        sf::Texture _food_texture;
        sf::Texture _linemate_texture;
        sf::Texture _deraumere_texture;
        sf::Texture _sibur_texture;
        sf::Texture _mendiane_texture;
        sf::Texture _phiras_texture;
        sf::Texture _thystame_texture;

        sf::Texture _player_texture;

        sf::Texture _info_bubble_texture;
        sf::Font _font;

        bool _map_loaded;
        bool _moving;
        sf::Vector2f _old_pos;

        gui::Map _map;
        std::vector<Player> _players;
        gui::InfoBubble _info;
    };
} // namespace gui

#endif /* !GUI_HPP_ */
