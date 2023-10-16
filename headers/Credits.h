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
    Credits();

    void upload(std::string textFile, std::string zonesFile); ///< Upload images with credits text and 

private:
    cv::Mat zones;
    cv::Mat text;
};
