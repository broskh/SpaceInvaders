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
		partita.navicella_misteriosa.punteggio = (rand() % ((PUNTEGGIO_NAVICELLA_MAX - PUNTEGGIO_NAVICELLA_MIN) / 10)) * 10 + PUNTEGGIO_NAVICELLA_MIN;
		partita.pos_x_navicella = MARGINE_SX_GIOCO;
	}
}

void muoviNavicellaMisteriosa (Partita &partita, unsigned int larghezza_navicella)
{
	unsigned int margine_dx = MARGINE_DX_GIOCO + larghezza_navicella;
	partita.pos_x_navicella = sucInRange (partita.pos_x_navicella, DIMENSIONE_LATO_UNITA_BARRIERA, margine_dx);
	if (partita.pos_x_navicella == margine_dx)
	{
		partita.navicella_misteriosa.stato = false;
	}
}

bool controlloCollisioneBarriere (stato_barriera barriere [N_BARRIERE] [ALT_BARRIERA] [LARG_BARRIERA], unsigned int pos_x_sparo, unsigned int pos_y_sparo)
{
	bool collisione = false;
	unsigned int altezza_barriera = ALT_BARRIERA * DIMENSIONE_LATO_UNITA_BARRIERA;
	if (pos_y_sparo >= POS_Y_BARRIERE && pos_y_sparo <= POS_Y_BARRIERE + altezza_barriera)
	{
		unsigned int pos_x_attuale = POS_X_PRIMA_BARRIERA;
		for (unsigned int n = 0 ; n < N_BARRIERE; n++)
		{
			if (pos_x_sparo >= pos_x_attuale && pos_x_sparo <= pos_x_attuale + LUNGHEZZA_PIXEL_BARRIERA)
			{
				unsigned int pos_y_attuale = POS_Y_BARRIERE;
				for (unsigned int r = 0; r < ALT_BARRIERA; r++)
				{
					if (pos_y_sparo >= pos_y_attuale && pos_y_sparo <= pos_y_attuale + DIMENSIONE_LATO_UNITA_BARRIERA)
					{
						for (unsigned int c = 0; c < LARG_BARRIERA; c++)
						{	
							if (pos_x_sparo >= pos_x_attuale && pos_x_sparo <= pos_x_attuale + DIMENSIONE_LATO_UNITA_BARRIERA) 
							{
								if (barriere [n] [r] [c] != distrutta)
								{
									barriere [n] [r] [c] = static_cast <stato_barriera> (precInRange (barriere [n] [r] [c], 0));
									collisione = true;
								}
								break;
							}
							pos_x_attuale += DIMENSIONE_LATO_UNITA_BARRIERA;								
						}
						break;
					}
					pos_y_attuale += DIMENSIONE_LATO_UNITA_BARRIERA;
				}
				break;
			}
			pos_x_attuale += LUNGHEZZA_PIXEL_BARRIERA + DISTANZA_BARRIERE;
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

void creaSparoMostri (Partita &partita, const ALLEGRO_FONT *font_mostri)
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

	unsigned int pos_y_attuale  = partita.ondata.pos_y + DIM_MOSTRI + DISTANZA_FILE_MOSTRI * (N_FILE_MOSTRI - 1);	
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
			pos_x_attuale += DISTANZA_ASSI_COL_MOSTRI;
		}
		pos_y_attuale -= DISTANZA_FILE_MOSTRI;
	}
}

bool controlloCollisioneBarriereDaSparoCarro (Partita &partita)
{
	bool collisione = false;
	if (partita.sparo_carro.stato)
	{
		collisione =  controlloCollisioneBarriere (partita.barriere, partita.sparo_carro.pos_x, partita.sparo_carro.pos_y);
	}
	if (collisione)
	{
		partita.sparo_carro.stato = false;
	}
	return collisione;
}

