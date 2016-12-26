/*
 * Header file contenente l'interfaccia del modulo per la gestione della partita.
 */

//INIZIO COSTANTI PER ALIENI
const unsigned int N_ALIENI_TOTALE = N_FILE_ALIENI * N_COL_ALIENI; /**<Numero totale degli alieni che compongono una nuovao ondata.*/
const unsigned int N_TIPI_ALIENI = 3; /**<Numero dei differenti tipi di alieni.*/
const unsigned int PUNTEGGIO_ALIENI [N_TIPI_ALIENI] = {10, 20, 30}; /**<Punteggi attribuiti ai differenti tipi di alieni.*/
const unsigned int SPOSTAMENTO_ONDATA_GIU = 5; /**<Peso dello spostamento verso il basso dell'ondata.*/
//FINE COSTANTI PER ALIENI

//INIZIO COSTANTI PER BARRIERE
const unsigned int ALT_INIZIO_SMUSSO_INFERIORE = ALTEZZA_BARRIERA / 2.3; /**<Altezza dalla quale inizia lo smusso inferiore di una barriera.*/
const unsigned int CENTRO_ORIZZONTALE_BARRIERA = LARGHEZZA_BARRIERA / 2 - 1; /**<Posizione centrale rispetto all'asse x di una barriera.*/
const unsigned int LARGHEZZA_PIEDE = LARGHEZZA_BARRIERA / 4; /**<Larghezza dei "piedi" di una barriera.*/
const unsigned int SMUSSO_INFERIORE = (LARGHEZZA_BARRIERA - (LARGHEZZA_PIEDE * 2)) / 2; /**<Dimensione dello smusso inferiore di una barriera.*/
const unsigned int SMUSSO_SUPERIORE = 4; /**<Dimensione dello smusso superiore di una barriera.*/
//INIZIO COSTANTI PER BARRIERE

//INIZIO COSTANTI PER NAVICELLA MISTERIOSA
const unsigned int PROBABILITA_COMPARSA_NAVICELLA = 25; /**<Percentuale di probabilità che compaia la navicella misteriosa.*/
const unsigned int PUNTEGGIO_NAVICELLA_MAX = 500; /**<Punteggio massimo che può assumere la navicella misteriosa.*/
const unsigned int PUNTEGGIO_NAVICELLA_MIN = 100; /**<Punteggio minimo che può assumere la navicella misteriosa.*/
//FINE COSTANTI PER NAVICELLA MISTERIOSA

//INIZIO COSTANTI PER FILE
const char FILE_SALVATAGGIO_PARTITA [] = "partita.sav"; /**<Percorso del file contenente la partita salvata.*/
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA
/**
 * Incrementa il valore dell'esplosione di un alieno.
 * 
 * @param partita Partita da modificare.
 * @param n_fila Numero della fila nella quale si trova l'alieno.
 * @param n_colonna Numero di colonna nella quale si trova l'alieno.
 */
void avanzaEsplosioneAlieno (Partita &partita, unsigned int n_fila, unsigned int n_colonna);

/**
 * Incrementa il valore dell'esplosione del carro armato.
 * 
 * @param partita Partita da modificare.
 */
void avanzaEsplosioneCarroArmato (Partita &partita);

/**
 * Carica da un file una partita lasciata in sospeso.
 * 
 * @param salvataggio Partita nella quale memorizzare i dati caricati.
 * 
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaPartita (Partita &salvataggio);

/**
 * Controlla se è avvenuta una collisione su un alieno.
 * 
 * @param partita Partita nella quale controllare se è avvenuta la collisione.
 * 
 * @return "false" nel caso in cui la collisione non sia avvenuta, "true" altrimenti.
 */
bool controlloCollisioneAlieni (Partita &partita);

