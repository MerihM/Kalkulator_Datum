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
	void JanuarInkrement() {
		*mjesec = 1;
		(*godina)++;
	}
	void DecembarDekrement() {
		*mjesec = 12;
		(*godina)--;
	}
	void InkrementDekrement(int* ZaInkrement, int* ZaDekrement) {
		(*ZaInkrement)++;
		(*ZaDekrement)--;
	}
public:
	Datum() {
		dan = new int(11);
		mjesec = new int(4);
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
	void NaprijedRacunanje(int BrDanaNaprijed) {
		BrDanaNaprijed += (*dan);
		(*mjesec)--;
		if (*mjesec < 1)
			DecembarDekrement();
		(*dan) = BrojDanaUMjesecu(*mjesec);
		if (BrDanaNaprijed >= 365)
			GodineNaprijed(&BrDanaNaprijed);
		if (BrDanaNaprijed >= 28)
			MjesecNaprijed(&BrDanaNaprijed);
		// Nisam siguran treba li, 75% da ne treba, da je viska jer se ostalo radi 
		//while (*dan > BrojDanaUMjesecu(*mjesec))
		//	InkrementDekrement(&BrDanaNaprijed, dan);
		RebalansDana(&BrDanaNaprijed);
		cout << "Ispis novog datuma " << *dan << "." << *mjesec << "." << *godina << endl;
	}
	void NazadRacunanje() {

	}
	void IzmedjuDatuma() {

	}
private:
	bool PrestupnaGodina(int GodinaProvjera) {
		return ((GodinaProvjera % 4 == 0 && GodinaProvjera % 100 != 0) || GodinaProvjera % 400 == 0);
	}
	void GodineNaprijed(int* BrDana) {
		while (*BrDana >= 365) {
			if (*mjesec != 2) {
				if ((*mjesec == 1 && PrestupnaGodina(*godina)) || (*mjesec != 1 && PrestupnaGodina(*godina + 1))) *BrDana -= 366;
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
	void MjesecNaprijed(int* BrDana) {
		while (*BrDana >= 28) {
			*BrDana -= BrojDanaUMjesecu((*mjesec)++);
			if (*mjesec > 12) JanuarInkrement();
		}
	}
	void RebalansDana(int* BrDana) {
		while (*BrDana != 0) {
			if (*BrDana < 0) InkrementDekrement(BrDana, dan);
			else InkrementDekrement(dan, BrDana);
		}
		if (*dan > BrojDanaUMjesecu(*mjesec)) {
			*dan -= BrojDanaUMjesecu(*mjesec);
			(*mjesec)++;
			if (*mjesec > 12) JanuarInkrement();
		}
	}
};
int main() {
	Datum d;
	d.NaprijedRacunanje(7854644);
}