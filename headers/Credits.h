/**
 * @file Credits.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Class with credits creation tools
 * @date 2023-10-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>

 /**
  * @brief Class with credits creation tools
  */
class Credits {
public:
    Credits();                                               ///< Create empty object (calling Credits::upload is necessary)

    ///< Upload images with credits text and layout (text : RGBA, layout : RGB)
    Credits(const std::string& fileNameText, const std::string& fileNameLayout);

    ///< Upload images with credits text and layout (text : RGBA, layout : RGB)
    void upload(const std::string& fileNameText, const std::string& fileNameLayout);

    void setAppearVelocity(const cv::Vec2d& appearVelocity); ///< Set velocity of time shift (pixels per frame)
    void setDisappearDelay(const double& disappearDelay);    ///< Time from appearing to disappearing (in frames)

    void render(const std::string& outputPath, int frameLimit = -1); ///< Render credits to the output path

private:
    ///< Render one frame to the output path & reuturn false if credits ended
    bool renderFrame(const std::string& outputPath, const int& time) const;
    ///< Render one credits line to the "frame" & edit imgLayout erasing rendered part & reuturn false if credits ended
    bool renderLine(cv::Mat& frame, cv::Mat& imgLayout, const cv::Point& rootPixel, const int& time) const;

    ///< in absolute time & position
    double calculateTransparency(const cv::Point& coord, const int& time, const double& disappearMultiplier, bool& hasEnded) const;
    ///< in relative time
    double calculateTransparency(const int& time, const double& disappearMultiplier, bool& hasEnded) const;
    ///< math function like sin(), but f(0) = 0, f(1) = 1, f(2) = 0
    static double waveFunction(double arg);

    static bool isPixelMarkerObject/*   */(const cv::Mat& imgLayout, const cv::Point& pixel); ///< Check if pixel is an object marker
    static bool isPixelMarkerEdge/*     */(const cv::Mat& imgLayout, const cv::Point& pixel); ///< Check if pixel is an edge marker
    static double getPixelDisappearMul/**/(const cv::Mat& imgLayout, const cv::Point& pixel); ///< Calculate disappear multiplier contained in marker pixel

    static std::string getOutputFileName(const std::string& outputPath, const int& time);

    cv::Mat imgLayout;
    cv::Mat imgText;

    cv::Vec2d appearVelocity;   ///< Velocity of time shift (pixels per frame)
    double disappearDelay;      ///< Time from appearing to disappearing (in frames)
};
