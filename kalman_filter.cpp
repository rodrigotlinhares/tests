#include "kalman_filter.h"

KalmanFilter::KalmanFilter() {
  filter = cv::KalmanFilter(4, 2, 0);
  state = cv::Mat_<float>(4, 1);
  processNoise = cv::Mat(4, 1, CV_32F);

  filter.statePre.at<float>(0) = -1;
  filter.statePre.at<float>(1) = -1;
  filter.statePre.at<float>(2) = 0;
  filter.statePre.at<float>(3) = 0;
  filter.transitionMatrix = *(cv::Mat_<float>(4, 4) << 1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1);
  
  setIdentity(filter.measurementMatrix);
  setIdentity(filter.processNoiseCov, cv::Scalar::all(1e-3));
  setIdentity(filter.measurementNoiseCov, cv::Scalar::all(1e-2));
  setIdentity(filter.errorCovPost, cv::Scalar::all(.1));
}

void KalmanFilter::estimate(int measured_x, int measured_y, cv::Mat image) {
  cv::Mat_<float> measurement(2,1);
  measurement(0) = measured_x;
  measurement(1) = measured_y;
  
  cv::Mat prediction = filter.predict();
  cv::Point predictPt(prediction.at<float>(0), prediction.at<float>(1));
      
  cv::Point measPt(measurement(0), measurement(1));
  cv::Mat estimated = filter.correct(measurement);
  cv::Point statePt(estimated.at<float>(0), estimated.at<float>(1));
  estimatedPoints.push_back(statePt);
}
