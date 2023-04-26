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
int towerDis = 1050;

int motor0 = 0;  // arm motor USE THIS MOTOR TO READ TICKS
int motor1 = 1;  // second arm motor
int armSpeed = 500;

int claw=3; //port for claw servo

int open = 1362 ;
int cube= 800; //closed claw on a cube

int high = 850;   //high tower motor position (from down)
int low = 940;   //lower tower motor position (from down)

int wrist = 2;   // wrist servo port
int wristLow = 1799;    // low tower wrist position
int wristHigh = 1457;   // high tower wrist position
int wristDown = 900;   // arm down wrist position

//Functions

void rturn(int angle);
void lturn(int angle);

void forward(int distance);
void back(int distance);

void wallRide(int distance);
void wallRideBack(int distance);
void wallSquare();

void onTower();
void offTower();
void onTowerBack();
void offTowerBack();

void align();

void armUp(int position);
void armDown(int position);
void armBump();

void cubeLow();
void cubeHigh();

void botgal();


//Main Create Program

int main()
{
  wait_for_light(1);
  shut_down_in(120);
  create_connect();
    
  lturn(85); //turns towards data center
  
  while(get_create_lbump() == 0) { //drives forward until contact with pvc 
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
    create_drive_direct(-lspeed, -rspeed); //backup to avoid "beaching" on pvc
  msleep(100);
  
  rturn(85); //turn to drive along wall
  forward(18); //drive forward to tower 1 (red tower)
  msleep(500);

  //Tower 1
  align();  //aligns with tower 1 (red tower)
  cubeLow();
  msleep(250); 
  
  
  
  //Tower 2
  wallRide(20); //drives forward to tower 2 (green/blue tower)
  msleep(500); 
  
  align(); //aligns with the edge of the tower
  cubeHigh();
  msleep(250); 
  
  //Tower 3
  wallRide(20); //drives forward to tower 3 (yellow tower)
  msleep(500);
  
  align(); //aligns with the edge of the tower
  cubeHigh();
  msleep(250); 
  botgal(); //grab botgal off tower, turn and drive to analysis lab, drop botgall, return to tower, facing original direction
  
  //Tower 4
  wallRide(40); //drive forward to tower 4 (green/blue tower)
  msleep(500);
  
  align(); //aligns with edge of tower
  cubeHigh();
  msleep(250);
  
  //Tower 5
  wallRide(28); //drives forward to tower 5 (orange tower)
  msleep(500);
  
  align(); //aligns with edge of tower
  cubeLow();
  msleep(250);
  
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
    create_drive_direct(0,170);
  }
  rturn(10);
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


void align() {
  if(analog_et(ET) > towerDis) {
    offTowerBack();
  } else {
    onTower();
  }
  forward(23);
}


void armBump () {
  
  while(digital(0) == 0) {
    mav(motor0, armSpeed);
    mav(motor1, armSpeed);
  }
  freeze(motor0);
  freeze(motor1);
  msleep(100);
  ao();
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
  
  while(abs(gmpc(motor0)) < position) {
    mav(motor0, -armSpeed);
    mav(motor1, -armSpeed);
  }
  freeze(motor0);
  freeze(motor1);
  msleep(100);
  ao();
}


void cubeLow() {
    cmpc(motor0);
  set_servo_position(wrist,wristLow);
  set_servo_position(claw,open);
  enable_servos();
  
  armUp(low);
  msleep(250);
  
  set_servo_position(claw,cube);
  msleep(700);
  cmpc(motor0);
  armDown(low);
  mav(motor0, -armSpeed);
  mav(motor1, -armSpeed);
  msleep(100);
  ao();
  
  msleep(150);
  set_servo_position(wrist,wristDown);
  msleep(250);
  set_servo_position(claw,open);
  msleep(250);
  disable_servos();
}

void cubeHigh() {
    cmpc(motor0);
  set_servo_position(wrist,wristHigh);
  set_servo_position(claw,open);
  enable_servos();
  
  armUp(high);
  msleep(250);
  
  set_servo_position(claw,cube);
  msleep(700);
  cmpc(motor0);
  armDown(high);
  mav(motor0, -armSpeed);
  mav(motor1, -armSpeed);
  msleep(100);
    
  msleep(150);
  set_servo_position(wrist,wristDown);
  msleep(250);
  set_servo_position(claw,open);
  msleep(250);
  disable_servos();
}



void botgal() { 

  lturn(90);
  back(57);
  create_stop();
  msleep(500); //add arm movement to drop botgal here

  while(get_create_lbump() == 0) {
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
    create_drive_direct(-lspeed,-rspeed);
    msleep(120);
    create_stop();

 rturn(90);
  create_stop();
  msleep(500);
}

 

void ringRun() {  // old main code for ring tower positioning
  
  lturn(90);
  
  while(get_create_lbump() == 0) {
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
  
  create_drive_direct(-lspeed, -rspeed);
  msleep(100);
  
  rturn(85);
  forward(10);
  msleep(500);
  
  //Tower 1
  align();
  msleep(250);
  
  
  //Tower 5
  wallRide(166);
  msleep(500);
  
  align();
  msleep(250);
  
  
  //Tower 3
  wallSquare();
  back(75);  //IF WALL RIDE BACK DOESNT WORK THEN USE NORMAL back(int distance)
  
  align();
  msleep(250);
  
  
  //Tower 2
  wallSquare();
  back(37);  //IF WALL RIDE BACK DOESNT WORK THEN USE NORMAL back(int distance)
  
  align();
  msleep(250);
  
  //Tower 4
  wallRide(85);
  msleep(500);
  align();
  msleep(250);
}

