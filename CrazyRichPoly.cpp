#include <iostream>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <iomanip>
using namespace std;

struct kartuKesempatan
{
	string isi;
	kartuKesempatan * next;
};

typedef kartuKesempatan * pointerToKartuKesempatan;
typedef pointerToKartuKesempatan listKartu;

struct map
{
	string kota;	//panjang teks kota 3
	int harga;
	char namaPemilik[5];
	listKartu infoKartu;
	map * next;
	map * prev;
};

typedef map * pointerToMap;
typedef pointerToMap listMap;

struct koordinat
{
	int x;
	int y;
};

struct dalamGame
{
	int uang;
	int aset;
	int kartuBebasPenjara;
	map * posisi;
};

struct pemain
{
	char nama[5];
	dalamGame infoDalamGame;
	koordinat infoKoordinat;
	pemain * next;
};

typedef pemain * pointerToPemain;

struct antrian
{
	pointerToPemain head;
	pointerToPemain tail;
};

struct riwayat
{
	char nama[5];
	int dadu;
	riwayat * next;
};

typedef riwayat * pointerToRiwayat;

// S I S T E M N Y A  S I S T E M

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_cursor(bool visible)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

//S I S T E M  K A R T U

void createListKartu(listKartu & first)
{
	first = NULL;
}

void insertLastKartu(listKartu &first, pointerToKartuKesempatan pKartu)
{
	if (first == NULL)
	{
		first = pKartu;
	}
	else
	{
		pointerToKartuKesempatan last = first;

		while (last->next != NULL)
			last = last->next;
		last->next = pKartu;
	}
}

void createElementKartu(listKartu &first, pointerToKartuKesempatan &pKartu)
{
	string kartu[10] = { "Bebas dari penjara", "Hari Kemerdekaan, Hadiah $15", "Traktir Lawan $20", "Mendapat bansos $10", "Terima uang $10", "Denda $5", "Membayar pajak $37", "Hari ulang tahun, terima $8", "Mendapat $16 dari pemain lawan", "Bayar perbaikan jalan $7" };
	int indexKartu;

	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		indexKartu = (rand() % 9);
		pKartu = new kartuKesempatan;
		pKartu->isi = kartu[indexKartu];
		pKartu->next = NULL;
		insertLastKartu(first, pKartu);
		if (i == 9) pKartu->next = first;
	}
}

//S I S T E M  M A P

void createListMap(listMap & first)
{
	first = NULL;
}

void insertLastMap(listMap &first, pointerToMap pMap)
{
	if (first == NULL)
	{
		first = pMap;
	}
	else
	{
		pointerToMap last = first;

		while (last->next != NULL)
			last = last->next;
		last->next = pMap;
		pMap->prev = last;
	}
}

void createElementMap(listMap &first, pointerToMap &pMap, listKartu lKartu)
{
	string kota[24] = { "STR", "GRT", "TSK", "STA", "PLN", "BDG", "JIL", "TGR", "DIY", "STB", "KRT", "MLG", "GDL", "BGR", "PLN", "STC", "MDN", "DPK", "EJL", "BKS", "SBY", "STD", "KRT", "JKT" };
	int harga[24] = { 0, 10, 16, 50, 75, 24, 0, 32, 40, 50, 0, 48, 0, 56, 75, 50, 64, 72, 0, 80, 88, 50, 0, 96 };
	/*KETERANGAN :
	    STA : STASIUN A   -> kota[4]
	    STB : STASIUN B   -> kota[10]
	    STC : STASIUN C   -> kota[16]
	    STD : STASIUN D   -> kota[22]
	    JIL : JAIL        -> kota[7]
	    EJL : ENTER JAIL  -> kota[19]
	    KRT : KARTU       -> kota[11] dan kota[23]
	    GDL : GA DULU     -> kota[13]
	*/

	for (int i = 0; i < 24; i++)
	{
		pMap = new map;
		pMap->kota = kota[i];
		pMap->harga = harga[i];
		strcpy(pMap->namaPemilik, "");
		pMap->infoKartu = NULL;

		if (pMap->kota == "KRT")
		{
			pMap->infoKartu = lKartu;
		}

		pMap->next = NULL;
		pMap->prev = NULL;

		insertLastMap(first, pMap);

		if (i == 23)
		{
			pMap->next = first;
			first->prev = pMap;
		}
	}
}

// S I S T E M  P E M A I N

void insertLastPemain(pointerToPemain &first, pointerToPemain pPemain)
{
	if (first == NULL)
		first = pPemain;
	else
	{
		pointerToPemain last = first;

		while (last->next != NULL)
			last = last->next;
		last->next = pPemain;
	}
}

void createElementPemain(pointerToPemain &first, listMap lMap, char jumlahPemain)
{
	pointerToPemain pPemain;

	set_cursor(true);
	pPemain = new pemain;
	do {
		gotoxy(11, 10);
		cout << "_____";
		gotoxy(11, 10);
		cin >> pPemain->nama;
		if (strcmp(strupr(pPemain->nama), "BOT") == 0)
		{
			strcpy(pPemain->nama, "");
		}
		else
		{
			break;
		}
	} while (true);
	pPemain->infoDalamGame.uang = 500;
	pPemain->infoDalamGame.aset = 0;
	pPemain->infoDalamGame.kartuBebasPenjara = 0;
	pPemain->infoDalamGame.posisi = lMap;
	pPemain->infoKoordinat.x = 2;	//POSISI X,Y START
	pPemain->infoKoordinat.y = 40;
	pPemain->next = NULL;
	insertLastPemain(first, pPemain);

	pPemain = new pemain;
	if (jumlahPemain == '2')
	{
		do {
			gotoxy(35, 10);
			cout << "_____";
			gotoxy(35, 10);
			cin >> pPemain->nama;
			if (strcmp(strupr(pPemain->nama), "BOT") == 0)
			{
				strcpy(pPemain->nama, "");
			}
			else
			{
				break;
			}
		} while (true);
	}
	else
		strcpy(pPemain->nama, "BOT");
	pPemain->infoDalamGame.uang = 500;
	pPemain->infoDalamGame.aset = 0;
	pPemain->infoDalamGame.kartuBebasPenjara = 0;
	pPemain->infoDalamGame.posisi = lMap;
	pPemain->infoKoordinat.x = 2;	//POSISI X,Y START
	pPemain->infoKoordinat.y = 41;
	pPemain->next = first;
	insertLastPemain(first, pPemain);
}

void createQueuePemain(antrian & qPemain)
{
	qPemain.head = NULL;
	qPemain.tail = NULL;
}

int getIndexKartuKesempatan(string isi)
{
	int indexKartu;
	string kartu[10] = { "Bebas dari penjara", "Hari Kemerdekaan, Hadiah $15", "Traktir Lawan $20", "Mendapat bansos $10", "Terima uang $10", "Denda $5", "Membayar pajak $37", "Hari ulang tahun, terima $8", "Mendapat $16 dari pemain lawan", "Bayar perbaikan jalan $7" };

	for (int i = 0; i < 10; i++)
	{
		if (isi == kartu[i])
		{
			indexKartu = i;
			break;
		}
	}

	return indexKartu;
}

// S I S T E M  R I W A Y A T
void createRiwayat(pointerToRiwayat & stackRiwayat)
{
	stackRiwayat = NULL;
}

void createElementRiwayat(pointerToRiwayat &newStackRiwayat, char nama[5], int dadu)
{
	newStackRiwayat = new riwayat;
	strcpy(newStackRiwayat->nama, nama);
	newStackRiwayat->dadu = dadu;
	newStackRiwayat->next = NULL;
}

void pushRiwayat(pointerToRiwayat &stackRiwayat, pointerToRiwayat newStackRiwayat)
{
	if (stackRiwayat == NULL)
		stackRiwayat = newStackRiwayat;
	else
	{
		newStackRiwayat->next = stackRiwayat;
		stackRiwayat = newStackRiwayat;
	}
}

