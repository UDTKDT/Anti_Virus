#include <fstream>
#include <sys/stat.h>
#include "integrity_checker.h"
#include "util.h"

std::string CalculateFileHash(const std::string &filePath) {
    std::string fileHash;
    int result = ComputeSHA256(filePath, fileHash);
    if (result != SUCCESS_CODE) {
        HandleError(result, filePath);
    }
    return fileHash;
}

// 해시 파일이 존재하는지 확인
bool IsHashFileExists(const std::string &hashFilePath) {
    struct stat buffer;
    return (stat(hashFilePath.c_str(), &buffer) == 0);
}

std::string GetHashFileName(const std::string &filePath) {
    // 해시 파일을 저장할 디렉토리
    std::string hashDirectory = "./integrity-check-hashes";

    // 디렉토리가 없으면 생성
    if (!IsDirectory(hashDirectory)) {
        if (mkdir(hashDirectory.c_str(), 0777) != 0) {
            HandleError(ERROR_CANNOT_OPEN_DIRECTORY, hashDirectory);
        }
    }
    // 해시 파일 경로 설정
    std::string hashFilePath = hashDirectory + "/" + filePath.substr(filePath.find_last_of("/\\") + 1) + ".hash";
    return hashFilePath;

}

// 파일의 해시 값을 저장
void SaveFileHash(const std::string &filePath) {
    std::string hashFilePath = GetHashFileName(filePath);
    
    // 파일의 해시 값을 저장하는 함수 구현
    std::string hash = CalculateFileHash(filePath);
    std::ofstream hashFile(hashFilePath);
    if (!hashFile.is_open()) {
        HandleError(ERROR_CANNOT_OPEN_FILE, hashFilePath);
    }

    hashFile << hash;
    hashFile.close();
}

// 기존에 저장된 해시 값을 불러오는 함수
std::string RetrieveStoredHash(const std::string &filePath) {
    std::ifstream hashFile(GetHashFileName(filePath));
    if (!hashFile.is_open()) {
        HandleError(ERROR_CANNOT_OPEN_FILE, filePath + ".hash");
    }

    std::string storedHash;
    hashFile >> storedHash;

    hashFile.close();
    return storedHash;
}

void RemoveFileHash(const std::string &filePath) {
    std::string hashFilePath = "integrity-check-hashes/" + filePath.substr(filePath.find_last_of("/\\") + 1) + ".hash";
    if (remove(hashFilePath.c_str()) != 0) {
        HandleError(ERROR_CANNOT_REMOVE_FILE, hashFilePath);
    }
}