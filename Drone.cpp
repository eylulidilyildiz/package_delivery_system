/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
Description : This is the source file of the Drone class. Getter and setters of the 
              Drone qualities are implemented in this file. In addition, comparison
              operators (less than, greater than, equality and inequality) and the 
              assignment operator (=) is overridden for the Drone class. 
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include "Drone.h"
#include "Package.h"

using namespace std;

//constructor
Drone :: Drone(int id, float batteryLife, float baseSpeed)
        : id(id), batteryLife(batteryLife), baseSpeed(baseSpeed)
{
        x = 0;
        y = 0;
        assignedPackageId = -1; 
        cooldownState = false;
        cooldownCount = 0;  
}
//copy constructor
Drone::Drone(const Drone& other) : id(other.id), batteryLife(other.batteryLife), baseSpeed(other.baseSpeed)
{
        x = other.x;
        y = other.y; 
        assignedPackageId = other.assignedPackageId;
        cooldownState = other.cooldownState;
}

//getters
int Drone :: getId(){ return id; }
float Drone :: getBatteryLife() { return batteryLife; }
float Drone :: getBaseSpeed(){ return baseSpeed; }
int Drone :: getX() const { return x; }
int Drone :: getY() const { return y; }
bool Drone :: getCooldownState(){ return cooldownState;  }
int Drone :: getCooldownCount() { return cooldownCount; }
int Drone :: getAssignedPackageId() { return assignedPackageId; }

//setters
void Drone :: setBatteryLife( float currentBattery ){
    batteryLife = currentBattery;
}
void Drone :: setX( int currentX ){
    x = currentX;
}
void Drone :: setY( int currentY ){
    y = currentY;
}

void Drone :: setAssignedPackageId( int id ){
    assignedPackageId = id;
}

void Drone :: setCooldownState(bool state){
    cooldownState= state;
}

void Drone :: updateCooldownCount(const int COOLDOWN_PERIOD){
    if(cooldownCount < COOLDOWN_PERIOD)
    {
        // if cooldown is not finished
        cooldownCount++;
        return;
    }
    //batteryLife = MAX_BATTERY;
    cooldownState = false;
    cooldownCount = 0; // reset cooldown if period is over
}

//assignment operator for references
Drone& Drone::operator=(const Drone& rhs) {
    if (this != &rhs) { // must not self-assign
        id = rhs.id;
        batteryLife = rhs.batteryLife;
        baseSpeed = rhs.baseSpeed;
        x = rhs.x;
        y = rhs.y;
        assignedPackageId = rhs.assignedPackageId; // Reference assignment
        cooldownState = rhs.cooldownState;
        cooldownCount = rhs.cooldownCount;
    }
    return *this;
}

// overriding comparator operators according to battery life & lower id
bool Drone :: operator < (const Drone& rhs) const 
{
    // compare batteries
    if (batteryLife != rhs.batteryLife) { 
        return batteryLife < rhs.batteryLife;
    }
    // if batteries are equal, drone with the higher id has the lower priority
    return id > rhs.id;
}

bool Drone :: operator > (const Drone& rhs) const 
{
    // compare batteries
    if (batteryLife != rhs.batteryLife) { 
        return batteryLife > rhs.batteryLife;
    }
    // if batteries are equal, drone with the higher id has the lower priority
    return id < rhs.id;
}

// overriding equality operators according id
bool Drone :: operator == (const Drone& rhs) const 
{
    return id == rhs.id;
} 


bool Drone :: operator != (const Drone& rhs) const 
{
    return id != rhs.id;
}