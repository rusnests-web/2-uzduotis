#include "studentas.h"
#include "funkcijos.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

void printas(studentas &A, int pasirinkimas)
{
    if (pasirinkimas == 1)
    {
        std::cout << std::left << std::setw(13) << A.vardas << std::left << std::setw(15) << A.pavarde << std::left << std::setw(20) << std::fixed << std::setprecision(2) << A.galutinisVid << std::left << std::setw(20) << &A << "\n";
    }
    else if (pasirinkimas == 2)
    {
        std::cout << std::left << std::setw(13) << A.vardas << std::left << std::setw(15) << A.pavarde << std::left << std::setw(20) << std::fixed << std::setprecision(2) << A.galutinisMed << std::left << std::setw(20) << &A << "\n";
    }
    else if (pasirinkimas == 3)
    {
        std::cout << std::left << std::setw(13) << A.vardas << std::left << std::setw(15) << A.pavarde << std::left << std::setw(20) << std::fixed << std::setprecision(2) << A.galutinisVid << std::left << std::setw(20) << A.galutinisMed << std::left << std::setw(20) << &A << "\n";
    }
}

void failo_skaitymas(std::vector<studentas> &grupe, string &failo_pavadinimas)
{
    std::ifstream failas;
    while (!failas.is_open())
    {
        if (failo_pavadinimas.empty())
        {
            std::cout << "Iveskite failo pavadinima: ";
            if (!(std::cin >> failo_pavadinimas))
            {
                throw std::runtime_error("Klaida: nepavyko nuskaityti failo pavadinimo");
            }
        }
        failas.clear();
        failas.open(failo_pavadinimas);
        if (!failas.is_open())
        {
            std::cout << "Klaida: failas '" << failo_pavadinimas << "' nerastas arba jo nepavyko atidaryti\n";
            failo_pavadinimas.clear();
        }
    }
    std::string eilute;
    if (!std::getline(failas, eilute))
    {
        return;
    }

    int nd_kiekis = 0;
    std::string zodis;
    std::istringstream antraste(eilute);
    while (antraste >> zodis)
    {
        if (zodis.size() > 2 && zodis[0] == 'N' && zodis[1] == 'D')
        {
            nd_kiekis++;
        }
    }

    while (std::getline(failas, eilute))
    {
        std::istringstream eilutes_srautas(eilute);
        studentas A{};
        if (!(eilutes_srautas >> A.vardas))
        {
            continue;
        }
        if (!(eilutes_srautas >> A.pavarde))
        {
            throw std::runtime_error("Klaida: netaisyklingi studento duomenys faile");
        }

        A.nd.reserve(nd_kiekis);
        A.suma = 0;
        for (int i = 0; i < nd_kiekis; i++)
        {
            int paz;
            if (!(eilutes_srautas >> paz))
            {
                throw std::runtime_error("Klaida: netaisyklingi namu darbu pazymiu duomenys faile");
            }
            A.nd.push_back(paz);
            A.suma += paz;
        }
        if (!(eilutes_srautas >> A.egz))
        {
            throw std::runtime_error("Klaida: netaisyklingi egzamino pazymio duomenys faile");
        }

        int k = A.nd.size();
        if (k > 0)
        {
            A.vidurkis = A.suma / k;
            std::sort(A.nd.begin(), A.nd.end());
            if (k % 2 == 0)
                A.mediana = (A.nd[k / 2 - 1] + A.nd[k / 2]) / 2.0;
            else
                A.mediana = A.nd[k / 2];
        }
        A.galutinisVid = 0.4 * A.vidurkis + 0.6 * A.egz;
        A.galutinisMed = 0.4 * A.mediana + 0.6 * A.egz;
        grupe.push_back(A);
    }
}

