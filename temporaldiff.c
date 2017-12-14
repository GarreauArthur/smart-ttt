#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define C_PLAYER 0
#define H_PLAYER 1
#define C_SYMBOLE 'X'
#define H_SYMBOLE 'O'
#define NB_STATES_MAX 362880

//------------------------------------------------------------------------------
// GLOBAL VARIABLES AND STRUCTURES
typedef struct{
	char state[10];
	float value;
} State;


State G_states[NB_STATES_MAX];//will contains all the states
int G_nbStates = 0;//number of states discovered

//------------------------------------------------------------------------------

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

int coupOrdi(char damier[9])
{
	int score = -20;

	return score;
}
//------------------------------------------------------------------------------
//temporal diff

/*
 * Transform the current state of the board into a string
 */
void toString(char damier[9], char state[10]){
	for(int i = 0; i<9;i++)
		state[i] = damier[i];
	state[9]='\0';
}


void updateValue(damier)
{
	int found = 0;
	char state[10];
	toString(damier,state);
	for(int i = 0; i < G_nbStates; i++)
	{
		if(strcmp(state,G_states[i].state) == 0)
		{
			found = 1;
			break;
		}
	}
	if(found == 0)//si nouvel état
	{
		Sate s;//State * s = (State *)malloc(sizeof(State)); if(s==NULL)exit(1);
		s.state = state;
		s.value = 0.5;
	}
	else//sinon
	{
		//V(s) <- V(s) + alpha.[V(s')-V(s)]
	}

}
//------------------------------------------------------------------------------
//MAIN

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
			jouer(damier, joueur);//coupOrdi(damier);
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
