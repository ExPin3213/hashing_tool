#include <iostream>
#include <getopt.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;


void help(char* arg0) {
    cout << "Usage: " << arg0 << " -g" << " <string>" << " | " << arg0 << " -c" << " <string>" << " <hash number>" << endl;
}

void opt_requirement(char opt) {
    switch (opt) {
        case 'c':
            cerr << "Option '-" << static_cast<char>(optopt) << "' requires <string> and <hash number> arguments" << endl;
            break;
        case 'g':
            cerr << "Option '-" << static_cast<char>(optopt) << "' requires <string> argument" << endl;
            break;
        default:
            cerr << "Unknown option '-" << static_cast<char>(optopt) << "'" << endl;
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
        if (argc >= 3 && argc <= 4) arg2 = argv[2];
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
                    } else if (argc < 4) {
                        cerr << "Error: <hash number> is required!" << endl;
                    } else {
                        cerr << "Error: too many arguments!" << endl;
                    }
                    break;
                case 'g':
                    if (argc == 3) {
                        // Generate a hash number
                        cout << "String: " << arg2 << "\n" << "Hash: " << hashObj(arg2) << endl;
                    } else if (argc < 3) {
                        cerr << "Error: <hash number> is required!" << endl;
                    } else {
                        cerr << "Error: too many arguments!" << endl;
                    }
                    break;
                case '?':
                    opt_requirement(optopt);
                    help(argv[0]);
                    break;
                default:
                    cerr << "Unknown error!" << endl;
            }
        }
    } else {
        cerr << "Error: no arguments!" << endl;
        help(argv[0]);
    }

    return 0;
}