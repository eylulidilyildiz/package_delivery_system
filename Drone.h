/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
Description : This is the header file of the Drone class. Each Drone has the following qualities:
              - The id, battery life and base speed properties, 
              - The x and y coordinates,
              - The cooldown status and the cooldown count,
              - Id of the Package which is assigned to the drone
*/

#ifndef __DRONE_H
#define __DRONE_H

#include "Package.h"
/**
 * Each drone is characterized by:
 * ID: A unique identifier.
 * Battery Life: The maximum energy available before recharging is required.
 * Speed: The drone’s base speed (meters per second).
 * All drones start from the hub located at (0, 0)
 */
class Drone{
public:
    Drone(int id = 0, float batteryLife = 0, float baseSpeed = 0); //constructor
    Drone(const Drone& other); //copy constructor

    //getters
    int getId();
    float getBatteryLife();
    float getBaseSpeed();
    int getX () const;
    int getY () const;

    int getAssignedPackageId();
    bool getCooldownState();
    int getCooldownCount();

    //setters
    void setBatteryLife(float currentBattery);
    void setX(int currentX);
    void setY(int currentY);

    void setAssignedPackageId(int id);
    void setCooldownState(bool state);
    void updateCooldownCount(const int COOLDOWN_PERIOD);

    //overriding operators for ordering in heap
    Drone& operator = (const Drone& rhs);
    bool operator < (const Drone& rhs) const;
    bool operator > (const Drone& rhs) const;
    bool operator == (const Drone& rhs) const;
    bool operator != (const Drone& rhs) const;
    
        
private:
    int id;
    float batteryLife;
    float baseSpeed;
    int x; // initially 0
    int y; // initially 0

    //helpers
    int assignedPackageId;
    bool cooldownState; // initially false
    int cooldownCount; // initially 0
};
    
#endif    