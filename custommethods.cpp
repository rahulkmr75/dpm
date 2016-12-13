#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "matrix.h"

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

#ifndef CUSTOM_FILE_NAMES_
#define CUSTOM_FILE_NAMES_
#define pathpersons "../dpm_database/persons/"
#define pathneg "../dpm_database/neg/"
#define pathfoot "../dpm_databases/foot/"
#define pathhead "../dpm_database/head/"
#define pathhand "../dpm_database/hand/"
#endif

#ifndef NET_CONSTANTS_
#define NET_CONSTANTS_
//defining the batch size and the 
//quantity of postive data in it
#define BATCH_SIZE 60
#define POS_BATCH_SIZE 20
#endif

using namespace std;
using namespace cv;
using namespace OpenNN;

enum DSET{PERSON,FOOT,HEAD,HAND,NEG};

void to_char_star(char *dst,string src){
    size_t i;
    for (i=0;i<src.size();i++)dst[i]=src[i];
    dst[i]='\0';
}
//loads the file names 
void loadDataNames(vector<string> &name,const DSET dset){
    string dir;
    if(dset==PERSON) dir=pathpersons;
    else if(dset==FOOT) dir=pathfoot;
    else if(dset==HEAD) dir= pathhead;
    else if(dset==HAND) dir= pathhand;
    else  dir=pathneg;

    string dircopy=dir;
    
    dircopy.append("index.txt");
    ifstream infile;
    cout<<dircopy<<endl;
    char filename[50];
    to_char_star(filename,dircopy);
    
    infile.open(filename);
   
    string temp; 
    while(infile>>temp){
	dircopy=dir;
	dircopy.append(temp);
	name.push_back(dircopy);
    }
    infile.close();
}
void getHOGFeature(Mat gray,vector<float> &descval,vector<Point> &locations){
    HOGDescriptor d(Size(32,16), Size(16,16),Size(4,4),Size(4,4),9
		    //winsize (32,16)
		    //blocksize (16,16)
		    //blockstride (4,4)
		    //cellsize (4,4)
		    //bins 9
		    );
    d.compute(gray,descval,Size(8,8),Size(0,0),locations
	//vector<float>& descval    
	//Size winstride=Size()
	//Size padding=Size()
	);
}
void make_io_vector(Matrix<float> &input,vector<string> &input_file_pos,vector<string> &input_file_neg,vector<int> &output,const int batch_num){
    int num_input=input.size(),num_output=output.size();
    for(size_t i=0;i<BATCH_SIZE;i++){
	Mat img;

	if(output.size()!=60)output.resize(60);
	

	if(i%3==0){
	    img=imread(input_file_pos[((i/3)+batch_num*20)%input_file_pos.size()],CV_LOAD_IMAGE_GRAYSCALE );
	   output[i]=1;
	} 
	else {
	    img=imread(input_file_neg[(i+batch_num*60)%input_file_neg.size()],CV_LOAD_IMAGE_GRAYSCALE);
	    output[i]=-1;   
	}
	resize(img,img,Size(32,32));
	
	vector<float> desc_val;
	vector<Point> point_val;
	getHOGFeature(img,desc_val,point_val);

	if(input.get_rows_number()!=BATCH_SIZE || input.get_columns_number()!=desc_val.size())input.set(BATCH_SIZE,desc_val.size());

	input.set_row(i,desc_val);
    }
}	
