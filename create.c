#include <kipr/wombat.h>
int arm1 = 0;
int arm2 = 2;
int claw = 3;
int close = 100;
int open = 1024;
int armspeed = 1000;
int downspeed = 200;
int high = 1;
int low = 0;
int lspeed = 700;
int rspeed = 700;
int line = 1500;

void forward(int distance) {
    set_create_distance(0);
    while (get_create_distance() < distance*10) {
        mav(rspeed, lspeed);
        msleep(10);
    }
    create_drive_direct(0,0);
    msleep(10);
}
    
void backward(int distance) {
    set_create_distance(0);
    while (abs(get_create_distance()) < distance*10) {
        mav(-rspeed, -lspeed);
        msleep(10);
    }
    create_drive_direct(0,0);
    msleep(10);
}

void wallride(int distance) {
    set_create_distance(0);
    while(get_create_distance() < distance*10) {
        if((get_create_rbump()==0) && (get_create_lbump()==0)) {
            create_drive_direct(rspeed, lspeed);
            msleep(10);
        }
        if((get_create_rbump()==1) && (get_create_lbump()==0)) {
            create_drive_direct(rspeed, lspeed-100);
            msleep(10);
        }
        if((get_create_rbump()==0) && (get_create_lbump()==1)) {
            create_drive_direct(rspeed-100, lspeed);
            msleep(10);
        }
        
    }
    create_drive_direct(0,0);
    msleep(10);
}
    
void rturn(int angle) {
    while (get_create_total_angle() < angle) {
        mav(-rspeed, lspeed);
        msleep(10);
    }
    create_drive_direct(0,0);
    msleep(10);
}
void lturn(int angle) {
    while (get_create_total_angle() < angle) {
        mav(rspeed, -lspeed);
        msleep(10);
    }
    create_drive_direct(0,0);
    msleep(10);
}

void high_grab() {
    enable_servo(claw);
    set_servo_position(claw, open);
    msleep(150);
    while(digital(high) == 0) {
        mav(arm1, -armspeed);
        mav(arm2, -armspeed);
        msleep(10);
    }
    freeze(arm1);
    freeze(arm2);
    forward(5);
    set_servo_position(claw, close);
    msleep(150);
    backward(10);
    lturn(90);
    while(digital(low) == 0) {
        mav(arm1, downspeed);
        mav(arm2, downspeed);
        msleep(10);
    }
    set_servo_position(claw, open);
    msleep(100);   
}

void low_grab() {
    enable_servo(claw);
    set_servo_position(claw, open);
    msleep(150);
    while(digital(low) == 0) {
        mav(arm1, downspeed);
        mav(arm2, downspeed);
        msleep(10);
    }
    freeze(arm1);
    freeze(arm2);
    forward(50);
    set_servo_position(claw, close);
    msleep(150);
}

void align() {
    while(get_create_rfcliff_amt() > line) {
        mav(rspeed, lspeed);
        msleep(10);
    }
    create_drive_direct(0, 0);
    msleep(10);
    while(get_create_rfcliff_amt() <= line) {
      mav(0, -lspeed);
      msleep(10);
    }
}
    
int main() {
    create_connect();
    //drive over to towers
    align();
    while(get_create_lbump() == 0) {
        forward(1);
        msleep(10);
    }
    msleep(500);
    backward(5);
    rturn(90);
    wallride(70);
    
    //grab botgal
    lturn(90);
    backward(5);
    rturn(25);
    align();
    backward(5);
    high_grab();
    
    //grab cubes
    
    
    
    create_disconnect();
    return 0;
}
