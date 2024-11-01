//
// Created by Daria Kuznetsova on 31.10.2024.
//

#include "NumberGeneration.h"
#include "random"

std::random_device NumberGeneration::rand;
std::mt19937 NumberGeneration::gen(NumberGeneration::rand());

size_t NumberGeneration::generateRandomNumber(size_t min, size_t max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

size_t NumberGeneration::generateRandomOddNumber(size_t min, size_t max) {
    if (min % 2 == 0) {
        min++;
    }

    if (max % 2 == 0) {
        max--;
    }

    if (min > max) {
        std::swap(min, max);
    }

    std::uniform_int_distribution<> dis(0, (max - min) / 2);
    return dis(gen) * 2 + min;
}
