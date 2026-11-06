#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>
#include "mediana.h"

double vidurkis(std::vector<double> pazymiai);

class studentas {
public:
    studentas() : egzaminas_(0) {}
    explicit studentas(std::istream& is);

    std::string vardas() const { return vardas_; }
    std::string pavarde() const { return pavarde_; }

    double galBalas(
        double (*skaiciuoti)(std::vector<double>) = mediana
    ) const;

    std::istream& readStudent(std::istream& is);

private:
    std::string vardas_;
    std::string pavarde_;
    double egzaminas_;
    std::vector<double> nd_;
};

bool compare(const studentas& a, const studentas& b);
bool comparePagalPavarde(const studentas& a, const studentas& b);

#endif