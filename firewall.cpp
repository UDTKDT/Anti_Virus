//g++ -o UdkdAgent firewall.* main.* error_codes.*

#include "firewall.h"

mINI::INIFile file("rules.ini");
mINI::INIStructure ini;

int Firewall() {
    int option=0;

    std::cout <<
        "Select Firewall Option \n\n"
        "1. Start Firewall \n"
        "2. Configure Firewall \n"
        "3. View Logs \n\n"
        "Please enter the option : ";

    std::cin >> option;
    std::cin.ignore();
    std::cout << std::endl;
    
    switch(option){
        case 1:
            StartFirewall();
            break;
        
        case 2:
            ConfigureFirewall();
            break;
        
        case 3:
            ViewLogs();
            break;

        default:
            std::cout << "Error : " << GetErrorMessage(ERROR_INVALID_OPTION) << std::endl;
            exit(ERROR_INVALID_OPTION);
            break;
    }

    return 0;
}

int StartFirewall(){

}

int ConfigureFirewall(){
    //이걸 help로 뺄지, 수정해서 간단하게 한 다음 기본으로 출력할지
    std::cout << 
        "If you want to ADD a new rule \n"
        "[A/add] [TO/FROM] [IP] [PORT] [o/x] \n\n"
        "If you want to UPDATE an existing rule \n"
        "[U/update] [Rule Number] [OPTION] > [Change value] \n\n"
        "If you want to DELETE a rule \n"
        "[D/delete] [Rule Number] \n\n"
        "[L/list] : View Firewall Rules \n\n" ;
    
    std::unordered_map<std::string, std::function<int(std::vector<std::string>&)>> command_map = {
        {"A", AddRule},
        {"add", AddRule},
        {"U", UpdateRule},
        {"update", UpdateRule},
        {"D", DeleteRule},
        {"delete", DeleteRule},
        {"L", RuleList},
        {"list", RuleList}
    };


    while (true){
        std::cout << "COMMAND : ";
        std::string input;
        std::getline(std::cin, input);
        std::cout << std::endl;

        if(input.empty()){
            //에러
            std::cout << "input error" << std::endl;
            exit(1);
        }

        //루프 종료하는 더 좋은 방법 구상해보기
        if (input =="EXIT") {
            break;
        }
        
        std::istringstream iss(input);
        std::vector<std::string> words;
        std::string word;

        // words에 추가하기 전에 소문자로 바꾸는 로직 추가하기
        // 로직 추가 후 비교할 때 소문자로만 비교하기

        while(iss >> word){
            words.push_back(word);
        }


        auto cmd = command_map.find(words[0]);
        if (cmd != command_map.end()){
            cmd->second(words);
        }
        else{
            std::cout << "Error : " << GetErrorMessage(ERROR_INVALID_OPTION) << std::endl;
            exit(ERROR_INVALID_OPTION);
        }
    }

    return 0;
}

int AddRule(std::vector<std::string>& words){
    if (words.size() == 5 && isValidIP(words[2]) && isValidPort(words[3])){
        ;
    }
    else if (words.size()==4){
        if (isValidIP(words[2])) {
            words.emplace(words.begin()+3, "any");
        } 
        else if (isValidPort(words[2])){
            words.emplace(words.begin()+2, "any");
        } 
        else{
            //에러
            std::cout << "error1" << std::endl;
            exit(1);
        }
    }
    else {
        //에러
        std::cout << "error2" << std::endl;
        exit(1);
    }

    if (!((words[1] == "TO" || words[1] == "FROM") && (words.back() == "x" || words.back() == "o"))){
        //에러
        std::cout << "error3" << std::endl;
        exit(1);
    }
    


    // //txt 파일에 룰 추가
    // std::string filename="firewall_rules.txt";
    // std::ofstream outfile;
    // outfile.open(filename, std::ios_base::app);

    // if (!outfile.is_open()) {
    //     //에러
    //     std::cout << "error4" << std::endl;
    //     exit(1);
    // }

    // for (size_t i=1; i < words.size(); ++i){
    //     std::string& j = words[i];
    //     j = (j == "TO") ? "OUT" : (j == "FROM") ? "IN" : (j == "o") ? "PERMIT" : (j == "x") ? "DENY" :j;
    //     outfile << j << " ";
    // }
    // outfile << "\n";

    // outfile.close();

    file.read(ini);
    
    auto it = ini.begin();
    std::string lastSection;

    // Iterate through the sections
    for (; it != ini.end(); ++it) {
        lastSection = it->first;
    }
    std::cout << "Last section name: " << lastSection << std::endl;

    


    std::cout << "Rule successfully added \n" << std::endl;
    return 0;
    
}



int UpdateRule(std::vector<std::string>& words){

}



int DeleteRule(std::vector<std::string>& words){

}



int RuleList(std::vector<std::string>& words){
    VariadicTable<std::string, std::string, std::string, std::string, std::string> vt({"No", "IN/OUT", "IP Address", "PORT", "Action"}, 10);

    vt.addRow("1", "192.168.10.20","22","IN","PERMIT");
    vt.addRow("2","19","22","IN","PERMIT");

    vt.print(std::cout);

}


int ViewLogs(){
    
}


////////////////////////////////////////////////////////////////////////////////////////

bool isValidIP(const std::string& ip) {
    std::regex ipPattern("^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\."
                         "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\."
                         "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\."
                         "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$");
    return std::regex_match(ip, ipPattern);
}

bool isValidPort(const std::string& port) {
    std::regex portPattern("^(6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{0,3}|0)$");
    return std::regex_match(port, portPattern);
}