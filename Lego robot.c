#include <kipr/wombat.h>
// servo
int sweeper = 0;
int lpos = 500;
int rpos = 1170;

/*
int arm;
int claw;
int up;
int mid;
int down;
int open;
int close; 
*/
// motors
int left = 3;
int right = 0;
int lspeed = 940;
int rspeed = 1000;
int cm = 100;
int degrees = 12;

//ir sensors
int ir = 0;
int line = 1700;
//int gray;

void line_follow(int distance) {
  int range = analog(ir) - line;
  float modifier = range*0.05;
  cmpc(right);
  cmpc(left);
  while ((gmpc(right) + gmpc(left))/2 < distance*cm) {
      if(analog(ir) > line) {
    	mav(right, rspeed + modifier);
   	 	mav(left, lspeed - modifier);
	  msleep(10);
      }
      if(analog(ir) < line) {
    	mav(right, rspeed - modifier);
   	 	mav(left, lspeed + modifier);
	      msleep(10);
      }
    msleep(10);
	  freeze(right);
	  freeze(left);
  }
}
    
     
void sweep(int direction) {
    
    
  if(direction == 0){
    enable_servo(sweeper);
    set_servo_position(sweeper, lpos);
    msleep(100);
    
  }
  if(direction == 1){
    enable_servo(sweeper);
    set_servo_position(sweeper, rpos);
    msleep(100);
    
  }
    disable_servo(sweeper);
}
     
void lturn(int angle) {    // lturn: turns left in degrees
cmpc(right);
while(gmpc(right) < (angle*degrees)) {
    mav(right, rspeed);
    mav(left, -lspeed);
}
freeze(right);
freeze(left);
msleep(100);    
}     
     
void rturn(int angle) {    
	cmpc(left);
	while(gmpc(left) < (angle*degrees)) {
    mav(right, -rspeed);
    mav(left, lspeed);
    msleep(10);    
  }
	freeze(right);
	freeze(left);
    msleep(100);
}   
     
void drive_forward(int distance) {
  cmpc(right);
  cmpc(left);  
    /*while (gmpc(right) < (distance*cm)) {
    mav(left, lspeed);
    mav(right, rspeed);
  }*/
  while ((gmpc(right)+gmpc(left)/2) < (distance*cm)) {
    if (gmpc(right) > gmpc(left)) {  
    	mav(left, lspeed*(gmpc(right)/gmpc(left)));
    	mav(right, rspeed);
	msleep(10);    
    }
    if (gmpc(left) > gmpc(right)) {  
    	mav(right, rspeed*(gmpc(left)/gmpc(right)));
    	mav(left, lspeed);
	msleep(10);
    } 
    if(gmpc(left) == gmpc(right)){
    mav(right, rspeed);
    mav(left, lspeed);    
    msleep(10);   
	    
    } 
      msleep(10);
  } 
}

void drive_backward(int distance) {
  cmpc(right);
  cmpc(left);  
  /*while (abs(gmpc(right)) < (distance*cm)) {
    mav(left, -lspeed);
    mav(right, -rspeed);  
  }*/
  while (abs((gmpc(right)+gmpc(left))/2) < (distance*cm)) {
    if (gmpc(right) > gmpc(left)) {  
    	mav(left, -lspeed*(gmpc(right)/gmpc(left)));
    	mav(right, -rspeed);
        msleep(10);
    }
    if (gmpc(left) > gmpc(right)) {  
    	mav(right, -rspeed*(gmpc(left)/gmpc(right)));
    	mav(left, -lspeed);
        msleep(10);
    }  
    if(gmpc(left) == gmpc(right)){
    mav(right, -rspeed);
    mav(left, -lspeed);
    msleep(10);    
    }  
    
  }
}     

void main() {
  //drive to firewall
    
  drive_forward(5);  
  rturn(90);
  drive_forward(80);
  lturn(90);
  //line up with black line
  while((analog(ir) < line)){
    mav(right, rspeed);
    mav(left, lspeed);
    msleep(10);
  }
    drive_forward(15);
    lturn(90);
        
  // drive along black line and sort poms
  line_follow(30);
  freeze(right);
  freeze(left);	
	
  msleep(100);  
  sweep(0); 
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100);   
  sweep(1); 
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100);   
  sweep(0); 
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100);   
  sweep(1); 
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100);   
  sweep(0);       
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100); 
  sweep(1);
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100); 
  sweep(0);   
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100);   
  sweep(1); 
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100);   
  sweep(0);       
  line_follow(30);
  freeze(right);
  freeze(left);
	
  msleep(100);   
  sweep(1);      
  /*turn and place firewall
  rturn(90);
  enable_servo(claw);
  enable_servo(arm);
  set_servo_position(arm, down);
  msleep(100);     
  set_servo_position(claw, open);
  msleep(100);      
  */
        
  //head towards watch floor
  lturn(90);
  drive_forward(50);  
  sweep(1);
        
  //leave green poms in watch floor
  drive_backward(15);
  lturn(90);     
        
  //leave red poms in analysis labs
  drive_forward(50);
  rturn(90);
  drive_forward(50);
  sweep(0);	
  drive_backward(50);
  lturn(90);          
 
     
    
  
}

