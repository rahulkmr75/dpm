#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "matrix.h"
#include "custommethods.cpp"

using namespace cv;
using namespace std;
int main(){
    //various vector to store the file names of the dataset.
    vector<string>index_persondata;
    vector<string>index_negdata;
    vector<string>index_headdata;

    //loading the file names
    loadDataNames(index_persondata,PERSON);
    loadDataNames(index_negdata,NEG);
    loadDataNames(index_headdata,HEAD);
 
    return 0;
}
