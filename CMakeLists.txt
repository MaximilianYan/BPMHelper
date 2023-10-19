cmake_minimum_required(VERSION 3.0.0)
project(BPMHelper)

include_directories(headers)

add_executable(${PROJECT_NAME}
                    sources/main.cpp
                    sources/BPMHelper.cpp
                    )

include_directories("D:/programming/libraries/opencv-4.5.5/build-release/install/include")
target_link_libraries(${PROJECT_NAME}
                        # "D:/programming/libraries/opencv-4.6.0/opencv-build-release-freetype/bin/libopencv_world460.dll"
                        # "D:/programming/libraries/opencv-4.5.5/build-release/install/x64/mingw/bin/libopencv_world455.dll"
                        # "D:/programming/libraries/opencv-4.5.5/build-release/install/x64/mingw/bin/opencv_videoio_ffmpeg455_64.dll"
                        "D:/programming/libraries/opencv-4.5.5/build-release/bin/libopencv_world455.dll"
                        "D:/programming/libraries/opencv-4.5.5/build-release/bin/opencv_videoio_ffmpeg455_64.dll"
                        )


add_executable(${PROJECT_NAME}_credits
                        sources/mainCredits.cpp
                        sources/Credits.cpp
                        sources/AverageCounter.cpp
                        )

include_directories("D:/programming/libraries/opencv-4.5.5/build-release/install/include")
target_link_libraries(${PROJECT_NAME}_credits
                        "D:/programming/libraries/opencv-4.5.5/build-release/bin/libopencv_world455.dll"
                        "D:/programming/libraries/opencv-4.5.5/build-release/bin/opencv_videoio_ffmpeg455_64.dll"
                        )
