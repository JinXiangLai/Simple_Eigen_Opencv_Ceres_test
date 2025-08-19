cmake_minimum_required(VERSION 3.10)
# ROS 的g2o会污染现版本，需要把 source ros关闭
project(edge_slam)

if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic) # ljx
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall   -O1 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall   -O1 -g")
set(CMAKE_BUILD_TYPE "Debug")
IF (NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ELSE()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})


# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native") # 该指令可能导致意外core dump
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")

add_compile_options(-Werror=return-type)


find_package(Eigen3 REQUIRED)
find_package(OpenCV 4 REQUIRED)

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/common.h
)

link_libraries(
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  -lfmt
)

# 添加可执行文件
add_executable(eigen_row_col_marjor_efficiency eigen_row_col_marjor_efficiency.cpp)
add_executable(cv_mat_block cv_mat_block.cpp)
add_executable(optimization_essential_matrix optimization_essential_matrix.cpp)
add_executable(inverse_depth_calculate inverse_depth_calculate.cpp)
add_executable(img_pca img_pca.cpp)
add_executable(binocular_half_rotation binocular_half_rotation.cpp)
add_executable(analysis_triangulate_A_matrix analysis_triangulate_A_matrix.cpp)
add_executable(edge_check_ut edge_check_ut.cpp)
add_executable(gpu_video_writer gpu_video_writer.cpp)
add_executable(test_cv_cuda test_cv_cuda.cpp)
add_executable(test_perf_create_and_delete_dir test_perf_create_and_delete_dir.cpp)
add_executable(eigen_parellel_error eigen_parellel_error.cpp)
add_executable(svd_singular_matrix svd_singular_matrix.cpp)
