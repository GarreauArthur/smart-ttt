#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define C_PLAYER 0
#define H_PLAYER 1
#define C_SYMBOLE 'X'
#define H_SYMBOLE 'O'

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

void jouer(char damier[9], int joueur)
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
			if(joueur == H_PLAYER)
			damier[y] = H_SYMBOLE;
			else damier[y] = C_SYMBOLE;
			ok = 1;
		}
	}
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
	if(joueur == C_PLAYER && gagner(damier))
		return 10;
	if(joueur == H_PLAYER && gagner(damier))
		return -10;
	return 0;
}

int minimax(char damier[9], int joueur)
{
	// si la partie est finie, on retourne le score
	int gagne = score(damier,joueur);
	if(gagne != 0)
		return gagne;	
	// si la partie n'est pas finie, on joue de nouveau coup
	int score = -1;
	int coup = -1;
	for(int i = 0; i<9; i++)
	{
		if(damier[i] != C_SYMBOLE && damier[i] != H_SYMBOLE)
		{
			char sym;
			int p;
			if(joueur == C_PLAYER)
			{
				sym =  H_SYMBOLE;
				p = C_PLAYER; 
			}
			else{
				sym = C_SYMBOLE;
				p = H_PLAYER;
			}
			damier[i] = sym;	
			int tempScore = minimax(damier, p);
			if(tempScore > score){
				score = tempScore;
				coup = i;
			}
			damier[i] = i+49;	
		}
	}
	if(coup == -1) return 0;
	return score;
}

void coupOrdi(char damier[9])
{
	int coup = -1;
	int score = -1;
	// on parcourt toute la grille
	for(int i = 0; i<9;i++)
	{
		// si la case est vide
		if(damier[i] != C_SYMBOLE && damier[i] != H_SYMBOLE)
		{
			damier[i] = C_SYMBOLE;
			//on calcule le meilleur score envisageable
			int tempScore = minimax(damier,C_PLAYER);
			//on remet la grille dans son état d'origine pour
			// tester les autres coups
			damier[i] = i + 49;
			if(score < tempScore)// si on a un meilleur coup
			{
				score = tempScore;
				coup = i;
			}
		}
	}
	// on joue le meilleur coup
	damier[coup] = C_SYMBOLE;
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
		if(joueur == H_PLAYER)
			jouer(damier, joueur);
		else
			coupOrdi(damier);
		tour++;
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
		joueur = (joueur == H_PLAYER) ? C_PLAYER : H_PLAYER;
		
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
