/**
 * @file BPMHelper.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Class with bpm-visualization tools
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>

 /**
  * @brief Class with bpm-visualization tools
  */
class BPMHelper {
public:
    BPMHelper(cv::Size FRAME_SIZE, double fps, double bpm);
    BPMHelper(cv::Size FRAME_SIZE);
    BPMHelper();                                            ///< default 1920x1080 frame size
    ~BPMHelper();

    void setBpm(double bpm);
    void setDuration(double duration);                      ///< set video duration in seconds

    enum RENDER_ERROR {
        OK = 0,
        FILE_ERR,
    };

    RENDER_ERROR render(std::ostream& logOutput);

private:
    const cv::Size FRAME_SIZE;
    double fps;                 ///< frames per second
    double bpf;                 ///< beats per frame
    double durationF;           ///< video duration in frames
};
