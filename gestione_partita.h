/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

const unsigned int DIMENSIONE_LATO_UNITA_BARRIERA = 4; /**<Lunghezza in pixel di ogni unità costituente le barriere.*/
const unsigned int LUNGHEZZA_PIXEL_BARRIERA = DIMENSIONE_LATO_UNITA_BARRIERA * LARG_BARRIERA;
const unsigned int N_MOSTRI_TOTALE = N_FILE_MOSTRI * N_COL_MOSTRI; /**<Numero totale dei mostri presenti inizialmente*/

extern char STRINGA_MOSTRO_3 []; /**<Stringa per rappresentare il mostro 3.*/
extern char STRINGA_MOSTRO_2 []; /**<Stringa per rappresentare il mostro 2.*/
extern char STRINGA_MOSTRO_1 []; /**<Stringa per rappresentare il mostro 1.*/
extern char STRINGA_NAVICELLA []; /**<Stringa per rappresentare la navicella misteriosa.*/
extern char STRINGA_CARRO_ARMATO []; /**<Stringa per rappresentare il carro armato.*/
extern char STRINGA_SPARO []; /**<Stringa per rappresentare lo sparo del carro armato.*/

extern unsigned int PUNTEGGIO_MOSTRO_3; /**<Punteggio attribuito al mostro 3.*/
extern unsigned int PUNTEGGIO_MOSTRO_2; /**<Punteggio attribuito al mostro 2.*/
extern unsigned int PUNTEGGIO_MOSTRO_1; /**<Punteggio attribuito al mostro 1.*/
extern unsigned int PUNTEGGIO_NAVICELLA_MAX; /**<Punteggio massimo attribuito alla navicella.*/
extern unsigned int PUNTEGGIO_NAVICELLA_MIN; /**<Punteggio minimo attribuito alla navicella.*/

extern unsigned int PROBABILITA_COMPARSA_NAVICELLA; /**<Probabilità percentuale di comparsa della navicella misteriosa.*/

extern unsigned int MARGINE_SX_GIOCO; /**<Margine sinistro del gioco.*/
extern unsigned int POS_X_PRIMA_BARRIERA;
extern unsigned int POS_Y_BARRIERE; /**<Posizone rispetto all'asse y dalla quale mostrare la prima barriera.*/
extern unsigned int DISTANZA_BARRIERE; /**<Distanza in pixel fra le barriere.*/
extern unsigned int DIM_MOSTRI; /**<Dimensione del font utilizzato per i mostri*/
extern unsigned int DISTANZA_FILE_MOSTRI; /**<Distamza fra le file di mostri.*/
extern unsigned int DISTANZA_ASSI_COL_MOSTRI; /**<Distanza fra gli assi delle colonne di mostri.*/
extern unsigned int MARGINE_SUP_GIOCO; /**<Margine superiore del gioco.*/
extern unsigned int MARGINE_DX_GIOCO; /**<Margine destro del gioco.*/
extern unsigned int DIM_FONT_TESTO; /**<Dimensione del font utilizzato per i testi generali.*/
extern unsigned int POS_Y_CARRO; /**<Posizione rispetto all'asse y dalla quale mostrare il carro armato.*/
extern unsigned int MARGINE_INF_GIOCO; /**<Margine inferiore del gioco.*/
extern unsigned int POS_X_PRIMO_ASSE_MOSTRI; /**<Posizone rispetto all'asse x nella quale è presente il primo asse delle colonne di mostri.*/
extern unsigned int POS_Y_PRIMA_FILA_ONDATA; /**<Posizione rispetto all'asse y dalla quale mostrare la prima fila di mostri.*/
extern char FILE_SALVATAGGIO_PARTITA []; /**<Percorso del file contenente la partita salvata.*/
extern unsigned int LARGHEZZA_DISPLAY; /**<Larghezza della finestra del gioco.*/
extern unsigned int ALTEZZA_DISPLAY; /**<Altezza della finestra del gioco.*/

//INIZIO INTERFACCIA
void stampa (Partita partita);

bool controlloCollisioneBarriereDaOndata (Partita &partita, const ALLEGRO_FONT *font_mostri);

bool controlloCollisioneNavicellaMisteriosa (Partita &partita, const unsigned int larghezza_navicella);

void creaNavicellaMisteriosa (Partita &partita);

void muoviNavicellaMisteriosa (Partita &partita, unsigned int larghezza_navicella);

bool controlloCollisioneCarroDaSparoMostri (Partita &partita, const unsigned int larghezza_carro, const unsigned int altezza_sparo);

bool controlloCollisioneBarriereDaSparoMostri (Partita &partita, const unsigned int altezza_sparo_alieni);

bool controlloCollisioneBarriereDaSparoCarro (Partita &partita);

ALLEGRO_BITMAP * sparoScelto (int pos_x, ALLEGRO_BITMAP *sparo_mostri_1, ALLEGRO_BITMAP *sparo_mostri_2);

void creaSparoMostri (Partita &partita, const ALLEGRO_FONT *font_mostri);

bool controlloCollisioneCarroDaOndata (Partita &partita);

bool controlloCollisioneMostri (Partita &partita, const ALLEGRO_FONT *font_mostri);

void muoviSparoMostri (Sparo &sparo, const unsigned int altezza_sparo_alieno);

void muoviMostri(Ondata &ondata, const unsigned int larghezza_colonna);

/**
 * Stabilisce qual'è la posizione rispetto all'asse y dello sparo del carro armato in movimento.
 * 
 * @param sapro Sparo del carro armato.
 * @param limite_sup Limite superiore dello sparo del carro armato.
 */
void muoviSparoCarro (Sparo &sparo);

/**
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso destra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 * @param limite_dx Limite dello spostamento del carro armato verso destra.
 */
void muoviDestraCarro (unsigned int &pos_x_carro);

/**
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso sinistra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 * @param limite_dx Limite dello spostamento del carro armato verso sinistra.
 */
void muoviSinistraCarro (unsigned int &pos_x_carro);

/**
 * Indica se esiste o meno una partita precedentemente salvata.
 * 
 * @param file Percorso del file dove verificare la presenza del salvataggio.
 * 
 * @return "true" se esiste una partita precedentemente salvata, "false" altrimenti.
 */
bool esisteSalvataggio ();

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
 * @param pos_x_iniziale_carro Posizione iniziale rispetto all'asse x del carro armato.
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
bool caricaPartita (Partita &salvataggio);

/**
 * Salva una partita da sospendere su un file.
 *
 * @param spaceInvaders struttura {@link SpaceInvaders} contenente tutte le informazioni relative al gioco in esecuzione.
 * @param file File nel quale salvare la partita.
 */
void salvaPartita (SpaceInvaders &spaceInvaders);

/**
 * Elimina un file di salvataggio nel caso in cui esista.
 *
 * @param file File di salvataggio da eliminare.
 * @param spaceInvaders Struttura {@link SpaceInvaders} contenente tutte le informazioni relative al gioco in esecuzione.
 * 
 * @return "true" se il file era presente ed è stato eliminato, "false" altrimenti.
 */
bool eliminaFileSalvataggio (SpaceInvaders &spaceInvaders);

//FINE INTERFACCIA
