#define _USE_MATH_DEFINES

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\glut.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Gjendje.h"
#include <cmath>
#include <iostream>
#include <sstream> // per istringstream, per manipulim inputi
#include <fstream> // per ifstream, per input nga skedar

#include <vector>
#include <string>

using namespace std;
								// prototipe funksionesh
void display();
void init();

void ndertoGraf(int);
void krijoHark(float, float, int);
void krijoVije(float, float, int);
void krijoRreth(float, int);

void lexoNeVektor(string s, vector <int> &v);
string konvertoBinar(int);

								// VARIABLA OpenGL

float rreze = 40.0;				// rrezja e gjendjeve	
int splice = 12;
float largesi = 80.0;			// distanca mes gjendjeve
vector <float> pozicione;		// koordinatat x te gjendjeve


double colors[4][3] = {
	{ 0.36, 0.93, 0.61 },		// kalim me 0 perpara, jeshile e lehte, 0
	{ 0.33, 0.69, 0.43 },		// kalim me 0 mbrapa, jeshile e erret, 1
	{ 1.0, 0.82, 0.15 },		// kalim me 1 perpara, e verdhe e lehte, 2
	{ 0.84, 0.75, 0.3 }		    // kalim me 1 mbrapa, e verdhe e erret, 3
};
														// VARIABLA

vector <int> hyrje;										// do te mbaje shifrat e hyrjes se vogel qe do kerkojme
vector <int> sekBinare;									// do te mbaje shifrat e sekuences binare ku po kerkojme hyrjen
string s_hyrje;											// hyrja e ruajtur edhe si string per lehtesi veprimesh me poshte ne kod
Gjendje gj[7];											// array me deri ne 7 gjendje qe do na duhen


