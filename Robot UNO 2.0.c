
// touch sensors
int FRtouch=0;   // Front right touch
int FLtouch=1;   // Front left touch
int BRtouch=2;   // Back right touch
int BLtouch=3;   // Back left touch

// limit switches
int uptouch=4;     // touch sensor to indicate when arm is up to a tower
int downtouch=5;   // touch sensor to indicate when arm is down to grab ring
int midtouch=6;    // touch sensor to indicate when arm is in place to store a cube in stack

// motors
int arm=2;       // large arm motor port
int ldrive=0;    
int rdrive=1;

// motor speeds
int armspeed;
int lspeed=400;    // left wheel speed
int rspeed=400;    // right wheel speed

int Tlspeed=300;   // left wheel turning speed
int Trspeed=300;   // right wheel turning speed

int wallride=450;  // wallriding right wheel speed

// analog sensors
int ET=0;

// servos
int claw1=0;    // Ring claw port
int claw2=1;    // Cube claw port

// servo posistions
int cubeOpen;    // Cube claw open servo position
int cubeClose;   // Cube claw closed servo position

// ring claw open positions from smallest to largest ring
int cR1;
int cR2;
int cR3;
int cR4;
int cR5;
// ring claw closed positions from smallest to largest ring
int oR1;
int oR2;
int oR3;
int oR4;
int oR5;
// fully open ring claw position(for Botgal)
int fullopen;


// other
int lineCount=0;  // number of lines the robot has passed
int degrees;      // ticks turn conversion
int CM;           // ticks straight cm convertion
int direction;    // variable for direction (positive 1 or negative 1)
int currentTower;
int card;
int lcenter=70;
int rcenter=90;
int towerDis;
int ETcount;
int ETlimit;








// FUNCTIONS

void rturn(int angle) {    // rturn: turns right in degrees

set_create_total_angle(0);
while(abs(set_create_total_angle()) < (angle*degrees)) {
    create_drive_direct(Tlspeed, -Trspeed);
}
create_stop();
}

void lturn(int angle) {    // lturn: turns left in degrees

set_create_total_angle(0);
while(abs(get_create_total_angle()) < (angle*degrees)) {
    create_drive_direct(-Tlspeed, Trspeed);
}
create_stop();
}

void driveForward(int distance) {    // driveForward: drives forward in cm

set_create_distance(0);
while(abs(get_create_distance()) < (distance*CM)) {
    create_drive_direct(Tlspeed, Trspeed);
}
create_stop();
}

void driveBack(int distance) {    // driveForward: drives backward in cm

set_create_distance(0);
while(abs(get_create_distance()) < (distance*CM)) {
    create_drive_direct(-Tlspeed, -Trspeed);
}
create_stop();
}

void driveAsist(int distance) {    // driveAsist: drives forward in cm an balances encoders (CANNOT BE USED FOR CREATE)

cmpc(rdrive);
cmpc(ldrive);
while(((gmpc(rdrive)+gmpc(ldrive))/2) < (distance*CM)) {
    

    if(gmpc(rdrive) = gmpc(ldrive)) {
        mav(rdrive, 1000);
        mav(ldrive, 1000);
        msleep(10);
    } else if(gmpc(rdrive) < gmpc(ldrive)) {
        mav(rdrive, 1000);
        mav(ldrive, 925);
        msleep(10);
    } else {
        mav(rdrive, 925);
        mav(ldrive, 1000);
        msleep(10);
    }
    
}
freeze(rdrive);
freeze(ldrive);
}

void rturnAsist(int angle) {    // rturnAsist: turns right in degrees and balances encoders (CANNOT BE USED FOR CREATE)

cmpc(rdrive);
cmpc(ldrive);
while(((abs(gmpc(rdrive)) + gmpc(ldrive)) /2) < (angle*degrees)) {
    

    if(abs(gmpc(rdrive)) = gmpc(ldrive)) {
        mav(rdrive, -1000);
        mav(ldrive, 1000);
        msleep(10);
    } else if(abs(gmpc(rdrive)) < gmpc(ldrive)) {
        mav(rdrive, -1000);
        mav(ldrive, 925);
        msleep(10);
    } else {
        mav(rdrive, -925);
        mav(ldrive, 1000);
        msleep(10);
    }
    
}
freeze(rdrive);
freeze(ldrive);
}


void squareBUMP() {    // squareBUMP: squares up on front with bumpers

while(get_create_lbump()=0) || (get_create_rbump()=0) {
    create_drive_direct(ldrive, rdrive);
}
create_stop();
}

void squareFRONT() {    // squareFRONT: squares up on front with touch sensors

while((digital(FRtouch)=0) || (digital(FLtouch)=0)) {
    create_drive_direct(ldrive, rdrive);
}
create_stop();
}

