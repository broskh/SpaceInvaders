/*
 * File contenente le strutture dati.
 */

#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

const unsigned int N_BARRIERE = 4; /**<Numero delle barriere presenti in una partita*/
const unsigned int LARG_BARRIERA = 20; /**<Largezza della barriera*/ //------------>DA CONTROLLARE<-------------
const unsigned int ALT_BARRIERA = 10; /**<Altezza della barriera*/ //------------>DA CONTROLLARE<-------------
const unsigned int N_FILE_MOSTRI = 5; /**<Numero delle file di mostri*/
const unsigned int N_COL_MOSTRI = 11; /**<Numero delle colonne di mostri*/
const unsigned int CARATTERI_NOME = 4; /**<Numero di caratteri per le stringhe contenti il nome del realizzatore di un punteggio.*/ 
const unsigned int MAX_HIGHSCORES = 10; /**<Numero di punteggi presenti nella classifica degli highscores.*/

/** Tipo che indica una determinata grafica.
 *
 * Sono presenti diverse modalità grafiche:
 * - "mono_bianco", "mono_giallo" e "mono_verde" se si tratta di una grafica monocroma del colore indicato;
 * - "fasce_vert" e "fasce_oriz" se i mostri sono colorati attraverso fasce adiacenti di colori differenti;
 * - "misto" se vogliamo che i mostri siano di colori differenti, e mai uguali per due mostri adiacenti.
 */
enum grafica {mono_bianco, mono_giallo, mono_verde, fasce_vert, fasce_oriz, misto};	//----------------------->aggiungere altre mono?<--------------------

/** Tipo che indica lo stato di ogni "quadrato" che costituisce la barriera.
 *
 * Ogni quadratino costituente la barriera all'interno del gioco inizialmente sarà rappresentato
 * dallo stato "intero". La prima volta che verrà colpito esso si sgretolerà parzialmente e sarà
 * rappresentato dallo stato "parziale". Infine, quando verrà colpito per la seconda volta, il
 * suo stato diventerà "distrutto", e graficamente non sarà più visibile.
 */
enum stato {distrutto, parziale, intero};

/** Tipo che indica una direzione.
 *
 * I mostri eseguono continuamentente un movimento a zig zag. Con questo tipo è possibile indicare
 * la direzione che stanno tenendo in un determinato momento.
 */
enum direzione {destra, sinistra};

/**
 * Tipo che indica una schermata dell'applicazione.
 *
 * All'esecuzione dell'applicaizone ci troveremo nel menù iniziale dal quale poi potremo cambiare schermata.
 * Potremo iniziare a giocare, modificare le opzioni o guardare la classifica dei punteggi migliori.
 */
enum schermata {s_menu, s_gioca, s_opzioni, s_highscores, s_pausa};

/**
 * Tipo che indica una voce del menù iniziale.
 */
enum voce_menu {v_gioca, v_carica, v_opzioni, v_highscores};

/**
 * Struttura per il punteggio.
 *
 * Conserva le informazioni relative ad un singolo punteggio.
 */
struct punteggio
{
	char nome [CARATTERI_NOME]; /**<Nome del giocatore*/
	int valore; /**<Valore del punteggio*/
};

/**
 * Struttura per le impostazioni.
 *
 * Conserva tutte le informazioni relative alle impostazioni del gioco. Da questa struttra quindi
 * è possibile sapere se la musica e gli effetti audio sono abilitati o meno, la modalità grafica scelta e
 * il numero delle vite iniziali.
 */
struct impostazioni
{
	bool musica; /**<Musica on/off*/
	bool eff_audio; /**<Effetti  audio on/off*/
	grafica mod_grafica; /**<Modalità grafica*/
	unsigned int vite_iniziali; /**<Vite iniziali*/
};

/**
 * Struttura per una singola ondata.
 *
 * Ogni volta che si affronta una nuova ondata questa struttura ne conserva le varie informazioni: il numero
 * di mostri non ancora abbattuti, l'indicazione di quali mostri sono vivi e quali no, e la direzione che si
 * sta seguendo nel continuo zig-zag dell'ondata
 */
struct ondata
{	
	bool mostri [N_FILE_MOSTRI] [N_COL_MOSTRI]; /**<Stato mostri*/	
	int mostri_rimasti; /**<Numero di mostri rimasti*/	
	direzione dir_mostri; /**<Direzione dello zig-zag*/
};

/**
 * Struttura per una singola partita.
 *
 * Ogni volta che viene avviata una nuova partita questa struttura ne contiene le informazioni.
 * Conserva il punteggio che si sta accumulando, il numero di vite rimanenti, lo stato delle barriere
 * e le informazioni relative all'ondata di mostri che si sta combattendo.
 */
struct partita
{
	punteggio punteggio_att; /**<Punteggio attuale*/
	unsigned int vite_rimanenti; /**<Vite rimanenti*/
	stato barriere [N_BARRIERE] [ALT_BARRIERA] [LARG_BARRIERA]; /**<Stato attuale delle barriere*/
	ondata ondata_att; /**<Ondata di mostri attuale*/
};

/**
 * Struttura per le informazioni generali del gioco.
 *
 * Contiene le informazioni di tipo generali che devono essere presenti ogni volta che viene
 * avviato il gioco. Conserva le informazioni relative alle impostazioni e ai miglioti punteggi
 * raggiunti.
 */
struct spaceInvaders
{	
	impostazioni impost_att; /**<Impostazioni attuali*/
	punteggio highscores [MAX_HIGHSCORES]; /**<Migliori punteggi raggiunti*/	
	unsigned int n_highscores; /**<Numero di punteggi memorizzati nell'array "highscores"*/
};
