#include <kipr/wombat.h>

void line_follow_left( int distance) {
  while ((gmpc(right)+gmpc(left))/2 < distance) {
    if (analog(ir) < (line+floor)/2) {
      mav(right, rspeed - 300);
      mav(left, lspeed);
    }
    if (analog(ir) > (line + floor)/2) {
      mav(right, rspeed);
      mav(left, lspeed - 300);
    }
  }
}

void line_follow_right( int distance) {
  while ((gmpc(right)+gmpc(left))/2 < distance) {
    if (analog(ir) < (line + floor)/2) {
      mav(right, rspeed);
      mav(left, lspeed - 300);
    }
    if (analog(ir) > (line+floor)/2) {
      mav(right, rspeed - 300);
      mav(left, lspeed);
    }
  }
}
