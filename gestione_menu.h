/*
 * Header file contenente l'interfaccia del modulo per la gestione dei menu.
 */

//INIZIO COSTANTI RIGUARDANTI LE VOCI DI MENÙ
const generic_string MENU_PRINCIPALE [] = {"Gioca", "Carica partita", "Opzioni", "Highscores", "Esci"}; /**<Voci del munù principale.*/
const int N_VOCI_MENU_PRINC = 5; /**<Numero di voci del menù principale.*/
const generic_string MENU_IMPOSTAZIONI [] = {"Musica: ", "Effetti audio: ", "Colore alieni: ", "Vite iniziali: "}; /**<Voci del munù impostazioni.*/
const int N_VOCI_MENU_IMPO = 4; /**<Numero di voci del menù impostazioni.*/
const generic_string MENU_PAUSA [] = {"Continua partita", "Salva partita", "Abbandona partita"}; /**<Voci del menù di pausa.*/
const int N_VOCI_MENU_PAUSA = 3; /**<Numero di voci del menù di pausa.*/
//FINE COSTANTI RIGUARDANTI LE VOCI DI MENÙ

//INIZIO COSTANTI RIGUARDANTI LE INDICAZIONI DEL MENÙ IMPOSTAZIONI
const generic_long_string INDICAZIONI_IMPOSTAZIONI [] = {"Usa le frecce su e giu' per cambiare opzione", "Usa le frecce destra e sinistra per modificare il valore", "Premi enter per salvare e tornare al menu principale", "Premi R per ripristinare i valori di default"}; /**<Indicazioni del menù impostazioni.*/
const int N_INDICAZIONI_MENU_IMPO = 4; /**<Numero di indicazioni del menù impostazioni.*/
//FINE COSTANTI RIGUARDANTI LE INDICAZIONI DEL MENÙ IMPOSTAZIONI

//INIZIO COSTANTI RIGUARDANTI I VALORI DELLE IMPOSTAZIONI
const char STRINGA_ON [] = "On"; /**<Stringa per rappresentare il valore "on".*/
const char STRINGA_OFF [] = "Off"; /**<Stringa per rappresentare il valore "off".*/
const char STRINGA_VERDE [] = "Verde"; /**<Stringa per rappresentare il valore "verde".*/
const char STRINGA_BIANCO [] = "Bianco"; /**<Stringa per rappresentare il valore "bianco".*/
const char STRINGA_ARANCIONE [] = "Arancione"; /**<Stringa per rappresentare il valore "arancione".*/
const char STRINGA_GIALLO [] = "Giallo"; /**<Stringa per rappresentare il valore "giallo".*/
const char STRINGA_BLU [] = "Blu"; /**<Stringa per rappresentare il valore "blu".*/
//FINEquindi COSTANTI RIGUARDANTI I VALORI DELLE IMPOSTAZIONI

//INIZIO INTERFACCIA
/**
 * Memorizza in una struttura {@link Menu} i valori passati per parametro.
 *
 * @param menu Menu che conterrà le informazioni passate come parametro.
 * @param testi_menu Testi che rappresentano le voci di menù.
 * @param n_voci Numero di voci del menù.
 * @param voce_sel Voce di menù attualmente selezionata.
 */
void inizializzaMenu (Menu &menu, const generic_string testi_menu [], int n_voci, int voce_sel);

/**
 * Genera una stringa in grado di rappresentare lo stato del valore di un particolare campo delle impostazioni.
 * Necessita di conoscere la voce del menù impostazioni alla quale ci si riferisce per poter capire di quale 
 * striga ritornare.
 *
 * @param stringa Stringa contenente il valore di una determinato campo delle {@link Impostazioni}.
 * @param voce Voce del menù impostazioni della quale si vuole ottenere il valore come stringa.
 * @param impostazioni Struttura {@link Impostazioni} dal quale si controlla il valore del campo.
 * 
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni}, "false" altrimenti.
 */
bool stringaValoreVoceImpostazioni (char stringa [], voce_menu_impostazioni voce, Impostazioni impostazioni);

/*
 * Modifica il valore di un determinato campo della struttura {@link Impostazioni}, assegnandone il precedente.
 * Tramite la voce di menu passata come parametro capisce quale campo deve andare a modificare.
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
 *
 * @param voce Voce del menù impostazioni attualmente selezionata.
 * @param impostazioni Struttura {@link Impostazioni} da modificare.
 *
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni}, "false" altrimenti.
 */
bool valoreCampoImpostazioniSuc (voce_menu_impostazioni voce, Impostazioni &impostazioni);

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
//FINE INTERFACCIA