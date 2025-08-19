#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>  // CUDA算术运算核心头文件
#include <iostream>

int main() {
    // 1. 检查CUDA设备
    if (cv::cuda::getCudaEnabledDeviceCount() == 0) {
        std::cerr << "CUDA device not found!" << std::endl;
        return -1;
    }
    cv::cuda::printCudaDeviceInfo(0); // 打印第0块GPU信息

    cv::cuda::DeviceInfo dev_info;
    std::cout << "Compute Capability: sm_" 
              << dev_info.majorVersion() << dev_info.minorVersion() << std::endl;
    return 0;

    // 2. 创建测试矩阵（CPU端）
    cv::Mat cpu_mat1 = (cv::Mat_<uchar>(3,3) << 1,2,3,4,5,6,7,8,9);
    cv::Mat cpu_mat2 = (cv::Mat_<uchar>(3,3) << 9,8,7,6,5,4,3,2,1);
    cv::Mat cpu_result;

    // 3. 上传数据到GPU
    cv::cuda::GpuMat gpu_mat1, gpu_mat2, gpu_result;
    gpu_mat1.upload(cpu_mat1);
    gpu_mat2.upload(cpu_mat2);

    // 4. 执行CUDA加法
    cv::cuda::add(gpu_mat1, gpu_mat2, gpu_result);

    // 5. 下载结果到CPU
    gpu_result.download(cpu_result);

    // 6. 验证结果
    std::cout << "Matrix1:\n" << cpu_mat1 << "\n\n"
              << "Matrix2:\n" << cpu_mat2 << "\n\n"
              << "CUDA Add Result:\n" << cpu_result << std::endl;

    return 0;
}