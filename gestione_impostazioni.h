/*
 * Header file contenente l'interfaccia del modulo per la gestione delle impostazioni.
 */

//INIZIO COSTANTI VALORI DI DEFAULT
const bool DEFAULT_MUSICA = true; /**<Valore di default del campo {@link Impostazioni.musica musica}.*/
const bool DEFAULT_EFFETTI_AUDIO = true; /**<Valore di default del campo {@link Impostazioni.effetti_audio effetti_audio}.*/
const colore DEFAULT_COLORE_ALIENI = verde; /**<Valore di default del campo {@link Impostazioni.colore_alieni colore_alieni}.*/
const unsigned int DEFAULT_VITE_INIZIALI = 3; /**<Valore di default del campo {@link Impostazioni.vite_iniziali vite_iniziali}.*/
//FINE COSTANTI VALORI DI DEFAULT

//INIZIO COSTANTI STRINGHE CAMPI
const char CAMPO_MUSICA [] = "musica"; /**<Stringa per identificare il campo {@link Impostazioni.musica musica}.*/
const char CAMPO_EFFETTI_AUDIO [] = "effetti_audio"; /**<Stringa per identificare il campo {@link Impostazioni.effetti_audio effetti_audio}.*/
const char CAMPO_COLORE_ALIENI [] = "colore_alieni"; /**<Stringa per identificare il campo {@link Impostazioni.colore_alieni colore_alieni}.*/
const char CAMPO_VITE_INIZIALI [] = "vite_iniziali"; /**<Stringa per identificare il campo {@link Impostazioni.vite_iniziali vite_iniziali}.*/
//FINE COSTANTI STRINGHE CAMPI

//INIZIO COSTANTI PER FILE
const char FILE_IMPOSTAZIONI [] = "SpaceInvaders.config"; /**<Percorso del file contenente le impostazioni salvate.*/
const char STRINGA_FILE_IMPOSTAZIONI_NON_TROVATO [] = "Errore nel caricamento del file di configurazione. File non esistente."; /**<Messaggio di errore che indica che il file di configurazione non è stato trovato.*/
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA
/**
 * Carica dal file di configurazione le impostazioni e le memorizza nell'apposita struttura.
 * 
 * @param impostazioni Struttura {@link Impostazioni} nella quale verranno caricate le impostazioni.
 * 
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaImpostazioni (Impostazioni &impostazioni);

/**
 * Assegna a tutti i campi di una struttura {@link Impostazioni} i relativi valori di default.
 *
 * @param impostazioni Struttura {@link Impostazioni} nella quale verranno settati i valori di default.
 */
void impostaValoriDefault (Impostazioni &impostazioni);

/**
 * Salva le impostazioni sul file di configurazione.
 *
 * @param impostazioni Impostazioni da salvare nel file di configurazione.
 */
void salvaImpostazioni (Impostazioni impostazioni);

/*
 * Stampa a console le impostazioni.
 * 
 * @param impostazioni Impostazioni da stampare.
 */
void stampa (Impostazioni impostazioni);

/*
 * Ritorna lo stato del campo colore_alieni.
 * 
 * @param impostazioni Impostazioni da analizzare.
 * 
 * @return il colore degli alieni.
 */
colore statoColoreAlieni (Impostazioni impostazioni);

/*
 * Ritorna lo stato del campo eff_audio.
 * 
 * @param impostazioni Impostazioni da analizzare.
 * 
 * @return "true" se gli effetti audio sono attivati, "false" altrimenti.
 */
bool statoEffettiAudio (Impostazioni impostazioni);

/*
 * Ritorna lo stato del campo musica.
 * 
 * @param impostazioni Impostazioni da analizzare.
 * 
 * @return "true" se la musica è attivata, "false" altrimenti.
 */
bool statoMusica (Impostazioni impostazioni);
//FINE INTERFACCIA