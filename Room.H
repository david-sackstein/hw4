#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <iostream>

using std::string;

class Room {
public:

    Room(unsigned int roomNumber = 0, unsigned int area = 0);

    unsigned int getRoomNumber() const { return roomNumber_; }
    bool getIsOccupied() const { return isOccupied_; }

    void setOccupied() { isOccupied_ = true; }
    void setVacant() { isOccupied_ = false; }

    void print() const;

private:

    unsigned int roomNumber_;
    unsigned int area_;
    bool isOccupied_;
};

#endif
