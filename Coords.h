//
// Created by Daria Kuznetsova on 24.08.2024.
//

#ifndef PAC_MAN_COORDS_H
#define PAC_MAN_COORDS_H

#include <iostream>

class Coords {
private:
    int x;
    int y;
public:
    Coords(int x, int y);

    std::pair<int, int> getXY() const;

    int getX() const;

    int getY() const;

    void setX(int x);

    void setY(int y);

    bool operator==(const Coords &rhs) const;

    bool operator!=(const Coords &rhs) const;
};


#endif //PAC_MAN_COORDS_H
