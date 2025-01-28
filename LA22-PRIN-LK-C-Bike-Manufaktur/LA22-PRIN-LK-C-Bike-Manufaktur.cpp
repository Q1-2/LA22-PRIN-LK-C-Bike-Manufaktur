#include <fstream>
#include <sstream>
#include <iostream>
#include "Komponente.h"
#include "Kategorie.h"
#include "Bike.h"

using namespace std;

// Initialisieren der statischen Variablen
int Bike::autowert = 0;

int main() {
    // Beispiel zur Verwendung der Klassen
    Bike bike("konfigurationsdatei.csv");

    // Ausgabe der Komponenten
    Komponente* temp = bike.getErsteKomp();
    while (temp) {
        cout << temp->toString() << endl;  // Ausgabe der toString()-Methode für jede Komponente
        temp = temp->getNaechste();  // Nächste Komponente
    }

    // Gesamtgewicht und Gesamtpreis ausgeben
    cout << "Gesamtgewicht: " << bike.ermittleGewicht() << " g" << endl;
    cout << "Gesamtpreis: " << bike.berechnePreis() << " EUR\n" << endl;

    // Ausgabe der aktuellen Komponenten
    temp = bike.getErsteKomp();
    cout << "Aktuelle Komponenten:" << endl;
    while (temp) {
        cout << temp->toString() << endl;
        temp = temp->getNaechste();
    }

    // Erstellen einer neuen Komponente, die ersetzt werden soll
    Komponente* neueKomponente = new RahmenTeil("r7,Gabel,367,299.50,Manu", "Manu A,56 cm");

    // Testen der Ersetzung
    string result = bike.ersetzeKomp(neueKomponente);
    cout << result << endl;  // Ausgabe des Ergebnisses der Ersetzung

    // Ausgabe der aktuellen Komponenten nach der Ersetzung
    temp = bike.getErsteKomp();
    cout << "Aktuelle Komponenten nach Ersetzung:" << endl;
    while (temp) {
        cout << temp->toString() << endl;
        temp = temp->getNaechste();
    }

    // Aufräumen
    delete neueKomponente;

    return 0;
}