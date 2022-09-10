/*
 * Copyright 2022 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

// declare your test functions here
void person_tests();
void test_elevator();
void floor_tests();

void start_tests() {
    // call your test functions here
    person_tests();
    test_elevator();
    floor_tests();
    return;
}

// write test functions here

void person_tests() {
    //initialize a person with targetFloor 5, anger 5
    Person p("0f0t5a5");
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl;
    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    //simulate time not being a multiple
    p.tick(TICKS_PER_ANGER_INCREASE - 1);
    //no change
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    p.tick(TICKS_PER_ANGER_INCREASE); //7 after
    p.tick(TICKS_PER_ANGER_INCREASE); //8 after
    p.tick(TICKS_PER_ANGER_INCREASE); //9 after
    exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 1" << endl;
    
    //non-default ctor
    Person p5("1f5t6a7");
    Person p10("1f1t1a1");
    ofstream outs;
    p5.print(outs);
    
    //tick
    bool exploded2 = p5.tick(TICKS_PER_ANGER_INCREASE); //8
    cout << exploded2 << " Expected 0" << endl;
    
    //tick2
    p5.tick(TICKS_PER_ANGER_INCREASE - 1); //no
    p5.tick(0);
    p5.tick(1.5);
    
    //explode
    p5.tick(TICKS_PER_ANGER_INCREASE); //9
    bool explode = p5.tick(TICKS_PER_ANGER_INCREASE); //10
    cout << explode << " Expected 1" << endl;
}

void floor_tests() {
    //declare people
    Person p("0f0t5a5");
    Person p2("0f0t3a4");
    Person p3("2f4t2a4");
    Person p4("2f5t1a4");
    Person p6("2f3t6a2");
    Person p7("3f2t5a5");
    
    //declare floor object
    Floor floor1;
    
    //add people to floor
    floor1.addPerson(p, 5);
    floor1.addPerson(p2, 3);
    floor1.addPerson(p3, -2);
    floor1.addPerson(p4, -4);
    floor1.addPerson(p6, 3);
    floor1.addPerson(p7, 3);
    

}

void test_elevator(){
    Elevator elevator1;
    //not servicing
    elevator1.tick(TICKS_PER_ELEVATOR_MOVE);
    //check if not servicing
    cout << "0 expected " << elevator1.isServicing() << endl;
    //set servicing
    elevator1.serviceRequest(3);
    cout << "1 expected " << elevator1.isServicing() << endl;
    //check currentFloor and targetFloor
    cout << "0 expected " << elevator1.getCurrentFloor() << endl;
    cout << "3 expected " << elevator1.getTargetFloor() << endl;
    //tick servicing
    elevator1.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << "1 expected " << elevator1.getCurrentFloor() << endl;
    elevator1.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << "2 expected " << elevator1.getCurrentFloor() << endl;
    elevator1.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << "3 expected " << elevator1.getCurrentFloor() << endl;
    cout << "3 expected " << elevator1.getTargetFloor() << endl;
    //end servicing
    elevator1.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << "0 expected " << elevator1.isServicing() << endl;
    //tick invalid
    elevator1.tick(0);
    cout << "0 expected " << elevator1.isServicing() << endl;
}
