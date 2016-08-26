/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

//INIZIO INTERFACCIA

/**
 * Carica da un file i migliori punteggi e li memorizza in un'apposita struttura.
 * 
 * @param highscores Array di strutture {@link punteggio} nel quale memorizzare i valori.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 * @param file File dal quale caricare i punteggi.
 *
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaPunteggi (punteggio (&highscores) [MAX_HIGHSCORES], unsigned int &n_highscores, const char file []);

/**
 * Salva i migliori punteggi su file.
 *
 * @param highscores Array di strutture {@link punteggio} che contiene i punteggi da salvare nel file.
 * @param n_highscores Numero di punteggi presenti attualmente nell'array "highscores".
 * @param file File nel quale salvare i punteggi.
 */
void salvaPunteggi (punteggio highscores [], unsigned int n_highscores, const char file []);

/**
 * Memorizza in una struttura "punteggio" i valori passati per parametro.
 *
 * @param punteggio Struttura {@link punteggio} nella quale verranno memorizzati i valori.
 * @param nome Stringa di tre caratteri contenente il nome del giocatore che ha raggiunto il punteggio.
 * @param valore Valore del punteggio.
 */
void inizializzaPunteggio (punteggio &punteggio, char nome [], int valore);

/**
 * Estrae da un array di strutture {@link punteggio} il miglior punteggio in assoluto.
 *
 * @param highscores Array di strutture {@link punteggio} dalla quale verrà estratto il miglior punteggio.
 *
 * @return il punteggio più alto presente negli highscores.
 */
punteggio migliorPunteggio (punteggio highscores []);

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
bool aggiungiPunteggio (punteggio (&highscores) [MAX_HIGHSCORES], unsigned int &n_highscores, punteggio nuovo_punteggio);

//FINE INTERFACCIA