void failo_skaitymas(std::list<studentas> &grupe, std::string &failo_pavadinimas)
{
    std::ifstream failas;
    while (!failas.is_open())
    {
        if (failo_pavadinimas.empty())
        {
            std::cout << "Iveskite failo pavadinima: ";
            if (!(std::cin >> failo_pavadinimas))
            {
                throw std::runtime_error("Klaida: nepavyko nuskaityti failo pavadinimo");
            }
        }
        failas.clear();
        failas.open(failo_pavadinimas);
        if (!failas.is_open())
        {
            std::cout << "Klaida: failas '" << failo_pavadinimas << "' nerastas arba jo nepavyko atidaryti\n";
            failo_pavadinimas.clear();
        }
    }
    std::string eilute;
    if (!std::getline(failas, eilute))
    {
        return;
    }

    int nd_kiekis = 0;
    std::string zodis;
    std::istringstream antraste(eilute);
    while (antraste >> zodis)
    {
        if (zodis.size() > 2 && zodis[0] == 'N' && zodis[1] == 'D')
        {
            nd_kiekis++;
        }
    }

    while (std::getline(failas, eilute))
    {
        std::istringstream eilutes_srautas(eilute);
        studentas A{};
        if (!(eilutes_srautas >> A.vardas))
        {
            continue;
        }
        if (!(eilutes_srautas >> A.pavarde))
        {
            throw std::runtime_error("Klaida: netaisyklingi studento duomenys faile");
        }

        A.nd.reserve(nd_kiekis);
        A.suma = 0;
        for (int i = 0; i < nd_kiekis; i++)
        {
            int paz;
            if (!(eilutes_srautas >> paz))
            {
                throw std::runtime_error("Klaida: netaisyklingi namu darbu pazymiu duomenys faile");
            }
            A.nd.push_back(paz);
            A.suma += paz;
        }
        if (!(eilutes_srautas >> A.egz))
        {
            throw std::runtime_error("Klaida: netaisyklingi egzamino pazymio duomenys faile");
        }

        int k = A.nd.size();
        if (k > 0)
        {
            A.vidurkis = A.suma / k;
            std::sort(A.nd.begin(), A.nd.end());
            if (k % 2 == 0)
                A.mediana = (A.nd[k / 2 - 1] + A.nd[k / 2]) / 2.0;
            else
                A.mediana = A.nd[k / 2];
        }
        A.galutinisVid = 0.4 * A.vidurkis + 0.6 * A.egz;
        A.galutinisMed = 0.4 * A.mediana + 0.6 * A.egz;
        grupe.push_back(A);
    }
}

void failu_generavimas(const string& failo_pavadinimas, size_t studentu_skaicius, size_t nd_kiekis)
{
    std::ofstream failas(failo_pavadinimas);
    if (!failas.is_open()) {
        std::cerr << "Klaida kuriant faila: " << failo_pavadinimas << "\n";
        return;
    }
    std::random_device seed;
    std::mt19937 rng(seed());
    std::uniform_int_distribution<int> pazDist(1, 10);
    failas << "Vardas Pavarde ";
    for (int j = 1; j <= nd_kiekis; ++j) {
        failas << "ND" << j << " ";
    }
    failas << "Egz.\n";
    for (size_t i = 1; i <= studentu_skaicius; ++i) {
        failas << "Vardas" << i << " " << "Pavarde" << i << " ";
        for (int j = 0; j < nd_kiekis; ++j) {
            failas << pazDist(rng) << " ";
        }
        failas << pazDist(rng) << "\n";
    }
    failas.close();
}

