#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>
#include "gradients.cpp"
#include <cmath>
int main(){
    using namespace cv;
    Mat bgr=imread("kate.jpg");
    Mat edge,edge2; 
    gradient2(bgr,edge,edge2);
    imshow("bgr",bgr);
    imshow("edge",edge);
    imshow("edge2",edge2);
    HOGDescriptor hog(Size(32,32),Size(16,16),Size(8,8),Size(8,8),9);
    std::vector<double> vec1;
    vec1.resize(9);
    Mat gray;
    cvtColor(bgr,gray,CV_BGR2GRAY);
    imshow("gray",gray);
    waitKey(0);
    getHOGFeature(gray,Point(323,10),Size(8,8),vec1);
    for(double n:vec1)std::cout<<n<<"\n";
    std::cout<<acos(0.9);
    return 0;
}
