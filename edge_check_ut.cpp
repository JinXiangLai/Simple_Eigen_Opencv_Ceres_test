#include <fmt/core.h>
#include <iostream>
#include <vector>

#include <Eigen/Dense>

using namespace std;
inline constexpr int kMinEdgeLen =
    10;  // 分辨率增大，测试发现，选点靠近边缘时，观测畸变大，易导致后续跟踪失败，需要报重新选点

bool MarkerDetectPixelValid(const int imgH, const int imgW, const double& r,
                            const Eigen::Vector2d& obv) {
    // 首先检验量测点不在图像边缘处，若在边缘则不添加，
    // 检验规则是外切正方形在图像内

    vector<Eigen::Vector2d> corners = {
        {r, r}, {-r, r}, {-r, -r}, {r, -r}};  // 为了滤除靠边缘的检测值
    for (int i = 0; i < corners.size(); ++i) {
        double x = obv.x() + corners[i].x();
        if (x > imgW - kMinEdgeLen || x < kMinEdgeLen) {
            cout << "Reject obv for detect marker x: " << x << " l: " << r
                 << " & imgW_: " << imgW << " & kMinEdgeLen: " << kMinEdgeLen
                 << endl;
            return false;
        }
        double y = obv.y() + corners[i].y();
        if (y > imgH - kMinEdgeLen || y < kMinEdgeLen) {
            cout << "Reject obv for detect marker y: " << y << " l: " << r
                 << " & imgH_: " << imgH << " & kMinEdgeLen: " << kMinEdgeLen
                 << endl;
            return false;
        }
    }

    return true;
}

int main() {
    const Eigen::Vector2d obv(689, 788);
    const int imgH = 832, imgW = 1280;
    const int r = 34;
    const bool valid = MarkerDetectPixelValid(imgH, imgW, r, obv);
    if (valid) {
        cout << "check valid!" << endl;
    } else {
        cout << "check invalid!" << endl;
    }

    const Eigen::Vector2d obv1(658, 438);
    const Eigen::Vector2d obv2(698, 767);
    const double norm = (obv1 - obv2).norm();
    cout << "norm: " << norm << endl;
    string map_data_path_ = "/home/ht/abc";
    uint64_t _cur_timestamp = 123;
    string save_name =
        fmt::format("{}{}_mvm.raw", map_data_path_, _cur_timestamp);
    cout << "save_name: " << save_name << endl;
    cout << fmt::format("pi: {}, pi:{:.2f}, int{}\n", M_PI, M_PI, int(2));
    Eigen::Matrix3d H;
    // H << 334.199, 0.0130992, -25.4604, 0.0130992, 348.781, 529.463, -25.4604,
    //     529.463, 805.688;
    H << 677.412, 3.55068, -9.61649, 3.55068, 650.906, 129.936, -9.61649,
        129.936, 26.0958;
    H += Eigen::Matrix3d::Identity() * 0.0001;
    cout << "invH * 9:\n" << H.inverse() << endl;
    return 0;
}