void spartos_analize()
{
    std::vector<size_t> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    std::random_device seed;
    std::mt19937 rng(seed());
    std::uniform_int_distribution<int> ndDist(7, 20);
    for (size_t dydis : dydziai) {
        std::string failo_pavadinimas = "studentai_" + std::to_string(dydis) + ".txt";
        std::ifstream dabartinis_failas(failo_pavadinimas);
        bool failas_egzistuoja = dabartinis_failas.is_open();
        dabartinis_failas.close();
        if (failas_egzistuoja)
        {
            std::cout << "Failas " << failo_pavadinimas << " jau egzistuoja; naudojamas esamas failas.\n";
        }
        else
        {
            int nd_kiekis = ndDist(rng);
            auto pradzia = std::chrono::high_resolution_clock::now();
            failu_generavimas(failo_pavadinimas, dydis, nd_kiekis);
            auto pabaiga = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_generavimo = pabaiga - pradzia;
            std::cout << dydis << " irasu failo (" << nd_kiekis << " ND) sukurimo laikas: " << std::fixed << std::setprecision(6) << t_generavimo.count() << "\n";
        }
    }
    int pasirinkimas = 1;
    std::cout << "Pasirinkite isvedimo failu duomenu rikiavimo parametra: \n";
    std::cout << "1. Pagal varda (iveskite 1); \n";
    std::cout << "2. Pagal pavarde (iveskite 2); \n";
    std::cout << "3. Pagal galutini (Vid.) (iveskite 3); \n";
    std::cout << "4. pagal galutini (Med.) (iveskite 4): ";
    std::cin >> pasirinkimas;
    if (pasirinkimas < 1 || pasirinkimas > 4)
    {
        pasirinkimas = 1;
    }
    for (size_t dydis : dydziai) {
        std::string failo_pavadinimas = "studentai_" + std::to_string(dydis) + ".txt";
        {
            std::vector<studentas> grupe;
            std::vector<studentas> vargsiukai;
            std::vector<studentas> kietiakai;
            std::string varg = "vargsiukai_" + std::to_string(dydis) + ".txt";
            std::string kiet = "kietiakai_" + std::to_string(dydis) + ".txt";
            auto t1 = std::chrono::high_resolution_clock::now();
            failo_skaitymas(grupe, failo_pavadinimas);
            auto t2 = std::chrono::high_resolution_clock::now(); 
            std::chrono::duration<double> t_skaitymo = t2 - t1;
            std::cout << dydis << " irasu failo skaitymo laikas (Vector): " << std::fixed << std::setprecision(6) << t_skaitymo.count() << "\n";
            auto t3 = std::chrono::high_resolution_clock::now();
            studentu_rusiavimas(grupe, vargsiukai, kietiakai);
            auto t4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_dalijimo = t4 - t3;
            std::cout << dydis << " irasu failo dalijimo i dvi grupes laikas (Vector): " << std::fixed << std::setprecision(6) << t_dalijimo.count() << "\n";
            auto t5 = std::chrono::high_resolution_clock::now();
            isvedimo_rusiavimas(vargsiukai, pasirinkimas);
            isvedimo_rusiavimas(kietiakai, pasirinkimas);
            auto t6 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_rusiavimo = t6 - t5;
            std::cout << dydis << " irasu failo rusiavimo didejimo tvarka su sort funkcija laikas (Vector): " << std::fixed << std::setprecision(6) << t_rusiavimo.count() << "\n";
            auto t7 = std::chrono::high_resolution_clock::now();
            studentu_isvedimas(varg, vargsiukai);
            auto t8 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_vargsiuku = t8 - t7;
            std::cout << dydis << " irasu vargsiuku isvedimo laikas (Vector): " << std::fixed << std::setprecision(6) << t_vargsiuku.count() << "\n";
            auto t9 = std::chrono::high_resolution_clock::now();
            studentu_isvedimas(kiet, kietiakai);
            auto t10 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_kietiaku = t10 - t9;
            std::cout << dydis << " irasu kietiaku isvedimo laikas (Vector): " << std::fixed << std::setprecision(6) << t_kietiaku.count() << "\n";
            std::chrono::duration<double> is_viso = t_skaitymo + t_dalijimo + t_rusiavimo + t_vargsiuku + t_kietiaku;
            std::cout << dydis << " irasu testo laikas (Vector): " << std::fixed << std::setprecision(6) << is_viso.count() << "\n";
        }

        {
            std::list<studentas> grupe;
            std::list<studentas> vargsiukai;
            std::list<studentas> kietiakai;
            std::string varg = "vargsiukai_" + std::to_string(dydis) + ".txt";
            std::string kiet = "kietiakai_" + std::to_string(dydis) + ".txt";
            auto t1 = std::chrono::high_resolution_clock::now();
            failo_skaitymas(grupe, failo_pavadinimas);
            auto t2 = std::chrono::high_resolution_clock::now(); 
            std::chrono::duration<double> t_skaitymo = t2 - t1;
            std::cout << dydis << " irasu failo skaitymo laikas (List): " << std::fixed << std::setprecision(6) << t_skaitymo.count() << "\n";
            auto t3 = std::chrono::high_resolution_clock::now();
            studentu_rusiavimas(grupe, vargsiukai, kietiakai);
            auto t4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_dalijimo = t4 - t3;
            std::cout << dydis << " irasu failo dalijimo i dvi grupes laikas (List): " << std::fixed << std::setprecision(6) << t_dalijimo.count() << "\n";
            auto t5 = std::chrono::high_resolution_clock::now();
            isvedimo_rusiavimas(vargsiukai, pasirinkimas);
            isvedimo_rusiavimas(kietiakai, pasirinkimas);
            auto t6 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_rusiavimo = t6 - t5;
            std::cout << dydis << " irasu failo rusiavimo didejimo tvarka su sort funkcija laikas (List): " << std::fixed << std::setprecision(6) << t_rusiavimo.count() << "\n";
            auto t7 = std::chrono::high_resolution_clock::now();
            studentu_isvedimas(varg, vargsiukai);
            auto t8 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_vargsiuku = t8 - t7;
            std::cout << dydis << " irasu vargsiuku isvedimo laikas (List): " << std::fixed << std::setprecision(6) << t_vargsiuku.count() << "\n";
            auto t9 = std::chrono::high_resolution_clock::now();
            studentu_isvedimas(kiet, kietiakai);
            auto t10 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> t_kietiaku = t10 - t9;
            std::cout << dydis << " irasu kietiaku isvedimo laikas (List): " << std::fixed << std::setprecision(6) << t_kietiaku.count() << "\n";
            std::chrono::duration<double> is_viso = t_skaitymo + t_dalijimo + t_rusiavimo + t_vargsiuku + t_kietiaku;
            std::cout << dydis << " irasu testo laikas (List): " << std::fixed << std::setprecision(6) << is_viso.count() << "\n\n";
        }    
    }
}

