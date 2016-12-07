/*
 * File contenente le strutture dati.
 */

//INIZIO COSTANTI BARRIERE
const unsigned int ALTEZZA_BARRIERA = 17; /**<Altezza della barriera (in unità).*/
const unsigned int N_BARRIERE = 4; /**<Numero delle barriere presenti in una partita.*/
const unsigned int LARGHEZZA_BARRIERA = 20; /**<Largezza della barriera (in unità).*/
//FINE COSTANTI BARRIERE

//INIZIO COSTANTI ONDATA
const unsigned int N_COL_ALIENI = 11; /**<Numero delle colonne di alieni.*/
const unsigned int N_FILE_ALIENI = 6; /**<Numero delle file di alieni.*/
//FINE COSTANTI ONDATA

//INIZIO COSTANTI PUNTEGGI
const int CARATTERI_NOME = 3; /**<Numero di caratteri per le stringhe contenti il nome di un giocatore.*/ 
const int MAX_HIGHSCORES = 10; /**<Numero massimo di punteggi presenti nella classifica degli highscores.*/
//FINE COSTANTI PUNTEGGI

//INIZIO COSTANTI VARIE
const int MAX_N_VOCI_MENU = 5; /**<Numero di voci massime presenti in un menu.*/
const int MAX_VITE = 10; /**<Numero massimo di vite.*/
const int N_COLORI_ALIENI = 5; /**<Numero di modalità cromatiche disponibili per la colorazione degli alieni.*/
//FINE COSTANTI VARIE

typedef char generic_long_string [61]; /**<Stringa generica in grado di contenere 60 caratteri.*/

typedef char generic_string [21]; /**<Stringa generica in grado di contenere 20 caratteri.*/

/** Tipo che indica un colore.
 *
 * Il colore viene utilizzato nelle impostazioni per indicare il colore per gli alieni
 */
enum colore {verde, bianco, arancione, giallo, blu};

/** Tipo che indica una direzione.
 *
 * Gli alieni eseguono continuamentente un movimento a zig zag. Con questo tipo è possibile indicare
 * la direzione nella quale si stanno muovendo.
 */
enum direzione {destra, sinistra};

/**
 * Tipo che indica una schermata dell'applicazione.
 *
 * All'esecuzione dell'applicaizone ci troveremo nel menù iniziale dal quale poi potremo cambiare schermata.
 */
enum schermata {s_menu, s_gioca, s_carica, s_opzioni, s_highscores, s_pausa, s_fine_partita, s_esci};

/** Tipo che indica lo stato di ogni unità che costituisce la barriera.
 *
 * Ogni unità costituente la barriera all'interno del gioco inizialmente sarà rappresentato
 * dallo stato "intero". La prima volta che verrà colpito esso si sgretolerà parzialmente e sarà
 * rappresentato dallo stato "parziale". Infine, quando verrà colpito per la seconda volta, il
 * suo stato diventerà "distrutto", e graficamente non sarà più visibile.
 */
enum stato_barriera {distrutta, parziale, integra};

/**
 * Tipo che indica una voce del menù impostazioni.
 */
enum voce_menu_impostazioni {v_musica, v_eff_audio, v_colori_alieni, v_vite_iniziali};

/**
 * Tipo che indica una voce del menù di pausa.
 */
enum voce_menu_pausa {v_continua, v_salva, v_abbandona};

/**
 * Tipo che indica una voce del menù principale.
 */
enum voce_menu_principale {v_gioca, v_carica, v_opzioni, v_highscores, v_esci};

/**
 * Struttura per contenere i dati di un alieno.
 */
struct Alieno
{
	bool stato; /**<Stato dell'alieno che indica se è stato colpito o no.*/
	unsigned int punteggio; /**<Punteggio che il giocatore guadagna dalla distruzione di questo alieno.*/
	unsigned int esplosione; /**<Evoluzione dello stato di esplosione dell'alieno dal momento in cui è stato colpito.*/
};

