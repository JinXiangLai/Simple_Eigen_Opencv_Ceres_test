#include "common.h"

using namespace std;

int main(int argc, char** argv) {
    double ratio = 1e-6;
    if (argc > 1) {
        ratio = atof(argv[1]);
    }
    const Eigen::Vector3d true_x(10, 31, 7.01);
    Eigen::Matrix3d H;
    H << 42.9978, -0.263839, -12.3629, -0.263839, 43.7347, 39.1302, -12.3629,
        39.1302, 38.4308;
    const Eigen::Vector3d true_b = H * true_x;

    const Eigen::Vector3d noise_x(1.0, 1.0, 0.5);

    const Eigen::Vector3d noise_b = true_b + H * noise_x;

    const Eigen::Matrix3d inv_H = H.inverse();
    Info << "H:\n" << H;
    Info << "H.determinant(): " << H.determinant();
    Info << "inv_H:\n" << inv_H;
    Info << "H * inv_H:\n" << H * inv_H;

    const Eigen::Vector3d est_x_from_invH = inv_H * noise_b;

    Eigen::JacobiSVD<Eigen::Matrix3d> svd(
        H, Eigen::ComputeFullU | Eigen::ComputeFullV);
    const Eigen::Vector3d& singular_values = svd.singularValues();
    Info << "singular_values: " << singular_values.transpose();
    Info << "conditional num: " << singular_values[0] / singular_values[2];
    Eigen::Vector3d inv_s(0, 0, 0);
    const double th = singular_values[0] * ratio;
    for (int i = 0; i < singular_values.rows(); ++i) {
        if (singular_values[i] > th) {
            inv_s[i] = 1.0 / singular_values[i];
        }
    }
    const Eigen::Matrix3d U = svd.matrixU();
    const Eigen::Matrix3d V = svd.matrixV();
    const Eigen::Matrix3d pseudo_inv_H = V * inv_s.asDiagonal() * U.transpose();
    Info << "pseudo_inv_H:\n" << pseudo_inv_H;
    Info << "pseudo_inv_H * H:\n" << pseudo_inv_H * H;

    const Eigen::Vector3d est_x_from_pseudoInvH = pseudo_inv_H * noise_b;

    Info << "true_x: " << true_x.transpose()
         << "\nest_x_from_invH: " << est_x_from_invH.transpose()
         << "\nest_x_from_pseudoInvH: " << est_x_from_pseudoInvH.transpose();
    const Eigen::Vector3d dx1 = true_x - est_x_from_invH;
    const Eigen::Vector3d dx2 = true_x - est_x_from_pseudoInvH;
    Info << "error1: " << dx1.norm() << ", error2: " << dx2.norm();
    return 0;
}