void strategiju_analize()
{
    const std::vector<size_t> dydziai = {1000, 10000, 100000, 1000000, 10000000};

    for (size_t dydis : dydziai)
    {
        const std::string failo_pavadinimas = "studentai_" + std::to_string(dydis) + ".txt";
        std::ifstream failas(failo_pavadinimas);

        if (!failas.is_open())
        {
            std::cerr << "Klaida: nerastas duomenu failas " << failo_pavadinimas << "\n";
            return;
        }
    }

    for (size_t dydis : dydziai)
        {
            const std::string failo_pavadinimas = "studentai_" + std::to_string(dydis) + ".txt";
            std::cout << "\n" << dydis << " studentu dalijimo laikai (sekundemis):\n";
            {
                std::vector<studentas> vector1;
                std::vector<studentas> vector1Vargsiukai;
                std::vector<studentas> vector1Kietiakai;
                std::string vectorFailas1 = failo_pavadinimas;
                failo_skaitymas(vector1, vectorFailas1);

                auto pradzia = std::chrono::steady_clock::now();
                studentu_rusiavimas(vector1, vector1Vargsiukai, vector1Kietiakai);
                auto pabaiga = std::chrono::steady_clock::now();
                const std::chrono::duration<double> laikas = pabaiga - pradzia;
                std::cout << "1 strategija (Vector): " << std::fixed << std::setprecision(6)
                          << laikas.count() << "\n" << std::flush;
            }

            {
                std::vector<studentas> vector2;
                std::vector<studentas> vector2Vargsiukai;
                std::string vectorFailas2 = failo_pavadinimas;
                failo_skaitymas(vector2, vectorFailas2);

                auto pradzia = std::chrono::steady_clock::now();
                studentu_rusiavimas_2strat(vector2, vector2Vargsiukai);
                auto pabaiga = std::chrono::steady_clock::now();
                const std::chrono::duration<double> laikas = pabaiga - pradzia;
                std::cout << "2 strategija (Vector): " << std::fixed << std::setprecision(6)
                          << laikas.count() << "\n" << std::flush;
            }

            {
                std::vector<studentas> vector3;
                std::vector<studentas> vector3Vargsiukai;
                std::string vectorFailas3 = failo_pavadinimas;
                failo_skaitymas(vector3, vectorFailas3);

                auto pradzia = std::chrono::steady_clock::now();
                studentu_rusiavimas_3strat(vector3);
                auto pabaiga = std::chrono::steady_clock::now();
                const std::chrono::duration<double> laikas = pabaiga - pradzia;
                std::cout << "3 strategija (Vector): " << std::fixed << std::setprecision(6)
                          << laikas.count() << "\n" << std::flush;
            }

            {
                std::list<studentas> list1;
                std::list<studentas> list1Vargsiukai;
                std::list<studentas> list1Kietiakai;
                std::string listFailas1 = failo_pavadinimas;
                failo_skaitymas(list1, listFailas1);

                auto pradzia = std::chrono::steady_clock::now();
                studentu_rusiavimas(list1, list1Vargsiukai, list1Kietiakai);
                auto pabaiga = std::chrono::steady_clock::now();
                const std::chrono::duration<double> laikas = pabaiga - pradzia;
                std::cout << "1 strategija (List):   " << std::fixed << std::setprecision(6)
                          << laikas.count() << "\n" << std::flush;
            }

            {
                std::list<studentas> list2;
                std::list<studentas> list2Vargsiukai;
                std::string listFailas2 = failo_pavadinimas;
                failo_skaitymas(list2, listFailas2);

                auto pradzia = std::chrono::steady_clock::now();
                studentu_rusiavimas_2strat(list2, list2Vargsiukai);
                auto pabaiga = std::chrono::steady_clock::now();
                const std::chrono::duration<double> laikas = pabaiga - pradzia;
                std::cout << "2 strategija (List):   " << std::fixed << std::setprecision(6)
                          << laikas.count() << "\n" << std::flush;
            }

            {
                std::list<studentas> list3;
                std::list<studentas> list3Vargsiukai;
                std::string listFailas3 = failo_pavadinimas;
                failo_skaitymas(list3, listFailas3);

                auto pradzia = std::chrono::steady_clock::now();
                studentu_rusiavimas_3strat(list3);
                auto pabaiga = std::chrono::steady_clock::now();
                const std::chrono::duration<double> laikas = pabaiga - pradzia;
                std::cout << "3 strategija (List):   " << std::fixed << std::setprecision(6)
                          << laikas.count() << "\n" << std::flush;
            }
        }
}

