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
int cm = 93;
int degrees = 13;

//ir sensors
int ir = 0;
int line = 1700;
//int gray;

void line_follow(int distance) {
  int range = analog(ir) - line;
  float modifier = range*0.02;
  cmpc(right);
  cmpc(left);
  while (gmpc(right) + gmpc(left) < distance*cm) {
    mav(right, rspeed - modifier);
    mav(left, lspeed + modifier);
    msleep(10);
  }
}
    
     
void sweep(int direction) {
  if(direction == 0){
    enable_servo(sweeper);
    set_servo_position(sweeper, lpos);
    msleep(10);
    
  }
  if(direction == 1){
    enable_servo(sweeper);
    set_servo_position(sweeper, rpos);
    msleep(100);
    
  }
}
     
void lturn(int angle) {    // lturn: turns left in degrees
cmpc(right);
while(gmpc(right) < (angle*degrees)) {
    mav(right, rspeed);
    mav(left, -lspeed);
}
ao(right);
ao(left);
}     
     
void rturn(int angle) {    
	cmpc(left);
	while(gmpc(left) < (angle*degrees)) {
    mav(right, -rspeed);
    mav(left, lspeed);
    msleep(10);    
  }
ao(right);
ao(left);
}   
     
void drive_forward(int distance) {
  cmpc(right);
  cmpc(left);  
    while (gmpc(right) < (distance*cm)) {
    mav(left, lspeed);
    mav(right, rspeed);
  }
  /*while ((gmpc(right)+gmpc(left)/2) < (distance*cm)) {
    if (gmpc(right) > gmpc(left)) {  
    	mav(left, lspeed*(gmpc(right)/gmpc(left)));
    	mav(right, rspeed);
    }
    if (gmpc(left) > gmpc(right)) {  
    	mav(right, rspeed*(gmpc(left)/gmpc(right)));
    	mav(left, lspeed);
    }  
    if(gmpc(left) == gmpc(right)){
    mav(right, rspeed);
    mav(left, lspeed);
    }
  } */
}

void drive_backward(int distance) {
  cmpc(right);
  cmpc(left);  
  while (abs(gmpc(right)) < (distance*cm)) {
    mav(left, -lspeed);
    mav(right, -rspeed);  
  }
 /* while (abs((gmpc(right)+gmpc(left))/2) < (distance*cm)) {
    if (abs(gmpc(right)) > abs(gmpc(left))) {  
    	mav(left, -lspeed*(gmpc(right)/gmpc(left)));
    	mav(right, -rspeed);
        msleep(10);
    }
    if (abs(gmpc(left)) > abs(gmpc(right))) {  
    	mav(right, -rspeed*(gmpc(left)/gmpc(right)));
    	mav(left, -lspeed);
        msleep(10);
    }  
  }*/
}     

void main() {
  //drive to firewall
  drive_forward(100);  
  rturn(90);
  drive_forward(75);
  lturn(90);
  //line up with black line
  while((analog(ir) > line)){
    mav(right, rspeed);
    mav(left, lspeed);
    msleep(10);
  }
    lturn(90);
        
  // drive along black line and sort poms
  line_follow(30);
  sweep(0); 
  line_follow(30);
  sweep(1); 
  line_follow(30);
  sweep(0); 
  line_follow(30);
  sweep(1); 
  line_follow(30);
  sweep(0);       
  line_follow(30);
  sweep(1);
  line_follow(30);
  sweep(0);   
  line_follow(30);
  sweep(1); 
  line_follow(30);
  sweep(0);       
  line_follow(30);
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
        
  //leave green poms in watch floor
  drive_backward(15);
  lturn(90);     
        
  //leave red poms in analysis labs
  drive_forward(50);
  rturn(90);
  drive_forward(50);
  drive_backward(50);
  lturn(90);          
 /*       
 //grab green drive and wait for create
  find_drive();      
  enable_servo(arm);
  set_servo_position(arm, mid);
  msleep(100);      
  enable_servo(claw);
  set_servo_position(claw, close);      
  msleep(100);
        
        
  //place green drive in servo rack
  rturn(100);
  drive_backward(50);      
  tower_align();
        
  //grab green drive and place in servo rack
  rturn(180):
  find_drive(); 
  enable_servo(arm);
  set_servo_position(arm, mid);
  msleep(100);      
  enable_servo(claw);
  set_servo_position(claw, close);      
  msleep(100);      
  rturn(100);
  drive_backward(50);      
  tower_align();   
  */
  //grab final green drive and place in servo rack
     
    
  
}


