

// touch sensors
int FRtouch=0;
int FLtouch=1;
int BRtouch=2;
int BLtouch=3;

// limit switches
int uptouch=4;
int downtouch=5;
int midtouch=6;

// motors
int arm=2;
int ldrive=0;
int rdrive=1;

// motor speeds
int armspeed;
int lspeed;
int rspeed;

int Tlspeed;
int Trspeed;

int wallride;

// analog sensors
int irA;
int irB;
int irGrey;
int irBlack;

// servos
int claw1=0;
int claw2=1;

// servo posistions
int cubeOpen;
int cubeClose;

int cR1;
int cR2;
int cR3;
int cR4;
int cR5;

int oR1;
int oR2;
int oR3;
int oR4;
int oR5;

int fullopen;


// other
int lineCount=0;
int degrees;      // ticks turn conversion
int CM;           // ticks straight cm convertion








// FUNCTIONS

void rturn(int angle) {    // rturn: turns right in degrees

set_create_total_angle(0);
while(get_create_total_angle()) < (angle*degrees)) {
    create_drive_direct(Tlspeed, -Trspeed);
}
create_stop();
}

void lturn(int angle) {    // lturn: turns left in degrees

set_create_total_angle(0);
while(get_create_total_angle() < (angle*degrees)) {
    create_drive_direct(-Tlspeed, Trspeed);
}
create_stop();
}

void driveForward(int distance) {    // driveForward: drives forward in cm

set_create_distance(0);
while(get_create_distance()) < (distance*CM)) {
    create_drive_direct(lspeed, rspeed);
}
create_stop();
}

void driveBack(int distance) {    // driveBack: drives backward in cm

set_create_distance(0);
while(get_create_distance()) < (distance*CM)) {
    create_drive_direct(-lspeed, -rspeed);
}
create_stop();
}

void driveAsist(int distance) {    // driveAsist: drives forward in cm and balances encoders

ccd(rdrive);
ccd(ldrive);
while(((gcd(rdrive)+gcd(ldrive))/2) < (distance*CM)) {
    

    if(gcd(rdrive) = gcd(ldrive)) {
        create_drive_direct(1000, 1000);
        msleep(10);
    } else if(gcd(rdrive) < gcd(ldrive)) {
        create_drive_direct(925, 1000);
        msleep(10);
    } else {
        create_drive_direct(1000, 925);
        msleep(10);
    }
    
}
create_stop();
}

void rturnAsist(int angle) {    // rturnAsist: turns right in degrees and balances encoders

ccd(rdrive);
ccd(ldrive);
while(((abs(gcd(rdrive)) + gcd(ldrive)) /2) < (angle*degrees)) {
    

    if(abs(gcd(rdrive)) = gcd(ldrive)) {
        create_drive_direct(1000, -1000);
        msleep(10);
    } else if(abs(gcd(rdrive)) < gcd(ldrive)) {
        create_drive_direct(925, -1000);
        msleep(10);
    } else {
        create_drive_direct(1000, -925);
        msleep(10);
    }
    
}
freeze(rdrive);
freeze(ldrive);
}


void squareFRONT() {    // squareFRONT: squares up on front with touch sensors

while((get_create_left_bump()==0) || (get_create_right_bump()==0)) {
    create_drive_direct(lspeed, rspeed);
}
freeze(rdrive);
freeze(ldrive);
}

void squareBACK() {    // squareBACK: squares up on back with touch sensors

while((get_create_right_bump()==0) || (get_create_left_bump()==0)) {
    create_drive_direct(-lspeed, -rspeed);
}
create_stop();
}



void towerALIGN(int line, int direction) {    // towerALIGN: directs robot to base tape infornt of towers

while (lineCount<line) {

    while(analog(irA)<irGrey) {
        create_drive_direct(lspeed*direction, wallride*direction);
        msleep(10);
    }
    while(analog(irA)>irGrey) {
        create_drive_direct(lspeed*direction, wallride*direction);
        msleep(10);
    }
    lineCount++;
}
create_drive_direct(lspeed*direction, wallride*direction);
msleep(250);
create_stop();
while((analog(irA)<irGrey) || (analog(irB)<irGrey)) {
    create_drive_direct(500*(-direction), 500*(-direction));
    msleep(10);
}
create_stop();
}




void openRing(int ring) {    // openRing: opens to grab ring by number (smallest ring is 1)
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


// MAIN PROGRAM

int main() {

// Getting to server room and square up
squareFRONT();   
driveBack(5);
rturn(90);
squareBACK();

// Positioning for wall ride
cdd(lspeed, wallride);   
msleep(1000);

// Wall riding and scoring
towerALIGN(1, 1);
score();
towerALIGN(4, 1);
score();
towerALIGN(2, -1);
score();
towerALIGN(1, 1);
score();
towerALIGN(2, -1);
score();

// FINISH Driving to analysis lab 
rturn();
driveForward(6);
squareBACK();
squareFRONT();
create_stop();
disable_servos();
create_disconnect();

}
