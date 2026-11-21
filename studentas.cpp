#include "studentas.h"

#include <sstream>
#include <utility>

studentas::studentas(std::istream& is) : egzaminas_(0)
{
    skaityti_studenta(is);
}

studentas::studentas(const studentas& other) = default;
studentas& studentas::operator=(const studentas& other) = default;
studentas::~studentas() = default;

double studentas::galutinis(
    double (*skaiciuoti)(std::vector<double>)
) const
{
    return 0.4 * skaiciuoti(nd_) + 0.6 * egzaminas_;
}

std::istream& studentas::skaityti_studenta(std::istream& is)
{
    std::string eilute;
    if (!std::getline(is, eilute))
        return is;

    std::istringstream eilutesSrautas(eilute);
    std::string vardas;
    std::string pavarde;

    if (!(eilutesSrautas >> vardas >> pavarde)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::vector<double> pazymiai;
    double pazymys;
    while (eilutesSrautas >> pazymys)
        pazymiai.push_back(pazymys);

    if (!eilutesSrautas.eof() || pazymiai.size() < 2) {
        is.setstate(std::ios::failbit);
        return is;
    }

    vardas_ = std::move(vardas);
    pavarde_ = std::move(pavarde);
    egzaminas_ = pazymiai.back();
    pazymiai.pop_back();
    nd_ = std::move(pazymiai);

    return is;
}

std::istream& operator>>(std::istream& is, studentas& s)
{
    return s.skaityti_studenta(is);
}

std::ostream& operator<<(std::ostream& os, const studentas& s)
{
    os << s.vardas_ << ' ' << s.pavarde_;

    for (double pazymys : s.nd_)
        os << ' ' << pazymys;

    return os << ' ' << s.egzaminas_;
}