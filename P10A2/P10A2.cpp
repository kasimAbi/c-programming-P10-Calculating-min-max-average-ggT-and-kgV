/**********************************************************/
/* Autor: Kasim Mermer                                    */
/* Datum: 11.12.2016									  */
/* Projekt: P10A2										  */
/* Beschreibung: min-/ max-/ mittelwert	ausrechnen.		  */
/**********************************************************/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<Windows.h>

#define Groesse 20
double pruefen(char[Groesse]);		// Funktionsdeklaration
int pruefen_int(char[Groesse]);
double get_Statistikwerte(int, int, double[]);
double wert_eingabe(void);


int main(void)
{
	// Initialisierungen/ Deklarationen
	int wahl = 0, anzahl = 0, index = 0, richtig;
	char eingabe[Groesse] = { 0 };		
	double *feld = 0;
	double wert;

	while (wahl != 4)
	{
		// Initialisierungen
		for (index = 0; index < anzahl; index++) {
			feld[index] = 0;
		}
		anzahl = 0;
		wert = 0.0;
		richtig = 0;

		// auswählen
		printf("Bitte waehlen sie eines der folgenden Optionen.\n (1) Minimumwert erfahren.\n (2) Maximumwert erfahren.\n (3) Mittelwert erfahren.\n (4) Programm beenden.\n\nIhre Wahl:\t");
		fgets(eingabe, Groesse, stdin);
		// Funktionsaufruf
		wahl = pruefen_int(eingabe);
		// führt eines der oben vorgegebenen menü werten aus. sonst keinen. und beenden wird unten speziell ausgeführt
		if (wahl < 4 && wahl > 0)
		{
			// Die Groesse des Arrays bestimmen.
			while (richtig != 1)
			{
				printf("\n\ngeben sie an, wie viele Zahlen sie eingeben moechten:\t");
				// String eingabe wird in integer umgewandelt in der Funktion(pruefen) und wird dann verwendet wenn die zahl groesser 0 ist und gueltig ist.
				fgets(eingabe, Groesse, stdin);
				anzahl = pruefen_int(eingabe);
				if (anzahl > 0)
				{
					// bedingung für die while schleife.
					richtig = 1;
				}
				else
				{
					printf("Ungueltiger Wert!.\n\n");
				}
			}
			// Wert(anzahl) wird in Byte mitgegeben. anzahl soll die Anzahl sein der zu erstellten Arrayplätzen. 
			feld = (double*)malloc(anzahl * sizeof(double));
			// werte für das array eingeben
			for (index = 0; index < anzahl; index++)
			{
				printf("Geben sie ihre %i.te Zahl ein:\t", index + 1);
				// Funktionsaufruf.
				feld[index] = wert_eingabe();
				// ein unwahrscheinlicher wert welches man eingibt dient bei mir als fehlermeldung.
				if (feld[index] == 49.10949)
				{
					// damit man die zahl erneut eingeben kann
					index--;
				}
			}
			// für die rechnung
			wert = get_Statistikwerte(wahl, anzahl, feld);
			switch (wahl)
			{
			case 1:
				printf("\nIhr Minimaler Wert: %lf\n", wert);
				break;

			case 2:
				printf("\nIhr Maximaler Wert: %lf\n", wert);
				break;

			case 3:
				printf("\nIhr Mittelwert: %lf\n", wert);
				break;

			default:
				printf("fehler_main\n\n");
				break;
			}
		}
		else if (wahl == 4)
		{
			printf("\nDas Programm wird nun beendet.");
		}
		else
		{
			printf("Sie haben etwas falsches eingegeben.\n");
		}
		// damit das Programm anhält
		fgets(eingabe, Groesse, stdin);
		// löscht commandozeile
		system("cls");
	}
	return 0;
}

// Funktion
double get_Statistikwerte(int wahl, int anzahl, double feld[])
{
	// Initialisierungen/ Deklarationen
	double fuer_Max = 1, fuer_Min = 1, fuer_mittel = 1, wert = 0;
	int index = 0;

	// solange index kleienr anzahl. anzahl der zahlen die in dem feld übergeben wurden
	for (index = 0; index < anzahl; index++)
	{
		// wenn fuer_min groesser gleich feld[] ist dann setzt er fuer_min gleich mit der Zahl von feld[]
		if (fuer_Min >= feld[index])
		{
			fuer_Min = feld[index];
		}
	}
	// solange index kleienr anzahl. anzahl der zahlen die in dem feld übergeben wurden
	for (index = 0; index < anzahl; index++)
	{
		// wenn fuer_min kleiner gleich feld[] ist dann setzt er fuer_min gleich mit der Zahl von feld[]
		if (fuer_Max <= feld[index])
		{
			fuer_Max = feld[index];
		}
	}
	// guckt was in der main gewählt wurde
	switch (wahl) 
	{
	case 1:
		// fuer minimumwert
		wert = fuer_Min;
		break;

	case 2:
		// fuer maximumwert
		wert = fuer_Max;
		break;

	case 3:
		// fuer mittelwert
		for (index = 0; index < anzahl; index++) 
		{
			fuer_mittel = fuer_mittel + feld[index];
		}
		wert = fuer_mittel / anzahl;
		break;

	default:
		// fuer den unwahrscheinlichen fall eines fehlers. der müsste oben aber abgefangen werden.
		wert = 0;
		printf("fehler");
		break;
	}
	// wert wird zurückgegeben
	return wert;
}

