/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** GUI
*/

#include <algorithm>
#include "GUI.hpp"

gui::GUI::GUI(unsigned int width, unsigned int height, SocketHandle &socket)
: _sock(socket), _window(sf::VideoMode(width, height), "Zappy - GUI"), _map_loaded(false), _moving(false)
{
    _background_texture.loadFromFile("assets/background_tile.png");
    _food_texture.loadFromFile("assets/food.png");
    _linemate_texture.loadFromFile("assets/linemate.png");
    _deraumere_texture.loadFromFile("assets/deraumere.png");
    _sibur_texture.loadFromFile("assets/sibur.png");
    _mendiane_texture.loadFromFile("assets/mendiane.png");
    _phiras_texture.loadFromFile("assets/phiras.png");
    _thystame_texture.loadFromFile("assets/thystame.png");

    _player_texture.loadFromFile("assets/player.png");

    _info_bubble_texture.loadFromFile("assets/info_bubble.png");
    _font.loadFromFile("assets/roboto.ttf");
}

gui::GUI::~GUI()
{}

void gui::GUI::initialize() const
{
    sendServerRequest("msz");
    sleep(0.01);
    sendServerRequest("mct");
}

void gui::GUI::update()
{
    if (!_map_loaded) {
        initialize();
    }

    handleWindowEvent();

    _window.clear(sf::Color::Black);

    for (auto &&tile : _map.tiles)
    {
        _window.draw(tile.sprite);
        for (auto &&resource : tile.resources.sprite_map)
        {
            _window.draw(resource.second);
        }
    }
    for (auto &&player : _players)
    {
        _window.draw(player.sprite);
    }
    _window.draw(_info.sprite);
    _window.draw(_info.text);

    _window.display();
}

void gui::GUI::readServerResponse(std::string &server_resp)
{
    std::queue<std::string> cmd_queue = split_str(server_resp, "\n");

    while (!cmd_queue.empty() && !cmd_queue.front().empty())
    {
        std::queue<std::string> cmd_line = split_str(cmd_queue.front(), " ");
        std::string cmd = cmd_line.front();
        cmd_line.pop();
        unsigned int argc = 0;

        if (cmd == "msz")
        {
            argc = 2;
            setMapSize(getCmdArg(cmd_line, argc), argc);
        }
        else if (cmd == "bct")
        {
            argc = 9;
            setTileContent(getCmdArg(cmd_line, argc), argc);
        }
        else if (cmd == "pnw")
        {
            argc = 5;
            addNewPlayer(getCmdArg(cmd_line, argc), argc, cmd_line.front());
        }
        else if (cmd == "ppo")
        {
            argc = 4;
            setPlayerPosition(getCmdArg(cmd_line, argc), argc);
        }
        else if (cmd == "pdi")
        {
            argc = 1;
            killPlayer(getCmdArg(cmd_line, argc), argc);
        }

        cmd_queue.pop();
    }
}

void gui::GUI::sendServerRequest(std::string request) const
{
    _sock.write_socket(request);
}

void gui::GUI::handleWindowEvent()
{
    sf::Event event;
    sf::View view(_window.getView());
    while (_window.pollEvent(event))
    {
        const sf::Vector2f newPos = _window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
        switch (event.type)
        {
        case sf::Event::Closed:
            _window.close();
            break;

        case sf::Event::Resized:
            _window.setView(sf::View(visibleArea));
            break;

        case sf::Event::MouseButtonPressed:
            if (!_map_loaded) break;
            if (event.mouseButton.button == sf::Mouse::Button::Right) {
                _moving = true;
                _old_pos = _window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            } else if (event.mouseButton.button == sf::Mouse::Button::Left) {
                displayInfo(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)));
            } else if (event.mouseButton.button == sf::Mouse::Middle) {
                displayInfo(sf::Vector2f(-1, -1));
            }
            break;

        case sf::Event::MouseButtonReleased:
            if (!_map_loaded) break;
            if (event.mouseButton.button == sf::Mouse::Button::Right) {
                _moving = false;
            }
            break;

        case sf::Event::MouseMoved:
            if (!_map_loaded) break;
            if (!_moving)
                break;
            view.move(_old_pos - newPos);
            _window.setView(view);
            _old_pos = _window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            break;

        case sf::Event::MouseWheelScrolled:
            if (!_map_loaded) break;
            if (_moving)
                break;
            if (event.mouseWheelScroll.delta < 0) {
                view.zoom(1.1f);
            } else {
                view.zoom(0.9f);
            }
            _window.setView(view);
            break;

        default:
            break;
        }
    }
}

