#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

bool arZodzioDalis(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || std::isdigit(static_cast<unsigned char>(c));
}

std::string iMazasesRaides(const std::string& str) {
    std::string rezultatas = str;
    std::transform(rezultatas.begin(), rezultatas.end(), rezultatas.begin(), ::tolower);
    return rezultatas;
}

void apdorotiFaila(const std::string& ivestiesFailas, std::map<std::string, int>& zodziuSkaicius, std::map<std::string, std::set<int>>& zodziuEilutes) {
    std::ifstream ivestiesSrautas(ivestiesFailas);

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
    std::ofstream isvestiesSrautas(isvestiesFailas);

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
    std::ofstream isvestiesSrautas(isvestiesFailas);

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
    const std::vector<std::string> domenai = {".ac", ".ac.uk", ".ad", ".ae", ".aero", ".af", ".ag", ".ai", ".al", ".am", ".an", ".ao", ".aq", ".ar", ".arpa", ".as", ".asia", ".at", ".au", ".aw", ".ax", ".az", ".ba", ".bb", ".bd", ".be", ".bf", ".bg", ".bh", ".bi", ".biz", ".bj", ".bm", ".bn", ".bo", ".br", ".bs", ".bt", ".bv", ".bw", ".by", ".bz", ".ca", ".cat", ".cc", ".cd", ".cf", ".cg", ".ch", ".ci", ".ck", ".cl", ".cm", ".cn", ".co", ".co.uk", ".com", ".coop", ".cr", ".cs", ".cu", ".cv", ".cw", ".cx", ".cy", ".cz", ".dd", ".de", ".dj", ".dk", ".dm", ".do", ".dz", ".ec", ".edu", ".ee", ".eg", ".eh", ".er", ".es", ".et", ".eu", ".fi", ".firm", ".fj", ".fk", ".fm", ".fo", ".fr", ".fx", ".ga", ".gb", ".gd", ".ge", ".gf", ".gg", ".gh", ".gi", ".gl", ".gm", ".gn", ".gov", ".gov.uk", ".gp", ".gq", ".gr", ".gs", ".gt", ".gu", ".gw", ".gy", ".hk", ".hm", ".hn", ".hr", ".ht", ".hu", ".id", ".ie", ".il", ".im", ".in", ".info", ".int", ".io", ".iq", ".ir", ".is", ".it", ".je", ".jm", ".jo", ".jobs", ".jp", ".ke", ".kg", ".kh", ".ki", ".km", ".kn", ".kp", ".kr", ".kw", ".ky", ".kz", ".la", ".lb", ".lc", ".li", ".lk", ".lr", ".ls", ".lt", ".ltd.uk", ".lu", ".lv", ".ly", ".ma", ".mc", ".md", ".me", ".me.uk", ".mg", ".mh", ".mil", ".mk", ".ml", ".mm", ".mn", ".mo", ".mobi", ".mod.uk", ".mp", ".mq", ".mr", ".ms", ".mt", ".mu", ".museum", ".mv", ".mw", ".mx", ".my", ".mz", ".na", ".name", ".nato", ".nc", ".ne", ".net", ".net.uk", ".nf", ".ng", ".nhs.uk", ".ni", ".nl", ".no", ".nom", ".np", ".nr", ".nt", ".nu", ".nz", ".om", ".org", ".org.uk", ".pa", ".pe", ".pf", ".pg", ".ph", ".pk", ".pl", ".plc.uk", ".pm", ".pn", ".post", ".pr", ".pro", ".ps", ".pt", ".pw", ".py", ".qa", ".re", ".ro", ".rs", ".ru", ".rw", ".sa", ".sb", ".sc", ".sch.uk", ".sd", ".se", ".sg", ".sh", ".si", ".sj", ".sk", ".sl", ".sm", ".sn", ".so", ".sr", ".ss", ".st", ".store", ".su", ".sv", ".sy", ".sz", ".tc", ".td", ".tel", ".tf", ".tg", ".th", ".tj", ".tk", ".tl", ".tm", ".tn", ".to", ".tp", ".tr", ".travel", ".tt", ".tv", ".tw", ".tz", ".ua", ".ug", ".uk", ".um", ".us", ".uy", ".uz", ".va", ".vc", ".ve", ".vg", ".vi", ".vn", ".vu", ".web", ".wf", ".ws", ".xxx", ".ye", ".yt", ".yu", ".za", ".zm", ".zr", ".zw"};
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
    std::ifstream ivestiesSrautas(ivestiesFailas);
    std::ofstream isvestiesSrautas(isvestiesFailas);

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

    std::cout << "Įveskite įvesties .txt failo pavadinimą: ";
    std::getline(std::cin, ivestiesFailas);

    std::cout << "Įveskite žodžių skaičiaus .txt failo pavadinimą: ";
    std::getline(std::cin, zodziuSkaiciusIsvestiesFailas);

    std::cout << "Įveskite cross-reference lentelės .txt failo pavadinimą: ";
    std::getline(std::cin, lentelesIsvestiesFailas);

    std::cout << "Įveskite URL išvesties .txt failo pavadinimą: ";
    std::getline(std::cin, urlIsvestiesFailas);

    std::map<std::string, int> zodziuSkaicius;
    std::map<std::string, std::set<int>> zodziuEilutes;

    std::cout << "Išvedama..." << std::endl;

    apdorotiFaila(ivestiesFailas + ".txt", zodziuSkaicius, zodziuEilutes);

    isvestiZodziuSkaicius(zodziuSkaicius, zodziuSkaiciusIsvestiesFailas + ".txt");
    sukurtiLentele(zodziuSkaicius, zodziuEilutes, lentelesIsvestiesFailas + ".txt");
    istrauktiURL(ivestiesFailas + ".txt", urlIsvestiesFailas + ".txt");

    std::cout << "Failai sėkmingai išvesti.";

    std::cin.get();

    return 0;
}