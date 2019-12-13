#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class PostcardPrinter
{
public:
    cv::Mat face;
    cv::Mat texture;
    cv::Mat text;
    cv::Rect faceRoi_;
    cv::Rect textRoi_;
    
public:
    PostcardPrinter(){
        
    };
    
    void alphaBlendC3(const Mat& src, Mat& dst, const Mat& alpha) {
        for (int i = 0; i < src.rows; i++)
            for (int j = 0; j < src.cols; j++)
            {
                uchar alpha_value = alpha.at<uchar>(i, j);
                if (alpha_value != 0)
                {
                    float weight = float(alpha_value) / 255.f;
                    dst.at<Vec3b>(i, j) = weight * src.at<Vec3b>(i, j) +
                    (1 - weight) * dst.at<Vec3b>(i, j);
                }
            }
    };
    
    void crumple(Mat& image, const Mat& texture, const Mat& mask) {
        Mat relief;
        cvtColor(texture, relief, COLOR_BGR2GRAY);
        relief = 255 - relief;
        
        Mat hsvImage;
        vector<Mat> planes;
        cvtColor(image, hsvImage, COLOR_BGR2HSV);
        
        split(hsvImage, planes);
        CV_Assert(planes.size() == 3);
        subtract(planes[2], relief, planes[2], mask);
        merge(planes, hsvImage);
        
        cvtColor(hsvImage, image, COLOR_HSV2BGR);
    };
    
    
    void printFragment(Mat& placeForFragment, Mat& fragment){
        // Get alpha channel
        vector<Mat> fragmentPlanes;
        split(fragment, fragmentPlanes);
        CV_Assert(fragmentPlanes.size() == 4);
        Mat alpha = fragmentPlanes[3];
        fragmentPlanes.pop_back();
        Mat bgrFragment;
        merge(fragmentPlanes, bgrFragment);
        
        // Add fragment with crumpling and alpha
        crumple(bgrFragment, placeForFragment, alpha);
        alphaBlendC3(bgrFragment, placeForFragment, alpha);
    };
    
    cv::Mat printPostcard(){
        Mat postcard;
        
        postcard = texture.clone();
        
        Mat placeForFace = postcard(faceRoi_);
        Mat placeForText = postcard(textRoi_);
        
        printFragment(placeForFace, face);
        printFragment(placeForText, text);
        
        return postcard;
    };
    
    cv::Mat printPostcardAnish(Mat image1, Mat image2, Mat image3){
        face = image1;
        text = image2;
        texture = image3;
        
        cvtColor(texture, texture, COLOR_RGBA2RGB);
        
        // Prepare postcard
        int unit = 320;
        cv::Size postcardSize = cv::Size(2 * unit, 3 * unit);
        int border = unit / 8;
        // Resize all input images properly
        resize(texture, texture, postcardSize);
        resize(face, face, cv::Size(postcardSize.width - 2 * border, postcardSize.width - 2 * border));
        cv::Size newTextSz;
        newTextSz.width = face.cols * 0.9;
        newTextSz.height = newTextSz.width * text.rows / text.cols;
        resize(text, text, newTextSz);
        
        // Choose places for face and text
        cv::Point shift(border, 2 * border);
        faceRoi_ = cv::Rect(shift, face.size());
        cv::Point origin(border + face.cols * 0.05, face.rows + 4.5 * border);
        textRoi_ = cv::Rect(origin, text.size());
        
        cv::Mat postcard = printPostcard();
        
        return postcard;
    };
    
};




