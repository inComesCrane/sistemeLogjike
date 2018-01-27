#include "Gjendje.h"
#include <string>
#include <iostream>

Gjendje::Gjendje() // constructor
{
}

Gjendje::~Gjendje() // destrcutor
{
}

Gjendje * Gjendje::getPasardhes(int i)
{
	return this->pas[i];
}

void Gjendje::setPasardhes(int i, Gjendje &gj)
{
	this->pas[i] = &gj;
}

int Gjendje::getRezultat(int i)
{
	return this->rezultat[i];
}

void Gjendje::setRezultat(int i, int vlere)
{
	this->rezultat[i] = vlere;
}

std::string Gjendje::getSekuence()
{
	return this->sek;
}

void Gjendje::setSekuence(std::string s)
{
	this->sek = s;
}

void Gjendje::appendSekuence(std::string s)
{
	this->sek.append(s);
}

char Gjendje::getEmer()
{
	return this->emer;
}

void Gjendje::setEmer(char c)
{
	this->emer = c;
}

void Gjendje::afishoGjendje()
{
	std::cout << "Gjendja: " << this << "\n";
	std::cout << "Emri: " << this->emer << "\n";
	std::cout << "Kalimi me 0: " << this->pas[0] << " me rezultat " << rezultat[0] << "\n";
	std::cout << "Kalimi me 1: " << this->pas[1] << " me rezultat " << rezultat[1] << "\n";
	std::cout << "Sekuenca: " << this->sek << "\n\n";
}
