/*
 * File contenente il modulo di salvataggio/caricamento delle impostazioni.
 */

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "struttura_dati.h"
#include "funzioni_generiche.h"
#include "gestione_partita.h"

//INIZIO MODULO

void creaNavicellaMisteriosa (Partita &partita)
{
	srand (time(NULL));	
	if (rand() % (100 / PROBABILITA_COMPARSA_NAVICELLA) == 0)
	{
		partita.navicella_misteriosa.stato = true;
		partita.navicella_misteriosa.punteggio = (rand() % ((PUNTEGGIO_M_X_MAX - PUNTEGGIO_M_X_MIN) / 10)) * 10 + PUNTEGGIO_M_X_MIN;
		partita.pos_x_navicella = MARGINE_SX_GIOCO;
	}
}

void muoviNavicellaMisteriosa (Partita &partita, const unsigned int limite_dx)
{
	partita.pos_x_navicella = sucInRange (partita.pos_x_navicella, LATO_UNITA, limite_dx);
	if (partita.pos_x_navicella == limite_dx)
	{
		partita.navicella_misteriosa.stato = false;
	}
}

bool controlloCollisioneBarriere (stato_barriera barriere [N_BARRIERE] [ALT_BARRIERA] [LARG_BARRIERA], unsigned int pos_x_sparo, unsigned int pos_y_sparo, const unsigned int pos_x_prima_barriera, const unsigned pos_y_prima_barriera, const unsigned int distanza_barriere)
{
	bool collisione = false;
	unsigned int altezza_barriera = ALT_BARRIERA * LATO_UNITA;
	if (pos_y_sparo >= pos_y_prima_barriera && pos_y_sparo <= pos_y_prima_barriera + altezza_barriera)
	{
		unsigned int pos_x_attuale = pos_x_prima_barriera;
		for (unsigned int n = 0 ; n < N_BARRIERE; n++)
		{
			if (pos_x_sparo >= pos_x_attuale && pos_x_sparo <= pos_x_attuale + LUNGHEZZA_PIXEL_BARRIERA)
			{
				unsigned int pos_y_attuale = pos_y_prima_barriera;
				for (unsigned int r = 0; r < ALT_BARRIERA; r++)
				{
					if (pos_y_sparo >= pos_y_attuale && pos_y_sparo <= pos_y_attuale + LATO_UNITA)
					{
						for (unsigned int c = 0; c < LARG_BARRIERA; c++)
						{	
							if (pos_x_sparo >= pos_x_attuale && pos_x_sparo <= pos_x_attuale + LATO_UNITA) 
							{
								if (barriere [n] [r] [c] != distrutta)
								{
									barriere [n] [r] [c] = static_cast <stato_barriera> (precInRange (barriere [n] [r] [c], 0));
									collisione = true;
								}
								break;
							}
							pos_x_attuale += LATO_UNITA;								
						}
						break;
					}
					pos_y_attuale += LATO_UNITA;
				}
				break;
			}
			pos_x_attuale += LUNGHEZZA_PIXEL_BARRIERA + distanza_barriere;
		}
	}
	return collisione;
}

ALLEGRO_BITMAP * sparoScelto (int pos_x, ALLEGRO_BITMAP *sparo_mostri_1, ALLEGRO_BITMAP *sparo_mostri_2)
{
	if (pos_x % 2 == 0)
	{
		return sparo_mostri_1;		
	}
	else
	{
		return sparo_mostri_2;
	}
}

void creaSparoMostri (Partita &partita, const unsigned int dim_font_mostri, const unsigned int distanza_file_mostri, const ALLEGRO_FONT *font_mostri, const unsigned int distanza_assi_col_mostri)
{
	srand (time(NULL));
	int fattore_casuale ;
	if (partita.ondata.mostri_rimasti < static_cast <int> (N_COL_MOSTRI))
	{
		fattore_casuale =  rand() % partita.ondata.mostri_rimasti;
	}
	else
	{
		fattore_casuale =  rand() % N_COL_MOSTRI;
	}

	unsigned int pos_y_attuale  = partita.ondata.pos_y + dim_font_mostri + distanza_file_mostri * (N_FILE_MOSTRI - 1);	
	for (int i = N_FILE_MOSTRI - 1; i >= 0 && fattore_casuale >= 0; i--)
	{
		unsigned int larghezza_mostro = al_get_text_width (font_mostri, partita.ondata.mostri [i] [0].stringa);
		unsigned int pos_x_attuale = partita.ondata.pos_x + larghezza_mostro / 2 - 3;
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			if (partita.ondata.mostri [i] [j].stato)
			{
				if (fattore_casuale == 0)
				{
					partita.sparo_mostri.stato = true;
					partita.sparo_mostri.pos_x = pos_x_attuale;
					partita.sparo_mostri.pos_y = pos_y_attuale;
				}
				fattore_casuale--;
			}
			pos_x_attuale += distanza_assi_col_mostri;
		}
		pos_y_attuale -= distanza_file_mostri;
	}
}

