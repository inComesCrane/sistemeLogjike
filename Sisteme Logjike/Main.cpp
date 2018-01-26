
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\glut.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Gjendje.h"

#include <iostream>
#include <sstream> // per istringstream
#include <fstream> // per ifstream

#include <vector>
//#include <string> eshte e deklaruar ne Gjendje.h

using namespace std;
							// prototipe funksionesh
void display();
void init();
void keyboard(unsigned char key, int x, int y);
void ndertoGraf(int);
void lexoNeVektor(string s, vector <int> &v);

							// OpenGL Variables
float kendiX = 0.0;
float kendiY = 0.0;
float kendiZ = 0.0;
int rreze = 20;
int splice = 10;
float largesi = 40.0;

double colors[4][3] = {
	{ 0.36, 0.93, 0.61 }, // gjendja fillestare, jeshile
	{ 1.0, 0.82, 0.15 }, // gjenjdet e ndermjetme, e verdhe
	{ 0.15, 0.65, 0.98 }, // gjendjet fundore, blu
	{ 0.98, 0.36, 0.4 } // gjendja e error-it, e kuqe
};


int main() {

	ifstream input("Te Dhena.txt", ios::in);
	vector <int> hyrje; // mban shifrat e hyrjes se vogel qe do kerkojme
	vector <int> sekBinare; // mban shifrat e sekuences binare ku po kerkojme hyrjen

	if (!input.is_open()) { // kontroll nqs e gjejme/hapim file-in e inputit
		cout << "File-i nuk u hap!";
		exit(1);
	}

	else { //dmth u hap file-i

		string in_line; // stringu ku do mbajme hyrjen nga file-i rresht pas rreshti
		
		cout << "\n\t Duke lexuar te dhenat...";
		cout << "\n -------------------------------------------";
		int i = 1; // mban rreshtin ku jemi aktualisht
		while (input >> in_line) {
			if (i == 2) // dmth jemi te rreshti 2
				lexoNeVektor(in_line, hyrje);

			else if (i == 5)   // dmth jemi te rreshti 5
				lexoNeVektor(in_line, sekBinare);
			
			i++;
		}
		for (i = 0; i < hyrje.size(); i++) {
			if (hyrje[i] != 1 && hyrje[i] != 0) { // nqs shifra nuk eshte 0 ose 1
				cout << "\n\n Hyrja permban shifra qe nuk jane 0/1. Rregulloni hyrjen dhe provoni perseri. \n\n";
				return 0;
			}
		}
		cout << endl;
		for (i = 0; i < sekBinare.size(); i++) {
			if (sekBinare[i] != 1 && sekBinare[i] != 0) { // nqs shifra nuk eshte 0 ose 1
				cout << "\n\n Sekuenca binare permban shifra qe nuk jane 0/1. Rregulloni sekuencen dhe provoni perseri. \n\n ";
				return 0;
			}
		}
		cout << "Inputi u lexua me sukses! \n";
	} // end leximin e file-it te inputit
	
	//------------------------------------------------------------------------------------------

	Gjendje gj[6];
	Gjendje *fundit0, *fundit1; // gjendjet e fundit ku jane gjetur sekuencat 0 dhe 1
	const int GJATESI = hyrje.size();

	if (hyrje[0] == 0) { // kontrollo per shifren e pare, ketu eshte 0

		gj[0].setPasardhes(1, gj[0]); // kalimi me 1 na le tek A
		gj[0].setPasardhes(0, gj[1]); // kalimi me 0 na con tek gjendja e rradhes, B

		gj[0].setRezultat(0, 0); // te gjitha klaimet japin rezultat 0 ne kete moment
		gj[0].setRezultat(1, 0);

		gj[0].setSekuence("1");
		gj[1].setSekuence("0");

		fundit0 = &gj[1]; // dmth gjendja B, se tek ajo kalojme me 0 dhe ka sek 0
		fundit1 = &gj[0]; // dmth gjendja A, se ajo ka sek 1
	}
	else { // shifra e pare ishte 1

		gj[0].setPasardhes(0, gj[0]); // kalimi me 0 na le tek A
		gj[0].setPasardhes(1, gj[1]); // kalimi me 1 na con tek gjendja e rradhes, B

		gj[0].setRezultat(0, 0); // te gjitha klaimet japin rezultat 0 ne kete moment
		gj[0].setRezultat(1, 0);

		gj[0].setSekuence("0");
		gj[1].setSekuence("1");

		fundit0 = &gj[0]; // dmth gjendja A
		fundit1 = &gj[1]; // dmth gjendja B

	/*	Gjendje *tmp = gj[0].getPasardhes(1); cout << "tmp: ";
		tmp->afishoGjendje();*/
	}
	cout << "\n fundit 0: "; fundit0->afishoGjendje();
	cout << "\n fundit 1: "; fundit1->afishoGjendje();
	cout << "\nGjendja 0: \n";
	gj[0].afishoGjendje();
	
	for (int i = 1; i < GJATESI; i++) {
		
		if (hyrje[i] == 0){   // nqs shifra e rradhes eshte 0

			gj[i].setPasardhes(0, gj[i + 1]); // do kalojme te gjendja pasardhese i+1 me 0
			gj[i].setPasardhes(1, *fundit1);  
			
			if (i == GJATESI - 1) // dmth jemi te fundi
				gj[i].setRezultat(0, 1);
			else
				gj[i].setRezultat(0, 0);
			gj[i].setRezultat(1, 0);
			string s = gj[i].getSekuence();
			s.append("0");
			//cout << s;
			gj[i + 1].setSekuence(s);
		}
		else {   // dmth shifra e rradhes eshte 1
			gj[i].setPasardhes(1, gj[i + 1]); // do kalojme te gjendja pasardhese, dmth i+1, me ane te 0
			gj[i].setPasardhes(0, *fundit0);

			if (i == GJATESI - 1) // dmth jemi te fundi
				gj[i].setRezultat(1, 1); // do kemi kalim me rezultat 1
			else
				gj[i].setRezultat(1, 0);
			gj[i].setRezultat(0, 0);
			string s = gj[i].getSekuence();
			s.append("0");
			//cout << s;
			gj[i + 1].setSekuence(s);
		}

		cout << "Gjendja: " << i << endl;
		gj[i].afishoGjendje();
	}




	return 0;

}

void lexoNeVektor(string s, vector <int> &v) {
	stringstream ss_line(s); // perdorim stringstream qe te kapim shifrat
	int len = s.length();
	for (int i = 0; i < len; i++) {
		char tmp = ss_line.get(); // merr shifren e rradhes
		int itmp = tmp - '0'; // konverto nga char ne int
		v.push_back(itmp); // shto tek vektori
	}
}
