/*
 * File contenente il modulo di salvataggio/caricamento delle impostazioni.
 */

#include "struttura_dati.h"
#include "gestione_partita.h"

//INIZIO MODULO

bool esisteSalvataggio (const char file [])
{
	ifstream f (file);
    	return f;
}

void nuovaPartita (Partita &partita, Impostazioni impostazioni)
{
	Punteggio punteggio;
	strcpy (punteggio.nome, "");
	punteggio.valore = 0;
	partita.punteggio = punteggio;

	partita.vite_rimanenti = impostazioni.vite_iniziali;

	for (unsigned int n = 0; n < N_BARRIERE; n++)
	{
		for (unsigned int r = 0; r < ALT_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARG_BARRIERA; c++)
			{
				partita.barriere [n] [r] [c] = intero;
			}
		}
	}

	nuovaOndata (partita.ondata);
}

void nuovaOndata (Ondata &ondata)
{
	int i = 0;
	Mostro mostro;

	mostro.stato = true;
	mostro.punteggio = PUNTEGGIO_M_30;
	strcpy (mostro.stringa, STRINGA_M_30);
	for (; i < 2; i++)
	{
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			ondata.mostri [i] [j] = mostro;
		}
	}

	mostro.stato = true;
	mostro.punteggio = PUNTEGGIO_M_20;
	strcpy (mostro.stringa, STRINGA_M_20);
	for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
	{
		ondata.mostri [i] [j] = mostro;
	}
	i++;

	mostro.stato = true;
	mostro.punteggio = PUNTEGGIO_M_10;
	strcpy (mostro.stringa, STRINGA_M_10);
	for (; i < 5; i++)
	{
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			ondata.mostri [i] [j] = mostro;
		}
	}

	assert (i = N_FILE_MOSTRI);
	
	ondata.mostri_rimasti = N_MOSTRI_TOTALE;
	
	ondata.dir_mostri = destra;
}

/*void inizializzaPartita (Partita &partita, Punteggio punteggio, unsigned int vite_rimanenti, stato_barriera barriere [N_BARRIERE] [ALT_BARRIERA] [LARG_BARRIERA], Ondata ondata)
{
	partita.punteggio = putneggio;
	partita.vite_rimanenti = vite_rimanenti;
	for (unsigned int n = 0; n < N_BARRIERE; n++)
	{
		for (unsigned int r = 0; r < ALT_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARG_BARRIERA; c++)
			{
				partita.barriere [n] [r] [c] = barriere [n] [r] [c];
			}
		}
	}
	partita.ondata = ondata;
}*/

bool caricaPartita (Partita &salvataggio, const char file [])
{
	ifstream f (file);
    	if (!f) {
		cerr<<"Errore nel caricamento del file "<<file<<endl;
		return false ;
    	}
	Partita temp;
	if (!(f>>temp.vite_rimanenti))
	{
		return false;
	}
	for (unsigned int n = 0; n < N_BARRIERE; n++)
	{
		for (unsigned int r = 0; r < ALT_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARG_BARRIERA; c++)
			{
				int stato_int;
				if (f>>stato_int)
				{
					temp.barriere [n] [r] [c] = static_cast <stato_barriera> (stato_int);
				}
				else
				{
					return false;
				}
			}
		}
	}
	for (unsigned int i = 0; i < N_FILE_MOSTRI; i++)
	{
		for (unsigned int k = 0; k < N_COL_MOSTRI; k++)
		{
			if (!(f>>temp.ondata.mostri [i] [k].stato && f>>temp.ondata.mostri [i] [k].punteggio))
			{
				return false;
			}
		}
	}
	if (!(f>>temp.ondata.mostri_rimasti))
	{
		return false;
	}
	int dir_int;
	if (f>>dir_int)
	{
		temp.ondata.dir_mostri = static_cast <direzione> (dir_int);
	}
	else
	{
		return false;
	}
	salvataggio = temp;
	return true;
}

void salvaPartita (Partita salvataggio, const char file [])
{
	ofstream f(file);

	f<<salvataggio.vite_rimanenti<<endl;
	for (unsigned int n = 0; n < N_BARRIERE; n++)
	{
		for (unsigned int r = 0; r < ALT_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARG_BARRIERA; c++)
			{
				f<<salvataggio.barriere [n] [r] [c]<<" ";
			}
			f<<endl;
		}
		f<<endl<<endl;
	}
	for (unsigned int i = 0; i < N_FILE_MOSTRI; i++)
	{
		for (unsigned int k = 0; k < N_COL_MOSTRI; k++)
		{
			f<<salvataggio.ondata.mostri [i] [k].stato<<" "<<salvataggio.ondata.mostri [i] [k].punteggio<<"\t";
		}
		f<<endl;
	}
	f<<salvataggio.ondata.mostri_rimasti<<endl;
	f<<salvataggio.ondata.dir_mostri;
}

bool eliminaFileSalvataggio (const char file [])
{
	if (!remove (file))
	{
		return true;
	}
	return false;
}

void stampa (Partita partita)
{
	cout<<partita.vite_rimanenti<<endl;
	for (unsigned int n = 0; n < N_BARRIERE; n++)
	{
		for (unsigned int r = 0; r < ALT_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARG_BARRIERA; c++)
			{
				cout<<partita.barriere [n] [r] [c]<<" ";
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}
	for (unsigned int i = 0; i < N_FILE_MOSTRI; i++)
	{
		for (unsigned int k = 0; k < N_COL_MOSTRI; k++)
		{
			cout<<partita.ondata.mostri [i] [k].stato<<" "<<partita.ondata.mostri [i] [k].punteggio<<"\t";
		}
		cout<<endl;
	}
	cout<<partita.ondata.mostri_rimasti<<endl;
	cout<<partita.ondata.dir_mostri<<endl;
}

//FINE MODULO
