/*
 * Header file contenente l'interfaccia del modulo per la gestione della partita.
 */

//INIZIO COSTANTI PER ALIENI
const unsigned int N_ALIENI_TOTALE = N_FILE_ALIENI * N_COL_ALIENI; /**<Numero totale degli alieni che compongono una nuovao ondata.*/
const unsigned int N_TIPI_ALIENI = 3; /**<Numero dei differenti tipi di alieni.*/
const unsigned int PUNTEGGIO_ALIENI [N_TIPI_ALIENI] = {10, 20, 30}; /**<Punteggi attribuiti ai differenti tipi di alieni.*/
//FINE COSTANTI PER ALIENI

//INIZIO COSTANTI PER BARRIERE
const unsigned int ALT_INIZIO_SMUSSO_INFERIORE = ALTEZZA_BARRIERA / 2.3; /**<Altezza dalla quale inizia lo smusso inferiore di una barriera.*/
const unsigned int CENTRO_ORIZZONTALE_BARRIERA = LARGHEZZA_BARRIERA / 2 - 1; /**<Posizione centrale rispetto all'asse x di una barriera.*/
const unsigned int LARGHEZZA_PIEDE = LARGHEZZA_BARRIERA / 4; /**<Larghezza dei "piedi" di una barriera.*/
const unsigned int SMUSSO_INFERIORE = (LARGHEZZA_BARRIERA - (LARGHEZZA_PIEDE * 2)) / 2; /**<Dimensione dello smusso inferiore di una barriera.*/
const unsigned int SMUSSO_SUPERIORE = 4; /**<Dimensione dello smusso superiore di una barriera.*/
//INIZIO COSTANTI PER BARRIERE

//INIZIO COSTANTI PER CARRO ARMATO
const unsigned int PESO_SPOSTAMENTO_CARRO_ARMATO = 5; /**<Peso (in pixel) dello spostamento laterale del carro armato.*/
const unsigned int RIP_ANIMAZIONE_ESPLOSIONE_CARRO = 2; /**<Numero di ripetizioni dell'animazione di esplosione del carro.*/
//FINE COSTANTI PER CARRO ARMATO

//INIZIO COSTANTI PER NAVICELLA MISTERIOSA
const unsigned int PROBABILITA_COMPARSA_NAVICELLA = 15; /**<Percentuale di probabilità che compaia la navicella misteriosa.*/
const unsigned int PUNTEGGIO_NAVICELLA_MAX = 500; /**<Punteggio massimo che può assumere la navicella misteriosa.*/
const unsigned int PUNTEGGIO_NAVICELLA_MIN = 100; /**<Punteggio minimo che può assumere la navicella misteriosa.*/
//FINE COSTANTI PER NAVICELLA MISTERIOSA

//INIZIO COSTANTI PER FILE
const char FILE_SALVATAGGIO_PARTITA [] = "partita.sav"; /**<Percorso del file contenente la partita salvata.*/
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA
/**
 * Carica da un file una partita lasciata in sospeso.
 * 
 * @param salvataggio Struttura {@link partita} contenente i dati della partita caricata.
 * @param file File dal quale caricare la partita.
 * 
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaPartita (Partita &salvataggio);

bool controlloCollisioneAlieni (Partita &partita);

bool controlloCollisioneBarriereDaOndata (Partita &partita);

bool controlloCollisioneBarriereDaSparoAlieni (Partita &partita);

bool controlloCollisioneBarriereDaSparoCarro (Partita &partita);

bool controlloCollisioneCarroDaOndata (Partita &partita);

bool controlloCollisioneCarroDaSparoAlieni (Partita &partita);

bool controlloCollisioneNavicellaMisteriosa (Partita &partita);

bool controlloFineOndata (Ondata ondata);

bool controlloFinePartita (Partita partita);

void creaNavicellaMisteriosa (Partita &partita);

void creaSparoAlieni (Partita &partita);

void creaSparoCarroArmato (Carro &carro);

/**
 * Elimina un file di salvataggio nel caso in cui esista.
 *
 * @param file File di salvataggio da eliminare.
 * @param spaceInvaders Struttura {@link SpaceInvaders} contenente tutte le informazioni relative al gioco in esecuzione.
 * 
 * @return "true" se il file era presente ed è stato eliminato, "false" altrimenti.
 */
bool eliminaFileSalvataggio (bool &partita_salvata);

/**
 * Indica se esiste o meno una partita precedentemente salvata.
 * 
 * @param file Percorso del file dove verificare la presenza del salvataggio.
 * 
 * @return "true" se esiste una partita precedentemente salvata, "false" altrimenti.
 */
bool esisteSalvataggio ();

void muoviAlieni(Ondata &ondata);

/**
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso destra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 */
void muoviCarroDestra (unsigned int &pos_x_carro);

/**
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso sinistra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 */
void muoviCarroSinistra (unsigned int &pos_x_carro);

void muoviNavicellaMisteriosa (Partita &partita);

void muoviSparoAlieni (Sparo &sparo);

/**
 * Stabilisce qual'è la posizione rispetto all'asse y dello sparo del carro armato in movimento.
 * 
 * @param sapro Sparo del carro armato.
 * @param limite_sup Limite superiore dello sparo del carro armato.
 */
void muoviSparoCarro (Sparo &sparo);

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
 * @param pos_x_carro_armato Posizione iniziale rispetto all'asse x del carro armato.
 */
void nuovaPartita (Partita &partita, Impostazioni impostazioni);

unsigned int percentualeAlieniEliminati (Ondata ondata);

/**
 * Salva una partita da sospendere su un file.
 *
 * @param spaceInvaders struttura {@link SpaceInvaders} contenente tutte le informazioni relative al gioco in esecuzione.
 * @param file File nel quale salvare la partita.
 */
void salvaPartita (Partita partita_in_corso, bool &partita_salvata);

void stampaPartita (Partita partita);
//FINE INTERFACCIA