bool controlloCollisioneBarriereDaSparoMostri (Partita &partita, const unsigned int altezza_sparo_alieni)
{
	bool collisione = false;
	if (partita.sparo_mostri.stato)
	{
		collisione =  controlloCollisioneBarriere (partita.barriere, partita.sparo_mostri.pos_x, partita.sparo_mostri.pos_y + altezza_sparo_alieni);
	}
	if (collisione)
	{
		partita.sparo_mostri.stato = false;
	}
	return collisione;
}

bool controlloCollisioneBarriereDaOndata (Partita &partita, const ALLEGRO_FONT *font_mostri)
{
	bool collisione = false;
	unsigned int pos_y_fila  = partita.ondata.pos_y + DIM_MOSTRI + DISTANZA_FILE_MOSTRI * (N_FILE_MOSTRI - 1);
	for (int i = N_FILE_MOSTRI - 1; i >= 0 && pos_y_fila >= POS_Y_BARRIERE; i--)
	{
		unsigned int larghezza_mostro = al_get_text_width (font_mostri, partita.ondata.mostri [i] [0].stringa);
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			unsigned int pos_x_attuale = (partita.ondata.pos_x + DISTANZA_ASSI_COL_MOSTRI * j) - larghezza_mostro / 2;
			if (partita.ondata.mostri [i] [j].stato)
			{
				for (unsigned int k = 0; k < larghezza_mostro; k += DIMENSIONE_LATO_UNITA_BARRIERA)
				{
					for (unsigned int l = 0; l < DIMENSIONE_LATO_UNITA_BARRIERA * DIMENSIONE_LATO_UNITA_BARRIERA; l += DIMENSIONE_LATO_UNITA_BARRIERA)
					{
						if (controlloCollisioneBarriere (partita.barriere, pos_x_attuale, pos_y_fila - l))
						{
							collisione = true;
						}
					}
				}
			}
		}
		pos_y_fila -= DISTANZA_FILE_MOSTRI;
	}
	
	return collisione;
}

bool controlloCollisioneCarroDaOndata (Partita &partita)
{
	bool collisione = false;
	unsigned int pos_y_fila  = partita.ondata.pos_y + DIM_MOSTRI + DISTANZA_FILE_MOSTRI * (N_FILE_MOSTRI - 1);
	for (int i = N_FILE_MOSTRI - 1; i >= 0 && (!collisione) && pos_y_fila >= POS_Y_CARRO; i--)
	{
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			if (partita.ondata.mostri [i] [j].stato)
			{
				collisione = true;
				break;
			}
		}
		pos_y_fila -= DISTANZA_FILE_MOSTRI;
	}
	return collisione;
}

bool controlloCollisioneCarroDaSparoMostri (Partita &partita, const unsigned int larghezza_carro, const unsigned int altezza_sparo)
{
	bool collisione = false;
	if (partita.sparo_mostri.stato && (partita.sparo_mostri.pos_y + altezza_sparo) >= POS_Y_CARRO && (partita.sparo_mostri.pos_x >= partita.pos_x_carro - (larghezza_carro / 2) && partita.sparo_mostri.pos_x <= partita.pos_x_carro + (larghezza_carro / 2)))
	{
		partita.vite_rimanenti--;
		partita.sparo_mostri.stato = false;
		collisione = true;
	}
	return collisione;
}

bool controlloCollisioneNavicellaMisteriosa (Partita &partita, const unsigned int larghezza_navicella)
{
	bool collisione = false;
	if (partita.sparo_carro.stato && partita.sparo_carro.pos_y <= (MARGINE_SUP_GIOCO + DIM_MOSTRI) && (partita.sparo_carro.pos_x >= partita.pos_x_navicella && partita.sparo_carro.pos_x <= (partita.pos_x_navicella + larghezza_navicella)))
	{
		partita.navicella_misteriosa.stato = false;
		partita.sparo_carro.stato = false;
		partita.punteggio.valore += partita.navicella_misteriosa.punteggio;
		collisione = true;
	}
	return collisione;
}

