#include <iostream>
#include <ctime>

int main() {
    // Ottenere il tempo corrente
    std::time_t now = std::time(0);

    // Convertire il tempo in una struttura tm
    std::tm *ltm = std::localtime(&now);

    // Stampare la data corrente
    std::cout << "Anno corrente: " << 1900 + ltm->tm_year << std::endl;
    std::cout << "Mese corrente: " << 1 + ltm->tm_mon << std::endl;
    std::cout << "Giorno corrente: " << ltm->tm_mday << std::endl;

    return 0;
}
