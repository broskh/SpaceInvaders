/*File contenente le strutture dati*/

#include <iostream>
#include <cassert>
using namespace std;

const unsigned int N_BARRIERE = 4; /*Numero delle barriere presenti a partita*/
const unsigned int LARG_BARRIERA = 20; /*Largezza della barriera*/	//------------>DA CONTROLLARE<-------------
const unsigned int ALT_BARRIERA = 10; /*Altezza della barriera*/	//------------>DA CONTROLLARE<-------------
const unsigned int N_FILE_MOSTRI = 5; /*Numero delle file di mostri*/
const unsigned int N_COL_MOSTRI = 11; /*Numero delle colonne di mostri*/
const unsigned int CARATTERI_NOME = 4; /*Numero di caratteri per le stringhe contente il nome del realizzatore di un punteggio.*/
const unsigned int N_HIGHSCORES = 10; /*Numero di punteggi presenti nella classifica degli highscores.*/

/* Tipo grafica per impostazioni.
 *
 * Sono presenti diverse modalità grafiche: "mono_bianco", "mono_giallo" e "mono_verde"
 * se si tratta di una grafica monocroma del colore indicato; "fasce_vert" e "fasce_oriz"
 * se i mostri sono colorati attraverso fasce adiacenti di colori differenti; e infine "misto"
 * se vogliamo che i mostri siano di colori differenti, e mai uguali per due mostri adiacenti.
 */
enum grafica {mono_bianco, mono_giallo, mono_verde, fasce_vert, fasce_oriz, misto};	//aggiungere altre mono?

/* Tipo stato per ogni quadrato che costituisce la barriera.
 *
 * Ogni quadratino costituente la barriera all'interno del gioco inizialmente sarà rappresentato
 * dallo stato "intero". La prima volta che verrà colpito esso si sgretolerà parzialmente e sarà
 * rappresentato dallo stato "parziale". Infine, quando verrà colpito per la seconda volta, il
 * suo stato diventerà "distrutto", e graficamente non sarà più visibile.
 */
enum stato {distrutto, parziale, intero};

/* Tipo stato per indicare la direzione dello zig-zag dei mostri.
 *
 * I mostri eseguono continuamentente un movimento a zig zag. Con questo tipo è possibile indicare
 * la direzione che stanno tenendo in un determinato momento.
 */
enum direzione {destra, sinistra};

/*
 * Struttura per il punteggio.
 *
 * Conserva le informazioni relative ad un singolo punteggio.
 */
struct punteggio
{
	char nome [CARATTERI_NOME]; /*Nome del giocatore*/
	int valore; /*Valore del punteggio*/
}

/*
 * Struttura delle impostazioni.
 *
 * Conserva tutte le informazioni derivanti dal settaggio delle impostazioni. Da questa struttra quindi
 * è possibile sapere se la musica e gli effetti audio sono abilitati o meno, la modalità grafica scelta e
 * il numero delle vite iniziali.
 */
struct impostazioni
{
	bool musica;	/*Musica on/off*/
	bool eff_audio;	/*Effetti  audio on/off*/
	grafica mod_grafica;	/*Modalità grafica*/
	unsigned int vite_iniziali;	/*Vite iniziali*/
};

/*
 * Struttura di una singola ondata.
 *
 * Ogni volta che si affronta una nuova ondata questa struttura ne conserva le varie informazioni: il numero
 * di mostri non ancora abbattuti, l'indicazione di quali mostri sono vivi e quali no, e la direzione che si
 * sta seguendo nel continuo zig-zag dell'ondata
 */
struct ondata
{
	bool mostri [N_FILE_MOSTRI] [N_COL_MOSTRI];	/*Stato mostri*/
	int mostri_rimasti;	/*Numero di mostri rimasti*/
	direzione dir_mostri;	/*Direzione dello zig-zag*/
};

/*
 * Struttura di una singola partita.
 *
 * Ogni volta che viene avviata una nuova partita questa struttura ne contiene le informazioni.
 * Conserva il punteggio che si sta accumulando, il numero di vite rimanenti, lo stato delle barriere
 * e le informazioni relative all'ondata di mostri che si sta combattendo.
 */
struct partita
{
	punteggio punteggio_att	/*Punteggio della partita*/
	unsigned int vite_rimanenti;	/*Vite rimanenti*/
	stato barriere [ALT_BARRIERA] [LARG_BARRIERA] [N_BARRIERE];	/*Stato attuale delle barriere*/
	ondata ondata_att;	/*Ondata di mostri attuale*/
};

/*
 * Struttura generale del gioco.
 *
 * Contiene le informazioni di tipo generali che devono essere presenti ogni volta che viene
 * avviato il gioco. Conserva le informazioni relative alle impostazioni, alla partita attuale
 * (se avviata) e il punteggio massimo raggiunto in ogni partita.
 */
struct spaceInvaders
{
	impostazioni impost_att;	/*Impostazioni attuali*/
	partita partita_att;	/*Partita attuale*/
	punteggio highscores [N_HIGHSCORES];	/*Highscores*/
};
