#pragma once
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Komponente abstract {
private:
    string iD;
protected:
    string bezeichnung;
    int gewicht;
    float preis;
    string hersteller;
    Komponente* naechste;
    Komponente* vorherige;

public:
    Komponente(const string& part0) : naechste(nullptr), vorherige(nullptr) {
        stringstream ss(part0);
        string temp[5];
        for (int i = 0; i < 5; i++) {
            getline(ss, temp[i], ',');
        }
        iD = temp[0];
        bezeichnung = temp[1];
        gewicht = stoi(temp[2]);
        preis = stof(temp[3]);
        hersteller = temp[4];
    }

    virtual string toString() const {
        return "ID=" + iD + ", " + bezeichnung + " wiegt " + to_string(gewicht) +
            " g, kostet " + to_string(preis) + " EUR, Hersteller: " + hersteller + ",";
    }

    // Getter f�r ID
    string getID() const {
        return iD;
    }

    // Getter f�r naechste
    Komponente* getNaechste() const {
        return naechste;
    }

    // Setter f�r naechste
    void setNaechste(Komponente* komp) {
        naechste = komp;
    }

    // Getter f�r vorherige
    Komponente* getVorherige() const {
        return vorherige;
    }

    // Setter f�r vorherige
    void setVorherige(Komponente* komp) {
        vorherige = komp;
    }

    // Getter f�r Bezeichnung
    string getBezeichnung() const {
        return bezeichnung;
    }

    // Getter f�r Gewicht
    int getGewicht() const {
        return gewicht;
    }

    // Getter f�r Preis
    float getPreis() const {
        return preis;
    }

    // Getter f�r Hersteller
    string getHersteller() const {
        return hersteller;
    }

};

