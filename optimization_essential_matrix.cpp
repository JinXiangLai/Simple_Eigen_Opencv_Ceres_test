#include "common.h"

using namespace std;

// 在优化本质矩阵时，由于平移t的尺度未知，通过t=R*t的方式优化t，
// 但是 [R*t]x ?= R*[t]x吗？不等于



int main() {
    Eigen::Vector3d rpy{5, 6, 7};
    rpy *= kDeg2Rad;
    Eigen::Vector3d t{1, 2, 3};
    t.normalize();

    Eigen::Matrix3d R =
        Eigen::AngleAxisd(rpy.z(), Eigen::Vector3d::UnitZ()) *
        Eigen::AngleAxisd(rpy.y(), Eigen::Vector3d::UnitY()) *
        Eigen::AngleAxisd(rpy.x(), Eigen::Vector3d::UnitX()).toRotationMatrix();

    cout << "[R*t]x:\n" << SkewSymmetric(R * t) << endl;
    cout << "R*[t]x:\n" << R * SkewSymmetric(t) << endl;
    
    // vector<int> a = {1, 2};
    // vector<reference_wrapper<vector<int>> >b(1);
    // b[0] = a;
    // a.push_back(3);
    // for(const int n : b[0].get()) {
    //     cout << n << " ";
    // }
    // cout << endl;
    cout << ceil(double(2)/3) << endl;

    Eigen::Matrix3d testArray = Eigen::Matrix3d::Identity();
    testArray.diagonal() << 4, 9, 16;
    cout << testArray.diagonal().array().sqrt().transpose() << endl; // 2, 3, 4

    set<int> updateId = {-1, 3, 4};
    updateId.erase(3);
    updateId.erase(5);
    cout << "update id:";
    for(const int& id : updateId) {
        cout << " " << id;
    }
    cout << endl;
    return 0;
}
