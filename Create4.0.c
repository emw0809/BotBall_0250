#include <stdio.h>
#include <kipr/wombat.h>

/*
PSEUDO CODE

0-15sec
-Turn to the left and raise your arm over the Rackastack
-Lower the arm and turn right to hit the top of the rackastack
-Hit it again by turning to ensure it is knocked over
-Turn to the left towards the server racks

15sec-30sec
-Drive straight towards the server racks out of the watch floor
-Stop as soon as the bumpers on the front of the create are pressed
-Back up slightly from the pipe wall along server racks to prevent rubbing
-Then turn right 90 deg so the create is facing down the line of server racks
-For precise alignment, if  the ET sensor senses a tower then it will begin moving backward until it reaches the left edge of the tower and no longer senses it
-If no tower is sensed it will drive forward and stop when the left edge of the tower is sensed

30sec-45sec
-Drive forward towards the center server tower
-When driving forward, while the left bumper isn’t pressed then drive slightly right into the pipe wall. When it is pressed then drive away from the wall. This being repeated will ensure the robot doesn't drift.
-Stop driving forward at the center tower once the approximate encoder distance is met.
-Use the same alignment procedure as in the second 15 seconds to align with the center tower
-Open claw and then raise the arm until the claw is at the top the center tower
-Close claw around botgal and lower arm so botgal is just above the ground.

45sec-60sec
-Turn the robot to the right 90 degrees so it is facing the analysis lab and backup room
-Drive forward until the robot senses the black line spanning across the whole board
-Drive forward a little past the line using encoders for precision
-Then open the claw to release the botgal into the analysis lab.
-Close claw and then turn around left 180 degrees to face the server racks

60sec-75sec
-Drive staring towards the server racks until bumper hits pipe
-Use the alignment procedure as described before to align with the central tower.
-Ride the wall forward using the left bumper like before 
-Stop after a certain distance using encoders so the robot is next to the right high tower.
-Raise arm with an opened claw
-Close claw around log and then lower arm just above the ground
-Turn left 90 degrees and back up until black line in front of the cyber security lab is sensed
-Turn right and back up until black center line is sensed

75sec-90sec
-Back up a little past the center line using encoders
-Lower the arm all the way so the cube is touching the ground 
-Open the claw to release the cube on the ground 
-Raise arm above the cube and close the claw
-Drive back using encoders and turn right to face the left high tower
-Drive forward until the bumpers hit the pvc pip in front of server racks
-Turn right 90 degrees and then align with left high tower

105sec-120sec
-Raise arm with an opened claw
-Close claw around log and then lower arm to about 5 inches of the ground.
-Turn left 90 degrees and back up until the black line in front of the cyber security lab is sensed
-Turn right and back up until the center line is sensed by cliff sensor
-Drive back a little after aligning with the center line so that the claw is over the cube that has already been placed
-Lower the arm so the cube touches the already placed one
-STOP CODE NO MORE MOVEMENT

*/



//Variables

int lspeed=185;   //left motor speed
int rspeed=185;   //right motor speed

int lwall=265;    //left motor wall ride speed
int rwall=220;    //right motor wall ride speed

int rTspeed=150;  //right motor turn speed
int lTspeed=150;  //left motor turn speed

float deg=1.12;   //encoders degrees conversion
int CM=10;        //encoders centimeters convertion

int ET = 0;       //ET sensor port
int towerDis = 1050;   //ET sensor tower distance threshhold value

int motor0 = 0;     //left arm motor portUSE THIS MOTOR TO READ POSITION TICKS
int motor1 = 1;     //second arm motor port
int armSpeed = 500; //arm motor speed

int claw=3;         //port for claw servo

int open = 1200;    //opened claw position
int close= 20;      //closed claw postion for botgal

int high = 850;     //high tower arm motor0 position (from all the way down)

int line = 1220;   //black line cliff sensor value


//Functions

void rturn(int angle);     //turn right in degrees using encoders
void lturn(int angle);     //turn left in degrees using encoders

void forward(int distance);  //drive forward in cm using encoders
void back(int distance);     //drive back in cm using encoders

