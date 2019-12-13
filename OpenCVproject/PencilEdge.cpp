//
//  PencilEdge.cpp
//  OpenCVproject
//
//  Created by Anish Kumar Dubey on 05/08/19.
//  Copyright © 2019 Anish Kumar Dubey. All rights reserved.
//

#include <stdio.h>
#include<opencv2/opencv.hpp>
#include<math.h>
#include "string"

using namespace std;
using namespace cv;

class PencilEdge {
    std::string greeting;
public:
    PencilEdge(){
        
    };
    
    Mat sketchPencilUsingEdgeDetection(Mat original){
        Mat img = original.clone();
        
        //convert to gray scale
        cvtColor(img, img, COLOR_BGR2GRAY);
        
        //Apply gaussian filter to grayscale image
        GaussianBlur(img, img, cv::Size(3, 3), 0);
        
        //Detect edges in the image and threshold it
        Laplacian(img, img, CV_8U, 5);
        
        //Invert the image
        img = 255-img;
        
        //Thresholding
        threshold(img, img, 150, 255, THRESH_BINARY);
        
        //Output
        cvtColor(img, img, COLOR_GRAY2BGR);
        
        return img;
        
    };
};

