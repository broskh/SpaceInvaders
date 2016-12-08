/*
 * File contenente il modulo per la gestione dei menu.
 */


#include <cstring>
#include <cstdio>
#include "strutture_dati.h"
#include "gestione_menu.h"

//INIZIO MODULO
int precInRangeCircuito (int n, int min, int max)
{
	n--;
	if (n < min)
	{
		n = max - 1;
	}
	return n;
}

int sucInRangeCircuito (int n, int min, int max)
{
	n++;
	if (n > (max - 1))
	{
		n = min;
	}
	return n;
}

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

bool valoreCampoImpostazioniPrec (voce_menu_impostazioni voce, Impostazioni &impostazioni)
{
	switch (voce)
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

bool valoreCampoImpostazioniSuc (voce_menu_impostazioni voce, Impostazioni &impostazioni)
{
	switch (voce)
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