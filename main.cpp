#include <iostream>
#include <fstream>
#include <string>

bool arZodzioDalis(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || 
           std::isdigit(static_cast<unsigned char>(c)) || 
           c == '-' || c == '_';
}

int main() {
    std::string ivestiesFailas;

    std::cout << "Įveskite įvesties .txt failo pavadinimą: ";
    std::getline(std::cin, ivestiesFailas);

    std::ifstream ivestiesSrautas(ivestiesFailas + ".txt");
    if (!ivestiesSrautas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << std::endl;
        return 1;
    }

    std::cout << "Failas sėkmingai atidarytas." << std::endl;

    ivestiesSrautas.close();
    return 0;
}