bool controlloCollisioneBarriereDaSparoCarro (Partita &partita, const unsigned int pos_x_prima_barriera, const unsigned pos_y_prima_barriera, const unsigned int distanza_barriere)
{
	bool collisione = false;
	if (partita.sparo_carro.stato)
	{
		collisione =  controlloCollisioneBarriere (partita.barriere, partita.sparo_carro.pos_x, partita.sparo_carro.pos_y, pos_x_prima_barriera, pos_y_prima_barriera, distanza_barriere);
	}
	if (collisione)
	{
		partita.sparo_carro.stato = false;
	}
	return collisione;
}

bool controlloCollisioneBarriereDaSparoMostri (Partita &partita, const unsigned int pos_x_prima_barriera, const unsigned pos_y_prima_barriera, const unsigned int distanza_barriere, const unsigned int altezza_sparo)
{
	bool collisione = false;
	if (partita.sparo_mostri.stato)
	{
		collisione =  controlloCollisioneBarriere (partita.barriere, partita.sparo_mostri.pos_x, partita.sparo_mostri.pos_y + altezza_sparo, pos_x_prima_barriera, pos_y_prima_barriera, distanza_barriere);
	}
	if (collisione)
	{
		partita.sparo_mostri.stato = false;
	}
	return collisione;
}

bool controlloCollisioneBarriereDaOndata (Partita &partita, const unsigned int pos_x_prima_barriera, const unsigned pos_y_prima_barriera, const unsigned int distanza_barriere, const unsigned int dim_font_mostri, const ALLEGRO_FONT *font_mostri, const unsigned int distanza_file_mostri, const unsigned int distanza_assi_col_mostri)
{
	bool collisione = false;
	unsigned int pos_y_fila  = partita.ondata.pos_y + dim_font_mostri + distanza_file_mostri * (N_FILE_MOSTRI - 1);
	for (int i = N_FILE_MOSTRI - 1; i >= 0 && pos_y_fila >= pos_y_prima_barriera; i--)
	{
		unsigned int larghezza_mostro = al_get_text_width (font_mostri, partita.ondata.mostri [i] [0].stringa);
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			unsigned int pos_x_attuale = (partita.ondata.pos_x + distanza_assi_col_mostri * j) - larghezza_mostro / 2;
			if (partita.ondata.mostri [i] [j].stato)
			{
				for (unsigned int k = 0; k < larghezza_mostro; k += LATO_UNITA)
				{
					for (unsigned int l = 0; l < LATO_UNITA * LATO_UNITA; l += LATO_UNITA)
					{
						if (controlloCollisioneBarriere (partita.barriere, pos_x_attuale, pos_y_fila - l, pos_x_prima_barriera, pos_y_prima_barriera, distanza_barriere))
						{
							collisione = true;
						}
					}
				}
			}
		}
		pos_y_fila -= distanza_file_mostri;
	}
	/////////////////////////
	
	return collisione;
}

bool controlloCollisioneCarroDaOndata (Partita &partita, const unsigned int dim_font_mostri, const unsigned int distanza_file_mostri, const unsigned int distanza_assi_col_mostri, const unsigned int pos_y_carro)
{
	bool collisione = false;
	unsigned int pos_y_fila  = partita.ondata.pos_y + dim_font_mostri + distanza_file_mostri * (N_FILE_MOSTRI - 1);
	for (int i = N_FILE_MOSTRI - 1; i >= 0 && (!collisione) && pos_y_fila >= pos_y_carro; i--)
	{
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			if (partita.ondata.mostri [i] [j].stato)
			{
				collisione = true;
				break;
			}
		}
		pos_y_fila -= distanza_file_mostri;
	}
	return collisione;
}

bool controlloCollisioneCarroDaSparoMostri (Partita &partita, const unsigned int larghezza_carro, const unsigned int altezza_sparo, const unsigned int dim_font_mostri, const unsigned int pos_y_carro)
{
	bool collisione = false;
	if (partita.sparo_mostri.stato && (partita.sparo_mostri.pos_y + altezza_sparo) >= pos_y_carro && (partita.sparo_mostri.pos_x >= partita.pos_x_carro - (larghezza_carro / 2) && partita.sparo_mostri.pos_x <= partita.pos_x_carro + (larghezza_carro / 2)))
	{
		partita.vite_rimanenti--;
		partita.sparo_mostri.stato = false;
		collisione = true;
	}
	return collisione;
}

