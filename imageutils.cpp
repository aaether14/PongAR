#include "imageutils.h"

cv::Mat QImageToMat(const QImage& sourceImage)
{
     cv::Mat temporary(sourceImage.height(), 
        sourceImage.width(),
        CV_8UC3,
        (uchar*)sourceImage.bits(),
        sourceImage.bytesPerLine());
     cv::Mat result;
     cv::cvtColor(temporary, result, CV_BGR2RGB);
     return result;
}

QRect cvRectToQRect(const cv::Rect& rect)
{
   return QRect(rect.x, rect.y, rect.width, rect.height);
}

std::vector<cv::Rect> detectHand(const cv::Mat& image, cv::CascadeClassifier& classifier)
{
   cv::Mat greyedImage;
   std::vector<cv::Rect> result;
   cv::cvtColor(image, greyedImage, CV_BGR2GRAY);
   classifier.detectMultiScale(greyedImage, result, 1.3, 5, cv::CASCADE_SCALE_IMAGE, cv::Size(1, 1));
   return result;
}