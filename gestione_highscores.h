/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

const char FILE_HIGHSCORES [] = "highscores"; /**<Percorso del file contenente gli highscores.*/

//INIZIO INTERFACCIA
/**
 * Stampa su console un {@link Punteggio}.
 * 
 * @param punteggio {@link Punteggio} da stampare.
 * 
 */
void stampa (Punteggio punteggio);

/**
 * Stampa su console un'array di punteggi.
 * 
 * @param highscores Array dei punteggi da stampare.
 * @param n Numero di punteggi nell'array.
 * 
 */
void stampa (Punteggio highscores [], int n);

/**
 * Carica da un file i migliori punteggi e li memorizza in un'apposita struttura.
 * 
 * @param highscores Array di strutture {@link Punteggio} nel quale memorizzare i valori.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 *
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaPunteggi (Punteggio (&highscores) [MAX_HIGHSCORES], int &n_highscores);

/**
 * Salva i migliori punteggi su file.
 *
 * @param highscores Array di strutture {@link Punteggio} che contiene i punteggi da salvare nel file.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 */
void salvaPunteggi (Punteggio highscores [], int n_highscores);

/**
 * Memorizza in una struttura "Punteggio" i valori passati per parametro.
 *
 * @param punteggio Struttura {@link Punteggio} nella quale verranno memorizzati i valori.
 * @param nome Stringa di tre caratteri contenente il nome del giocatore che ha raggiunto il punteggio.
 * @param valore Valore del punteggio.
 */
void inizializzaPunteggio (Punteggio &punteggio, char nome [], int valore);

/**
 * Aggiunge il nuovo punteggio nella posizione specificata dell'array.
 *
 * @param highscores Array di strutture {@link punteggio} contenente i punteggi migliori.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 * @param nuovo_punteggio Nuovo punteggio raggiunto da aggiungere (se necessario) fra i punteggi migliori.
 * @param posizione Posizione dell'array nella quale inserire il punteggio.
 */
void aggiungiPunteggio (Punteggio (&highscores) [MAX_HIGHSCORES], int &n_highscores, Punteggio nuovo_punteggio, int posizione);

/**
 * Controlla in quale posizione della classifica degli highscores il nuovo punteggio merita di essere inserito.
 * Se il punteggio non deve essere aggiunto agli highscores, il metodo ritorna il valore "-1".
 *
 * @param highscores Array di strutture {@link punteggio} contenente i punteggi migliori.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 * @param nuovo_punteggio Nuovo punteggio raggiunto da aggiungere (se necessario) fra i punteggi migliori.
 * 
 * @return la posizione dell'array degli highscores nella quale il nuovo punteggio andrebbe inserito; "-1" se
 * il punteggio non merita di essere inserito.
 */
int posizionePunteggio (Punteggio (&highscores) [MAX_HIGHSCORES], int &n_highscores, Punteggio nuovo_punteggio);
//FINE INTERFACCIA