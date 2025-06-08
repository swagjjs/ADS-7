// Copyright 2022 NNTU-CS
#ifndef TRAIN_H
#define TRAIN_H

class Train {
 private:
    struct Car {
        bool light; 
        Car* next;
        Car* prev;
    };
    int countOp;
    Car* first;  
    Car* current;

 public:
    Train();
    ~Train();
    void addCar(bool light);
    int getLength();
    int getOpCount();
};

#endif  // TRAIN_H
