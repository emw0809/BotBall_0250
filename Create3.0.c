#include <stdio.h>
#include <kipr/wombat.h>

//Variables

int lspeed=300;
int rspeed=300;

int lwall=280;
int rwall=240;

int rTspeed=200;
int lTspeed=200;

float deg=1.65;
int CM=10;

int towerDis;

int motor0 = 0;
int motor1 = 1;
int armSpeed = 275;

int open ;
int r1 ; //open value for given ring
int r2 ;
int r3 ;
int r4 ;
int r5 ;
int r1c ; //closed on given ring
int r2c ;
int r3c ;
int r4c ;
int r5c ;
int cube ; //closnig on a cube

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


//Main Create Program

int main()
{
  create_connect();
  
  lturn(90);
  
  while(get_create_lbump()==0) {
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
  
  back(3);
  rturn(90);
  
  wallRide(150);
  
  msleep(500);
  
  wallRideBack(100);
  
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
      create_drive_direct(0,400);
    }
    rturn(25);
    create_drive_direct(-350,-350);
    msleep(75);
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
  while(analog_et(0) < towerDis) {
    create_drive_direct(lTspeed,rTspeed);
  }
  create_stop();
}


void offTower() {
  while(analog_et(0) > towerDis) {
    create_drive_direct(lTspeed,rTspeed);
  }
  create_stop();
}


void onTowerBack() {
  while(analog_et(0) < towerDis) {
    create_drive_direct(-lTspeed,-rTspeed);
  }
  create_stop();
}


void offTowerBack() {
  while(analog_et(0) > towerDis) {
    create_drive_direct(-lTspeed,-rTspeed);
  }
  create_stop();
}




void armUp (int position) {
  while(gmpc(0) < position) {
    mav(motor0, armSpeed);
    mav(motor1, armSpeed);
  }
  ao();
}


void armDown (int position) {
  while(gmpc(0) > position) {
    mav(motor0, -armSpeed);
    mav(motor1, -armSpeed);
  }
  ao();
}









