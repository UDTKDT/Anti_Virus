#include <iostream>
#include <sys/ptrace.h>
#include <getopt.h>
#include "main.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <filesystem>
#include <string>
#include <fstream>
#include <dirent.h>
#include "scan.h"

#include "scan.h"

#include "scan.h"

using namespace std;

void CheckOpt(int &argc, char** &argv){
    int optionIndex= 0;
    int opt;
<<<<<<< HEAD
<<<<<<< HEAD
    const char* option="hib:s"; //인자값 필요로 한다면 :붙이기 ex) hib:s:
=======
    const char* option="hid:s"; //인자값 필요로 한다면 :붙이기 ex) hib:s:
>>>>>>> 2bf9cde838a041c93af123dbc95fb9d8ab86ca47
=======
    const char* option="hid:sp"; //인자값 필요로 한다면 :붙이기 ex) hib:s:
>>>>>>> 582089411009f0f4a9bf94b2c6318716af4aae23

    while((opt = getopt_long(argc, argv, option, options, &optionIndex)) != -1 ){
        switch(opt){
            case 'h':
                help(); 
                break;

            case 'i':
                info();
                break;
<<<<<<< HEAD

<<<<<<< HEAD
            case 'b':
                background(argv[2]);
=======
            case 'd':
                detect(argv[2]);
>>>>>>> 2bf9cde838a041c93af123dbc95fb9d8ab86ca47
                break;
=======
>>>>>>> 582089411009f0f4a9bf94b2c6318716af4aae23
            
            case 's':
                scan();
                break;

            case 'd':
                detect(optarg);
                break;

            case 'p':
                process();
                break;

            case '?':
                error();
                break;

            default:
                abort();
        }
    }

}

int main(int argc, char **argv){

<<<<<<< HEAD
<<<<<<< HEAD
=======
    if(self()){
        return 1;
    }
>>>>>>> 2bf9cde838a041c93af123dbc95fb9d8ab86ca47

=======
>>>>>>> 582089411009f0f4a9bf94b2c6318716af4aae23
    //옵션 값 확인
    if (argc > 1) 
        CheckOpt(argc, argv);
    else
        cout << "Try 'UdkdAgent --help' for more information." << endl;

    return 0;
}