/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

//INIZIO INTERFACCIA

/*
 * Carica da un file i migliori punteggi e li memorizza in un'apposita struttura.
 * Ritorna false nel caso in cui il caricamento non sia riuscito.
 * 
 * highscores Array di strutture :punteggio nel quale memorizzare i valori.
 * file File dal quale caricare i punteggi.
 */
bool caricaPunteggi (punteggio (&highscores) [MAX_HIGHSCORES], unsigned int &n_highscores, const char file []);

/*
 * Salva i punteggi migliori su file.
 *
 * highscores Array di strutture :punteggio che contiene i punteggi da salvare nel file. 
 * file File nel quale salvare i punteggi.
 */
void salvaPunteggi (punteggio highscores [], unsigned int n_highscores, const char file []);

/*
 * Memorizza in una struttura "punteggio" i valori passati per parametro.
 *
 * punteggio Struttura :punteggio nella quale verranno memorizzati i valori.
 * nome Stringa di tre caratteri contenente il nome del giocatore che ha raggiunto il punteggio.
 * valore Punteggio raggiunto.
 */
void inizializzaPunteggio (punteggio &punteggio, char nome [], int valore);

/*
 * Ritorna il punteggio più alto presente negli highscores.
 *
 * highscores Array di strutture :punteggio: dalla quale verrà estratto il miglior punteggio.
 */
punteggio migliorPunteggio (punteggio highscores []);

/*
 * Controlla se il nuovo punteggio merita di essere inserito fra gli highscores.
 * Nel caso sia necessario lo aggiunge agli highscores nella corretta posizione, rimuove il punteggio
 * più basso e ritorna "true". Altrimenti non lo aggiunge e ritorna "false".
 *
 * highscores Array di strutture :punteggio: contenente i punteggi migliori.
 * nuovo_punteggio Nuovo punteggio raggiunto da aggiungere (se necessario) fra i punteggi migliori.
 */
bool aggiungiPunteggio (punteggio (&highscores) [MAX_HIGHSCORES], unsigned int &n_highscores, punteggio nuovo_punteggio);

//FINE INTERFACCIA
