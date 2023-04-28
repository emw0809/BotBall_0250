int lspeed = 700;
int rspeed = 700;

void forward(int distance) {
    set_create_distance(0);
    while (get_create_distance() < distance*10) {
        mav(rspeed, lspeed);
        msleep(10);
    }
    create_drive_direct(0,0);
    msleep(10);
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
  while(get_create_lbump() == 0){
    forward(1);
    msleep(10);
  }
  create_drive_direct(0,0);
  create_disconnect();
  return 0;
}
