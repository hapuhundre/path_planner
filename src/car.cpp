#include "car.h"
#include "consts.h"
#include <math.h>
#include <vector>

Car::Car(){
  car_lane = 1;
  car_v = 0.0;
}

void Car::update(double x, double y, double yaw, double v, double s, double d){
  // car_lane = lane;
  car_x = x;
  car_y = y;
  car_yaw = yaw;
  car_v = v;
  car_s = s;
  car_d = d;
  // 车辆周围的状态必须初始化 NOTE~
  is_right = false;
  is_left = false;
  is_ahead = false;

  //
  diff_v = 0.0;
}

Car::~Car(){
}

void Car::near_update(double d, double v_x, double v_y, double s, int prev_pts_size){
  float temp_d = d;
  int temp_lane = -1;
  if(temp_d > 0 && temp_d < 4){
      temp_lane = 0;
    } else if(temp_d > 4 && temp_d < 8){
      temp_lane = 1;
    } else if(temp_d > 8 && temp_d < 12){
      temp_lane = 2;
    }
  if(temp_lane<0){
    return ;
  }

  double t_vx = v_x;
  double t_vy = v_y;
  double t_s  = s;
  double t_speed = sqrt(t_vx*t_vx + t_vy*t_vy);
  t_s += ((double)prev_pts_size * dt * t_speed);
  if( temp_lane == car_lane){
    is_ahead |= ( t_s > car_s && t_s < (car_s+30) ); // 前
  } else if(temp_lane == car_lane + 1){
    is_right |= ( t_s > (car_s-30) && t_s < (car_s+30) ); // 前后均要考虑
  } else if(temp_lane == car_lane - 1){
    is_left |= ( t_s > (car_s-30) && t_s < (car_s+30) ); // the same as is_right
  }
}

void Car::car_behavior(){
  if(is_ahead){ // 前面有个车
    if(!is_left && car_lane > 0 ){ // 从左边超车，你得左边没车，而且不是左变现（不然开到沟里去，了解一下）
	  car_lane -= 1;
	}
	else if(!is_right && car_lane != 2){ // 右边超车还是得按照基本法来
      car_lane += 1;
	}
	else{ // 减速
	  diff_v -= ACC; 
	}
  }
  else{  // 前面没有车 尽量走lane=1
	if(car_lane != 1){
	  if( (car_lane==0 && !is_right) || (car_lane==2 && !is_left) ){
	    car_lane = 1;
	  }
	}
	if (car_v < MAX_SPPED){
	  diff_v += ACC;
	}
  }
}

void Car::change_lane(int lane){    
  car_lane = lane;
}

void Car::change_v(double ref_v){
  car_v = ref_v;
}

bool Car::car_right(){
  return is_right;
}

bool Car::car_ahead(){
  return is_ahead;
}

bool Car::car_left(){
  return is_left;
}

int Car::get_lane(){
  return car_lane;
}

double Car::get_x(){
  return car_x;
}

double Car::get_y(){
  return car_y;
}

double Car::get_v(){
  return car_v;
}

double Car::get_yaw(){
  return car_yaw;
}

double Car::get_s(){
  return car_s;
}

double Car::get_d(){
  return car_d;
}

double Car::get_diff_v(){
  return diff_v;
}