#include "imageutils.h"

cv::Mat QImageToMat(const QImage& sourceImage)
{
   return cv::Mat(sourceImage.height(), 
      sourceImage.width(),
      CV_8UC3,
      (uchar*)sourceImage.bits(),
      sourceImage.bytesPerLine()).clone();
}

QImage cvMatToQImage(const cv::Mat& cvImage)
{
   QImage::Format format;
   switch (cvImage.channels())
   {
      case 1:
         format = QImage::Format_Grayscale8;
         break;
      case 3:
         format = QImage::Format_RGB888;
         break;
      case 4: 
         format = QImage::Format_RGBA8888;
         break;
   }
   return QImage((uchar*)cvImage.data, cvImage.cols, cvImage.rows, cvImage.step, format).copy();
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
   classifier.detectMultiScale(greyedImage, result, 1.1, 5, cv::CASCADE_SCALE_IMAGE, cv::Size(1, 1));
   return result;
}