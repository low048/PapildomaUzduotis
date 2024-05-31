#include <iostream>
#include <fstream>
#include <string>

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