void squareBACK() {    // squareBACK: squares up on back with touch sensors

while((digital(BRtouch)=0) || (digital(BLtouch)=0)) {
    create_drive_direct(ldrive, rdrive);
}
create_stop();
}



void towerPOSITION(int line) {    // towerPOSITION: moves robot over the entered number of towers, enter negative tower number to go backwards

if(line>0) {
    direction= 1;
} else {
    direction= -1;
}

while (lineCount<abs(line)) {

    while(cliffLeft()<irGrey) {
        create_drive_direct(lspeed*direction, wallride*direction)
        msleep(10);
    }
    while(cliffLeft()>irGrey) {
        create_drive_direct(lspeed*direction, wallride*direction)
        msleep(10);
    }
    lineCount++;
}
create_stop
}

void towerVISION(int tower) {    // towerVISION: moves robot over the entered number of towers, enter negative tower number to go backwards

if (currentTower < tower) {
direction=1;
} else {
direction=-1;
}

while (get_object_area(tower) < card) {
    create_drive_direct(lspeed*direction, wallride*direction);
    msleep(10);
    camera_update();
    }
    create_stop();

while ((get_object_center_x(tower,0) > rcenter)||(get_object_center_x(tower,0) < lcenter)) {

    if(get_object_center_x(tower,0) < lcenter ) {
        create_drive_direct(lspeed, wallride)
        msleep(10);
    }
    if(get_object_center_x(tower,0) > rcenter ) {
        create_drive_direct(-lspeed, -wallride)
        msleep(10);
    }
    create_stop();
}

currentTower=tower;

}


void towerALIGN(int tower) {  

if (currentTower < tower) {
direction=1;
} else {
direction=-1;
}

while (ETcount < tower) {
    create_drive_direct(lspeed*direction, wallride*direction);

    if (analog_et(ET) < towerDis) {
    ETcount++;
    msleep(10);
    }
    }
create_stop();

while (analog_et(ET) < towerDis) {
    create_drive_direct(lspeed*direction, wallride*direction);
    }

if (direction == 1) {
driveBack();
} else {
driveBack();
}
create_stop();
currentTower=tower;
}



}

}




void openRing(int ring) {    // openRing: opens to grad ring by number (smallest ring is 1)
if(ring==1) {
    set_servo_position(claw1, oR1);
}
if(ring==2) {
    set_servo_position(claw1, oR2);
}
if(ring==3) {
    set_servo_position(claw1, oR3);
}
if(ring==4) {
    set_servo_position(claw1, oR4);
}
if(ring==5) {
    set_servo_position(claw1, oR5);
}
enable_servo(claw1);
}

void closeRing(int ring) {    // closeRing: closes to grad ring by number (smallest ring is 1)
if(ring==1) {
    set_servo_position(claw1, cR1);
}
if(ring==2) {
    set_servo_position(claw1, cR2);
}
if(ring==3) {
    set_servo_position(claw1, cR3);
}
if(ring==4) {
    set_servo_position(claw1, cR4);
}
if(ring==5) {
    set_servo_position(claw1, cR5);
}
enable_servo(claw1);
}


void armUP() {    // posistions arm to grab from tower 
while(uptouch==0) {
    mav(arm, armspeed);
}
off(arm);
}



void armDOWN() {    // posistions arm to grab from patch holder
while(downtouch==0) {
    mav(arm, -armspeed);
}
off(arm);
}

void armMID() {    // posistions arm to grab from patch holder
while(midtouch==0) {
    mav(arm, -armspeed);
}
off(arm);
}

void score(int Ring) {    // grabs and stores cube, then grabs ring and scores it
set_servo_position(claw2, cubeOpen);
enable_servo(claw2);
armUP();
set_servo_position(claw2, cubeClose);
msleep(150);
armMID();
set_servo_position(claw2, cubeOpen);
msleep(150);
disable_servo(claw2);

openRing(Ring);
enable_servo(claw1);
armDOWN();
closeRing(Ring);
msleep(150);
armUP();
set_servo_position(claw1, fullopen);
msleep(150);
armMID();
}


// MIAN PROGRAMS

int main() {    // DO NOT WRITE MAIN CODE IN HERE (FOR TESTING ONLY RIGHT NOW) draft main code in seperate function
mainDRAFT();
return(0);
}


void mainDRAFT() {    // drafting space for main program

create_connect();

// Wall riding and scoring
towerPOSITION(1);
msleep(250);
towerPOSITION(4);
msleep(250);
towerPOSITION(-2);
msleep(250);
towerPOSITION(1);
msleep(250);
towerPOSITION(-2);
msleep(250);

create_disconnect();


}