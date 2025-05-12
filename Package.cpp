/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
Description : This is the source file of the Package class. Getter and setters of the Package 
              qualities are implemented in this file. Also, comparison operators (less than, 
              greater than, equality and inequality) are overridden for the Package class. 
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include "Package.h"

using namespace std;

//PACKAGE IMPLEMENTATIONS

//constructor
Package :: Package(int id, int destX, int destY, float weight, int priority)
        : id(id), x(destX), y(destY), weight(weight), priority(priority) {}
        
//copy constructor
Package::Package(const Package& other) 
        : id(other.id), x(other.x), y(other.y), weight(other.weight), priority(other.priority) {}

//getters
int Package :: getId(){ return id; }
int Package :: getX(){ return x; }
int Package :: getY(){ return y; }
float Package :: getWeight(){ return weight; }
int Package :: getPriority(){ return priority; }

// operators

/**
 * Less than operator returns true if the priority of the Package on the LHS is
 * smaller than the one on the RHS. If priorities are equal, it checks higher id
 * as a tie breaker
 */
bool Package :: operator < (const Package& rhs) const 
{
    // compare priorities
    if (priority != rhs.priority) { 
        return priority < rhs.priority;
    }
    // if priorities are equal, package with the higher id has the lower priority
    return id > rhs.id;
}

/**
 * Greater than operator returns true if the priority of the Package on the LHS is
 * greater than the one on the RHS. If priorities are equal, it checks lower id
 * as a tie breaker
 */
bool Package :: operator > (const Package& rhs) const 
{
    // compare priorities
    if (priority != rhs.priority) { 
        return priority > rhs.priority;
    }
    // if priorities are equal, package with the higher id has the lower priority
    return id < rhs.id;
}

/**
 * Equality operator returns true if the id's of the Packages are equal,
 * false otherwise.
 */ 
bool Package :: operator == (const Package& rhs) const 
{
    return id == rhs.id;
}

/**
 * Inequality operator returns false if the id's of the Packages are equal,
 * true otherwise.
 */ 
bool Package :: operator != (const Package& rhs) const 
{
    return id != rhs.id;
}

