//
// Created by lightol on 2020/3/13.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>

// 测试std::round()与cvRound()函数的精度差别，这个在ORB_SLAM里面有直接体现

using std::cout;
using std::endl;

int main() {
    float a = 3.34;
    int b1 = std::round(a);
    int b2 = cvRound(a);
    float c = 3.53;
    int d1 = std::round(c);
    int d2 = cvRound(c);

    cout << "b1 = " << b1 << endl;
    cout << "b2 = " << b2 << endl;
    cout << "d1 = " << d1 << endl;
    cout << "d2 = " << d2 << endl;
}

