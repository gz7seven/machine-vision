// ������Դ�ڣ�http://www.cnblogs.com/tornadomeet/archive/2012/06/06/2538695.html
// ���ڳ����޸��˳���

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

    ////����meanshiftͼ����������зָ�

    pyrMeanShiftFiltering(src,dst,spatialRad,colorRad,maxPryLevel);

    RNG rng=theRNG();

    Mat mask(dst.rows+2,dst.cols+2,CV_8UC1,Scalar::all(0));

    for(int i=0;i<dst.rows;i++)    //opencvͼ��Ⱦ���Ҳ�ǻ���0����

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

 

    //��ȻcreateTrackbar�����Ĳ���onChange����Ҫ����2��������ʽΪonChange(int,void*)

    //����������ϵͳ��Ӧ��������ʹ��createTrackbar����ʱ������õĺ������Բ���д����������

    //���Ŷ�����д����������ú�����ʵ�ֹ����л�����Ҫ����(int,void*)2����������

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

    waitKey();//���޵ȴ��û�������Ӧ

//    while(1);//���ﲻ����while(1)��ԭ������Ҫ�ȴ��û��Ľ�������while(1)û�иù��ܡ���Ȼ2�߶������޵ȴ������á�

    return 0;

}