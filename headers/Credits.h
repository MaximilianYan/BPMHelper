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

    void render(const std::string& outputPath);              ///< Render credits to the output path

private:
    ///< Render one frame to the output path & reuturn false if frame is empty
    bool renderFrame(const std::string& outputPath, const int& time);
    ///< Render one credits line to the "frame" & edit imgLayout erasing rendered part & reuturn false if (the rendered part of the) frame is empty
    bool renderLine(cv::Mat& frame, cv::Mat& imgLayout, const cv::Point& rootPixel, const int& time);



    static bool isPixelObjectMarker(const cv::Mat& imgLayout, const cv::Point& pixel); ///< Check if pixel is object marker

    cv::Mat imgLayout;
    cv::Mat imgText;

    cv::Vec2d appearVelocity;   ///< Velocity of time shift (pixels per frame)
    double disappearDelay;      ///< Time from appearing to disappearing (in frames)
};
