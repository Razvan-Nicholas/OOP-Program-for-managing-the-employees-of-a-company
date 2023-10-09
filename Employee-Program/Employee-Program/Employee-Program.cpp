#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <conio.h>

class Angajat {
public:
    std::string nume;
    std::string prenume;
    int varsta;
    std::string adresa;
    std::string departament;
    std::string functie;
    int salariu;
    int zile_concediu;

    void afiseaza() {
        std::cout << "Nume: " << nume << ", Prenume: " << prenume << ", Varsta: " << varsta << ", Adresa: " << adresa << ", Dept.: " << departament << ", Functie: " << functie << ", Salariu: " << salariu << ", Zile Concediu: " << zile_concediu << std::endl;
    }
};

class BazaDeDateAngajati {
public:
    std::string numeFisier;
    std::vector<Angajat> angajati;

    void incarcaDate() {
        std::ifstream fisier(numeFisier);
        while (fisier.good()) {
            Angajat a;
            fisier >> a.nume >> a.prenume >> a.varsta >> a.adresa >> a.departament >> a.functie >> a.salariu >> a.zile_concediu;
            angajati.push_back(a);
        }
        fisier.close();
    }

    void salveazaDate() {
        std::ofstream file(numeFisier);
        for (int i = 0; i < angajati.size(); i++) {
            file << angajati[i].nume << " " << angajati[i].prenume << " " << angajati[i].varsta << " " << angajati[i].adresa
                << " " << angajati[i].departament << " " << angajati[i].functie << " " << angajati[i].salariu << " " << angajati[i].zile_concediu << std::endl;
        }
        file.close();
    }
    void adaugaAngajat(Angajat angajat) {
        angajati.push_back(angajat);
    }

    void stergeAngajat(std::string nume, std::string prenume) {
        for (std::vector<Angajat>::iterator it = angajati.begin(); it != angajati.end();) {
            if (it->nume == nume && it->prenume == prenume) {
                it = angajati.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void adaugaSalariuSiZileConcediu(std::string nume, std::string prenume, std::string luna, int salariu, int zile_concediu) {
        for (int i = 0; i < angajati.size(); i++) {
            if (angajati[i].nume == nume && angajati[i].prenume == prenume) {
                angajati[i].salariu = salariu;
                angajati[i].zile_concediu = zile_concediu;
                break;
            }
        }
    }

    void afiseaza() {
        for (int i = 0; i < angajati.size(); i++) {
            angajati[i].afiseaza();
        }
    }

    void sorteazaDupaNume() {
        std::sort(angajati.begin(), angajati.end(), [](const Angajat& a, const Angajat& b) {
            if (a.nume != b.nume) {
                return a.nume < b.nume;
            }
            else {
                return a.prenume < b.prenume;
            }
            });
    }

    void sorteazaDupaSalariuMediu() {
        std::sort(angajati.begin(), angajati.end(), [](const Angajat& a, const Angajat& b) {
            return a.salariu < b.salariu;
            });
    }

    void afiseazaDupaDepartament(std::string departament) {
        for (int i = 0; i < angajati.size(); i++) {
            if (angajati[i].departament == departament) {
                angajati[i].afiseaza();
            }
        }
    }
};

int main() {
    BazaDeDateAngajati bd;
    bd.numeFisier = "angajati.txt";
    bd.incarcaDate();

    while (1) {
        std::cout << "Meniu:\n";
        std::cout << "1. Adauga angajat\n";
        std::cout << "2. Sterge angajat\n";
        std::cout << "3. Adauga salariu si zile de concediu\n";
        std::cout << "4. Afiseaza angajatii ordonati\n";
        std::cout << "5. Afiseaza angajatii dintr-un departament\n";
        std::cout << "6. Iesire\n";
        std::cout << "Alegerea ta: ";
        int choice;
        char ch;
        choice = 0;
        while (!choice)
            std::cin >> choice;

        if (choice == 1) {
            Angajat a;
            std::cout << "Nume: ";
            std::cin >> a.nume;
            std::cout << "Prenume: ";
            std::cin >> a.prenume;
            std::cout << "Varsta: ";
            std::cin >> a.varsta;
            std::cout << "Adresa: ";
            std::cin >> a.adresa;
            std::cout << "Departament: ";
            std::cin >> a.departament;
            std::cout << "Functie: ";
            std::cin >> a.functie;
            std::cout << "Salariu: ";
            std::cin >> a.salariu;
            std::cout << "Zile concediu: ";
            std::cin >> a.zile_concediu;
            bd.adaugaAngajat(a);
            bd.salveazaDate();
        }
        else
            if (choice == 2) {
                std::string nume, prenume;
                std::cout << "Nume: ";
                std::cin >> nume;
                std::cout << "Prenume: ";
                std::cin >> prenume;
                bd.stergeAngajat(nume, prenume);
                bd.salveazaDate();
            }
            else
                if (choice == 3) {
                    std::string nume, prenume, luna;
                    int salariu, zile_concediu;
                    std::cout << "Nume: ";
                    std::cin >> nume;
                    std::cout << "Prenume: ";
                    std::cin >> prenume;
                    std::cout << "Luna: ";
                    std::cin >> luna;
                    std::cout << "Salariu: ";
                    std::cin >> salariu;
                    std::cout << "Zile concediu: ";
                    std::cin >> zile_concediu;
                    bd.adaugaSalariuSiZileConcediu(nume, prenume, luna, salariu, zile_concediu);
                    bd.salveazaDate();
                }
                else
                    if (choice == 4) {
                        std::cout << "1. Sortare dupa nume\n";
                        std::cout << "2. Sortare dupa salariu mediu\n";
                        std::cout << "Alegerea ta: ";
                        int sort_choice;
                        std::cin >> sort_choice;

                        if (sort_choice == 1) {
                            bd.sorteazaDupaNume();
                        }
                        else if (sort_choice == 2) {
                            bd.sorteazaDupaSalariuMediu();
                        }
                        bd.afiseaza();
                        std::cin >> ch;
                    }
                    else
                        if (choice == 5) {
                            std::string departament;
                            std::cout << "Departament: ";
                            std::cin >> departament;
                            bd.afiseazaDupaDepartament(departament);
                            std::cin >> ch;
                        }
                        else
                            if (choice == 6) {
                                break;
                            }


    }
    return 0;
}