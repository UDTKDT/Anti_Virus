#include <getopt.h>
#include <iostream>
#include <cstring>
#include <sys/ptrace.h>
#include <chrono>
<<<<<<< HEAD
<<<<<<< HEAD
#include <vector>
#include <dirent.h>
#include <fstream>
#include <unistd.h>
=======
#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
>>>>>>> 2bf9cde838a041c93af123dbc95fb9d8ab86ca47
=======
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <filesystem>
#include <string>
#include <fstream>
#include <dirent.h>
#include "process.h"
#include <dirent.h>
#include <fstream>
#include <vector>
#include <signal.h>
#include <algorithm>
#include "antidbg.h"
#include "scan.h"
>>>>>>> 582089411009f0f4a9bf94b2c6318716af4aae23

using namespace std;

struct option options[]={
    {"help", no_argument, 0, 'h'},
    {"info", no_argument, 0, 'i'},
<<<<<<< HEAD
<<<<<<< HEAD
    {"background",required_argument, 0, 'b'},
=======
    {"detect",required_argument, 0, 'd'},
>>>>>>> 2bf9cde838a041c93af123dbc95fb9d8ab86ca47
=======
    {"detect", required_argument, 0, 'd'},
>>>>>>> 582089411009f0f4a9bf94b2c6318716af4aae23
    {"scan", no_argument, 0,'s'}, //인자값 필요로 한다면 no_argument -> required_argument
    {"ps", no_argument, 0, 'p'},
    {0,0,0,0}
};

void scan(){
    cout << " " << endl;
}

void error();

void help();

<<<<<<< HEAD
<<<<<<< HEAD
void error(){
    cout << "error" << endl;
}


int logic1(){
    DIR* dir;
    struct dirent *entry;

    dir = opendir("/proc");

    while((entry = readdir(dir)) != nullptr){
        string path = "/proc/" + string(entry->d_name);
        
        if (entry->d_type == DT_DIR && string(entry->d_name).find_first_not_of("0123456789") == string::npos){
            string comm_path = path+"/comm";
            ifstream comm_file(comm_path);
            string process_name;

            if (comm_file >> process_name){
                cout << "process ID : " << entry->d_name << " process Name : " << process_name << endl;
            }
            comm_file.close();
        }

    }
    closedir(dir);
    
    return 0;
}

int logic2(){
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
    {
        cout << "don't trace me !!"  << endl;
=======
=======
void info();
>>>>>>> 582089411009f0f4a9bf94b2c6318716af4aae23

int logic1(){
    cout << "logic1" << endl;
    return 0;
}

int self(void){
<<<<<<< HEAD
    if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
        cout << "No debugging please" << endl;
        cout << "This will exit gdb now." << endl;
        sleep(2);
        exit(1);
>>>>>>> 2bf9cde838a041c93af123dbc95fb9d8ab86ca47
        return 1;
    }
=======
>>>>>>> 582089411009f0f4a9bf94b2c6318716af4aae23
    return 0;
}

<<<<<<< HEAD
void background(char* argv){

    if(strcmp(argv, "logic")==0){
        logic1();
    }
    // while (1){
    //     cout << "Anti-debugging Logic Running…" << endl;

    //     logic1();
    //     // logic2();
    //     sleep(1);

    // }

    


}
=======
void detect(char* argv){
    if(strcmp(argv, "logic1") == 0){
        logic1();
    } else if(strcmp(argv, "self") == 0){
        self();
    }
}
<<<<<<< HEAD
>>>>>>> 2bf9cde838a041c93af123dbc95fb9d8ab86ca47
=======
>>>>>>> 582089411009f0f4a9bf94b2c6318716af4aae23
