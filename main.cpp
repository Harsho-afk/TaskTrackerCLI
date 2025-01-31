#include <cctype>
#include <iostream>
#include <string>

int add(std::string desc,int status);

int main(int argc, char *argv[]) {
    while (1) {
        if (argc < 2) {
            // replace with help
            std::cerr << "Pass arguments\n";
        }
        if (argc == 2) {
            if (argv[1] == std::string("list")) {
                // list
                std::cout << "listing\n";
            } else {
                // replace with help
                std::cerr << "wrong arguments\n";
            }
        }
        if (argc > 2) {
            if (argv[1] == std::string("add")) {
                std::string desc(argv[2]);
                if (!(desc[0] == '"' && desc.back() == '"') &&
                    !(desc[0] == '\'' && desc[0] == '\'')) {
                    std::cerr << "wrong desc format\n";
                }
                int status = 0;
                if(argc == 4) {
                    std::string posStatus(argv[3]);
                    if(posStatus.length() == 1 && isdigit(posStatus[0])) {
                        status = posStatus[0] - '0';
                    }
                }
                add(desc,status);
            }
        }
    }
    return 0;
}
