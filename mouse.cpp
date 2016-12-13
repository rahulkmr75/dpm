#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>
void callBackFunc(int event,int x,int y,int* rect){
    if(event==EVENT_LBUTTONDOWN){
	if(rect[4]==-1){
	    rect[0]=rect[2]=x;rect[1]=rect[3]=y;rect[4]=0;
	}
	if(rect[4]==0){
	    rect[2]=x;rect[3]=y;rect[4]=-1;
	}
    }
    else if(event==EVENT_MOUSEMOVE){
	if(rect[4]==0){
	    rect[2]=x;rect[3]=y;
	}
    }
    else if (event==EVENT_LBUTTONDBLCLK && rect[4]== && rect[0]!=-1)rect[4]=2;
}
void main(){
    using namespace cv;
    Mat img=imread("kate.jpg");
    namedWindow("image",1);
    int *rect=new int[5];
    rect[0]=rect[1]=rect[2]=rect[3]=rect[4]=-1; 
    setMouseCallback("image",callBackFunc,rect);
    while(rect[4]!=2){
	imshow("image",img);
	circle(img,img,Point
	waitKey(0);
    }
    
