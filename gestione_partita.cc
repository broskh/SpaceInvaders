/*
 * File contenente il modulo per la gestione della partita.
 */

using namespace std;
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "strutture_dati.h"
#include "gestione_partita.h"
#include "gestione_grafica.h"

//INIZIO CONFIGURAZIONE TRACING
#ifdef DEBUG_MODE
	#ifdef DEBUG_LEVEL
		static unsigned int debug_level = DEBUG_LEVEL;
	#else
		static unsigned int debug_level = 0;
	#endif
#endif
//FINE CONFIGURAZIONE TRACING

//INIZIO MODULO
//INIZIO FUNZIONI PRIVATE
/*
 * Ritorna il numero precedente di n, retrocedendo del peso definito e non andando oltre il valore minimo min.
 */
int precInRange (int n, int peso, int min)
{
	n -= peso;
	if (n < min)
	{
		n = min;
	}
	return n;
}

/*
 * Ritorna il numero precedente di n, retrocedendo di un peso uguale a 1 e non andando oltre il valore minimo min.
 */
int precInRange (int n, int min)
{
	return precInRange (n, 1, min);
}

/*
 * Controlla se si è verificata una generica collisione sulle barriere basandosi sulle coordinate e la larghezza del corpo collidente.
 */
bool controlloCollisioneBarriere (stato_barriera barriere [N_BARRIERE] [ALTEZZA_BARRIERA] [LARGHEZZA_BARRIERA], unsigned int pos_x_corpo, unsigned int pos_y_corpo, unsigned int larghezza_corpo)
{
	bool collisione = false;
	unsigned int altezza_barriera = ALTEZZA_BARRIERA * altezzaLatoUnitaBarriera ();
	unsigned int larghezza_pixel_barriera = LARGHEZZA_BARRIERA * larghezzaLatoUnitaBarriera ();
	if (pos_y_corpo >= POS_Y_BARRIERE && pos_y_corpo <= POS_Y_BARRIERE + altezza_barriera) //controllo preventivo che il corpo collidente sia nella proiezione delle barriere rispetto all'asse y
	{
		unsigned int pos_x_attuale = POS_X_PRIMA_BARRIERA;
		for (unsigned int n = 0 ; n < N_BARRIERE; n++)
		{
			if (pos_x_corpo + larghezza_corpo >= pos_x_attuale && pos_x_corpo <= pos_x_attuale + larghezza_pixel_barriera) //controllo preventivo che il corpo collidente sia nella proiezione della barriera rispetto all'asse x
			{
				unsigned int pos_y_attuale = POS_Y_BARRIERE;
				for (unsigned int r = 0; r < ALTEZZA_BARRIERA; r++)
				{
					if (pos_y_corpo + altezzaLatoUnitaBarriera () >= pos_y_attuale && pos_y_corpo <= pos_y_attuale + altezzaLatoUnitaBarriera ())
					{
						for (unsigned int c = 0; c < LARGHEZZA_BARRIERA; c++)
						{	
							if (pos_x_corpo + larghezza_corpo >= pos_x_attuale && pos_x_corpo <= pos_x_attuale + larghezzaLatoUnitaBarriera ())
							{
								if (barriere [n] [r] [c] != distrutta)
								{
									barriere [n] [r] [c] = static_cast <stato_barriera> (precInRange (barriere [n] [r] [c], 0));
									collisione = true;
									D2(cout<<"Barriera "<<n<<" colpita nella riga "<<r<<", colonna "<<c<<"."<<endl);
								}
								//break;
							}
							pos_x_attuale += larghezzaLatoUnitaBarriera ();								
						}
						break;
					}
					pos_y_attuale += altezzaLatoUnitaBarriera ();
				}
				break;
			}
			pos_x_attuale += larghezza_pixel_barriera + DISTANZA_BARRIERE;
		}
	}
	return collisione;
}

/*
 * Inizializza un alieno con le informazioni di base.
 */
void inizializzaAlieno (Alieno &alieno, unsigned int punteggio)
{
	alieno.stato = true;
	alieno.punteggio = punteggio;
	alieno.esplosione = false;
}

/*
 * Inizializza una barriera con le informazioni di base.
 */
