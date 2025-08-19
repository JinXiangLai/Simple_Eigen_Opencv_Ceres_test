#include <Eigen/Core>
#include <iostream>

using namespace std;

int main() {
    // 生成测试数据
    Eigen::MatrixXf A = Eigen::MatrixXf::Random(1000, 1000);

    // 记录两种计算结果
    Eigen::setNbThreads(1);
    Eigen::MatrixXf serial_result = A.array().sin().exp();

    Eigen::setNbThreads(4);
    Eigen::MatrixXf parallel_result = A.array().sin().exp();

    // 比较差异
    float max_diff = (serial_result - parallel_result).array().abs().maxCoeff();
    cout << "Max difference: " << max_diff << endl;
}