void printRiwayat(pointerToRiwayat stackRiwayat)
{
	gotoxy(90, 5);
	cout << char(218) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(191);
	gotoxy(90, 6);
	cout << char(179) << "Riwayat Dadu Pemain " << char(179) << endl;
	gotoxy(90, 7);
	cout << char(179) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(179);

	int x = 90, y = 8, yMax = 13;
	pointerToRiwayat pBantu = stackRiwayat;
	while (pBantu != NULL)
	{
		gotoxy(x, y);
		cout << char(179) << left << setw(6) << pBantu->nama << " " << char(179) << " " << left << setw(6) << pBantu->dadu << "     " << char(179);

		if (y == yMax)
			break;
		y++;
		pBantu = pBantu->next;
	}

	gotoxy(x, y);
	cout << char(192) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(217);
}

// T A M P I L A N  M E N U

void tampilanMenuUtama()
{
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(219) << char(219) << char(187) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(200) << char(205) << char(205) << char(205) << char(205) << char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(201) << char(188) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(200) << char(205) << char(188) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(219) << char(201) << char(205) << char(188) << char(32) << char(200) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) << char(188) << char(32) << char(32) << char(32) << char(32) << char(200) << char(219) << char(219) << char(201) << char(188) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(205) << char(205) << char(205) << char(205) << char(188) << char(32) << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << char(32) << char(32) << char(32) << char(200) << char(205) << char(188) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(187) << char(32) << char(32) << char(219) << char(219) << char(187) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(32) << char(200) << char(205) << char(188) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << endl;
	cout << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << char(32) << char(200) << char(205) << char(205) << char(205) << char(205) << char(188) << char(32) << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << endl;
	cout << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << endl;	//
	cout << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(219) << char(219) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << endl;
	cout << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << endl;
	cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << endl;
	cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << endl;
	cout << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << endl;
	cout << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(219) << char(219) << char(187) << endl;
	cout << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(201) << char(188) << endl;
	cout << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(188) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(219) << char(219) << char(201) << char(188) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(205) << char(188) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(205) << char(205) << char(205) << char(205) << char(188) << char(32) << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << char(32) << char(32) << char(32) << char(200) << char(205) << char(188) << char(32) << char(32) << char(32) << endl;
	//BATAS JUDUL
	cout << endl;
	//MENU
	cout << char(220) << char(219) << char(32) << char(32) << endl;
	cout << char(32) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(223) << char(220) << char(223) << char(219) << char(32) << char(219) << char(32) << char(219) << char(32) << char(219) << char(32) << char(32) << char(32) << char(220) << char(223) << char(219) << char(32) << char(219) << endl;
	cout << char(220) << char(219) << char(220) << char(32) << char(220) << char(32) << char(32) << char(219) << char(32) << char(223) << char(32) << char(219) << char(32) << char(219) << char(220) << char(219) << char(32) << char(219) << char(220) << char(220) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << endl;
	cout << endl;
	cout << char(219) << char(223) << char(219) << char(32) << endl;
	cout << char(32) << char(220) << char(223) << char(32) << char(32) << char(32) << char(223) << char(219) << char(223) << char(32) << char(219) << char(223) << char(223) << char(32) << char(219) << char(220) << char(32) << char(219) << char(32) << char(223) << char(219) << char(223) << char(32) << char(220) << char(223) << char(219) << char(32) << char(219) << char(220) << char(32) << char(219) << char(32) << char(219) << char(223) << char(223) << endl;
	cout << char(219) << char(220) << char(220) << char(32) << char(220) << char(32) << char(32) << char(219) << char(32) << char(32) << char(219) << char(219) << char(220) << char(32) << char(219) << char(32) << char(223) << char(219) << char(32) << char(32) << char(219) << char(32) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(32) << char(223) << char(219) << char(32) << char(219) << char(220) << char(219) << endl;
	cout << endl;
	cout << char(219) << char(223) << char(223) << char(219) << char(32) << endl;
	cout << char(32) << char(32) << char(223) << char(220) << char(32) << char(32) << char(32) << char(219) << char(220) << char(223) << char(32) << char(219) << char(223) << char(223) << char(32) << char(219) << char(32) << char(32) << char(32) << char(219) << char(32) << char(219) << char(32) << char(220) << char(223) << char(219) << char(32) << char(219) << char(223) << char(219) << endl;
	cout << char(219) << char(220) << char(220) << char(219) << char(32) << char(220) << char(32) << char(219) << char(32) << char(219) << char(32) << char(219) << char(219) << char(220) << char(32) << char(219) << char(220) << char(220) << char(32) << char(219) << char(220) << char(219) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(223) << char(220) << endl;
}

