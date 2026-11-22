#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include "mediana.h"

#include <iostream>
#include <string>
#include <vector>

class studentas : public zmogus
{
public:
    studentas() : egzaminas_(0) {}
    explicit studentas(std::istream& is);

    studentas(const studentas& other);
    studentas& operator=(const studentas& other);
    ~studentas();

    double galutinis(double (*skaiciuoti)(std::vector<double>) = mediana) const;

    std::istream& skaityti_studenta(std::istream& is);
    void spausdinti(std::ostream& out, int pasirinkimas) const override;

    friend std::ostream& operator<<(std::ostream& out, const studentas& s);

private:
    double egzaminas_;
    std::vector<double> nd_;
};

std::istream& operator>>(std::istream& is, studentas& s);
std::ostream& operator<<(std::ostream& out, const studentas& s);

#endif