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

//sample frames should be in hsv
cv::Mat computeHandHistogram(std::vector<cv::Mat> sampleFrames)
{
    cv::Mat handHist, result;
    cv::calcHist(sampleFrames, {0, 1}, cv::noArray(), handHist, {180, 256}, {0, 180, 0, 256});
    cv::normalize(handHist, result, 0, 255, cv::NORM_MINMAX);
    return result;
}

//image should be in hsv
cv::Mat histogramMasking(cv::Mat image, cv::Mat histogram)
{
    cv::Mat result, backProjection, filteredProjection, threshold;
    std::vector<cv::Mat> images = {image};
    cv::calcBackProject(images, {0, 1}, histogram, backProjection, {0, 180, 0, 256}, 1.0);
    cv::Mat disc = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(21, 21));
    cv::filter2D(backProjection, filteredProjection, -1, disc);
    cv::threshold(filteredProjection, threshold, 150, 255, cv::THRESH_BINARY);
    cv::Mat rect = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(threshold, result, cv::MORPH_CLOSE, rect, cv::Point(-1, -1), 7);
    return result;
}

cv::Mat backgroundSubstraction(cv::Mat image)
{

}