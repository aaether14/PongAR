#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <QImage>

cv::Mat QImageToMat(const QImage& sourceImage);
QImage cvMatToQImage(const cv::Mat& cvImage);
QRect cvRectToQRect(const cv::Rect& rect);

std::vector<cv::Rect> detectHand(const cv::Mat& image, cv::CascadeClassifier& classifier);