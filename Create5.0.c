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
int towerDis = 2300;

int motor0 = 0;  // arm motor USE THIS MOTOR TO READ TICKS
int motor1 = 1;  // second arm motor
int armSpeed = 500;

int claw=3; //port for claw servo

int open = 1200;   //opened claw position
int close= 20;   //closed claw postion for botgal

int high = 850;   //high tower motor position (from down)
int mid = 550;

int line;   // black line cliff sensor value


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

void grabGal();
void grabCube();
void rackStack();

void forwardLineR();
void backLineR();
void forwardLineL();
void backLineL();


//Main Create Program

int main()
{
  //wait_for_light(1);   // intitial setup code
  shut_down_in(117);
  create_connect();
  
  forward(2);
  
  rturn(84);
  
  while(get_create_lbump() == 0) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(100, 100);
  }
  create_stop();
  
  create_drive_direct(-lspeed, -rspeed);   // backup from wall to avoid rubbing when turning
  msleep(100);
  
  rturn(85);     // turn to drive along wall
  

  // GETTING BOTGAL


  wallRide(73);
  forwardLineR();
  forward(3);
  grabGal;

  msleep(24000);  //WAIT BEFORE DORPPING ARM AND TURNING AROUND

  
  // Placing BOTGAL


  liftGal();
  msleep(500);
  rturn(90);
  forwardLineR();
  forward(30);
  dropGal();
  msleep(250);
  

  // NEXT GETTING RIGHT CUBE


  rturn(180);
  while(get_create_lbump() == 0) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(120, 120);
  }
  create_stop();

  create_drive_direct(-lspeed, -rspeed);   // backup from wall to avoid rubbing when turning
  msleep(100);
  
  rturn(85);     // turn to drive along wall
  forwardLineR();

  wallRide(39);
  align();
  forward(6);
  grabGal();
  msleep(100);
  liftGal();

  // Placing Cube

  rturn(90);
  forwardLineR();
  lturn(90);
  backLineL();
  back(8);
  dropGal();


  // Getting left Cube
  
  create_disconnect();



}




// Function Definitions

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


void forwardLineR() {
  while(get_create_rcliff() == 0) {           
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
}

void backLineR() {
  while(get_create_rcliff() == 0) {           
    create_drive_direct(-lspeed, -rspeed);
  }
  create_stop();
}

void forwardLineL() {
  while(get_create_lcliff() == 0) {           
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
}

void backLineL() {
  while(get_create_lcliff() == 0) {           
    create_drive_direct(-lspeed, -rspeed);
  }
  create_stop();
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


void grabGal() {
  
  set_servo_position(claw,open);
  enable_servos();
  cmpc(motor0);
  armUp(high);
  msleep(600);
  
  set_servo_position(claw,close);
  msleep(700);
  disable_servos();
  
}

void liftGal() {
  set_servo_position(claw,close);
  enable_servos();
  msleep(300);
  cmpc(motor0);
  armDown(300);

  freeze(motor0);
  freeze(motor1);
}

void dropGal() {
  cmpc(motor0);
  armDown(550);
  
  mav(motor0, -armSpeed);
  mav(motor1, -armSpeed);
  msleep(100);
  ao();

  set_servo_position(claw,open);
  enable_servos();
  msleep(800);

  cmpc(motor0);
  armUp(mid);

  set_servo_position(claw,close);
  msleep(800);
  disable_servos();
  
}


void grabCube() {
  
  set_servo_position(claw,open);
  enable_servos();
  cmpc(motor0);
  armUp(high);
  msleep(600);
  
  set_servo_position(claw,close);
  msleep(700);
  cmpc(motor0);
  armDown(high);
  
  mav(motor0, -armSpeed);
  mav(motor1, -armSpeed);
  msleep(100);
  ao();
  
  msleep(300);
  armUp(400);
  freeze(motor0);
  freeze(motor1);
  
}

void rackStack() {
  lturn(45);
  msleep(100);
  
  set_servo_position(claw, close);
  enable_servos();
  armUp(450);
  freeze(motor0);
  freeze(motor1);
  
  lturn(72);
  msleep(250);
  armDown(200);
  freeze(motor0);
  freeze(motor1);
  
  rturn(54);
  lturn(54);
  
  set_create_total_angle(0);
  while (abs(get_create_total_angle()) < (55*deg)) {
    create_drive_direct(375, -375);
  }
  create_stop();
  
  rturn(82);
  msleep(100);
  
  armDown(250);
  mav(motor0, -armSpeed);
  mav(motor1, -armSpeed);
  msleep(100);
  ao();
  
}

