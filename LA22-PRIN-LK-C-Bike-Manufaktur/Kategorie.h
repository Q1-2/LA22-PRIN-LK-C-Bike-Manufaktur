#pragma once
#include <string>
using namespace std;

class Kategorie {
private:
    string bezeichnung;
    bool versicherung;

public:
    Kategorie(const string& bezeichnung) : bezeichnung(bezeichnung), versicherung(false) {}
    void setVersicherung(bool vers) { versicherung = vers; }
    string getBezeichnung() const { return bezeichnung; }
    bool hasVersicherung() const { return versicherung; }
};