double wert_eingabe()
{
	double wert = 0;
	int  minus = 0, laenge = 0, index = 0;
	// String
	char eingabe[Groesse] = { 0 };
	// String eingabe
	fgets(eingabe, Groesse, stdin);
	// String wird als Integer Wert zurückgegeben und dann in Wert übergeben
	if (eingabe[0] == '-')
	{
		minus = 1;
	}
	laenge = strlen(eingabe);
	if (eingabe[0] == '-') {
		laenge = laenge - 2;		// laenge um 2 Stellen kürzen wegen dem + am Anfang und \0 ganz zum Schluss
		for (index = 0; index < laenge; index++) {	// Damit man das + weg bekommt
			eingabe[index] = eingabe[index + 1];	// ersetzt die "i.te" stelle mit der "i+1.te stelle
			eingabe[index + 1] = 0;		// setzt die i+1 stelle auf 0
		}
	}
	wert = pruefen(eingabe);
	if (minus == 1)
	{
		wert = wert * (-1);
	}
	// wert wird zurückgegeben
	return wert;
}

double pruefen(char eingabe[Groesse]) {	// Funktion
	int i = 0, laenge = 0, fehler = 0, punkt = 0, wert2 = 0, minus = 0;
	double wert = 0.0;
	laenge = strlen(eingabe);		// laenge von der Anzahl des Strings ausrechnen bzw herausfinden
	if (eingabe[0] == '+') {
		laenge = laenge - 2;		// laenge um 2 Stellen kürzen wegen dem + am Anfang und \0 ganz zum Schluss
		for (i = 0; i < laenge; i++) {	// Damit man das + weg bekommt
			eingabe[i] = eingabe[i + 1];	// ersetzt die "i.te" stelle mit der "i+1.te stelle
			eingabe[i + 1] = 0;		// setzt die i+1 stelle auf 0
		}
	}
	else {
		laenge--;		// laenge um 1 Stelle kürzen wegen \0 ganz zum Schluss
	}
	for (i = 0; i < laenge; i++) {
		if (isdigit(eingabe[i]) == 0) {		// kontrolliert ob die "i.te" Stelle von dem String die Werte von 0-9 besitzt,
											// indem es eine "0" also "false" oder eine "1" also "true" als rückgabeparameter zurück gibt.
			fehler++;			// wenn der rueckgabeparameter von der Funktion isDigit eine 1 ist, setzt er die Variable fehler auf 1.
			if (eingabe[i] == '.') {	// überprüft ob ein '.' also eine Komma vorhanden ist. Bzw mehrere Kommas vorhanden sind
				fehler--;
				punkt++;	// Für die Fehlerabfange falls mehrere Komams vorhanden sind
			}
		}
	}

	if (fehler == 0 && punkt == 0) {		// Falls der User einen Integer Wert eingegeben hat
		wert2 = atoi(eingabe);		// in Integer umwandeln und auf die Variable wert2 gleichsetzen
		wert = (double)wert2;		// wert2 als double in wert einschreiben
									// printf("eingabe:\t%lf\n\n", wert);	// Verwendungszweck: Kontrolle
	}
	else if (fehler == 0 && punkt == 1) {		// wenn fehler = 0 ist und punkt = 0 ist führt er das aus
		wert = atof(eingabe);		// Den String Wert in einen Double Wert umwandeln
									// printf("eingabe:\t%lf\n\n", wert);	// Verwendungszweck: Kontrolle
	}
	else {		// wenn fehler auf 1 gesetzt wurde dann führt er das aus
		printf("Sie haben einen Ungueltigen Wert eingegeben.\n\n");
		fehler = 0;		// setzt den fehler Wert wieder auf 0
		wert = 49.10949;
	}
	return wert;	// Gibt eine 0 als 'False' zurück
}

// funktionsaufruf für pruefen
int pruefen_int(char eingabe[Groesse]) {		// ein string wurde übergeben. ein integer wert wird übergeben
	int laenge = 0, fehler = 0, index = 0;	// initialisierungen
	laenge = strlen(eingabe);		// um herauszufinden wie groß der string ist
	if (eingabe[0] == '+') {		// überprüft ob ein + am anfang steht um es abzufangen
		laenge -= 2;		// wenn ja dann dekrementiert er die länge um 2
		for (index = 0; index < laenge; index++) {		// dient dazu um den + weg zu machen und um die zahlen zu vertauschen
			eingabe[index] = eingabe[index + 1];		// tauscht den ersten wert des arrays mit dem nächsten
			eingabe[index + 1] = 0;		// setzt den nächsten wert des arrays auf 0
		}
	}
	else {		// wenn die obige bedingung nicht erfüllt wurde dann führt er das aus
		laenge -= 1;	// länge wird um 1 dekrementiert. (länge--)
	}
	for (index = 0; index < laenge; index++) {		// dient dazu um alle string- zeichen zu überprüfen ob auch alle zahlen sind
		if (isdigit(eingabe[index]) == 0) {	// wenn eine 0 zurückgegeben wurde(also false) dann ist die stelle des arrays KEINE zahl und
			fehler++;		// die variable fehler wird incrementiert
		}
	}
	index = 0;		// index wird auf 0 gesetzt
	if (fehler == 0) {		// wenn fehler = 0 ist dann führt er die schleife aus
		index = atoi(eingabe);		// wandelt den string in einen integer wert um und setzt es mit index gleich
	}
	fehler = 0;	// setzt fehler = 0
	return index;	// gibt index wieder zurück
}			// ende........