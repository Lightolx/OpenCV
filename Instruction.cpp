//
// Created by lightol on 2020/3/13.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>

// 对cv::Mat各个成员的详细解释

using std::cout;
using std::endl;

int main() {
    //      Step1: 初始化及赋值
    /*      step1.1: 只初始化不赋值，一般采用两种方式
     *      cv::Mat image = cv::Mat(int rows, int cols, int type);   type 指　CV_32SC4等
     *      cv::Mat image = cv::Mat(cv::Size size, int type);　　　　　cv::Size 是一个表示(rows, cols)的变量

            int rows = 3;
            int cols = 4;
            cv::Mat image = cv::Mat(3, 4, CV_32SC4);
            cv::Size size(3,4);
            cv::Mat image1(size, CV_16UC4);

     *
     *      step1.2: 初始化的同时赋值
     *      step1.2.1: 可以借助于数组
     　     uchar data[3][3];
            uchar k = 1;

            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    data[i][j] = k++;
                }
            }

            cv::Mat image = cv::Mat(3, 3, CV_32FC1, data);
            // todo:: 上面那个不会成功的，因为你数组里都是无符号整型，当然不能转化为32位浮点型，用下面的代码
        //    cv::Mat image = cv::Mat(3, 3, CV_8UC1, data);
            cout << image;

      *     step1.2.2: 初始化的时候也可以直接赋值
      　    cv::Mat image;
            image = (cv::Mat_<float>(4,4) << 1.2, 1.3, 1.5, 1.8,
                                             1.3, 2.0, 2.5, 3.2,
                                             1.5, 2.5, 3.0, 4.5,
                                             1.8, 3.2, 4.5, 5.0);
            cout << image;
    */

    //      Step2: 访问元素及修改元素的值
    /*      step1: 最基本的，按下标索引访问
     *      uchar I = image(i,j);
     *
            cv::Mat image = cv::imread("lane.png");
            uchar I = image.at<uchar>(100,100);
            cout << "I = " << I << endl;

     *      step2: 按行列的范围访问
            cv::Mat image = cv::imread("lane.png");
            cv::Mat subImage = image.rowRange(1,1).colRange(0,4);
            // todo:: 错是因为rowRange和colRange都是包左不包右的，也就是实际得到的行数是4-1, 列数是4-0
            // cv::Mat subImage = image.rowRange(1,4).colRange(0,4);
            cout << "subImage.rows = " << subImage.rows << endl;
            cout << "subImage.cols = " << subImage.cols << endl;
     *
     *
     */

    //      Step3: cv::Mat 的各个成员的解释
    /*      https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#size_t%20Mat::elemSize1()%20const
     *      step1: cv::Mat 矩阵的元素的物理意义
     *          矩阵的每个元素都代表照片上的一个像素，就像rows, cols分别表示矩阵的行列数，把它输出出来是跟照片的像素数量一模一样的
            cv::Mat image = cv::imread("city.jpg");
            cout << "rows = " << image.rows << ", cols = " << image.cols << endl;

            step2: cv::Mat矩阵的一个元素是怎么表示彩色的
            　　你肯定会疑惑彩色图像包含RGB通道，凭啥cv::Mat的一个元素就全记录下来了？这是因为cv::Mat矩阵的一个元素
            不单单是一个int型的数字啊，它是一个结构体，包含很多信息的，就像vector<Eigen::Matrix>的每个元素还能
            表示一个位姿呢，只不过cv::Mat是2维矩阵，vector是一维向量，这本质上没啥差别啊

            step3: CV_8UC3，每个数都代表啥
                    先来看看声明cv::Mat时用到的的CV_8UC3，CV_16SC4, CV_32SC4，CV_64FC3这些东西表示啥吧，以CV_8UC3为例：
                最后一位3表示通道数，不用说就是传说中的RGB三个通道（也有可能存储方式是BGR)，CV_8UC4表示多了一个alpha（透明度）通道；
                第一位8, 32等表示每个通道拥有的bit数（位数），比如8位表示一个字节，32位表示4个字节；
                第二个U,S,F等表示每个通道内的数据(RGB值）的存储类型，分别是unsigned int, int, float；

                8U, 16S, 64F的搭配是有道理的，比如8UC1用来存储灰度图，这是因为它的范围是0~255，所以只用1个通道的8个bit就足够表示了，存储类型当然也确定为unsigned int;
                8UC3可以用来存储一般的彩色图，因为RGB三个值的范围都是0~255，所以用3个通道，每个通道内用一个unsigned int就够了，你也没必要非要用16SU3，给每个通道分配16位，还用int, 完全就是浪费存储空间，况且它也不会取到负值；
                而对于一些画质比较细腻，比如把色彩范围划分为0~1023的图像，每个通道只用8个bit就不够存储了，必须至少用16UC3;
                更有甚者，非要把RGB值精确到小数点的，就是要用浮点型表示，这时候就必须要用float型了，比如32FC3;

                    所以你在预定义的类型中不会看到8FC3，因为只有8个bit，还要表示float型，你能表示几个数？你也不会看到64UC3，用64个bit去表示一个unsigned　int，最大的那个数是2^64-1，你能把颜色划分的这么细，划出这么多数？
                最基本的，一个像素包含RGB三个通道，这是在声明cv::Mat时的CV_32SC3中的最后一位定义的
     *
     */

    //      Step4: 怎么处理cv::Mat　imread()的照片
    /*
     *          关键是怎么处理矩阵的每个元素，进一步的，怎么处理每个元素的每个成员：
     *
     *      step3.1:  首先找到要处理的元素p(i,j)的位置
     *      1.　用指针的方式进行查找，首先确定起点？　          uchar* ptr = image.data;  为什么用uchar型的指针？因为我要一个字节一个字节的搜啊
     *      2.  指针指到p所在的行的行首，每一行有多少个字节？　　int step0 = image.step[0];
     *      3.  指针指到p所在的位置，每个元素有多少个字节？     int step1 = image.step[1];
     *
     *      step3.2:   找到了元素所在的位置，接下来处理元素里面的各个成员
     *      1.　有哪些成员呢?             废话，rgb三个值呗（可能还有alpha)
     *      2.　RGB三个值是怎么存储的呢?   在内存中按顺序存储啊，所以在这里想到了用指针，逐个字节地去访问它们
     *      3.　RGB每个通道占几个字节?     在上面讲了每个通道都是占用8,16,32,64个bit，除以8就得到他们占用多少个字节了
     *      4.  怎么知道有几个通道，每个通道占几个bit?         看下面两个函数：
     *                          返回通道数　　         int channel = image.channel();
     *                          一个通道占用的字节数　　int elemSize1 = image.elemSize1();
     *      5.　最小的处理单位应该是通道还是字节?      当然应该是通道，比如我要求把R值减1，用的是16UC3，16个bit占两个字节，你还能分别去处理两个字节不成？当然是把两个字节当成一个整体处理了
     *
     *      综上所述，要想对p(i,j)的3个通道进行赋值，需要
     *　     for (int k = 0; k < channels; ++k)
     *       {
     *           *(ptr + i*step0 + j*step1 + k*elemSize1) = I;
     *       }

            cv::Mat image0 = cv::imread("city.jpg");
            uchar* ptr0 = image0.data;

            int rows1 = image0.rows;
            int cols1 = image0.cols;
            cv::Mat image1(rows1, cols1, image0.type());
            uchar* ptr1 = image1.data;
            int step0 = image1.step[0];
            int step1 = image1.step[1];
            int channels = image1.channels();
            int elemSize1 = image1.elemSize1();　　//　在这里要注意，万一一个通道占了两个字节，把这两个字节当成一个处理?

            for (int i = 0; i < rows1; ++i)
            {
                for (int j = 0; j < cols1; ++j)
                {
                    for (int k = 0; k < channels; ++k)
                    {
                        *(ptr1 + i*step0 + j*step1 + k*elemSize1) = *(ptr0 + i*step0 + j*step1 + k*elemSize1);
                    }
                }
            }


            cv::imshow("image1", image1);
            cv::waitKey();
     */
}