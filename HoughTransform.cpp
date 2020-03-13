#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <eigen3/Eigen/Eigen>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include <fstream>

using std::cout;
using std::endl;
using std::cerr;

// 霍夫变换，检测图像上的直线元素

int main(int argc, char *argv[]) {
    cv::Mat image = cv::imread("../data/hough.jpg", cv::IMREAD_GRAYSCALE);
    cv::imshow("im_pro", image);

    // canny进行边缘检测
    cv::Mat im_edge;
    cv::Canny(image, im_edge, 155, 350);
    cv::imshow("im_edge", im_edge);

    // hough变换检测直线
    {
        // 这里解释下Hough变换的原理
        // step0: 对于2D像素平面上的任何一条直线l，都可以用(r, theta)两个参数来表达，见hough_line.jpg,
        //        这也就是说，直线l上的每个点都必须满足：
        //        x * cos(theta) + y * sin(theta) = r;
        // step1: 反过来看，对于任意一条直线m(R, Theta)，只要它穿过某个像素点(x,y),那么(R, Theta)就必须满足：
        //        x * cos(Theta) + y * sin(Theta) = R; 也就是说只需要两个点就能求解出(R, Theta).
        // step2: 那么对于im_edge上的像素点(x,y)，穿过这个pixel的可能有无数条直线，不过这些直线在(r, theta)空间中
        //      　肯定都满足：
        //        r = x * cos(theta) + y * sin(theta);
        //        如果把(theta, r)分别看做函数的自变量与因变量，而像素坐标(x,y)看做函数的参数，
        //        那么上式本质上就是一个正弦函数y*sin(theta)与余弦函数x*cos(theta)的线性叠加，在这里画出来看看
        // step3: 在(r, theta)平面上，画出穿过直线 u + v = 200 上所有像素的所有直线
        std::ofstream fout("../matlab/line.txt");
        for (int x = 25; x < 120; ++x) {
            int y = 200 - x;
            for (int i = 0; i < 360; ++i) {
                double theta = i / 360.0 * M_PI;
                double r = x * cos(theta) + y * sin(theta);
                fout << i << " " << r << endl;
            }
        }

        fout.close();  // 在matlab文件夹下plotCurve即可观察到所有的曲线都相交于一点
    }

    std::vector<cv::Vec2f> lines;
    // hough变换的本质是每个边缘上的像素点对对偶空间(r, theta)上的每一个voxel进行投票:
    //      (1, M_PI/180)是指定的voxel的size,也就是一个像素,1°;
    //      50是判定阈值，也就是对偶空间上的一个点有超过50个像素给它投票，则认为它真的表示像素平面上的一条直线,
    cv::HoughLines(im_edge, lines, 1, M_PI/180, 100);
    cout << "lines.size = " << lines.size() << ", 100的阈值过大，只检测出来了矩形的4个边" << endl;
    cv::Mat im_hough(im_edge.size(), CV_8UC1, cv::Scalar(0));
    for (const auto &line : lines) {  // r = x * cos(theta) + y * sin(theta);
        double r = line.val[0];    // r表示图像左上角到直线的距离
        double theta = line.val[1];// theta表示旋转角度(0~垂直线，π/2~水平线)
        double k1 = cos(theta);
        double k2 = sin(theta);
        if (fabs(k1 - 0) < 1e-6) {  // theta = PI/2, 说明是条水平线 r = k2 * y, 即 x = r/k2;
            for (int y = 0; y < im_edge.cols; ++y) {
                double x = r / k2;
                im_hough.at<uchar>(x, y) = 255;
            }

        } else if (k2 == 0) {  // theta = 0, 说明是条垂直线 r = k1 * x, 即 y = r / k1;
            for (int x = 0; x < im_edge.rows; ++x) {
                double y = r / k1;
                im_hough.at<uchar>(x, y) = 255;
            }
        } else {
            for (int x = 0; x < im_edge.rows; ++x) {
                double y = (r - k1 * x) / k2;
                im_hough.at<uchar>(x, y) = 255;
            }
        }
    }
    cv::imshow("im_hough_rect", im_hough);

    // 判定是否是直线的阈值需要手动调整，在这里的例子里表现为要小于五角星的每条边上的像素个数;
    cv::HoughLines(im_edge, lines, 1, M_PI/180, 60);
    cout << "lines.size = " << lines.size() << ", 60的阈值比较合适，把五角星的边基本都检测出来了" << endl;
    cv::waitKey();
}