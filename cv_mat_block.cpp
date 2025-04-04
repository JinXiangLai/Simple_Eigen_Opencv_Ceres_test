#include "common.h"

using namespace std;

int main() {

    cv::Mat_<double> m0 = (cv::Mat_<double>(4, 4) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    cout << "m0:\n" << m0 << endl;
    cout << "m0(cv::Range(0, 3), cv::Range(0, 3)):\n" << m0(cv::Range(0, 3), cv::Range(0, 3)) << endl;
    cout << "m0(cv::Range(0, 3), cv::Range(3, 4)):\n" << m0(cv::Range(0, 3), cv::Range(3, 4)) << endl;

    cv::Mat_<double> tvec = (cv::Mat_<double>(1, 3) << 1, -2, 3);
    Eigen::Vector3d t(tvec.ptr<double>());
    cout << "t: " << t.transpose() << endl;

    Eigen::Matrix3d R = Eigen::AngleAxisd(5*kDeg2Rad, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    // Eigen::AngleAxisd dr(R.block(0, 0, 3, 3)); // 无法编译通过，block()不返回Eigen::Matrix类型
    // cout << "dr ang: " << dr.angle() * kRad2Deg << endl;
    // cout << "dr axis: " << dr.axis().transpose() << endl;

    // Eigen::Matrix<double, 3, 1> m{-1}; (-1)// 均不可行
    Eigen::Matrix<double, 3, 1> m;
    m.setConstant(-1.1);
    cout << "m: " << m.transpose() << endl;

    return 0;

}