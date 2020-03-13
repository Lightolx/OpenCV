//
// Created by lightol on 2020/3/13.
//

// 将视频读入后存储成图像，再一帧一帧播放

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv/cv.hpp>

using std::cout;
using std::endl;
using std::cerr;

std::vector<cv::Mat> vImages;

void onTrackbar(int id, void *userdata) {
    imshow("src", vImages[id]);
}

int main(int argc, char *argv[]) {
    // 生成cv::VideoCapture对象
    int nImages;
    const std::string leftVideo("../data/cut.avi");
    cv::VideoCapture leftCap;
    if (leftVideo.substr(leftVideo.size() - 4) == ".avi") {
        leftCap.open(leftVideo);
        if (!leftCap.isOpened()) {
            cout << "open video failed." << endl;
        }

        nImages = leftCap.get(CV_CAP_PROP_FRAME_COUNT);
    }

    // 逐帧读入图像
    vImages.resize(nImages);
    for (int ni = 0; ni < nImages; ++ni) {
        // Step1: visualize them
        cv::Mat image;
        leftCap >> image;
        vImages[ni] = image;
    }

    // 通过cv_bar来实现视频滚动条
    // ffmpeg -i CAM101.avi -ss 70 -t 15 -codec copy cut.avi  裁剪视频命令,从第70s开始，往后裁剪15s
    int id = 0;
    cv::namedWindow("src", cv::WINDOW_NORMAL);
    cv::imshow("src", vImages[0]);  // 去掉这一行的话，刚开始没有启动回调函数之前Window里面是空的，不信可以去了试试
    cv::createTrackbar("intensity","src", &id, nImages-1, onTrackbar);//将图片指针传入userdata
    cv::waitKey(0);

    return 0;
}