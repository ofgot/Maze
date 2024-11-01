//
// Created by Daria Kuznetsova on 24.08.2024.
//

#ifndef PAC_MAN_COORDS_H
#define PAC_MAN_COORDS_H

#include <iostream>

class Coords {
private:
    size_t x;
    size_t y;
public:
    Coords(size_t x, size_t y);

    std::pair<size_t, size_t> getXY() const;

    size_t getX() const;

    size_t getY() const;

    bool operator==(const Coords &rhs) const;

    bool operator!=(const Coords &rhs) const;
};


#endif //PAC_MAN_COORDS_H
