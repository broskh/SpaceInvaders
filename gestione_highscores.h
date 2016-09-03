/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

//INIZIO INTERFACCIA

/**
 * Carica da un file i migliori punteggi e li memorizza in un'apposita struttura.
 * 
 * @param highscores Array di strutture {@link Punteggio} nel quale memorizzare i valori.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 * @param file File dal quale caricare i punteggi.
 *
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaPunteggi (Punteggio (&highscores) [MAX_HIGHSCORES], unsigned int &n_highscores, const char file []);

/**
 * Salva i migliori punteggi su file.
 *
 * @param highscores Array di strutture {@link Punteggio} che contiene i punteggi da salvare nel file.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 * @param file File nel quale salvare i punteggi.
 */
void salvaPunteggi (Punteggio highscores [], unsigned int n_highscores, const char file []);

/**
 * Memorizza in una struttura "Punteggio" i valori passati per parametro.
 *
 * @param punteggio Struttura {@link Punteggio} nella quale verranno memorizzati i valori.
 * @param nome Stringa di tre caratteri contenente il nome del giocatore che ha raggiunto il punteggio.
 * @param valore Valore del punteggio.
 */
void inizializzaPunteggio (Punteggio &punteggio, char nome [], int valore);

/**
 * Estrae da un array di strutture {@link Punteggio} il miglior punteggio in assoluto.
 *
 * @param highscores Array di strutture {@link Punteggio} dalla quale verrà estratto il miglior punteggio.
 *
 * @return il punteggio più alto presente negli highscores.
 */
Punteggio migliorPunteggio (Punteggio highscores []);

/**
 * Controlla se il nuovo punteggio merita di essere inserito fra gli highscores, e nel caso lo aggiunge.
 * Se il punteggio deve essere aggiunto agli highscores, dopo averlo messo nella corretta posizione,
 * rimuove il punteggio più basso. Altrimenti non lo aggiunge.
 *
 * @param highscores Array di strutture {@link punteggio} contenente i punteggi migliori.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 * @param nuovo_punteggio Nuovo punteggio raggiunto da aggiungere (se necessario) fra i punteggi migliori.
 *
 * @return "true" se il punteggio è stato aggiunto, altrimenti "false".
 */
bool aggiungiPunteggio (Punteggio (&highscores) [MAX_HIGHSCORES], unsigned int &n_highscores, Punteggio nuovo_punteggio);

//FINE INTERFACCIA