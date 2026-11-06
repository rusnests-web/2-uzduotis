#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentas.h"
#include <string>
#include <vector>
#include <list>

void printas(studentas &A, int pasirinkimas);
void failo_skaitymas(std::vector<studentas>& grupe, std::string& failo_pavadinimas);
void failo_skaitymas(std::list<studentas>& grupe, std::string& failo_pavadinimas);
void failu_generavimas(const std::string& failo_pavadinimas, size_t studentu_skaicius, size_t nd_kiekis);
void spartos_analize();
void strategiju_analize();
void studentu_rusiavimas(const std::vector<studentas>& grupe, std::vector<studentas>& vargsiukai, std::vector<studentas>& kietiakai);
void studentu_rusiavimas(const std::list<studentas>& grupe, std::list<studentas>& vargsiukai, std::list<studentas>& kietiakai);
void studentu_rusiavimas_2strat(std::vector<studentas>& grupe, std::vector<studentas>& vargsiukai);
void studentu_rusiavimas_2strat(std::list<studentas>& grupe, std::list<studentas>& vargsiukai);
void studentu_rusiavimas_3strat(std::vector<studentas>& grupe, std::vector<studentas>& vargsiukai);
void studentu_rusiavimas_3strat(std::list<studentas>& grupe, std::list<studentas>& vargsiukai);
bool yra_kietiakas(const studentas& A);
bool yra_vargsiukas(const studentas& A);
void studentu_isvedimas(const std::string& failoPavadinimas, const std::vector<studentas>& grupe);
void studentu_isvedimas(const std::string& failoPavadinimas, const std::list<studentas>& grupe);
void isvedimo_rusiavimas(std::vector<studentas>& grupe, int pasirinkimas);
void isvedimo_rusiavimas(std::list<studentas>& grupe, int pasirinkimas);
bool pagal_varda(const studentas &A, const studentas &B);
bool pagal_pavarde(const studentas &A, const studentas &B);
bool pagal_galutinisVid(const studentas &A, const studentas &B);
bool pagal_galutinisMed(const studentas &A, const studentas &B);

#endif