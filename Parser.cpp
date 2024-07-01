#include "Parser.hpp"

deadnotxaa::Arguments deadnotxaa::ParseArguments(int argc, char** argv) {
    Arguments parsed_args;

    for (int i = 0; i < argc; ++i) {
        if (argv[i] == kInputFilenameArg) {
            parsed_args.input_filename = argv[i + 1];
        } else if (argv[i] == kOutputFilenameArg) {
            parsed_args.output_filename = argv[i + 1];
        } else if (argv[i] == kNoOpenMPArg) {
            parsed_args.threading_type = ThreadingType::NoTreading;
        } else if (argv[i] == kOpenMPThreadsArg) {
            if (std::strcmp(argv[i + 1], "default") == 0) {
                parsed_args.threading_type = ThreadingType::DefaultThreading;
            } else {
                parsed_args.threading_type = ThreadingType::CustomThreading;
                parsed_args.number_of_threads = std::stoul(argv[i + 1]);
            }
        }
    }

    return parsed_args;
}
