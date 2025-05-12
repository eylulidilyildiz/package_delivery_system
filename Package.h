/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
Description : This is the header file of the Package class. Each Package has the id, 
              priority and weight properties, and the destination x and y coordinates.

*/

#ifndef __PACKAGE_H
#define __PACKAGE_H

/**
 * Each package to be delivered has:
 * ID: A unique identifier.
 * Destination: Coordinates (x, y) where it must be delivered.
 * Priority: A numerical value indicating delivery urgency (higher means more urgent).
 * Weight: The package weight, affecting the drone’s effective speed
 */
class Package{
public:
    //constructor
    Package(int id = 0, int destX = 0, int destY = 0, float weight = 0, int priority = 0);
    //copy constructor
    Package(const Package& other);

    //getters
    int getId();
    int getX();
    int getY();
    float getWeight();
    int getPriority();  

    //overriding operators for ordering and comparing in heap
    bool operator < (const Package& rhs) const;
    bool operator > (const Package& rhs) const;
    bool operator == (const Package& rhs) const;
    bool operator != (const Package& rhs) const;

private:
    int id;
    int x;
    int y;
    float weight;
    int priority;
};

#endif