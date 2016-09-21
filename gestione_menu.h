/*
 * Header file contenente l'interfaccia del modulo di gestione degi menu.
 */

#include <cstring>
#include <cstdio>

const char MENU_PRINCIPALE [] [MAX_STRINGA_GENERICA] = {"Gioca", "Carica partita", "Opzioni", "Highscores", "Esci"}; /**<Voci del munù principale*/
const int N_VOCI_MENU_PRINC = 5; /**<Numero di voci del menù principale.*/
const char MENU_IMPOSTAZIONI [] [MAX_STRINGA_GENERICA] = {"Musica: ", "Effetti audio: ", "Modalita' grafica: ", "Vite iniziali: "}; /**<Voci del munù impostazioni.*/
const int N_VOCI_MENU_IMPO = 4; /**<Numero di voci del menù impostazioni.*/
const char INDICAZIONI_IMPOSTAZIONI [] [MAX_STRINGA_GENERICA_LUNGA] = {"Usa le frecce su e giu' per cambiare opzione", "Usa le frecce destra e sinistra per modificare il valore", "Premi enter per salvare e tornare al menu principale", "Premi R per ripristinare i valori di default"}; /**<Indicazioni del menù impostazioni.*/
const int N_INDICAZIONI_MENU_IMPO = 4; /**<Numero di indicazioni del menù impostazioni.*/
const char MENU_PAUSA [] [MAX_STRINGA_GENERICA] = {"Continua partita", "Salva partita", "Abbandona partita"}; /**<Indicazioni del menù di pausa.*/
const int N_VOCI_MENU_PAUSA = 3; /**<Numero di voci del menù di pausa.*/

//INIZIO INTERFACCIA
/**
 * Modifica il valore della voce selezionata impostandola alla precedente.
 * 
 * @param menu Menu nel quale modificare la voce di menù selezionata.
 */
void vocePrec (Menu &menu);

/**
 * Modifica il valore della voce selezionata impostandola alla precedente.
 * 
 * @param menu Menu nel quale modificare la voce di menù selezionata.
 * @param voce_saltata Voce da saltare nella ricerca della voce precedente.
 */
void vocePrec (Menu &menu, int voce_saltata);

/**
 * Modifica il valore della voce selezionata impostandola alla successiva.
 * 
 * @param menu Menu nel quale modificare la voce di menù selezionata.
 */
void voceSuc (Menu &menu);

/**
 * Modifica il valore della voce selezionata impostandola alla successiva.
 * 
 * @param menu Menu nel quale modificare la voce di menù selezionata.
 * @param voce_saltata Voce da saltare nella ricerca della voce successiva.
 */
void voceSuc (Menu &menu, int voce_saltata);

/**
 * Memorizza in una struttura {@link Menu} i valori passati per parametro.
 *
 * @param impo Struttura {@link menu} nella quale verranno memorizzati i valori.
 * @param testi_menu Array di stringhe da assegnare al campo {@link #Menu.testi_menu testi_menu}.
 * @param n_voci Valore intero da assegnare al campo {@link #Menu.n_voci n_voci}.
 * @param voce_sel Valore "intero da assegnare al campo {@link #Menu.voce_sel voce_sel}.
 */
void inizializzaMenu (Menu &menu, const char testi_menu [] [MAX_STRINGA_GENERICA], int n_voci, int voce_sel);

/**
 * Genera una stringa in grado di rappresentare lo stato del valore di un particolare campo delle impostazioni.
 * Necessita di conoscere la voce del menù impostazioni alla quale ci si riferisce per poter capire di quale 
 * campo si vuole ottenere il valore sotto forma di stringa.
 *
 * @param stringa Stringa contenente il valore di una determinato campo della struttura {@link Impostazioni}.
 * @param voce Voce di menù impostazioni della quale si vuole ottenere il valore come stringa.
 * @param impostazioni Struttura {@link Impostazioni} dal quale si controlla il valore del campo.
 * 
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni}, "false" altrimenti.
 */
bool stringaValoreVoceImpostazioni (char stringa [], voce_menu_impostazioni voce, Impostazioni impostazioni);

/*
 * Modifica il valore di un determinato campo della struttura {@link Impostazioni}, assegnandone il precedente.
 * Tramite la voce di menu passata come parametro capisce quale campo deve andare a modificare.
 * Questo metodo viene utilizzato per cambiare il valore di un campo dal menu impostazioni.
 *
 * @param voce Voce del menù impostazioni attualmente selezionata.
 * @param impostazioni Struttura {@link Impostazioni} da modificare.
 *
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni}, "false" altrimenti.
 */
bool valoreCampoImpostazioniPrec (voce_menu_impostazioni voce, Impostazioni &impostazioni);

/*
 * Modifica il valore di un determinato campo della struttura {@link Impostazioni}, assegnandone il successivo.
 * Tramite la voce di menu passata come parametro capisce quale campo deve andare a modificare.
 * Questo metodo viene utilizzato per cambiare il valore di un campo dal menu impostazioni.
 *
 * @param voce Voce del menù impostazioni attualmente selezionata.
 * @param impostazioni Struttura {@link Impostazioni} da modificare.
 *
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni}, "false" altrimenti.
 */
bool valoreCampoImpostazioniSuc (voce_menu_impostazioni voce, Impostazioni &impostazioni);
//FINE INTERFACCIA