//
//  KelvinFilter.cpp
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

class KelvinFilter {
    std::string greeting;
public:
    KelvinFilter(){
        
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
    
    Mat kelvin(Mat original){
        Mat img = original.clone();
        
        // Specifying the x-axis for mapping
        float originalR[] = {0, 60, 110, 150, 235, 255};
        float originalG[] = {0, 68, 105, 190, 255};
        float originalB[] = {0, 88, 145, 185, 255};
        
        // Specifying the y-axis for mapping
        float rCurve[] = {0, 102, 185, 220, 245, 245};
        float gCurve[] = {0, 68, 120, 220, 255};
        float bCurve[] = {0, 12, 140, 212, 255};
        
        vector<Mat> channels;
        split(img, channels);
        
        Mat lookupTable(1, 256, CV_8U);
        uchar* lut = lookupTable.ptr();
        
        //Create a lookup table
        float fullRange[256];
        
        for(int i=0; i< 256; i++){
            fullRange[i] = (float)i;
        }
        
        //Apply interpolation and create a lookup table
        interpolation(lut, fullRange, bCurve, originalB);
        LUT(channels[0], lookupTable, channels[0]);
        
        interpolation(lut, fullRange, gCurve, originalG);
        LUT(channels[1], lookupTable, channels[1]);
        
        interpolation(lut, fullRange, rCurve, originalR);
        LUT(channels[2], lookupTable, channels[2]);
        
        Mat output;
        merge(channels, output);
        
        return output;
    };
    
};
