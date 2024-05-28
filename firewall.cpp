//g++ -o UdkdAgent firewall.* main.* error_codes.*

#include "firewall.h"


int Firewall() {
    int option=0;

    PrintFirewallOption();

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
            break;
    }

    return 0;
}


void PrintFirewallOption(){
    std::cout <<
        "Select Firewall Option \n\n"
        "1. Start Firewall \n"
        "2. Configure Firewall \n"
        "3. View Logs \n\n"
        "Please enter the option : ";
}

int StartFirewall(){

}

int ConfigureFirewall(){
    std::cout << 
        "If you want to ADD a new rule \n"
        "[A/add] [TO/FROM] [IP] [PORT] [o/x] \n\n"
        "If you want to UPDATE an existing rule \n"
        "[U/update] [Rule Number] [OPTION] > [Change value] \n\n"
        "If you want to DELETE a rule \n"
        "[D/delete] [Rule Number] \n\n"
        "[L/list] : View Firewall Rules \n\n" 
        "COMMAND : ";
    
    std::string input;
    std::getline(std::cin, input);

    //사용자 입력 파싱/////////////////
    std::istringstream iss(input);
    std::vector<std::string> words;
    std::string word;

    while(iss >> word){
        words.push_back(word);
    }
    //////////////////////////////////

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

    auto cmd = command_map.find(words[0]);
    if (cmd != command_map.end()){
        cmd->second(words);
    }
    else{
        std::cout << "error" << std::endl;
        //나중에 에러 처리 하기
    }
    
    

}

int AddRule(std::vector<std::string>& words){
    std::cout << words[0] << words[1] << words[2] << std::endl;
}



int UpdateRule(std::vector<std::string>& words){
    std::cout << words[0] << words[1] << words[2] << std::endl;

}



int DeleteRule(std::vector<std::string>& words){
    std::cout << words[0] << words[1] << words[2] << std::endl;

}




int RuleList(std::vector<std::string>& words){
    VariadicTable<std::string, std::string, std::string, std::string, std::string> vt({"No", "IP Address", "PORT", "IN/OUT", "Action"}, 10);

    // vt.addRow("1", "192.168.10.20","22","IN","PERMIT");
    // vt.addRow("2","19","22","IN","PERMIT");

    // vt.print(std::cout);

}


int ViewLogs(){
    
}