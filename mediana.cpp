// mediana.cpp
#include "mediana.h"

#include <algorithm>
#include <stdexcept>

double mediana(std::vector<double> pazymiai)
{
    if (pazymiai.empty()) {
        throw std::invalid_argument("Negalima apskaiciuoti medianos, nes pazymiu sarasas tuscias");
    }

    std::sort(pazymiai.begin(), pazymiai.end());

    const std::size_t vidurys = pazymiai.size() / 2;

    if (pazymiai.size() % 2 == 0) {
        return (pazymiai[vidurys - 1] + pazymiai[vidurys]) / 2.0;
    }

    return pazymiai[vidurys];
}

double vidurkis(std::vector<double> pazymiai)
{
    if (pazymiai.empty()) {
        throw std::invalid_argument("Negalima skaiciuoti vidurkio be pazymiu");
    }

    double suma = 0;
    for (double pazymys : pazymiai) {
        suma += pazymys;
    }

    return suma / pazymiai.size();
}