void inizializzaBarriera (stato_barriera barriera [ALTEZZA_BARRIERA] [LARGHEZZA_BARRIERA])
{
	unsigned int offset_no_disegno = CENTRO_ORIZZONTALE_BARRIERA - SMUSSO_SUPERIORE - 1;
	for (unsigned int i = 0; i < ALTEZZA_BARRIERA; i++)
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

		for (unsigned int j = 0; j < LARGHEZZA_BARRIERA; j++)
		{
			if (!(((i < ALT_INIZIO_SMUSSO_INFERIORE) && (j < (CENTRO_ORIZZONTALE_BARRIERA - offset_no_disegno) || j > (CENTRO_ORIZZONTALE_BARRIERA + 1 + offset_no_disegno))) ||((i >= ALT_INIZIO_SMUSSO_INFERIORE) && (j >= (LARGHEZZA_PIEDE - 1 + offset_no_disegno) && j <= (LARGHEZZA_BARRIERA - LARGHEZZA_PIEDE - offset_no_disegno)))))
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

/*
 * Inizializza il carro armato con le informazioni di base.
 */
void inizializzaCarroArmato (Carro &carro)
{
	carro.esplosione = 0;
	carro.pos_x = POS_CENTRO_X - larghezzaCarroArmato () / 2;
	carro.sparo.stato = false;
}

/*
 * Inizializza la navicella misteriosa con le informazioni di base.
 */
void inizializzaNavicellaMisteriosa (Navicella &navicella)
{
	navicella.stato = false;
	navicella.pos_x = 0;
	navicella.punteggio = 0;
}

/*
 * Stampa tutte le informazioni di una Partita sullo stream passato per parametro.
 */
void output (Partita partita, ostream &os)
{
	os<<partita.punteggio.valore<<endl<<endl;
	
	os<<partita.vite_rimanenti<<endl<<endl;

	for (unsigned int n = 0; n < N_BARRIERE; n++)
	{
		for (unsigned int r = 0; r < ALTEZZA_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARGHEZZA_BARRIERA; c++)
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
			os<<partita.ondata.alieni [i] [k].stato<<" "<<partita.ondata.alieni [i] [k].punteggio<<" "<<partita.ondata.alieni [i] [k].esplosione<<" "<<"\t";
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

	os<<partita.carro_armato.esplosione<<endl;
	os<<partita.carro_armato.pos_x<<endl;
	os<<partita.carro_armato.sparo.stato<<endl;
	os<<partita.carro_armato.sparo.pos_x<<endl;
	os<<partita.carro_armato.sparo.pos_y<<endl<<endl;
}

/*
 * Ritorna la larghezza di un alieno sulla base della fila dell'ondata alla quale appartiene.
 */
unsigned int sceltaLarghezzaAlieno (unsigned int numero_fila)
{
	if (numero_fila < N_FILE_ALIENI)
	{
		return larghezzaAlieno (numero_fila / (N_FILE_ALIENI / N_TIPI_ALIENI));
	}
	
	return 0;
}

/*
 * Ritorna il numero successivo di n, procedendo del peso definito e non andando oltre il valore assimo max.
 */
int sucInRange (int n, int peso, int max)
{
	n += peso;
	if (n > max)
	{
		n = max;
	}
	return n;
}

/*
 * Ritorna il numero successivo di n, procedendo di un peso uguale a 1 e non andando oltre il valore assimo max.
 */
int sucInRange (int n, int max)
{
	return sucInRange (n, 1, max);
}
//FINE FUNZIONI PRIVATE
void avanzaEsplosioneAlieno (Partita &partita, unsigned int n_fila, unsigned int n_colonna)
{
	partita.ondata.alieni [n_fila] [n_colonna].esplosione++;
}

void avanzaEsplosioneCarroArmato (Partita &partita)
{
	partita.carro_armato.esplosione++;
}

bool caricaPartita (Partita &partita)
{
	ifstream f (FILE_SALVATAGGIO_PARTITA);
	if (!f) {
		D1(cout<<"Errore nel caricamento del file di salvataggio. File non esistente."<<endl);
		return false;
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
		for (unsigned int r = 0; r < ALTEZZA_BARRIERA; r++)
		{
			for (unsigned int c = 0; c < LARGHEZZA_BARRIERA; c++)
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
			if (!(f>>temp.ondata.alieni [i] [k].stato && f>>temp.ondata.alieni [i] [k].punteggio && f>>temp.ondata.alieni [i] [k].esplosione))
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
	
	if (!(f>>temp.carro_armato.esplosione && f>>temp.carro_armato.pos_x && f>>temp.carro_armato.sparo.stato && f>>temp.carro_armato.sparo.pos_x && f>>temp.carro_armato.sparo.pos_y))
	{
		return false;
	}

	partita = temp;
	D1(cout<<"File di salvataggio caricato correttamente."<<endl);
	return true;
}

bool controlloCollisioneAlieni (Partita &partita)
{
	bool collisione = false;
	if (partita.carro_armato.sparo.stato)
	{
		unsigned int pos_y_fila  = partita.ondata.pos_y + altezzaAlieno () + DISTANZA_FILE_ALIENI * (N_FILE_ALIENI - 1); //parto dal fondo
		for (int i = N_FILE_ALIENI - 1; i >= 0; i--)
		{
			if (partita.carro_armato.sparo.pos_y <= pos_y_fila && partita.carro_armato.sparo.pos_y >= pos_y_fila - altezzaAlieno ()) //controllo preventivo che il colpo sia nella proiezione di questa fila dell'ondata rispetto al'asse y
			{
				unsigned int larghezza_alieno = sceltaLarghezzaAlieno (i);
				unsigned int pos_x_fila = partita.ondata.pos_x - larghezza_alieno / 2;
				for (unsigned int j = 0; j < N_COL_ALIENI; j++)
				{
					if (partita.carro_armato.sparo.pos_x + larghezzaSparoCarroArmato () >= pos_x_fila && partita.carro_armato.sparo.pos_x <= pos_x_fila + larghezza_alieno)
					{
						if (partita.ondata.alieni [i] [j].stato)
						{
							partita.ondata.alieni [i] [j].stato = false;
							partita.ondata.alieni [i] [j].esplosione = true;
							partita.punteggio.valore += partita.ondata.alieni [i] [j].punteggio;
							partita.carro_armato.sparo.stato = false;
							partita.ondata.alieni_rimasti--;
							collisione = true;
							D2(cout<<"Alieno nella riga "<<i<<", colonna "<<j<<" colpita."<<endl);
						}
						break;
					}
					pos_x_fila += DISTANZA_ASSI_COL_ALIENI;
				}
			}
			if (partita.carro_armato.sparo.pos_y > pos_y_fila || collisione) // se lo sparo ero in uno spazio fra le colonne di alieni o è stata registrata una collizione, esce dal ciclo
			{
				break;
			}
			pos_y_fila -= DISTANZA_FILE_ALIENI;
		}
	}
	return collisione;
}

bool controlloCollisioneBarriereDaOndata (Partita &partita)
{
	bool collisione = false;
	unsigned int pos_y_fila  = partita.ondata.pos_y + altezzaAlieno () + DISTANZA_FILE_ALIENI * (N_FILE_ALIENI - 1);
	for (int i = N_FILE_ALIENI - 1; i >= 0 && pos_y_fila >= POS_Y_BARRIERE; i--)
	{
		unsigned int larghezza_alieno = sceltaLarghezzaAlieno (i);
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			unsigned int pos_x_attuale = (partita.ondata.pos_x + DISTANZA_ASSI_COL_ALIENI * j) - larghezza_alieno / 2;
			if (partita.ondata.alieni [i] [j].stato)
			{
				for (unsigned int k = 0; k < larghezza_alieno; k += larghezzaLatoUnitaBarriera ())
				{
					for (unsigned int l = 0; l < altezzaLatoUnitaBarriera () * ALTEZZA_BARRIERA; l += altezzaLatoUnitaBarriera ()) //effettuo il controllo su ogni singola unità della barriera perchè nel momento in cui l'ondata scende, deve essere distrutta ogni unità colpita dagli alieni.
					{
						if (controlloCollisioneBarriere (partita.barriere, pos_x_attuale, pos_y_fila - l, larghezza_alieno))
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

bool controlloCollisioneBarriereDaSparoAlieni (Partita &partita)
{
	bool collisione = false;
	if (partita.sparo_alieni.stato)
	{
		collisione =  controlloCollisioneBarriere (partita.barriere, partita.sparo_alieni.pos_x, partita.sparo_alieni.pos_y + altezzaSparoAlienoAttuale (partita.sparo_alieni.pos_x), larghezzaSparoAlienoAttuale (partita.sparo_alieni.pos_x));
	}
	if (collisione)
	{
		partita.sparo_alieni.stato = false;
	}
	return collisione;
}

bool controlloCollisioneBarriereDaSparoCarro (Partita &partita)
{
	bool collisione = false;
	if (partita.carro_armato.sparo.stato)
	{
		collisione =  controlloCollisioneBarriere (partita.barriere, partita.carro_armato.sparo.pos_x, partita.carro_armato.sparo.pos_y, larghezzaSparoCarroArmato ());
	}
	if (collisione)
	{
		partita.carro_armato.sparo.stato = false;
	}
	return collisione;
}

bool controlloCollisioneCarroDaOndata (Partita &partita)
{
	bool collisione = false;
	unsigned int pos_y_fila  = partita.ondata.pos_y + altezzaAlieno () + DISTANZA_FILE_ALIENI * (N_FILE_ALIENI - 1);
	for (int i = N_FILE_ALIENI - 1; i >= 0 && (!collisione) && pos_y_fila >= MARGINE_INF_GIOCO - altezzaCarroArmato (); i--)
	{
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			if (partita.ondata.alieni [i] [j].stato)
			{
				collisione = true;
				D2(cout<<"Carro colpito dall'ondata aliena."<<endl);
				break;
			}
		}
		pos_y_fila -= DISTANZA_FILE_ALIENI;
	}
	return collisione;
}

bool controlloCollisioneCarroDaSparoAlieni (Partita &partita)
{
	unsigned int pos_y_carro = MARGINE_INF_GIOCO - altezzaCarroArmato ();
	bool collisione = false;
	if (partita.sparo_alieni.stato && ((partita.sparo_alieni.pos_y +  altezzaSparoAlienoAttuale (partita.sparo_alieni.pos_x)) >= pos_y_carro) && ((partita.sparo_alieni.pos_x + larghezzaSparoAlienoAttuale (partita.sparo_alieni.pos_x)) >= partita.carro_armato.pos_x) && (partita.sparo_alieni.pos_x <= partita.carro_armato.pos_x + larghezzaCarroArmato ()))
	{
		partita.vite_rimanenti--;
		partita.sparo_alieni.stato = false;
		partita.carro_armato.esplosione = true;
		collisione = true;
		D2(cout<<"Carro colpito da uno sparo alieno."<<endl);
	}
	return collisione;
}

bool controlloCollisioneNavicellaMisteriosa (Partita &partita)
{
	unsigned int pos_y_fondo_navicella = MARGINE_SUP_GIOCO + altezzaNavicellaMisteriosa ();
	bool collisione = false;
	if (partita.carro_armato.sparo.stato && partita.navicella_misteriosa.stato && partita.carro_armato.sparo.pos_y <= (pos_y_fondo_navicella) && ((partita.carro_armato.sparo.pos_x + larghezzaSparoCarroArmato ()) >= partita.navicella_misteriosa.pos_x && partita.carro_armato.sparo.pos_x <= (partita.navicella_misteriosa.pos_x + larghezzaNavicellaMisteriosa ())))
	{
		partita.navicella_misteriosa.stato = false;
		partita.carro_armato.sparo.stato = false;
		partita.punteggio.valore += partita.navicella_misteriosa.punteggio;
		collisione = true;
		D2(cout<<"Navicella misteriosa colpita."<<endl);
	}
	return collisione;
}

bool controlloFineOndata (Partita &partita)
{
	if (partita.ondata.alieni_rimasti > 0)
	{
		return false;
	}
	partita.vite_rimanenti++;
	partita.punteggio.valore += 500;
	D1(cout<<"Ondata aliena distrutta."<<endl);
	return true;
}

bool controlloFinePartita (Partita partita)
{
	if (partita.vite_rimanenti < 0)
	{
		D1(cout<<"Partita terminata.."<<endl);
		return true;
	}
	else
	{
		return false;
	}
}

void creaNavicellaMisteriosa (Partita &partita)
{
	srand (time(NULL));	
	if (rand() % (100 / PROBABILITA_COMPARSA_NAVICELLA) == 0) //la navicella viene creata solo se viene rispettata questa condizione. in questo modo compare seguendo un calcolo probabilistico.
	{
		partita.navicella_misteriosa.stato = true;
		partita.navicella_misteriosa.punteggio = (rand() % ((PUNTEGGIO_NAVICELLA_MAX - PUNTEGGIO_NAVICELLA_MIN) / 10)) * 10 + PUNTEGGIO_NAVICELLA_MIN;
		partita.navicella_misteriosa.pos_x = MARGINE_SX_GIOCO;
		D2(cout<<"Navicella misteriosa creata."<<endl);
	}
}

void creaSparoAlieni (Partita &partita)
{
	srand (time(NULL));
	int fattore_casuale = rand() % N_COL_ALIENI; //numero casuale di una colonna d alieni
	bool creato = false;
	while (!creato)
	{
		unsigned int pos_y_attuale  = partita.ondata.pos_y + altezzaAlieno () + DISTANZA_FILE_ALIENI * (N_FILE_ALIENI - 1);
		for (int i = N_FILE_ALIENI - 1; i >= 0 && !creato; i--) //ciclo che controlla dall'ultima fila tutti gli alieni in una colonna
		{
			unsigned int pos_x_attuale = partita.ondata.pos_x - larghezzaSparoAlienoAttuale (partita.sparo_alieni.pos_x) / 2 + DISTANZA_ASSI_COL_ALIENI * fattore_casuale;
			if (partita.ondata.alieni [i] [fattore_casuale].stato)
			{
				partita.sparo_alieni.stato = true;
				partita.sparo_alieni.pos_x = pos_x_attuale;
				partita.sparo_alieni.pos_y = pos_y_attuale;
				creato = true;
				D2(cout<<"Sparo alieno creato."<<endl);
			}
			pos_y_attuale -= DISTANZA_FILE_ALIENI;
		}
		if (!creato) //se quella colonna dell'ondata non ha più alieni, si controlla la successiva
		{
			fattore_casuale = sucInRange (fattore_casuale, N_COL_ALIENI);
		}
	}
}

void creaSparoCarroArmato (Partita &partita)
{
	partita.carro_armato.sparo.stato = true;
	partita.carro_armato.sparo.pos_x = partita.carro_armato.pos_x + larghezzaCarroArmato () / 2;
	partita.carro_armato.sparo.pos_y = MARGINE_INF_GIOCO - altezzaCarroArmato () - altezzaSparoCarroArmato ();
	D2(cout<<"Sparo del carro armato creato."<<endl);
}

bool eliminaFileSalvataggio ()
{
	if (!remove (FILE_SALVATAGGIO_PARTITA))
	{
		D1(cout<<"Rimosso file di salvataggio."<<endl);
		return true;
	}
	return false;
}

bool esisteSalvataggio ()
{
	ifstream f (FILE_SALVATAGGIO_PARTITA);
    	return f;
}

void muoviAlieni (Partita &partita)
{
	unsigned int limite_dx = MARGINE_DX_GIOCO - (larghezzaAlieno (2)) / 2;
	unsigned int limite_sx = MARGINE_SX_GIOCO + (larghezzaAlieno (2)) / 2;
	unsigned int pos_y_carro = MARGINE_INF_GIOCO - altezzaCarroArmato ();
	unsigned int offset_colonne_dx = 0; //numero di colonne totali meno quelle completamente mancanti a partire da destra
	unsigned int offset_colonne_sx = N_COL_ALIENI - 1; //numero di colonne totali meno quelle completamente mancanti a partire da destra
	for (int j = N_COL_ALIENI - 1; j >= 0 && offset_colonne_dx == 0; j--)
	{
		for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
		{
			if (partita.ondata.alieni [i] [j].stato)
			{
				offset_colonne_dx = j;
				break;
			}
		}
	}
	for (unsigned int j = 0; j < N_COL_ALIENI && offset_colonne_sx == N_COL_ALIENI - 1; j++)
	{
		for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
		{
			if (partita.ondata.alieni [i] [j].stato)
			{
				offset_colonne_sx = j;
				break;
			}
		}
	}
	unsigned int margine_dx_primo_asse = limite_dx - DISTANZA_ASSI_COL_ALIENI * offset_colonne_dx; //limite destro del primo asse dell'ondata
	int margine_sx_primo_asse = limite_sx - DISTANZA_ASSI_COL_ALIENI * offset_colonne_sx; //limite sinistro del primo asse dell'ondata
	if (partita.ondata.alieni_rimasti)
	{
		if (partita.ondata.dir_alieni == destra)
		{
			partita.ondata.pos_x = sucInRange (partita.ondata.pos_x, margine_dx_primo_asse);
			if (partita.ondata.pos_x == margine_dx_primo_asse)
			{
				partita.ondata.dir_alieni = sinistra;
				partita.ondata.pos_y = sucInRange (partita.ondata.pos_y, SPOSTAMENTO_ONDATA_GIU, pos_y_carro);
			}
		}
		else if (partita.ondata.dir_alieni == sinistra)
		{
			partita.ondata.pos_x = precInRange (partita.ondata.pos_x, margine_sx_primo_asse);
			if (static_cast <int> (partita.ondata.pos_x) == margine_sx_primo_asse)
			{
				partita.ondata.dir_alieni = destra;
				partita.ondata.pos_y = sucInRange (partita.ondata.pos_y, SPOSTAMENTO_ONDATA_GIU, pos_y_carro);
			}
		}
	}
}

void muoviCarroDestra (Partita &partita)
{
	partita.carro_armato.pos_x = sucInRange (partita.carro_armato.pos_x, MARGINE_DX_GIOCO - larghezzaCarroArmato ());
}

void muoviCarroSinistra (Partita &partita)
{
	partita.carro_armato.pos_x = precInRange (partita.carro_armato.pos_x, MARGINE_SX_GIOCO);
}

void muoviNavicellaMisteriosa (Partita &partita)
{
	unsigned int limite_dx = MARGINE_DX_GIOCO - larghezzaNavicellaMisteriosa ();
	partita.navicella_misteriosa.pos_x = sucInRange (partita.navicella_misteriosa.pos_x, limite_dx);
	if (partita.navicella_misteriosa.pos_x == limite_dx)
	{
		partita.navicella_misteriosa.stato = false;
	}
}

void muoviSparoAlieni (Partita &partita)
{
	unsigned int limite_inferiore = MARGINE_INF_GIOCO - altezzaSparoAlienoAttuale (partita.sparo_alieni.pos_x);
	partita.sparo_alieni.pos_y = sucInRange (partita.sparo_alieni.pos_y, limite_inferiore);
	if (partita.sparo_alieni.pos_y >= limite_inferiore)
	{
		partita.sparo_alieni.stato = false;
	}
}

void muoviSparoCarro (Partita &partita)
{
	partita.carro_armato.sparo.pos_y = precInRange (partita.carro_armato.sparo.pos_y, MARGINE_SUP_GIOCO);
	if (partita.carro_armato.sparo.pos_y == MARGINE_SUP_GIOCO)
	{
		partita.carro_armato.sparo.stato = false;
	}
}

void nuovaOndata (Partita &partita)
{
	unsigned int i;

	for (i = 0; i < N_FILE_ALIENI; i++)
	{		
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			inizializzaAlieno (partita.ondata.alieni [N_FILE_ALIENI - 1 - i] [j], PUNTEGGIO_ALIENI [i / (N_FILE_ALIENI / N_TIPI_ALIENI)]);
		}
	}

	assert (i = N_FILE_ALIENI);
	
	partita.ondata.alieni_rimasti = N_ALIENI_TOTALE;
	
	partita.ondata.dir_alieni = destra;
	
	partita.ondata.pos_x = POS_X_PRIMO_ASSE_ALIENI;
	
	partita.ondata.pos_y = POS_Y_PRIMA_FILA_ONDATA;
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
		inizializzaBarriera (partita.barriere [i]);
	}

	nuovaOndata (partita);

	partita.sparo_alieni.stato = false;
	
	inizializzaNavicellaMisteriosa (partita.navicella_misteriosa);

	inizializzaCarroArmato (partita.carro_armato);
}

unsigned int percentualeAlieniEliminati (Partita partita)
{
	return 100 - partita.ondata.alieni_rimasti * 100 / N_ALIENI_TOTALE;
}

Punteggio * punteggioAttuale (Partita &partita)
{
	return &partita.punteggio;
}

void salvaPartita (Partita partita)
{
	ofstream f(FILE_SALVATAGGIO_PARTITA);
	output (partita, f);
	D1(cout<<"Partita caricata correttamente."<<endl);
}

void stampaPartita (Partita partita)
{
	output (partita, cout);
}

unsigned int statoEsplosioneAlieno (Partita partita, unsigned int n_fila, unsigned int n_colonna)
{
	return partita.ondata.alieni [n_fila] [n_colonna].esplosione;
}

unsigned int statoEsplosioneCarroArmato (Partita partita)
{
	return partita.carro_armato.esplosione;
}

bool statoNavicellaMisteriosa (Partita partita)
{
	return partita.navicella_misteriosa.stato;
}

bool statoSparoAlieni (Partita partita)
{
	return partita.sparo_alieni.stato;
}

bool statoSparoCarroArmato (Partita partita)
{
	return partita.carro_armato.sparo.stato;
}

void terminaEsplosioneAlieno (Partita &partita, unsigned int n_fila, unsigned int n_colonna)
{
	partita.ondata.alieni [n_fila] [n_colonna].esplosione = 0;
}

void terminaEsplosioneCarroArmato (Partita &partita)
{
	partita.carro_armato.esplosione = 0;
}
//FINE MODULO
