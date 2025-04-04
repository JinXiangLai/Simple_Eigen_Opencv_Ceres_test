#include "common.h"

using namespace std;

int main() {
    const int size = 100;
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> mat_col = Eigen::MatrixXd::Random(size, size);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> mat_row = Eigen::MatrixXd::Random(size, size);

    // 测试列优先矩阵乘法
    auto start = chrono::high_resolution_clock::now();
    Eigen::MatrixXd result_col = mat_col * mat_col;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_col = end - start;
    cout << "ColMajor time: " << elapsed_col.count() << " seconds\n";

    // 测试行优先矩阵乘法
    start = chrono::high_resolution_clock::now();
    Eigen::MatrixXd result_row = mat_row * mat_row;
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_row = end - start;
    cout << "RowMajor time: " << elapsed_row.count() << " seconds\n";

    pair<Eigen::Quaterniond, Eigen::Vector3d> pose;
    pose.first = Eigen::Quaterniond(Eigen::AngleAxisd(0.5*M_PI, Eigen::Vector3d::UnitZ()).toRotationMatrix());
    pose.second = Eigen::Vector3d(1, 2, -0.3);
    cout << "pose.first\n: " << pose.first.toRotationMatrix() << endl;
    cout << "pose.second: " << pose.second.transpose() << endl;

    return 0;
}