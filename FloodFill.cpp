#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>

using std::cout;
using std::endl;

// 试验floodfill函数，2D图像上的区域生长算法

int main() {
    cv::Mat src = imread("../data/fish.jpg",cv::IMREAD_UNCHANGED);

    cv::Rect rect;  // 只是为了给floodfill函数一个默认值
    cv::floodFill(src, cv::Point(37, 175), cv::Scalar(255, 0, 0), &rect, cv::Scalar::all(20), cv::Scalar::all(20));

    cv::namedWindow("fish", cv::WINDOW_NORMAL);
    cv::imshow("fish", src);
    cv::waitKey();
}