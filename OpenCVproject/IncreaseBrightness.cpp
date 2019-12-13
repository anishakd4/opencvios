//
//  BrightnessFilter.cpp
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

class IncreaseBrightness {
    std::string greeting;
public:
    IncreaseBrightness(){
        
    };
    
    Mat increaseBrightness(Mat image){
        
        //Specify offset factor
        int beta = 100;
        
        //Convert to YCrCb color space
        Mat ycbImage;
        cvtColor(image, ycbImage, COLOR_BGR2YCrCb);
        
        //Convert to float 32
        ycbImage.convertTo(ycbImage, CV_32F);
        
        vector<Mat> channels(3);
        split(ycbImage, channels);
        
        //Add offset to y-channel
        channels[0] = channels[0] + beta;
        
        //clipping operation performed to limit pixel values between 0 and 255
        min(channels[0], 255, channels[0]);
        max(channels[0], 0, channels[0]);
        
        //Merge the channels
        merge(channels, ycbImage);
        
        //Convert back to cv_8uc3
        ycbImage.convertTo(ycbImage, CV_8UC3);
        
        //Convert back to BGR
        cvtColor(ycbImage, ycbImage, COLOR_YCrCb2BGR);
        
        return ycbImage;
    };
    
};
