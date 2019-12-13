//
//  ClarendonFilter.cpp
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

class ClarendonFilter {
    std::string greeting;
public:
    ClarendonFilter(){
        
    };
    
    void interpolation(uchar* lut, float* fullRange, float* Curve, float* originalValue){
        for(int i=0; i<256; i++){
            int j=0;
            float a = fullRange[i];
            while(a > originalValue[j]){
                j++;
            }
            if(a == originalValue[j]){
                lut[i] = Curve[j];
                continue;
            }
            float slope = ((float)(Curve[j] - Curve[j-1]))/(originalValue[j] - originalValue[j-1]);
            int constant = Curve[j] - slope * originalValue[j];
            lut[i] = slope*fullRange[i] + constant;
        }
    };
    
    Mat clarendon(Mat original){
        //Enhance the channel for any image bgr or HSV image
        Mat img = original.clone();
        float origin[] = {0, 28, 56, 85, 113, 141, 170, 198, 227, 255};
        float rCurve[] = {0, 16, 35, 64, 117, 163, 200, 222, 237, 249};
        float gCurve[] = {0, 24, 49, 98, 141, 174, 201, 223, 239, 255};
        float bCurve[] = {0, 38, 66, 104, 139, 175, 206, 226, 245, 255};
        
        //Spliting the channels
        vector<Mat> channels;
        split(img, channels);
        
        //Create a lookup table
        float fullRange[256];
        
        for(int i=0; i< 256; i++){
            fullRange[i] = (float)i;
        }
        
        Mat lookupTable(1, 256, CV_8U);
        uchar* lut = lookupTable.ptr();
        
        //Apply interpolation and create a lookup table
        interpolation(lut, fullRange, bCurve, origin);
        LUT(channels[0], lookupTable, channels[0]);
        
        interpolation(lut, fullRange, gCurve, origin);
        LUT(channels[1], lookupTable, channels[1]);
        
        interpolation(lut, fullRange, rCurve, origin);
        LUT(channels[2], lookupTable, channels[2]);
        
        Mat output;
        merge(channels, output);
        return output;
    };
    
};
