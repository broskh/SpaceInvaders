/*
 * Header file contenente l'interfaccia del modulo per la gestione della classifica.
 */

//INIZIO COSTANTI PER FILE
const char FILE_HIGHSCORES [] = "highscores"; /**<Percorso del file contenente la classifica.*/
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA
/**
 * Aggiunge una lettera al nome del giocatore che ha realizzato il punteggio.
 * Se il nome ha già raggiunto il numero massimo di caratteri, la nuova lettera 
 * sostituisce l'ultima precedentemente presente.
 *
 * @param punteggio Punteggio da modificare.
 * @param nuova_lettera Nuova lettera da aggiugnere al nome.
 */
void aggiungiLetteraNomePunteggio (Punteggio &punteggio, char nuova_lettera);

/**
 * Aggiunge il nuovo punteggio nella posizione specificata della classifica.
 *
 * @param classifica Classifica da modificare.
 * @param nuovo_punteggio Punteggio da aggiungere nella classifica.
 * @param posizione Posizione della classifica nella quale inserire il punteggio.
 */
void aggiungiPunteggio (Classifica &classifica, Punteggio nuovo_punteggio, int posizione);

/**
 * Cancella l'ultimo carattere dal nome del giocatore che ha realizzato il punteggio.
 * 
 * @param punteggio Punteggio da modificare.
 */
void cancellaUltimoCarattereNome (Punteggio &punteggio);

/**
 * Carica dal file la classifica.
 * 
 * @param classifica Classifica nella quale caricare le informazioni.
 *
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaPunteggi (Classifica &classifica);

/**
 * Inizializza una Classifica vuota.
 *
 * @param classifica Classifica da inizializzare.
 */
void inizializzaClassificaVuota (Classifica &classifica);

/**
 * Inizializza un Punteggio con i valori passati per parametro.
 *
 * @param punteggio Punteggio da inizializzare.
 * @param nome Stringa contenente il nome del giocatore che ha raggiunto il punteggio.
 * @param valore Valore del punteggio.
 */
void inizializzaPunteggio (Punteggio &punteggio, name_string nome, int valore);

/**
 * Calcola in quale posizione della classifica il nuovo punteggio merita di essere inserito.
 *
 * @param classifica Classifica analizzata.
 * @param nuovo_punteggio Punteggio da valutare.
 * 
 * @return la posizione della classifica nella quale il nuovo punteggio andrebbe inserito, "-1" se
 * il punteggio non merita di essere inserito.
 */
int posizionePunteggio (Classifica classifica, Punteggio nuovo_punteggio);

/**
 * Salva la classifica su file.
 *
 * @param classifica {@link Classifica} da salvare.
 */
void salvaPunteggi (Classifica classifica);

/**
 * Stampa a console la {@link Classifica}.
 * 
 * @param classifica Classifica da stampare.
 */
void stampa (Classifica classifica);

/**
 * Stampa su console un {@link Punteggio}.
 * 
 * @param punteggio {@link Punteggio} da stampare.
 */
void stampa (Punteggio punteggio);
//FINE INTERFACCIA