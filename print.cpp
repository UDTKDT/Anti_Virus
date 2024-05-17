#include <iostream>
#include <fstream>
#include <string>
#include "print.h"

using namespace std;

void error(){
    cout << "Error: Invalid option\n"
         << "For usage information, type 'UdkdAgent --help'\n";
}

void help(){
    cout << "Usage: ./UdkdAgent [OPTIONS]\n"
         << " \n"
         << "Options: \n"
         << "  -i, --info               Print detailed information about the Agent.\n"
         << "  -d, --detect             Activate the anti-debugging protection. Use this feature to safeguard sensitive code from being analyzed or tampered with by external debugging.\n"
         << "  -s, --scan [path]        Scan files in the specified directory. Default is '/' if no path is provided.\n"
         << "  -p, --ps                 Collect detailed information about a process and save it to a file. Also provides options to terminate processes.\n";
}

void info(){
    cout << "Program Information\n"
         << "=====================================================================\n"
         << "Name: UdkdAgent\n";

    ifstream file("/etc/os-release");
    string line;

    if(file.is_open()){
        while(getline(file, line)){
            if(line.substr(0, 11) == "PRETTY_NAME"){
                string version = line.substr(line.find("=") + 2, line.length() - line.find("=") - 3);
                cout << "Ubuntu Version: " << version << endl;
                break;
            }
        }
        file.close();
    } else{
        cout << "Failed to open /etc/os-release" << endl;
    }

    cout << " \n"
         << "Description: UdkdAgent is designed to enhance system protection through anti-debugging, malware detection techniques, and inspecting processes.\n"
         << " \n"
         << "Key Features include: \n"
         << "    - Malware Scanning: Eliminates potential threats before they can cause harm.\n"
         << "    - Anti-Debugging: Protects sensitive code from being analyzed or manipulated by unauthorized debuggers.\n"
         << "    - Inspect Process: Focuses on overseeing processes that use excessive resources or act unpredictably, and terminates then as needed to maintain system stability and security.\n"
         << " \n"
         << "This tool is essential for maintaining optimal security in vulnerable or targeted environments, providing users with peace of mind through defensive capabilities.\n";
}