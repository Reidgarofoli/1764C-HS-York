#include "variables.hpp"

//pid tuning
void auton_0() {
    chassis.setPose(0,0,180);
    chassis.moveToPose(0, 14, 180, 10000, {.forwards = false}, false);
    mogovalue = true;
    mogomech.set_value(mogovalue);
}

void auton_1() {

}

void auton_2() {

}

void auton_3() {

}

void auton_4() {//crosby's skills auton

}

void autonselect(int auton) {
    if (auton == 0){auton_0();}
    if (auton == 1){auton_1();}
    if (auton == 2){auton_2();}
    if (auton == 3){auton_3();}
    if (auton == 4){auton_4();}
    
}