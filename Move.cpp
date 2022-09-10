/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Allison Lee, Joan Suh
 * leealli, joansuh
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    stringstream str(commandString);
    int num = 0;
    char temp = ' ';
    str >> temp;
    if (str.fail()) {
        str.clear();
        isPass = true;
        isPickup = false;
        isSave = false;
        isQuit = false;
    } else {
        toupper(temp);
        if (temp == 'Q') {
            isPass = false;
            isPickup = false;
            isSave = false;
            isQuit = true;
        } else if (temp == 'S') {
            isPass = false;
            isPickup = false;
            isSave = true;
            isQuit = false;
        } else {
            str >> num;
            elevatorId = num;
            str >> temp;
            if (temp == 'f') {
                str >> num;
                targetFloor = num;
                isPass = false;
                isPickup = false;
                isSave = false;
                isQuit = false;
            } else {
                isPass = false;
                isPickup = true;
                isSave = false;
                isQuit = false;
            }
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPass == true || isSave == true || isQuit == true) {
        return true;
    } else if (isPickup == true) {
        if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing()) {
            return true;
        }
    } else {
        if ((targetFloor >= 0) && (targetFloor < NUM_FLOORS) && (targetFloor != elevators[elevatorId].getCurrentFloor()) && (elevatorId >= 0) && (elevatorId < NUM_ELEVATORS) && (!elevators[elevatorId].isServicing())) {
            return true;
        }
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    int floorDiff = 0;
    targetFloor = pickupFloor.getPersonByIndex(pickupList[0] - '0').getTargetFloor();
    for (int i = 0; i < pickupList.size(); i++) {
        peopleToPickup[i] = pickupList[i] - '0';
        numPeopleToPickup++;
        totalSatisfaction += MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        floorDiff = abs((pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor()) - (currentFloor));
        if (floorDiff > abs(targetFloor - currentFloor)) {
            targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
