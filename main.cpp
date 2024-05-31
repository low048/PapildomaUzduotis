#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
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

void apdorotiFaila(const std::string& ivestiesFailas, std::map<std::string, int>& zodziuSkaicius, std::map<std::string, std::set<int>>& zodziuEilutes) {
    std::ifstream ivestiesSrautas(ivestiesFailas + ".txt");

    if (!ivestiesSrautas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << std::endl;
        return;
    }

    std::string eilute;
    int eilutesNumeris = 0;

    while (getline(ivestiesSrautas, eilute)) {
        ++eilutesNumeris;
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
                zodziuEilutes[isvalytasZodis].insert(eilutesNumeris);
            }
        }
    }

    ivestiesSrautas.close();
}

void isvestiZodziuSkaicius(const std::map<std::string, int>& zodziuSkaicius, const std::string& isvestiesFailas) {
    std::ofstream isvestiesSrautas(isvestiesFailas + ".txt");

    if (!isvestiesSrautas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << std::endl;
        return;
    }

    isvestiesSrautas << "Žodžiai, kurie pasikartoja daugiau nei vieną kartą:\n";
    for (const auto& pora : zodziuSkaicius) {
        if (pora.second > 1) {
            isvestiesSrautas << pora.first << ": " << pora.second << "\n";
        }
    }

    isvestiesSrautas.close();
}

void sukurtiLentele(const std::map<std::string, int>& zodziuSkaicius, const std::map<std::string, std::set<int>>& zodziuEilutes, const std::string& isvestiesFailas) {
    std::ofstream isvestiesSrautas(isvestiesFailas + ".txt");

    if (!isvestiesSrautas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << std::endl;
        return;
    }

    isvestiesSrautas << "Cross-reference lentelė žodžiams, kurie pasikartoja daugiau nei vieną kartą:\n";
    for (const auto& pora : zodziuEilutes) {
        if (zodziuSkaicius.at(pora.first) > 1) {
            isvestiesSrautas << pora.first << " pasikartoja eilutėse: ";
            for (const auto& eil : pora.second) {
                isvestiesSrautas << eil << " ";
            }
            isvestiesSrautas << "\n";
        }
    }

    isvestiesSrautas.close();
}

bool patikrintiArURL(const std::string& zodis) {
    const std::vector<std::string> domenai = { ".com", ".org", ".net", ".lt", ".edu", ".gov", ".uk", ".de", ".fr", ".it", ".ru", ".jp", ".cn" };
    if (zodis.find("http://") == 0 || zodis.find("https://") == 0 || zodis.find("www.") == 0) {
        return true;
    }
    for (const auto& domenas : domenai) {
        if (zodis.size() > domenas.size() && zodis.substr(zodis.size() - domenas.size()) == domenas) {
            return true;
        }
    }
    return false;
}

void istrauktiURL(const std::string& ivestiesFailas, const std::string& isvestiesFailas) {
    std::ifstream ivestiesSrautas(ivestiesFailas + ".txt");
    std::ofstream isvestiesSrautas(isvestiesFailas + "_urls.txt");

    if (!ivestiesSrautas.is_open() || !isvestiesSrautas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << std::endl;
        return;
    }

    std::string eilute;
    std::set<std::string> nuorodos;

    while (getline(ivestiesSrautas, eilute)) {
        std::istringstream srautas(eilute);
        std::string zodis;
        while (srautas >> zodis) {
            if (patikrintiArURL(zodis)) {
                nuorodos.insert(zodis);
            }
        }
    }

    isvestiesSrautas << "Nuorodos, rastos tekste:\n";
    for (const auto& url : nuorodos) {
        isvestiesSrautas << url << "\n";
    }

    ivestiesSrautas.close();
    isvestiesSrautas.close();
}

int main() {
    std::string ivestiesFailas;
    std::string zodziuSkaiciusIsvestiesFailas;
    std::string lentelesIsvestiesFailas;
    std::string urlIsvestiesFailas;
    std::map<std::string, int> zodziuSkaicius;
    std::map<std::string, std::set<int>> zodziuEilutes;

    std::cout << "Įveskite įvesties .txt failo pavadinimą: ";
    std::getline(std::cin, ivestiesFailas);

    std::cout << "Įveskite žodžių skaičiaus .txt failo pavadinimą: ";
    std::getline(std::cin, zodziuSkaiciusIsvestiesFailas);

    std::cout << "Įveskite cross-reference lentelės .txt failo pavadinimą: ";
    std::getline(std::cin, lentelesIsvestiesFailas);

    std::cout << "Įveskite URL išvesties .txt failo pavadinimą: ";
    std::getline(std::cin, urlIsvestiesFailas);

    apdorotiFaila(ivestiesFailas, zodziuSkaicius, zodziuEilutes);
    isvestiZodziuSkaicius(zodziuSkaicius, zodziuSkaiciusIsvestiesFailas);
    sukurtiLentele(zodziuSkaicius, zodziuEilutes, lentelesIsvestiesFailas);
    istrauktiURL(ivestiesFailas, urlIsvestiesFailas);

    return 0;
}
