#include "Room.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;
using std::boolalpha;

//**********************************************************
//  Function name : Room::Room
//  Description   : Create new room with room number and 
//					area. Set occupacion to false.
//  Paramaters    : roomNumber - integer of Room Number
//					area - area value
//  Return value  : None.
//**********************************************************
Room::Room(unsigned int roomNumber, unsigned int area) :
    roomNumber_(roomNumber), 
    area_(area),
    isOccupied_(false)
{
}

//**********************************************************
//  Function name : Room::print
//  Description   : Prints rooms' features.
//  Paramaters    : None.
//  Return value  : None.
//**********************************************************
void Room::print() const
{
    cout << "Number : " << roomNumber_ << "\n";
    cout << "Size : " << area_ << " square meters " << "\n";
    cout << "Is Occupied : " << boolalpha << isOccupied_ << "\n";
}

