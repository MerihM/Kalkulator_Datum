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
		dan = new int(12);
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
		DaniNaprijed(&BrDanaNaprijed);
		cout << "Ispis novog datuma " << *dan << "." << *mjesec << "." << *godina << endl;
	}
	void NazadRacunanje(int BrDanaNazad) {
		BrDanaNazad -= (*dan) - 1;
		(*mjesec)--;
		if (*mjesec < 1)
			DecembarDekrement();
		(*dan) = BrojDanaUMjesecu(*mjesec);
		if (BrDanaNazad >= 365)
			GodineNazad(&BrDanaNazad);
		if (BrDanaNazad >= 28)
			MjesecNazad(&BrDanaNazad);
		DaniNazad(&BrDanaNazad);
		cout << "Ispis novog datuma " << *dan << "." << *mjesec << "." << *godina << endl;
	}
	void IzmedjuDatuma() {
		/*
			Ovo ide vani, prima kao argumente dva objekta tipa Datum.
			Izracuna broj dana tako sto se prvo nadje broj dana prvog i drugog datuma
			Nadje se razlika broja dana. Provjeri se koliko je prestupnih godina izmedju 
			dvije godine i doda se na broj dana, isto tako se doda broj izostavljenih dana 
			u mjesecu.
			BrDana1 = PrviDatum->dan + ((PrviDatum->mjesec - 1) * 28) + (PrviDatum->godina * 365);
			^^ Za drugi datum
			^^ Doda se broj prestupnih dana i izostavljenih dana u mjesecu
			int veci = max(BrDana1, BrDana2), manji = min(BrDana1, BrDana2), UkupnoDana = 0;
			UkupnoDana = veci - manji;
		*/
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
	void DaniNaprijed(int* BrDana) {
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
	void GodineNazad(int* BrDana){
		while (*BrDana >= 365) {
			if (*mjesec != 2) {
				if ((*mjesec != 1 && PrestupnaGodina(*godina)) || (*mjesec == 1 && PrestupnaGodina(*godina - 1))) *BrDana -= 366;
				else *BrDana -= 365;
			}
			else if (*mjesec == 2) {
				if (*dan <= 28 && PrestupnaGodina(*godina - 1)) *BrDana -= 366;
				else if (*dan == 29) { (*dan)--; *BrDana -= 366; }
				else *BrDana -= 365;
			}
			(*godina)--;
		}
	}
	void MjesecNazad(int* BrDana) {
		while (*BrDana >= 28) {
			*BrDana -= BrojDanaUMjesecu((*mjesec)--);
			if (*mjesec < 1) DecembarDekrement();
		}
	}
	void DaniNazad(int* BrDana) {
		while (*BrDana != 0) {
			if (*BrDana < 0) {
				(* BrDana)++;
				(*dan)++;
			}
			else {
				(*BrDana)--;
				(*dan)--;
			}
		}
		if (*dan > BrojDanaUMjesecu(*mjesec)) {
			*dan -= BrojDanaUMjesecu(*mjesec);
			(*mjesec)++;
			if (*mjesec > 12) JanuarInkrement();
		}
		else if (*dan < 1) {
			cout << "Preostalo manje od 1 dana " << endl;
			(*dan)--;
			(* mjesec)--;
			if (*mjesec < 1) DecembarDekrement();
			*dan += BrojDanaUMjesecu(*mjesec);
		}
	}
};
int main() {
	Datum d;
	//d.NaprijedRacunanje(78541);
	d.NazadRacunanje(542134);
}