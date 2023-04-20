// claw positions (servo value positions)
int clawopen= ;
int clawredring= ;
int claworaangering= ;
int clawyellowring= ;
int clawgreenring= ;
int clawbluering= ;

//arm movement
int liftspeed= ; //positive value moves the arm from the ground, up and towards the tower. Negative value moves the arm away from the tower and down towards the ground
int armtall= ; //moves claw from cube drop position to the top of the tall tower
int armshort= ; //moves claw from cube drop position to the top of the short tower
int dropcubet= ; //moves cube from top of tall tower to the location to drop it
itn dropcubes= ; //moves cube from the top of short tower to the location to drop it
int armredring= ; //moves arm from dropping cube to grabbing red ring from rock-a-stack
int armorangering= ; //moves arm from dropping cube to grabbing orange ring from rock-a-stack
int armyellowring= ; //moves arm from dropping cube to grabbing yellow ring from rock-a-stack
int armgreenring= ; //moves arm from dropping cube to grabbinggreen  ring from rock-a-stack
int armbluering= ; //moves arm from dropping cube to grabbing blue ring from rock-a-stack
int tostand= ; //moves arm from cube drop position to ground to grab ring stand 

// ports
int claw= ;
int arm1= ;
int arm2= ;

//general movement
int speed= ; //speed for driving
int cm;  //ticks straight cm convertion
int turnspeed= ; //speed for turning. Use positive and negative

//functions
void grabstand {
  set_servo_position(claw,clawclose);
}

void ringstand { 		//moves arm from cube drop to ground and closes claw to grab ring stand for transportation
cmpc(arm1)
while(gmpc(arm1)>tostand) {
  mav(arm1,-liftspeed);
  mav(arm2,-liftspeed);
}
  freeze(arm1);
  freeze(arm2);
  Set_servo_position(claw,clawclose);
}

void tallcube { 		//moves claw from down on the ground to the top tall tower, grabs cube and moves to position to drop cube, drops cube
set_servo_position(claw,clawopen);
cmpc(arm1);
while (gmpc(arm1)<armtall) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawcube);
cmpc(arm1);
while(gmpc(arm1)>dropcube) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
} 
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawopen);
cmpc(arm1);
}

void shortcube {			//moves claw from down on ground to short tower, grabs cube, moves to position to drop, drops cube
set_servo_position(claw,clawopen);
cmpc(arm1);
while (gmpc(arm1)<armshort) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawcube);
cmpc(arm1);
while(gmpc(arm1)>dropcube) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
} 
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawopen);
cmpc(arm1);
}

void redring {			//moves arm from cube drop position to rock-a-stack, grabs red ring, lifts ring to short tower, releases ring, returns to cube drop position.
while(gmpc(arm1)>-armredring) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawredring);
cmpc(arm1);
while(gmpc(arm1)<-armredring) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
cmpc(arm1);
While(gmpc(arm1)<armshort) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawopen);
cmpc(arm1);
while(gmpc(arm1)>-armshort) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
}
  
void orangering {			//moves arm from cube drop position to rock-a-stack, grabs orange ring, lifts ring to short tower, releases ring, returns to cube drop position.
while(gmpc(arm1)>-armorangering) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,claworangering);
cmpc(arm1);
while(gmpc(arm1)<-armorangering) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
cmpc(arm1);
While(gmpc(arm1)<armshort) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawopen);
cmpc(arm1);
while(gmpc(arm1)>-armshort) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
}
  
void yellowring {			//moves arm from cube drop position to rock-a-stack, grabs yellow ring, lifts ring to tall tower, releases ring, returns to cube drop position.
while(gmpc(arm1)>-armyellowring) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawyellowring);
cmpc(arm1);
while(gmpc(arm1)<-armyellowring) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
cmpc(arm1);
While(gmpc(arm1)<armtall) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawopen);
cmpc(arm1);
while(gmpc(arm1)>-armtall) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
}
  
void greenring {			//moves arm from cube drop position to rock-a-stack, grabs green ring, lifts ring to tall tower, releases ring, returns to cube drop position.
while(gmpc(arm1)>-armgreenring) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawgreenring);
cmpc(arm1);
while(gmpc(arm1)<-armgreenering) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
cmpc(arm1);
While(gmpc(arm1)<armtall) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawopen);
cmpc(arm1);
while(gmpc(arm1)>-armtall) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
}
  
void bluering {			//moves arm from cube drop position to rock-a-stack, grabs blue ring, lifts ring to tall tower, releases ring, returns to cube drop position.
while(gmpc(arm1)>-armbluering) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawbluering);
cmpc(arm1);
while(gmpc(arm1)<-armbluering) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
cmpc(arm1);
While(gmpc(arm1)<armtall) {
mav(arm1,liftspeed);
mav(arm2,liftspeed);
}
freeze(arm1);
freeze(arm2);
set_servo_position(claw,clawopen);
cmpc(arm1);
while(gmpc(arm1)>-armtall) {
mav(arm1,-liftspeed);
mav(arm2,-liftspeed);
}
freeze(arm1);
freeze(arm2);
}

void wallride {
create_drive_direct(speed, (speed+10));
}

void driveforward(int distance) {
set_create_distance(0);
while(get_create_distance()< (distance*cm)) {
create_drive_direct(speed,speed);
}
create_stop();

void rturn(int angle) {
set_create_total_angle(0);
while(get_create_total_angle()<angle*degrees)) {
create_drive_direct(turnspeed,-turnspeed);
}
create_stop();
}

void lturn(int angle) {
set_create_total_angle(0);
while(get_create_total_angle()<(angle*degrees)) {
create_drive _direct(-turnspeed,turnspeed);
}
create_stop();
}

void toorange {
  open_camera();
  while(get_object_area_  {
  wallride;
  }
        create_stop();
        }
        
void toyellow {
  open_camera();
  while(get_object_area  {
    wallride;
  }
        create_stop();
        }
  
void togreen {
  open_camera();
  while(get_object_area   {
  wallride;
  }
        create_stop();
        }
void toblue {
  open_camera();
  while(get_object_area   {
    create_drive_direct(-speed,-speed);
  }
        create_stop();
        }
  
  
//main
int main {
  //leave start box, prep for cubes and rings
  grabstand; //arm starts down, claw closes around ring stand for transportation
  driveforward(_);
  rturn(90)
  create_stop();
  shortcube;
  redring;
  ringstand;
  toorange;
  shortcube;
  orangering;
  ringstand;
  toyellow;
  tallcube
  yellowring;
  ringstand;
  togreen;
  tallcube;
  greenring;
  ringstand;
  toblue;
  tallcube;
  bluering;
  
  
  
  
