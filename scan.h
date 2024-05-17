#ifndef SCAN_H
#define SCAN_H

#include <string>
#include <vector>
#include <fts.h>
#include <yara.h>

using namespace std;

struct UserData {
    vector<string>* detectedMalware;
    const string* filePath;
};

void scan();
void scanDirectory(const string& path, int option);
void compareByHash(FTSENT *node, vector<string>& detectedMalware, vector<string>& hashes);
vector<string> loadHashes(const string& filename);
string computeSHA256(const string& filename);
void checkYaraRule(const string& filePath, vector<string>& detectedMalware);
int yaraCallbackFunction(YR_SCAN_CONTEXT* context, int message, void* message_data, void* user_data);

#endif