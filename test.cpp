#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>
#include "gradients.cpp"
#include <cmath>
#include "hogVisual.cpp"
int main(){
    using namespace cv;
    Mat bgr=imread("kate.jpg");
    Mat edge,edge2; 
    gradient(bgr,edge);
    imshow("edge",edge);
    waitKey(0);
    pyrDown(bgr,bgr);
    pyrDown(bgr,bgr);
    gradient2(bgr,edge,edge2);
    Mat gray;
    cvtColor(bgr,gray,CV_BGR2GRAY);


    std::vector<int> vecx={3,3,3,1,0,-1,-3,-3,-3},
		vecy={0,-1,-3,-3,-3,-3,-3,-1,0};
    int win_size=16;
    for(int i=3;i<bgr.rows-win_size;i=i+win_size/2){
	for(int j=3;j<bgr.cols-win_size;j+=win_size/2){
	    std::vector<double> vec1(9,0.0);
	    getHOGFeature(gray,Point(j,i),Size(win_size,win_size),vec1);    
	    for(double n:vec1)std::cout<<n<<sp;
    	    //line(edge,Point(j,i),Point(j+vecx[t],i+vecy[t]),Scalar(255,0,0),1,8);
	}
    }
	    
    /*int l=16;
    Point p1(680,21);
    Point p2(l,l);
    getHOGFeature(gray,p1,Size(l,l),vec1);
    vec2.resize(9);
    for(int i=0;i<9;i++)std::cout<<vec1[i]<<"\n";
    std::cout<<nl<<nl;

    
    getHOGFeature2(edge,edge2,p1,Size(l,l),vec2);
    for(double n:vec2)std::cout<<n<<"\n";
    
    rectangle(edge,p1,p2+p1,Scalar(255,0,0),1,8);*/
    imshow("edge",edge);
    imshow("bgr",bgr);
    waitKey(0);
    return 0;
}
