#include <fstream>
#include <sys/stat.h>
#include "integrity_checker.h"
#include "util.h"

CIntegrityChecker::CIntegrityChecker(const std::string& filePath) : m_filePath(filePath) {}

std::string CIntegrityChecker::CalculateFileHash() {
    std::string fileHash;
    int result = ComputeSHA256(m_filePath, fileHash);
    if (result != SUCCESS_CODE) {
        HandleError(result, m_filePath);
    }
    return fileHash;
}

std::string CIntegrityChecker::GetHashFileName() {
    // 해시 파일을 저장할 디렉토리
    std::string hashDirectory = "./integrity-check-hashes";

    // 디렉토리가 없으면 생성
    if (!IsDirectory(hashDirectory)) {
        if (mkdir(hashDirectory.c_str(), 0777) != 0) {
            HandleError(ERROR_CANNOT_OPEN_DIRECTORY, hashDirectory);
        }
    }
    // 해시 파일 경로 설정
    std::string hashFilePath = hashDirectory + "/" + m_filePath.substr(m_filePath.find_last_of("/\\") + 1) + ".hash";
    return hashFilePath;

}

// 파일의 해시 값을 저장
void CIntegrityChecker::SaveFileHash() {
    std::string hashFilePath = GetHashFileName();
    
    // 파일의 해시 값을 저장하는 함수 구현
    std::string hash = CalculateFileHash();
    std::ofstream hashFile(hashFilePath);
    if (!hashFile.is_open()) {
        HandleError(ERROR_CANNOT_OPEN_FILE, hashFilePath);
    }

    hashFile << hash;
    hashFile.close();
}

// 기존에 저장된 해시 값을 불러오는 함수
std::string CIntegrityChecker::RetrieveStoredHash() {
    std::ifstream hashFile(GetHashFileName());
    if (!hashFile.is_open()) {
        HandleError(ERROR_CANNOT_OPEN_FILE, m_filePath + ".hash");
    }

    std::string storedHash;
    hashFile >> storedHash;

    hashFile.close();
    return storedHash;
}

void CIntegrityChecker::RemoveFileHash() {
    std::string hashFilePath = GetHashFileName();
    if (remove(hashFilePath.c_str()) != 0) {
        HandleError(ERROR_CANNOT_REMOVE_FILE, hashFilePath);
    }
}