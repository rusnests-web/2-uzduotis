#include "studentas.h"
#include "funkcijos.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <sstream>
#include <stdexcept>

studentas sukurti_studenta(
    const std::string& vardas,
    const std::string& pavarde,
    const std::vector<double>& nd,
    double egz)
{
    std::ostringstream eilute;
    eilute << vardas << ' ' << pavarde;

    for (double pazymys : nd) {
        eilute << ' ' << pazymys;
    }
    eilute << ' ' << egz << '\n';

    std::istringstream srautas(eilute.str());
    studentas naujas(srautas);

    if (!srautas) {
        throw std::runtime_error("Klaida: nepavyko sukurti studento");
    }

    return naujas;
}

int main()
{
    int k;
    std::vector<studentas> grupe;
    std::list<studentas> grupe_list;
    int konteineris = 1;
    std::string failo_pavadinimas;
    std::cout << "Ar norite sugeneruoti penkis atsitiktinius studentu sarasu failus arba dirbti su jau sukurtais? (t / n): ";
    std::string atsakymas1;
    std::cin >> atsakymas1;
    while (atsakymas1 != "t" && atsakymas1 != "n")
    {
        std::cout << "Klaida: neteisinga ivestis, iveskite t arba n: ";
        std::cin >> atsakymas1;
    }
    if (atsakymas1 == "t")
    {
        int analize;
        std::cout << "Pasirinkite analize: \n";
        std::cout << "1. Tik studentu dalijimo strategiju laikai (iveskite 1); \n";
        std::cout << "2. Visa programos spartos analize (iveskite 2): ";
    while (!(std::cin >> analize) || (analize != 1 && analize != 2))
    {
        std::cout << "Klaida: neteisinga ivestis, iveskite 1 arba 2: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    if (analize == 1)
        strategiju_analize();
    else
        spartos_analize();
    return 0;
    }

    else if (atsakymas1 == "n")
    {
        std::cout << "Ar norite skaityti studentu duomenis is failo? (t / n): ";
        std::string atsakymas2;
        std::cin >> atsakymas2;
        while (atsakymas2 != "t" && atsakymas2 != "n")
        {
            std::cout << "Klaida: neteisinga ivestis, iveskite t arba n: ";
            std::cin >> atsakymas2;
        }
        if (atsakymas2 == "t")
        {
            try
            {
                failo_skaitymas(grupe, failo_pavadinimas);
            }
            catch (const std::exception &e)
            {
                std::cout << e.what();
                return 1;
            }
            std::sort(grupe.begin(), grupe.end(), [](const studentas& a, const studentas& b)
            {
                if (a.vardas() != b.vardas())
                    return a.vardas() < b.vardas();
                return a.pavarde() < b.pavarde();
            });

        }
        else if (atsakymas2 == "n")
        {
            std::cout << "Pasirinkite konteineri: \n";
            std::cout << "1. Vector (iveskite 1); \n";
            std::cout << "2. List (iveskite 2): ";
            while (!(std::cin >> konteineris) || (konteineris != 1 && konteineris != 2))
            {
                std::cout << "Klaida: neteisinga ivestis, iveskite 1 (Vector) arba 2 (List): ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            std::cout << "Ar zinomas studentu skaicius sarase? (t / n): ";
            std::string atsakymas3;
            std::cin >> atsakymas3;
            while (atsakymas3 != "t" && atsakymas3 != "n")
            {
                std::cout << "Klaida: neteisinga ivestis, iveskite t arba n: ";
                std::cin >> atsakymas3;
            }
            if (atsakymas3 == "t")
            {
                std::cout << "Iveskite studentu skaiciu sarase: ";
                int n;
                while (!(std::cin >> n) || n <= 0) 
                {
                    std::cout << "Klaida: studentu skaicius turi buti skaicius, didesnis uz 0. Iveskite studentu skaiciu sarase: ";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                for (int j = 0; j < n; j++)
                {
                    std::string vardas;
                    std::string pavarde;
                    std::vector<double> nd;
                    std::cout << "Iveskite per tarpa studento varda ir pavarde: ";
                    std::cin >> vardas >> pavarde;
                    std::cout << "Iveskite semestro namu darbu pazymiu kieki: ";
                    while (!(std::cin >> k) || k <= 0) 
                    {
                        std::cout << "Klaida: pazymiu kiekis turi buti skaicius, didesnis uz 0. Iveskite pazymiu kieki: ";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    std::cout << "Ar norite sugeneruoti atsitiktinius namu darbu ir egzamino pazymius? (t / n): ";
                    std::string atsakymas4;
                    std::cin >> atsakymas4;
                    while (atsakymas4 != "t" && atsakymas4 != "n")
                    {
                        std::cout << "Klaida: neteisinga ivestis, iveskite t arba n: ";
                        std::cin >> atsakymas4;
                    }
                    if (atsakymas4 == "n")
                    {
                        for (int i = 0; i < k; i++)
                        {
                            double pazymys;
                            std::cout << "Iveskite " << i + 1 << " pazymi: ";
                            while (!(std::cin >> pazymys) || pazymys < 1 || pazymys > 10) 
                            {
                                std::cout << "Klaida: netaisyklingi duomenys, iveskite " << i + 1 << " pazymi (skaiciu nuo 1 iki 10): ";
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                            }
                            nd.push_back(pazymys);
                        }
                        double egz;
                        std::cout << "Iveskite egzamino pazymi: ";
                        while (!(std::cin >> egz) || egz < 1 || egz > 10) 
                            {
                                std::cout << "Klaida: netaisyklingi duomenys, iveskite egzamino pazymi (skaiciu): ";
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                            }
                        studentas naujas = sukurti_studenta(vardas, pavarde, nd, egz);
                        if (konteineris == 1)
                            grupe.push_back(naujas);
                        else
                            grupe_list.push_back(naujas);
                    }
                    else if (atsakymas4 == "t")
                    {
                        for (int i = 0; i < k; i++)
                        {
                            nd.push_back(rand() % 10 + 1);
                        }
                        double egz = rand() % 10 + 1;
                        std::cout <<"Sugeneruoti namu darbu pazymiai: ";
                        for (int paz : nd) std::cout << paz << " ";
                        std::cout << "\n";
                        std::cout <<"Sugeneruotas egzamino pazymys: " << egz << "\n";
                        studentas naujas = sukurti_studenta(vardas, pavarde, nd, egz);
                        if (konteineris == 1)
                            grupe.push_back(naujas);
                        else
                            grupe_list.push_back(naujas);
                    }
                }
            }
            else if (atsakymas3 == "n")
            {
                while (true)
                {
                    std::string vardas;
                    std::string pavarde;
                    std::vector<double> nd;
                    std::cout << "Iveskite per tarpa studento varda ir pavarde (arba iveskite q, jei norite baigti): ";
                    std::cin >> vardas;
                    if (vardas == "q") break;
                    std::cin >> pavarde;
                    std::cout << "Iveskite semestro namu darbu pazymiu kieki: ";
                    while (!(std::cin >> k) || k <= 0) 
                    {
                        std::cout << "Klaida: pazymiu kiekis turi buti skaicius, didesnis uz 0. Iveskite pazymiu kieki: ";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    std::cout << "Ar norite sugeneruoti atsitiktinius namu darbu ir egzamino pazymius? (t / n): ";
                    std::string atsakymas4;
                    std::cin >> atsakymas4;
                    while (atsakymas4 != "t" && atsakymas4 != "n")
                    {
                        std::cout << "Klaida: neteisinga ivestis, iveskite t arba n: ";
                        std::cin >> atsakymas4;
                    }
                    if (atsakymas4 == "n")
                    {
                        for (int i = 0; i < k; i++)
                        {
                            std::cout << "Iveskite " << i + 1 << " pazymi: ";
                            int a;
                            while (!(std::cin >> a) || a < 1 || a > 10) 
                            {
                                std::cout << "Klaida: netaisyklingi duomenys, iveskite " << i + 1 << " pazymi (skaiciu): ";
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                            }
                            nd.push_back(a);
                        }
                        std::cout << "Iveskite egzamino pazymi: ";
                        double egz;
                        while (!(std::cin >> egz) || egz < 1 || egz > 10) 
                            {
                                std::cout << "Klaida: netaisyklingi duomenys, iveskite egzamino pazymi (skaiciu): ";
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                            }
                        studentas naujas = sukurti_studenta(vardas, pavarde, nd, egz);
                        if (konteineris == 1)
                            grupe.push_back(naujas);
                        else
                            grupe_list.push_back(naujas);
                    }
                    else if (atsakymas4 == "t")
                    {
                        for (int i = 0; i < k; i++)
                        {
                            nd.push_back(rand() % 10 + 1);
                        }
                        double egz = rand() % 10 + 1;
                        std::cout <<"Sugeneruoti namu darbu pazymiai: ";
                        for (int paz : nd) std::cout << paz << " ";
                        std::cout << "\n";
                        std::cout <<"Sugeneruotas egzamino pazymys: ";
                        std::cout << egz << "\n";
                        studentas naujas = sukurti_studenta(vardas, pavarde, nd, egz);
                        if (konteineris == 1)
                            grupe.push_back(naujas);
                        else
                            grupe_list.push_back(naujas);
                    }
                }
            }
        }
    }
    std::cout << "Pasirinkite galutinio balo skaiciavimo buda: \n";
    std::cout << "1. Pagal namu darbu pazymiu vidurki (iveskite 1); \n";
    std::cout << "2. Pagal namu darbu pazymiu mediana (iveskite 2); \n";
    std::cout << "3. Pagal abu (iveskite 3): ";
    int pasirinkimas;
    while (!(std::cin >> pasirinkimas) || (pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3))
    {
        std::cout << "Klaida: neteisinga ivestis, iveskite 1, 2 arba 3: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cout << "Studentu duomenys (" << (konteineris == 2 ? "List" : "Vector") << "): \n";
    if (pasirinkimas == 1)
    {
        std::cout << std::left << std::setw(13) << "Vardas" << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(20) << "Galutinis (Vid.)" << std::left << std::setw(20) << "Objekto adresas" << "\n";
        std::cout << std::string(68, '-') << "\n";
    }
    else if (pasirinkimas == 2)
    {
        std::cout << std::left << std::setw(13) << "Vardas" << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(20) << "Galutinis (Med.)" << std::left << std::setw(20) << "Objekto adresas" << "\n";
        std::cout << std::string(68, '-') << "\n";
    }
    else if (pasirinkimas == 3)
    {
        std::cout << std::left << std::setw(13) << "Vardas" << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(20) << "Galutinis (Vid.)" << std::left << std::setw(20) << "Galutinis (Med.)" << std::left << std::setw(20) << "Objekto adresas" << "\n";
        std::cout << std::string(88, '-') << "\n";
    }
    if (konteineris == 2)
    {
        for (studentas &B : grupe_list) printas(B, pasirinkimas);
    }
    else
    {
        for (studentas &B : grupe) printas(B, pasirinkimas);
    }
}