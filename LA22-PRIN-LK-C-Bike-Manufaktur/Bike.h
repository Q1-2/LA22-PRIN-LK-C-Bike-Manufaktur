#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Komponente.h"
#include "Kategorie.h"
#include "RahmenTeil.h"
#include "EinzelTeil.h"
#include "SchaltElement.h"

using namespace std;

class Bike {
private:
	static int autowert;
	int bikeID;
	int anzahlKomp;
	string modell;
	Kategorie* kategorie;
	Komponente* ersteKomp;
	Komponente* letzteKomp;
	vector<string> konfigzeilen;

public:
	Bike(const string& dateiname) : ersteKomp(nullptr), letzteKomp(nullptr), anzahlKomp(0) {
		leseDatenAusDatei(dateiname);
		hinzufuegenKomp();  // Komponenten beim Erstellen des Bikes hinzuf�gen
	}

	void leseDatenAusDatei(const string& dateiname) {
		ifstream file(dateiname);

		// �berpr�fen, ob die Datei erfolgreich ge�ffnet wurde
		if (!file.is_open()) {
			cerr << "Fehler: Die Datei konnte nicht ge�ffnet werden: " << dateiname << endl;
			return;
		}

		string line;

		// Lesen der Komponenten
		while (getline(file, line)) {
			if (line.empty()) continue;  // Leere Zeilen �berspringen

			cout << "Lesen der Zeile: " << line << endl;  // Debugging-Ausgabe

			if (line.find(';') != string::npos) {
				// Trennen der Zeile in part0 und part1
				size_t pos = line.find(';');
				string part0 = line.substr(0, pos);
				string part1 = line.substr(pos + 1);

				// Bestimmen des Typs und Hinzuf�gen der Komponente
				stringstream ss(part0);
				string type;
				getline(ss, type, ',');  // Typ der Komponente


				if (type[0] == 'r') {  // RahmenTeil
					hinzufuegen(new RahmenTeil(part0, part1));
				}
				else if (type[0] == 's') {  // SchaltElement
					hinzufuegen(new SchaltElement(part0, part1));
				}
				else if (type[0] == 'e') {  // EinzelTeil
					hinzufuegen(new EinzelTeil(part0, part1));
				}
				//else if (type[0] == 'g') {  // Gabel (falls ben�tigt)
				//    hinzufuegen(new Gabel(part0, part1));
				//}

			}
			else {
				// Letzte Zeile f�r Modell und Kategorie
				stringstream ss(line);
				getline(ss, modell, ';');
				// Hier k�nnte man die Kategorie setzen, falls ben�tigt
				// kategorie = new Kategorie(modell);
			}
		}
		file.close();
	}

	void hinzufuegenKomp() {
		for (const string& line : konfigzeilen) {
			// Hier annehmen, dass die Zeilen entsprechend dem Typ der Komponente formatiert sind
			stringstream ss(line);
			string type;
			getline(ss, type, ',');  // Typ der Komponente
			if (type == "RahmenTeil") {
				string part0, part1;
				getline(ss, part0, ',');
				getline(ss, part1);
				hinzufuegen(new RahmenTeil(part0, part1));
			}
			else if (type == "SchaltElement") {
				string part0, part1;
				getline(ss, part0, ',');
				getline(ss, part1);
				hinzufuegen(new SchaltElement(part0, part1));
			}
			else if (type == "EinzelTeil") {
				string part0, part1;
				getline(ss, part0, ',');
				getline(ss, part1);
				hinzufuegen(new EinzelTeil(part0, part1));
			}
		}
	}

	bool hinzufuegen(Komponente* komp) {
		if (!ersteKomp) {
			ersteKomp = komp;
			letzteKomp = komp;
		}
		else {
			letzteKomp->setNaechste(komp);
			komp->setVorherige(letzteKomp);
			letzteKomp = komp;
		}
		anzahlKomp++;
		return true;
	}

	int ermittleGewicht() const {
		int gesamtGewicht = 0;
		Komponente* temp = ersteKomp;
		while (temp) {
			gesamtGewicht += temp->getGewicht();
			temp = temp->getNaechste();
		}
		return gesamtGewicht;
	}

