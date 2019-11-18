#include <getopt.h>
#include <iostream>
#include <stdlib.h>
#include <string>

struct options_set_t {
    bool help{0};
    bool version{0};
    bool list{0};
    std::string list_arg;
};

int main(int argc, char **argv) {
    options_set_t opts;

    while (true) {
        int option_index = 0;
        static option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {"list", required_argument, 0, 'l'},
            {0, 0, 0, 0}
        };

        int option = getopt_long(argc, argv, "hvl:", long_options, nullptr);
        if (option == -1) {
            break;
        }
        switch (option) {
        case 'h':
            opts.help = true;
            break;
        case 'v':
            opts.version = true;
            break;
        case 'l':
            opts.list = true;
            opts.list_arg = optarg;
            break;
        default:
            break;
        }
    }

    if (opts.help) {
        std::cout << "Usage:\t\t" << argv[0] << " [-h] [--help] [-v] [--version] [-l] [--list]" << std::endl;
    }
    if (opts.version) {
        std::cout << "Version:\t 1.0.0" << std::endl;
    }
    if (opts.list) {
        std::cout << "List arguments:\t ";
        if (opts.list_arg.find(",") == std::string::npos) {
            std::cout << opts.list_arg << std::endl;
        } else {
            std::string arguments = opts.list_arg;
            int last_pos = 0;
            size_t pos = 0;
            while ((pos = arguments.find(",")) != std::string::npos) {
                std::string token = arguments.substr(0, pos);
                std::cout << token << " ";
                arguments.erase(0, pos + 1);
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
