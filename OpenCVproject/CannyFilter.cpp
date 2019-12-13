//
//  CannyFilter.cpp
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

class CannyFilter {
    std::string greeting;
public:
    CannyFilter(){
        
    };
    
    Mat canny(Mat src){
        Mat edges;
        
        //variables for low and high thresholds
        int lowThreshold = 50;
        int highTHreshold = 100;
        
        //Sobel aperture sizes for canny edge detector
        int apertureSizes[] = {3,5,7};
        int apertureIndex = 0;
        
        //Gaussian blur size
        int blurAmount = 5;
        
        Mat blurredSrc;
        
        //Blur the image before edge detection
        if(blurAmount > 0){
            GaussianBlur(src, blurredSrc, cv::Size(2*blurAmount + 1, 2* blurAmount + 1), 0);
        }else{
            blurredSrc = src.clone();
        }
        
        //Canny requires aperture size to be odd
        int apertureSize = apertureSizes[apertureIndex];
        
        //Apply canny to get the edges
        Canny(blurredSrc, edges, lowThreshold, highTHreshold, apertureSize);
        
        return edges;
    }
    
};
