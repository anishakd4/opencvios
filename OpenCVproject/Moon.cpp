//
//  Moon.cpp
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

class Moon {
    std::string greeting;
public:
    Moon(){
        
    };
    
    Mat adjustSaturation(Mat original, float saturationScale){
        Mat hsvImage;
        
        //Convert to  hsv color space
        cvtColor(original, hsvImage, COLOR_BGR2HSV);
        
        //Convert to float32
        hsvImage.convertTo(hsvImage, CV_32F);
        
        vector<Mat> channels(3);
        split(hsvImage, channels);
        
        //Multiply S channel by scaling factor
        channels[1] = channels[1] * saturationScale;
        
        //Clipping operation performed to limit pixel values between 0 and 255
        min(channels[1], 255, channels[1]);
        max(channels[1], 0, channels[1]);
        
        //Merge the channels
        merge(channels, hsvImage);
        
        //convert back from float32
        hsvImage.convertTo(hsvImage, CV_8UC3);
        
        cvtColor(hsvImage, hsvImage, COLOR_HSV2BGR);
        
        return hsvImage;
    };
    
    void interploation(uchar* lut, float* fullRange, float* curve, float* originalValue){
        for(int i=0; i<256; i++){
            int j=0;
            int a = fullRange[i];
            while(a > originalValue[j]){
                j++;
            }
            if(a == originalValue[j]){
                lut[i] = curve[j];
                continue;
            }
            float slope = ((float)(curve[j] - curve[j-1]))/(originalValue[j] - originalValue[j-1]);
            float constant = curve[j] - slope*originalValue[j];
            lut[i] = slope*fullRange[i] + constant;
        }
    };
    
    Mat moon(Mat original){
        Mat img = original.clone();
        
        float origin[]={0, 15, 30, 50, 70, 90, 120, 160, 180, 210, 255 };
        float Curve[]={0, 0, 5, 15, 60, 110, 150, 190, 210, 230, 255 };
        
        //Create a lookup table
        float fullRange[256];
        for(int i=0; i<256; i++){
            fullRange[i] = (float)i;
        }
        
        Mat lookupTable(1, 256, CV_8U);
        uchar* lut = lookupTable.ptr();
        
        //Apply interploation and create lookup table
        interploation(lut, fullRange, Curve, origin);
        
        //Apply the mapping to the L channel of the LAB color space
        Mat labimage;
        cvtColor(img, labimage, COLOR_BGR2Lab);
        
        //Splitting the channels
        vector<Mat> channels;
        split(labimage, channels);
        
        LUT(channels[0], lookupTable, channels[0]);
        merge(channels, labimage);
        
        Mat dummy;
        cvtColor(labimage, dummy, COLOR_Lab2BGR);
        
        cvtColor(labimage, img, COLOR_Lab2BGR);
        
        Mat output = adjustSaturation(img, 0.01);
        return output;
    };
};
