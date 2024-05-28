#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <functional>

#include "error_codes.h"
#include "VariadicTable.h"


//////////////////////////
int ConfigureFirewall();
int AddRule(std::vector<std::string>& words);
int UpdateRule(std::vector<std::string>& words);
int DeleteRule(std::vector<std::string>& words);
int RuleList(std::vector<std::string>& words);
//////////////////////////


void PrintFirewallOption();

int ViewLogs();

int StartFirewall();



int Firewall();