void gui::GUI::displayInfo(const sf::Vector2f cursor_pos)
{
    unsigned int factor = _map.tiles.front().sprite.getGlobalBounds().width;
    unsigned int pos_x = static_cast<unsigned int>(cursor_pos.x) / factor;
    unsigned int pos_y = static_cast<unsigned int>(cursor_pos.y) / factor;
    auto tile_it = std::find_if(_map.tiles.begin(), _map.tiles.end(),
        [pos_x, pos_y](auto const &t){ return t.x == pos_x && t.y == pos_y; });

    if (tile_it == std::end(_map.tiles)) {
        _info.sprite.setColor(sf::Color::Transparent);
        _info.text.setString("");
        return;
    }

    unsigned int size = 200;
    _info.sprite.setTexture(_info_bubble_texture);
    _info.sprite.setTextureRect(sf::IntRect(0, 0, size, size));
    _info.sprite.setPosition(pos_x * factor, pos_y * factor);
    _info.sprite.setColor(sf::Color(255, 255, 255, 200));

    _info.text.setFont(_font);
    _info.text.setCharacterSize(12);
    std::string text = "X: " + std::to_string(pos_x) + "  Y: " + std::to_string(pos_y) + "\t\t\t\tegg: " + std::to_string(tile_it->egg)
        + "\n\nfood: " + std::to_string(tile_it->resources.food) + "\t\t\t\t\tthystame: " + std::to_string(tile_it->resources.thystame)
        + "\n\nlinemate: " + std::to_string(tile_it->resources.linemate) + "\n\nderaumere: " + std::to_string(tile_it->resources.deraumere)
        + "\n\nsibur: " + std::to_string(tile_it->resources.sibur) + "\n\nmendiane: " + std::to_string(tile_it->resources.mendiane)
        + "\n\nphiras: " + std::to_string(tile_it->resources.phiras) + "\n";
    _info.text.setString(text);
    _info.text.setPosition(_info.sprite.getPosition() + sf::Vector2f(10, 10));
}

void gui::GUI::displayInfo(const sf::Vector2f cursor_pos, Player &player)
{
    unsigned int factor = _map.tiles.front().sprite.getGlobalBounds().width;
    unsigned int pos_x = static_cast<unsigned int>(cursor_pos.x) / factor;
    unsigned int pos_y = static_cast<unsigned int>(cursor_pos.y) / factor;

    unsigned int size = 200;
    _info.sprite.setTexture(_info_bubble_texture);
    _info.sprite.setTextureRect(sf::IntRect(0, 0, size, size));
    _info.sprite.setPosition(pos_x * factor, pos_y * factor);
    _info.sprite.setColor(sf::Color(255, 255, 255, 200));

    _info.text.setFont(_font);
    _info.text.setCharacterSize(12);
    std::string text = "X: " + std::to_string(pos_x) + "  Y: " + std::to_string(pos_y) + "\t\t\t\tnumber: " + std::to_string(player.number)
        + "\n\nfood: " + std::to_string(player.resources.food) + "\tteam: " + std::to_string(player.orientation)
        + "\n\nlinemate: " + std::to_string(player.resources.linemate) + "\tlevel: " + std::to_string(player.level)
        + "\n\nderaumere: " + std::to_string(player.resources.deraumere) + "\torientation: " + ORIENTATION[player.orientation]
        + "\n\nsibur: " + std::to_string(player.resources.sibur) + "\n\nmendiane: " + std::to_string(player.resources.mendiane)
        + "\n\nphiras: " + std::to_string(player.resources.phiras) + "\tthystame: " + std::to_string(player.resources.thystame) + "\n";
    _info.text.setString(text);
    _info.text.setPosition(_info.sprite.getPosition() + sf::Vector2f(10, 10));
}

void gui::GUI::setMapSize(std::vector<unsigned int> argv, unsigned int argc)
{
    if (argv.size() < argc)
    {
        printf("GUI: setMapSize: Wrong number of argument passed. (Got: %lu, Expected: %u)\n", argv.size(), argc);
        exit(84);
    }

    _map.width = argv[0];
    _map.height = argv[1];

    for (unsigned int i = 0; i < _map.width; i++)
    {
        for (unsigned int j = 0; j < _map.height; j++)
        {
            Tile tile = {i, j,
                {0, 0, 0, 0, 0, 0, 0, std::unordered_map<unsigned int, sf::Sprite>()},
                0, sf::Sprite(_background_texture)
            };

            tile.sprite.setPosition(i * tile.sprite.getGlobalBounds().width,
                j * tile.sprite.getGlobalBounds().height);

            _map.tiles.push_back(tile);
        }
    }
    _map_loaded = true;
}

