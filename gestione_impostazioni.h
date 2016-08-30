/*
 * Header file contenente l'interfaccia del modulo di gestione delle impostazioni.
 */

//INIZIO INTERFACCIA

const bool DEFAULT_MUSICA = true; /**<Valore di default del campo musica.*/
const bool DEFAULT_EFFETTI_AUDIO = true; /**<Valore di default del campo effetti_audio.*/
const grafica DEFAULT_MODALITA_GRAFICA = mono_bianco; /**<Valore di default del campo mod_grafica.*/
const unsigned int DEFAULT_VITE_INIZIALI = 3; /**<Valore di default del campo vite_iniziali.*/

/**
 * Carica da un file di configurazione le impostazioni e le memorizza in un'apposita struttura.
 * 
 * @param impo Struttura {@link impostazioni} nella quale memorizzare i valori.
 * @param file File di configurazione dal quale caricare le impostazioni.
 * 
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaImpostazioni (impostazioni &impo, const char file []);

/**
 * Salva le impostazioni su un file di configurazione.
 *
 * @param impo Struttura {@link impostazioni} che contiene le impostazioni da salvare nel file di configurazione. 
 * @param file File di configurazione nel quale salvare le impostazioni.
 */
void salvaImpostazioni (impostazioni impo, const char file []);

/**
 * Memorizza in una struttura {@link impostazioni} i valori passati per parametro.
 *
 * @param impo Struttura {@link impostazioni} nella quale verranno memorizzati i valori.
 * @param musica Valore booleano da assegnare al campo {@link #impostazioni.musica musica}.
 * @param effetti_audio Valore booleano da assegnare al campo {@link #impostazioni.eff_audio eff_audio}.
 * @param modalita_grafica Valore "grafica" da assegnare al campo {@link #impostazioni.mod_grafica mod_grafica}.
 * @param vite_iniziali Valore intero da assegnare al campo {@link #impostazioni.vite_iniziali vite_iniziali}.
 */
void inizializzaImpostazioni (impostazioni &impo, bool musica, bool effetti_audio, grafica modalita_grafica, unsigned int vite_iniziali);

/**
 * Assegna a tutti i campi di una struttura {@link impostazioni} i relativi valori di default.
 *
 * @param impo Struttura {@link impostazioni} nella quale vengono settati i valori di default.
 */
void impostaValoriImpostazioniDefault (impostazioni &impo);

//FINE INTERFACCIA
