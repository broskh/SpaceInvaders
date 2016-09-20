/*
 * Header file contenente l'interfaccia del modulo di gestione delle impostazioni.
 */

const bool DEFAULT_MUSICA = true; /**<Valore di default del campo musica.*/
const bool DEFAULT_EFFETTI_AUDIO = true; /**<Valore di default del campo effetti_audio.*/
const grafica DEFAULT_MODALITA_GRAFICA = mono_bianco; /**<Valore di default del campo mod_grafica.*/
const unsigned int DEFAULT_VITE_INIZIALI = 3; /**<Valore di default del campo vite_iniziali.*/

extern char FILE_IMPOSTAZIONI [];

//INIZIO INTERFACCIA
/**
 * Carica da un file di configurazione le impostazioni e le memorizza in un'apposita struttura.
 * 
 * @param impostazioni Struttura {@link Impostazioni} nella quale memorizzare i valori.
 * 
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaImpostazioni (Impostazioni &impostazioni);

/**
 * Salva le impostazioni su un file di configurazione.
 *
 * @param impostazioni Struttura {@link Impostazioni} che contiene le impostazioni da salvare nel file di configurazione.
 */
void salvaImpostazioni (Impostazioni impostazioni);

/**
 * Memorizza in una struttura {@link Impostazioni} i valori passati per parametro.
 *
 * @param impostazioni Struttura {@link Impostazioni} nella quale verranno memorizzati i valori.
 * @param musica Valore booleano da assegnare al campo {@link #Impostazioni.musica musica}.
 * @param effetti_audio Valore booleano da assegnare al campo {@link #Impostazioni.eff_audio eff_audio}.
 * @param modalita_grafica Valore "grafica" da assegnare al campo {@link #Impostazioni.mod_grafica mod_grafica}.
 * @param vite_iniziali Valore intero da assegnare al campo {@link #Impostazioni.vite_iniziali vite_iniziali}.
 */
void inizializzaImpostazioni (Impostazioni &impostazioni, bool musica, bool effetti_audio, grafica modalita_grafica, unsigned int vite_iniziali);

/**
 * Assegna a tutti i campi di una struttura {@link Impostazioni} i relativi valori di default.
 *
 * @param impo Struttura {@link Impostazioni} nella quale vengono settati i valori di default.
 */
void impostaValoriImpostazioniDefault (Impostazioni &impostazioni);

/*
 * Stampa a console le impostazioni.
 * @param impostazioni {@link Impostazioni} da stampare.
 */
void stampa (Impostazioni impostazioni);
//FINE INTERFACCIA