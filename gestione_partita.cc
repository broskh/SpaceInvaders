/*
 * File contenente il modulo di salvataggio/caricamento delle impostazioni.
 */

#include "struttura_dati.h"
#include "funzioni_generiche.h"
#include "gestione_partita.h"

//INIZIO MODULO

void muoviAlieni (Ondata &ondata, const unsigned int limite_sx, const unsigned int limite_dx, const unsigned int limite_inf, const unsigned int distanza_assi_colonne_mostri, const unsigned int larghezza_colonna, const unsigned int distanza_file_mostri)
{
	unsigned int reale_limite_dx = limite_dx - ((N_COL_MOSTRI - 1) * distanza_assi_colonne_mostri + larghezza_colonna / 2);
	if (ondata.mostri_rimasti)
	{
		if (ondata.dir_mostri == destra)
		{
			ondata.pos_x = sucInRange (ondata.pos_x, 2, reale_limite_dx);
			if (ondata.pos_x == reale_limite_dx)
			{
				ondata.dir_mostri = sinistra;
				ondata.pos_y = sucInRange (ondata.pos_y, distanza_file_mostri / 4, limite_inf);
			}
		}
		else if (ondata.dir_mostri == sinistra)
		{
			ondata.pos_x = precInRange (ondata.pos_x, 2, limite_sx);
			if (ondata.pos_x == limite_sx)
			{
				ondata.dir_mostri = destra;
				ondata.pos_y = sucInRange (ondata.pos_y, distanza_file_mostri / 4, limite_inf);
			}
		}
	}
}

void muoviSparoCarro (Sparo &sparo, const unsigned int limite_sup)
{
	sparo.pos_y = precInRange (sparo.pos_y, LATO_UNITA, limite_sup);
	if (sparo.pos_y == limite_sup)
	{
		sparo.stato = false;
	}
}

void muoviDestraCarro (unsigned int &pos_x_carro, const int limite_dx)
{
	pos_x_carro = sucInRange (pos_x_carro, LATO_UNITA, limite_dx);
}

void muoviSinistraCarro (unsigned int &pos_x_carro, const int limite_sx)
{
	pos_x_carro = precInRange (pos_x_carro, LATO_UNITA, limite_sx);
}

bool esisteSalvataggio (const char file [])
{
	ifstream f (file);
    	return f;
}

void nuovaPartita (Partita &partita, Impostazioni impostazioni, const unsigned int pos_x_iniziale_carro, const unsigned int pos_x_iniziale_ondata, const unsigned int pos_y_iniziale_ondata)
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
				partita.barriere [n] [r] [c] = integra;
			}
		}
	}

	nuovaOndata (partita.ondata, pos_x_iniziale_ondata, pos_y_iniziale_ondata);
	
	partita.pos_x_carro = pos_x_iniziale_carro;

	partita.sparo_carro.stato = false;

	partita.sparo_mostri.stato = false;
}

void nuovaOndata (Ondata &ondata, const unsigned int pos_x_iniziale, const unsigned int pos_y_iniziale)
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
	
	ondata.pos_x = pos_x_iniziale;
	
	ondata.pos_y = pos_y_iniziale;
}

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
	if (!(f>>temp.ondata.pos_x))
	{
		return false;
	}
	if (!(f>>temp.ondata.pos_y))
	{
		return false;
	}
	
	
	if (!(f>>temp.pos_x_carro))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_carro.stato))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_carro.pos_x))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_carro.pos_y))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_mostri.stato))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_mostri.pos_x))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_mostri.pos_y))
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
	f<<salvataggio.ondata.dir_mostri<<endl;
	f<<salvataggio.ondata.pos_x<<endl;
	f<<salvataggio.ondata.pos_y<<endl;

	f<<salvataggio.pos_x_carro<<endl;

	f<<salvataggio.sparo_carro.stato<<endl;
	f<<salvataggio.sparo_carro.pos_x<<endl;
	f<<salvataggio.sparo_carro.pos_y<<endl;

	f<<salvataggio.sparo_mostri.stato<<endl;
	f<<salvataggio.sparo_mostri.pos_x<<endl;
	f<<salvataggio.sparo_mostri.pos_y<<endl;
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
	cout<<partita.ondata.pos_x<<endl;
	cout<<partita.ondata.pos_y<<endl;
	cout<<partita.pos_x_carro<<endl;
	cout<<partita.sparo_carro.stato<<endl;
	cout<<partita.sparo_carro.pos_x<<endl;
	cout<<partita.sparo_carro.pos_y<<endl;
	cout<<partita.sparo_mostri.stato<<endl;
	cout<<partita.sparo_mostri.pos_x<<endl;
	cout<<partita.sparo_mostri.pos_y<<endl;
}

//FINE MODULO
