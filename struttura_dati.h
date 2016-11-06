/*
 * File contenente le strutture dati.
 */

#include <allegro5/allegro.h>

const unsigned int N_BARRIERE = 4; /**<Numero delle barriere presenti in una partita.*/
const unsigned int LARG_BARRIERA = 20; /**<Largezza della barriera.*/
const unsigned int ALT_BARRIERA = 17; /**<Altezza della barriera.*/
const unsigned int N_FILE_ALIENI = 6; /**<Numero delle file di alieni.*/
const unsigned int N_COL_ALIENI = 11; /**<Numero delle colonne di alieni.*/

const int N_COLORI_ALIENI = 5; /**<Numero di modalità grafiche disponibili.*/
const int MAX_VITE = 10; /**<Numero massimo di vite.*/
const int CARATTERI_NOME = 3; /**<Numero di caratteri per le stringhe contenti il nome del realizzatore di un punteggio.*/ 
const int MAX_HIGHSCORES = 10; /**<Numero di punteggi presenti nella classifica degli highscores.*/

const int MAX_STRINGA_GENERICA = 20; /**<Numero di caratteri massimo utilizzato per stringhe generiche.*/
const int MAX_STRINGA_NUMERAZIONE = 4; /**<Numero di caratteri massimo utilizzato per le stringhe conteneti la numerazione nella classifica degli highscore.*/
const int MAX_STRINGA_GENERICA_LUNGA = 60; /**<Numero di caratteri masssimo utilizzato per stringhe generiche lunghe.*/
const int MAX_N_VOCI = 5; /**<Numero di voci masssime presenti in un menu.*/

/** Tipo che indica una determinata grafica.
 *
 * Sono presenti diverse modalità grafiche:
 * - "mono_bianco", "mono_giallo" e "mono_verde" se si tratta di una grafica monocroma del colore indicato;
 * - "fasce_vert" e "fasce_oriz" se i alieni sono colorati attraverso fasce adiacenti di colori differenti;
 * - "misto" se vogliamo che i alieni siano di colori differenti, e mai uguali per due alieni adiacenti.
 */
enum colore {verde, bianco, arancione, giallo, blu};

/** Tipo che indica lo stato di ogni "quadrato" che costituisce la barriera.
 *
 * Ogni quadratino costituente la barriera all'interno del gioco inizialmente sarà rappresentato
 * dallo stato "intero". La prima volta che verrà colpito esso si sgretolerà parzialmente e sarà
 * rappresentato dallo stato "parziale". Infine, quando verrà colpito per la seconda volta, il
 * suo stato diventerà "distrutto", e graficamente non sarà più visibile.
 */
enum stato_barriera {distrutta, parziale, integra};

/** Tipo che indica una direzione.
 *
 * I alieni eseguono continuamentente un movimento a zig zag. Con questo tipo è possibile indicare
 * la direzione che stanno tenendo in un determinato momento.
 */
enum direzione {destra, sinistra};

/**
 * Tipo che indica una schermata dell'applicazione.
 *
 * All'esecuzione dell'applicaizone ci troveremo nel menù iniziale dal quale poi potremo cambiare schermata.
 * Potremo iniziare a giocare, modificare le opzioni o guardare la classifica dei punteggi migliori.
 */
enum schermata {s_menu, s_gioca, s_carica, s_opzioni, s_highscores, s_pausa, s_fine_partita, s_esci};

/**
 * Tipo che indica una voce del menù principale.
 */
enum voce_menu_principale {v_gioca, v_carica, v_opzioni, v_highscores, v_esci};

/**
 * Tipo che indica una voce del menù impostazioni.
 */
enum voce_menu_impostazioni {v_musica, v_eff_audio, v_colori_alieni, v_vite_iniziali};

/**
 * Tipo che indica una voce del menù di pausa.
 */
enum voce_menu_pausa {v_continua, v_salva, v_abbandona};

/**
 * Struttura per il punteggio.
 *
 * Conserva le informazioni relative ad un singolo punteggio.
 */
struct Punteggio
{
	char nome [CARATTERI_NOME + 1]; /**<Nome del giocatore.*/
	int valore; /**<Valore del punteggio.*/
};

/**
 * Struttura per le impostazioni.
 *
 * Conserva tutte le informazioni relative alle impostazioni del gioco. Da questa struttura quindi
 * è possibile sapere se la musica e gli effetti audio sono abilitati o meno, la modalità grafica scelta e
 * il numero delle vite iniziali.
 */
struct Impostazioni
{
	bool musica; /**<Musica on/off.*/
	bool eff_audio; /**<Effetti  audio on/off.*/
	colore colore_alieni; /**<Modalità grafica.*/
	unsigned int vite_iniziali; /**<Vite iniziali.*/
};

