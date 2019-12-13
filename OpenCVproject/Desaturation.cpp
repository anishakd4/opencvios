//
//  Desaturation.cpp
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

class Desaturation {
    std::string greeting;
public:
    Desaturation(){
        
    };
    
    Mat desaturation(Mat image){
        
        //Specifying saturation scale factor
        float saturationScale = 0.01;
        
        Mat hsvImage;
        cvtColor(image, hsvImage, COLOR_BGR2HSV);
        
        //Convert to float32
        hsvImage.convertTo(hsvImage, CV_32F);
        
        vector<Mat> channels(3);
        //Split the channels
        split(hsvImage, channels);
        
        //Multiply S channel by scaling factor
        channels[1] = channels[1] * saturationScale;
        
        //Clipping operation performed to limit pixel values between 0 and 255
        min(channels[1], 255, channels[1]);
        max(channels[1], 0, channels[1]);
        
        //Merge the channels
        merge(channels, hsvImage);
        
        //Convert back to 8uc3
        hsvImage.convertTo(hsvImage, CV_8UC3);
        
        Mat imSat;
        cvtColor(hsvImage, imSat, COLOR_HSV2BGR);
        
        return imSat;
    };
    
};
