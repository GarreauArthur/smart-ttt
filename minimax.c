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
		return 10;
	if(damier[4] == damier[2] && damier[2]==damier[6])
		return 10;
	for(int i = 0; i<3;i++)
	{
		if(damier[i] == damier[3+i] && damier[i]==damier[i+6])//colonne
			return 10;
		if(damier[0+3*i] == damier[1+3*i] && damier[0+3*i]==damier[2+3*i])//ligne
			return 10;
	}
	return 0;
}

int finJeu(char damier[9])
{
	if(gagner(damier) == 10)
		return 10;
	else
	{
		for(int i = 0; i<9; i++)
		{
			if(damier[i] != C_SYMBOLE && damier[i] != H_SYMBOLE)
			{
				return -1;
			}
		}
	}
	return 0;
}

int minimax(char damier[9], int joueur)
{

	int score = -20;
	int coup = -1;
	for(int i = 0; i<9; i++)
	{
		if(damier[i] != C_SYMBOLE && damier[i] != H_SYMBOLE)
		{
			// le joueur joue
			damier[i] = (joueur == C_PLAYER ? C_SYMBOLE : H_SYMBOLE);
			// fin du game ?
			int scorefinal = finJeu(damier);
			if(scorefinal != -1)
			{
				// win : 10, draw : 0, on vient de joueur, on ne peut pas perdre
				damier[i] = i+49;
				return scorefinal;
			}
			else // coup suivant
			{
				//on recupère l'inverse du score de l'adversaire
				// si adv perd -10 => on récupère 10
				// si adv gagne 10 => on récupère -10
				// si match nul => on récupère 0
				int joueurSuivant = (joueur == C_PLAYER ? H_PLAYER : C_PLAYER);
				int scoretmp = -minimax(damier,joueurSuivant);
				if(score < scoretmp)
				{
					coup = i;
					score = scoretmp;
				}
				damier[i] = i+49;
			}
		}
	}
	return score;
}

int coupOrdi(char damier[9])
{
	int score = -20;
	int coup = -1;
	for(int i = 0; i<9; i++)
	{
		if(damier[i] != C_SYMBOLE && damier[i] != H_SYMBOLE)
		{
			// le joueur joue
			damier[i] = C_SYMBOLE;
			// fin du game ?
			int scorefinal = finJeu(damier);
			if(scorefinal != -1)
			{
				// win : 10, draw : 0, on vient de joueur, on ne peut pas perdre
				return scorefinal;
			}
			else // coup suivant
			{
				//on recupère l'inverse du score de l'adversaire
				// si adv perd -10 => on récupère 10
				// si adv gagne 10 => on récupère -10
				// si match nul => on récupère 0
				int scoretmp = -minimax(damier,H_PLAYER);
				if(score < scoretmp)
				{
					coup = i;
					score = scoretmp;
				}
				damier[i] = i+49;
			}
		}
	}
	damier[coup] = C_SYMBOLE;
	return score;
}

int main(void){
	char damier[9];
	init_damier(damier);
	int joueur = 1;
	int fin = 0;
	int gagne = -1;
	system("clear");
	affiche_damier(damier);
	printf("who's starting ?\n0 : computer\n1 : you\n");
	scanf("%d",&joueur);
	while(fin == 0)
	{
		if(joueur == H_PLAYER)
			jouer(damier, joueur);
		else
			coupOrdi(damier);
		system("clear");
		affiche_damier(damier);
		gagne = finJeu(damier);
		if(gagne == 10)
		{
			fin = 1;
			if(joueur == H_PLAYER)
				printf("Bravo, vous avez gagné\n");
			else
				printf("Dommage, vous avez perdu\n");
		}
		else if(gagne == 0)
		{
			fin = 1;
			printf("match nul\n");
		}
		else
			joueur = (joueur == H_PLAYER) ? C_PLAYER : H_PLAYER;
	}
	return 0;
}
