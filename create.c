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
    while (get_create_distance() < distance) {
        mav(rspeed, lspeed);
        msleep(10);
    }
}
    
void backward(int distance) {
    set_create_distance(0);
    while (abs(get_create_distance()) < distance) {
        mav(-rspeed, -lspeed);
        msleep(10);
    }
}
    
void rturn(int angle) {
    while (get_create_total_angle() < angle) {
        mav(-rspeed, lspeed);
        msleep(10);
    }
}
void lturn(int angle) {
    while (get_create_total_angle() < angle) {
        mav(rspeed, -lspeed);
        msleep(10);
    }
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
    forward(50);
    set_servo_position(claw, close);
    msleep(150);
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
    
    while(get_create_rfcliff_amt() <= line) {
      mav(0, lspeed);
      msleep(10);
    }
}
    
int main() {
    create_connect();
    align();
    forward(300);
    msleep(500);
    backward(300);
    high_grab();
    msleep(500);
    low_grab();
    create_disconnect();
    return 0;
}
