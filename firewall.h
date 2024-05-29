#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <regex>

#include "error_codes.h"
#include "VariadicTable.h"
#include "ini.h"

/////////2번 옵션/////////////
int ConfigureFirewall();
int AddRule(std::vector<std::string>& words);
int UpdateRule(std::vector<std::string>& words);
int DeleteRule(std::vector<std::string>& words);
int RuleList(std::vector<std::string>& words);
bool isValidIP(const std::string& ip);
bool isValidPort(const std::string& port);
//////////////////////////




int ViewLogs();

int StartFirewall();

int Firewall();