/*
 * Header file contenente l'interfaccia del modulo per la gestione dei menu.
 */

//INIZIO COSTANTI RIGUARDANTI LE VOCI DI MENÙ
const generic_string MENU_PRINCIPALE [] = {"Gioca", "Carica partita", "Opzioni", "Highscores", "Esci"}; /**<Voci del munù principale.*/
const int N_VOCI_MENU_PRINC = 5; /**<Numero di voci del menù principale.*/
const generic_string MENU_IMPOSTAZIONI [] = {"Musica: ", "Effetti audio: ", "Colore alieni: ", "Vite iniziali: "}; /**<Voci del munù delle impostazioni.*/
const int N_VOCI_MENU_IMPO = 4; /**<Numero di voci del menù delle impostazioni.*/
const generic_string MENU_PAUSA [] = {"Continua partita", "Salva partita", "Abbandona partita"}; /**<Voci del menù di pausa.*/
const int N_VOCI_MENU_PAUSA = 3; /**<Numero di voci del menù di pausa.*/
//FINE COSTANTI RIGUARDANTI LE VOCI DI MENÙ

//INIZIO COSTANTI RIGUARDANTI I VALORI DELLE IMPOSTAZIONI
const char STRINGA_ON [] = "On"; /**<Stringa per rappresentare il valore "on".*/
const char STRINGA_OFF [] = "Off"; /**<Stringa per rappresentare il valore "off".*/
const char STRINGA_VERDE [] = "Verde"; /**<Stringa per rappresentare il {@link colore} "verde".*/
const char STRINGA_BIANCO [] = "Bianco"; /**<Stringa per rappresentare il {@link colore} "bianco".*/
const char STRINGA_ARANCIONE [] = "Arancione"; /**<Stringa per rappresentare il {@link colore} "arancione".*/
const char STRINGA_GIALLO [] = "Giallo"; /**<Stringa per rappresentare il {@link colore} "giallo".*/
const char STRINGA_BLU [] = "Blu"; /**<Stringa per rappresentare il {@link colore} "blu".*/
//FINEquindi COSTANTI RIGUARDANTI I VALORI DELLE IMPOSTAZIONI

//INIZIO INTERFACCIA
/**
 * Calcola il valore della schermata da mostrare all'uscita dal menù di pausa e agisce di conseguenza sulla partita.
 * 
 * @param menu {@link Menu Menù} di pausa.
 * @param partita_in_corso Partita attualmente in pausa.
 * @param partita_salvata Valore che indica se è presente una partita salvata.
 *
 * @return il valore della prossima schermata da mostrare.
 */
schermata cambiaSchermataMenuPausa (Menu menu, Partita partita_in_corso, bool &partita_salvata);

/**
 * Calcola il valore della prossima schermata da mostrare a seconda della selezione effettuta nel menù principale.
 * 
 * @param menu {@link Menu Menù} principale.
 *
 * @return il valore della prossima schermata da mostrare.
 */
schermata cambiaSchermataMenuPrincipale (Menu menu);

/**
 * Inizializza il {@link Menu menù} delle impostazioni.
 *
 * @param menu {@link Menu Menù} da inizializzare.
 */
void inizializzaMenuImpostazioni (Menu &menu);

/**
 * Inizializza il {@link Menu menù} di pausa.
 *
 * @param menu {@link Menu Menù} da inizializzare.
 */
void inizializzaMenuPausa (Menu &menu);

/**
 * Inizializza il {@link Menu menù} principale.
 *
 * @param menu {@link Menu Menù} da inizializzare.
 */
void inizializzaMenuPrincipale (Menu &menu);

/**
 * Seleziona la prima voce di menù.
 * 
 * @param menu {@link Menu Menù} da modificare.
 */
void selezionaPrimaVoce (Menu &menu);

/**
 * Genera una stringa in grado di rappresentare lo stato del valore di un particolare campo delle impostazioni.
 *
 * @param stringa Stringa che conterrà il risultato.
 * @param dimensione_stringa Dimensione massima della stringa.
 * @param voce Voce del {@link Menu menù} delle impostazioni della quale si vuole ottenere la stringa rappresentante il valore.
 * @param impostazioni {@link Impostazioni} dalle quali controllare il valore del campo.
 * 
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni} valido, "false" altrimenti.
 */
bool stringaValoreVoceImpostazioni (char stringa [], size_t dimensione_stringa, voce_menu_impostazioni voce, Impostazioni impostazioni);

/**
 * Modifica il valore di un determinato campo delle Impostazioni, assegnandone il precedente.
 * Identifica il campo da modificare attraverso la voce del {@link Menu menù} delle impostazioni selezionata.
 *
 * @param menu_impostazioni {@link Menu Menù} delle impostazioni.
 * @param impostazioni Struttura {@link Impostazioni} da modificare.
 *
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni} valido, "false" altrimenti.
 */
bool valoreCampoImpostazioniPrec (Menu menu_impostazioni, Impostazioni &impostazioni);

/**
 * Modifica il valore di un determinato campo delle Impostazioni, assegnandone il successivo.
 * Identifica il campo da modificare attraverso la voce del {@link Menu menù} delle impostazioni selezionata.
 *
 * @param menu_impostazioni {@link Menu Menù} delle impostazioni.
 * @param impostazioni Struttura {@link Impostazioni} da modificare.
 *
 * @return "true" se la voce di menù passata corrispone ad un tipo {@link voce_menu_impostazioni} valido, "false" altrimenti.
 */
bool valoreCampoImpostazioniSuc (Menu menu_impostazioni, Impostazioni &impostazioni);

/**
 * Modifica il valore della voce selezionata impostandola alla precedente.
 * 
 * @param menu {@link Menu Menù} nel quale modificare la voce selezionata.
 */
void vocePrec (Menu &menu);

/**
 * Modifica il valore della voce selezionata impostandola alla precedente.
 * 
 * @param menu {@link Menu Menù} nel quale modificare la voce selezionata.
 * @param voce_saltata Voce da saltare nella ricerca della precedente.
 */
void vocePrec (Menu &menu, int voce_saltata);

/**
 * Modifica il valore della voce selezionata impostandola alla successiva.
 * 
 * @param menu {@link Menu Menù} nel quale modificare la voce selezionata.
 */
void voceSuc (Menu &menu);

/**
 * Modifica il valore della voce selezionata impostandola alla successiva.
 * 
 * @param menu {@link Menu Menù} nel quale modificare la voce selezionata.
 * @param voce_saltata Voce da saltare nella ricerca della successiva.
 */
void voceSuc (Menu &menu, int voce_saltata);
//FINE INTERFACCIA