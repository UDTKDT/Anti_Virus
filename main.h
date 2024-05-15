#include <getopt.h>
#include <iostream>
#include <cstring>
#include <sys/ptrace.h>
#include <chrono>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <unistd.h>

using namespace std;

//pr test test2
struct option options[]={
    {"help", no_argument, 0, 'h'},
    {"info", no_argument, 0, 'i'},
    {"background",required_argument, 0, 'b'},
    {"scan", no_argument, 0,'s'}, //인자값 필요로 한다면 no_argument -> required_argument
    {0,0,0,0}
};

void scan(){
    cout << "이 프로그램은 .. " << endl;
}

void help(){
    cout << "Usage: ./UdkdAgent [OPTIONS]" << endl;
    cout << " " << endl;
    cout << "Options: " << endl;
    cout << "  -i, --info               Print detailed information about the Agent." << endl;
    cout << "  -d, --detect             Activate the anti-debugging protection. Use this feature to safeguard sensitive code from being analyzed or tampered with by external debugging." << endl;
    cout << "  -s, --scan [path]        Scan files in the specified directory. Default is '/' if no path is provided." << endl; 
}

void info(){
    cout << "Program Information" << endl;
    cout << "=====================================================================" << endl;
    cout << "Name: UdkdAgent" << endl;
    cout << "Version: " << endl;
    cout << "Release Date: " << endl;
    cout << " " << endl;
    cout << "Description: UdkdAgent is designed to enhance system protection through anti-debugging and malware detection techniques." << endl;
    cout << " " << endl;
    cout << "Key Features include: " << endl;
    cout << "    - Malware Scanning: Eliminates potential threats before they can cause harm." << endl;
    cout << "    - Anti-Debugging: Protects sensitive code from being analyzed or manipulated by unauthorized debuggers." << endl;
    cout << " " << endl;
    cout << "This tool is essential for maintaining optimal security in vulnerable or targeted environments, providing users with peace of mind through defensive capabilities." << endl;
}

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
        return 1;
    }

    cout << "normal execution" << endl;
    return 0;
}

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
