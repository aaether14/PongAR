#include "imageutils.h"

cv::Mat QImage2Mat(const QImage& sourceImage)
{
     cv::Mat temporary(sourceImage.height(), 
        sourceImage.width(),
        CV_8UC3,
        (uchar*)sourceImage.bits(),
        sourceImage.bytesPerLine());
     cv::Mat result;
     cvtColor(temporary, result,CV_BGR2RGB);
     return result;
}