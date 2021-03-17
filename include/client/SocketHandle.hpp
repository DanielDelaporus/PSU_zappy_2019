/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** SocketHandle
*/

#ifndef SOCKETHANDLE_HPP_
#define SOCKETHANDLE_HPP_

#include <iostream>
#include <cstring>

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

class SocketHandle {
    public:
        SocketHandle(std::string &ip, int port, std::string &);
        ~SocketHandle();

        std::string run();
        int write_socket(std::string &buf);

    protected:
        int read_output();
    private:
        int _listenfd;
        struct sockaddr_in _serv_addr;
        std::string _buffer;
        fd_set _rfds_stdin;
        fd_set _write_fd;
        fd_set _write_set;
};

#endif /* !SOCKETHANDLE_HPP_ */
