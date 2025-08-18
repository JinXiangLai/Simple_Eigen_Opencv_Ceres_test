#include "common.h"

using namespace std;

int main(int argc, char **argv) {

  double message_ratio = 0.5;

  if (argc > 1) {
    message_ratio = atof(argv[1]);
  }
  const string img_path = "../src/test.png";
  cv::Mat img = cv::imread(img_path, cv::IMREAD_GRAYSCALE);
  if (img.empty()) {
    cout << "img empty!";
    return -1;
  } else {
    cout << img.size << endl;
    // cv::imshow("test img", img);
    // cv::waitKey();
  }

  // cv::COLOR_BGR2GRAY;
  message_ratio = min(message_ratio, 1.0);
  Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> mat;
  mat.resize(img.rows, img.cols);
  for (int i = 0; i < img.rows; ++i) {
    for (int j = 0; j < img.cols; ++j) {
      mat(i, j) = img.ptr<uint8_t>(i)[j];
    }
  }
  // cout << "mat:\n" << mat << endl;

  Eigen::JacobiSVD<Eigen::MatrixXf> svd(mat, Eigen::ComputeFullU |
                                                 Eigen::ComputeFullV);
  const Eigen::MatrixXf U = svd.matrixU();
  const Eigen::MatrixXf V = svd.matrixV();
  Eigen::VectorXf s = svd.singularValues();

  cout << "singularValues: " << s.head(10).transpose() << endl;

  // 二分法查找最低满足信息比的索引
  // const double sum_norm = s.norm();
  // int a = 0;
  // int b = s.rows() - 1;
  // int m = 0;
  // cout << "a, b: " << a << ", " << b << ", sum " << sum_norm << endl;
  // while (a < b) {
  //  m = (a + b) / 2;
  //  const double cur_norm = s.middleRows(0, m).norm();
  //  sleep(1.0);
  //  const double ratio = cur_norm / sum_norm;
  //  cout << "a, b, m, ratio: " << a << ", " << b << ", " << m << ", " << ratio
  //       << endl;
  //  if (ratio > message_ratio) {
  //    b = m;
  //  } else if (ratio < message_ratio) {
  //    a = m;
  //  } else {
  //    cout << "break m: " << m << " ratio: " << ratio << endl;
  //    break;
  //  }

  //  // cout << "m: " << m << " ratio: " << ratio << endl;
  //}

  int m = int(message_ratio * s.rows());

  const Eigen::MatrixXf compress_mat = U.block(0, 0, U.rows(), m) *
                                       s.middleRows(0, m).asDiagonal() *
                                       V.block(0, 0, V.rows(), m).transpose();

  cv::Mat com_img = img.clone();
  for (int i = 0; i < img.rows; ++i) {
    for (int j = 0; j < img.cols; ++j) {
      //  mat(i, j) = img.ptr<uint8_t>(i)[j];
      com_img.ptr<uint8_t>(i)[j] = uint8_t(compress_mat(i, j));
    }
  }

  cv::Mat merge_img(img.rows, img.cols * 2, img.type());
  img.copyTo(merge_img.rowRange(0, img.rows).colRange(0, img.cols));
  com_img.copyTo(
      merge_img.rowRange(0, img.rows).colRange(img.cols, img.cols * 2));
  cv::imshow("merge_img", merge_img);
  cv::waitKey();

  return 0;
}