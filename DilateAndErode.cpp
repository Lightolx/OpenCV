//
// Created by lightol on 2020/3/13.
//

// 针对于图像的膨胀与腐蚀操作

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>

int main(int argc, char *argv[]) {
    cv::Mat image = cv::imread("../data/hough.jpg", cv::IMREAD_UNCHANGED);
    cv::imshow("im_pro", image);

    cv::Mat image_dilate;
    // 膨胀核为9*9的矩形
    cv::dilate(image, image_dilate, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9)));
    cv::imshow("im_dilate", image_dilate);

    cv::Mat image_erode;
    cv::erode(image, image_erode, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9)));
    cv::imshow("im_erode", image_erode);

    cv::waitKey();
}