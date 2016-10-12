/*
 * File contenente il modulo di salvataggio/caricamento delle impostazioni.
 */

#include "struttura_dati.h"
#include "funzioni_generiche.h"
#include "gestione_partita.h"

//INIZIO MODULO
unsigned int sceltaLarghezzaAlieno (unsigned int numero_fila, unsigned int larghezza_alieno_1, unsigned int larghezza_alieno_2, unsigned int larghezza_alieno_3)
{
	if (numero_fila < 2)
	{
		return larghezza_alieno_1;
	}
	else if (numero_fila < 4)
	{
		return larghezza_alieno_2;
	}
	else if (numero_fila < 6)
	{
		return larghezza_alieno_3;
	}
	
	return 0;
}

void creaSparoCarroArmato (Carro &carro, const unsigned int larghezza_pixel_carro, unsigned int pos_y)
{
	carro.sparo.stato = true;
	carro.sparo.pos_x = carro.pos_x + larghezza_pixel_carro / 2;
	carro.sparo.pos_y = pos_y;
}

void creaNavicellaMisteriosa (Partita &partita)
{
	srand (time(NULL));	
	if (rand() % (100 / PROBABILITA_COMPARSA_NAVICELLA) == 0)
	{
		partita.navicella_misteriosa.stato = true;
		partita.navicella_misteriosa.punteggio = (rand() % ((PUNTEGGIO_NAVICELLA_MAX - PUNTEGGIO_NAVICELLA_MIN) / 10)) * 10 + PUNTEGGIO_NAVICELLA_MIN;
		partita.navicella_misteriosa.pos_x = MARGINE_SX_GIOCO;
	}
}

void muoviNavicellaMisteriosa (Partita &partita, unsigned int larghezza_navicella)
{
	unsigned int margine_dx = MARGINE_DX_GIOCO + larghezza_navicella;
	partita.navicella_misteriosa.pos_x = sucInRange (partita.navicella_misteriosa.pos_x, DIMENSIONE_LATO_UNITA_BARRIERA, margine_dx);
	if (partita.navicella_misteriosa.pos_x == margine_dx)
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
			if (pos_x_sparo >= pos_x_attuale && pos_x_sparo <= pos_x_attuale + LARGHEZZA_PIXEL_BARRIERA)
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
			pos_x_attuale += LARGHEZZA_PIXEL_BARRIERA + DISTANZA_BARRIERE;
		}
	}
	return collisione;
}

ALLEGRO_BITMAP * sparoScelto (int pos_x, ALLEGRO_BITMAP * sparo_alieni_1, ALLEGRO_BITMAP * sparo_alieni_2)
{
	if (pos_x % 2 == 0)
	{
		return sparo_alieni_1;		
	}
	else
	{
		return sparo_alieni_2;
	}
}

void creaSparoAlieni (Partita &partita, unsigned int altezza_alieni, unsigned int larghezza_alieno_1, unsigned int larghezza_alieno_2, unsigned int larghezza_alieno_3)
{
	srand (time(NULL));
	int fattore_casuale ;
	if (partita.ondata.alieni_rimasti < static_cast <int> (N_COL_ALIENI))
	{
		fattore_casuale =  rand() % partita.ondata.alieni_rimasti;
	}
	else
	{
		fattore_casuale =  rand() % N_COL_ALIENI;
	}

	unsigned int pos_y_attuale  = partita.ondata.pos_y + altezza_alieni + DISTANZA_FILE_ALIENI * (N_FILE_ALIENI - 1);	
	for (int i = N_FILE_ALIENI - 1; i >= 0 && fattore_casuale >= 0; i--)
	{
		unsigned int larghezza_alieno = sceltaLarghezzaAlieno (i, larghezza_alieno_1, larghezza_alieno_2, larghezza_alieno_3);
		unsigned int pos_x_attuale = partita.ondata.pos_x + larghezza_alieno / 2 - 3;
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			if (partita.ondata.alieni [i] [j].stato)
			{
				if (fattore_casuale == 0)
				{
					partita.sparo_alieni.stato = true;
					partita.sparo_alieni.pos_x = pos_x_attuale;
					partita.sparo_alieni.pos_y = pos_y_attuale;
				}
				fattore_casuale--;
			}
			pos_x_attuale += DISTANZA_ASSI_COL_ALIENI;
		}
		pos_y_attuale -= DISTANZA_FILE_ALIENI;
	}
}