void tampilanMenuTentang()
{
	char pil2;
	do {
		cout << char(32) << char(223) << char(219) << char(223) << char(32) << char(219) << char(223) << char(223) << char(32) << char(219) << char(220) << char(32) << char(219) << char(32) << char(223) << char(219) << char(223) << char(32) << char(220) << char(223) << char(219) << char(32) << char(219) << char(220) << char(32) << char(219) << char(32) << char(219) << char(223) << char(223) << char(32) << char(223) << endl;
		cout << char(32) << char(32) << char(219) << char(32) << char(32) << char(219) << char(219) << char(220) << char(32) << char(219) << char(32) << char(223) << char(219) << char(32) << char(32) << char(219) << char(32) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(32) << char(223) << char(219) << char(32) << char(219) << char(220) << char(219) << char(32) << char(220) << endl;
		cout << endl;
		cout << char(220) << char(223) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(223) << char(223) << char(32) << char(220) << char(223) << char(219) << char(32) << char(219) << char(223) << char(219) << char(32) << char(220) << char(223) << char(219) << char(32) << char(32) << char(32) << char(219) << char(220) << char(220) << char(32) << char(219) << char(223) << char(223) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(223) << char(220) << char(223) << char(219) << char(32) << char(220) << char(223) << char(219) << char(32) << char(219) << char(32) << char(219) << char(220) << char(32) << char(219) << endl;
		cout << char(219) << char(223) << char(219) << char(32) << char(220) << char(32) << char(32) << char(32) << char(219) << char(220) << char(220) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(223) << char(220) << char(32) << char(219) << char(223) << char(219) << char(32) << char(32) << char(32) << char(219) << char(220) << char(219) << char(32) << char(219) << char(219) << char(220) << char(32) << char(219) << char(223) << char(220) << char(32) << char(219) << char(32) << char(223) << char(32) << char(219) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(32) << char(219) << char(32) << char(223) << char(219) << endl;
		cout << endl;
		cout << char(219) << char(220) << char(220) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(223) << char(223) << char(32) << char(219) << char(223) << char(219) << char(32) << char(220) << char(223) << char(219) << char(32) << char(223) << char(219) << char(223) << char(32) << char(219) << char(32) << char(219) << char(32) << char(219) << char(223) << char(219) << char(32) << char(220) << char(223) << char(219) << char(32) << char(219) << char(220) << char(32) << char(219) << endl;
		cout << char(219) << char(220) << char(219) << char(32) << char(220) << char(32) << char(32) << char(32) << char(219) << char(223) << char(223) << char(32) << char(219) << char(219) << char(220) << char(32) << char(219) << char(223) << char(220) << char(32) << char(219) << char(223) << char(219) << char(32) << char(32) << char(219) << char(32) << char(32) << char(219) << char(220) << char(219) << char(32) << char(219) << char(223) << char(220) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(32) << char(223) << char(219) << endl;
		cout << endl;
		cout << char(219) << char(223) << char(223) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(223) << char(220) << char(223) << char(219) << char(32) << char(219) << char(223) << char(223) << char(32) << char(219) << char(220) << char(32) << char(219) << char(32) << char(219) << char(32) << char(219) << char(32) << char(32) << char(32) << char(219) << char(32) << char(219) << char(32) << char(223) << char(219) << char(223) << char(32) << char(220) << char(223) << char(219) << char(32) << char(219) << char(223) << char(220) << char(223) << char(219) << char(32) << char(220) << char(223) << char(219) << endl;
		cout << char(219) << char(220) << char(220) << char(32) << char(220) << char(32) << char(32) << char(32) << char(219) << char(32) << char(223) << char(32) << char(219) << char(32) << char(219) << char(219) << char(220) << char(32) << char(219) << char(32) << char(223) << char(219) << char(32) << char(219) << char(220) << char(219) << char(32) << char(32) << char(32) << char(219) << char(220) << char(219) << char(32) << char(32) << char(219) << char(32) << char(32) << char(219) << char(223) << char(219) << char(32) << char(219) << char(32) << char(223) << char(32) << char(219) << char(32) << char(219) << char(223) << char(219) << endl;
		cout << "\nMasukkan Pilihan : ";
		cin >> pil2;
		cout << endl;
		if (pil2 == 'a' || pil2 == 'A')
        {
           cout << "1. Para pemain akan dibagikan uang sebesar $500" << endl;
           cout << "2. Pilih jumlah pemain yang akan bermain lalu pilih pemain pertama yang akan bermain."<<endl;
           cout << "Jika bermain sendiri maka otomatis akan bermain dengan BOT" << endl;
           cout << "3. Masukkan username/nama, selain 'BOT', pemain lalu urutan bermain akan diacak" << endl;
           cout << "4. Setelah menentukan urutan, pemain muali bermain dengan merandom dadu" << endl;
           cout << "   Pemain akan bergerak sesuai dengan hasil nilai dadu" << endl;
           cout << "5. Pemain bermain dengan menuruti peraturan yang tertera" << endl;
        }
        else if (pil2 == 'b' || pil2 == 'B')
        {
           cout << "1. Setiap pemain yang melewati garis start maka akan mendapat" << endl;
           cout << "   uang 500 dollar dari pihak bank." << endl;
           cout << "2. Ketika pion mendarat di area kosong atau tidak dimiliki, pemain" << endl;
           cout << "   dapat membeli area tersebut dari bank sesuai dengan harga" << endl;
           cout << "3. Bangunan yang belum dibangun dapat diperjuar belikan dengan pemain" << endl;
           cout << "   lain. Untuk harga sesuai dengan harga yang sudah tertera." << endl;
           cout << "4. Jika bidak mendarat di properti yang dimiliki oleh pemain lain" << endl;
           cout << "   akan dikenakan denda area sesuai harga denda" << endl;
           cout << "5. Kartu kesempatan merupakan kartu yang memberikan" << endl;
           cout << "   petunjuk-petunjuk yang harus diikuti pemain." << endl;
           cout << "6. Penyebab masuk penjara :" << endl;
           cout << "   - Pion berhenti di 'Enter Jail'" << endl;
           cout << "   - Mendapat perintah dari kartu kesempatan" << endl;
           cout << "7. Penyebab keluar penjara :" << endl;
           cout << "   - Mendapat angka dadu 6" << endl;
           cout << "   - Memiliki kartu bebas penjara" << endl;
           cout << "8. Pemain dinyatakan bangkrut jika berhutang dan tidak dapat" << endl;
           cout << "   membayarnya kepada pemain lain" << endl;
           cout << "9. Permainan selesai jika salah satu pemain bangkrut atau menyerah dalam permainan" << endl;
        }

		system("pause");
		system("cls");
	} while (pil2 != 'c' && pil2 != 'C');
	cout << endl;
}

void tampilanMenuKeluar()
{
	system("cls");
	cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << endl;
	cout << char(200) << char(205) << char(205) << char(219) << char(219) << char(201) << char(205) << char(205) << char(188) << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(205) << char(188) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(219) << char(219) << char(219) << char(219) << char(201) << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(219) << char(219) << char(201) << char(205) << char(205) << char(188) << char(32) << char(32) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << endl;
	cout << char(32) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(200) << char(205) << char(188) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(200) << char(205) << char(188) << char(32) << char(32) << char(32) << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << char(32) << char(32) << char(32) << char(32) << char(32) << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << endl;
	cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << endl;
	cout << char(219) << char(219) << char(187) << char(32) << char(32) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(187) << char(219) << char(219) << char(187) << char(32) << char(32) << char(219) << char(219) << char(187) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(219) << char(219) << char(186) << char(32) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(205) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(205) << char(188) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(219) << char(219) << char(201) << char(205) << char(219) << char(219) << char(187) << char(32) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(32) << char(200) << char(205) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(219) << char(219) << char(186) << char(32) << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << char(32) << char(32) << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << char(32) << endl;
	cout << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << char(32) << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188) << endl;
	Sleep(3000);
}

void menuPilih1atau2Pemain(char & jumlahPemain)
{
	system("cls");
	cout << char(218) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) <<
		char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) <<
		char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) <<
		char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(191) << endl;
	cout << char(179) << "                                         " << char(179) << endl;
	cout << char(179) << "                                         " << char(179) << endl;
	cout << char(179) << "         Mau Main Berapa Orang?          " << char(179) << endl;
	cout << char(179) << "                                         " << char(179) << endl;
	cout << char(179) << "                                         " << char(179) << endl;
	cout << char(179) << "              1 Pemain                   " << char(179) << endl;
	cout << char(179) << "              2 Pemain                   " << char(179) << endl;
	cout << char(179) << "                                         " << char(179) << endl;
	cout << char(179) << "                                         " << char(179) << endl;
	cout << char(179) << "          Pilihan (1/2) :                " << char(179) << endl;
	cout << char(179) << "                                         " << char(179) << endl;
	cout << char(192) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) <<
		char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) <<
		char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) <<
		char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(217) << endl;
	set_cursor(true);
	do {
		gotoxy(27, 10);
		cout << " " << endl;
		gotoxy(27, 10);
		cin >> jumlahPemain;
	} while (jumlahPemain != '1' && jumlahPemain != '2');
	set_cursor(false);

	cout << endl << endl;
	system("pause");
}

void menuInputNamaPemain(pointerToPemain &first, listMap lMap, char jumlahPemain)
{
	system("cls");
	for (int i = 0; i < 12; i++)
	{
		if (i == 0)
		{
			for (int j = 0; j < 51; j++)
			{
				if (j == 0) cout << char(218);
				else if (j == 50) cout << char(191);
				else cout << char(196);
			}
		}
		else if (i == 11)
		{
			for (int j = 0; j < 51; j++)
			{
				if (j == 0) cout << char(192);
				else if (j == 50) cout << char(217);
				else cout << char(196);
			}
		}
		else
		{
			for (int j = 0; j < 51; j++)
			{
				if (j == 0 || j == 50) cout << char(179);
				else cout << " ";
			}
		}

		cout << endl;
	}

	gotoxy(10, 1);
	cout << "Pemain 1" << endl << endl;
	gotoxy(10, 3);
	cout << char(176) << char(220) << char(220) << char(220) << char(220) << char(176) << endl;
	gotoxy(10, 4);
	cout << char(223) << char(223) << char(220) << char(219) << char(219) << char(220) << endl;
	gotoxy(10, 5);
	cout << char(223) << char(223) << char(219) << char(219) << char(219) << char(220) << endl;
	gotoxy(10, 6);
	cout << char(176) << char(223) << char(219) << char(219) << char(219) << char(220) << char(176) << char(219) << char(220) << endl;
	gotoxy(10, 7);
	cout << char(177) << char(220) << char(219) << char(219) << char(219) << char(220) << char(223) << char(223) << endl;
	gotoxy(2, 9);
	cout << "Masukkan Nama (5 Huruf)" << endl;
	gotoxy(11, 10);
	cout << "_____" << endl;

	cout << endl << endl;
	gotoxy(34, 1);
	cout << "Pemain 2" << endl << endl;
	gotoxy(33, 4);
	cout << char(220) << char(220) << char(219) << endl;
	gotoxy(33, 5);
	cout << char(223) << char(223) << char(219) << char(220) << char(220) << char(220) << char(220) << char(220) << char(220) << char(219) << endl;
	gotoxy(33, 6);
	cout << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << endl;
	gotoxy(33, 7);
	cout << " " << char(220) << char(219) << "   " << char(220) << char(219) << endl;
	gotoxy(26, 9);
	cout << "Masukkan Nama (5 Huruf)" << endl;
	if (jumlahPemain == '1')
	{
		gotoxy(35, 10);
		cout << "BOT__" << endl;
	}
	else
	{
		gotoxy(35, 10);
		cout << "_____" << endl;
	}

	createElementPemain(first, lMap, jumlahPemain);

	set_cursor(false);
	cout << endl << endl << endl;
	system("pause");
}

