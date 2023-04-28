#include <kipr/wombat.h>
//pseudocode
/*
0-15 seconds
Turn right, and move forward to grab the first set of poms
Move backward, and turn left to grab the second set of poms

15-30
Continue moving forward past the black line
Turn right until lined up with the black line
Line follow, and sweep up the next 3 sets of poms

30-45
Turn 180 degrees until lined up with black line again
Line follow and sweep up the next 2 sets of 2 poms, and 2 sets of single poms
Turn left 90 degrees
Drive forward into the analysis lab
Leave half of the poms in the analysis lab

45-60
Back up out of the analysis lab
Turn right 90 degrees
Drive forward until adjacent to the watch floor
Turn left 90 degrees
Drive into the watch floor
Leave the other half of the poms in the watch floor
Back out of the watch floor


*/

// servo
int sweeper = 1; //port of sweeper
int sharky = 3; //port of wireshark servo
int lpos = 500; //position of sweeper servo on the left
int rpos = 1170; //position of sweeper servo on the right
int servstop = 100; //msleep for servos after each turn

// motors
int left = 2; //port of left motor
int right = 1; //port of right motor
int lspeed = 1000; //speed of left motor
int rspeed = 1000; //speed of right motor
int cm = 100; //constant used to translate encoders into centimeters
int degrees = 12; //constant used to translate encoders into degrees

//ir sensors
int ir = 0; //port of ir sensor
int line = 2200; //ir value of black line
//int gray;

//code for following a line on the right
//DESCRIPTIONS OF EACH FUNCTION AT THE BOTTOM OF THE DOC
void line_follow(int distance);
void line_follow_left(int distance1);
void line_follow_repos(int distance4);
void line_follow_back(int distance1);
void shark (int cycle);
void sweep (int direction);
void lturn(int angle);
void rturn(int angle);
void drive_forward(int distance);
void drive_backward(int distance);

int main() {
  
  //wait_for_light(1);
  shut_down_in(120);
   //pick up first poms
  sweep(0);
  shark(2);
  drive_forward(2);
  msleep(100);
  rturn(15);
  drive_forward(15);
  sweep(1);
   //pick up more poms
  drive_backward(12);
  lturn(27);
  drive_forward(16);
  sweep(0);
  //pick up more poms
  drive_forward(10);
  rturn(25);
  sweep(1);
    //turn onto the line so that it follows to the next set of poms
  drive_forward(8);
  drive_forward(7);
  while((analog(0)<1500)){
  mav(1, -rspeed);
  mav(2, lspeed);
  msleep(10);
  }
  rturn(5);
    
  //sort poms
  mav(right, 0);
  mav(left, 0);
  line_follow_repos(3);
  line_follow_left(7);
  sweep(0);
  //sort next set
  line_follow_repos(5);
  line_follow_left(13);
  sweep(1);
  //sort next set
  line_follow_left(15);
  sweep(0);
  //sort next set
  drive_forward(10);
  sweep(1);
  //sort next set
  drive_forward(8);
  sweep(0);
  //turn to set up for getting the wireshark
  lturn(120);
  drive_forward(2);
  sweep(1);
  drive_forward(1);
  sweep(0);
  lturn(43);
  //get the wireshark
  drive_backward(2);
  shark(1);
  msleep(500);
  shark(2);
  drive_forward(1);
  shark(1);
  drive_forward(5);
  //turn onto the line
   while((analog(0)<1500)){
  mav(1, rspeed);
  mav(2, lspeed-500);
  msleep(10);
  }
  printf("Turned successfully/n");
  mav(1,0);
  mav(2,0);
  
        
  // drive along black line and sort poms
  line_follow(50);
  freeze(right);
  freeze(left);	
  sweep(1);
	
  msleep(100);   
  msleep(100);
  line_follow(15);
  freeze(right);
  freeze(left);
	
  msleep(100);   
  sweep(0); 
  msleep(100);
  line_follow(25);
  freeze(right);
  freeze(left);
	

	
        
  //head towards analysis lab
  lturn(90);
  sweep(1);
  drive_forward(20);  
        
  //leave green poms in analysis lab
  drive_backward(28);
  rturn(80);     
        
  //leave red poms in watch floor labs
  drive_forward(49);
  lturn(88);
  drive_forward(38);
  sweep(3);
  drive_backward(10);
  drive_forward(5);
  sweep(3);
  drive_backward(10);
  drive_forward(5);
  drive_backward(26);
  lturn(90);
     
  return 0;   
  }
