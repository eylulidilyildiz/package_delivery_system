/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
Description : This is the header file of the PackageDelivery class. This class has four heaps,
              two for the Drones and two for the Packages that are in the system or in cooldown,
              and two public methods: the constructor and the simulation() function. 
              Additionally, it has helper methods for reading inputs and initializing the heaps,
              calculating the distance, effective speed and completion times, package assignments 
              and execution of the Tasks.
*/

#ifndef __PACKAGEDELIVERY_H
#define __PACKAGEDELIVERY_H

#include <iostream>
#include <fstream>
#include <cmath>

#include "Heap.h"
#include "Drone.h"
#include "Package.h"

using namespace std;

// Constants
const float MAX_PACKAGE_WEIGHT = 10.0f;
const float WEIGHT_FACTOR = 0.2f;
const float BATTERY_FACTOR = 0.3f;
const int COOLDOWN_PERIOD = 5;
const float MAX_BATTERY = 300.0f;

class PackageDelivery{
    public:
        PackageDelivery ( const string droneFile , const string packageFile );
        void simulation();
    
    private:
        Heap<Drone> droneHeap;
        Heap<Package> packageHeap;
        Heap<Drone> cooldownDroneHeap;
        Heap<Package> cooldownPackageHeap;

        int tick; // initially zero

        // helpers for creating drone and package heaps
        void readDroneInputs(const string droneFile);
        void readPackageInputs(const string packageFile); 

        //handling assignments
        void assignDroneToPackage(Package& assignedPackage, Drone& drone, float& completionTime);

        //helpers for calculations
        float calcDistance(Drone drone, Package package);
        float calcEffectiveSpeed(Drone drone, Package package);
        float calcCompletionTime(Drone drone, Package package);

        //helpers for simulation
        void printElements();
        void executeOrCooldown(Drone& drone);
        void updateCooldownCounts();
};

#endif