#include "studentas.h"

#include <sstream>
#include <utility>

studentas::studentas(std::istream& is) : egzaminas_(0)
{
    readStudent(is);
}

double studentas::galutinis(
    double (*skaiciuoti)(std::vector<double>)
) const
{
    return 0.4 * skaiciuoti(nd_) + 0.6 * egzaminas_;
}

std::istream& studentas::readStudent(std::istream& is)
{
    std::string eilute;
    if (!std::getline(is, eilute)) {
        return is;
    }

    std::istringstream eilutesSrautas(eilute);
    if (!(eilutesSrautas >> vardas_ >> pavarde_)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::vector<double> pazymiai;
    double pazymys;
    while (eilutesSrautas >> pazymys) {
        pazymiai.push_back(pazymys);
    }

    if (pazymiai.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    egzaminas_ = pazymiai.back();
    pazymiai.pop_back();
    nd_ = std::move(pazymiai);

    return is;
}