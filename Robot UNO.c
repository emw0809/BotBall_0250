
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

cmpc(ldrive);
while(gmpc(ldrive) < (angle*degrees)) {
    mav(rdrive, -Trspeed);
    mav(ldrive, Tlspeed);
}
freeze(rdrive);
freeze(ldrive);
}

void lturn(int angle) {    // lturn: turns left in degrees

cmpc(rdrive);
while(gmpc(rdrive) < (angle*degrees)) {
    mav(rdrive, Trspeed);
    mav(ldrive, -Tlspeed);
}
freeze(rdrive);
freeze(ldrive);
}

void driveForward(int distance) {    // driveForward: drives forward in cm

cmpc(rdrive);
while(gmpc(rdrive) < (distance*CM)) {
    mav(rdrive, rspeed);
    mav(ldrive, lspeed);
}
freeze(rdrive);
freeze(ldrive);
}

void driveBack(int distance) {    // driveBack: drives backward in cm

cmpc(rdrive);
while(gmpc(rdrive) < (distance*CM)) {
    mav(rdrive, -rspeed);
    mav(ldrive, -lspeed);
}
freeze(rdrive);
freeze(ldrive);
}

void driveAsist(int distance) {    // driveAsist: drives forward in cm an balances encoders

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

void rturnAsist(int angle) {    // rturnAsist: turns right in degrees and balances encoders

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


void squareFRONT() {    // squareFRONT: squares up on front with touch sensors

while((digital(FRtouch)=0) || (digital(FLtouch)=0)) {
    mav(rdrive, rspeed);
    mav(ldrive, lspeed);
}
freeze(rdrive);
freeze(ldrive);
}

void squareBACK() {    // squareBACK: squares up on back with touch sensors

while((digital(BRtouch)=0) || (digital(BLtouch)=0)) {
    mav(rdrive, -rspeed);
    mav(ldrive, -lspeed);
}
freeze(rdrive);
freeze(ldrive);
}



void towerALIGN(int line, int direction) {    // towerALIGN: directs robot to base tape infornt of towers

while (lineCount<line) {

    while(analog(irA)<irGrey) {
        mav(rdrive, wallride*direction);
        mav(ldrive, lspeed*direction);
        msleep(10);
    }
    while(analog(irA)>irGrey) {
        mav(rdrive, wallride*direction);
        mav(ldrive, lspeed*direction);
        msleep(10);
    }
    lineCount++;
}
mav(rdrive, wallride*direction);
mav(ldrive, lspeed*direction);
msleep(250);
freeze(rdrive);
freeze(ldrive);
while((analog(irA)<irGrey) || (analog(irB)<irGrey)) {
    mav(rdrive, 500*(-direction));
    mav(ldrive, 500*(-direction));
    msleep(10);
}
freeze(rdrive);
freeze(ldrive);
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


// MAIN PROGRAM

int main() {

// Getting to server room and square up
squareFRONT();   
driveBack(5);
rturn(90);
squareBACK();

// Positioning for wall ride
mav(rdrive, wallride);   
mav(ldrive, lspeed);
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
ao();
disable_servos();

}