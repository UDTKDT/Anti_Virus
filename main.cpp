#include "main.h"

using namespace std;

void CheckOpt(int argc, char** argv){
    int optionIndex= 0;
    int opt;
    const char* option="hidsp"; //인자값 필요로 한다면 :붙이기 ex) hib:s:

    while((opt = getopt_long(argc, argv, option, options, &optionIndex)) != -1 ){
        switch(opt){
            case 'h':
                help(); 
                break;
            
            case 'i':
                info();
                break;

            case 's':
                scan();
                break;

            case 'd':
                detect();
                break;

            case 'p':
                showprocess();
                break;

            case '?':
                error();
                break;
            
            default:
                abort();
        }
    }
}

void help() {
    cout << "Help message" << endl;
    // 추가적인 도움말 메시지를 작성합니다.
}

void info() {
    cout << "Information message" << endl;
    // 추가적인 정보 메시지를 작성합니다.
}

void detect() {
    cout << "Detect functionality" << endl;
    // 추가적인 탐지 기능을 작성합니다.
}

void error() {
    cout << "Error message" << endl;
    // 추가적인 오류 메시지를 작성합니다.
}
void showprocess() {
    cout << "Process functionality" << endl;
    // 프로세스 관련 기능을 작성합니다.
}

int main(int argc, char **argv){

    //옵션 값 확인
    if (argc > 1) 
        CheckOpt(argc, argv);
    else
        cout << "Try 'UdkdAgent --help' for more information." << endl;
    
    return 0;
}