/**
 * Struttura per contenere i dati delle impostazioni.
 */
struct Impostazioni
{
	bool musica; /**<Attivazione o disattivazione della musica.*/
	bool eff_audio; /**<Attivazione o disattivazione degli effetti audio.*/
	colore colore_alieni; /**<Colore per gli alieni.*/
	unsigned int vite_iniziali; /**<Vite iniziali.*/
};

/**
 * Struttura per contenere i dati per la gestione dei menù.
 */
struct Menu
{
	generic_string testi_menu [MAX_N_VOCI_MENU]; /**<Testi usati per rappresentare le voci del menù.*/
	int n_voci; /**<Numero di voci presenti nel menù.*/
	int voce_selezionata; /**<Voce del menù attualmente selezionata.*/
};

/**
 * Struttura per contenere i dati della navicella misteriosa.
 */
struct Navicella
{
	bool stato; /**<Stato della navicella misteriosa che indica se è comparsa o no.*/
	unsigned int punteggio; /**<Punteggio che il giocatore guadagna dalla distruzione di questa navicella misteriosa.*/
	unsigned int pos_x; /**<Posizione rispetto all'asse x della navicella misteriosa.*/
};

/**
 * Struttura per contenere i dati di un'ondata.
 */
struct Ondata
{	
	Alieno alieni [N_FILE_ALIENI] [N_COL_ALIENI]; /**<Alieni componenti l'ondata.*/	
	int alieni_rimasti; /**<Numero di alieni rimasti.*/	
	direzione dir_alieni; /**<Direzione del movimento a zig-zag dell'ondata.*/
	unsigned int pos_x; /**<Posizione rispetto all'asse delle x dell'alieno nella prima fila e prima colonna.*/
	unsigned int pos_y; /**<Posizione rispetto all'asse delle y dell'alieno nella prima fila e prima colonna.*/
};

/**
 * Struttura per contenere i dati di un punteggio.
 */
struct Punteggio
{
	char nome [CARATTERI_NOME + 1]; /**<Nome del giocatore.*/
	int valore; /**<Valore del punteggio.*/
};

/**
 * Struttura per contenere i dati della classifica dei punteggi migliori.
 */
struct Classifica
{
	Punteggio highscores [MAX_HIGHSCORES]; /**<Punteggi presenti nella classifica.*/	
	int n_highscores; /**<Numero di punteggi presenti nella classifica.*/
};

/**
 * Struttura per contenere i dati di uno sparo.
 */
struct Sparo
{
	bool stato; /**<Stato dello sparo che indica se è stato effettuato o no.*/
	unsigned int pos_x; /**<Posizione rispetto all'asse delle x dello sparo.*/
	unsigned int pos_y; /**<Posizione rispetto all'asse delle y dello sparo.*/
};

/**
 * Struttura per contenere i dati del carro armato.
 */
struct Carro
{
	unsigned int esplosione; /**<Evoluzione dello stato di esplosione del carro armato dal momento in cui è stato colpito.*/
	unsigned int pos_x; /**<Indica la posizione rispetto all'asse delle x del carro armato.*/
	Sparo sparo; /**<Informazioni relative allo sparo del carro armato.*/
};

/**
 * Struttura per contenere i dati di una partita.
 */
struct Partita
{
	Punteggio punteggio; /**<Punteggio della partita.*/
	int vite_rimanenti; /**<Vite rimanenti.*/
	stato_barriera barriere [N_BARRIERE] [ALTEZZA_BARRIERA] [LARGHEZZA_BARRIERA]; /**<Stato che indica il deterioramento delle unità delle barriere.*/
	Ondata ondata; /**<Ondata di alieni.*/
	Sparo sparo_alieni; /**<Informazioni relative allo sparo degli alieni.*/
	Carro carro_armato; /**<Informazioni relative allo sparo del carro armato.*/
	Navicella navicella_misteriosa; /**<Informazioni relative alla navicella misteriosa.*/
};