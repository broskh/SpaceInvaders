/*
 * File contenente il modulo di salvataggio/caricamento delle impostazioni.
 */

#include "struttura_dati.h"
#include "gestione_partita.h"

//INIZIO MODULO

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
					temp.barriere [n] [r] [c] = static_cast <stato> (stato_int);
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
			if (!(f>>temp.ondata.mostri [i] [k]))
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
			f<<salvataggio.ondata.mostri [i] [k]<<" ";
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
			cout<<partita.ondata.mostri [i] [k]<<" ";
		}
		cout<<endl;
	}
	cout<<partita.ondata.mostri_rimasti<<endl;
	cout<<partita.ondata.dir_mostri<<endl;
}

//FINE MODULO
