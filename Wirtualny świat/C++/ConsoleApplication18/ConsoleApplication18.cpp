// ConsoleApplication18.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "swiat.h"
//#include <windows.h>


int main() 
{
	//SetConsoleTitle("Wirtualny Swiat");
	system("Title Krzysztof Chobot");
	swiat* swiat1 = new swiat;	
	swiat1->start(*swiat1);
	cout << "nacisnij enter aby rozpoczac gre\n";
	getchar();
	swiat1->rysujSwiat();
	while (true){
	getchar();
	system("cls");
	swiat1->gra();
	swiat1->rysujSwiat();		
	}
	cout << "koniec";
    return 0;
}

