// servo
int sweep;
int lpos;
int rpos;
int arm;

int claw;
int up;
int mid;
int down;
int open;
int close; 

// motors
int left;
int right;
int lspeed;
int rspeed;

//ir sensors
int ir;
int line;
int gray;



int main() {
  //drive to firewall
 rturn(90);
  drive_forward(100);
  lturn(90);
  // use claw to pick up firewall and place on back of robot
  grab_firewall();
  //line up with black line
  while((analog(ir) > gray){
    mav(right, rspeed);
    mav(left, lspeed);
    msleep(10);
  }
    lturn(90);
        /*
  // drive along black line and sort poms
  line_follow(50);
  sweep(0); 
  line_follow(50);
  sweep(0); 
  line_follow(50);
  sweep(0); 
 
  //turn and place firewall
  rturn(90);
  enable_servo(claw);
  enable_servo(arm);
  set_servo_position(arm, down);
  msleep(100);     
  set_servo_position(claw, open);
  msleep(100);      
        
  //head towards watch floor
  lturn(90);
  drive_forward(50);  
        
  //leave green poms in watch floor
  drive_backward(75);
  lturn(90);     
        
  //leave red poms in analysis labs
  drive_forward(50);
  rturn(90);
  drive_forward(50);
  drive_backward(50);
  lturn(90);          
        
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

void line_follow(int distance) {
  int range = analog(ir)-floor;
  float modifier = range*0.02;
  cmpc(right);
  cmpc(left);
  while (gmpc(right) + gmpc(left) < distance*cm) {
    mav(right, rspeed - modifier);
    mav(left, lspeed + modifier);
    msleep(10);
  }
}
    
     
void sort(bool direction) {
  if(direction = 0){
    enable_servo(sweep);
    set_servo_position(sweep, left);
    msleep(10);
    
  }
  if(direction = 1){
    enable_servo(sweep);
    set_servo_position(sweep, right);
    msleep(10);
    
  }
}
     
void lturn(int angle) {    // lturn: turns left in degrees
cmpc(right);
while(gmpc(right) < (angle*degrees)) {
    mav(right, rspeed);
    mav(left, -lspeed);
}
freeze(right);
freeze(left);
}     
     
void rturn(int angle) {    
cmpc(left);
while(gmpc(left) < (angle*degrees)) {
    mav(right, -rspeed);
    mav(left, lspeed);
}
freeze(right);
freeze(left);
}   
     
void drive_forward(int distance) {
  cmpc(right);
  while (gmpc(right) < (distance*cm)) {
    mav(left, lspeed);
    mav(right, rspeed);
  }
}
     
void drive_backward(int distance) {
  cmpc(right);
  while (abs(gmpc(right)) < (distance*cm)) {
    mav(left, -lspeed);
    mav(right, -rspeed);
  }
}     
     
void find_drive() {
  
}
     
void tower_align() {
  cmpc(right);
  while(analog(ir) > gray){
    mav(right, -rspeed);
    msleep(10);
  }
  
  while(abs(gmpc(left)) < abs(gmpc(right))) {
    mav(left, -lspeed);
  }
}
   