/**
 * Controlla se è avvenuta, da parte dell'ondata di alieni, una collisione contro le barriere.
 * 
 * @param partita Partita nella quale controllare se è avvenuta la collisione.
 * 
 * @return "false" nel caso in cui la collisione non sia avvenuta, "true" altrimenti.
 */
bool controlloCollisioneBarriereDaOndata (Partita &partita);

/**
 * Controlla se è avvenuta, da parte di uno sparo alieno, una collisione contro le barriere.
 * 
 * @param partita Partita nella quale controllare se è avvenuta la collisione.
 * 
 * @return "false" nel caso in cui la collisione non sia avvenuta, "true" altrimenti.
 */
bool controlloCollisioneBarriereDaSparoAlieni (Partita &partita);

/**
 * Controlla se è avvenuta, da parte di uno sparo del carro, una collisione contro le barriere.
 * 
 * @param partita Partita nella quale controllare se è avvenuta la collisione.
 * 
 * @return "false" nel caso in cui la collisione non sia avvenuta, "true" altrimenti.
 */
bool controlloCollisioneBarriereDaSparoCarro (Partita &partita);

/**
 * Controlla se è avvenuta, da parte dell'ondata di alieni, una collisione contro il carro armato.
 * 
 * @param partita Partita nella quale controllare se è avvenuta la collisione.
 * 
 * @return "false" nel caso in cui la collisione non sia avvenuta, "true" altrimenti.
 */
bool controlloCollisioneCarroDaOndata (Partita &partita);

/**
 * Controlla se è avvenuta, da parte di uno sapro alieno, una collisione contro il carro armato.
 * 
 * @param partita Partita nella quale controllare se è avvenuta la collisione.
 * 
 * @return "false" nel caso in cui la collisione non sia avvenuta, "true" altrimenti.
 */
bool controlloCollisioneCarroDaSparoAlieni (Partita &partita);

/**
 * Controlla se è avvenuta una collisione contro la navicella misteriosa.
 * 
 * @param partita Partita nella quale controllare se è avvenuta la collisione.
 * 
 * @return "false" nel caso in cui la collisione non sia avvenuta, "true" altrimenti.
 */
bool controlloCollisioneNavicellaMisteriosa (Partita &partita);

/**
 * Controlla se sono stati distrutti tutti gli alieni facenti parte dell'ondata.
 * 
 * @param partita Partita nella quale controllare lo stato dell'ondata.
 * 
 * @return "true" se tutti gli alieni dell'ondata sono stati distrutti, "false" altrimenti.
 */
bool controlloFineOndata (Partita &partita);

/**
 * Controlla se il giocatore ha terminato le proprie vite.
 * 
 * @param partita Partita da controllare.
 * 
 * @return "true" se la partita è terminata, "false" altrimenti.
 */
bool controlloFinePartita (Partita partita);

/**
 * Se si verifica la condizione probabilistica, crea la navicella misteriosa.
 * 
 * @param partita Partita da modificare.
 */
void creaNavicellaMisteriosa (Partita &partita);

/**
 * Crea uno sparo alieno.
 * 
 * @param partita Partita da modificare.
 */
void creaSparoAlieni (Partita &partita);

/**
 * Crea lo sapro del carro armato.
 * 
 * @param partita Partita da modificare.
 */
void creaSparoCarroArmato (Partita &partita);

/**
 * Elimina il file di salvataggio nel caso in cui esista.
 * 
 * @return "true" se il file era presente ed è stato eliminato, "false" altrimenti.
 */
bool eliminaFileSalvataggio ();

/**
 * Indica se esiste o meno una partita salvata.
 * 
 * @return "true" se esiste una partita salvata, "false" altrimenti.
 */
bool esisteSalvataggio ();

/**
 * Muove l'ondata di alieni.
 *
 * @param partita Partita da modificare.
 */
void muoviAlieni(Partita &partita);

/**
 * Muove il carro armato a destra.
 *
 * @param partita Partita da modificare.
 */
void muoviCarroDestra (Partita &partita);

