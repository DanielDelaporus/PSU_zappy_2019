/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019 [WSL: Ubuntu]
** File description:
** parseur cpp file
*/

#include "../../include/client/Parseur.hpp"

ParseurClass::ParseurClass() {}

ParseurClass::~ParseurClass() {}

void ParseurClass::readoutput(std::vector<std::vector<std::string>> input)
{
    for (std::size_t i = 0; i < input.size(); i++) {
        std::cout << "Tile " << i << std::endl;
        for (std::size_t j = 0; j < input[i].size(); j++)
            std::cout << input[i][j] << std::endl;
    }
}

std::vector<std::vector<std::string>> ParseurClass::parse(std::string input)
{
    std::vector<std::vector<std::string>> output;

    input.erase(0, 1);
    input.erase(input.length() - 1, 1);

    std::istringstream iss(input);

    std::string result;
    std::string subresult;

    int i = 0;
    
    while (std::getline(iss, result, ',')) {
        subresult = result;
        std::istringstream iss2(subresult);
        std::vector<std::string> suboutput;

        while (std::getline(iss2, subresult, ' '))
            if (!subresult.empty())
                suboutput.insert(suboutput.end(), subresult);
        output.insert(output.end(), suboutput);
        i++;
    }
    return output;
}