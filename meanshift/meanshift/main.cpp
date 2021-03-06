// 程序来源于：http://www.cnblogs.com/tornadomeet/archive/2012/06/06/2538695.html
// 由于出错，修改了程序

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#pragma comment(lib,"opencv_highgui2411d.lib")
#pragma comment(lib,"opencv_core2411d.lib")
#pragma comment(lib,"opencv_imgproc2411d.lib")

using namespace cv;
using namespace std;


Mat src,dst;

int spatialRad=10,colorRad=10,maxPryLevel=1;

//const Scalar& colorDiff=Scalar::all(1);

 

void meanshift_seg()

{

    ////调用meanshift图像金字塔进行分割

    pyrMeanShiftFiltering(src,dst,spatialRad,colorRad,maxPryLevel);

    RNG rng=theRNG();

    Mat mask(dst.rows+2,dst.cols+2,CV_8UC1,Scalar::all(0));

    for(int i=0;i<dst.rows;i++)    //opencv图像等矩阵也是基于0索引

        for(int j=0;j<dst.cols;j++)

            if(mask.at<uchar>(i+1,j+1)==0)

            {

                Scalar newcolor(rng(256),rng(256),rng(256));

                floodFill(dst,mask,Point(j,i),newcolor,0,Scalar::all(1),Scalar::all(1));

            }

    imshow("dst",dst);

}

 

void meanshift_seg_s(int i,void *)

{

    spatialRad = i;

    meanshift_seg();

}

 

void meanshift_seg_c(int i,void *)

{

    colorRad = i;

    meanshift_seg();

}

 

void meanshift_seg_m(int i,void *)

{

    maxPryLevel = i;

    meanshift_seg();

}

 

int main(int argc, uchar* argv[])

{

     

    namedWindow("src",WINDOW_AUTOSIZE);

    namedWindow("dst",WINDOW_AUTOSIZE);

 

    src=imread("E://Fig2.22(a).jpg");

    CV_Assert(!src.empty());

 

    spatialRad=10;

    colorRad=10;

    maxPryLevel=1;

 

    //虽然createTrackbar函数的参数onChange函数要求其2个参数形式为onChange(int,void*)

    //但是这里是系统响应函数，在使用createTrackbar函数时，其调用的函数可以不用写参数，甚至

    //括号都不用写，但是其调用函数的实现过程中还是需要满足(int,void*)2个参数类型

    createTrackbar("spatialRad","dst",&spatialRad,80,meanshift_seg_s);

    createTrackbar("colorRad","dst",&colorRad,60,meanshift_seg_c);

    createTrackbar("maxPryLevel","dst",&maxPryLevel,5,meanshift_seg_m);

 

//    meanshift_seg(0,0);

 

    imshow("src",src);

    /*char c=(char)waitKey();

    if(27==c)

        return 0;*/

    imshow("dst",src);

    imshow("flood",src);

    waitKey();//无限等待用户交互响应

//    while(1);//这里不能用while(1)的原因是需要等待用户的交互，而while(1)没有该功能。虽然2者都有无限等待的作用。

    return 0;

}