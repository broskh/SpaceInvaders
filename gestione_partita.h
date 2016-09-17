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
const unsigned int LUNGHEZZA_PIXEL_BARRIERA = LATO_UNITA * LARG_BARRIERA;

bool controlloCollisioneBarriereSparoMostri (Partita &partita, const unsigned int pos_x_prima_barriera, const unsigned pos_y_prima_barriera, const unsigned int distanza_barriere, const unsigned int altezza_sparo);

bool controlloCollisioneBarriereSparoCarro (Partita &partita, const unsigned int pos_x_prima_barriera, const unsigned pos_y_prima_barriera, const unsigned int distanza_barriere);

ALLEGRO_BITMAP * sparoScelto (int pos_x, ALLEGRO_BITMAP *sparo_mostri_1, ALLEGRO_BITMAP *sparo_mostri_2);

const unsigned int N_MOSTRI_TOTALE = N_FILE_MOSTRI * N_COL_MOSTRI; /**<Numero totale dei mostri presenti inizialmente*/

void creaSparoMostri (Partita &partita, const unsigned int dim_font_mostri, const unsigned int distanza_file_mostri, const ALLEGRO_FONT *font_mostri, const unsigned int distanza_assi_col_mostri);

bool controlloCollisioneBarriere (Partita &partita, const unsigned int pos_x_prima_barriera, const unsigned pos_y_prima_barriera, const unsigned int distanza_barriere);

bool controlloCollisioneCarro (Partita &partita,  const ALLEGRO_FONT *font_mostri, const unsigned int dim_font_mostri, const unsigned int distanza_file_mostri, const unsigned int distanza_assi_col_mostri, const unsigned int pos_y_carro);

bool controlloCollisioneMostri (Partita &partita, const unsigned int dim_font_mostri, const unsigned int distanza_file_mostri, const ALLEGRO_FONT *font_mostri, const unsigned int distanza_assi_col_mostri);

void muoviSparoMostri (Sparo &sparo, const unsigned int limite_inf);

void muoviMostri(Ondata &ondata, const unsigned int limite_sx, const unsigned int limite_dx, const unsigned int limite_inf, const unsigned int distanza_assi_colonne_mostri, const unsigned int larghezza_colonna, const unsigned int distanza_file_mostri);

/**
 * Stabilisce qual'è la posizione rispetto all'asse y dello sparo del carro armato in movimento.
 * 
 * @param sapro Sparo del carro armato.
 * @param limite_sup Limite superiore dello sparo del carro armato.
 */
void muoviSparoCarro (Sparo &sparo, const unsigned int limite_sup);

/**
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso destra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 * @param limite_dx Limite dello spostamento del carro armato verso destra.
 */
void muoviDestraCarro (unsigned int &pos_x_carro, const int limite_dx);

/**
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso sinistra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 * @param limite_dx Limite dello spostamento del carro armato verso sinistra.
 */
void muoviSinistraCarro (unsigned int &pos_x_carro, const int limite_sx);

/**
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
void nuovaOndata (Ondata &ondata, const unsigned int pos_x_iniziale, const unsigned int pos_y_iniziale);

/**
 * Memorizza in una struttura {@link Partita} i valori necessari per iniziare una nuova partita.
 *
 * @param partita Struttura {@link Partita} nella quale verranno memorizzati i valori.
 * @param impostazioni Struttura {@link Impostazioni} dal quale verranno prelevate alcune informazioni necessari per la corretta inizializzazione di una nuova partita.
 * @param pos_x_iniziale_carro Posizione iniziale rispetto all'asse x del carro armato.
 */
void nuovaPartita (Partita &partita, Impostazioni impostazioni, const unsigned int pos_x_iniziale_carro, const unsigned int pos_x_iniziale_ondata, const unsigned int pos_y_iniziale_ondata);

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
 * @param spaceInvaders struttura {@link SpaceInvaders} contenente tutte le informazioni relative al gioco in esecuzione.
 * @param file File nel quale salvare la partita.
 */
void salvaPartita (SpaceInvaders &spaceInvaders, const char file []);

/**
 * Elimina un file di salvataggio nel caso in cui esista.
 *
 * @param file File di salvataggio da eliminare.
 * @param spaceInvaders Struttura {@link SpaceInvaders} contenente tutte le informazioni relative al gioco in esecuzione.
 * 
 * @return "true" se il file era presente ed è stato eliminato, "false" altrimenti.
 */
bool eliminaFileSalvataggio (const char file [], SpaceInvaders &spaceInvaders);

//FINE INTERFACCIA
