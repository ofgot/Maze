//
// Created by Daria Kuznetsova on 16.12.2024.
//

#ifndef MAZE_SAVELOADGAME_H
#define MAZE_SAVELOADGAME_H

#include <iostream>
#include <vector>
#include "Field.h"
#include "Player.h"

class SaveLoadGame {
public:
    bool saveGameField(const std::string &fileName, const std::vector<std::vector<char>> &field);
    bool loadField(const std::string &fileName, Field &field);
    bool savePLayer(const std::string &fileName, const Field &field, const Player player);
    bool loadPLayer(const std::string &fileName, Player &player, Field &field);
};


#endif //MAZE_SAVELOADGAME_H
