#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

bool arZodzioDalis(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || 
           std::isdigit(static_cast<unsigned char>(c)) || 
           c == '-' || c == '_';
}

std::string iMazasesRaides(const std::string& str) {
    std::string rezultatas = str;
    std::transform(rezultatas.begin(), rezultatas.end(), rezultatas.begin(), ::tolower);
    return rezultatas;
}

void apdorotiFaila(const std::string& ivestiesFailas, std::map<std::string, int>& zodziuSkaicius) {
    std::ifstream ivestiesSrautas(ivestiesFailas + ".txt");
    if (!ivestiesSrautas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << std::endl;
        return;
    }

    std::string eilute;
    while (getline(ivestiesSrautas, eilute)) {
        std::istringstream srautas(eilute);
        std::string zodis;
        while (srautas >> zodis) {
            std::string isvalytasZodis;
            for (char c : zodis) {
                if (arZodzioDalis(c)) {
                    isvalytasZodis += c;
                }
            }
            if (!isvalytasZodis.empty()) {
                isvalytasZodis = iMazasesRaides(isvalytasZodis);
                zodziuSkaicius[isvalytasZodis]++;
            }
        }
    }

    ivestiesSrautas.close();
}

int main() {
    std::string ivestiesFailas;
    std::map<std::string, int> zodziuSkaicius;

    std::cout << "Įveskite įvesties .txt failo pavadinimą: ";
    std::getline(std::cin, ivestiesFailas);

    apdorotiFaila(ivestiesFailas, zodziuSkaicius);

    for (const auto& pora : zodziuSkaicius) {
        std::cout << pora.first << ": " << pora.second << std::endl;
    }

    return 0;
}
