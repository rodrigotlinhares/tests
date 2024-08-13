#include <cv.h>
#include <highgui.h>
#include <iostream>

// Rotate image
int main() {
  cv::VideoCapture cap(0);
  cv::Mat frame;
  cap >> frame;
  cv::Mat transform(2, 3, CV_32F);
  float theta = 3.14;
  float half_cols = frame.cols / 2;
  float half_rows = frame.rows / 2;
  cv::namedWindow("", CV_WINDOW_NORMAL);
  transform.at<float>(0, 0) = cos(theta);
  transform.at<float>(0, 1) = -sin(theta);
  transform.at<float>(0, 2) = -(cos(theta) * half_cols - sin(theta) * half_rows) + half_cols;
  transform.at<float>(1, 0) = sin(theta);
  transform.at<float>(1, 1) = cos(theta);
  transform.at<float>(1, 2) = -(sin(theta) * half_cols + cos(theta) * half_rows) + half_rows;

  char key = 'a';
  while(key != 'q') {
    cap >> frame;
    warpAffine(frame, frame, transform, frame.size());
    cv::imshow("", frame);
    key = cv::waitKey(10);
    if(key == 'w') {
      theta += 1;
      transform.at<float>(0, 0) = cos(theta);
      transform.at<float>(0, 1) = -sin(theta);
      transform.at<float>(0, 2) = -(cos(theta) * half_cols - sin(theta) * half_rows) + half_cols;
      transform.at<float>(1, 0) = sin(theta);
      transform.at<float>(1, 1) = cos(theta);
      transform.at<float>(1, 2) = -(sin(theta) * half_cols + cos(theta) * half_rows) + half_rows;
    }
  }
  return 0;
}
