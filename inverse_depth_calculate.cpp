#include "common.h"

using namespace std;

int main() {
    Eigen::Vector3d rpy{5, 6, 7};
    rpy *= kDeg2Rad;
    Eigen::Vector3d t1_0{1, 2, 3};
    Eigen::Matrix3d R1_0 =
        Eigen::AngleAxisd(rpy.z(), Eigen::Vector3d::UnitZ()) *
        Eigen::AngleAxisd(rpy.y(), Eigen::Vector3d::UnitY()) *
        Eigen::AngleAxisd(rpy.x(), Eigen::Vector3d::UnitX()).toRotationMatrix();
    
    const double trueiDepthi = 0.098;
    const Eigen::Vector3d px0{200, 300, 1};
    const Eigen::Vector3d Pc0 = 1.0/trueiDepthi * invK * px0;
    const Eigen::Vector3d Pc1 = R1_0 * Pc0 + t1_0;
    const Eigen::Vector3d Pn1 = (Eigen::Vector3d() << Pc1.x()/Pc1.z(), Pc1.y()/Pc1.z(), 1).finished();
    // 添加一点噪声
    const Eigen::Vector2d px1 = K.block(0, 0, 2, 3) * Pn1 + Eigen::Vector2d{1.0, 0.0};

    const Eigen::Matrix3d skewPx1 = SkewSymmetric({px1.x(), px1.y(), 1});
    // 只有前两维是有效的
    const Eigen::Vector2d rvalue = (-skewPx1 * K * R1_0 * invK * px0).head(2);
    const Eigen::Vector2d lvalue = (skewPx1 * K * t1_0).head(2);
    // 如何写成解不等式组的形式呢？
    // 那就得显示拆分各个等式了，然后变换成 mx1 * 1x1 = mx1的形式
    // va * ρ = vb ==> ρ = va.T*vb / va.T*va
    const auto rho = (lvalue.transpose() * rvalue) / (lvalue.transpose() * lvalue);
    
    const double r1 = rvalue[0] / lvalue[0], r2 = rvalue[1] / lvalue[1];
    cout << "r1: " << r1 << endl;
    cout << "r2: " << r2 << endl;
    cout << "0.5*(r1+r2): " << 0.5*(r1+r2) << endl;

    cout << "rho: " << rho << endl;

}