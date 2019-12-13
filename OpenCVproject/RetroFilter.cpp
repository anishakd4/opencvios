//
//  RetroFilter.cpp
//  OpenCVproject
//
//  Created by Anish Kumar Dubey on 06/08/19.
//  Copyright © 2019 Anish Kumar Dubey. All rights reserved.
//

#include <stdio.h>
#include<opencv2/opencv.hpp>
#include<math.h>
#include "string"

using namespace std;
using namespace cv;

class RetroFilter {
public:
    Mat image;
    Mat fuzzyBorder;
    Mat scratches;
    cv::Size frameSize;
    float multiplier_;
    cv::Mat borderColor_;
    cv::Mat scratchColor_;
    std::vector<cv::Mat> sepiaPlanes_;
    cv::Mat sepiaH_;
    cv::Mat sepiaS_;
    cv::RNG rng_;
public:
    RetroFilter(){
        
    };
    
    void alphaBlendC1(Mat src, Mat dst, Mat alpha)
    {
        for (int i = 0; i < src.rows; i++)
            for (int j = 0; j < src.cols; j++)
            {
                uchar alphaVal = alpha.at<uchar>(i, j);
                if (alphaVal != 0)
                {
                    float weight = static_cast<float>(alphaVal) / 255.0f;
                    dst.at<uchar>(i, j) = weight * src.at<uchar>(i, j) +
                    (1 - weight) * dst.at<uchar>(i, j);
                }
            }
    }
    
    void applyToPhoto(const Mat& frame, Mat& retroFrame){
        
        Mat luminance;
        cvtColor(frame, luminance, COLOR_BGR2GRAY);
        
        // Add scratches
        Scalar meanColor = mean(luminance.row(luminance.rows / 2));
        scratchColor_.setTo(meanColor * 2.0);
        int x = rng_.uniform(0, scratches.cols - luminance.cols);
        int y = rng_.uniform(0, scratches.rows - luminance.rows);
        cv::Rect roi(cv::Point(x, y), luminance.size());
        scratchColor_.copyTo(luminance, scratches(roi));
        
        // Add fuzzy border
        borderColor_.setTo(meanColor * 1.5);
        alphaBlendC1(borderColor_, luminance, fuzzyBorder);
        
        // Apply sepia-effect
        sepiaPlanes_[2] = luminance + 20;
        Mat hsvFrame;
        merge(sepiaPlanes_, hsvFrame);
        cvtColor(hsvFrame, retroFrame, COLOR_HSV2RGB);
    };
    
    Mat retro(Mat inputImage, Mat imageBorder, Mat imageScratches){
        
        image = inputImage;
        frameSize = inputImage.size();
        fuzzyBorder = imageBorder;
        scratches = imageScratches;

        multiplier_ = 1.0;

        borderColor_.create(frameSize, CV_8UC1);
        scratchColor_.create(frameSize, CV_8UC1);

        sepiaH_.create(frameSize, CV_8UC1);
        sepiaH_.setTo(Scalar(19));
        sepiaS_.create(frameSize, CV_8UC1);
        sepiaS_.setTo(Scalar(78));
        sepiaPlanes_.resize(3);
        sepiaPlanes_[0] = sepiaH_;
        sepiaPlanes_[1] = sepiaS_;

        resize(fuzzyBorder, fuzzyBorder, frameSize);

        if (scratches.rows < frameSize.height || scratches.cols < frameSize.width){
            resize(scratches, scratches, frameSize);
        }

        Mat output;
        applyToPhoto(inputImage, output);
        
        return output;
    };
    
};
