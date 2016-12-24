/*
 * Header file contenente l'interfaccia del modulo per la gestione della classifica.
 */

//INIZIO COSTANTI PER FILE
const char FILE_HIGHSCORES [] = "highscores"; /**<Percorso del file contenente la classifica.*/
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA
/**
 * Aggiunge una lettera al nome del realizzatore del punteggio.
 * Se il nome ha giù raggiunto il numero massimo di caratteri, la nuova lettera sostituisce l'ultima all'interno del nome.
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
 * @param putneggio Punteggio da modificare.
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
 * Inizializza una {@link Classifica} vuota.
 *
 * @param classifica {@link Classifica} da inizializzare.
 */
void inizializzaClassifica (Classifica &classifica);

/**
 * Inizializza un {@link Punteggio} con i valori passati per parametro.
 *
 * @param punteggio {@link Punteggio} nel quale verranno memorizzati i valori.
 * @param nome Stringa contenente il nome del giocatore che ha raggiunto il punteggio.
 * @param valore Valore del punteggio.
 */
void inizializzaPunteggio (Punteggio &punteggio, char nome [], int valore);

/**
 * Calcola in quale posizione della classifica il nuovo punteggio merita di essere inserito.
 * Se il punteggio non deve essere aggiunto alla classifica, il metodo ritorna il valore "-1".
 *
 * @param classifica Classifica analizzata.
 * @param nuovo_punteggio Punteggio da controllare.
 * 
 * @return la posizione della classifica nella quale il nuovo punteggio andrebbe inserito. Ritorna "-1" se
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
 * Stampa su console la {@link Classifica}.
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
