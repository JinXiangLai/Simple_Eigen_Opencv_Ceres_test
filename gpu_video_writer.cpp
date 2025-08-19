#include <iostream>
#include <opencv2/cudacodec.hpp>  // CUDA 视频编码器
#include <opencv2/opencv.hpp>

int main() {

    if (cv::cuda::getCudaEnabledDeviceCount() == 0) {
        std::cout << "CUDA is NOT available!" << std::endl;
    } else {
        std::cout << "CUDA is available!" << std::endl;
        std::cout << cv::getBuildInformation() << std::endl;
    }

     // 初始化CUDA
     cv::cuda::printCudaDeviceInfo(cv::cuda::getDevice());

    // 1. 初始化视频写入器（CUDA 加速）
    const std::string output_video_path = "output_gpu.mp4";
    const int frame_width = 640;   // 视频宽度
    const int frame_height = 480;  // 视频高度
    const double fps = 30.0;       // 帧率
    const int codec =
        cv::VideoWriter::fourcc('H', '2', '6', '4');  // H.264 编码

    // 2. 创建 CUDA 视频写入器
    cv::Ptr<cv::cudacodec::VideoWriter> gpu_writer =
        cv::cudacodec::createVideoWriter(output_video_path,
                                         cv::Size(frame_width, frame_height));

    if (gpu_writer.empty()) {
        std::cerr << "Error: Failed to initialize CUDA video writer!"
                  << std::endl;
        return -1;
    }

    // 3. 模拟生成测试图像（实际应用中替换为你的图像输入）
    for (int i = 0; i < 100; i++) {
        // 生成一个彩色渐变图像（CPU 端）
        cv::Mat cpu_frame(frame_height, frame_width, CV_8UC3);
        cpu_frame =
            cv::Scalar(i % 255, (i * 2) % 255, (i * 3) % 255);  // 渐变颜色

        // 将 CPU 数据上传到 GPU（如果输入已经是 GpuMat，可跳过）
        cv::cuda::GpuMat gpu_frame;
        gpu_frame.upload(cpu_frame);

        // 4. 写入视频（GPU 加速）
        gpu_writer->write(gpu_frame);

        std::cout << "Writing frame " << i << std::endl;
    }

    // 5. 释放资源
    gpu_writer.release();
    std::cout << "Video saved to: " << output_video_path << std::endl;

    return 0;
}