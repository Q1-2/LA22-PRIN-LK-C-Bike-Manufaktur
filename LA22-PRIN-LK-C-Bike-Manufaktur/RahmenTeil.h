#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "Komponente.h"

using namespace std;

class RahmenTeil : public Komponente {
private:
    string gruppe;
    string abmessung;

public:
    RahmenTeil(const string& part0, const string& part1) : Komponente(part0) {
        stringstream ss(part1);
        string temp[2];
        for (int i = 0; i < 2; i++) {
            getline(ss, temp[i], ',');
        }
        gruppe = temp[0];
        abmessung = temp[1];
    }

    string toString() const override {
        return Komponente::toString() + " " + gruppe + ", " + abmessung + " cm";
    }
};