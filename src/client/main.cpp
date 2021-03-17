/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include <sstream>
#include <memory>
#include "SocketHandle.hpp"
#include "IA.hpp"
#include "GUI.hpp"

void usage(void)
{
    printf("USAGE:  ./zappy_ai -p port -n name -h machine\n");
    printf("\tport\tis the port number\n");
    printf("\tname\tis the name of the team\n");
    printf("\tmachine\tis the name of the machine; localhost by default\n");
}

int loop_graphic(int serv_port, const char *ip, const char *name)
{
    std::string _ip = ip;
    std::string _name = name;
    std::string result;
    SocketHandle sock(_ip, serv_port, _name);
    gui::GUI gui(800, 600, sock);

    while(gui.isOpen())
    {
        std::string buffer = sock.run();
        if (!buffer.empty()) {
            std::cout << buffer << std::endl;
        }

        gui.readServerResponse(buffer);
        gui.update();

        buffer.clear();
    }
    return 0;
}

int loop_shell() {
    std::string line;
    std::string result;
    IA::IA ia;

    while(1) {
        std::getline(std::cin, line);
        if (!line.empty()) {
            std::cout << "Server Say : " << line << std::endl;
            if (line.compare("dead") == 0)
                break;
            ia.update(line);
            line.clear();

            result = ia.next_move();
            std::cout << "Got : " << result << std::endl;
        }
    }
    return 0;
}

int loop_ai(int serv_port, const char *ip, const char *name)
{
    std::string _ip = ip;
    std::string _name = name;
    std::string result;

    std::string buffer;

    SocketHandle sock(_ip, serv_port, _name);
    IA::IA ia;

    while(1) {
        buffer.clear();
        buffer = sock.run();
        if (!buffer.empty()) {
            std::cout << "\033[1;31mReceived >> \033[0m" << buffer << std::endl;
            if (buffer.compare("dead") == 0)
                break;
            ia.update(buffer);
            buffer.clear();

            result = ia.next_move();
            std::cout << "\033[1;31mCommand  >> \033[0m" << result << std::endl;
            sock.write_socket(result);
        }
    }
    return 0;
}

int check_ai_or_graph(int serv_port, const char *ip, const char *name)
{
    if (strcmp(name, "GRAPHIC") == 0)
        return loop_graphic(serv_port, ip, name);
    else
        return loop_ai(serv_port, ip, name);
}

int main(int argc, char **argv)
{
    int serv_port = 0;
    char *name = NULL;
    char *machine = NULL;

    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        usage();
        return 0;
    }
    if (argc != 5 && argc != 7) {
        usage();
        return 84;
    }
    if (strcmp(argv[1], "-p") == 0)
        serv_port = atoi(argv[2]);
    else {
        usage();
        return 84;
    }
    if (serv_port <= 0 || serv_port > 65535) {
        std::cout << "Port must be between 1 and 65535\n" << std::endl;
        return 84;
    }
    if (strcmp(argv[3], "-n") == 0 && argv[4][0] != '-')
        name = argv[4];
    if (!name) {
        usage();
        return 84;
    }
    if (argc == 7 && strcmp(argv[5], "-h") == 0)
        machine = argv[6];
    else if (argc == 5)
        return check_ai_or_graph(serv_port, "127.0.0.1", name);
    else {
        usage();
        return 84;
    }

    return check_ai_or_graph(serv_port, machine, name);
}