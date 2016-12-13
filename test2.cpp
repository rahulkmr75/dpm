#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <cmath>
#include "hogVisual.cpp"
using namespace std;
using namespace cv;
#ifdef _DEBUG
#pragma comment(lib, "opencv_core247d.lib")        
#pragma comment(lib, "opencv_imgproc247d.lib")   //MAT processing       
#pragma comment(lib, "opencv_objdetect247d.lib") //HOGDescriptor
#pragma comment(lib, "opencv_highgui247d.lib")       
#else
#pragma comment(lib, "opencv_core247.lib")       
#pragma comment(lib, "opencv_imgproc247.lib")
#pragma comment(lib, "opencv_objdetect247.lib")
#pragma comment(lib, "opencv_highgui247.lib")       
#endif

int main(){
    vector< vector <float> > v_descval;
    vector< vector<Point> > v_loc;
    Mat img, gray;
    img=imread("apple.jpeg");
    pyrDown(img,img);
    resize(img,img,Size(32,32));
    cvtColor(img,gray,CV_BGR2GRAY);
    HOGDescriptor d(Size(32,16), Size(16,16),Size(4,4),Size(4,4),9
		    //winsize (32,16)
		    //blocksize (16,16)
		    //blockstride (4,4)
		    //cellsize (4,4)
		    //bins 9
		    );
    
    vector <float> descval;
    vector<Point> locations;
    d.compute(gray,descval,Size(8,8),Size(0,0),locations
	//vector<float>& descval    
	//Size winstride=Size()
	//Size padding=Size()
	);
    //Mat visual=getHOGVisual(gray,descval,Size(32,16),Size(4,4),10,5);
    imshow("gray",gray);
    imshow("img",img);
    waitKey(0);
    int l=descval.size(),p=locations.size();
    cout<<locations.size()<<endl;
    //for(int i=0;i<l;i++)cout<<descval[i]<<endl;
    return 0;
}