void studentu_rusiavimas(const std::vector<studentas> &grupe, std::vector<studentas> &vargsiukai, std::vector<studentas> &kietiakai)
{
    for (const studentas &B : grupe)
    {
        if (B.galutinisVid < 5.0 || B.galutinisMed < 5.0)
        {
            vargsiukai.push_back(B);
        }
        else
        {
            kietiakai.push_back(B);
        }
    }
}

void studentu_rusiavimas(const std::list<studentas> &grupe, std::list<studentas> &vargsiukai, std::list<studentas> &kietiakai)
{
    for (const studentas &B : grupe)
    {
        if (B.galutinisVid < 5.0 || B.galutinisMed < 5.0)
        {
            vargsiukai.push_back(B);
        }
        else
        {
            kietiakai.push_back(B);
        }
    }
}

bool yra_vargsiukas(const studentas& A)
{
    return A.galutinisVid < 5.0 || A.galutinisMed < 5.0;
}

void studentu_rusiavimas_2strat(
    std::vector<studentas>& grupe,
    std::vector<studentas>& vargsiukai)
{
    vargsiukai.clear();

    for (const studentas& A : grupe)
    {
        if (yra_vargsiukas(A))
        {
            vargsiukai.push_back(A);
        }
    }

    grupe.erase(
        std::remove_if(grupe.begin(), grupe.end(), yra_vargsiukas),
        grupe.end());
}

void studentu_rusiavimas_2strat(
    std::list<studentas>& grupe,
    std::list<studentas>& vargsiukai)
{
    vargsiukai.clear();

    for (const studentas& A : grupe)
    {
        if (yra_vargsiukas(A))
        {
            vargsiukai.push_back(A);
        }
    }

    grupe.remove_if(yra_vargsiukas);
}

bool yra_kietiakas(const studentas& A)
{
    return !yra_vargsiukas(A);
}