void gui::GUI::setTileContent(std::vector<unsigned int> argv, unsigned int argc)
{
    if (argv.size() < argc)
    {
        printf("GUI: setTileContent: Wrong number of argument passed. (Got: %lu, Expected: %u)\n", argv.size(), argc);
        return;
    }

    unsigned int x = argv[0];
    unsigned int y = argv[1];

    auto tile_it = std::find_if(_map.tiles.begin(), _map.tiles.end(), 
        [x, y](auto const &t){ return t.x == x && t.y == y; });

    if (tile_it != std::end(_map.tiles)) {
        tile_it->resources.food = argv[2];
        tile_it->resources.linemate = argv[3];
        tile_it->resources.deraumere = argv[4];
        tile_it->resources.sibur = argv[5];
        tile_it->resources.mendiane = argv[6];
        tile_it->resources.phiras = argv[7];
        tile_it->resources.thystame = argv[8];
    }
    else
    {
        printf("GUI: setTileContent: No tile found at position (%u, %u)", x ,y);
        return;
    }
    
    auto addSprite = [x, y, tile_it](const unsigned int &res_id, const unsigned int &res_qte, const sf::Texture &texture) {
        if (res_qte > 0) {
            sf::Sprite sprite(texture);
            sprite.setPosition(x * sprite.getGlobalBounds().width, y * sprite.getGlobalBounds().height);
            tile_it->resources.sprite_map.insert({res_id, sprite});
        }
    };
    tile_it->resources.sprite_map.clear();
    addSprite(0, tile_it->resources.food, _food_texture);
    addSprite(1, tile_it->resources.linemate, _linemate_texture);
    addSprite(2, tile_it->resources.deraumere, _deraumere_texture);
    addSprite(3, tile_it->resources.sibur, _sibur_texture);
    addSprite(4, tile_it->resources.mendiane, _mendiane_texture);
    addSprite(5, tile_it->resources.phiras, _phiras_texture);
    addSprite(6, tile_it->resources.thystame, _thystame_texture);
}

void gui::GUI::addNewPlayer(std::vector<unsigned int> argv, unsigned int argc, std::string &team)
{
    if (argv.size() < argc)
    {
        printf("GUI: addNewPlayer: Wrong number of argument passed. (Got: %lu, Expected: %u)\n", argv.size(), argc);
        return;
    }

    unsigned int x = argv[1];
    unsigned int y = argv[2];
    Player player = {argv[0], x, y, argv[3], argv[4], team,
        {10, 0, 0, 0, 0, 0, 0, std::unordered_map<unsigned int, sf::Sprite>()},
        sf::Sprite(_player_texture)
    };

    player.sprite.setPosition(x * player.sprite.getGlobalBounds().width, y * player.sprite.getGlobalBounds().height);
    _players.push_back(player);
}

void gui::GUI::setPlayerPosition(std::vector<unsigned int> argv, unsigned int argc)
{
    if (argv.size() < argc)
    {
        printf("GUI: setPlayerPosition: Wrong number of argument passed. (Got: %lu, Expected: %u)\n", argv.size(), argc);
        return;
    }

    unsigned int pl_nbr = argv[0];
    unsigned int x = argv[1];
    unsigned int y = argv[2];
    unsigned int rot = argv[3];

    auto pl_it = std::find_if(_players.begin(), _players.end(),
        [pl_nbr](const auto &pl) { return pl.number == pl_nbr; }
    );
    if (pl_it != _players.end()) {
        pl_it->x = x;
        pl_it->y = y;
        pl_it->orientation = rot;
        pl_it->sprite.setPosition(x * pl_it->sprite.getGlobalBounds().width, y * pl_it->sprite.getGlobalBounds().height);
    }
}

void gui::GUI::killPlayer(std::vector<unsigned int> argv, unsigned int argc)
{
    if (argv.size() < argc)
    {
        printf("GUI: killPlayer: Wrong number of argument passed. (Got: %lu, Expected: %u)\n", argv.size(), argc);
        return;
    }

    unsigned int pl_nbr = argv[0];
    auto pl_it = std::find_if(_players.begin(), _players.end(),
        [pl_nbr](const auto &pl) { return pl.number == pl_nbr; }
    );
    pl_it->sprite.setColor(sf::Color::Transparent);
    _players.erase(pl_it);
}

bool gui::GUI::isOpen() const
{
    return _window.isOpen();
}


std::queue<std::string> gui::GUI::split_str(std::string &str, std::string delimiter) const
{
    std::queue<std::string> queue;

    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        queue.push(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    if (!str.empty()) {
        queue.push(str);
        str.clear();
    }
    return queue;
}

const std::vector<unsigned int> gui::GUI::getCmdArg(std::queue<std::string> &argq, unsigned int expected_argc) const
{
    std::vector<unsigned int> arg;

    if (argq.size() < expected_argc)
    {
        printf("GUI: getCmdArg: the queue doesn't contain the expected number of argument (queue size: %lu, expected size: %u)\n", argq.size(), expected_argc);
        return arg;
    }

    for (size_t i = 0; i < expected_argc; i++)
    {
        arg.push_back(std::stoul(argq.front()));
        argq.pop();
    }
    return arg;
}
