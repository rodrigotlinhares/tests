#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include <cv.h>
#include <highgui.h>
#include <iostream>

class KalmanFilter {
public:
  KalmanFilter();
  void estimate(int measured_x, int measured_y, cv::Mat image);
  std::vector<cv::Point> estimatedPoints;

private:
  cv::KalmanFilter filter;
  cv::Mat_<float> state; // x, y, Vx, Vy
  cv::Mat processNoise;
};

#endif
