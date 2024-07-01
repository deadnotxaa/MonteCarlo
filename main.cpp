#include "Parser.hpp"
#include "hit.h"

#include <iostream>
#include <random>
#include <fstream>
#include <string>

#include <omp.h>


uint64_t CalculateOMP(const float*, uint64_t, deadnotxaa::Arguments&);
uint64_t CalculateWithoutOMP(const float*, uint64_t);
void WriteResult(float, const float*, std::ofstream&);


int main(int argc, char** argv) {
    deadnotxaa::Arguments args = deadnotxaa::ParseArguments(argc, argv);
    auto axis_range = get_axis_range();

    std::ifstream input_file(std::string(args.input_filename), std::ios::in);
    std::ofstream output_file(std::string(args.output_filename), std::ios::out);

    uint64_t points_number;
    input_file >> points_number;

    omp_set_num_threads(static_cast<int32_t>(args.number_of_threads));
    uint64_t hits_number;
    if (args.threading_type == deadnotxaa::ThreadingType::NoTreading) {
        hits_number = CalculateWithoutOMP(axis_range, points_number);
    } else {
        hits_number = CalculateOMP(axis_range, points_number, args);
    }

    WriteResult((float)hits_number / (float)points_number, axis_range, output_file);
    return 0;
}


uint64_t CalculateOMP(const float* axis_range, uint64_t points_number, deadnotxaa::Arguments& args) {
    uint64_t hit_counter = 0;

    double start = omp_get_wtime();
#pragma omp parallel default(none) shared(axis_range, points_number, hit_counter)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> x_axis_dis(axis_range[0], axis_range[1]);
        std::uniform_real_distribution<float> y_axis_dis(axis_range[2], axis_range[3]);
        std::uniform_real_distribution<float> z_axis_dis(axis_range[4], axis_range[5]);

        int local_cnt = 0;
        int i;

#pragma omp for nowait schedule(static)
        for (i = 0; i < points_number; ++i) {
            if (hit_test(x_axis_dis(gen), y_axis_dis(gen), z_axis_dis(gen))) {
                ++local_cnt;
            }
        }

#pragma omp critical
        hit_counter += local_cnt;
    }
    double end = omp_get_wtime();
    std::printf("Time (%i thread(s)): %g ms\n", args.number_of_threads, (end - start) * 1000);

    return hit_counter;
}


uint64_t CalculateWithoutOMP(const float* axis_range, uint64_t points_number) {
    uint64_t hit_counter = 0;

    double start = omp_get_wtime();
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> x_axis_dis(axis_range[0], axis_range[1]);
        std::uniform_real_distribution<float> y_axis_dis(axis_range[2], axis_range[3]);
        std::uniform_real_distribution<float> z_axis_dis(axis_range[4], axis_range[5]);

        for (int i = 0; i < points_number; ++i) {
            if (hit_test((float)x_axis_dis(gen), (float)y_axis_dis(gen), (float)z_axis_dis(gen))) {
                ++hit_counter;
            }
        }
    }
    double end = omp_get_wtime();
    std::printf("Time (%i thread(s)): %g ms\n", 0, (end - start) * 1000);

    return hit_counter;
}

void WriteResult(float rate, const float* axis_range, std::ofstream& output_file) {
    float volume = rate * (axis_range[1] - axis_range[0]) * (axis_range[3] - axis_range[2]) * (axis_range[5] - axis_range[4]);
    output_file << volume;
}
