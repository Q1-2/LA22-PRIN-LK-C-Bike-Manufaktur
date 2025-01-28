#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Komponente.h"

using namespace std;

class EinzelTeil : public Komponente {
private:
    string name;
    string abmessung;

public:
    EinzelTeil(const string& part0, const string& part1) : Komponente(part0) {
        stringstream ss(part1);
        string temp[2];
        for (int i = 0; i < 2; i++) {
            getline(ss, temp[i], ',');
        }
        name = temp[0];
        abmessung = temp[1];
    }

    string toString() const override {
        return Komponente::toString() + " Name: " + name + ", " + abmessung + " cm";
    }
};

