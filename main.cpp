#include <iostream>
#include <getopt.h>

using std::cout;
using std::endl;
using std::string;


void help(char* arg0) {
    cout << "Usage: " << arg0 << " -g" << " <string>" << " | " << arg0 << " -c" << " <string>" << " <hash number>" << endl;
}

void opt_requirement(char opt) {
    switch (opt) {
        case 'c':
            cout << "Option '-" << static_cast<char>(optopt) << "' requires <string> and <hash number> arguments" << endl;
            break;
        case 'g':
            cout << "Option '-" << static_cast<char>(optopt) << "' requires <string> argument" << endl;
            break;
        default:
            cout << "Unknown option '-" << static_cast<char>(optopt) << "'" << endl;
    }
}

int main(int argc, char* argv[]) {
    // Disable error messages from getopt
    opterr = 0;
    

    if (argc > 1) {
        int opt;
        std::hash<string> hashObj;
        string arg2, arg3;

        // Prevent segmentation fault
        if (argc >= 3 && argc <=4) arg2 = argv[2];
        while ((opt = getopt(argc, argv, "c:g:")) != -1) {
            switch (opt) {
                case 'c':
                    if (argc == 4) {
                        arg3 = argv[3];
                        // Check if the hash number is equal to arg3
                        if (std::to_string(hashObj(arg2)) == arg3) {
                            cout << "True" << endl;
                        } else {
                            cout << "False" << endl;
                        }
                    } else {
                        std::cerr << "Error: <hash number> is required" << endl;
                        return -1;
                    }
                    break;
                case 'g':
                    // Generate a hash number
                    cout << "String: " << arg2 << "\n" << "Hash: " << hashObj(arg2) << endl;
                    break;
                case '?':
                    opt_requirement(optopt);
                    help(argv[0]);
                    break;
                default:
                    std::cerr << "Unknown error!" << endl;
                    return -2;
            }
        }
    } else {
        std::cerr << "Error: no arguments!" << endl;
        help(argv[0]);
        return -1;
    }

    return 0;
}