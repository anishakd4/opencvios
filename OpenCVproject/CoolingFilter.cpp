//
//  CoolingFilter.cpp
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

class CoolingFilter {
    std::string greeting;
public:
    CoolingFilter(){
        
    };
    
    void interpolation(uchar* lut, float* fullRange, float* Curve, float* originalValue){
        for(int i=0 ;i <256; i++){
            int j=0;
            float a = fullRange[i];
            while(a>originalValue[j]){
                j++;
            }
            if(a==originalValue[j]){
                lut[i] = Curve[j];
                continue;
            }
            float slope = ((float)(Curve[j] - Curve[j-1]))/(originalValue[j] - originalValue[j-1]);
            float constant = Curve[j] - slope*originalValue[j];
            lut[i] = slope * fullRange[i] + constant;
        }
    };
    
    Mat cool (Mat image){
        
        //Pivot points for X-coordinates
        float originalValue[] = {0, 50, 100, 150, 200, 255};
        //Changed points on Y-axis for each channel
        float bCurve[] = {0, 80, 150, 190, 220, 255};
        float rCurve[] = {0, 20, 40, 75, 150, 255};
        
        //Spliting the channels
        vector<Mat> channels(3);
        split(image, channels);
        
        //Create a lookup table
        float fullRange[256];
        for(int i=0; i<256; i++){
            fullRange[i] = (float)i;
        }
        Mat lookupTable(1, 256, CV_8U);
        uchar* lut = lookupTable.ptr();
        
        //Apply interpolation and create lookup table
        interpolation(lut, fullRange, rCurve, originalValue);
        //Apply mapping and check for underflow/overflow in red channel
        LUT(channels[2], lookupTable, channels[2]);
        min(channels[2], 255, channels[2]);
        max(channels[2], 0, channels[2]);
        
        //Apply interpolation and create lookup table
        interpolation(lut, fullRange, bCurve, originalValue);
        //Apply mapping and check for underflow/overflow in blue channel
        LUT(channels[0], lookupTable, channels[0]);
        min(channels[0], 255, channels[0]);
        max(channels[0], 0, channels[0]);
        
        Mat output;
        merge(channels, output);
        
        return output;
    };
    
};
