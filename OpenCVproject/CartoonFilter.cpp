//
//  CartoonFilter.cpp
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

class CartoonFilter {
    std::string greeting;
public:
    CartoonFilter(){
        
    };
    
    Mat makeCartoon(Mat original){
        Mat img = original.clone();
        
        //Convert to gray scale
        Mat imGray;
        cvtColor(img, imGray, COLOR_BGR2GRAY);
        
        //Apply gaussian filter to gray scale image
        GaussianBlur(imGray, imGray, cv::Size(3, 3), 0);
        
        //Detect edges in the image and threshold it
        Mat edges, edgeMask;
        //Parameters for laplacian filter
        int kernel_size = 5;
        int ddepth = CV_8U;
        
        Laplacian(imGray, edges, ddepth, kernel_size, 1);
        
        convertScaleAbs(edges, edges);
        
        edges = 255 - edges;
        
        threshold(edges, edgeMask, 150, 255, THRESH_BINARY);
        
        //Create a highly blurred image using edgePreservingFilter
        Mat imgBilateral;
        edgePreservingFilter(img, imgBilateral, 2, 50, 0.4);
        
        //Create a output matrix
        Mat output;
        bitwise_and(imgBilateral, imgBilateral, output, edgeMask);
        
        return output;
    };
};
