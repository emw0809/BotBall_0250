// claw positions
Int clawopen= ;
Int clawredring= ;
Int claworgring= ;
Int clawyelring= ;
Int clawgrering= ;
Int clawbluring= ;

//arm movement
Int liftspeed= ; //positive value moves the arm from the ground, up and towards the tower. Negative value moves the arm away from the tower and down towards the ground
Int armtall= ; //moves claw from cube drop position to the top of the tall tower
Int armshort= ; //moves claw from cube drop position to the top of the short tower
Int dropcubet= ; //moves cube from top of tall tower to the location to drop it
Itn dropcubes= ; //moves cube from the top of short tower to the location to drop it
Int armredring= ; //moves arm from dropping cube to grabbing red ring from rock-a-stack
Int armorgring= ; //moves arm from dropping cube to grabbing orange ring from rock-a-stack
Int armyelring= ; //moves arm from dropping cube to grabbing yellow ring from rock-a-stack
Int armgrering= ; //moves arm from dropping cube to grabbinggreen  ring from rock-a-stack
Int armbluring= ; //moves arm from dropping cube to grabbing blue ring from rock-a-stack

// ports
Int claw= ;
Int arm1= ;
Int arm2= ;

//general movement
Int speed= ; //speed for driving
Int cm;  //ticks straight cm convertion


Void ringstand { 		//closes claw to grab ring stand for transportation
Set_servo_position(claw,clawclose);
}

Void tallcube { 		//moves claw from down on the ground to the top tall tower, grabs cube and moves to position to drop cube, drops cube
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

Void shortcube {			//moves claw from down on ground to short tower, grabs cube, moves to position to drop, drops cube
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

Void redring {			//moves arm from cube drop position to rock-a-stack, grabs red ring, lifts ring to short tower, releases ring, returns to cube drop position.
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

Void wallride {
create_drive_direct(speed, (speed+10));
}

Void driveforward(int distance) {
set_create_distance(0);
while(get_create_distance()< (distance*cm)) {
create_drive_direct(speed,speed);
}
create_stop();

Void rturn(int angle) {
set_create_total_angle(0);
while(get_create_total_angle()<angle*degrees)) {
create_drive_direct(turnspeed,-turnspeed);
}
create_stop();

Void lturn(int angle) {
set_create_total_angle(0);
while(get_create_total_angle()<(angle*degrees)) {
create_drive _direct(-turnspeed,turnspeed);
}
create_stop();

Int main {


