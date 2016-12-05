#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <cmath>
#include <iostream>
#define PI 3.141592653589793
#define RT18 4.242640687119285
#define sp "  "
#define nl "\n"
using namespace cv;
void gradient(Mat &src,Mat &dst){
    Mat gray;
    bool rgb=src.channels()==3; 
    int r=src.rows,c=src.cols,i,j,k;
    if(rgb)cvtColor(src,gray,CV_BGR2GRAY);
    else gray=src.clone();
    dst.create(Size(c,r),CV_8UC1);
    for(i=1;i<r-1;i++){
	for(j=1;j<c-1;j++){
	    int sumx=0,sumy=0;
		for(k=0;k<9;k++){
		    Scalar intensity=gray.at<uchar>(i+(k/3)-1,j-1+k%3);
		    sumx=sumx+intensity.val[0]*(k%3-1);
		    sumy=sumy+intensity.val[0]*(k/3-1);
		}
	    int sum=sqrt((sumx*sumx+sumy*sumy)/18);
	    //if(sum<10)sum=0;
	    dst.at<uchar>(i,j)=sum;
	}
    }
}
void gradient2(Mat &src,Mat &dst,Mat &dst2){
    Mat gray;
    bool rgb=src.channels()==3; 
    int r=src.rows,c=src.cols,i,j,k;
    if(rgb)cvtColor(src,gray,CV_BGR2GRAY);
    else gray=src.clone();
    dst.create(Size(c,r),CV_8UC1);
    dst2.create(Size(c,r),CV_8UC1);
    for(i=1;i<r-1;i++){
	for(j=1;j<c-1;j++){
	    int sumx=0,sumy=0;
		for(k=0;k<9;k++){
		    Scalar intensity=gray.at<uchar>(i+(k/3)-1,j-1+k%3);
		    sumx=sumx+intensity.val[0]*(k%3-1);
		    sumy=sumy+intensity.val[0]*(k/3-1);
		}
	    double mag=sqrt(sumx*sumx+sumy*sumy);
	    int sum=(int)(mag/RT18);
	    //if(sum<10)sum=0;

	    int theta;
	    if(mag!=0)theta=(int)((acos(sumx/mag))*180/PI);
	    else theta =0;

	    dst.at<uchar>(i,j)=sum;
	    dst2.at<uchar>(i,j)=theta;
	    std::cout<<sumx<<sp<<sumy<<sp<<theta<<nl;
	}
    }
}
void getHOGFeature(Mat &img,Point p,Size s,std::vector<double> &vec){
    /*write the code for bound checking 
	here*/
    for(int i=p.y;i<p.y+s.height;i++){
	for(int j=p.x;j<p.x+s.width;j++){
	    //computing the gradient
	    int sumx=0,sumy=0;
		for(int k=0;k<9;k++){
		    Scalar intensity=img.at<uchar>(i+(k/3)-1,j-1+k%3);
		    sumx=sumx+intensity.val[0]*(k%3-1);
		    sumy=sumy+intensity.val[0]*(k/3-1);
		}
		if(sumx==0 and sumy==0){
		}
		else{	
		    double theta , sum;
		    if(sumx==0)theta=PI/2;
		    else theta=atan(sumy/sumx);
		    sum=sqrt((sumx*sumx+sumy*sumy)/18);

		    //tan(x)=tan(PI + x)
		    if(theta<0)theta+=(PI);
		    int I=(int)(9*theta/PI);
		    double f=9*theta/PI - I; 
		    if(I==8 || I==9)vec[8]+=sum;
		    else{
			vec[I]+=(sum*(1-f));
			vec[I+1]=(sum*f);
		    }
		}
	}
    }
}