bool controlloCollisioneNavicellaMisteriosa (Partita &partita, const unsigned int larghezza_navicella, const unsigned int altezza_navicella, const unsigned int pos_y_navicella)
{
	bool collisione = false;
	if (partita.sparo_carro.stato && partita.sparo_carro.pos_y <= (pos_y_navicella + altezza_navicella) && (partita.sparo_carro.pos_x >= partita.pos_x_navicella && partita.sparo_carro.pos_x <= (partita.pos_x_navicella + larghezza_navicella)))
	{
		partita.navicella_misteriosa.stato = false;
		partita.sparo_carro.stato = false;
		partita.punteggio.valore += partita.navicella_misteriosa.punteggio;
		collisione = true;
	}
	return collisione;
}

bool controlloCollisioneMostri (Partita &partita, const unsigned int dim_font_mostri, const unsigned int distanza_file_mostri, const ALLEGRO_FONT *font_mostri, const unsigned int distanza_assi_col_mostri)
{
	bool collisione = false;
	if (partita.sparo_carro.stato)
	{
		unsigned int pos_y_fila  = partita.ondata.pos_y + dim_font_mostri + distanza_file_mostri * (N_FILE_MOSTRI - 1);
		for (int i = N_FILE_MOSTRI - 1; i >= 0; i--)
		{
			if (partita.sparo_carro.pos_y <= pos_y_fila && partita.sparo_carro.pos_y >= pos_y_fila - dim_font_mostri)
			{
				unsigned int larghezza_mostro = al_get_text_width (font_mostri, partita.ondata.mostri [i] [0].stringa);
				unsigned int pos_x_fila = partita.ondata.pos_x - larghezza_mostro / 2;
				for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
				{
					if (partita.sparo_carro.pos_x >= pos_x_fila && partita.sparo_carro.pos_x <= pos_x_fila + larghezza_mostro)
					{
						if (partita.ondata.mostri [i] [j].stato)
						{
							partita.ondata.mostri [i] [j].stato = false;
							partita.punteggio.valore += partita.ondata.mostri [i] [j].punteggio;
							partita.sparo_carro.stato = false;
							partita.ondata.mostri_rimasti--;
							collisione = true;
						}
						break;
					}
					pos_x_fila += distanza_assi_col_mostri;
				}
			}
			if (partita.sparo_carro.pos_y > pos_y_fila || collisione)
			{
				break;
			}
			pos_y_fila -= distanza_file_mostri;
		}
	}
	return collisione;
}

void muoviMostri (Ondata &ondata, const unsigned int limite_sx, const unsigned int limite_dx, const unsigned int limite_inf, const unsigned int distanza_assi_colonne_mostri, const unsigned int larghezza_colonna, const unsigned int distanza_file_mostri)
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

