# package_delivery_system
Package Delivery System

/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
*/

# Package Delivery System Simulation
This project is a drone-based package delivery system which is implemented using the heap structure.

## Description
This system manages a simulation in which packages are distributed to different destinations using drones. 
Drones and Packages are taken as input with .txt files. Packages are sorted among themselves according to 
their numerical priority values, and drones are sorted according to their remaining battery life and IDs. 
In the simulation, the most suitable packages are assigned to the drones according to their package priorities 
and estimated completion times of the process, it is checked whether the drone has enough battery and either 
the Task is executed or the drone enters the cooldown period to recharge.

## Project Structure
- **`Heap.h` / `Heap.cpp`** : Operations such as insertion and deletion of template heaps that will be used to
keep drones and packages constantly ordered according to their specific features are managed within the Heap class.

- **`Drone.h` / `Drone.cpp`** : The id, battery life, base speed, x and y properties of the drones, Drone assignment
and cooldown status are managed within the Drone class.

- **`Package.h` / `Package.cpp`** : The id, weight and priority properties, and the destination coordinates, are
handled in the Package class.

- **`PackageDelivery.h` / `PackageDelivery.cpp`** : Receiving, ordering and simulating Package and Drone data is 
managed in the class.

## Functionality
- Reads drone inputs and inserts them into the heap based on their battery lives and id's.
- Reads package inputs and inserts them into the heap based on their priorities (and lower id's as a tie breaker).
- Assigns the drone at the root of the max heap to the package with the highest priority.
- Then, traversing over the other packages, calculates the estimated completion times.
- If there is a package with the same priority as the chosen one with a lower time, assigns that package to the drone.
- After the assignment is done, checks whether drone battery is enough for the estimated completion time.
- If battery is enough task is executed, package is removed and drone's battery and coordinates are updated.
- If the battery is not enough, both the drone and the package go to cooldown period at the hub (0,0).
- tick is incremented after each operation.

## Input File Format

###  `drone.txt`
- first line: size
- rest of the lines: ID , battery life , speed

###  `package.txt`
- first line: size
- rest of the lines: ID , (x , y) , Weight , Prority

## Output Format
- Each successful task is printed by: drone id, package id, tick, completion time and drone's remaining battery life.
- If a drone goes to cooldown, this is indicated in the output instead of the completion time and battery life.
