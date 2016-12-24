/*
 * File contenente il modulo per la gestione dei menu.
 */

using namespace std;
#include <iostream>
#include <cstring>
#include <cstdio>
#include "strutture_dati.h"
#include "gestione_menu.h"
#include "gestione_partita.h"

//INIZIO CONFIGURAZIONE TRACING
/*#ifdef DEBUG_MODE
	#ifdef DEBUG_LEVEL
		static unsigned int debug_level = DEBUG_LEVEL;
	#else
		static unsigned int debug_level = 0;
	#endif
#endif*/
//FINE CONFIGURAZIONE TRACING

//INIZIO MODULO
//INIZIO FUNZIONI PRIVATE
/*
 * Inizializza un menù con i valori passati per parametro.
 */
void inizializzaMenu (Menu &menu, const generic_string testi_menu [], int n_voci, int voce_sel)
{
	menu.n_voci = n_voci;
	menu.voce_selezionata = voce_sel;
	int i, j;
	for (i = 0; i < menu.n_voci; i++)
	{
		for (j = 0; testi_menu [i] [j] != '\0'; j++)
		{	
			menu.testi_menu [i] [j] = testi_menu [i] [j];
		}
		menu.testi_menu [i] [j] = '\0';
	}
}

/*
 * Ritorna il numero precedente di n. Se n raggiunge un valore minore di min, riparte da max - 1.
 */
int precInRangeCircuito (int n, int min, int max)
{
	n--;
	if (n < min)
	{
		n = max - 1;
	}
	return n;
}

/*
 * Ritorna il numero successivo di n. Se n raggiunge un valore maggiore di max, riparte da min.
 */
int sucInRangeCircuito (int n, int min, int max)
{
	n++;
	if (n > (max - 1))
	{
		n = min;
	}
	return n;
}
//FINE FUNZIONI PRIVATE

schermata cambiaSchermataMenuPausa (Menu menu, Partita partita_in_corso, bool &partita_salvata)
{
	if (menu.voce_selezionata == v_continua)
	{
		return s_gioca;
	}
	else if (menu.voce_selezionata == v_salva)
	{
		salvaPartita (partita_in_corso);
		partita_salvata = true;
	}
	else if (menu.voce_selezionata == v_abbandona)
	{
		;
	}
	return s_menu;
}

schermata cambiaSchermataMenuPrincipale (Menu menu)
{
	if (menu.voce_selezionata == v_gioca)
	{
		return s_gioca;
	}
	else if (menu.voce_selezionata == v_carica)
	{
		return s_carica;
	}
	else if (menu.voce_selezionata == v_opzioni)
	{
		return s_opzioni;
	}
	else if (menu.voce_selezionata == v_highscores)
	{
		return s_highscores;
	}
	else if (menu.voce_selezionata == v_esci)
	{
		return s_esci;
	}
	return s_menu;
}

void inizializzaMenuImpostazioni (Menu &menu)
{
	inizializzaMenu (menu, MENU_IMPOSTAZIONI, N_VOCI_MENU_IMPO, v_musica);
}

void inizializzaMenuPausa (Menu &menu)
{
	inizializzaMenu (menu, MENU_PAUSA, N_VOCI_MENU_PAUSA, v_continua);
}

void inizializzaMenuPrincipale (Menu &menu)
{
	inizializzaMenu (menu, MENU_PRINCIPALE, N_VOCI_MENU_PRINC, v_gioca);
}

void selezionaPrimaVoce (Menu &menu)
{
	menu.voce_selezionata = 0;
}

bool stringaValoreVoceImpostazioni (char stringa [], voce_menu_impostazioni voce, Impostazioni impostazioni)
{
	switch (voce)
	{
		case v_musica:
			if (impostazioni.musica)
			{
				strcpy (stringa, STRINGA_ON);
			}
			else
			{
				strcpy (stringa, STRINGA_OFF);
			}
			break;
		case v_eff_audio:
			if (impostazioni.eff_audio)
			{
				strcpy (stringa, STRINGA_ON);
			}
			else
			{
				strcpy (stringa, STRINGA_OFF);
			}
			break;
		case v_colori_alieni:
			switch (impostazioni.colore_alieni)
			{
				case verde:
					strcpy (stringa, STRINGA_VERDE);
					break;
				case bianco:
					strcpy (stringa, STRINGA_BIANCO);
					break;
				case arancione:
					strcpy (stringa, STRINGA_ARANCIONE);
					break;
				case giallo:
					strcpy (stringa, STRINGA_GIALLO);
					break;
				case blu:
					strcpy (stringa, STRINGA_BLU);
					break;
			}
			break;
		case v_vite_iniziali:
			sprintf(stringa, "%d", impostazioni.vite_iniziali);
			break;
		default:
			return false;
			break;
	}
	return true;
}

bool valoreCampoImpostazioniPrec (Menu menu, Impostazioni &impostazioni)
{
	switch (menu.voce_selezionata)
	{
		case v_musica:
			impostazioni.musica = !impostazioni.musica;
			break;
		case v_eff_audio:
			impostazioni.eff_audio = !impostazioni.eff_audio;
			break;
		case v_colori_alieni:
			impostazioni.colore_alieni = static_cast <colore> (precInRangeCircuito (impostazioni.colore_alieni, 0, N_COLORI_ALIENI));
			break;
		case v_vite_iniziali:
			impostazioni.vite_iniziali = precInRangeCircuito (impostazioni.vite_iniziali, 1, MAX_VITE + 1);
			break;
		default:
			return false;
			break;
	}
	return true;
}

bool valoreCampoImpostazioniSuc (Menu menu, Impostazioni &impostazioni)
{
	switch (menu.voce_selezionata)
	{
		case v_musica:
			impostazioni.musica = !impostazioni.musica;
			break;
		case v_eff_audio:
			impostazioni.eff_audio = !impostazioni.eff_audio;
			break;
		case v_colori_alieni:
			impostazioni.colore_alieni = static_cast <colore> (sucInRangeCircuito (impostazioni.colore_alieni, 0, N_COLORI_ALIENI));
			break;
		case v_vite_iniziali:
			impostazioni.vite_iniziali = sucInRangeCircuito (impostazioni.vite_iniziali, 1, MAX_VITE + 1);
			break;
		default:
			return false;
			break;
	}
	return true;
}

void vocePrec (Menu &menu)
{
	menu.voce_selezionata = precInRangeCircuito (menu.voce_selezionata, 0, menu.n_voci);
}

void vocePrec (Menu &menu, int voce_saltata)
{
	menu.voce_selezionata = precInRangeCircuito (menu.voce_selezionata, 0, menu.n_voci);
	if (menu.voce_selezionata == voce_saltata)
	{
		menu.voce_selezionata = precInRangeCircuito (menu.voce_selezionata, 0, menu.n_voci);
	}
}

void voceSuc (Menu &menu)
{
	menu.voce_selezionata = sucInRangeCircuito (menu.voce_selezionata, 0, menu.n_voci);
}

void voceSuc (Menu &menu, int voce_saltata)
{
	menu.voce_selezionata = sucInRangeCircuito (menu.voce_selezionata, 0, menu.n_voci);
	if (menu.voce_selezionata == voce_saltata)
	{
		menu.voce_selezionata = sucInRangeCircuito (menu.voce_selezionata, 0, menu.n_voci);
	}
}
//FINE MODULO