bool controlloCollisioneBarriereDaSparoCarro (Partita &partita)
{
	bool collisione = false;
	if (partita.carro_armato.sparo.stato)
	{
		collisione =  controlloCollisioneBarriere (partita.barriere, partita.carro_armato.sparo.pos_x, partita.carro_armato.sparo.pos_y);
	}
	if (collisione)
	{
		partita.carro_armato.sparo.stato = false;
	}
	return collisione;
}

bool controlloCollisioneBarriereDaSparoAlieni (Partita &partita, unsigned int altezza_sparo_alieni)
{
	bool collisione = false;
	if (partita.sparo_alieni.stato)
	{
		collisione =  controlloCollisioneBarriere (partita.barriere, partita.sparo_alieni.pos_x, partita.sparo_alieni.pos_y + altezza_sparo_alieni);
	}
	if (collisione)
	{
		partita.sparo_alieni.stato = false;
	}
	return collisione;
}

bool controlloCollisioneBarriereDaOndata (Partita &partita, unsigned int altezza_alieni, unsigned int larghezza_alieno_1, unsigned int larghezza_alieno_2, unsigned int larghezza_alieno_3)
{
	bool collisione = false;
	unsigned int pos_y_fila  = partita.ondata.pos_y + altezza_alieni + DISTANZA_FILE_ALIENI * (N_FILE_ALIENI - 1);
	for (int i = N_FILE_ALIENI - 1; i >= 0 && pos_y_fila >= POS_Y_BARRIERE; i--)
	{
		unsigned int larghezza_alieno = sceltaLarghezzaAlieno (i, larghezza_alieno_1, larghezza_alieno_2, larghezza_alieno_3);
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			unsigned int pos_x_attuale = (partita.ondata.pos_x + DISTANZA_ASSI_COL_ALIENI * j) - larghezza_alieno / 2;
			if (partita.ondata.alieni [i] [j].stato)
			{
				for (unsigned int k = 0; k < larghezza_alieno; k += DIMENSIONE_LATO_UNITA_BARRIERA)
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
		pos_y_fila -= DISTANZA_FILE_ALIENI;
	}
	
	return collisione;
}

bool controlloCollisioneCarroDaOndata (Partita &partita, unsigned int altezza_alieni, unsigned int pos_y_carro)
{
	bool collisione = false;
	unsigned int pos_y_fila  = partita.ondata.pos_y + altezza_alieni + DISTANZA_FILE_ALIENI * (N_FILE_ALIENI - 1);
	for (int i = N_FILE_ALIENI - 1; i >= 0 && (!collisione) && pos_y_fila >= pos_y_carro; i--)
	{
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			if (partita.ondata.alieni [i] [j].stato)
			{
				collisione = true;
				break;
			}
		}
		pos_y_fila -= DISTANZA_FILE_ALIENI;
	}
	return collisione;
}

bool controlloCollisioneCarroDaSparoAlieni (Partita &partita, unsigned int larghezza_carro, unsigned int altezza_sparo_alieni, unsigned int pos_y_carro)
{
	bool collisione = false;
	if (partita.sparo_alieni.stato && (partita.sparo_alieni.pos_y + altezza_sparo_alieni) >= pos_y_carro && (partita.sparo_alieni.pos_x >= partita.carro_armato.pos_x - (larghezza_carro / 2) && partita.sparo_alieni.pos_x <= partita.carro_armato.pos_x + (larghezza_carro / 2)))
	{
		partita.vite_rimanenti--;
		partita.sparo_alieni.stato = false;
		collisione = true;
	}
	return collisione;
}

bool controlloCollisioneNavicellaMisteriosa (Partita &partita, unsigned int altezza_navicella, unsigned int larghezza_navicella, unsigned int larghezza_sparo)
{
	bool collisione = false;
	if (partita.carro_armato.sparo.stato && partita.carro_armato.sparo.pos_y <= (MARGINE_SUP_GIOCO + altezza_navicella) && ((partita.carro_armato.sparo.pos_x + larghezza_sparo) >= partita.navicella_misteriosa.pos_x && partita.carro_armato.sparo.pos_x <= (partita.navicella_misteriosa.pos_x + larghezza_navicella)))
	{
		partita.navicella_misteriosa.stato = false;
		partita.carro_armato.sparo.stato = false;
		partita.punteggio.valore += partita.navicella_misteriosa.punteggio;
		collisione = true;
	}
	return collisione;
}

