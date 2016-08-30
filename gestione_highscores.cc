/*
 * File contenente il modulo di salvataggio/caricamento delle impostazioni.
 */

#include "struttura_dati.h"
#include "gestione_highscores.h"

//INIZIO MODULO

bool caricaPunteggi (punteggio (&highscores) [MAX_HIGHSCORES], unsigned int &n_highscores, const char file [])
{
	ifstream f (file) ;
    	if (!f) {
		cerr<<"Errore nel caricamento del file "<<file<<endl;
		return false ;
    	}
	int i = 0;
	char nome [CARATTERI_NOME];
	int valore;
	while (f>>nome)
	{
		f>>valore;
		inizializzaPunteggio (highscores [i], nome, valore);
		i++;
    	}

	assert (i <= 10);
	
	if (i == 0)
	{
		n_highscores = 0;
		return false;
	}
	n_highscores = i;
	return true;
}

void salvaPunteggi (punteggio highscores [], unsigned int n_highscores, const char file [])
{
	ofstream f(file) ;
	for (unsigned  int i = 0; i < n_highscores; i++)
	{
		f<<highscores [i].nome<< " "<<highscores [i].valore<<endl;
	}
}

void inizializzaPunteggio (punteggio &punteggio, char nome [], int valore)
{
	strncpy (punteggio.nome, nome, CARATTERI_NOME);
	punteggio.valore = valore;
}

punteggio migliorPunteggio (punteggio highscores [])
{
	return highscores [0];
}

void scambiaPunteggio (punteggio &punt1, punteggio &punt2)
{
	punteggio temp = punt2;
	punt2 = punt1;
	punt1 = temp;
}

bool aggiungiPunteggio (punteggio (&highscores) [MAX_HIGHSCORES], unsigned int &n_highscores, punteggio nuovo_punteggio)
{
	for (unsigned int i = 0; i < n_highscores; i++)
	{
		if (nuovo_punteggio.valore > highscores [i].valore)
		{
			punteggio pros = nuovo_punteggio;
			while (i < n_highscores && i < MAX_HIGHSCORES)
			{
				scambiaPunteggio (highscores [i], pros);
				i++;
			}
			if (n_highscores < MAX_HIGHSCORES)
			{
				n_highscores++;
			}
			return true;
		}
	}
	return false;
}

void stampa (punteggio punt)
{
	cout<<punt.nome<<" "<<punt.valore;	
}

void stampa (punteggio highscores [], int n)
{
	for (int i = 0; i < n; i++)
	{
		stampa (highscores [i]);
		cout<<endl;
	}
}

//FINE MODULO
