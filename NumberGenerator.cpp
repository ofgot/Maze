//
// Created by Daria Kuznetsova on 31.10.2024.
//

#include "NumberGenerator.h"
#include "random"

std::random_device NumberGenerator::rand;
std::mt19937 NumberGenerator::gen(NumberGenerator::rand());

size_t NumberGenerator::generateRandomNumber(size_t min, size_t max) {
    std::uniform_int_distribution<> dis(static_cast<int>(min), static_cast<int>(max));
    return dis(gen);
}

size_t NumberGenerator::generateRandomOddNumber(size_t min, size_t max) {
    if (min % 2 == 0) {
        min++;
    }

    if (max % 2 == 0) {
        max--;
    }

    if (min > max) {
        std::swap(min, max);
    }

    std::uniform_int_distribution<> dis(0, static_cast<int>(max - min) / 2);
    return dis(gen) * 2 + min;
}