bool controlloCollisioneAlieni (Partita &partita, unsigned int altezza_alieni, unsigned int larghezza_alieno_1, unsigned int larghezza_alieno_2, unsigned int larghezza_alieno_3)
{
	bool collisione = false;
	if (partita.carro_armato.sparo.stato)
	{
		unsigned int pos_y_fila  = partita.ondata.pos_y + altezza_alieni + DISTANZA_FILE_ALIENI * (N_FILE_ALIENI - 1);
		for (int i = N_FILE_ALIENI - 1; i >= 0; i--)
		{
			if (partita.carro_armato.sparo.pos_y <= pos_y_fila && partita.carro_armato.sparo.pos_y >= pos_y_fila - altezza_alieni)
			{
				unsigned int larghezza_alieno = sceltaLarghezzaAlieno (i, larghezza_alieno_1, larghezza_alieno_2, larghezza_alieno_3);
				unsigned int pos_x_fila = partita.ondata.pos_x - larghezza_alieno / 2;
				for (unsigned int j = 0; j < N_COL_ALIENI; j++)
				{
					if (partita.carro_armato.sparo.pos_x >= pos_x_fila && partita.carro_armato.sparo.pos_x <= pos_x_fila + larghezza_alieno)
					{
						if (partita.ondata.alieni [i] [j].stato)
						{
							partita.ondata.alieni [i] [j].stato = false;
							partita.punteggio.valore += partita.ondata.alieni [i] [j].punteggio;
							partita.carro_armato.sparo.stato = false;
							partita.ondata.alieni_rimasti--;
							collisione = true;
						}
						break;
					}
					pos_x_fila += DISTANZA_ASSI_COL_ALIENI;
				}
			}
			if (partita.carro_armato.sparo.pos_y > pos_y_fila || collisione)
			{
				break;
			}
			pos_y_fila -= DISTANZA_FILE_ALIENI;
		}
	}
	return collisione;
}

