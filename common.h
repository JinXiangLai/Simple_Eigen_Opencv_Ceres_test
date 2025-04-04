#include <chrono>
#include <iostream>

#include <opencv2/opencv.hpp>

#include <Eigen/Dense>

constexpr double kRad2Deg = 180 / M_PI;
constexpr double kDeg2Rad = M_PI / 180;

constexpr int kImgWidth = 640;
constexpr int kImgHeight = 480;

// 行优先存入
// clang-format off
const Eigen::Matrix3d K = (Eigen::Matrix3d() << 620.0, 0.0, 320.0,
                                                0.0, 240.0, 420.0,
                                                0.0, 0.0, 1.0).finished();
const Eigen::Matrix3d invK = K.inverse();
// clang-format on

inline Eigen::Matrix3d SkewSymmetric(const Eigen::Vector3d& v) {
    Eigen::Matrix3d S;
    // clang-format off
    S << 0, -v(2), v(1), 
         v(2), 0, -v(0), 
        -v(1), v(0), 0;
    // clang-format on
    return S;
}
