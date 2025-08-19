#include <fstream>
#include <iostream>
#include <vector>

#include <Eigen/Dense>
#include <random>

using namespace std;

#define COLS 3  // 4

bool ReadAmatrixFromFile(const string& filePath, vector<Eigen::MatrixXd>& As);
Eigen::Vector3d GetPwBySVD(const Eigen::MatrixXd& A);
void FindDuplicateEquations(const Eigen::MatrixXd& A);

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "usage: ./main  text_file_path!" << endl;
        return 0;
    }

    const string filePath(argv[1]);
    vector<Eigen::MatrixXd> As;
    bool readSucceed = ReadAmatrixFromFile(filePath, As);
    if (!readSucceed) {
        cout << "Get data from " << filePath << "error!" << endl;
        return -1;
    }

    for (int i = 0; i < As.size(); ++i) {
        const Eigen::Vector3d estPw = GetPwBySVD(As[i]);
        cout << "estPw[" << i << "]: " << estPw.transpose() << endl;
    }

    return 0;
}

bool ReadAmatrixFromFile(const string& filePath, vector<Eigen::MatrixXd>& As) {
    // 打开文件
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cerr << "Failed to open file!" << endl;
        return false;
    }

    const string splitSymbol = ", ";

    // 读取一行数据
    string line;
    vector<double> data;
    while (getline(inFile, line)) {
        // 使用 stringstream 分割数据
        stringstream ss(line);

        string token;

        // 以 ", " 为分隔符分割数据
        while (getline(ss, token, ',')) {
            // 去除 token 前后的空格
            token.erase(0, token.find_first_not_of(' '));  // 删除前导空格
            token.erase(token.find_last_not_of(' ') + 1);  // 删除尾随空格
            data.push_back(stod(token));
        }

        // 输出分割后的数据
        // cout << "Read data:\n";
        // for (const auto& value : data) {
        //     cout << value << ", ";
        // }
        // cout << endl << endl;

        const int rows = data.size() / COLS;
        Eigen::MatrixXd A =
            Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic,
                                     Eigen::RowMajor>>(data.data(), rows, COLS);
        As.push_back(A);
        cout << "A.size: [" << A.rows() << " x " << A.cols() << "]" << endl;
        cout << "A:\n" << A << endl;
        data.clear();
    }

    if (As.empty()) {
        cerr << "Failed to read line from file!" << endl;
    }

    // 关闭文件
    inFile.close();
    return 1;
}

Eigen::Vector3d GetPwBySVD(const Eigen::MatrixXd& A) {
#if COLS == 4
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeFullV);
    const Eigen::Vector4d bestV =
        svd.matrixV().col(svd.singularValues().size() - 1);
    const Eigen::Vector3d estPw = bestV.head(3) / bestV[3];

    const Eigen::Vector4d& singularValues = svd.singularValues();
    cout << "singularValues on normlized plane: " << singularValues.transpose()
         << endl;
    cout << "condition number: " << singularValues[0] / singularValues[3]
         << endl;  // 这里应该越小越好
    // 飞机能看到的着落点不可能比飞机高
    if (estPw.z() > 0) {
        return -estPw;
    }
#else
    // 缺少res向量
    const Eigen::Vector3d estPw = Eigen::Vector3d::Zero();
#endif
    return estPw;
}

void FindDuplicateEquations(const Eigen::MatrixXd& A) {
    vector<bool> equationUseful(
        A.rows() / 2, true);  // 这里是计算齐次坐标值，因此无法使用条件数来判断
}
