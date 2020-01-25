// Simple library-based anticheat
#include <iostream>
#include <unistd.h>
#include <memory>
#include <ctime>
#include <string>

using namespace std;


// Thx StackOverflow!
std::string exec(const char* cmd) {
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

namespace anticheat {
    volatile bool flag = false;
    int hash_str(uint16_t pid)  {
        string command = "pldd ";
        command += to_string(pid);
        string out = exec(command.c_str());
        hash<string> h;
        return h(out);
    }

    int Init(void(*killer)(void)) {
        cout << "Simple anticheat initializer" << endl;
        int hash_old, hash_new;
        hash_old = hash_new = 0;
        for(;;) {
            if(flag == true) {
                cout << "Deinitalizing anitcheat" << endl;
                exit(EXIT_SUCCESS);
            }
            if(hash_old == 0) {
                cout << "it's first running, get hash" << endl;
                hash_old = hash_str(getpid());
            }
            hash_new = hash_str(getpid());
            if(hash_new != hash_old) {
                cout << "Cheat loading detected, killing!" << endl;
                killer(); 
            }
        }
    }
    void DeInit(void) {
        flag = true;
    }
    
}