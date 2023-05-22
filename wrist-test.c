int arm1 = 0;
int arm2 = 1;
int claw = 0;
int wrist = 1;

int arm_up;
int arm_down;
int wrist_up;
int wrist_down;

int armspeed = 400;

void highGrab(){
  set_servo_position(claw, open);
  msleep(100);
  int speed = 5;
  int arm_position = gmpc(arm1);
  int servo_position = get_servo_position(wrist);
  while(motor_positon != arm_up || servo_positon != wrist_up){
    if(arm_position < arm_up-10){
      arm_positon += 5;
      mtp(arm1, armspeed, arm_position);
      mtp(arm2, armspeed, arm_position);
      msleep(speed);
    }else if(arm_position > arm_up+10){
      arm_positon -= 5;
      mtp(arm1, armspeed, arm_position);
      mtp(arm2, armspeed, arm_position);
      msleep(speed);
    }else {
      freeze(arm1);
      freeze(arm2);
    }if(servo_position < wrist_up-5){
      servo_positon += 2;
      set_servo_position(wrist, servo_position);
      msleep(speed);
    }else if(servo_position > wrist_up+5){
      arm_positon -= 2;
      set_servo_position(wrist, servo_position);
      msleep(speed);
    }
  }
  set_servo_position(claw, close);
  msleep(100);
}

int main(){
  cmpc(arm1);
  highGrab();
  
}