/**
 * Muove il carro armato a sinistra.
 *
 * @param partita Partita da modificare.
 */
void muoviCarroSinistra (Partita &partita);

/**
 * Muove la navicella misteriosa.
 *
 * @param partita Partita da modificare.
 */
void muoviNavicellaMisteriosa (Partita &partita);

/**
 * Muove uno sparo alieno.
 *
 * @param partita Partita da modificare.
 */
void muoviSparoAlieni (Partita &partita);

/**
 * Muove lo sparo del carro armato.
 *
 * @param partita Partita da modificare.
 */
void muoviSparoCarro (Partita &partita);

/**
 * Inizializza un'ondata ripristinando tutte le informazioni di base.
 *
 * @param partita Partita da modificare.
 */
void nuovaOndata (Partita &partita);

/**
 * Inizializza una partita con tutte le informazioni di base.
 *
 * @param partita Partita da inizializzare
 * @param impostazioni Impostazioni di gioco che modificano le informazioni da inserire nella nuova partita.
 */
void nuovaPartita (Partita &partita, Impostazioni impostazioni);

/**
 * Percentuale degli alieni distrutti.
 * 
 * @param partita Partita da analizzare.
 * 
 * @return la percentuale di alieni eliminati.
 */
unsigned int percentualeAlieniEliminati (Partita partita);

/**
 * Ritorna il punteggio della partita.
 * 
 * @param Partita partita da analizzare.
 */
Punteggio * punteggioAttuale (Partita &partita);

/**
 * Salva una partita su file.
 *
 * @param partita Partita da salvare.
 */
void salvaPartita (Partita partita);

/*
 * Stampa a console la partita.
 * 
 * @param partita Partita da stampare.
 */
void stampaPartita (Partita partita);

/*
 * Ritorna il valore dello stato di esplosione di un alieno.
 * 
 * @param partita Partita da analizzare.
 * @param n_fila Numero della fila nella quale si trova l'alieno.
 * @param n_colonna Numero di colonna nella quale si trova l'alieno.
 * 
 * @return il valore dello stato di esplosione dell'alieno.
 */
unsigned int statoEsplosioneAlieno (Partita partita, unsigned int n_fila, unsigned int n_colonna);

/*
 * Ritorna il valore dello stato di esplosione del carro armato.
 * 
 * @param partita Partita da analizzare.
 * 
 * @return il valore dello stato di esplosione del carro armato.
 */
unsigned int statoEsplosioneCarroArmato (Partita partita);

/*
 * Ritorna lo stato della navicella misteriosa.
 * 
 * @param partita Partita da analizzare.
 * 
 * @return "true" se la navicella misteriosa è comparsa, "false" altrimenti.
 */
bool statoNavicellaMisteriosa (Partita partita);

/*
 * Ritorna lo stato dello sparo degli alieni.
 * 
 * @param partita Partita da analizzare.
 * 
 * @return "true" se lo sparo è stato effettuato, "false" altrimenti.
 */
bool statoSparoAlieni (Partita partita);

/*
 * Ritorna lo stato dello sparo del carro armato.
 * 
 * @param partita Partita da analizzare.
 * 
 * @return "true" se lo sparo è stato effettuato, "false" altrimenti.
 */
bool statoSparoCarroArmato (Partita partita);

/**
 * Pone termine all'esplosione di un alieno.
 * 
 * @param partita Partita da modificare.
 * @param n_fila Numero della fila nella quale si trova l'alieno.
 * @param n_colonna Numero di colonna nella quale si trova l'alieno.
 */
void terminaEsplosioneAlieno (Partita &partita, unsigned int n_fila, unsigned int n_colonna);

/**
 * Pone termine all'esplosione del carro armato.
 * 
 * @param partita Partita da modificare.
 */
void terminaEsplosioneCarroArmato (Partita &partita);
//FINE INTERFACCIA