int main(int argc, char **argv) {

	ifstream input("Te Dhena.txt", ios::in);
	if (!input.is_open()) {								// kontrollojme nqs e gjejme/hapim file-in e inputit
		cout << "File-i nuk u hap!";
		exit(1);
	}

	else {										// u hap file-i

		string in_line;							// stringu ku do mbajme hyrjen nga file-i rresht pas rreshti

		cout << "\n\t Duke lexuar te dhenat...";
		cout << "\n-------------------------------------------";

		int rreshti = 1;						// mban rreshtin ku jemi duke lexuar aktualisht ne file
		while (input >> in_line) {				// kontrollon nqs jemi ne fund te file-it dhe njekohesisht merr rreshtin e rradhes
			if (rreshti == 2) {					
				lexoNeVektor(in_line, hyrje);	// hyrja ruhet shifer pas shifre ne nje vektor
				s_hyrje = in_line;				// hyrja ruhet dhe e tera ne nje string per lehtesi me poshte
			}
			else if (rreshti == 5) {			// dmth jemi te rreshti 5
				lexoNeVektor(in_line, sekBinare);
			}
			rreshti++;
		}			

		if (hyrje.empty()) {
			cout << "\n\n Hyrja nuk mund te jete bosh! Rregulloni hyrjen dhe provoni perseri. \n\n";
			return 0;
		}
		if (hyrje.size() < 2 || hyrje.size() > 6) {
			cout << "\n\n Hyrja nuk mund te jete me e vogel se 2 ose me e madhe se 6 shifra! Rregulloni hyrjen dhe provoni perseri. \n\n";
			return 0;
		}
		if (sekBinare.empty()) {
			cout << "\n\n Sekuenca binare nuk mund te jete bosh! Rregulloni sekuencen dhe provoni perseri. \n\n";
			return 0;
		}
		for (int i = 0; i < hyrje.size(); i++) {			// kontrollojme gjithe shifrat e hyrjes per input te padeshiruar
			if (hyrje[i] != 1 && hyrje[i] != 0) {			// nqs shifra nuk eshte 0 ose 1
				cout << "\n\n Hyrja permban shifra qe nuk jane 0/1. Rregulloni hyrjen dhe provoni perseri. \n\n";
				return 0;
			}
		}
		for (int i = 0; i < sekBinare.size(); i++) {
			if (sekBinare[i] != 1 && sekBinare[i] != 0) {	// nqs shifra nuk eshte 0 ose 1
				cout << "\n\n Sekuenca binare permban shifra qe nuk jane 0/1. Rregulloni sekuencen dhe provoni perseri. \n\n ";
				return 0;
			}
		}
		if (sekBinare.size() < hyrje.size()) {
			cout << "\n\n Sekuenca binare nuk mund te jete me e vogel se hyrja! Rregulloni inputin dhe provoni perseri.\n";
			return 0;
		}
		cout << "\n  Inputi u lexua me sukses! \n";
	} // end leximin e file-it te inputit

	
	bool afisho_tek_e_thjeshtuar[7] = { true,true,true,true,true,true,true }; // nqs vlear eshte true atehere gjendja koresponduese do te afishohet te tabela e thjeshtuar
	char emraGjendje[7] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	Gjendje *fundit0, *fundit1, *gjFundit;				// gjendjet e fundit ku jane gjetur sekuencat 0 dhe 1, si dhe gjendja e fundit e automatit
	const int H_GJATESI = hyrje.size();
	const int S_GJATESI = sekBinare.size();

														// ndertimi i gjendjes se pare
	if (hyrje[0] == 0) {				// kontrollo per shifren e pare, ketu eshte 0

		gj[0].setPasardhes(1, gj[0]);	// kalimi me 1 na le tek A
		gj[0].setPasardhes(0, gj[1]);	// kalimi me 0 na con tek gjendja e rradhes, B

		gj[0].setRezultat(0, 0);		// te gjitha kalimet japin rezultat 0 ne kete moment
		gj[0].setRezultat(1, 0);

		gj[0].setSekuence("1");
		gj[1].setSekuence("0");

		fundit0 = &gj[1];				// dmth gjendja B, se tek ajo kalojme me 0 dhe ka sek 0
		fundit1 = &gj[0];				// dmth gjendja A, se ajo ka sekuence 1
	}
	else {								// shifra e pare ishte 1

		gj[0].setPasardhes(0, gj[0]);	// kalimi me 0 na le tek vetja
		gj[0].setPasardhes(1, gj[1]);	// kalimi me 1 na con tek gjendja e rradhes, B

		gj[0].setRezultat(0, 0);		// te gjitha kalimet japin rezultat 0 ne kete moment
		gj[0].setRezultat(1, 0);

		gj[0].setSekuence("0");			// per kete gjendje
		gj[1].setSekuence("1");			// per gjendjen e rradhes

		fundit0 = &gj[0];				// dmth gjendja A
		fundit1 = &gj[1];				// dmth gjendja B
	}
	gj[0].setEmer('A');					// vendosi emrin A
	
	int i;
	for (i = 1; i < H_GJATESI; i++) {			// nga shifra e dyte e hyrjes deri ne fund te saj, pasi shifra e pare eshte trajtuar me siper
		if (hyrje[i] == 0) {					// nqs shifra e rradhes eshte 0
			gj[i].setPasardhes(0, gj[i + 1]);	// do kalojme te gjendja pasardhese i+1 me 0
			gj[i].setPasardhes(1, *fundit1);

			if (i == H_GJATESI - 1)				// dmth jemi te fundi i hyrjes
				gj[i].setRezultat(0, 1);
			else
				gj[i].setRezultat(0, 0);
			gj[i].setRezultat(1, 0);

			string s = gj[i].getSekuence();
			s.append("0");
			gj[i + 1].setSekuence(s);
		}										// e njejte si if por kur shifra e hyrjes eshte 1
		else {									// dmth shifra e rradhes eshte 1
			gj[i].setPasardhes(1, gj[i + 1]);	// do kalojme te gjendja pasardhese, dmth i+1, me ane te 0
			gj[i].setPasardhes(0, *fundit0);

			if (i == H_GJATESI - 1)				// dmth jemi te fundi i hyrjes
				gj[i].setRezultat(1, 1);		// do kemi kalim me rezultat 1
			else
				gj[i].setRezultat(1, 0);
			gj[i].setRezultat(0, 0);

			string s = gj[i].getSekuence();
			s.append("1");
			gj[i + 1].setSekuence(s);
		}							
		gjFundit = &gj[i + 1];					
		gj[i].setEmer(emraGjendje[i]);					// vendosi nje char si emer (nga array ku mbajme char te perdorshem per emra)
	}
	gjFundit->setEmer(emraGjendje[i]);

														// Ndertimi i Kalimeve te Gjendjes se Fundit
	string s = gjFundit->getSekuence();
	s.append("0");										// do shofim ku do shkoje me kalim me 0
	for (int i = 1; i < H_GJATESI; i++) {				// fillon nga i qe ne substring te mos kapim shifren e pare te sekuences por nga e dyta deri ne fund
		bool found = false;
		string sub_sekuence = s.substr(i);				// substring i tere sekuences se gjendjes se fundit, nga shifra e i-te deri ne fund

		for (int j = H_GJATESI; j >= 0; j--) {			// kerko mbrapsht ne vektorin e gjendjeve derisa gjen nje me sekuence si e jona
			if (gj[j].getSekuence() == sub_sekuence) {
				found = true;
				gjFundit->setPasardhes(0, gj[j]);		// meqe sekuenca eshte njelloj, do kalojme me 0 ketu
				if (sub_sekuence == s_hyrje)			// nqs substringu i sekuences plus 0'ne qe i beme append eshte sa hyrja, do te thote se rezultati i kalimit do jete 1
					gjFundit->setRezultat(0, 1);
				else
					gjFundit->setRezultat(0, 0);		// perndryshe rezultati do jete 0
				break;
			}
		}
		if (found)
			break;

		if (i == H_GJATESI - 1 && !found) {			// nqs jemi ne fund dhe s'kemi gjetur gje
			gjFundit->setPasardhes(0, *fundit0);	// do te thote se kalimi me 0 do na coj te vendi i fndit ku sekuenca ishte vtm 0
			gjFundit->setRezultat(0, 0);
		}
	}

														// e njejta gje si me siper, vetem se per kalimin me 1
	s = gjFundit->getSekuence();
	s.append("1");
	for (int i = 1; i < H_GJATESI; i++) {
		bool found = false;
		string sub_sekuence = s.substr(i);

		for (int j = H_GJATESI; j >= 0; j--) {
			if (gj[j].getSekuence() == sub_sekuence) {
				found = true;
				gjFundit->setPasardhes(1, gj[j]);
				if (sub_sekuence == s_hyrje)
					gjFundit->setRezultat(1, 1);
				else
					gjFundit->setRezultat(1, 0);
				break;
			}
		}
		if (found)
			break;

		if (i == H_GJATESI - 1 && !found) {			// jemi ne fund dhe s'kemi gjetur gje
			gjFundit->setPasardhes(1, *fundit1);
			gjFundit->setRezultat(1, 0);
		}
	}												// mbaron krijimi i automatit te gjendjeve, gjendjet u lidhen me njera tjetren

														// gjejme vendndodhjen e hyrjes ne sekuencen binare qe morem si input
	Gjendje *gjTani = &gj[0];							// do bredhim neper gjendje duke filluar nga e para, dmth gjendja A
	for (int i = 0; i < S_GJATESI; i++) {
		if (sekBinare[i] == 0)
			gjTani = gjTani->getPasardhes(0);
		else									// dmth sekBinare[i] == 1
			gjTani = gjTani->getPasardhes(1);

		if (gjTani == gjFundit) {				// dmth jemi ne fund te hyrjes
			cout << "\n 1! Pozicioni i hyrjes: " << i - hyrje.size() + 2; // afishojme pozicionin e shifres se pare te hyrjes
		}
	}

	cout << "\n-------------------------------------------\n";;
	cout << "\n\t Tabela e Gjendjeve: \n\n";
	cout << "Kodimi\t" << "Gjendja\t" << "X = 0\t" << "X = 1\t" << "Rez. 0\t" << "Rez. 1\n"; //formatuar cuditshem qe te jete me i lexueshem
	cout << "-------------------------------------------------------\n";
	for (int i = 0; i <= H_GJATESI; i++) {														// kap te gjithe gjendjet
		cout << konvertoBinar(i) << "\t" << emraGjendje[i] << "\t"								// afisho te dhenat e tyre
			<< gj[i].getPasardhes(0)->getEmer() << "\t" << gj[i].getPasardhes(1)->getEmer() << "\t" 
			<< gj[i].getRezultat(0) << "\t" << gj[i].getRezultat(1) << endl << endl;
	}

	// Krijimi i tabeles se thjeshtuar te gjendjeve
	for (int i = 0; i <= H_GJATESI; i++) {
		for (int j = i+1; j <= H_GJATESI; j++) {
			if (gj[i] == gj[j])							// gjej gjendjet qe jane njelloj
				afisho_tek_e_thjeshtuar[j] = false;		// dhe shenoji qe te mos afishohen				
		}
	}

	cout << "\n\t Tabela e Thjeshtuar e Gjendjeve: \n\n";
	cout << "Kodimi\t" << "Gjendja\t" << "X = 0\t" << "X = 1\t" << "Rez. 0\t" << "Rez. 1\n";
	cout << "-------------------------------------------------------\n";
	for (int i = 0; i <= H_GJATESI; i++) {
		if (afisho_tek_e_thjeshtuar[i]) {
			cout << konvertoBinar(i) << "\t" << emraGjendje[i] << "\t"
				<< gj[i].getPasardhes(0)->getEmer() << "\t" << gj[i].getPasardhes(1)->getEmer() << "\t"
				<< gj[i].getRezultat(0) << "\t" << gj[i].getRezultat(1) << endl << endl;
		}
	}

	
															// NDERTIMI I DIAGRAMES me OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	
	glutInitWindowPosition(650, 150);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Grafiku i Gjendjeve");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}


void lexoNeVektor(string s, vector <int> &v) {
	stringstream ss_line(s); // perdorim stringstream qe te kapim shifrat
	size_t len = s.length();
	for (int i = 0; i < len; i++) {
		char tmp = ss_line.get(); // merr shifren e rradhes
		int itmp = tmp - '0'; // konverto nga char ne int
		v.push_back(itmp); // shto tek vektori
	}
}
string konvertoBinar(int nr) {
	vector <int> v;
	int mbetje = 0;
	string binar;
	do {
		mbetje = nr % 2;
		nr = nr / 2;
		v.push_back(mbetje);
	} while (nr != 0);
	for (int i = v.size() - 1; i >= 0; i--) { // lexo mbrapsht vektorin
		char tmp = '0' + v[i];
		binar.push_back(tmp);
	}
	return binar;
}


void init() {
	glClearColor(237, 236, 227, 1);
	glViewport(0, 0, 800, 600);
	glOrtho(-600.0, 600.0, -500.0, 500.0, -500.0, 500.0);
	glMatrixMode(GL_PROJECTION | GL_DEPTH);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ndertoGraf(hyrje.size() + 1);						// nderto sferat dhe ruaj koordinatat x te tyre

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.1);
	for (int i = 0; i < hyrje.size(); i++) {			// harqet qe do te lidhin gjendjet e tjera
		if (gj[i].rriNeVend(0))							// nqs gjendja rri tek vetja kur kalon me 0
			krijoRreth(pozicione[i], 0);
		if (gj[i].rriNeVend(1))
			krijoRreth(pozicione[i], 1);
	}
	
	for (float i = 0; i < hyrje.size(); i++) {			// vijat qe lidhin gjendjet me shifrat e hyrjes
		krijoVije(pozicione[i], pozicione[i + 1], hyrje[i]);
	}

	for (int i = hyrje.size(); i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			if (gj[i].getPasardhes(0) == &gj[j])		// nqs gjendja i kalon te j me 0
				krijoHark(pozicione[i], pozicione[j], 0);
			if (gj[i].getPasardhes(1) == &gj[j])		// nqs gjendja i kalon te j me 1
				krijoHark(pozicione[i], pozicione[j], 1);
		}		
	}

	glFlush();
}

