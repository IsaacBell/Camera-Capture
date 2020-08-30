// I had to install OpenCV4, which contains references to OpenCV2
// in its includes folder. Then I linked the OpenCV2 packages,
// which need to be imported in very specific order

// I don't know how to switch from Black & White to Color in C++
// But so far this is promising

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

int main()
{
    cv::namedWindow("raw", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("gray", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("canny", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture cap;
    cap.open(0);

    if (!cap.isOpened())
    {
        std::cerr << "Couldn't open capture." << std::endl;
        return -1;
    }

    cv::UMat bgr_frame, gray, canny;

    for (;;)
    {
        cap >> bgr_frame;
        if (bgr_frame.empty()) break;

        cv::imshow("raw", bgr_frame);

        cv::cvtColor(bgr_frame, gray, cv::COLOR_BGR2RGB);
        cv::imshow("gray", gray);

        cv::Canny(gray, canny, 10, 100, 3, true);
        cv::imshow("canny", canny);

        char c = cv::waitKey(10);
        if (c == 27) break;
    }

    cap.release();
    return 0;
}
