// servo
int sweep;
int lpos;
int rpos;

// motors
int left;
int right;
int lspeed;
int rspeed;

//ir sensors
int ir
int floor;
int line;
int green;
int red; 

int error;

int main() {
  //drive to firewall
  rturn(90);
  drive_forward(100);
  lturn(90);
  // use claw to pick up firewall and place on back of robot
  grab_firewall();
  //line up with black line
  while((analog(ir)>=(floor-error)) && (analog(ir)>=(floor+error)){
    mav(right, rspeed);
    mav(left, lspeed);
    msleep(10);
    lturn(90);
  }
  // drive along black line and sort poms
  int i;
  for (i = 0, i < 10, i++) {
    while(((analog(ir)>=(floor-error)) && (analog(ir)>=(floor+error)) || ((analog(ir)>=(line-error)) && (analog(ir)>=(line+error)) {
      line_follow();
      msleep(10);
    }
    while(((analog(ir)>=(green-error)) && (analog(ir)>=(green+error)) || ((analog(ir)>=(red-error)) && (analog(ir)>=(red+error)) {
      sort();
      msleep(10);
    }                                                                      
  }
  //turn and place firewall
  place_firewall();
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
  
  //place green drive in servo rack
  
  //grab green drive and place in servo rack
  
  //grab final green drive and place in servo rack
  
}

void line_follow() {
  if((analog(ir)>=(floor-50)) && (analog(ir)>=(floor+50)) {
    mav(left, lspeed);
    msleep(10);
  }
  if((analog(ir)>=(line-50)) && (analog(ir)>=(line+50)) {
    mav(right, rspeed);
    msleep(10);
  }
   msleep(10);
}
    
     
void sort() {
  if((analog(ir)>=(green-error)) && (analog(ir)>=(green+error)) {
    set_servo_position(sweep, lpos);
    msleep(250);
  }
  if((analog(ir)>=(red-error)) && (analog(ir)>=(red+error)) {
    set_servo_position(sweep, rpos);
    msleep(250);
  }
    msleep(10);
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
     
void find_tower() {
  
}
   
void grab_firewall() {
  
}
     
void place_firewall(){
  
}
     
void grab_drive(){
  
}
     
void place_drive(){
  
}
