/**
Author : Eylul Idil Yildiz
ID: 22302223
Section : 3
Homework : 2
Description : This is the source file of the PackageDelivery class. The implementations of 
              the constructor and simulation() function are handled in this class. 
              Additionally, helper methods for input readings and heap initializations,
              the distance, effective speed and completion time calculations, package assignments,
              cooldown updates and task executions are implemented in this file. Lastly, the
              implementation of the function printElements() which prints the contents of the 
              four heaps is included. 
*/

#include <iostream>
#include <fstream>
#include <cmath>

//other classes
#include "Heap.h"
#include "Drone.h"
#include "Package.h"
#include "PackageDelivery.h"

using namespace std;


PackageDelivery :: PackageDelivery( const string droneFile , const string packageFile )
{
    //initialize and fill the droneHeap
    droneHeap = Heap<Drone>();   
    readDroneInputs(droneFile);

    //initialize and fill packageHeap
    packageHeap = Heap<Package>(); 
    readPackageInputs(packageFile);

    cooldownDroneHeap = Heap<Drone>();
    cooldownPackageHeap = Heap<Package>();
}


void PackageDelivery :: simulation(){

    tick = 0;
    if(droneHeap.heapIsEmpty())
    {
        return;
    }
    bool stop = false;
    while ( ( !packageHeap.heapIsEmpty() || !cooldownPackageHeap.heapIsEmpty()) &&  stop == false)
    {
        if( !cooldownDroneHeap.heapIsEmpty())
        {
            //if there are elements that in the cooldown heap
            Drone& maxDrone = cooldownDroneHeap.getElementAt(0); //max drone
            if(maxDrone.getCooldownCount() >= COOLDOWN_PERIOD)
            {
                //remove drone from cooldown
                cooldownDroneHeap.heapDeleteRoot();
                maxDrone.updateCooldownCount(COOLDOWN_PERIOD); //set to zero again
                maxDrone.setBatteryLife( MAX_BATTERY );

                int lastAssignedId = maxDrone.getAssignedPackageId();
                Package& lastAssigned = cooldownPackageHeap.getPackageById(lastAssignedId);
                cooldownPackageHeap.heapDeleteElement(lastAssigned); //should delete the element with the same id

                packageHeap.heapInsert(lastAssigned);
                executeOrCooldown(maxDrone);

            }
            else if(!droneHeap.heapIsEmpty()){ 
                //if none of the drones in cooldown has reached MAX_BATTERY yet
                //check the available drones in droneHeap
                Drone currentDrone = droneHeap.heapDeleteRoot(); //max drone
                executeOrCooldown(currentDrone); 
            }
        }
        else if(!droneHeap.heapIsEmpty()){
            //if there are no drones in cooldown but there exists at least one drone in droneHeap
            Drone currentDrone = droneHeap.heapDeleteRoot(); //max drone
            executeOrCooldown(currentDrone);
              
        }
        else{
            stop = true;  
        }
        tick ++;
        updateCooldownCounts();
        //until all packages are delivered   
    }
}


// HELPERS

void PackageDelivery :: executeOrCooldown(Drone& currentDrone)
{
    if(packageHeap.heapIsEmpty()){
        return;
    }
        
     
    float completionTime = 0.0f;
    Package& assignedPackage = packageHeap.getElementAt(0); 

    assignDroneToPackage(assignedPackage, currentDrone, completionTime);

    // Feasibility Check: The simulation calculates if the drone can complete the task
    // based on its remaining battery.
    if(currentDrone.getBatteryLife() >= completionTime )
    {
        //decrease drone battery
        currentDrone.setBatteryLife(currentDrone.getBatteryLife() - completionTime );
        //print
        cout << "Drone " << currentDrone.getId() << " Package " << assignedPackage.getId() << " at tick " << tick;
        cout <<" (delivery time: " << completionTime;
        cout << ", battery life: " << currentDrone.getBatteryLife() << ")" << endl;

            //set drone coordinates
        int destX = assignedPackage.getX();
        int destY = assignedPackage.getY();
        currentDrone.setX(destX);
        currentDrone.setY(destY);
        droneHeap.heapInsert(currentDrone); //insert current drone back to the heap
        packageHeap.heapDeleteElement(assignedPackage); //remove the assigned package
    }
    else{
        //drone goes to cooldown
        cout << "Drone " << currentDrone.getId() << " Package " << assignedPackage.getId() << " at tick " << tick;
        cout << " cool down" << endl ;

        //goes back to hub
        currentDrone.setCooldownState(true);
        currentDrone.setX(0);
        currentDrone.setY(0);
        cooldownDroneHeap.heapInsert(currentDrone);

        packageHeap.heapDeleteElement(assignedPackage); //remove the assigned package
        cooldownPackageHeap.heapInsert(assignedPackage);
    }
}

/**
 * pick the drone which has most battery life and then iterate over packages heap 
 * to choose most reasonable (package with the highest priority and lower completion
 * time as a tie breaker) package for that drone
 */
void PackageDelivery :: assignDroneToPackage(Package& assignedPackage, Drone& drone, float& completionTime){
    completionTime = 0.0f;
    if(packageHeap.heapIsEmpty())
    {
        return;
    }

    // take the first drone in the heap
    assignedPackage = packageHeap.getElementAt(0);
    float currentCompTime = calcCompletionTime(drone, assignedPackage);
    completionTime = currentCompTime;
    // int index = 0;
    //check the packages to see if there is another one with the same priority
    for (int i = 1; i < packageHeap.getHeapSize(); i++)
    {
        Package currentPackage = packageHeap.getElementAt(i);
        if(currentPackage.getPriority() != assignedPackage.getPriority())
        {
            // then the current and the rest of the packages have lower priority
            break;
        }
        //if priorities are the same
        currentCompTime = calcCompletionTime(drone, currentPackage);

        if(currentCompTime < completionTime){
            completionTime = currentCompTime;
            assignedPackage = currentPackage;
            //index = i;
        }
    }  
    drone.setAssignedPackageId(assignedPackage.getId());
}


