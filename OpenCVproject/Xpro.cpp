//
//  Xpro.cpp
//  OpenCVproject
//
//  Created by Anish Kumar Dubey on 05/08/19.
//  Copyright © 2019 Anish Kumar Dubey. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "string"

using namespace cv;
using namespace std;

class Xpro {
    std::string greeting;
public:
    Xpro(){
        
    };
    
    cv::Mat xproo(cv::Mat original, float vignetteScale){
        Mat img = original.clone();
        
        //Apply vignette with some radius
        img = applyVignette(img, vignetteScale);
        
        // Specifying the x-axis for mapping
        float originalR[] = {0, 42, 105, 148, 185, 255};
        float originalG[] = {0, 40, 85, 125, 165, 212, 255};
        float originalB[] = {0, 40, 82, 125, 170, 225, 255 };
        
        // Specifying the y-axis for mapping
        float rCurve[] = {0, 28, 100, 165, 215, 255 };
        float gCurve[] = {0, 25, 75, 135, 185, 230, 255 };
        float bCurve[] = {0, 38, 90, 125, 160, 210, 222};
        
        //Spliting the channels
        vector<Mat> channels(3);
        split(img, channels);
        
        float fullRange[256];
        for(int i=0 ;i < 256; i++){
            fullRange[i] = (float)i;
        }
        
        Mat lookupTable(1, 256, CV_8U);
        uchar* lut = lookupTable.ptr();
        
        interploation(lut, fullRange, rCurve, originalR);
        LUT(channels[2], lookupTable, channels[2]);
        interploation(lut, fullRange, gCurve, originalG);
        LUT(channels[1], lookupTable, channels[1]);
        interploation(lut, fullRange, bCurve, originalB);
        LUT(channels[0], lookupTable, channels[0]);
        
        Mat output;
        
        merge(channels, output);
        
        //Adjusting the contrast a bit
        output = adjustContrast(output, 1.2);
        
        return output;
    };
    
    cv::Mat adjustContrast(cv::Mat original, float alpha){
        Mat ycbImage;
        
        cvtColor(original, ycbImage, COLOR_BGR2YCrCb);
        
        ycbImage.convertTo(ycbImage, CV_32F);
        
        vector<Mat> channels;
        split(ycbImage, channels);
        
        //Scale the y channel
        channels[0] = channels[0] * alpha;
        
        //clipping operation performed to limit pixel values between 0 and 255
        min(channels[0], 255, channels[0]);
        max(channels[0], 0, channels[0]);
        
        //Merge the channels
        merge(channels, ycbImage);
        
        ycbImage.convertTo(ycbImage, CV_8UC3);
        
        Mat contrastImage;
        cvtColor(ycbImage, contrastImage, COLOR_YCrCb2BGR);
        
        return contrastImage;
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
    
    cv::Mat applyVignette(cv::Mat original, float vignetteScale){
        Mat img = original.clone();
        
        int rows = img.rows;
        int cols = img.cols;
        
        //Compute the kernel size from the image dimensions
        int k = std::min(rows, cols) / vignetteScale;
        
        Mat kernelX = getGaussianKernel(cols, k);
        Mat kernelY = getGaussianKernel(rows, k);
        
        Mat kernelX_Transpose;
        transpose(kernelX, kernelX_Transpose);
        Mat kernel = kernelY * kernelX_Transpose;
        
        Mat mask;
        normalize(kernel, mask, 0, 1, NORM_MINMAX);
        
        //convert to float32
        img.convertTo(img, CV_32F);
        mask.convertTo(mask, CV_32F);
        
        //SPlit the channels
        vector<Mat> channels(3);
        split(img, channels);
        
        //Apply the halo to all the channels of the image
        channels[0] = channels[0] + channels[0].mul(mask);
        channels[1] = channels[1] + channels[1].mul(mask);
        channels[2] = channels[2] + channels[2].mul(mask);
        
        //Merge the channels
        merge(channels, img);
        img = img/2;
        
        img.convertTo(img, CV_8UC3);
        
        return img;
    };
};
