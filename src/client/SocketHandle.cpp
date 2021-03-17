/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** SocketHandle
*/

#include <sys/time.h>
#include "../../include/client/SocketHandle.hpp"

SocketHandle::SocketHandle(std::string &ip, int port, std::string &name)
{
    struct hostent *he = new hostent;
    _listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_listenfd < 0) {
        std::cerr << "Socket Error\n" << std::endl;
        exit (84);
    }
    std::memset(&_serv_addr, '0', sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_port = htons(port);
    std::cout << ip << std::endl;
    if ((he = gethostbyname(ip.data())) != NULL)
    {
        memcpy(&_serv_addr.sin_addr, he->h_addr_list[0], he->h_length);
    } else if (inet_pton(AF_INET, ip.data(), &_serv_addr.sin_addr) <= 0) {
        std::cerr << "IP not correct\n" << std::endl;
        exit (84);
    }
    if (connect(_listenfd, (struct sockaddr *) &_serv_addr,
        sizeof(_serv_addr)) < 0) {
        std::cerr << "Error while connecting to server\n" << std::endl;
        exit (84);
    }

    FD_ZERO(&_rfds_stdin);
    FD_ZERO(&_write_fd);
    FD_SET(_listenfd, &_rfds_stdin);
    FD_SET(_listenfd, &_write_fd);
    read_output();
    _buffer = "";
    dprintf(_listenfd, "%s\n", name.data());
}

SocketHandle::~SocketHandle()
{
    read_output();
}

std::string SocketHandle::run()
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 50;
    _buffer = "";
    fd_set _rfds_set = _rfds_stdin;
    _write_set = _write_fd;
    int reader_sel = select(_listenfd + 1, &_rfds_set,
        &_write_set, NULL, &tv);
    if (reader_sel < 0)
        std::cerr << "select failed\n " << std::endl;
    if (reader_sel > 0) {
        if (FD_ISSET(_listenfd, &_rfds_set))
            read_output();
    }
    return _buffer;
}

int SocketHandle::read_output()
{
    int reader;
    char buffer[10000];
    memset(buffer, '\0', 10000);

    do {
        reader = read(_listenfd, buffer, sizeof(buffer));
        if (reader > 0) {
            buffer[reader] = 0;
            _buffer += buffer;
            memset(buffer, '\0', 10000);
        } else if (reader == 0) {
            std::cout << "Connection closed by foreign host.\n";
            exit (0);
        } else {
            std::cerr << "Error while reading data.\n";
            exit(84);
        }
    } while (reader == sizeof(buffer));
    return 0;
}

int SocketHandle::write_socket(std::string &buf)
{
    if (FD_ISSET(_listenfd, &_write_set)) {
            dprintf(_listenfd, "%s\n", buf.data());
        return 0;
    }
    return 84;
}