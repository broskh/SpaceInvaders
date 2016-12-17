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
 * Calcola il valore della schermata da mostrare all'uscita dal menù di pausa e agisce di conseguenza sulla partita.
 * 
 * @param menu Menù di pausa.
 * @param partita_in_corso Partita attualmente in pausa.
 * @param partita_salvata Valore booleano che indica se è presente una partita salvata.
 *
 * @return il valore della prossima schermata da mostrare.
 */
schermata cambiaSchermataMenuPausa (Menu menu, Partita partita_in_corso, bool &partita_salvata);

/**
 * Calcola il valore della prossima schermata da mostrare a seconda della selezione effettuta nel menù principale.
 * 
 * @param menu Menù principale.
 *
 * @return il valore della prossima schermata da mostrare.
 */
schermata cambiaSchermataMenuPrincipale (Menu menu);

/**
 * Inizializza un {@link Menu menù} con i valori necessari per utilizzarlo come menù delle impostazioni.
 *
 * @param menu Menu da inizializzare.
 */
void inizializzaMenuImpostazioni (Menu &menu);

/**
 * Inizializza un {@link Menu menù} con i valori necessari per utilizzarlo come menù di pausa.
 *
 * @param menu Menu da inizializzare.
 */
void inizializzaMenuPausa (Menu &menu);

/**
 * Inizializza un {@link Menu menù} con i valori necessari per utilizzarlo come menù principale.
 *
 * @param menu Menu da inizializzare.
 */
void inizializzaMenuPrincipale (Menu &menu);

/**
 * Nel menù la voce selezionata diventa la prima.
 * 
 * @param menu Menù da modificare.
 */
void selezionaPrimaVoce (Menu &menu);

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
 * @param menu Menù delle impostazioni.
 * @param impostazioni Struttura {@link Impostazioni} da modificare.
 *
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni}, "false" altrimenti.
 */
bool valoreCampoImpostazioniPrec (Menu menu, Impostazioni &impostazioni);

/*
 * Modifica il valore di un determinato campo della struttura {@link Impostazioni}, assegnandone il successivo.
 * Tramite la voce di menu passata come parametro capisce quale campo deve andare a modificare.
 *
 * @param menu Menù delle impostazioni.
 * @param impostazioni Struttura {@link Impostazioni} da modificare.
 *
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni}, "false" altrimenti.
 */
bool valoreCampoImpostazioniSuc (Menu menu, Impostazioni &impostazioni);

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
