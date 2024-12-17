//
// Created by Daria Kuznetsova on 16.12.2024.
//

#include "SaveLoadGame.h"
#include "fstream"

// Saves the game field to a file in binary format
bool SaveLoadGame::saveGameField(const std::string &fileName, const std::vector<std::vector<char>> &field) {
    try {
        std::string projectRoot = std::__fs::filesystem::current_path().parent_path().string();
        std::ofstream outFile(projectRoot + "/" + fileName, std::ios::binary | std::ios::trunc);

        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for saving: " << fileName << std::endl;
            return false;
        }

        for (const auto &row: field) {
            size_t rowSize = row.size();
            outFile.write(reinterpret_cast<const char *>(&rowSize), sizeof(rowSize));
            outFile.write(row.data(), rowSize);
        }

        std::cout << "Field saved successfully!" << std::endl;
        outFile.close();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error saving game: " << e.what() << std::endl;
        return false;
    }
}

// Loads the game field from a binary file and sets it to the given Field object
bool SaveLoadGame::loadField(const std::string &fileName, Field &field) {
    try {
        std::string projectRoot = std::__fs::filesystem::current_path().parent_path().string();
        std::ifstream inFile(projectRoot + "/savedField.bin", std::ios::binary);

        if (!inFile.is_open()) {
            std::cerr << "Failed to open file for loading: savedField.bin" << std::endl;
            return false;
        }
        if (std::__fs::filesystem::file_size(projectRoot + "/savedField.bin") == 0){
            std::cerr << "File is empty: " << fileName << std::endl;
            return false;
        }

        std::vector<std::vector<char>> fieldData;
        size_t rowSize = 0;
        while (inFile.read(reinterpret_cast<char *>(&rowSize), sizeof(rowSize))) {
            std::vector<char> row(rowSize);
            inFile.read(row.data(), rowSize);
            fieldData.push_back(row);
        }

        field.setField(fieldData);
        inFile.close();
        std::cout << "Field loaded successfully!" << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error loading game: " << e.what() << std::endl;
        return false;
    }
}

// Saves the player's position and field details (size, start, exit positions) to a file in binary format
bool SaveLoadGame::savePLayer(const std::string &fileName, const Field &field, const Player player) {
    try {
        std::string projectRoot = std::__fs::filesystem::current_path().parent_path().string();
        std::ofstream outFile(projectRoot + "/" + fileName, std::ios::binary | std::ios::trunc);

        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for saving: savedField.bin" << std::endl;
            return false;
        }

        size_t x = field.getX();
        size_t y = field.getY();
        size_t startX = field.getStartPosition().getX();
        size_t startY = field.getStartPosition().getY();
        size_t endX = field.getExitPosition().getX();
        size_t endY = field.getExitPosition().getY();
        size_t playerX = player.getX();
        size_t playerY = player.getY();

        outFile.write(reinterpret_cast<const char *>(&x), sizeof(x));
        outFile.write(reinterpret_cast<const char *>(&y), sizeof(y));
        outFile.write(reinterpret_cast<const char *>(&startX), sizeof(startX));
        outFile.write(reinterpret_cast<const char *>(&startY), sizeof(startY));
        outFile.write(reinterpret_cast<const char *>(&endX), sizeof(endX));
        outFile.write(reinterpret_cast<const char *>(&endY), sizeof(endY));

        outFile.write(reinterpret_cast<const char *>(&playerX), sizeof(playerX));
        outFile.write(reinterpret_cast<const char *>(&playerY), sizeof(playerY));

        std::cout << "Data for player and field saved successfully!" << std::endl;
        outFile.close();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error saving game: " << e.what() << std::endl;
        return false;
    }
}

// Loads the player's position and field details (size, start, exit positions) from a file and sets them
bool SaveLoadGame::loadPLayer(const std::string &fileName, Player &player, Field &field) {
    try {
        std::string projectRoot = std::__fs::filesystem::current_path().parent_path().string();
        std::ifstream inFile(projectRoot + "/" + fileName, std::ios::binary);

        if (!inFile.is_open()) {
            std::cerr << "Failed to open file for loading: savedField.bin" << std::endl;
            return false;
        }

        if (std::__fs::filesystem::file_size(projectRoot + "/savedOther.bin") == 0){
            return false;
        }

        size_t x, y, startX, startY, endX, endY, playerX, playerY;

        inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
        inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
        inFile.read(reinterpret_cast<char*>(&startX), sizeof(startX));
        inFile.read(reinterpret_cast<char*>(&startY), sizeof(startY));
        inFile.read(reinterpret_cast<char*>(&endX), sizeof(endX));
        inFile.read(reinterpret_cast<char*>(&endY), sizeof(endY));
        inFile.read(reinterpret_cast<char*>(&playerX), sizeof(playerX));
        inFile.read(reinterpret_cast<char*>(&playerY), sizeof(playerY));

        field.setX(x);
        field.setY(y);
        field.setStartPosition(startX, startY);
        field.setExitPosition(endX, endY);

        player.setPosition(playerX, playerY);

        inFile.close();
        std::cout << "Data for player and field loaded successfully!" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading game: " << e.what() << std::endl;
        return false;
    }
}
