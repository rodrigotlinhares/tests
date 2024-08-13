#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"

int main()
{
    cv::VideoCapture capture("/home/rodrigolinhares/videos/retina/seance3/OD2m.avi");
    cv::Mat frame, frame_gray, output;
    std::vector<cv::KeyPoint> keypoints;
    cv::SurfFeatureDetector detector(100);
    std::stringstream ss;
    int counter = 0;
    char key = 0;
    while(key != 'q')
    {
        capture >> frame;
        cv::cvtColor(frame, frame_gray, CV_BGR2GRAY);

        detector.detect(frame_gray, keypoints);

        cv::drawKeypoints(frame, keypoints, output, cv::Scalar(255, 255),
                          cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        cv::imshow("", output);
        key = cv::waitKey();
        if(key == 'm')
        {
            ss << "surf_" << counter << ".png";
            cv::imwrite(ss.str(), output);
            ss.str("");
            counter++;
        }
    }
  return 0;
  } 
