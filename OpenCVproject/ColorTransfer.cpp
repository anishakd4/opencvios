//
//  ColorTransfer.cpp
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

class ColorTransfer {
    std::string greeting;
public:
    ColorTransfer(){
        
    };
    
    Mat colorTransferFilter(Mat dst, Mat src){
        
        //Create a copy of the destination image
        Mat output = dst.clone();
        
        Mat srcLab, dstLab, outputLab;
        cvtColor(src, srcLab, COLOR_BGR2Lab);
        cvtColor(dst, dstLab, COLOR_BGR2Lab);
        cvtColor(output, outputLab, COLOR_BGR2Lab);
        
        //convert to float 32
        srcLab.convertTo(srcLab, CV_32F);
        dstLab.convertTo(dstLab, CV_32F);
        outputLab.convertTo(outputLab, CV_32F);
        
        //Create matrices to store the seperated channels
        vector<Mat> srcChannels(3);
        vector<Mat> dstChannels(3);
        vector<Mat> outputChannels(3);
        
        //split the channels
        split(srcLab, srcChannels);
        split(dstLab, dstChannels);
        split(outputLab, outputChannels);
        
        float mean1, mean2, mean3, mean4, mean5, mean6;
        float std1, std2, std3, std4, std5, std6;
        Scalar meanSrc, meanDst, stdSrc, stdDst;
        
        //Finding the mean and std for for different channels for srcLab image
        meanStdDev(srcLab, meanSrc, stdSrc, Mat());
        mean1 = meanSrc[0];
        mean2 = meanSrc[1];
        mean3 = meanSrc[2];
        std1 = stdSrc[0];
        std2 = stdSrc[1];
        std3 = stdSrc[2];
        
        //Finding the mean and std for for different channels for dstLab image
        meanStdDev(dstLab, meanDst, stdDst, Mat());
        mean4 = meanDst[0];
        mean5 = meanDst[1];
        mean6 = meanDst[2];
        std4 = stdDst[0];
        std5 = stdDst[1];
        std6 = stdDst[2];
        
        //Subtract the mean of the destination image
        outputChannels[0] = dstChannels[0] - mean4;
        outputChannels[1] = dstChannels[1] - mean5;
        outputChannels[2] = dstChannels[2] - mean6;
        
        merge(outputChannels, outputLab);
        cvtColor(outputLab, output, COLOR_Lab2BGR);
        
        //scale the standard deviation of the destination image
        outputChannels[0] = outputChannels[0] * (std4/std1);
        outputChannels[1] = outputChannels[1] * (std5/std2);
        outputChannels[2] = outputChannels[2] * (std6/std3);
        
        merge(outputChannels, outputLab);
        cvtColor(outputLab, output, COLOR_Lab2BGR);
        
        //Add the mean of the source image to get the color
        outputChannels[0] = outputChannels[0] + mean1;
        outputChannels[1] = outputChannels[1] + mean2;
        outputChannels[2] = outputChannels[2] + mean3;
        
        merge(outputChannels, outputLab);
        cvtColor(outputLab, output, COLOR_Lab2BGR);
        
        //Merge the channels
        merge(outputChannels, outputLab);
        
        //convert back to to cv8uc3
        outputLab.convertTo(outputLab, CV_8UC3);
        
        //convert image back to bgr color space
        cvtColor(outputLab, output, COLOR_Lab2BGR);
        
        return output;
    };
    
};

