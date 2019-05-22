#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/video/background_segm.hpp>
#include <QImage>

cv::Mat QImageToMat(const QImage& sourceImage);
QImage cvMatToQImage(const cv::Mat& cvImage);
QRect cvRectToQRect(const cv::Rect& rect);

cv::Mat histogramMasking(cv::Mat image, cv::Mat histogram);
cv::Mat computeHandHistogram(std::vector<cv::Mat> sampleFrames);