void ndertoGraf(const int nrGjendje) {									// ndertimi i sferave qe paraqesinn gjendjet
	float zhvendosX = -0.5 * (nrGjendje - 1) * (rreze * 2 + largesi);	// qenderzo
	glColor4d(0.25, 0.46, 0.83, 1.0);
	for (int i = 0; i < nrGjendje; i++) {
		glPushMatrix();
			pozicione.push_back(zhvendosX);								// mbaj koordinaten x te qendres se sferes
			glTranslatef(zhvendosX, 1.0, 1.0);
			glutWireSphere(rreze, splice, splice);						// vizato gjendjet si sfera
		glPopMatrix();

		zhvendosX += 2 * largesi;
	}
}

void krijoHark(float x1, float x2, int kalim) {							// ndertimi i harqeve qe paraqesin kalimet mbrapa
	float pi = M_PI;
	float rr = (x2 - x1) / 2;

	int ngjyre = 0;
	if (kalim == 0)
		ngjyre = 1;
	else
		ngjyre = 3;

	glPushMatrix(); 
		glColor4d(colors[ngjyre][0], colors[ngjyre][1], colors[ngjyre][2], 1);
		glTranslatef(x1 + rr, rreze, 1.0);		// zhvendos harkun
		glRotatef(-90.0, 0.0, 0.0, 1.0);

		glBegin(GL_LINES);						// nderto harkun
			for (float i = 0.0; i <= pi; i += 0.001)
				glVertex3f((sin(i)*rr), (cos(i)*rr), 1.0);
		glEnd();
	glPopMatrix();
}