void muoviSparoMostri (Sparo &sparo, const unsigned int limite_inf)
{
	sparo.pos_y = sucInRange (sparo.pos_y, LATO_UNITA, limite_inf);
	if (sparo.pos_y >= limite_inf)
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

void inizializzaBarriere (stato_barriera barriera [ALT_BARRIERA] [LARG_BARRIERA])
{
	const unsigned int CENTRO_LARG = LARG_BARRIERA / 2 - 1;
	const unsigned int ALT_INIZIO_SMUSSO_INFERIORE = ALT_BARRIERA / 2.3;

	const unsigned int SMUSSO_SUPERIORE = 4;
	const unsigned int LARG_PIEDE = LARG_BARRIERA / 4;
	const unsigned int SMUSSO_INFERIORE = (LARG_BARRIERA - (LARG_PIEDE * 2)) / 2;

	unsigned int offset_no_disegno = CENTRO_LARG - SMUSSO_SUPERIORE - 1;
	for (unsigned int i = 0; i < ALT_BARRIERA; i++)
	{
		if (i <= SMUSSO_SUPERIORE)
		{
			offset_no_disegno ++;
		}
		else if (i == ALT_INIZIO_SMUSSO_INFERIORE)
		{
			offset_no_disegno = SMUSSO_INFERIORE;
		}
		else if (i > ALT_INIZIO_SMUSSO_INFERIORE && i < ALT_INIZIO_SMUSSO_INFERIORE + SMUSSO_INFERIORE)
		{
			offset_no_disegno --;
		}

		for (unsigned int j = 0; j < LARG_BARRIERA; j++)
		{
			if (!(((i < ALT_INIZIO_SMUSSO_INFERIORE) && (j < (CENTRO_LARG - offset_no_disegno) || j > (CENTRO_LARG + 1 + offset_no_disegno))) ||((i >= ALT_INIZIO_SMUSSO_INFERIORE) && (j >= (LARG_PIEDE - 1 + offset_no_disegno) && j <= (LARG_BARRIERA - LARG_PIEDE - offset_no_disegno)))))
			{
				barriera [i] [j] = integra;
			}
			else
			{
				barriera [i] [j] = distrutta;
			}
		}
	}
}

void nuovaPartita (Partita &partita, Impostazioni impostazioni, const unsigned int pos_x_iniziale_carro, const unsigned int pos_x_iniziale_ondata, const unsigned int pos_y_iniziale_ondata, const unsigned int pos_x_navicella)
{
	Punteggio punteggio;
	strcpy (punteggio.nome, "");
	punteggio.valore = 0;
	partita.punteggio = punteggio;

	partita.vite_rimanenti = impostazioni.vite_iniziali;

	for (unsigned int i = 0; i < N_BARRIERE; i++)
	{
		inizializzaBarriere (partita.barriere [i]);
	}

	nuovaOndata (partita.ondata, pos_x_iniziale_ondata, pos_y_iniziale_ondata);
	
	partita.pos_x_carro = pos_x_iniziale_carro;

	partita.sparo_carro.stato = false;

	partita.sparo_mostri.stato = false;
	
	partita.navicella_misteriosa.stato = false;
	strcpy (partita.navicella_misteriosa.stringa, STRINGA_M_X);

	partita.pos_x_navicella = pos_x_navicella;
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

	if (!(f>>temp.punteggio.valore))
	{
		return false;
	}

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
			if (!(f>>temp.ondata.mostri [i] [k].stato && f>>temp.ondata.mostri [i] [k].punteggio && f>>temp.ondata.mostri [i] [k].stringa))
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
	if (!(f>>temp.ondata.pos_x && f>>temp.ondata.pos_y))
	{
		return false;
	}
	
	if (!(f>>temp.pos_x_carro))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_carro.stato && f>>temp.sparo_carro.pos_x && f>>temp.sparo_carro.pos_y))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_mostri.stato && f>>temp.sparo_mostri.pos_x && f>>temp.sparo_mostri.pos_y))
	{
		return false;
	}
	
	if (!(f>>temp.navicella_misteriosa.stato && f>>temp.navicella_misteriosa.punteggio && f>>temp.navicella_misteriosa.stringa))
	{
		return false;
	}
	
	if (!(f>>temp.pos_x_navicella))
	{
		return false;
	}

	salvataggio = temp;
	return true;
}

void salvaPartita (SpaceInvaders &spaceInvaders, const char file [])
{
	ofstream f(file);
	Partita partita = spaceInvaders.partita_in_corso;

	f<<partita.punteggio.valore<<endl<<endl;
	
	f<<partita.vite_rimanenti<<endl<<endl;

	for (unsigned int n = 0; n < N_BARRIERE; n++)
	{
		for (unsigned int r = 0; r < ALT_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARG_BARRIERA; c++)
			{
				f<<partita.barriere [n] [r] [c]<<" ";
			}
			f<<endl;
		}
		f<<endl<<endl;
	}

	for (unsigned int i = 0; i < N_FILE_MOSTRI; i++)
	{
		for (unsigned int k = 0; k < N_COL_MOSTRI; k++)
		{
			f<<partita.ondata.mostri [i] [k].stato<<" "<<partita.ondata.mostri [i] [k].punteggio<<" "<<partita.ondata.mostri [i] [k].stringa<<"\t";
		}
		f<<endl;
	}
	f<<partita.ondata.mostri_rimasti<<endl;
	f<<partita.ondata.dir_mostri<<endl;
	f<<partita.ondata.pos_x<<endl;
	f<<partita.ondata.pos_y<<endl<<endl;

	f<<partita.pos_x_carro<<endl<<endl;

	f<<partita.sparo_carro.stato<<endl;
	f<<partita.sparo_carro.pos_x<<endl;
	f<<partita.sparo_carro.pos_y<<endl<<endl;

	f<<partita.sparo_mostri.stato<<endl;
	f<<partita.sparo_mostri.pos_x<<endl;
	f<<partita.sparo_mostri.pos_y<<endl<<endl;

	f<<partita.navicella_misteriosa.stato<<endl;
	f<<partita.navicella_misteriosa.punteggio<<endl;
	f<<partita.navicella_misteriosa.stringa<<endl<<endl;

	f<<partita.pos_x_navicella;

	spaceInvaders.partita_salvata = true;
}

bool eliminaFileSalvataggio (const char file [], SpaceInvaders &spaceInvaders)
{
	if (!remove (file))
	{
		spaceInvaders.partita_salvata = false;
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
