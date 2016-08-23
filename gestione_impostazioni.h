/*
 * Header file contenente l'interfaccia del modulo di gestione delle impostazioni.
 */

//INIZIO INTERFACCIA

const bool DEFAULT_MUSICA = true; /*Valore di default del campo musica.*/
const bool DEFAULT_EFFETTI_AUDIO = true; /*Valore di default del campo effetti_audio.*/
const grafica DEFAULT_MODALITA_GRAFICA = mono_bianco; /*Valore di default del campo mod_grafica.*/
const unsigned int DEFAULT_VITE_INIZIALI = 3; /*Valore di default del campo vite_iniziali.*/

/*
 * Carica da un file di configurazione le impostazioni e le memorizza in un'apposita struttura.
 * Ritorna false nel caso in cui il caricamento non sia riuscito.
 * 
 * impo Struttura "impostazioni" nella quale memorizzare i valori.
 * file File di configurazione dal quale caricare le impostazioni.
 */
bool caricaImpostazioni (impostazioni &impo, const char file []);

/*
 * Salva le impostazioni su un file di configurazione.
 *
 * impo Struttura "impostazioni" che contiene le impostazioni da salvare nel file di configurazione. 
 * file File di configurazione nel quale salvare le impostazioni.
 */
void salvaImpostazioni (impostazioni impo, const char file []);

/*
 * Memorizza in una struttura "impostazioni" i valori passati per parametro.
 *
 * impo Struttura "impostazioni" nella quale verranno memorizzati i valori.
 * musica Valore booleano da assegnare al campo "musica".
 * effetti_audio Valore booleano da assegnare al campo "eff_audio".
 * modalita_grafica Valore "grafica" da assegnare al campo "mod_grafica".
 * vite_iniziali Valore intero da assegnare al campo "vite_iniziali".
 */
void inizializzaImpostazioni (impostazioni &impo, bool musica, bool effetti_audio, grafica modalita_grafica, unsigned int vite_iniziali);

/*
 * Ritorna una struttura "impostazioni" contenente i valori di default.
 *
 * impo Struttura "impostazioni" nella quale vengono settati i valori di default.
 */
void impostaValoraImpostazioniDefault (impostazioni &impo);


//FINE INTERFACCIA