void line_follow(int distance) {
  cmpc(right);
  cmpc(left);
  while ((gmpc(right) + gmpc(left))/2 < distance*cm) {
      if(analog(ir) > line) {
    	mav(right, rspeed-400);
   	 	mav(left, lspeed);
        msleep(1);
	  
      }
      if(analog(ir) < line) {
    	mav(right, rspeed);
   	 	mav(left, lspeed-400);
        msleep(1);
      }
      msleep(10);
	  freeze(right);
	  freeze(left);
  }
}
//code for following a line on the left
void line_follow_left(int distance1) {
  cmpc(right);
  cmpc(left);
  while ((gmpc(right) + gmpc(left))/2 < distance1*cm) {
      if(analog(ir) > line) {
    	mav(right, rspeed);
   	 	mav(left, lspeed-400);
        msleep(1);
	  
      }
      if(analog(ir) < line) {
    	mav(right, rspeed-400);
   	 	mav(left, lspeed);
        msleep(1);
      }
      msleep(10);
	  freeze(right);
	  freeze(left);
  }
}
//code for following a line when the robot needs to be repositioned
void line_follow_repos(int distance4) {
  cmpc(right);
  cmpc(left);
  while ((gmpc(right) + gmpc(left))/2 < distance4*cm) {
      if(analog(ir) > line) {
    	mav(right, rspeed);
   	 	mav(left, lspeed-700);
        msleep(1);
	  
      }
      if(analog(ir) < line) {
    	mav(right, rspeed-700);
   	 	mav(left, lspeed);
        msleep(1);
      }
      msleep(10);
	  freeze(right);
	  freeze(left);
  }
}
//code for the robot to follow a line backward
void line_follow_back(int distance1) {
  cmpc(right);
  cmpc(left);
  while ((gmpc(right) + gmpc(left))/2*(-1) > distance1*cm*-1) {
      if(analog(ir) > line) {
    	mav(right, -rspeed-400);
   	 	mav(left, -lspeed);
        msleep(1);
	  
      }
      if(analog(ir) < line) {
    	mav(right, -rspeed);
   	 	mav(left, -lspeed-400);
        msleep(1);
      }
      msleep(10);
	  freeze(right);
	  freeze(left);
  }
}
//code for the servo that grabs the wireshark
void shark (int cycle) {
  if (cycle == 1){
      enable_servo(sharky);
      set_servo_position(sharky,1850);
      msleep(500);
  }
  if (cycle == 2) {
      enable_servo(sharky);
      set_servo_position(sharky, 276);
      msleep(500);
  }
}
//code for sweeping poms     
void sweep(int direction) {
    
  if(direction == 3){
    enable_servo(sweeper);

    set_servo_position(sweeper,750);
    msleep(100);
    
  }
    
  if(direction == 0){
    enable_servo(sweeper);
    set_servo_position(sweeper, 1036);
    msleep(servstop);
    set_servo_position(sweeper, 902);
    msleep(servstop);
    set_servo_position(sweeper, 768);
    msleep(servstop);
    set_servo_position(sweeper, 634);
    msleep(servstop);
    set_servo_position(sweeper, lpos);
    msleep(100);
    
  }
  if(direction == 1){
    enable_servo(sweeper);
    set_servo_position(sweeper, 634);
    msleep(servstop);
    set_servo_position(sweeper, 768);
    msleep(servstop);
    set_servo_position(sweeper, 902);
    msleep(servstop);
    set_servo_position(sweeper, 1036);
    msleep(servstop);
    set_servo_position(sweeper, rpos);
    msleep(100);
    
  }
    disable_servo(sweeper);
}
//code for turning left     
void lturn(int angle) {    // lturn: turns left in degrees
cmpc(right);
while(gmpc(right) < (angle*degrees)) {
    mav(right, rspeed-80);
    mav(left, -(lspeed-80));
}
freeze(right);
freeze(left);
msleep(100);    
}     
//code for turning right     
void rturn(int angle) {    
	cmpc(left);
	while(gmpc(left) < (angle*degrees)) {
    mav(right, -(rspeed-50));
    mav(left, lspeed-50);
    msleep(10);    
  }
	freeze(right);
	freeze(left);
    msleep(100);
}   
//code for driving forward     
void drive_forward(int distance) {
  cmpc(right);
  cmpc(left);  
    /*while (gmpc(right) < (distance*cm)) {
    mav(left, lspeed);
    mav(right, rspeed);
  }*/
  while ((gmpc(right)+gmpc(left)/2) < (distance*cm)) {
    mav(right, rspeed);
    mav(left, lspeed);    
    msleep(10);
    printf("Not yet...\n");
	    
      msleep(10);
  } 
  freeze(left);
  freeze(right);
}
//code for driving backward
void drive_backward(int distance) {
  cmpc(right);
  cmpc(left);  
  /*while (abs(gmpc(right)) < (distance*cm)) {
    mav(left, -lspeed);
    mav(right, -rspeed);  
  }*/
  while (abs((gmpc(right)+gmpc(left))/2) < (distance*cm)) {  
    mav(right, -rspeed);
    mav(left, -lspeed);
    
    
  }
    freeze(right);
    freeze(left);
}    

