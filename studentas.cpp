#include "studentas.h"

#include <iomanip>
#include <ostream>
#include <sstream>
#include <utility>

studentas::studentas(std::istream& is) : egzaminas_(0)
{
    skaityti_studenta(is);
}

studentas::studentas(const studentas& other) = default;
studentas& studentas::operator=(const studentas& other) = default;
studentas::~studentas() = default;

void studentas::spausdinti(std::ostream& out, int pasirinkimas) const
{
    out << std::left << std::setw(13) << vardas() << std::setw(15) << pavarde() << std::fixed << std::setprecision(2);

    if (pasirinkimas == 1)
        out << std::setw(20) << galutinis(vidurkis);
    else if (pasirinkimas == 2)
        out << std::setw(20) << galutinis(mediana);
    else
        out << std::setw(20) << galutinis(vidurkis) << std::setw(20) << galutinis(mediana);
}

double studentas::galutinis(double (*skaiciuoti)(std::vector<double>)) const
{
    return 0.4 * skaiciuoti(nd_) + 0.6 * egzaminas_;
}

std::istream& studentas::skaityti_studenta(std::istream& is)
{
    std::string eilute;
    if (!std::getline(is, eilute))
        return is;

    std::istringstream eilutesSrautas(eilute);

    std::string vardasNaujas;
    std::string pavardeNauja;
    std::vector<double> pazymiai;
    double pazymys;

    if (!(eilutesSrautas >> vardasNaujas >> pavardeNauja)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    while (eilutesSrautas >> pazymys)
        pazymiai.push_back(pazymys);

    if (!eilutesSrautas.eof() || pazymiai.size() < 2) {
        is.setstate(std::ios::failbit);
        return is;
    }

    vardas(vardasNaujas);
    pavarde(pavardeNauja);

    egzaminas_ = pazymiai.back();
    pazymiai.pop_back();
    nd_ = std::move(pazymiai);

    return is;
}

std::istream& operator>>(std::istream& is, studentas& s)
{
    return s.skaityti_studenta(is);
}

std::ostream& operator<<(std::ostream& out, const studentas& s)
{
    out << s.vardas() << ' ' << s.pavarde();

    for (double pazymys : s.nd_)
        out << ' ' << pazymys;

    return out << ' ' << s.egzaminas_;
}