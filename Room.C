#include "Room.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;
using std::boolalpha;

Room::Room(unsigned int roomNumber, unsigned int area) :
    roomNumber_(roomNumber), 
    area_(area),
    isOccupied_(false)
{
}

void Room::print() const
{
    cout << "Number : " << roomNumber_ << "\n";
    cout << "Size: " << area_ << " square meters\n";
    cout << "Is Occupied : " << boolalpha << isOccupied_ << "\n";
}

