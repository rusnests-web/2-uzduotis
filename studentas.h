#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>

#include "mediana.h"

class studentas
{
public:
    studentas() : egzaminas_(0) {}
    explicit studentas(std::istream& is);

    studentas(const studentas& other);
    studentas& operator=(const studentas& other);
    ~studentas();

    std::string vardas() const { return vardas_; }
    std::string pavarde() const { return pavarde_; }

    double galutinis(
        double (*skaiciuoti)(std::vector<double>) = mediana
    ) const;

    std::istream& skaityti_studenta(std::istream& is);

private:
    std::string vardas_;
    std::string pavarde_;
    double egzaminas_;
    std::vector<double> nd_;
};

#endif