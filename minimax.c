#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_damier(char damier[9])
{
	int i;
	for(i = 0; i<9; i++)
		damier[i]= i+49;
}

void affiche_damier(char damier[9])
{
	printf("|---|---|---|\n");
	for(int i=6; i<9; i++)
		printf("| %c ",damier[i]);
	printf("|\n|---|---|---|\n");
	for(int i=3; i<6; i++)
		printf("| %c ",damier[i]);
	printf("|\n|---|---|---|\n");
	for(int i=0; i<3; i++)
		printf("| %c ",damier[i]);
	printf("|\n|---|---|---|\n");
}

void jouer(char damier[9], int joueur, int *tour)
{
	int y, ok = 0;
	while(ok == 0)
	{
		printf("Quelle case :\n");
		scanf("%d", &y);
		y--;
		if(y < 0 || y > 8)
		{
			printf("erreur valeurs\n");
		}
		else if(damier[y] == 'X' || damier[y] == 'O')
		{
			printf("case déjà occupée\n");
		}
		else
		{
			if(joueur == 1)
			damier[y] = 'X';
			else damier[y] = 'O';
			ok = 1;
		}
	}
	(*tour)++;
}

int gagner(char damier[9])
{

	if(damier[4] == damier[0] && damier[0]==damier[8])
		return 1;
	if(damier[4] == damier[2] && damier[2]==damier[6])
		return 1;
	for(int i = 0; i<3;i++)
	{
		if(damier[i] == damier[3+i] && damier[i]==damier[i+6])//colonne
			return 1;
		if(damier[0+3*i] == damier[1+3*i] && damier[0+3*i]==damier[2+3*i])//ligne
			return 1;
	}
	return 0;
}



int score(char damier[9], int joueur)
{
	if(joueur == 0 && gagner(damier))
		return 10;
	if(joueur == 1 && gagner(damier))
		return -10;
	return 0;
}

int main(void){
	char damier[9];
	init_damier(damier);
	int joueur = 1;
	int fin = 0;
	int tour = 0;
	system("clear");
	affiche_damier(damier);
	while(fin == 0)
	{
		jouer(damier, joueur, &tour);
		system("clear");
		affiche_damier(damier);
		if(gagner(damier) == 1)
		{
			fin = 1;
			printf("joueur %d a gagné !!!\n", joueur);
		}
		else if(tour == 9)
		{
			fin = 1;
			printf("match nul");
		}
		joueur = (joueur == 1) ? 2 : 1;
		
	}
	return 0;
}







/******

111000000 : ligne >> 3
000111000
000000111
100010001 : diagonale
001010100
100100100 : colone >>
010010010
001001001
****/