bool controlloCollisioneMostri (Partita &partita, const ALLEGRO_FONT *font_mostri)
{
	bool collisione = false;
	if (partita.sparo_carro.stato)
	{
		unsigned int pos_y_fila  = partita.ondata.pos_y + DIM_MOSTRI + DISTANZA_FILE_MOSTRI * (N_FILE_MOSTRI - 1);
		for (int i = N_FILE_MOSTRI - 1; i >= 0; i--)
		{
			if (partita.sparo_carro.pos_y <= pos_y_fila && partita.sparo_carro.pos_y >= pos_y_fila - DIM_MOSTRI)
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
					pos_x_fila += DISTANZA_ASSI_COL_MOSTRI;
				}
			}
			if (partita.sparo_carro.pos_y > pos_y_fila || collisione)
			{
				break;
			}
			pos_y_fila -= DISTANZA_FILE_MOSTRI;
		}
	}
	return collisione;
}

void muoviMostri (Ondata &ondata, const unsigned int larghezza_colonna)
{
	unsigned int reale_MARGINE_DX_GIOCO = MARGINE_DX_GIOCO - ((N_COL_MOSTRI - 1) * DISTANZA_ASSI_COL_MOSTRI + larghezza_colonna / 2);
	int peso_spostamento_laterale = N_MOSTRI_TOTALE / ondata.mostri_rimasti;
	if (ondata.mostri_rimasti)
	{
		if (ondata.dir_mostri == destra)
		{
			ondata.pos_x = sucInRange (ondata.pos_x, peso_spostamento_laterale, reale_MARGINE_DX_GIOCO);
			if (ondata.pos_x == reale_MARGINE_DX_GIOCO)
			{
				ondata.dir_mostri = sinistra;
				ondata.pos_y = sucInRange (ondata.pos_y, DISTANZA_FILE_MOSTRI / 4, POS_Y_CARRO);
			}
		}
		else if (ondata.dir_mostri == sinistra)
		{
			ondata.pos_x = precInRange (ondata.pos_x, peso_spostamento_laterale, MARGINE_SX_GIOCO);
			if (ondata.pos_x == MARGINE_SX_GIOCO)
			{
				ondata.dir_mostri = destra;
				ondata.pos_y = sucInRange (ondata.pos_y, DISTANZA_FILE_MOSTRI / 4, POS_Y_CARRO);
			}
		}
	}
}

void muoviSparoCarro (Sparo &sparo)
{
	sparo.pos_y = precInRange (sparo.pos_y, DIMENSIONE_LATO_UNITA_BARRIERA, MARGINE_SUP_GIOCO);
	if (sparo.pos_y == MARGINE_SUP_GIOCO)
	{
		sparo.stato = false;
	}
}

void muoviSparoMostri (Sparo &sparo, const unsigned int altezza_sparo_alieno)
{
	unsigned int limite_inf = MARGINE_INF_GIOCO - altezza_sparo_alieno;
	sparo.pos_y = sucInRange (sparo.pos_y, DIMENSIONE_LATO_UNITA_BARRIERA, limite_inf);
	if (sparo.pos_y >= limite_inf)
	{
		sparo.stato = false;
	}
}

void muoviDestraCarro (unsigned int &pos_x_carro)
{
	pos_x_carro = sucInRange (pos_x_carro, DIMENSIONE_LATO_UNITA_BARRIERA, MARGINE_DX_GIOCO);
}

void muoviSinistraCarro (unsigned int &pos_x_carro)
{
	pos_x_carro = precInRange (pos_x_carro, DIMENSIONE_LATO_UNITA_BARRIERA, MARGINE_SX_GIOCO);
}

bool esisteSalvataggio ()
{
	ifstream f (FILE_SALVATAGGIO_PARTITA);
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

void nuovaPartita (Partita &partita, Impostazioni impostazioni)
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

	nuovaOndata (partita.ondata);
	
	partita.pos_x_carro = LARGHEZZA_DISPLAY / 2;

	partita.sparo_carro.stato = false;

	partita.sparo_mostri.stato = false;
	
	partita.navicella_misteriosa.stato = false;
	strcpy (partita.navicella_misteriosa.stringa, STRINGA_NAVICELLA);

	partita.pos_x_navicella = MARGINE_SX_GIOCO;
}

