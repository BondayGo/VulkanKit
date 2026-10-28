cmake_minimum_required(VERSION 3.16)
project(VulkanKitReport LANGUAGES CXX)

add_executable(vk_report vk_report.cpp)
target_compile_features(vk_report PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(vk_report PRIVATE /W4 /EHsc)
endif()
