//
// Created by Daria Kuznetsova on 31.10.2024.
//

#ifndef MAZE_NUMBERGENERATION_H
#define MAZE_NUMBERGENERATION_H
#include "iostream"
#include "random"

class NumberGeneration {
public:
    static std::random_device rand;
    static std::mt19937 gen;

    static size_t generateRandomNumber(size_t min, size_t max);
    static size_t generateRandomOddNumber(size_t min, size_t max);
};


#endif //MAZE_NUMBERGENERATION_H