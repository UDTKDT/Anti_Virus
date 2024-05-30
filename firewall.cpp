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
    //이걸 help()로 뺄지, 기본으로 출력할지
    std::cout << 
        "\033[1;34m[ADD] \033[0m \n"
        "[A/add] [TO/FROM] [IP] [PORT] [o/x] \n\n"
        "\033[1;32m[UPDATE] \033[0m\n"
        "[U/update] [Rule Number] [OPTION] [>] [Change Value] \n\n"
        "\033[1;31m[DELETE] \033[0m\n"
        "[D/delete] [Rule Number] \n\n"
        "\033[1;33m[LIST] \033[0m\n"
        "[L/list] \n\n" ;
    
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

        //input 받은거 처리 함수 만들기
        // 1. 대소문자 구분 x
        // 2. x/o -> PERMIT/DENY
        // 3. to/from -> OUT/IN

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
    
    file.read(ini);
    
    auto it = std::prev(ini.end());
    std::string lastSection = it->first;
    std::string ruleNum = std::to_string(stoi(lastSection)+1);
    std::vector<std::string> keys = {"","Direction", "IP", "PORT", "Action"};

    ini[ruleNum];
    for (size_t i = 1; i < keys.size(); ++i) {
        std::string& j = words[i];
        j = (j == "TO") ? "OUT" : (j == "FROM") ? "IN" : (j == "o") ? "PERMIT" : (j == "x") ? "DENY" :j;
        ini[ruleNum][keys[i]] = j;
    }
    file.write(ini);

    std::cout << "Rule successfully added \n" << std::endl;
    return 0;
    
}

int UpdateRule(std::vector<std::string>& words){
    
    
    file.read(ini);
    
  
    ini[words[1]][words[2]]=words[4];
    

    file.write(ini);
    std::cout << "Rule successfully Updated" << std::endl;
}



int DeleteRule(std::vector<std::string>& words){

}



int RuleList(std::vector<std::string>& words){
    VariadicTable<std::string, std::string, std::string, std::string, std::string> vt({"No", "Direction", "IP Address", "PORT", "Action"}, 10);
    
    file.read(ini);
    //ini가 null일 경우 에러처리 코드 추가

    for (auto const& it : ini){ 
        std::vector<std::string> tmp;
        auto const& section = it.first;
        auto const& collection = it.second;
        
         for (auto const& it2 : collection){
            tmp.push_back(it2.second);
	    }
        vt.addRow(it.first,tmp[0],tmp[1],tmp[2],tmp[3]);
    }

    vt.print(std::cout);

    return 0;
}


int ViewLogs(){
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////
//private

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


