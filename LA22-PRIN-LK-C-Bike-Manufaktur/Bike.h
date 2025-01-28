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
		hinzufuegenKomp();  // Komponenten beim Erstellen des Bikes hinzufügen
	}

	void leseDatenAusDatei(const string& dateiname) {
		ifstream file(dateiname);

		// Überprüfen, ob die Datei erfolgreich geöffnet wurde
		if (!file.is_open()) {
			cerr << "Fehler: Die Datei konnte nicht geöffnet werden: " << dateiname << endl;
			return;
		}

		string line;

		// Lesen der Komponenten
		while (getline(file, line)) {
			if (line.empty()) continue;  // Leere Zeilen überspringen

			cout << "Lesen der Zeile: " << line << endl;  // Debugging-Ausgabe

			if (line.find(';') != string::npos) {
				// Trennen der Zeile in part0 und part1
				size_t pos = line.find(';');
				string part0 = line.substr(0, pos);
				string part1 = line.substr(pos + 1);

				// Bestimmen des Typs und Hinzufügen der Komponente
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
				//else if (type[0] == 'g') {  // Gabel (falls benötigt)
				//    hinzufuegen(new Gabel(part0, part1));
				//}

			}
			else {
				// Letzte Zeile für Modell und Kategorie
				stringstream ss(line);
				getline(ss, modell, ';');
				// Hier könnte man die Kategorie setzen, falls benötigt
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

		// Schleife über alle Komponenten
		while (temp) {
			gesamtPreis += temp->getPreis(); // Grundpreis der aktuellen Komponente hinzufügen

			// Überprüfen, ob die aktuelle Komponente ein RahmenTeil ist und die Bezeichnung "Manu" enthält
			if (dynamic_cast<RahmenTeil*>(temp) && temp->getBezeichnung().find("Manu") != string::npos) {
				gesamtPreis *= 0.90; // 10% Rabatt auf den Gesamtpreis anwenden
			}

			/*
			dynamic_cast<RahmenTeil*>(temp) prüft, ob temp ein Zeiger auf ein RahmenTeil - Objekt ist. 
			dynamic_cast wird verwendet, um sicherzustellen, dass der Typ korrekt ist, 
			und gibt nullptr zurück, wenn der Cast fehlschlägt.
				
			temp->getBezeichnung().find("Manu") sucht in der Bezeichnung nach "Manu".
			Wenn beide Bedingungen erfüllt sind, wird ein Rabatt von 10 % auf den Gesamtpreis angewendet.
			*/


			// Überprüfen, ob die aktuelle Komponente ein EinzelTeil ist und der Name mit "Tubeless" beginnt
			if (dynamic_cast<EinzelTeil*>(temp) && temp->getHersteller().find("Tubeless") == 0) {
				gesamtPreis += 12.0f; // Zusatzkosten von 12 Euro für Tubeless-Komponenten hinzufügen
			}

			// Überprüfen, ob die Bezeichnung der aktuellen Komponente "Bremsscheibe" enthält
			if (temp->getBezeichnung().find("Bremsscheibe") != string::npos) {
				gesamtPreis += 8.0f; // Zusatzkosten von 8 Euro für Bremsscheiben hinzufügen
			}

			temp = temp->getNaechste(); // Zeiger auf die nächste Komponente setzen
		}

		return gesamtPreis; // Gesamtpreis zurückgeben
	}

	Komponente* getErsteKomp() const {
		return ersteKomp;  // Gibt die erste Komponente zurück
	}

	string ersetzeKomp(Komponente* neu) {
		stringstream ausbau;
		ausbau << "Auszubauende Komponenten:\n";

		// Überprüfen, ob die letzte Komponente die zu ersetzende ist
		if (letzteKomp && letzteKomp->getID() == neu->getID()) {
			ausbau << letzteKomp->toString() << endl;
			letzteKomp = neu; // Ersetze die letzte Komponente
			letzteKomp->setVorherige(nullptr);
			return ausbau.str();
		}

		// Durch die Liste von hinten nach vorne iterieren
		Komponente* aktuelle = letzteKomp;
		while (aktuelle != ersteKomp) {
			ausbau << aktuelle->toString() << endl; // Füge die aktuelle Komponente zur Demontage-Liste hinzu

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
				return ausbau.str(); // Rückgabe der Demontage-Liste
			}

			aktuelle = aktuelle->getVorherige(); // Nächste Komponente in der Liste
		}

		// Wenn die Komponente nicht gefunden wurde
		ausbau.str(""); // Leeren des Stringstreams
		ausbau << "Komponente nicht ausgebaut";
		return ausbau.str();
	}

};