	float berechnePreis() const {
		float gesamtPreis = 0.0f; // Initialisierung des Gesamtpreises auf 0
		Komponente* temp = ersteKomp; // Setzen des Zeigers auf die erste Komponente

		// Schleife �ber alle Komponenten
		while (temp) {
			gesamtPreis += temp->getPreis(); // Grundpreis der aktuellen Komponente hinzuf�gen

			// �berpr�fen, ob die aktuelle Komponente ein RahmenTeil ist und die Bezeichnung "Manu" enth�lt
			if (dynamic_cast<RahmenTeil*>(temp) && temp->getBezeichnung().find("Manu") != string::npos) {
				gesamtPreis *= 0.90; // 10% Rabatt auf den Gesamtpreis anwenden
			}

			/*
			dynamic_cast<RahmenTeil*>(temp) pr�ft, ob temp ein Zeiger auf ein RahmenTeil - Objekt ist. 
			dynamic_cast wird verwendet, um sicherzustellen, dass der Typ korrekt ist, 
			und gibt nullptr zur�ck, wenn der Cast fehlschl�gt.
				
			temp->getBezeichnung().find("Manu") sucht in der Bezeichnung nach "Manu".
			Wenn beide Bedingungen erf�llt sind, wird ein Rabatt von 10 % auf den Gesamtpreis angewendet.
			*/


			// �berpr�fen, ob die aktuelle Komponente ein EinzelTeil ist und der Name mit "Tubeless" beginnt
			if (dynamic_cast<EinzelTeil*>(temp) && temp->getHersteller().find("Tubeless") == 0) {
				gesamtPreis += 12.0f; // Zusatzkosten von 12 Euro f�r Tubeless-Komponenten hinzuf�gen
			}

			// �berpr�fen, ob die Bezeichnung der aktuellen Komponente "Bremsscheibe" enth�lt
			if (temp->getBezeichnung().find("Bremsscheibe") != string::npos) {
				gesamtPreis += 8.0f; // Zusatzkosten von 8 Euro f�r Bremsscheiben hinzuf�gen
			}

			temp = temp->getNaechste(); // Zeiger auf die n�chste Komponente setzen
		}

		return gesamtPreis; // Gesamtpreis zur�ckgeben
	}

	Komponente* getErsteKomp() const {
		return ersteKomp;  // Gibt die erste Komponente zur�ck
	}

	string ersetzeKomp(Komponente* neu) {
		stringstream ausbau;
		ausbau << "Auszubauende Komponenten:\n";

		// �berpr�fen, ob die letzte Komponente die zu ersetzende ist
		if (letzteKomp && letzteKomp->getID() == neu->getID()) {
			ausbau << letzteKomp->toString() << endl;
			letzteKomp = neu; // Ersetze die letzte Komponente
			letzteKomp->setVorherige(nullptr);
			return ausbau.str();
		}

		// Durch die Liste von hinten nach vorne iterieren
		Komponente* aktuelle = letzteKomp;
		while (aktuelle != ersteKomp) {
			ausbau << aktuelle->toString() << endl; // F�ge die aktuelle Komponente zur Demontage-Liste hinzu

			if (aktuelle->getID() == neu->getID()) {
				// Ersetzen der Komponente
				neu->setVorherige(aktuelle->getVorherige());
				neu->setNaechste(aktuelle->getNaechste());

				if (aktuelle->getVorherige()) {
					aktuelle->getVorherige()->setNaechste(neu);
				}
				if (aktuelle->getNaechste()) {
					aktuelle->getNaechste()->setVorherige(neu);
				}

				aktuelle->setVorherige(nullptr);
				aktuelle->setNaechste(nullptr);
				return ausbau.str(); // R�ckgabe der Demontage-Liste
			}

			aktuelle = aktuelle->getVorherige(); // N�chste Komponente in der Liste
		}

		// Wenn die Komponente nicht gefunden wurde
		ausbau.str(""); // Leeren des Stringstreams
		ausbau << "Komponente nicht ausgebaut";
		return ausbau.str();
	}

};