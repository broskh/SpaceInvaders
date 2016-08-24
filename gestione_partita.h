/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

//INIZIO INTERFACCIA

/*
 * Carica da un file una partita lasciata in sospeso.
 * Ritorna false nel caso in cui il caricamento non sia riuscito.
 * 
 * salvataggio Struttura :partita contente i dati della partita caricata.
 * file File dal quale caricare la partita.
 */
bool caricaPartita (partita &salvataggio, const char file []);

/*
 * Salva una partita da sospendere su file.
 *
 * salvataggio struttura :partita contenente i dati della partita da salvare sul file. 
 * file File nel quale salvare la partita.
 */
void salvaPartita (partita salvataggio, const char file []);

/*
 * Elimina un file di salvataggio nel caso in cui esista.
 * Ritorna "true" se il file era presente ed è stato eliminato, "false" altrimenti.
 *
 * file File di salvataggio da eliminare.
 */
bool eliminaFileSalvataggio (const char file []);

//FINE INTERFACCIA
