/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019 [WSL: Ubuntu]
** File description:
** parseur hpp file
*/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#ifndef PARSEUR_HPP_
#define PARSEUR_HPP_

class ParseurClass {
    public:
        ParseurClass();
        ~ParseurClass();
    
        void readoutput(std::vector<std::vector<std::string>>);
        std::vector<std::vector<std::string>> parse(std::string);
    private:
};

#endif