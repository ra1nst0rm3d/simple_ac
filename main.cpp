// Simple library-based anticheat
#include <iostream>
#include <memory>
#include <ctime>
#include <string>

using namespace std;

namespace anticheat {
    volatile bool flag = false;
    int hash_str(uint16_t pid)  {
        FILE* p;
        string* command = new string;
        *command = "pldd ";
        *command += to_string(pid);
        p = popen(command->c_str(), "r");
        delete command;
        unique_ptr<string> out(new string);
        char* buf = new char;
        *out = fgets(buf, sizeof(buf), p);
        hash<string> h;
        return h(*out);
    }

    int Init(uint16_t pid, void(*killer)(void)) {
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
                hash_old = hash_str(pid);
            }
            hash_new = hash_str(pid);
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