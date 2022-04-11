#include <iostream>

using namespace std;

class Datum {
	int* dan, * mjesec, * godina;
	int BrojDanaUMjesecu(int Mjesec) {
		switch (Mjesec)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
			break;
		case 2: {
			if (PrestupnaGodina(*godina))
				return 29;
			else 
				return 28;
			break;
		}
		default:
			break;
		}
	}
	void InkrementDekrementPtr(int* ZaInkrement, int* ZaDekrement) {
		(* ZaInkrement)++;
		(* ZaDekrement)--;
	}
	void JanuarInkrement() {
		*mjesec = 1;
		(*godina)++;
	}
	void DecembarDekrement() {
		*mjesec = 12;
		(*godina)--;
	}
public:
	Datum() {
		dan = new int(1);
		mjesec = new int(1);
		godina = new int(2022);
	}
	Datum(int UneseniDan, int UneseniMjesec, int UnesenaGodina) {
		dan = new int(UneseniDan);
		mjesec = new int(UneseniMjesec);
		godina = new int(UnesenaGodina);
	}
	~Datum() {
		delete dan; dan = NULL;
		delete mjesec; mjesec = NULL;
		delete godina; godina = NULL;
	}
	void NaprijedRacunanje(int BrDanaNaprijed, bool nazad = false) {
		if (!nazad) {
			BrDanaNaprijed += (*dan);
			(*mjesec)--;
			if (*mjesec < 1) DecembarDekrement();
			(*dan) = BrojDanaUMjesecu(*mjesec);
			if (BrDanaNaprijed >= 365)
				GodineRebalans(&BrDanaNaprijed, nazad);
			if (BrDanaNaprijed >= 28)
				MjesecRebalans(&BrDanaNaprijed, nazad);
			while (*dan > BrojDanaUMjesecu(*mjesec))
				InkrementDekrementPtr(&BrDanaNaprijed, dan);
			DaniRebalans(&BrDanaNaprijed, nazad);
			cout << "Ispis novog datuma " << *dan << "." << *mjesec << "." << *godina << endl;
		}
		else {
			BrDanaNaprijed += (*dan);
			(*mjesec)--;
			if (*mjesec < 1) DecembarDekrement();
			(*dan) = BrojDanaUMjesecu(*mjesec);
			if (BrDanaNaprijed >= 365)
				GodineRebalans(&BrDanaNaprijed, nazad);
			if (BrDanaNaprijed >= 28)
				MjesecRebalans(&BrDanaNaprijed, nazad);
			while (*dan > BrojDanaUMjesecu(*mjesec))
				InkrementDekrementPtr(&BrDanaNaprijed, dan);
			DaniRebalans(&BrDanaNaprijed, nazad);
			cout << "Ispis novog datuma " << *dan << "." << *mjesec << "." << *godina << endl;
		}
	}
	void NazadRacunanje() {

	}
	void IzmedjuDatuma() {

	}
private:
	bool PrestupnaGodina(int GodinaProvjera) {
		return ((GodinaProvjera % 4 == 0 && GodinaProvjera % 100 != 0) || GodinaProvjera % 400 == 0);
	}
	void GodineRebalans(int* BrDana, bool nazad = false) {
		if (!nazad) {
			while (*BrDana >= 365) {
				if (*mjesec != 2) {
					if ((*mjesec == 1 && PrestupnaGodina(*godina)) || PrestupnaGodina(*godina + 1)) *BrDana -= 366;
					else *BrDana -= 365;
				}
				else if (*mjesec == 2) {
					if (*dan <= 28 && PrestupnaGodina(*godina)) *BrDana -= 366;
					else if (*dan == 29) { (*dan)--; *BrDana -= 366; }
					else *BrDana -= 365;
				}
				(*godina)++;
			}
		}
		else {
			while (*BrDana >= 365) {
				if (*mjesec != 2) {
					if ((*mjesec == 1 && PrestupnaGodina(*godina)) || PrestupnaGodina(*godina - 1)) *BrDana -= 366;
					else *BrDana -= 365;
				}
				else if (*mjesec == 2) {
					if (*dan <= 28 && PrestupnaGodina(*godina)) *BrDana -= 366;
					else if (*dan == 29) { (*dan)--; *BrDana -= 366; }
					else *BrDana -= 365;
				}
				(*godina)--;
			}
		}
	}
	void MjesecRebalans(int *BrDana, bool nazad = false) {
		if (!nazad) {
			while (*BrDana >= 28) {
				*BrDana -= BrojDanaUMjesecu(*mjesec);
				(*mjesec)++;
				if (*mjesec > 12)
					JanuarInkrement();
			}
		}
		else {
			while (*BrDana >= 28) {
				*BrDana -= BrojDanaUMjesecu(*mjesec);
				(*mjesec)--;
				if (*mjesec < 1)
					DecembarDekrement();
			}
		}
	}
	void DaniRebalans(int *BrDana, bool nazad = false) {
		if (!nazad) {
			while (*BrDana != 0) {
				if (*BrDana < 0)
					InkrementDekrementPtr(BrDana, dan);
				else
					InkrementDekrementPtr(dan, BrDana);
			}
			if (*dan > BrojDanaUMjesecu(*mjesec)) {
				(*mjesec)++;
				if (*mjesec > 12)
					JanuarInkrement();
				*dan -= BrojDanaUMjesecu(*mjesec);
			}
			else if (*dan < 1) {
				(*mjesec)--;
				if (*mjesec < 1)
					DecembarDekrement();
				*dan += BrojDanaUMjesecu(*mjesec);
			}
		}
		else {
			if (*BrDana < 0)
				*dan += *BrDana;
			else
				*dan -= *BrDana;
			if (*dan < 1) {
				(*mjesec)--;
				if (*mjesec < 1)
					DecembarDekrement();
				*dan += BrojDanaUMjesecu(*mjesec);
			}
		}
	}
};
int main() {
	Datum d;
	d.NaprijedRacunanje(367, true);
}