#include <stdio.h>
#include <kipr/wombat.h>

//Variables

int lspeed=185;
int rspeed=185;

int lwall=265;
int rwall=220;

int rTspeed=150;
int lTspeed=150;

float deg=1.12;
int CM=10;

int ET = 0;   //ET sensor port
int towerDis = 1650;    

int motor0 = 0;  // arm motor USE THIS MOTOR TO READ TICKS
int motor1 = 1;  // second arm motor
int armSpeed = 275;

int claw=2; //port for claw servo

int open = 900 ;
int r1 ; //open claw value for given ring
int r2 ;
int r3 ;
int r4 ;
int r5 ;
int r1c = 38 ; //closed claw on given ring
int r2c ;
int r3c ;
int r4c ;
int r5c ;
int cube= 60; //closed claw on a cube

int high = 920;   //high tower motor position (from down)
int low = 1150;   //lower tower motor position (from down)

//Functions

void rturn(int angle);
void lturn(int angle);

void forwad(int distance);
void back(int distance);

void wallRide(int distance);
void wallRideBack(int distance);
void wallSquare();

void onTower();
void offTower();
void onTowerBack();
void offTowerBack();

void armUp(int position);
void armDown(int position);

void cubeLow();
void cubeHigh();


//Main Create Program

int main()
{
  create_connect();

  
  set_servo_position(claw,open);
  enable_servos(claw);
  armUp(low);
  msleep(1000);
  set_servo_position(claw,cube);
  msleep(1000);
  armDown(1000);
  msleep(1000);
  
  
  create_disconnect();
}




//Function Definitions

void rturn(int angle) {
  set_create_total_angle(0);
  while (abs(get_create_total_angle()) < (angle*deg)) {
    create_drive_direct(lTspeed, -rTspeed);
  }
  create_stop();
}



void lturn(int angle) {
  set_create_total_angle(0);
  while (abs(get_create_total_angle()) < (angle*deg)) {
    create_drive_direct(-lTspeed, rTspeed);
  }
  create_stop();
}



void forward(int distance) {
  set_create_distance(0);
  while (abs(get_create_distance()) < (distance*CM)) {
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
}



void back(int distance) {
  set_create_distance(0);
  while (abs(get_create_distance()) < (distance*CM)) {
    create_drive_direct(-lspeed, -rspeed);
  }
  create_stop();
}




void wallRide(int distance) {
  
  set_create_distance(0);
  
  while (abs(get_create_distance()) < (distance*CM)) {
    if (get_create_lbump()==0) {
      create_drive_direct(lspeed, rwall);
    }else{
      create_drive_direct(lwall, rspeed);
    }
  }
  create_stop();
}

void wallRideBack(int distance) {
  
  set_create_distance(0);
  
  while (abs(get_create_distance()) < (distance*CM)) {
    while (get_create_lbump()==0) {
      create_drive_direct(0,200);
    }
    create_drive_direct(-220,-265);
    msleep(300);
  }
  create_stop();
}



void wallSquare() {
  while (get_create_lbump()==0) {
    create_drive_direct(0,400);
  }
  rturn(25);
  create_stop();
}



void onTower() {
  while(analog_et(ET) < towerDis) {
    create_drive_direct(lTspeed,rTspeed);
  }
  create_stop();
}


void offTower() {
  while(analog_et(ET) > towerDis) {
    create_drive_direct(lTspeed,rTspeed);
  }
  create_stop();
}


void onTowerBack() {
  while(analog_et(ET) < towerDis) {
    create_drive_direct(-lTspeed,-rTspeed);
  }
  create_stop();
}


void offTowerBack() {
  while(analog_et(ET) > towerDis) {
    create_drive_direct(-lTspeed,-rTspeed);
  }
  create_stop();
}




void armUp (int position) {

  cmpc(motor0);

  while(gmpc(motor0) < position) {
    mav(motor0, armSpeed);
    mav(motor1, armSpeed);
  }
  freeze(motor0);
  freeze(motor1);
  msleep(100);
  ao();
}


void armDown (int position) {

  cmpc(motor0);

  while(gmpc(motor0) < position) {
    mav(motor0, -armSpeed);
    mav(motor1, -armSpeed);
  }
  freeze(motor0);
  freeze(motor1);
  msleep(100);
  ao();
}


void cubeLow() {
  set_servo_position(claw,open);
  enable_servos(claw);

  armUp(low);
  msleep(400);

  set_servo_position(claw,cube);
  msleep(800);

  armDown(low);
  msleep(400);
}

void cubeHigh() {
  set_servo_position(claw,open);
  enable_servos(claw);

  armUp(low);
  msleep(400);

  set_servo_position(claw,cube);
  msleep(800);

  armDown(low);
  msleep(400);
}