void muoviAlieni (Ondata &ondata, unsigned int larghezza_colonna, unsigned int pos_y_carro)
{
	unsigned int margine_dx_reale = MARGINE_DX_GIOCO - ((N_COL_ALIENI - 1) * DISTANZA_ASSI_COL_ALIENI + larghezza_colonna / 2);
	unsigned int peso_spostamento_laterale = (N_FILE_ALIENI * N_COL_ALIENI / ondata.alieni_rimasti) + 1;
	if (peso_spostamento_laterale > MAX_SPOSTAMENTO_ONDATA)
	{
		peso_spostamento_laterale = MAX_SPOSTAMENTO_ONDATA;
	}
	if (ondata.alieni_rimasti)
	{
		if (ondata.dir_alieni == destra)
		{
			ondata.pos_x = sucInRange (ondata.pos_x, peso_spostamento_laterale, margine_dx_reale);
			if (ondata.pos_x == margine_dx_reale)
			{
				ondata.dir_alieni = sinistra;
				ondata.pos_y = sucInRange (ondata.pos_y, DISTANZA_FILE_ALIENI / 4, pos_y_carro);
			}
		}
		else if (ondata.dir_alieni == sinistra)
		{
			ondata.pos_x = precInRange (ondata.pos_x, peso_spostamento_laterale, MARGINE_SX_GIOCO);
			if (ondata.pos_x == MARGINE_SX_GIOCO)
			{
				ondata.dir_alieni = destra;
				ondata.pos_y = sucInRange (ondata.pos_y, DISTANZA_FILE_ALIENI / 4, pos_y_carro);
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

void muoviSparoAlieni (Sparo &sparo, unsigned int altezza_sparo_alieni)
{
	unsigned int limite_inf = MARGINE_INF_GIOCO - altezza_sparo_alieni;
	sparo.pos_y = sucInRange (sparo.pos_y, DIMENSIONE_LATO_UNITA_BARRIERA, limite_inf);
	if (sparo.pos_y >= limite_inf)
	{
		sparo.stato = false;
	}
}

void muoviDestraCarro (unsigned int &pos_x_carro, const unsigned int larghezza_carro)
{
	pos_x_carro = sucInRange (pos_x_carro, PESO_SPOSTAMENTO_CARRO_ARMATO, MARGINE_DX_GIOCO - larghezza_carro);
}

void muoviSinistraCarro (unsigned int &pos_x_carro)
{
	pos_x_carro = precInRange (pos_x_carro, PESO_SPOSTAMENTO_CARRO_ARMATO, MARGINE_SX_GIOCO);
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

void nuovoCarroArmato (Carro &carro, const unsigned int pos_x_carro_armato)
{
	carro.esploso = 0;
	carro.pos_x = pos_x_carro_armato;
	carro.sparo.stato = false;
}

void nuovaNavicella (Navicella &navicella)
{
	navicella.stato = false;
	navicella.pos_x = MARGINE_SX_GIOCO;
	navicella.punteggio = 0;
}

void nuovaPartita (Partita &partita, Impostazioni impostazioni, const unsigned int pos_x_carro_armato)
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

	partita.sparo_alieni.stato = false;
	
	nuovaNavicella (partita.navicella_misteriosa);

	nuovoCarroArmato (partita.carro_armato, pos_x_carro_armato);
}

void nuovoAlieno (Alieno &alieno, unsigned int punteggio)
{
	alieno.stato = true;
	alieno.punteggio = punteggio;
	alieno.esploso = false;
}

void nuovaOndata (Ondata &ondata)
{
	int i = 0;
	unsigned int punteggio_attuale;

	punteggio_attuale = PUNTEGGIO_ALIENO_1;
	for (; i < 2; i++)
	{
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			nuovoAlieno (ondata.alieni [i] [j], punteggio_attuale);
		}
	}

	punteggio_attuale = PUNTEGGIO_ALIENO_2;
	for (; i < 4; i++)
	{
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			nuovoAlieno (ondata.alieni [i] [j], punteggio_attuale);
		}
	}

	punteggio_attuale = PUNTEGGIO_ALIENO_3;
	for (; i < 6; i++)
	{
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			nuovoAlieno (ondata.alieni [i] [j], punteggio_attuale);
		}
	}

	assert (i = N_FILE_ALIENI);
	
	ondata.alieni_rimasti = N_FILE_ALIENI * N_COL_ALIENI;
	
	ondata.dir_alieni = destra;
	
	ondata.pos_x = POS_X_PRIMO_ASSE_ALIENI;
	
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

	for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
	{
		for (unsigned int k = 0; k < N_COL_ALIENI; k++)
		{
			if (!(f>>temp.ondata.alieni [i] [k].stato && f>>temp.ondata.alieni [i] [k].punteggio && f>>temp.ondata.alieni [i] [k].esploso))
			{
				return false;
			}
		}
	}
	if (!(f>>temp.ondata.alieni_rimasti))
	{
		return false;
	}
	int dir_int;
	if (f>>dir_int)
	{
		temp.ondata.dir_alieni = static_cast <direzione> (dir_int);
	}
	else
	{
		return false;
	}

	if (!(f>>temp.ondata.pos_x && f>>temp.ondata.pos_y))
	{
		return false;
	}
	
	if (!(f>>temp.sparo_alieni.stato && f>>temp.sparo_alieni.pos_x && f>>temp.sparo_alieni.pos_y))
	{
		return false;
	}
	
	if (!(f>>temp.navicella_misteriosa.stato && f>>temp.navicella_misteriosa.punteggio && f>>temp.navicella_misteriosa.pos_x))
	{
		return false;
	}
	
	if (!(f>>temp.carro_armato.esploso && f>>temp.carro_armato.pos_x && f>>temp.carro_armato.sparo.stato && f>>temp.carro_armato.sparo.pos_x && f>>temp.carro_armato.sparo.pos_y))
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

	for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
	{
		for (unsigned int k = 0; k < N_COL_ALIENI; k++)
		{
			os<<partita.ondata.alieni [i] [k].stato<<" "<<partita.ondata.alieni [i] [k].punteggio<<" "<<partita.ondata.alieni [i] [k].esploso<<" "<<"\t";
		}
		os<<endl;
	}
	os<<partita.ondata.alieni_rimasti<<endl;
	os<<partita.ondata.dir_alieni<<endl;
	os<<partita.ondata.pos_x<<endl;
	os<<partita.ondata.pos_y<<endl<<endl;

	os<<partita.sparo_alieni.stato<<endl;
	os<<partita.sparo_alieni.pos_x<<endl;
	os<<partita.sparo_alieni.pos_y<<endl<<endl;

	os<<partita.navicella_misteriosa.stato<<endl;
	os<<partita.navicella_misteriosa.punteggio<<endl;
	os<<partita.navicella_misteriosa.pos_x<<endl<<endl;

	os<<partita.carro_armato.esploso<<endl;
	os<<partita.carro_armato.pos_x<<endl;
	os<<partita.carro_armato.sparo.stato<<endl;
	os<<partita.carro_armato.sparo.pos_x<<endl;
	os<<partita.carro_armato.sparo.pos_y<<endl<<endl;
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