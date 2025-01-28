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

    // Getter für ID
    string getID() const {
        return iD;
    }

    // Getter für naechste
    Komponente* getNaechste() const {
        return naechste;
    }

    // Setter für naechste
    void setNaechste(Komponente* komp) {
        naechste = komp;
    }

    // Getter für vorherige
    Komponente* getVorherige() const {
        return vorherige;
    }

    // Setter für vorherige
    void setVorherige(Komponente* komp) {
        vorherige = komp;
    }

    // Getter für Bezeichnung
    string getBezeichnung() const {
        return bezeichnung;
    }

    // Getter für Gewicht
    int getGewicht() const {
        return gewicht;
    }

    // Getter für Preis
    float getPreis() const {
        return preis;
    }

    // Getter für Hersteller
    string getHersteller() const {
        return hersteller;
    }

};

