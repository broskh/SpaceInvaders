/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

//INIZIO INTERFACCIA

const char STRINGA_M_10 [] = "B"; /**<Stringa per rappresentare il mostro M_10.*/
const unsigned int PUNTEGGIO_M_10 = 10; /**<Punteggio attribuito al mostro M_10.*/
const char STRINGA_M_20 [] = "D"; /**<Stringa per rappresentare il mostro M_20.*/
const unsigned int PUNTEGGIO_M_20 = 20; /**<Punteggio attribuito al mostro M_20.*/
const char STRINGA_M_30 [] = "F"; /**<Stringa per rappresentare il mostro M_30.*/
const unsigned int PUNTEGGIO_M_30 = 30; /**<Punteggio attribuito al mostro M_30.*/
const char STRINGA_M_X [] = "2"; /**<Stringa per rappresentare la navicella misteriosa (M_X).*/
const unsigned int PUNTEGGIO_M_X_MAX = 500; /**<Punteggio massimo attribuito al mostro M_X.*/
const unsigned int PUNTEGGIO_M_X_MIN = 100; /**<Punteggio minimo attribuito al mostro M_X.*/

const char STRINGA_CARRO_ARMATO [] = "-"; /**<Stringa per rappresentare il carro armato.*/
const char STRINGA_SPARO [] = "|";

const unsigned int LATO_UNITA = 4; /**<Lunghezza in pixel di ogni unità costituente le barriere.*/

const unsigned int N_MOSTRI_TOTALE = N_FILE_MOSTRI * N_COL_MOSTRI; /**<Numero totale dei mostri presenti inizialmente*/

/*
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso destra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 * @param limite_offset Limite dell'offset positivo.
 *
 * @return il nuovo valore dell'offset del carro armato.
 */
int offsetDestraCarro (int offset_carro, int limite_offset);

/*
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso sinistra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 * @param limite_offset Limite dell'offset negativo.
 *
 * @return il nuovo valore dell'offset del carro armato.
 */
int offsetSinistraCarro (int offset_carro, int limite_offset);

/*
 * Indica se esiste o meno una partita precedentemente salvata.
 * 
 * @param file Percorso del file dove verificare la presenza del salvataggio.
 * 
 * @return "true" se esiste una partita precedentemente salvata, "false" altrimenti.
 */
bool esisteSalvataggio (const char file []);

/**
 * Memorizza in una struttura {@link Ondata} i valori necessari per la realizzazione di una nuova ondata.
 *
 * @param ondata Struttura {@link Ondata} nella quale verranno memorizzati i valori.
 */
void nuovaOndata (Ondata &ondata);

/**
 * Memorizza in una struttura {@link Partita} i valori necessari per iniziare una nuova partita.
 *
 * @param partita Struttura {@link Partita} nella quale verranno memorizzati i valori.
 * @param impostazioni Struttura {@link Impostazioni} dal quale verranno prelevate alcune informazioni necessari per la corretta inizializzazione di una nuova partita.
 */
void nuovaPartita (Partita &partita, Impostazioni impostazioni);

/**
 * Carica da un file una partita lasciata in sospeso.
 * 
 * @param salvataggio Struttura {@link partita} contenente i dati della partita caricata.
 * @param file File dal quale caricare la partita.
 * 
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaPartita (Partita &salvataggio, const char file []);

/**
 * Salva una partita da sospendere su un file.
 *
 * salvataggio struttura {@link partita} contenente i dati della partita da salvare sul file. 
 * file File nel quale salvare la partita.
 */
void salvaPartita (Partita salvataggio, const char file []);

/**
 * Elimina un file di salvataggio nel caso in cui esista.
 *
 * @param file File di salvataggio da eliminare.
 * 
 * @return "true" se il file era presente ed è stato eliminato, "false" altrimenti.
 */
bool eliminaFileSalvataggio (const char file []);

//FINE INTERFACCIA
