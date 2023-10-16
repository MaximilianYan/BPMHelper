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
    Credits();                                                  ///< Create empty object (calling Credits::upload is necessary)
    
    ///< Upload images with credits text and layout (text : RGBA, layout : RGB)
    Credits(const std::string& fileNameText, const std::string& fileNameLayout);

    ///< Upload images with credits text and layout (text : RGBA, layout : RGB)
    void upload(const std::string& fileNameText, const std::string& fileNameLayout);

    void setAppearVelocity(const cv::Vec2d& appearVelocity);    ///< Set velocity of time shift (pixels per frame)
    void setDisappearDelay(const double& disappearDelay);       ///< Time from appearing to disappearing (in frames)

    void render(const std::string& outputPath);

private:
    cv::Mat imgLayout;
    cv::Mat imgText;

    cv::Vec2d appearVelocity;   ///< Velocity of time shift (pixels per frame)
    double disappearDelay;      ///< Time from appearing to disappearing (in frames)
};
