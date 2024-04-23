/**********************************************************/
/* Autor: Kasim Mermer                                    */
/* Datum: 10.12.2016									  */
/* Projekt: P10A1										  */
/* Beschreibung: ggT- / kgV- rechner 					  */
/**********************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>		// für atoi- Funktion
#include <string.h>		// für strlen- Funktion
#include <ctype.h>		// für isDigit- Funktion

#define Groesse 10
int pruefen(char[Groesse]);		// Funktionsdeklaration
int wert_eingabe(void);
int rechnung_ggT(int[], int);
int rechnung_kgV(int[], int);

int main(void) 
{
	int index, index2, wert, auswahl = 0, laenge, ggT, kgV;		// Deklarationen/ Initialisierungen
	char eingabe[Groesse] = { 0 };			// String
	// zeiger Initialisieren. man kann es auch deklarieren.
	int *feld = 0;		

	while (auswahl != 4) 
	{
		wert = 0;		// Initialisierungen
		auswahl = 0;
		// Damit er in die if- Schleife gleich rein springt wenn auswahl nicht passt
		laenge = -1;		
		ggT = 0;
		kgV = 0;

		printf("Was moechten sie tun?\n (1) ggT bestimmen.\n (2) kgV bestimmen.\n (3) ggT und kgV bestimmen.\n (4) Programm beenden.\n\nihre Wahl?\t");
		auswahl = wert_eingabe();
		// system("cls");
		if (auswahl < 4 && auswahl > 0)
		{
			printf("Wie viele Zahlen moechten sie eingeben? \t");
			// Anzahl der Zeichen von dem String
			laenge = wert_eingabe();
			// Wert(laenge) wird in Byte mitgegeben. laenge soll die Anzahl sein der zu erstellten Arrayplätzen.
			feld = (int*)malloc(laenge * sizeof(int));
			if (feld == NULL)
			{
				return 0;
			}
		}
														
		// Wenn laenge ugleich 0 ist (0 soll eine Fehlermeldung sein), führ er die unteren Befehle aus.	
		if (laenge != 0)	// if 1
		{
			// Führt solange index < laenge ist aus
			for (index = 0; index < laenge; index++)		
			{
				printf("Geben sie ihre %i.te Zahl ein:\t", index + 1);
				wert = wert_eingabe();
				// Wenn Wert keine 0 ist
				if (wert != 0)		// if 2
				{
					feld[index] = wert;
				}
				// Wenn die obige if- Bedingung nicht zutrifft(Wert = 0 also)
				else		// else 2
				{
					// Damit der User einen neuen Wert eingeben kann
					index--;		
				}
			}
			if (auswahl < 4 && auswahl > 0)
			{
				printf("\n");
				printf("Sie haben folgende Zahlen eingegeben:\n");
			}
			// zum ausgeben der Zahlen. index2 = 1 weil die 0 nciht mit berücksichtigt werden soll
			for (index = 0, index2 = 1; index < laenge; index++)		
			{
				printf("%i\t", feld[index]);	
				// Für Zeilensprung damit das Ordedntlicher aussieht
				if (index2 == 7)												
				{
					printf("\n");
					// setzt index2 wieder auf 0 damit der Zeilensprung auch zur richtigen Zeit ausgeführt ist.
					index2 = 0;		
				}
				// zählt index2 hoch für Zeilensprung
				index2++;		
			}
			// auswahl wird gewählt
			switch (auswahl) 
			{
			// wenn auswahl = 1 ist
			case 1: 
				// rechnung_ggT- Funktion wird aufgerufen und dabei wird feld[] und laenge übergeben und der rückgabewert wird ggT gesetzt
				ggT = rechnung_ggT(feld, laenge);
				printf("\n\n");
				printf("ggT lautet: %i\n", ggT);
				// beenden switch- case
				break;

			case 2:
				// rechnung_kgV- Funktion wird aufgerufen und dabei wird feld[] und laenge übergeben und der rückgabewert wird kgV gesetzt
				kgV = rechnung_kgV(feld, laenge);
				printf("\n\n");
				printf("kgV lautet: %i\n", kgV);
				// beenden switch- case
				break;

			case 3:
				// rechnung_ggT- Funktion wird aufgerufen und dabei wird feld[] und laenge übergeben und der rückgabewert wird ggT gesetzt
				ggT = rechnung_ggT(feld, laenge);
				// rechnung_kgV- Funktion wird aufgerufen und dabei wird feld[] und laenge übergeben und der rückgabewert wird kgV gesetzt
				kgV = rechnung_kgV(feld, laenge);
				printf("\n\n");
				printf("ggT lautet: %i\n", ggT);
				printf("kgV lautet: %i\n", kgV);
				// beenden switch- case
				break;

			case 4:
				// Beenden
				printf("Das Programm wird nun beendet.");
				// beenden switch- case
				break;

			default:
				// Fehlerausgabe
				printf("Fehelr.");
				// beenden switch- case
				break;
			}
		}
		else	// else 1
		{
			printf("Sie haben etwas Falsches eingegeben.\n");
		}
		printf("\n");
		// leert den Array wieder.
		for (index = 0; index < laenge; index++)		
		{
			feld[index] = 0;
		}
		// Damit das Programm zum stehen kommt.
		wert = wert_eingabe();	
		// löscht die Commandozeilen.
		system("cls");		
	}
	return 0;
}

// funktionsaufruf für pruefen
int pruefen(char eingabe[Groesse]) 
{	// ein string wurde übergeben. ein integer wert wird übergeben
	int laenge = 0, fehler = 0, index = 0;	// initialisierungen
	laenge = strlen(eingabe);		// um herauszufinden wie groß der string ist
	if (eingabe[0] == '+') 
	{	// überprüft ob ein + am anfang steht um es abzufangen
		laenge -= 2;		// wenn ja dann dekrementiert er die länge um 2
		for (index = 0; index < laenge; index++) 
		{	// dient dazu um den + weg zu machen und um die zahlen zu vertauschen
			eingabe[index] = eingabe[index + 1];		// tauscht den ersten wert des arrays mit dem nächsten
			eingabe[index + 1] = 0;		// setzt den nächsten wert des arrays auf 0
		}
	}
	else
	{	// wenn die obige bedingung nicht erfüllt wurde dann führt er das aus
		laenge -= 1;	// länge wird um 1 dekrementiert. (länge--)
	}
	for (index = 0; index < laenge; index++) 
	{	// dient dazu um alle string- zeichen zu überprüfen ob auch alle zahlen sind
		if (isdigit(eingabe[index]) == 0) 
		{	// wenn eine 0 zurückgegeben wurde(also false) dann ist die stelle des arrays KEINE zahl und
			fehler++;		// die variable fehler wird incrementiert
		}
	}
	index = 0;		// index wird auf 0 gesetzt
	if (fehler == 0) 
	{	// wenn fehler = 0 ist dann führt er die schleife aus
		index = atoi(eingabe);		// wandelt den string in einen integer wert um und setzt es mit index gleich
	}
	fehler = 0;	// setzt fehler = 0
	return index;	// gibt index wieder zurück
}			// ende........

// Funktionsaufruf wert_eingabe
int wert_eingabe() 
{
	int wert = 0;
	// String
	char eingabe[Groesse] = { 0 };			
	// String eingabe
	fgets(eingabe, Groesse, stdin);		
	// String wird als Integer Wert zurückgegeben und dann in Wert übergeben
	wert = pruefen(eingabe);		
	return wert;
}

// Funktion
int rechnung_ggT(int feld[], int laenge) 
{
	int ggT = 0, index = 0, index2 = 0, zwischenspeicher = 0, groesste_zahl = 0;		// Initialisierungen
	// Um die groesste Zahl herauszufinden
	for (index = 0; index < laenge; index++)	
	{
		// wenn die index.te Zahl größer groesste_zahl ist dann setzt er sie gleich groesste_zahl.
		if (feld[index] > groesste_zahl) 
		{
			// neue groesste Zahl speichern
			groesste_zahl = feld[index];		
		}
	}
	// damit alle Zahlen auch gerechnet werden bis zur groessten Zahl.
	for (index = 1; index <= groesste_zahl; index++)		
	{
		// soll alle die im feld[] gespeicherten Werte testen.
		for (index2 = 0; index2 < laenge; index2++)		
		{
			if (feld[index2] % index == 0)
			{
				// damit man weiß, ob die Zahl index mit alles Werten im feld[] teilbar sind
				zwischenspeicher++;		
			}
			// wenn index mit allen Werten teilbar ist, dann setzt er ggT = index und gibt das dann später wenn der Wert nicht umgeändert wurde aus.
			if (zwischenspeicher == laenge)		
			{										 
				ggT = index;
			}
		}
		// damit der neue Wert von index wieder getestet werden kann ob es mit allen Werten teilbar ist
		zwischenspeicher = 0;		
	}
	// ggT wird zurückgegeben
	return ggT;
}

// Funktion
int rechnung_kgV(int feld[], int laenge)
{
	int kgV = 0, index = 0, index2 = 0, zwischenspeicher = 0;		// Initialisierungen

	// damit alle Zahlen auch gerechnet werden bis zur groessten Zahl.
	for (index = 1; zwischenspeicher != laenge; index++)
	{
		// damit der neue Wert von index wieder getestet werden kann ob es mit allen Werten teilbar ist
		zwischenspeicher = 0;
		// soll alle die im feld[] gespeicherten Werte testen.
		for (index2 = 0; index2 < laenge; index2++)
		{
			if (index % feld[index2] == 0)
			{
				// damit man weiß, ob die Zahl index mit alles Werten im feld[] teilbar sind
				zwischenspeicher++;
			}
			// wenn index mit allen Werten teilbar ist, dann setzt er kgV = index und gibt das dann später wenn der Wert nicht umgeändert wurde aus.
			if (zwischenspeicher == laenge)
			{
				kgV = index;
			}
		}
	}
	// kgV wird zurückgegeben
	return kgV;
}