/**
 * Struttura per i msotri.
 * 
 * Da questa struttura dati è possibile prelevare le informazioni relative allo stato e al punteggio di un alieno. 
 */
struct Alieno
{
	bool stato; /**<Stato del alieno.*/
	unsigned int punteggio; /**<Punteggio derivante dalla distruzione di questo alieno.*/
	unsigned int esplosione;
};

/**
 * Struttura per una singola ondata.
 *
 * Ogni volta che si affronta una nuova ondata questa struttura ne conserva le varie informazioni: il numero
 * di alieni non ancora abbattuti, l'indicazione di quali alieni sono vivi e quali no, e la direzione che si
 * sta seguendo nel continuo zig-zag dell'ondata.
 */
struct Ondata
{	
	Alieno alieni [N_FILE_ALIENI] [N_COL_ALIENI]; /**<Stato alieni.*/	
	int alieni_rimasti; /**<Numero di alieni rimasti.*/	
	direzione dir_alieni; /**<Direzione dello zig-zag.*/
	unsigned int pos_x; /**<Indica la posizione rispetto all'asse delle x del alieno nella prima fila e prima colonna.*/
	unsigned int pos_y; /**<Indica la posizione rispetto all'asse delle y del alieno nella prima fila e prima colonna.*/
};

/**
 * Struttura per un singolo sparo.
 *
 * Sia il carro armato che gli alieni possono sparare dei colpi. Con questa struttua è possibile contenere le
 * informazioni relative ad un singolo sparo.
 */
struct Sparo
{
	bool stato; /**<Indica se è stato sparato un colpo da parte del carro armato.*/
	unsigned int pos_x; /**<Indica la posizione rispetto all'asse delle x del colpo sparato dal carro armato.*/
	unsigned int pos_y; /**<Indica la posizione rispetto all'asse delle y del colpo sparato dal carro armato.*/
};

struct Carro
{
	unsigned int esplosione;
	unsigned int pos_x; /**<Indica lo spostamento del carro armato rispetto alla posizione centrale iniziale.*/
	Sparo sparo; /**<Informazioni relative allo sparo del carro armato.*/
};

struct Navicella
{
	bool stato;
	unsigned int punteggio; /**<Punteggio attribuito alla navicella misteriosa.*/
	unsigned int pos_x; /**<Posizione relativa all'asse x della navicella misteriosa.*/
};

/**
 * Struttura per una singola partita.
 *
 * Ogni volta che viene avviata una nuova partita questa struttura ne contiene le informazioni.
 * Conserva il punteggio che si sta accumulando, il numero di vite rimanenti, lo stato delle barriere
 * e le informazioni relative all'ondata di alieni che si sta combattendo.
 */
struct Partita
{
	Punteggio punteggio; /**<Punteggio attuale.*/
	int vite_rimanenti; /**<Vite rimanenti.*/
	stato_barriera barriere [N_BARRIERE] [ALT_BARRIERA] [LARG_BARRIERA]; /**<Stato attuale delle barriere.*/
	Ondata ondata; /**<Ondata di alieni attuale.*/
	Sparo sparo_alieni; /**<Informazioni relative allo sparo dei alieni.*/
	Carro carro_armato;
	Navicella navicella_misteriosa;
};

/**
 * Struttura per le informazioni generali del gioco.
 *
 * Contiene le informazioni di tipo generali che devono essere presenti ogni volta che viene
 * avviato il gioco. Conserva le informazioni relative alle impostazioni e ai miglioti punteggi
 * raggiunti.
 */
struct SpaceInvaders
{	
	Impostazioni impostazioni; /**<Impostazioni attuali.*/
	Punteggio highscores [MAX_HIGHSCORES]; /**<Migliori punteggi raggiunti.*/	
	int n_highscores; /**<Numero di punteggi memorizzati nell'array "highscores".*/
	bool partita_salvata; /**<Booleano che indica se è presente una partita salvata o no.*/
	Partita partita_in_corso; /**<Struttura {@link Partita} che contiene le informazioni relative alla partita in corso, o alla prossima partita che si giocherà.*/
};

/**
 * Struttura per la gestione dei menu.
 *
 * Contiene le informazioni relative al numero di voci totali del menu e alla voce selezionata attualemtne.
 * Inoltre contiene una variabile per sapere se la voce selezionata è da disegnare o no; in questo modo
 * è possibile creare un effetto di lampeggiamento sulla voce selezionata.
 */
struct Menu
{
	char testi_menu [MAX_N_VOCI] [MAX_STRINGA_GENERICA]; /**<Testi rappresentanti le voci del menù.*/
	int n_voci; /**<Numero di voci presenti nel menù.*/
	int voce_sel; /**<Voce del menù attualmente selezionata.*/
};