void nuovaOndata (Ondata &ondata)
{
	int i = 0;
	Mostro mostro;

	mostro.stato = true;
	mostro.punteggio = PUNTEGGIO_MOSTRO_1;
	strcpy (mostro.stringa, STRINGA_MOSTRO_1);
	for (; i < 2; i++)
	{
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			ondata.mostri [i] [j] = mostro;
		}
	}

	mostro.stato = true;
	mostro.punteggio = PUNTEGGIO_MOSTRO_2;
	strcpy (mostro.stringa, STRINGA_MOSTRO_2);
	for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
	{
		ondata.mostri [i] [j] = mostro;
	}
	i++;

	mostro.stato = true;
	mostro.punteggio = PUNTEGGIO_MOSTRO_3;
	strcpy (mostro.stringa, STRINGA_MOSTRO_3);
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
	
	ondata.pos_x = POS_X_PRIMO_ASSE_MOSTRI;
	
	ondata.pos_y = POS_Y_PRIMA_FILA_ONDATA;
}

bool caricaPartita (Partita &salvataggio)
{
	ifstream f (FILE_SALVATAGGIO_PARTITA);
    	if (!f) {
		cerr<<"Errore nel caricamento del file "<<FILE_SALVATAGGIO_PARTITA<<endl;
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

void output (Partita partita, ostream &os)
{
	os<<partita.punteggio.valore<<endl<<endl;
	
	os<<partita.vite_rimanenti<<endl<<endl;

	for (unsigned int n = 0; n < N_BARRIERE; n++)
	{
		for (unsigned int r = 0; r < ALT_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARG_BARRIERA; c++)
			{
				os<<partita.barriere [n] [r] [c]<<" ";
			}
			os<<endl;
		}
		os<<endl<<endl;
	}

	for (unsigned int i = 0; i < N_FILE_MOSTRI; i++)
	{
		for (unsigned int k = 0; k < N_COL_MOSTRI; k++)
		{
			os<<partita.ondata.mostri [i] [k].stato<<" "<<partita.ondata.mostri [i] [k].punteggio<<" "<<partita.ondata.mostri [i] [k].stringa<<"\t";
		}
		os<<endl;
	}
	os<<partita.ondata.mostri_rimasti<<endl;
	os<<partita.ondata.dir_mostri<<endl;
	os<<partita.ondata.pos_x<<endl;
	os<<partita.ondata.pos_y<<endl<<endl;

	os<<partita.pos_x_carro<<endl<<endl;

	os<<partita.sparo_carro.stato<<endl;
	os<<partita.sparo_carro.pos_x<<endl;
	os<<partita.sparo_carro.pos_y<<endl<<endl;

	os<<partita.sparo_mostri.stato<<endl;
	os<<partita.sparo_mostri.pos_x<<endl;
	os<<partita.sparo_mostri.pos_y<<endl<<endl;

	os<<partita.navicella_misteriosa.stato<<endl;
	os<<partita.navicella_misteriosa.punteggio<<endl;
	os<<partita.navicella_misteriosa.stringa<<endl<<endl;

	os<<partita.pos_x_navicella;
}

void salvaPartita (SpaceInvaders &spaceInvaders)
{
	ofstream f(FILE_SALVATAGGIO_PARTITA);
	Partita partita = spaceInvaders.partita_in_corso;

	output (partita, f);

	spaceInvaders.partita_salvata = true;
}

bool eliminaFileSalvataggio (SpaceInvaders &spaceInvaders)
{
	if (!remove (FILE_SALVATAGGIO_PARTITA))
	{
		spaceInvaders.partita_salvata = false;
		return true;
	}
	return false;
}

void stampa (Partita partita)
{
	output (partita, cout);
}
//FINE MODULO