void wallRide(int distance);       //wall ride forward using left bumper and encoders for distance in cm
void wallRideBack(int distance);   //wall ride back using left bumper and encoders for distance in cm
void wallSquare();                 //turns into wall until left bumper hits to become square with the wall

void onTower();       //Moves forward until tower is sensed by ET sensor
void offTower();      //Moves forward until tower is NOT sensed by ET sensor
void onTowerBack();   //Moves back until tower is sensed by ET sensor
void offTowerBack();  //Moves back until tower is NOT sensed by ET sensor

void align();  //Uses ET sensor to align with left edge of tower

void armUp(int position);    //Moves arm up using encoders position in ticks
void armDown(int position);  //Moves arm down
void armBump();              //Moves arm up until limit button is hit

void grabGal();    //Moves arm up from down position to high tower, grabs botgall, and moves arm down
void grabCube();   //Moves arm up from down position to high tower, grabs a yellow log cube, and moves arm down
void rackStack();  //Knocks over rackastack from start poition

void forwardLine1();  //drives forward until line is sensed
void forwardLine2();  //drives forward until it has PASSED a line
void backLine1();     //drives back until line is sensed
void backLine2();     //drives back until it has PASSED a line

//Main Create Program

int main()
{
  //wait_for_light(1);   // intitial setup code
  shut_down_in(120);
  create_connect();
  
  forward(4);
  lturn(90);    //turn towards server room
  
  /*
  forward(4);   //move a little away from wall
  rackStack();  //knock over rackastack
  */
  
  while(get_create_lbump() == 0) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
  
  create_drive_direct(-lspeed, -rspeed);   // backup from wall to avoid rubbing when turning
  msleep(100);
  
  rturn(85);     // turn to drive along wall
  forward(13);   // drive forward a little over to tower 1 (red tower) to get closer to alignment before using ET sensor
  msleep(250);
  
  align();       //aligns with left edge of tower 1 (red tower) using ET sensor
  msleep(250);
  
  wallRide(72);  // rides the server wall with bumpers to get to botgal
  align();       // aligns with left edge of center server tower using ET sensor
  
  forward(18);   // shifting over to acount for claw offset
  grabGal();     // lifting arm, grabbing botgal, and lowering arm
  msleep(250);
  
  rturn(90);     // turning directly away from server towers
  forward(57);   // driving towards analysis lab
  msleep(250);
  
  set_servo_position(claw,open);  //opening claw to drop botgal in analysis lab
  enable_servos();
  msleep(700);
  disable_servos();
  
  rturn(180);   //turns towards server racks
  while(get_create_lbump() == 0) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
  
  create_drive_direct(-lspeed, -rspeed);   // backup from wall to avoid rubbing when turning
  msleep(100);
  
  rturn(85);
  align();
  msleep(150);
  
  wallRide(38);
  msleep(250);
  align();
  msleep(150);
  grabCube();
  
  rturn(90);
  forwardLine1();
  lturn(90);
  backLine2();
  
  back(6);
  
  create_stop();     // ensuring stop code
  disable_servos();
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


void forwardLine1() {
  while(get_create_lfcliff() < line) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
}

void forwardLine2() {
  while(get_create_lfcliff() < line) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(lspeed, rspeed);
  }
  while(get_create_lfcliff() < line) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(lspeed, rspeed);
  }
  create_stop();
}



void backLine1() {
  while(get_create_lfcliff() < line) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(-lspeed, -rspeed);
  }
  create_stop();
}

void backLine2() {
  while(get_create_lfcliff() < line) {           // drives forward until bumpers contact pvc server wall
    create_drive_direct(-lspeed, -rspeed);
  }
  while(get_create_lfcliff() < line) {           // drives forward until bumpers contact pvc server wall
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
  cmpc(motor0);
  armDown(high);
  
  mav(motor0, -armSpeed);
  mav(motor1, -armSpeed);
  msleep(100);
  ao();
  
  msleep(300);
  armUp(100);
  freeze(motor0);
  freeze(motor1);
  
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
  rturn(45);
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

