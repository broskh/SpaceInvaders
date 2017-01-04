/*
 * File contenente le strutture dati.
 */

//INIZIO CONFIGURAZIONE PER TRACING
#ifdef DEBUG_MODE
	#define DBG(MIN_DEBUG, ISTRUZIONE) {if ((MIN_DEBUG) <= debug_level) {ISTRUZIONE; } }
#else
	/**
	 * Se si è in modalità debug controlla il livello di debug attivo e se esso è maggiore di quello passato per parametro,
	 * esegue l'istruzione indicata.
	 * 
	 * @param MIN_DEBUG Livello di debug minimo che deve essere attivo per poter eseguire l'istruzione indicata.
	 * @param ISTRUZIONE Istruzione da eseguire nel caso in cui il livello di debug attivo sia consono.
	 */
	#define DBG(MIN_DEBUG, ISTRUZIONE)
#endif

/**
 * Esegue l'istruzione indicata se il livello di debug attivo è uguale a 1.
 * 
 * @param ISTRUZIONE Istruzione da eseguire.
 */
#define D1(ISTRUZIONE) DBG(1, ISTRUZIONE)
/**
 * Esegue l'istruzione indicata se il livello di debug attivo è uguale a 2.
 * 
 * @param ISTRUZIONE Istruzione da eseguire.
 */
#define D2(ISTRUZIONE) DBG(2, ISTRUZIONE)
//FINE CONFIGURAZIONE PER TRACING

//INIZIO COSTANTI BARRIERE
const unsigned int ALTEZZA_BARRIERA = 17; /**<Altezza della barriera (in unità).*/
const unsigned int N_BARRIERE = 4; /**<Numero delle barriere presenti in una partita.*/
const unsigned int LARGHEZZA_BARRIERA = 20; /**<Largezza della barriera (in unità).*/
//FINE COSTANTI BARRIERE

//INIZIO COSTANTI ONDATA
const unsigned int N_COL_ALIENI = 11; /**<Numero delle colonne di alieni di cui è composta l'ondata.*/
const unsigned int N_FILE_ALIENI = 6; /**<Numero delle file di alieni di cui è composta l'ondata.*/
//FINE COSTANTI ONDATA

//INIZIO COSTANTI PUNTEGGI
const int CARATTERI_NOME = 3; /**<Numero di caratteri massimo del nome di un gicoatore.*/
const int MAX_HIGHSCORES = 10; /**<Numero massimo di punteggi che possono essere memorizzati nella classifica degli highscores.*/
//FINE COSTANTI PUNTEGGI

//INIZIO COSTANTI VARIE
const int MAX_N_VOCI_MENU = 5; /**<Numero di voci massime che possono comporre un menù.*/
const int MAX_VITE = 10; /**<Numero massimo di vite.*/
const int N_COLORI_ALIENI = 5; /**<Numero di modalità cromatiche disponibili per la colorazione degli alieni.*/
//FINE COSTANTI VARIE

typedef char generic_long_string [61]; /**<Stringa generica in grado di contenere 60 caratteri.*/

typedef char generic_string [21]; /**<Stringa generica in grado di contenere 20 caratteri.*/

typedef char name_string [CARATTERI_NOME + 1]; /**<Stringa utilizzata per contenere il nome di un giocatore (Max. 3 caratteri).*/

typedef char numbering_string [4]; /**<Stringa utilizzata per la numerazione nella classifica degli highscores.*/

/** 
 * Tipo che indica un colore.
 * Il colore viene utilizzato nelle impostazioni per indicare il colore per gli alieni
 */
enum colore {verde, bianco, arancione, giallo, blu};

/**
 * Tipo che indica una direzione laterale.
 */
enum direzione {destra, sinistra};

/**
 * Tipo che indica una schermata dell'applicazione.
 */
enum schermata {s_menu, s_gioca, s_carica, s_opzioni, s_highscores, s_pausa, s_fine_partita, s_esci};

/**
 * Tipo che indica lo stato di una singola unità che costituisce la barriera.
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
	unsigned int punteggio; /**<Valore del punteggio che il giocatore guadagna dalla distruzione di questo alieno.*/
	unsigned int esplosione; /**<Valore che indica lo stato di evoluzione dell'esplosione dell'alieno.*/
};

/**
 * Struttura per contenere i dati delle impostazioni.
 */
struct Impostazioni
{
	bool musica; /**<Attivazione o disattivazione della musica.*/
	bool effetti_audio; /**<Attivazione o disattivazione degli effetti audio.*/
	colore colore_alieni; /**<Colore per gli alieni.*/
	unsigned int vite_iniziali; /**<Vite iniziali.*/
};

/**
 * Struttura per contenere i dati per la gestione di un menù.
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
	bool stato; /**<Stato della navicella misteriosa che indica se è presente o no.*/
	unsigned int punteggio; /**<Valore del punteggio che il giocatore guadagna dalla distruzione della navicella misteriosa.*/
	unsigned int pos_x; /**<Posizione della navicella misteriosa rispetto all'asse x.*/
	direzione dir_navicella; /**<Direzione del movimento della navicella.*/
};

/**
 * Struttura per contenere i dati di un'ondata.
 */
struct Ondata
{	
	Alieno alieni [N_FILE_ALIENI] [N_COL_ALIENI]; /**<Alieni che compongono l'ondata.*/	
	int alieni_rimasti; /**<Numero di alieni rimasti.*/	
	direzione dir_alieni; /**<Direzione laterale del movimento a zig-zag dell'ondata.*/
	unsigned int pos_x; /**<Posizione dell'alieno nella prima fila e nella prima colonna rispetto all'asse delle x.*/
	unsigned int pos_y; /**<Posizione dell'alieno nella prima fila e nella prima colonna rispetto all'asse delle y.*/
};

/**
 * Struttura per contenere i dati di un punteggio.
 */
struct Punteggio
{
	name_string nome; /**<Nome del realizzatore del punteggio.*/
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
	unsigned int pos_x; /**<Posizione dello sparo rispetto all'asse delle x.*/
	unsigned int pos_y; /**<Posizione dello sparo rispetto all'asse delle y.*/
};

/**
 * Struttura per contenere i dati del carro armato.
 */
struct Carro
{
	unsigned int esplosione; /**<Valore che indica lo stato di evoluzione dell'esplosione del carro armato.*/
	unsigned int pos_x; /**<Indica la posizione del carro armato rispetto all'asse delle x.*/
	Sparo sparo; /**<Informazioni relative allo sparo del carro armato.*/
};

/**
 * Struttura per contenere i dati di una partita.
 */
struct Partita
{
	Punteggio punteggio; /**<Informazioni relative al punteggio della partita.*/
	int vite_rimanenti; /**<Vite rimanenti.*/
	stato_barriera barriere [N_BARRIERE] [ALTEZZA_BARRIERA] [LARGHEZZA_BARRIERA]; /**<Informazioni riguardanti lo stato di deterioramento delle singole unità che compongono le barriere.*/
	Ondata ondata; /**<Informazioni relative all'ondata di alieni.*/
	Sparo sparo_alieni; /**<Informazioni relative allo sparo degli alieni.*/
	Carro carro_armato; /**<Informazioni relative al carro armato.*/
	Navicella navicella_misteriosa; /**<Informazioni relative alla navicella misteriosa.*/
};