void studentu_rusiavimas_3strat(
    std::vector<studentas>& grupe)
{
    grupe.clear();

    auto riba = std::partition(
        grupe.begin(), grupe.end(), yra_kietiakas);

    grupe.assign(riba, grupe.end());
}

void studentu_rusiavimas_3strat(
    std::list<studentas>& grupe)
{
    grupe.clear();

    auto riba = std::partition(
        grupe.begin(), grupe.end(), yra_kietiakas);

    grupe.assign(riba, grupe.end());
}

void studentu_isvedimas(const std::string &failoPavadinimas, const std::vector<studentas> &grupe)
{
    std::ofstream outputas(failoPavadinimas);
    if (!outputas.is_open())
    {
        std::cerr << "Klaida: nepavyko atidaryti failo " << failoPavadinimas << " rasymui\n";
        return;
    }
    outputas << std::left << std::setw(13) << "Vardas" << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(20) << "Galutinis (Vid.)" << std::left << std::setw(20) << "Galutinis (Med.)" << "\n";
    outputas << std::string(68, '-') << "\n";
    for (const studentas&A : grupe)
    {
        outputas << std::left << std::setw(13) << A.vardas << std::left << std::setw(15) << A.pavarde << std::left << std::setw(20) << std::fixed << std::setprecision(2) << A.galutinisVid << std::left << std::setw(20) << A.galutinisMed << "\n";
    }
    outputas.close();
}

void studentu_isvedimas(const std::string &failoPavadinimas, const std::list<studentas> &grupe)
{
    std::ofstream outputas(failoPavadinimas);
    if (!outputas.is_open())
    {
        std::cerr << "Klaida: nepavyko atidaryti failo " << failoPavadinimas << " rasymui\n";
        return;
    }
    outputas << std::left << std::setw(13) << "Vardas" << std::left << std::setw(15) << "Pavarde" << std::left << std::setw(20) << "Galutinis (Vid.)" << std::left << std::setw(20) << "Galutinis (Med.)" << "\n";
    outputas << std::string(68, '-') << "\n";
    for (const studentas&A : grupe)
    {
        outputas << std::left << std::setw(13) << A.vardas << std::left << std::setw(15) << A.pavarde << std::left << std::setw(20) << std::fixed << std::setprecision(2) << A.galutinisVid << std::left << std::setw(20) << A.galutinisMed << "\n";
    }
    outputas.close();
}

void isvedimo_rusiavimas(std::vector<studentas> &grupe, int pasirinkimas) {
    if (pasirinkimas == 1) {
        std::sort(grupe.begin(), grupe.end(), pagal_varda);
    } 
    else if (pasirinkimas == 2) {
        std::sort(grupe.begin(), grupe.end(), pagal_pavarde);
    } 
    else if (pasirinkimas == 3) {
        std::sort(grupe.begin(), grupe.end(), pagal_galutinisVid);
    } 
    else if (pasirinkimas == 4) {
        std::sort(grupe.begin(), grupe.end(), pagal_galutinisMed);
    }
}

void isvedimo_rusiavimas(std::list<studentas> &grupe, int pasirinkimas) {
    if (pasirinkimas == 1) {
        grupe.sort(pagal_varda);
    } 
    else if (pasirinkimas == 2) {
        grupe.sort(pagal_pavarde);
    } 
    else if (pasirinkimas == 3) {
        grupe.sort(pagal_galutinisVid);
    } 
    else if (pasirinkimas == 4) {
        grupe.sort(pagal_galutinisMed);
    }
}

bool pagal_varda(const studentas &A, const studentas &B) {
    if (A.vardas != B.vardas) return A.vardas < B.vardas;
    return A.pavarde < B.pavarde;
}
bool pagal_pavarde(const studentas &A, const studentas &B) {
    if (A.pavarde != B.pavarde) return A.pavarde < B.pavarde;
    return A.vardas < B.vardas;
}
bool pagal_galutinisVid(const studentas &A, const studentas &B)
{
    return A.galutinisVid < B.galutinisVid;
}
bool pagal_galutinisMed(const studentas &A, const studentas &B)
{
    return A.galutinisMed < B.galutinisMed;
}