void PackageDelivery :: updateCooldownCounts()
{
    if(cooldownDroneHeap.heapIsEmpty())
    {
        return;
    }
    for (int i = 0; i < cooldownDroneHeap.getHeapSize(); i++)
    {
        Drone& drone = cooldownDroneHeap.getElementAt(i);
        drone.updateCooldownCount(COOLDOWN_PERIOD);
    }
}

// drone.txt and package.txt files are read using <fstream>
// the drones and packages are created and inserted into the heaps

/** the contents of the drone.txt file is as follows:
 * (first row) number of drones
 * (rest of the rows) ID , battery life , speed
 */
void PackageDelivery :: readDroneInputs( const string droneFile){
    ifstream input(droneFile);
    if ( !input.is_open() ){
        cout << "Error: Could not open " << droneFile << endl;
        return;
    }

    int size;
    input >> size; //first number in the .txt file gives the number of drones

    for (int i = 0; i < size; i++)
    {
        int id;
        float batteryLife, baseSpeed;
        input >> id >> batteryLife >> baseSpeed;
        Drone current(id, batteryLife, baseSpeed); // construct a drone
        droneHeap.heapInsert(current);
    }

    input.close();    
}

/** the contents of the package.txt file is as follows:
 * (first row) number of packages
 * (rest of the rows) / ID , (x , y ) , Weight , Prority
 */
void PackageDelivery :: readPackageInputs( const string packageFile){
    ifstream input(packageFile);
    if ( !input.is_open() ){
        cout << "Error: Could not open " << packageFile << endl;
        return;
    }

    int size;
    input >> size; //first number in the .txt file gives the number of packages
    for (int i = 0; i < size; i++)
    {
        int id, x, y, priority;
        float weight;
        input >> id >> x >> y >> weight >> priority;
        Package current(id, x, y, weight, priority); // construct a package
        packageHeap.heapInsert(current);
    }

    input.close();    
}

/**
 * distance between (x1,y1) and (x2,y2) is calculated as:
 *  sqrt( (x1-x2)^2 + (y1-y2)^2 )
 */
float PackageDelivery:: calcDistance(Drone drone, Package package){
    float diffX = package.getX() - drone.getX();
    float diffY = package.getY() - drone.getY();
    float distance = sqrt( (diffX * diffX) + (diffY * diffY) );
    return floor(distance * 10.0f) / 10.0f; // round to one decimal
}

/**
 * Effective Speed is calculated as:
 * Base Speed × (1 − WEIGHT_FACTOR × package weight /MAX_PACKAGE_WEIGHT) (1 − BATTERY_FACTOR × (1 − battery life/max battery) )
 */
float PackageDelivery :: calcEffectiveSpeed(Drone drone, Package package)
{
    float weightMultiplier = 1.0f - WEIGHT_FACTOR * ( package.getWeight() / MAX_PACKAGE_WEIGHT );
    float batteryMultiplier = 1.0f - BATTERY_FACTOR * (1.0f- drone.getBatteryLife() / MAX_BATTERY );
    float effectiveSpeed = drone.getBaseSpeed() * weightMultiplier * batteryMultiplier;
    return floor(effectiveSpeed * 10.0f) / 10.0f; // one decimal
}

/**
 * Duration is calculated as:
 * distance / speed
 */
float PackageDelivery :: calcCompletionTime(Drone drone, Package package)
{
    float effectiveSpeed = calcEffectiveSpeed(drone, package);
    float distance = calcDistance(drone, package);
    float time = (distance / effectiveSpeed);
    return floor( time * 10.0f ) / 10.0f; // rounded to one decimal
}

//for tracking elements in heaps
void PackageDelivery :: printElements()
{
    cout << "Drones:" << endl;
    for (int i = 0; i < droneHeap.getHeapSize(); i++)
    {
        Drone& drone = droneHeap.getElementAt(i);
        cout << "id: " << drone.getId() << " battery: " << drone.getBatteryLife() << " speed: " << drone.getBaseSpeed() <<
        " x: " << drone.getX() << " y: " << drone.getY() << endl;
    }

    cout << "Packages:" << endl;
    for (int i = 0; i < packageHeap.getHeapSize(); i++)
    {
        Package& p = packageHeap.getElementAt(i);
        cout << "id: " << p.getId() << " priority: " << p.getPriority() << " weight: " << p.getWeight();
        cout << " x: " << p.getX() << " y: " << p.getY() << endl;
    }

    cout << "Cooldown Drones:" << endl;
    for (int i = 0; i < cooldownDroneHeap.getHeapSize(); i++)
    {
        Drone& drone = cooldownDroneHeap.getElementAt(i);
        cout << "id: " << drone.getId() << " battery: " << drone.getBatteryLife() << " count: " << drone.getCooldownCount();
        cout << " x: " << drone.getX() << " y: " << drone.getY() << endl;
    }

    cout << "Cooldown Packages:" << endl;
    for (int i = 0; i < cooldownPackageHeap.getHeapSize(); i++)
    {
        Package& p = cooldownPackageHeap.getElementAt(i);
        cout << "id: " << p.getId() << " priority: " << p.getPriority() << " weight: " << p.getWeight() << 
        " x: " << p.getX() << " y: " << p.getY() << endl;
    }
}