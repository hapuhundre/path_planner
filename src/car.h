#ifndef CAR_H
#define CAR_H

#include <vector>

class Car{
  public:
    
    Car();
    void update(double x, double y, double yaw, double v, double s, double d);
    ~Car();
    void near_update(double d, double v_x, double v_y, double s, int prev_pts_size);
    // void speed_update(double delta_speed);
    void change_lane(int lane);
    void change_v(double ref_v);
    void car_behavior();

    bool car_right();
    bool car_left();
    bool car_ahead();
    
    int get_lane();
    double get_x();
    double get_y();
    double get_v();
    double get_yaw();
    double get_s();
    double get_d();
    double get_diff_v();

  private:
    int car_lane;
    bool is_right = false;
    bool is_left = false;
    bool is_ahead = false;
    double car_x, car_y, car_yaw, car_v, car_s, car_d, diff_v;
};

#endif