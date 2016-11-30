#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>
#include "gradients.cpp"
int main(){
    using namespace cv;
    Mat bgr=imread("kate.jpg");
    Mat edge;
    gradient(bgr,edge,true);
    imshow("bgr",bgr);
    imshow("edge",edge);
    waitKey(0);
    return 0;
}