void krijoVije(float x1, float x2, int kalim) {						// ndertimi i vijave qe tregojne kalimet para
	int ngjyre = 0;
	if (kalim == 0)
		ngjyre = 0;
	else
		ngjyre = 2;

	glPushMatrix();					
		glColor4d(colors[ngjyre][0], colors[ngjyre][1], colors[ngjyre][2], 1);
		glTranslatef(rreze, 1.0, 1.0);			// zhvendos vijen
	
		glBegin(GL_LINES);						// nderto vijen
			glVertex3d(x1-rreze, 0.0, 1.0);
			glVertex3d(x2-rreze, 0.0, 1.0);
		glEnd();
	glPopMatrix();
}

void krijoRreth( float x, int kalim) {							// nderton rathet qe tregojne kalimet qe e lene ne vete
	int ngjyre = 0;
	if (kalim == 0)
		ngjyre = 0;
	else
		ngjyre = 2;

	glPushMatrix();
		glColor4d(colors[ngjyre][0], colors[ngjyre][1], colors[ngjyre][2], 1);
		glTranslatef(x, -rreze, 1.0);
		glBegin(GL_LINES);
			for (float i = 0.0; i < 2 * M_PI; i += 0.001)
				glVertex3f(cos(i) * rreze, sin(i) * rreze, 1.0);
		glEnd();
	glPopMatrix();
}