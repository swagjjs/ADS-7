// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstdlib>

Train::Train() : countOp(0), first(nullptr), current(nullptr) {}

Train::~Train() {
    if (!first) return;
    
    Car* temp = first->next;
    while (temp != first) {
        Car* next = temp->next;
        delete temp;
        temp = next;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
        current = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) return 0;
    
    countOp = 0;
    
    bool allLightsOff = true;
    Car* temp = first;
    do {
        if (temp->light) {
            allLightsOff = false;
            break;
        }
        temp = temp->next;
    } while (temp != first);
    
    if (allLightsOff) {
        first->light = true;
        countOp++;
        
        Car* currentCar = first->next;
        int steps = 1;
        while (!currentCar->light) {
            currentCar = currentCar->next;
            steps++;
            countOp++;
        }
        
        first->light = false;
        countOp++;
        
        return steps;
    } else {
        Car* startCar = first;
        while (!startCar->light) {
            startCar = startCar->next;
            countOp++;
        }
        startCar->light = false;
        countOp++;
        
        int length = 1;
        Car* currentCar = startCar->next;
        countOp++;
        
        while (true) {
            if (currentCar->light) {
                currentCar->light = false;
                countOp += length;
                length = 1;
                currentCar = currentCar->next;
                countOp++;
            } else {
                length++;
                currentCar = currentCar->next;
                countOp++;
            }
            
            if (currentCar == startCar && !currentCar->light) {
                return length;
            }
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