void randomUrutanPemain(pointerToPemain listPemain, antrian &qPemain)
{
	system("cls");
	cout << "\n Acak Urutan Pemain" << endl;
	Sleep(1000);
	srand(time(0));
	int acak = (rand() % 9);
	pointerToPemain pBantuPemain = listPemain;
	createQueuePemain(qPemain);

	for (int i = 0; i <= acak; i++)
	{
		if (i == acak)
		{
			qPemain.head = pBantuPemain;
			qPemain.tail = pBantuPemain->next;
		}

		pBantuPemain = pBantuPemain->next;
	}

	Sleep(1000);
	cout << "  Urutan 1 : " << qPemain.head->nama << endl;
	Sleep(1000);
	cout << "  Urutan 2 : " << qPemain.head->next->nama << endl << endl << endl;

	system("pause");
}

void menuMap(antrian qPemain, pointerToPemain &listPemain, pointerToRiwayat &stackRiwayat, string &namaPemenang)
{
	system("cls");
	char map[43][84] = {
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@      O  |           |           |           |           |           |  O      @@",
    "@@     O J [-----------+-----------+-----------+-----------+-----------] G O     @@",
    "@@    O I  |   T G R   |   D I Y   |   S T B   |   K R T   |   M L G   |  D O    @@",
    "@@   O L   [-----------+-----------+-----------+-----------+-----------]   L O   @@",
    "@@  O      |   $ 3 2   |   $ 4 0   |   $ 5 0   |K S M P T N|   $ 4 8   |      O  @@",
    "@@-----p-p-+-----------d-----------d-----------d-----------d-----------+-p-p-----@@",
    "@@     | | |                                                           | | |     @@",
    "@@     |B|$|                 ***  ****   ***  ***** *   *              |$|B|     @@",
    "@@     |D|2|                *     *  *  *   *    *   * *               |5|G|     @@",
    "@@     |G|4|               **     ***   *****   *     *                |6|R|     @@",
    "@@     | | |                *     *  *  *   *  *      *                | | |     @@",
    "@@-----+-+-]                 ***  *   * *   * *****   *                [-+-+-----@@",
    "@@     | | |                                                           | | |     @@",
    "@@     |P|$|       ****  *   *** *   *    ****   ***  *    *   *       |$|P|     @@",
    "@@     |L|7|       *  *  *  *    *   *    *   * *   * *     * *        |7|L|     @@",
    "@@     |N|5|       ***   * **    *****    ****  *   * *      *         |5|N|     @@",
    "@@     | | |       *  *  *  *    *   *    *     *   * *      *         | | |     @@",
    "@@-----+-+-]       *   * *   *** *   *    *      ***  *****  *         [-+-+-----@@",
    "@@     | | |                                                           | | |     @@",
    "@@     |S|$|                        ###########                        |$|S|     @@",
    "@@     |T|5|                        @ D A D U @                        |5|T|     @@",
    "@@     |A|0|                        @#########@                        |0|C|     @@",
    "@@     | | |                        @    X    @                        | | |     @@",
    "@@-----+-+-]                        @#########@                        [-+-+-----@@",
    "@@     | | |                                                           | | |     @@",
    "@@     |T|$|            ###################################            |$|M|     @@",
    "@@     |S|1|            @                                 @            |6|D|     @@",
    "@@     |K|6|            @ K A R T U   K E S E M P A T A N @            |4|N|     @@",
    "@@     | | |            @                                 @            | | |     @@",
    "@@-----+-+-]            @#################################@            [-+-+-----@@",
    "@@     | | |            @                                 @            | | |     @@",
    "@@     |G|$|            @                                 @            |$|D|     @@",
    "@@     |R|1|            @#################################@            |7|P|     @@",
    "@@     |T|0|                                                           |2|K|     @@",
    "@@     | | |                                                           | | |     @@",
    "@@-----d-d-+-----------p-----------p-----------p-----------p-----------+-d-d-----@@",
    "@@  O      |   J K T   |   K R T   |   S T D   |   S B Y   |   B K S   |      O  @@",
    "@@   O S   [-----------+-----------+-----------+-----------+-----------]   E O   @@",
    "@@    O T  |   $ 9 6   |K S M P T N|   $ 5 0   |   $ 8 8   |   $ 8 0   |  J O    @@",
    "@@     O R [-----------+-----------+-----------+-----------+-----------] L O     @@",
    "@@      O  |           |           |           |           |           |  O      @@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    };
	char keyboardInput;
	bool petakKosong = false, dendaPetak = false, petakKartuKesempatan = false, petakGDL1 = false, petakGDL2 = false;
	int dadu;
	srand(time(0));
	dadu = 1 + (rand() % 6);
	pointerToPemain pBantuAntrian = qPemain.head;
	namaPemenang = "";

	do {
		system("cls");
		for (int i = 0; i < 43; i++)
		{
			for (int j = 0; j < 84; j++)
			{
				if (map[i][j] == '#')
					cout << (char) 220;
				else if (map[i][j] == '*')
				{
					cout << (char) 4;
				}
				else if (map[i][j] == 'O')
				{
					cout << (char) 30;
				}
				else if (map[i][j] == '@')
				{
					cout << (char) 219;
				}
				else if (map[i][j] == '|')
				{
					cout << (char) 179;
				}
				else if (map[i][j] == '+')
				{
					cout << (char) 197;
				}
				else if (map[i][j] == '-')
				{
					cout << (char) 196;
				}
				else if (map[i][j] == ']')
				{
					cout << (char) 180;
				}
				else if (map[i][j] == '[')
				{
					cout << (char) 195;
				}
				else if (map[i][j] == 'd')
				{
					cout << (char) 193;
				}
				else if (map[i][j] == 'p')
				{
					cout << (char) 194;
				}
				else if (map[i][j] == 'X')
				{
					cout << dadu;
				}
				else
				{
					cout << map[i][j];
				}
			}

			cout << endl;
		}

		cout << endl << endl;

		//POSISI X,Y PEMAIN PADA MAP
		gotoxy(listPemain->infoKoordinat.x, listPemain->infoKoordinat.y);
		cout << left << setw(5) << listPemain->nama << endl;
		gotoxy(listPemain->next->infoKoordinat.x, listPemain->next->infoKoordinat.y);
		cout << left << setw(5) << listPemain->next->nama << endl;

		//HARUS DISINI BUAT BELI PETAK
		if (petakKosong)
		{
			if (pBantuAntrian->next == listPemain)
			{
				gotoxy(15, 35);
				cout << "                                                        " << endl;
				//MAU BELI PETAK INI?
				gotoxy(15, 35);
				cout << pBantuAntrian->next->nama << ", mau beli " << listPemain->infoDalamGame.posisi->kota << "($" << listPemain->infoDalamGame.posisi->harga << ")[Y/N]? " << endl;
				char beliPetak;
				do {
					beliPetak = getch();
					if (beliPetak == 'N' || beliPetak == 'n')
						break;
					else if (beliPetak == 'Y' || beliPetak == 'y')
					{
						if (listPemain->infoDalamGame.uang >= listPemain->infoDalamGame.posisi->harga)
						{
							listPemain->infoDalamGame.uang -= listPemain->infoDalamGame.posisi->harga;
							listPemain->infoDalamGame.aset += listPemain->infoDalamGame.posisi->harga;
							strcpy(listPemain->infoDalamGame.posisi->namaPemilik, listPemain->nama);
						}

						break;
					}
				} while (true);
			}
			else
			{
				if (strcmp(listPemain->next->nama, "BOT") == 0)
				{
					if (listPemain->next->infoDalamGame.uang >= listPemain->next->infoDalamGame.posisi->harga)
					{
						listPemain->next->infoDalamGame.uang -= listPemain->next->infoDalamGame.posisi->harga;
						listPemain->next->infoDalamGame.aset += listPemain->next->infoDalamGame.posisi->harga;
						strcpy(listPemain->next->infoDalamGame.posisi->namaPemilik, listPemain->next->nama);
					}
				}
				else
				{
					gotoxy(15, 35);
					cout << "                                                        " << endl;
					//MAU BELI PETAK INI?
					gotoxy(15, 35);
					cout << pBantuAntrian->next->nama << ", mau beli " << listPemain->next->infoDalamGame.posisi->kota << "($" << listPemain->next->infoDalamGame.posisi->harga << ")[Y/N]? " << endl;
					char beliPetak;
					do {
						beliPetak = getch();
						if (beliPetak == 'N' || beliPetak == 'n')
							break;
						else if (beliPetak == 'Y' || beliPetak == 'y')
						{
							if (listPemain->next->infoDalamGame.uang >= listPemain->next->infoDalamGame.posisi->harga)
							{
								listPemain->next->infoDalamGame.uang -= listPemain->next->infoDalamGame.posisi->harga;
								listPemain->next->infoDalamGame.aset += listPemain->next->infoDalamGame.posisi->harga;
								strcpy(listPemain->next->infoDalamGame.posisi->namaPemilik, listPemain->next->nama);
							}

							break;
						}
					} while (true);
				}
			}

			petakKosong = false;
		}

		//DIA NGINJAK PETAK BUKAN ATAS NAMA DIA
		if (dendaPetak)
		{
			if (pBantuAntrian->next == listPemain)
			{
				gotoxy(15, 35);
				cout << "                                                        " << endl;
				//KETERANGAN DENDA
				gotoxy(15, 35);
				cout << pBantuAntrian->next->nama << ", denda " << "$" << listPemain->infoDalamGame.posisi->harga << ", yang dimiliki oleh " << pBantuAntrian->nama << endl;

				//UANG PEMAIN 1 BERKURANG
				if (listPemain->infoDalamGame.uang < listPemain->infoDalamGame.posisi->harga)
				{
					//NGEJUAL PETAK YANG DIA PUNYA
					pointerToMap pBantuJualPetak = listPemain->infoDalamGame.posisi;
					while (true)
					{
						if (strcmp(pBantuJualPetak->namaPemilik, pBantuAntrian->next->nama))
						{
							listPemain->infoDalamGame.uang += pBantuJualPetak->harga;
							listPemain->infoDalamGame.aset -= pBantuJualPetak->harga;
							strcpy(pBantuJualPetak->namaPemilik, "");
						}

						if (listPemain->infoDalamGame.uang >= listPemain->infoDalamGame.posisi->harga)
						{
							listPemain->infoDalamGame.uang -= listPemain->infoDalamGame.posisi->harga;
							break;
						}

						if (listPemain->infoDalamGame.aset == 0)
						{
							namaPemenang = listPemain->next->nama;
							break;
						}

						pBantuJualPetak = pBantuJualPetak->next;
					}
				}
				else
				{
					listPemain->infoDalamGame.uang -= listPemain->infoDalamGame.posisi->harga;
				}

				//UANG PEMAIN 2 BERTAMBAH
				listPemain->next->infoDalamGame.uang += listPemain->infoDalamGame.posisi->harga;
			}
			else
			{
				gotoxy(15, 35);
				cout << "                                                        " << endl;
				//MAU BELI PETAK INI?
				gotoxy(15, 35);
				cout << pBantuAntrian->next->nama << ", denda " << "$" << listPemain->next->infoDalamGame.posisi->harga << ", yang dimiliki oleh " << pBantuAntrian->nama << endl;

				//UANG PEMAIN 2 BERKURANG
				if (listPemain->next->infoDalamGame.uang < listPemain->next->infoDalamGame.posisi->harga)
				{
					//NGEJUAL PETAK YANG DIA PUNYA
					pointerToMap pBantuJualPetak = listPemain->next->infoDalamGame.posisi;
					while (true)
					{
						if (strcmp(pBantuJualPetak->namaPemilik, pBantuAntrian->next->nama))
						{
							listPemain->next->infoDalamGame.uang += pBantuJualPetak->harga;
							listPemain->next->infoDalamGame.aset -= pBantuJualPetak->harga;
							strcpy(pBantuJualPetak->namaPemilik, "");
						}

						if (listPemain->next->infoDalamGame.uang >= listPemain->next->infoDalamGame.posisi->harga)
						{
							listPemain->next->infoDalamGame.uang -= listPemain->next->infoDalamGame.posisi->harga;
							break;
						}

						if (listPemain->next->infoDalamGame.aset == 0)
						{
							namaPemenang = listPemain->nama;
							break;
						}

						pBantuJualPetak = pBantuJualPetak->next;
					}
				}
				else
				{
					listPemain->next->infoDalamGame.uang -= listPemain->next->infoDalamGame.posisi->harga;
				}

				//UANG PEMAIN 1 BERTAMBAH
				listPemain->infoDalamGame.uang += listPemain->next->infoDalamGame.posisi->harga;
			}

			Sleep(1000);
			dendaPetak = false;
		}

		//Kalau pemain sebelumnya stop di kartu kesempatan
        if (petakKartuKesempatan)
        {
        	if (pBantuAntrian->next == listPemain)
        	{
        		gotoxy(25, 32);
        		cout << listPemain->infoDalamGame.posisi->infoKartu->isi;
        		Sleep(3000);
        		int indexKartu = getIndexKartuKesempatan(listPemain->infoDalamGame.posisi->infoKartu->isi);	//Ini Index Isi Kartu Kesempatan
        		switch (indexKartu)
        		{
        			case 0:	//bebas dari penjara
        				listPemain->infoDalamGame.kartuBebasPenjara++;
        				break;
        			case 1:	//merdeka, + $15
        				listPemain->infoDalamGame.uang += 15;
        				break;
        			case 2:	//Traktir lawan, -$20
                        listPemain->infoDalamGame.uang -= 20;
                        listPemain->next->infoDalamGame.uang += 20;
        				break;
        			case 3:	//bansos, + $10
                        listPemain->infoDalamGame.uang += 10;
        				break;
        			case 4:	//terima uang $10
        				listPemain->infoDalamGame.uang += 10;
        				break;
        			case 5:	//denda $5
        				listPemain->infoDalamGame.uang -= 5;
        				break;
        			case 6:	//bayar pajak, -$37
                        listPemain->infoDalamGame.uang -= 37;
        				break;
        			case 7:	//ulang tahun, +$8
        				listPemain->infoDalamGame.uang += 8;
        				break;
        			case 8:	//dapet dari lawan, + $16
        				listPemain->infoDalamGame.uang += 16;
                        listPemain->next->infoDalamGame.uang -= 16;
        				break;
        			default:	//denda -$7
        				listPemain->infoDalamGame.uang -= 7;
        				break;
        		}

        		listPemain->infoDalamGame.posisi->infoKartu = listPemain->infoDalamGame.posisi->infoKartu->next;
        	}
        	else
        	{
        		gotoxy(25, 32);
        		cout << listPemain->next->infoDalamGame.posisi->infoKartu->isi;
        		Sleep(3000);
        		int index = getIndexKartuKesempatan(listPemain->next->infoDalamGame.posisi->infoKartu->isi);	//Ini Index Isi Kartu Kesempatan
        		switch (index)
        		{
        			case 0:	//bebas dari penjara
        				listPemain->next->infoDalamGame.kartuBebasPenjara++;
        				break;
        			case 1:	//merdeka, + $15
        				listPemain->next->infoDalamGame.uang += 15;
        				break;
        			case 2:	//Traktir lawan, -$20
                        listPemain->infoDalamGame.uang += 20;
                        listPemain->next->infoDalamGame.uang -= 20;
        				break;
        			case 3:	//bansos, + $10
                        listPemain->next->infoDalamGame.uang += 10;
        				break;
        			case 4:	//terima uang $10
        				listPemain->next->infoDalamGame.uang += 10;
        				break;
        			case 5:	//denda $5
        				listPemain->next->infoDalamGame.uang -= 5;
        				break;
        			case 6:	//bayar pajak, -$37
                        listPemain->next->infoDalamGame.uang -= 37;
        				break;
        			case 7:	//ulang tahun, +$8
        				listPemain->next->infoDalamGame.uang += 8;
        				break;
        			case 8:	//dapet dari lawan, + $16
        				listPemain->infoDalamGame.uang -= 16;
                        listPemain->next->infoDalamGame.uang += 16;
        				break;
        			default:	//denda -$7
        				listPemain->next->infoDalamGame.uang -= 7;
        				break;
        		}

        		listPemain->next->infoDalamGame.posisi->infoKartu = listPemain->next->infoDalamGame.posisi->infoKartu->next;
        	}

        	petakKartuKesempatan = false;
        	gotoxy(25, 32);
        		cout << "                               ";
        }

		if (namaPemenang != "")
		{
			break;
		}

		//SKIP MAIN SAAT DI GDL
		if(strcmp(pBantuAntrian->nama, listPemain->nama) == 0 && petakGDL1 == true)
        {
            pBantuAntrian = pBantuAntrian->next;
            petakGDL1 = false;
            continue;
        }
        if(strcmp(pBantuAntrian->nama, listPemain->next->nama) == 0 && petakGDL2 == true)
        {
            pBantuAntrian = pBantuAntrian->next;
            petakGDL2 = false;
            continue;
        }

		//STATUS PEMAIN
		gotoxy(1, 45);
		cout << char(218) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(191) << endl;
		gotoxy(1, 46);
		cout << char(179) << "Pemain " << left << setw(6) << listPemain->nama << "       " << char(179) << endl;
		gotoxy(1, 47);
		cout << char(179) << "Uang    : $" << left << setw(6) << listPemain->infoDalamGame.uang << "   " << char(179) << endl;
		gotoxy(1, 48);
		cout << char(179) << "Aset    : $" << left << setw(6) << listPemain->infoDalamGame.aset<< "   " << char(179) << endl;
		gotoxy(1, 49);
		cout << char(179) << "Total   : $" << left << setw(6) << listPemain->infoDalamGame.uang + listPemain->infoDalamGame.aset<< "   " << char(179) << endl;
		gotoxy(1, 50);
		cout << char(192) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(217) << endl;

		gotoxy(25, 45);
		cout << char(218) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(191) << endl;
		gotoxy(25, 46);
		cout << char(179) << "Pemain " << left << setw(6) << listPemain->next->nama << "       " << char(179) << endl;
		gotoxy(25, 47);
		cout << char(179) << "Uang    : $" << left << setw(6) << listPemain->next->infoDalamGame.uang << "   " << char(179) << endl;
		gotoxy(25, 48);
		cout << char(179) << "Aset    : $" << left << setw(6) << listPemain->next->infoDalamGame.aset<< "   " << char(179) << endl;
		gotoxy(25, 49);
		cout << char(179) << "Total   : $" << left << setw(6) << listPemain->next->infoDalamGame.uang + listPemain->next->infoDalamGame.aset<< "   " << char(179) << endl;
		gotoxy(25, 50);
		cout << char(192) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(196) << char(217) << endl;

		//RIWAYAT DADU PEMAIN
		printRiwayat(stackRiwayat);

		gotoxy(15, 35);
		cout << "                                                        " << endl;
		//Giliran Pemain X, untuk roll dadu, tekan apa saja

		if (strcmp(pBantuAntrian->nama, "BOT") == 0)
		{
			gotoxy(15, 35);
			cout << "Giliran " << pBantuAntrian->nama << " untuk roll dadu" << endl;
			srand(time(0));
			dadu = 1 + (rand() % 6);
		}
		else
		{
			gotoxy(15, 35);
			cout << "Giliran " << pBantuAntrian->nama << " untuk roll dadu silakan tekan apa saja" << endl;
			keyboardInput = getch();
			if (keyboardInput != NULL)
			{
				//Kondisi kalau pemain klik tombol 'ESC' di keyboard
				if (keyboardInput == 27)
				{
					int totalA = listPemain->infoDalamGame.uang + listPemain->infoDalamGame.aset, totalB = listPemain->next->infoDalamGame.uang + listPemain->next->infoDalamGame.aset;
					if (totalA > totalB)
					{
						namaPemenang = listPemain->nama;
					}
					else if (totalA < totalB)
					{
						namaPemenang = listPemain->next->nama;
					}
					else
					{
						namaPemenang = "DRAW";
					}

					break;
				}

				srand(time(0));
				dadu = 1 + (rand() % 6);
			}
		}

		//KALAU MASUK PENJARA DAN PUNYA KARTU BEBAS PENJARA
		if (pBantuAntrian->infoDalamGame.posisi->kota == "JIL" && pBantuAntrian->infoDalamGame.kartuBebasPenjara > 0)
		{
			dadu = 6;
			pBantuAntrian->infoDalamGame.kartuBebasPenjara--;
		}

		if (strcmp(pBantuAntrian->nama, listPemain->nama) == 0)	//listPemain->nama = Pemain 1
		{
			//KONDISI KALAU LAGI DI JAIL
			if ((pBantuAntrian->infoDalamGame.posisi->kota == "JIL" && dadu == 6) || (pBantuAntrian->infoDalamGame.posisi->kota != "JIL"))
			{
				//YANG DIATUR SI PEMAIN 1
				for (int i = 1; i <= dadu; i++)
				{
					//Posisi Awal Start (2,40)
					//Start -> GRT (2,32) mundur -8
					//GRT -> TSK (2,26) mundur -6
					//STA (2,20)
					//PLN (2,14)
					//BDG (2,8)
					//JIL (2,1)
					if (listPemain->infoKoordinat.x == 2)
					{
						if (listPemain->infoKoordinat.y == 40)
						{
							listPemain->infoKoordinat.x = 2;
							listPemain->infoKoordinat.y -= 8;
						}
						else if (listPemain->infoKoordinat.y == 32 || listPemain->infoKoordinat.y == 26 || listPemain->infoKoordinat.y == 20 || listPemain->infoKoordinat.y == 14)
						{
							listPemain->infoKoordinat.x = 2;
							listPemain->infoKoordinat.y -= 6;
						}
						else if (listPemain->infoKoordinat.y == 8 || listPemain->infoKoordinat.y == 1)
						{
							listPemain->infoKoordinat.x = 12;
							listPemain->infoKoordinat.y = 1;
						}
					}

					//TGR (12,1)
					//DIY (24,1)
					//STB (36,1)
					//KRT (48,1)
					//MLG (60,1)
					//TRV (75,1)
					else if (listPemain->infoKoordinat.y == 1)
					{
						if (listPemain->infoKoordinat.x == 12 || listPemain->infoKoordinat.x == 24 || listPemain->infoKoordinat.x == 36 || listPemain->infoKoordinat.x == 48)
						{
							listPemain->infoKoordinat.x += 12;
							listPemain->infoKoordinat.y = 1;
						}
						else if (listPemain->infoKoordinat.x == 60)
						{
							listPemain->infoKoordinat.x = 75;
							listPemain->infoKoordinat.y = 1;
						}
						else if (listPemain->infoKoordinat.x == 75)
						{
							listPemain->infoKoordinat.x = 76;
							listPemain->infoKoordinat.y = 8;
						}
					}

					//BGR (76,8)
					//PLN (76,14)
					//STC (76,20)
					//MDN (76,26)
					//DPK (76,32)
					else if (listPemain->infoKoordinat.x == 76)
					{
						if (listPemain->infoKoordinat.y == 8 || listPemain->infoKoordinat.y == 14 || listPemain->infoKoordinat.y == 20 || listPemain->infoKoordinat.y == 26)
						{
							listPemain->infoKoordinat.x = 76;
							listPemain->infoKoordinat.y += 6;
						}
						else if (listPemain->infoKoordinat.y == 32)
						{
							listPemain->infoKoordinat.x = 76;
							listPemain->infoKoordinat.y = 40;
						}
						else if (listPemain->infoKoordinat.y == 40)
						{
							listPemain->infoKoordinat.x = 60;
							listPemain->infoKoordinat.y = 41;
						}
					}

					//JKT (12,41)
					//KRT (24,41)
					//STD (36,41)
					//SBY (48,41)
					//BKS (60,41)
					//STR (2,40)
					else if (listPemain->infoKoordinat.y == 41)
					{
						if (listPemain->infoKoordinat.x == 60 || listPemain->infoKoordinat.x == 48 || listPemain->infoKoordinat.x == 36 || listPemain->infoKoordinat.x == 24)
						{
							listPemain->infoKoordinat.x -= 12;
							listPemain->infoKoordinat.y = 41;
						}
						else if (listPemain->infoKoordinat.x == 12)
						{
							listPemain->infoKoordinat.x = 2;
							listPemain->infoKoordinat.y = 40;
						}
					}

					//PINDAH POSISI SECARA DATA DI STRUCT
					listPemain->infoDalamGame.posisi = listPemain->infoDalamGame.posisi->next;
					if (listPemain->infoDalamGame.posisi->kota == "JIL")
						listPemain->infoDalamGame.posisi = listPemain->infoDalamGame.posisi->next;
				}

				//--------------------------------
				//KONDISI DIA MASUK PETAK "ENTER JAIL" PEMAIN 1 (76,40)
				if (listPemain->infoKoordinat.x == 76 && listPemain->infoKoordinat.y == 40)
				{
					listPemain->infoKoordinat.x = 2;
					listPemain->infoKoordinat.y = 1;

					pointerToMap pBantuPemainToJail = listPemain->infoDalamGame.posisi;
					while (true)
					{
						if (pBantuPemainToJail->kota == "JIL")
						{
							listPemain->infoDalamGame.posisi = pBantuPemainToJail;
							break;
						}

						pBantuPemainToJail = pBantuPemainToJail->next;
					}
				}

				//KALAU DI BERHENTI DI PETAK KARTU KESEMPATAN
				if (listPemain->infoDalamGame.posisi->kota == "KRT")
				{
					petakKartuKesempatan = true;
				}
			}

			//SAMPAI DI PETAK GDL
			if(listPemain->infoDalamGame.posisi->kota == "GDL")
            {
                petakGDL1 = true;
            }

			//PEMBELIAN PETAK YANG DITUJU
			if (listPemain->infoDalamGame.posisi->harga != 0 && strcmp(listPemain->infoDalamGame.posisi->namaPemilik, "") == 0)
			{
				petakKosong = true;
			}

			//PETAKNYA ADA NAMA?
			if (strcmp(listPemain->infoDalamGame.posisi->namaPemilik, "") != 0)
			{
				if (strcmp(listPemain->infoDalamGame.posisi->namaPemilik, pBantuAntrian->nama) == 0)
				{
					dendaPetak = false;
				}
				else
				{
					dendaPetak = true;
				}
			}
		}
		else
		{
			if ((pBantuAntrian->infoDalamGame.posisi->kota == "JIL" && dadu == 6) || (pBantuAntrian->infoDalamGame.posisi->kota != "JIL"))
			{
				//YANG DIATUR SI PEMAIN 2
				for (int i = 1; i <= dadu; i++)
				{
					//Posisi Awal Start (2,41)
					//GRT (2,34) mundur -7
					//TSK (2,28) mundur -6
					//STA (2,22)
					//PLN (2,16)
					//BDG (2,10)
					//JIL (2,2)
					if (listPemain->next->infoKoordinat.x == 2)
					{
						if (listPemain->next->infoKoordinat.y == 41)
						{
							listPemain->next->infoKoordinat.x = 2;
							listPemain->next->infoKoordinat.y -= 7;
						}
						else if (listPemain->next->infoKoordinat.y == 34 || listPemain->next->infoKoordinat.y == 28 || listPemain->next->infoKoordinat.y == 22 || listPemain->next->infoKoordinat.y == 16)
						{
							listPemain->next->infoKoordinat.x = 2;
							listPemain->next->infoKoordinat.y -= 6;
						}
						else if (listPemain->next->infoKoordinat.y == 10 || listPemain->next->infoKoordinat.y == 2)
						{
							listPemain->next->infoKoordinat.x = 18;
							listPemain->next->infoKoordinat.y = 1;
						}
					}

					//TGR (18,1)
					//DIY (30,1)
					//STB (42,1)
					//KRT (54,1)
					//MLG (66,1)
					//TRV (76,2)
					else if (listPemain->next->infoKoordinat.y == 1)
					{
						if (listPemain->next->infoKoordinat.x == 18 || listPemain->next->infoKoordinat.x == 30 || listPemain->next->infoKoordinat.x == 42 || listPemain->next->infoKoordinat.x == 54)
						{
							listPemain->next->infoKoordinat.x += 12;
							listPemain->next->infoKoordinat.y = 1;
						}
						else if (listPemain->next->infoKoordinat.x == 66)
						{
							listPemain->next->infoKoordinat.x = 76;
							listPemain->next->infoKoordinat.y = 2;
						}
					}

					//BGR (76,10)
					//PLN (76,16)
					//STC (76,22)
					//MDN (76,28)
					//DPK (76,34)
					else if (listPemain->next->infoKoordinat.x == 76)
					{
						if (listPemain->next->infoKoordinat.y == 2)	// INI KONDISI DI TRAVEL
						{
							listPemain->next->infoKoordinat.x = 76;
							listPemain->next->infoKoordinat.y = 10;
						}
						else if (listPemain->next->infoKoordinat.y == 10 || listPemain->next->infoKoordinat.y == 16 || listPemain->next->infoKoordinat.y == 22 || listPemain->next->infoKoordinat.y == 28)
						{
							listPemain->next->infoKoordinat.x = 76;
							listPemain->next->infoKoordinat.y += 6;
						}
						else if (listPemain->next->infoKoordinat.y == 34)
						{
							listPemain->next->infoKoordinat.x = 75;
							listPemain->next->infoKoordinat.y = 41;
						}
					}

					//JKT (18,41)
					//KRT (30,41)
					//STD (42,41)
					//SBY (54,41)
					//BKS (66,41)
					//STR (2,41)
					else if (listPemain->next->infoKoordinat.y == 41)
					{
						if (listPemain->next->infoKoordinat.x == 66 || listPemain->next->infoKoordinat.x == 54 || listPemain->next->infoKoordinat.x == 42 || listPemain->next->infoKoordinat.x == 30)
						{
							listPemain->next->infoKoordinat.x -= 12;
							listPemain->next->infoKoordinat.y = 41;
						}
						else if (listPemain->next->infoKoordinat.x == 18)
						{
							listPemain->next->infoKoordinat.x = 2;
							listPemain->next->infoKoordinat.y = 41;
						}
						else if (listPemain->next->infoKoordinat.x == 75)
						{
							listPemain->next->infoKoordinat.x = 66;
							listPemain->next->infoKoordinat.y = 41;
						}
					}

					//PINDAH POSISI SECARA DATA DI STRUCT
					listPemain->next->infoDalamGame.posisi = listPemain->next->infoDalamGame.posisi->next;
					if (listPemain->next->infoDalamGame.posisi->kota == "JIL")
						listPemain->next->infoDalamGame.posisi = listPemain->next->infoDalamGame.posisi->next;
				}

				//KALAU DI BERHENTI DI PETAK KARTU KESEMPATAN
				if (listPemain->next->infoDalamGame.posisi->kota == "KRT")
				{
					petakKartuKesempatan = true;
				}
			}

			//SAMPAI DI PETAK GDL
			if(listPemain->next->infoDalamGame.posisi->kota == "GDL")
            {
                petakGDL2 = true;
            }

			//--------------------------------
			//KONDISI DIA MASUK PETAK "ENTER JAIL" PEMAIN 2 (75,41)
			if (listPemain->next->infoKoordinat.x == 75 && listPemain->next->infoKoordinat.y == 41)
			{
				listPemain->next->infoKoordinat.x = 2;
				listPemain->next->infoKoordinat.y = 2;
				pointerToMap pBantuPemainToJail = listPemain->next->infoDalamGame.posisi;
				while (true)
				{
					if (pBantuPemainToJail->kota == "JIL")
					{
						listPemain->next->infoDalamGame.posisi = pBantuPemainToJail;
						break;
					}

					pBantuPemainToJail = pBantuPemainToJail->next;
				}
			}

			//PEMBELIAN PETAK YANG DITUJU
			if (listPemain->next->infoDalamGame.posisi->harga != 0 && strcmp(listPemain->next->infoDalamGame.posisi->namaPemilik, "") == 0)
			{
				petakKosong = true;
			}

			//PETAKNYA ADA NAMA?
			if (strcmp(listPemain->next->infoDalamGame.posisi->namaPemilik, "") != 0)
			{
				if (strcmp(listPemain->next->infoDalamGame.posisi->namaPemilik, pBantuAntrian->nama) == 0)
				{
					dendaPetak = false;
				}
				else
				{
					dendaPetak = true;
				}
			}
		}

		//MASUKKAN RIWAYAT
		pointerToRiwayat newStackRiwayat;
		createElementRiwayat(newStackRiwayat, pBantuAntrian->nama, dadu);
		pushRiwayat(stackRiwayat, newStackRiwayat);

		//Bekerja si Circular Pemain
		pBantuAntrian = pBantuAntrian->next;
		Sleep(3000);
	} while (true);

	cout << endl;
	cout << endl;
	gotoxy(1, 55);
	system("pause");
}

void menuMenang(string namaPemenang)
{
	system("cls");
	int x = 25, y = 1;
	set_cursor(false);
	while (true)
	{
		gotoxy(48, 8);
		cout << "Selamat, " << namaPemenang << "!" << endl;
		gotoxy(53, 10);
		cout << char(219) << char(220) << char(219) << char(219) << char(220) << char(219) << endl;
		gotoxy(44, 11);
		cout << char(219) << char(220) << char(219) << char(220) << char(219) << char(220) << char(219) << char(220) << char(219) << char(222) << char(219) << char(197) << char(219) << char(219) << char(221) << char(219) << char(220) << char(219) << char(220) << char(219) << char(220) << char(219) << char(220) << char(219) << endl;
		gotoxy(44, 12);
		cout << char(219) << char(219) << char(219) << char(197) << char(219) << char(219) << char(219) << char(219) << char(219) << char(222) << char(219) << char(219) << char(219) << char(219) << char(221) << char(219) << char(219) << char(219) << char(219) << char(219) << char(197) << char(219) << char(219) << char(219) << endl;
		gotoxy(44, 13);
		cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(222) << char(219) << char(219) << char(219) << char(219) << char(221) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << endl;
		gotoxy(x, 15);
		cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << endl;
		gotoxy(x, y);
		cout << char(249) << "    " << char(176) << "    " << char(177) << "    " << char(178) << "    " << char(219) << "    " << char(186) << "    " << char(179) << "    " << char(186) << "    " << char(219) << "    " << char(178) << "    " << char(177) << "    " << char(176) << "    " << char(249) << endl;
		Sleep(500);
		y++;
		if (y == 6)
		{
			gotoxy(x, y);
			cout << "                                                             " << endl;
			y--;
			gotoxy(x, y);
			cout << "                                                             " << endl;
			y--;
			gotoxy(x, y);
			cout << "                                                             " << endl;
			y--;
			gotoxy(x, y);
			cout << "                                                             " << endl;
			y--;
			gotoxy(x, y);
			cout << "                                                             " << endl;
			y--;
		}

		if (kbhit())
			break;
	}

	gotoxy(x, 16);
	cout << "";
	gotoxy(x, 20);
	system("pause");
}

void clearAllDataPemain(char &jumlahPemain, pointerToPemain &listPemain, antrian &qPemain)
{
	jumlahPemain = '0';
	listPemain = NULL;
	createQueuePemain(qPemain);
}

main()
{
	//Deklarasi Variable Biasa
	char indexMenuAwal = '0', jumlahPemain = '0';
	string namaPemenang;

	//Deklarasi Pointer dan Sejenisnya
	pointerToPemain listPemain = NULL;
	antrian qPemain;

	listKartu lKartu;
	pointerToKartuKesempatan pKartu;

	listMap lMap;
	pointerToMap pMap;

	pointerToRiwayat stackRiwayat;

	//Load Data Kartu Kesempatan
	createListKartu(lKartu);
	createElementKartu(lKartu, pKartu);

	//Create Riwayat
	createRiwayat(stackRiwayat);

	//Load Data Map
	createListMap(lMap);
	createElementMap(lMap, pMap, lKartu);

	do {
		system("cls");
		switch (indexMenuAwal)
		{
			case '0':
				set_cursor(true);
				tampilanMenuUtama();
				cout << endl;
				cout << "MASUKKAN PILIHAN : ";
				cin >> indexMenuAwal;
				cout << endl;
				set_cursor(false);
				system("pause");
				break;
			case '1':
				menuPilih1atau2Pemain(jumlahPemain);
				menuInputNamaPemain(listPemain, lMap, jumlahPemain);
				Sleep(1000);
				randomUrutanPemain(listPemain, qPemain);
				menuMap(qPemain, listPemain, stackRiwayat, namaPemenang);
				menuMenang(namaPemenang);
				indexMenuAwal = '0';
				break;
			case '2':
				tampilanMenuTentang();
				indexMenuAwal = '0';
				break;
			default:
				indexMenuAwal = '0';
				system("cls");
				break;
		}

		if (indexMenuAwal == '3') tampilanMenuKeluar();
		clearAllDataPemain(jumlahPemain, listPemain, qPemain);
	} while (indexMenuAwal != '3');
}
