#include <cv.h>
#include <highgui.h>

int main() {
    cv::VideoCapture capture(0);
    cv::Mat frame, sobel;
    char key = 0;
    cv::namedWindow("", CV_WINDOW_NORMAL);

    while(key != 'q') {
        capture >> frame;
        cv::Sobel(frame, sobel, CV_32F, 1, 0, 1);
        std::vector<cv::Mat> channels;
        split(sobel, channels);
        cv::imshow("0", channels[0]);
        cv::imshow("1", channels[1]);
        cv::imshow("2", channels[2]);
        key = cv::waitKey(10);
    }
}
