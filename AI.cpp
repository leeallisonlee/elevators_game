/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Allison Lee, Joan Suh
 * leealli, joansuh
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    BuildingState state = buildingState;
    
    //check if no one is in the building
    int numPeopleInBuilding = 0;
    for (int i = 0; i < 10; i++) {
        numPeopleInBuilding += state.floors[i].numPeople;
    }
    if (numPeopleInBuilding == 0) {
        return "";
    }
    
    //pass move
    if (state.elevators[0].isServicing && state.elevators[1].isServicing && state.elevators[2].isServicing) {
        return "";
    }
    
    
    //pickup and service moves
    //calculate floor with the highest number of people
    int greatestPeopleFloorNum = 0; //index
    int greatestNotServicingFloorNum = 0; //index
    int greatestNotServicingFloorNum2 = 0;
    int greatestPeopleCount = 0;
    for (int i = 0; i < 10; i++) {
        if ((state.floors[i].numPeople > greatestPeopleCount)) {
            greatestPeopleFloorNum = i;
            greatestPeopleCount = state.floors[i].numPeople;
            
            //calculate floor with highest number of people that another elevator is not going to
            if ((state.elevators[0].targetFloor != i) && (state.elevators[1].targetFloor != i) && (state.elevators[2].targetFloor != i)) {
                greatestNotServicingFloorNum2 = greatestNotServicingFloorNum;
                greatestNotServicingFloorNum = i;
            }
        }

    }
    
    //find the closest elevator to this floor
    int serviceMoveElevatorId = -1; //index
    int currFloorComparison = NUM_FLOORS;
    for (int i = 0; i < 3; i++) {
        if (state.elevators[i].isServicing == false) {
            if (abs(state.elevators[i].currentFloor - (greatestPeopleFloorNum)) < currFloorComparison) {
                currFloorComparison = abs(state.elevators[i].currentFloor - (greatestPeopleFloorNum));
                serviceMoveElevatorId = i;
            }
        }
    }
    //return pickup move list if serviceMoveElevatorId current floor = greatestPeopleFloorNum
    if (state.elevators[serviceMoveElevatorId].currentFloor == greatestPeopleFloorNum) {
        string pickUpMove = "e" + to_string(serviceMoveElevatorId) + "p";
        return pickUpMove;
    }
     
    //if elevator not servicing and people on current floor, pickup
    for (int i = 0; i < 3; i++) {
        _Floor currFloor = state.floors[state.elevators[i].currentFloor];
        if (!state.elevators[i].isServicing && (currFloor.numPeople > 0)) {
            string pickUpMove = "e" + to_string(i) + "p";
            return pickUpMove;
        }
    }
    
    //return service move

        if (greatestPeopleFloorNum == greatestNotServicingFloorNum) {
            string serviceMove = "e" + to_string(serviceMoveElevatorId) + "f" + to_string(greatestNotServicingFloorNum);
            return serviceMove;
        } else if (greatestPeopleFloorNum == greatestNotServicingFloorNum2){
            string serviceMove = "e" + to_string(serviceMoveElevatorId) + "f" + to_string(greatestNotServicingFloorNum2);
            return serviceMove;
        }
    return "";
}

        

    

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
 
    
    
    string pickupListUp = "";
    string pickupListDown = "";
    
    int numGoingUp = 0;
    int numGoingDown = 0;
//    int goingUpAnger = 0;
//    int goingDownAnger = 0;
    
    //calculate number of ppl going up and down, anger level additions
    for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
        if (floorToPickup.getPersonByIndex(i).getTargetFloor() > floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
            numGoingUp++;
//            goingUpAnger += floor.getPersonByIndex(i).getAngerLevel();
            pickupListUp += to_string(i);
        } else {
            numGoingDown++;
//            goingDownAnger += floor.getPersonByIndex(i).getAngerLevel();
            pickupListDown += to_string(i);
        }
    }
    
//    bool up = true;
    //calculate who to take (up or down people)
    //true is up, false is down
    if ((numGoingUp >= numGoingDown)) {
//        up = true;
        return pickupListUp;
    } else {
//        up = false;
        return pickupListDown;
    }
    

    
}


