#pragma once

#include <string_view>
#include <string>
#include <cinttypes>
#include <cstring>

#include <omp.h>

namespace deadnotxaa {

const std::string_view kInputFilenameArg = "--input";
const std::string_view kOutputFilenameArg = "--output";
const std::string_view kNoOpenMPArg = "--no-omp";
const std::string_view kOpenMPThreadsArg = "--omp-threads";

enum class ThreadingType {
    NoTreading,
    DefaultThreading,
    CustomThreading,
};

struct Arguments {
    ThreadingType threading_type;
    uint32_t number_of_threads = omp_get_max_threads();
    std::string_view input_filename;
    std::string_view output_filename;
};

Arguments ParseArguments(int, char**);

} // deadnotxaa
