/*
 * File contenente il modulo di gestione dei menu.
 */

#include "struttura_dati.h"
#include "funzioni_generiche.h"
#include "gestione_menu.h"

//INIZIO MODULO
void vocePrec (Menu &menu)
{
	menu.voce_sel = precInRangeCircuito (menu.voce_sel, 0, menu.n_voci);
}

void vocePrec (Menu &menu, int voce_saltata)
{
	menu.voce_sel = precInRangeCircuito (menu.voce_sel, 0, menu.n_voci);
	if (menu.voce_sel == voce_saltata)
	{
		menu.voce_sel = precInRangeCircuito (menu.voce_sel, 0, menu.n_voci);
	}
}

void voceSuc (Menu &menu)
{
	menu.voce_sel = sucInRangeCircuito (menu.voce_sel, 0, menu.n_voci);
}

void voceSuc (Menu &menu, int voce_saltata)
{
	menu.voce_sel = sucInRangeCircuito (menu.voce_sel, 0, menu.n_voci);
	if (menu.voce_sel == voce_saltata)
	{
		menu.voce_sel = sucInRangeCircuito (menu.voce_sel, 0, menu.n_voci);
	}
}

void inizializzaMenu (Menu &menu, const char testi_menu [] [MAX_STRINGA_GENERICA], int n_voci, int voce_sel)
{
	menu.n_voci = n_voci;
	menu.voce_sel = voce_sel;
	for (int i = 0; i < menu.n_voci; i++)
	{
		for (int j = 0; j < MAX_STRINGA_GENERICA; j++)
		{
			menu.testi_menu [i] [j] = testi_menu [i] [j];
		}
	}
}

bool stringaValoreVoceImpostazioni (char stringa [], voce_menu_impostazioni voce, Impostazioni impostazioni)
{
	switch (voce)
	{
		case v_musica:
			if (impostazioni.musica)
			{
				strcpy (stringa, "On");
			}
			else
			{
				strcpy (stringa, "Off");
			}
			break;
		case v_eff_audio:
			if (impostazioni.eff_audio)
			{
				strcpy (stringa, "On");
			}
			else
			{
				strcpy (stringa, "Off");
			}
			break;
		case v_mod_grafica:
			switch (impostazioni.mod_grafica)
			{
				case mono_bianco:
					strcpy (stringa, "Monocromo bianco");
					break;
				case mono_giallo:
					strcpy (stringa, "Monocromo giallo");
					break;
				case mono_verde:
					strcpy (stringa, "Monocromo verde");
					break;
				case fasce_vert:
					strcpy (stringa, "Fasce verticali");
					break;
				case fasce_oriz:
					strcpy (stringa, "Fasce orizzontali");
					break;
				case misto:
					strcpy (stringa, "Misto");
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
		case v_mod_grafica:
			impostazioni.mod_grafica = static_cast <grafica> (precInRangeCircuito (impostazioni.mod_grafica, 0, N_MODALITA_GRAFICHE));
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
		case v_mod_grafica:
			impostazioni.mod_grafica = static_cast <grafica> (sucInRangeCircuito (impostazioni.mod_grafica, 0, N_MODALITA_GRAFICHE));
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
//FINE MODULO