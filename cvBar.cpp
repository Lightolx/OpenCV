#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>

// 使用cv::createTrackbar()函数，通过滚动条调整图像的亮度

using std::cout;
using std::endl;

int maxIntensity = 100;

void onTrackbar_src(int pos, void *userdata)
{
    imshow("src", *(cv::Mat *)userdata * pos / double(maxIntensity));//使用userdata，先强制转换格式，然后此函数要求传入内容，所以还要取内容符，第三步
}
int main() {
    cv::Mat src=imread("../data/fish.jpg",cv::IMREAD_UNCHANGED);
    if(!src.data) {
        cout << "no image found" << endl;
        return -1;
    }

    int intensity = 50;

    cv::namedWindow("src");
    cv::imshow("src", src);  // 去掉这一行的话，刚开始没有启动回调函数之前Window里面是空的，不信可以去了试试
    cv::createTrackbar("intensity","src", &intensity, maxIntensity, onTrackbar_src, &src);//将图片指针传入userdata

    cv::waitKey(0);

    return 0;
}