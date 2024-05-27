#pragma once

#include <unordered_map>

int StartMonitoring();
std::vector<std::string> ReadWatchList(const std::string& filePath);
void InitializeWatchList(const std::vector<std::string>& watchList);
int CreateInotifyInstance();
void AddWatchListToInotify(int inotifyFd, const std::vector<std::string>& watchList, std::unordered_map<int, std::string>& watchDescriptors);
void RunEventLoop(int inotifyFd, const std::unordered_map<int, std::string>& watchDescriptors);
void ProcessEvent(struct inotify_event *event, const std::unordered_map<int, std::string>& watchDescriptors);
void VerifyFileIntegrity(const std::string &filePath);