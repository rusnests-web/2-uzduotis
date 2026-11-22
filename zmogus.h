#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <iostream>
#include <string>

class zmogus
{
public:
    zmogus() = default;

    zmogus(const zmogus& other) = default;
    zmogus& operator=(const zmogus& other) = default;
    virtual ~zmogus() = default;

    const std::string& vardas() const { return vardas_; }
    const std::string& pavarde() const { return pavarde_; }

    virtual void spausdinti(std::ostream& out, int pasirinkimas) const = 0;

protected:
    void vardas(const std::string& vardas) { vardas_ = vardas; }
    void pavarde(const std::string& pavarde) { pavarde_ = pavarde; }

private:
    std::string vardas_;
    std::string pavarde_;
};

#endif