/*
 * Header file contenente l'interfaccia del modulo per la gestione della grafica.
 */

//INIZIO COSTANTI GRAFICHE GENERALI
const unsigned int ALTEZZA_DISPLAY = 480; /**<Altezza della finestra del gioco.*/
const unsigned int LARGHEZZA_DISPLAY = 640; /**<Larghezza della finestra del gioco.*/
const unsigned int MARGINE_SX_GIOCO = 30; /**<Posizione del margine sinistro del gioco.*/
const unsigned int MARGINE_DX_GIOCO = LARGHEZZA_DISPLAY - MARGINE_SX_GIOCO; /**<Posizione del margine destro del gioco.*/
const unsigned int MARGINE_INF_GIOCO = 470; /**<Posizione del margine inferiore del gioco.*/
const unsigned int MARGINE_SUP_GIOCO = 45; /**<Posizione del margine superiore del gioco.*/
const unsigned int POS_CENTRO_X = ((MARGINE_DX_GIOCO - MARGINE_SX_GIOCO) / 2) + MARGINE_SX_GIOCO; /**<Posizione centrale della della finestra rispetto all'asse delle x.*/
//FINE COSTANTI GRAFICHE GENERALI

//INIZIO COSTANTI PER FONT E TESTI
const unsigned int DIMENSIONE_TESTO = 15; /**<Dimensione del font utilizzato per i testi generali.*/
const unsigned int DIMENSIONE_TITOLO = 140; /**<Dimensione del font utilizzato per il titolo.*/
const unsigned int SPAZIO_TESTO = 10; /**<Spazio fra righe di testo adiacenti.*/
const unsigned int SPAZIO_TESTO_GRANDE = 30; /**<Spazio grande fra righe di testo adiacenti.*/
//FINE COSTANTI PER FONT E TESTI

//INIZIO COSTANTI SCHERMATA FINE PARTITA
const char STRINGA_INDICAZIONI_FINE_PARTITA [] = "Premi enter per salvare e tornare al menu principale"; /**<Indicazione nella schermata di fine partita.*/
//FINE COSTANTI SCHERMATA FINE PARTITA

//INIZIO COSTANTI SCHERMATA DEL MENU PRINCIPALE
const unsigned int POS_X_ESEMPIO_ALIENI = 255; /**<Posizione rispetto all'asse x dalla quale mostrare gli alieni d'esempio nel menù principale.*/
const unsigned int POS_X_ESEMPIO_PUNTEGGIO = 305; /**<Posizione rispetto all'asse x dalla quale mostrare i punteggi degli alieni d'esempio nel menù principale.*/
const unsigned int POS_Y_ESMEPIO_ALIENI = 200; /**<Posizione rispetto all'asse y dalla quale mostrare gli alieni d'esempio nel menù principale.*/
const unsigned int POS_Y_TITOLO_MENU_PRINCIPALE = 25; /**<Posizione rispetto all'asse y nella quale mostrare il titolo nel menù principale.*/
const unsigned int POS_Y_VOCI_MENU_PRINCIPALE = 340; /**<Posizione rispetto all'asse y dalla quale mostrare le voci del menù principale.*/
const char STRINGA_PUNTEGGIO_ALIENI [] = "  PTS"; /**<Stringa utilizzata per rappresentare il punteggio degli alieni.*/
const char STRINGA_PUNTEGGIO_NAVICELLA_MISTERIOSA [] = "=      ?  PTS"; /**<Stringa utilizzata per rappresentare il punteggio della navicella misteriosa.*/
const char STRINGA_TITOLO_MENU_PRINCIPALE [] = "."; /**<Titolo nella schermata del menù principale.*/
//FINE COSTANTI SCHERMATA DEL MENU PRINCIPALE

//INIZIO COSTANTI SCHERMATA DI GIOCO
const unsigned int DISTANZA_ASSI_COL_ALIENI = 40; /**<Distanza fra gli assi delle colonne degli alieni.*/
const unsigned int DISTANZA_BARRIERE = 64; /**<Distanza fra le barriere.*/
const unsigned int DISTANZA_FILE_ALIENI = 35; /**<Distanza fra le file di alieni.*/
const unsigned int POS_X_PRIMA_BARRIERA = DISTANZA_BARRIERE; /**<Posizione rispetto all'asse x dalla quale mostrare la prima barriera.*/
const unsigned int POS_X_PRIMO_ASSE_ALIENI = POS_CENTRO_X - (DISTANZA_ASSI_COL_ALIENI * (N_COL_ALIENI - 1) / 2); /**<Posizone rispetto all'asse x dalla quale mostrare il primo asse di colonne degli alieni.*/
const unsigned int POS_Y_BARRIERE = 360; /**<Posizone rispetto all'asse y dalla quale mostrare la prima barriera.*/
const unsigned int POS_Y_INFORMAZIONI_PARTITA = 10; /**<Posizione rispetto all'asse y dalla quale mostrare le informazioni della partita.*/
const unsigned int POS_Y_PRIMA_FILA_ONDATA = 80; /**<Posizione rispetto all'asse y dalla quale mostrare la prima fila di alieni.*/
const char STRINGA_PUNTEGGIO [] = "Punteggio:    "; /**<Stringa utilizzata nella rappresentazione del punteggio nella schermata di gioco.*/
const char STRINGA_VITE [] = "Vite:    "; /**<Stringa utilizzata nella rappresentazione delle vite nella schermata di gioco.*/
//FINE COSTANTI SCHERMATA DI GIOCO

//INIZIO COSTANTI SCHERMATA DEL MENU IMPOSTAZIONI
const unsigned int POS_X_VALORI_IMPOSTAZIONI = 270; /**<Posizione rispetto all'asse x dalla quale mostrare i valori dei vari campi impostazioni.*/
const unsigned int POS_X_VOCI_IMPOSTAZIONI = 95; /**<Posizione rispetto all'asse x dalla quale mostrare i campi impostazioni.*/
const unsigned int POS_Y_IMPOSTAZIONI = 105; /**<Posizione rispetto all'asse y dalla quale mostrare i campi impostazioni.*/
const unsigned int POS_Y_INDICAZIONI_IMPOSTAZIONI = 310; /**<Posizione rispetto all'asse y dalla quale mostrare le indicazioni della schermata del meù impostazioni.*/
const unsigned int POS_Y_TITOLO_IMPOSTAZIONI = 60; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo della schermata del meù impostazioni.*/
const char STRINGA_TITOLO_IMPOSTAZIONI [] = "IMPOSTAZIONI:"; /**<Titolo nella schermata del menù delle impostazioni.*/
//FINE COSTANTI SCHERMATA DEL MENU IMPOSTAZIONI

//INIZIO COSTANTI SCHERMATA DEGLI HIGHSCORES
const unsigned int POS_X_NOMI_PUNTEGGI = 280; /**<Posizione rispetto all'asse x dalla quale mostrare i nomi dei giocatori che hanno realizzato i punteggi.*/
const unsigned int POS_X_NUMERAZIONE_PUNTEGGI = 250; /**<Posizione rispetto all'asse x dalla quale mostrare il numero dei punteggi.*/
const unsigned int POS_X_VALORI_PUNTEGGI = 330; /**<Posizione rispetto all'asse x dalla quale mostrare i valori dei punteggi.*/
const unsigned int POS_Y_ELENCO_PUNTEGGI = 90; /**<Posizione rispetto all'asse y dalla quale mostrare i punteggi.*/
const unsigned int POS_Y_HIGHSCORES_TITOLO = 60; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo della schermata degli highscores.*/
const unsigned int POS_Y_INDICAZIONI_HIGHSCORES = 410; /**<Posizione rispetto all'asse y dalla quale mostrare le indicazioni della schermata degli highscores.*/
const char STRINGA_INDICAZIONI_HIGHSCORES [] = "Premi enter per tornare al menu principale"; /**<Indicazione nella schermata della classifica degli highscores.*/
const char STRINGA_TITOLO_HIGHSCORES [] = "HIGHSCORES:";  /**<Titolo nella schermata della classifica degli highscores.*/
//FINE COSTANTI SCHERMATA DEGLI HIGHSCORES

//INIZIO COSTANTI SCHERMATA DEL MENU DI PAUSA
const unsigned int POS_Y_TITOLO_PAUSA = 100; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo del menù di pausa.*/
const unsigned int POS_Y_VOCI_PAUSA = 220; /**<Posizione rispetto all'asse y dalla quale mostrare le voci del menù di pausa.*/
const char STRINGA_TITOLO_PAUSA [] = "PAUSA";  /**<Titolo nella schermata del menù di pausa.*/
//FINE COSTANTI SCHERMATA DEL MENU DI PAUSA

//INIZIO COSTANTI GENERICHE DI GIOCO
const unsigned int N_STATI_SPRITE = 2; /**<Numero di stati degli sprite.*/
const int RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_ALIENI = 1; /**<Numero di ripetizioni dell'animazione dell'esplosione degli alieni.*/
const int RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_CARRO = 2; /**<Numero di ripetizioni dell'animazione dell'esplosione del carro armato.*/
//FINE COSTANTI GENERICHE DI GIOCO

//INIZIO COSTANTI PER FILE
const char FILE_ALIENO_TIPO_1 [] ="Images/alieno1.png"; /**<Percorso del file contenente l'immagine per rappresentare l'alieno di tipo 1.*/
const char FILE_ALIENO_TIPO_2 [] ="Images/alieno2.png"; /**<Percorso del file contenente l'immagine per rappresentare l'alieno di tipo 2.*/
const char FILE_ALIENO_TIPO_3 [] ="Images/alieno3.png"; /**<Percorso del file contenente l'immagine per rappresentare l'alieno di tipo 3.*/
const char FILE_BARRIERA [] = "Images/barriera.png"; /**<Percorso del file contenente l'immagine per rappresentare un'unità della barriera.*/
const char FILE_CARRO_ARMATO [] ="Images/carro_armato.png"; /**<Percorso del file contenente l'immagine per rappresentare il carro armato.*/
const char FILE_ESPLOSIONE_ALIENO [] = "Images/esplosione_alieno.png"; /**<Percorso del file contenente l'immagine per rappresentare l'esplosione di un alieno.*/
const char FILE_ESPLOSIONE_CARRO [] = "Images/esplosione_carro.png"; /**<Percorso del file contenente l'immagine per rappresentare l'esplosione carro armato.*/
const char FILE_FONT_TESTO [] = "Fonts/space_invaders.ttf"; /**<Percorso del file contenente il font utilizzato per i testi.*/
const char FILE_FONT_TITOLO [] = "Fonts/dustbust_invaders.ttf"; /**<Percorso del file contenente il font utilizzato per il titolo nel menù principale.*/
const char FILE_NAVICELLA_MISTERIOSA [] ="Images/navicella_misteriosa.png"; /**<Percorso del file contenente l'immagine per rappresentare la navicella misteriosa.*/
const char FILE_SPARO_ALIENI_1 [] = "Images/sparo_alieni_1.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x pari.*/
const char FILE_SPARO_ALIENI_2 [] = "Images/sparo_alieni_2.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x dispari.*/
const char FILE_SPARO_CARRO [] ="Images/sparo_carro.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo del carro armato.*/
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA
/**
 * Fornisce l'altezza in pixel di un alieno.
 * Non viene fatta distinzione per la fila alla quale appartiene l'alieno, perchè per migliorare l'aspetto del gioco gli alieni devono 
 * avere tutti la stessa altezza.
 * 
 * @return l'altezza dell'alieno.
 */
unsigned int altezzaAlieno ();

/**
 * Fornisce l'altezza in pixel del carro armato.
 *
 * @return l'altezza del carro armato.
 */
unsigned int altezzaCarroArmato ();

/**
 * Fornisce l'altezza in pixel di un'unità che compone la barriera.
 *
 * @return l'altezza di un'unità che compone la barriera.
 */
unsigned int altezzaLatoUnitaBarriera ();

/**
 * Fornisce l'altezza in pixel della navicella misteriosa.
 *
 * @return l'altezza della navicella misteriosa.
 */
unsigned int altezzaNavicellaMisteriosa ();

/**
 * Fornisce l'altezza in pixel dello sparo alieno corretto sulla base della posizione rispetto all'asse x dello sparo.
 *
 * @param pos_x_sparo Posizione rispetto all'asse x dello sparo alieno.
 *
 * @return l'altezza dello sparo alieno corretto.
 */
unsigned int altezzaSparoAlienoAttuale (unsigned int pos_x_sparo);

/**
 * Fornisce l'altezza in pixel dello sparo del carro armato.
 *
 * @return l'altezza dello sparo del carro armato.
 */
unsigned int altezzaSparoCarroArmato ();

/**
 * Procedura di distruzione del modulo per la gestione della grafica.
 * Si occupa di deallocare correttamente la memoria alloccata in fase di inizializzazione del modulo.
 */
void distruggiGrafica ();

/**
 * Procedura di inizializzazione del modulo per la gestione della grafica.
 * Si occupa di inizializzare correttamente tutte le variabili necessarie e di seguire i metodi di inizializzazione di determinate librerie "Allegro".
 * 
 * @return "true" se il modulo è stato correttamente inizializzato, "false" altrimenti.
 */
bool inizializzaGrafica ();

/**
 * Fornisce la larghezza in pixel dell'alieno sulla base del numero della fila dell'ondata nella quale si trova.
 *
 * @param n_fila_alieno Numero della fila dell'ondata nella quale si trova l'alieno.
 *
 * @return la larghezza dell'alieno.
 */
unsigned int larghezzaAlieno (unsigned int n_fila_alieno);

/**
 * Fornisce la larghezza in pixel del carro armato.
 *
 * @return la larghezza del carro armato.
 */
unsigned int larghezzaCarroArmato ();

/**
 * Fornisce la larghezza in pixel di un'unità che compone la barriera.
 *
 * @return la larghezza di un'unità che compone la barriera.
 */
unsigned int larghezzaLatoUnitaBarriera ();

/**
 * Fornisce la larghezza in pixel della navicella misteriosa.
 *
 * @return la larghezza della navicella misteriosa.
 */
unsigned int larghezzaNavicellaMisteriosa ();

/**
 * Fornisce la larghezza in pixel dello sparo alieno corretto sulla base della posizione rispetto all'asse x dello sparo.
 *
 * @param pos_x_sparo Posizione rispetto all'asse x dello sparo alieno.
 *
 * @return la larghezza dello sparo alieno corretto.
 */
unsigned int larghezzaSparoAlienoAttuale (unsigned int pos_x_sparo);

/**
 * Fornisce la larghezza in pixel dello sparo del carro armato.
 *
 * @return la larghezza dello sparo del carro armato.
 */
unsigned int larghezzaSparoCarroArmato ();

/*
 * Stampa sul display tutto il contenuto che riguarda la schermata di fine partita.
 *
 * @param classifica Classifica degli highscores.
 * @param partita Partita appena terminata.
 * @param posizione_punteggio_attuale Posizione all'interno della classifica del punteggio raggiunto nella partita appena terminata. É uguale a "-1" se non rientra all'interno della classifica.
 * @param redraw_lampeggio Valore booleano che indica se è necessario mostrare o no gli elementi che necessitano di un effetto lampeggiante.
 */
void stampaFinePartita (Classifica classifica, Partita partita, int posizione_punteggio_attuale, bool redraw_lampeggio);

/*
 * Stampa sul display tutto il contenuto che riguarda la schermata di gioco.
 *
 * @param partita Partita in corso.
 * @param animazione Valore booleano utilizzato per fare determinate scelte riguardo ad alcuni elementi da mostrare, consentendo così un effetto di animazione.
 * @param colore_alieni Colore con il quale mostrare gli alieni.
 */
void stampaGioca (Partita partita, bool animazione, colore colore_alieni);

/*
 * Stampa sul display tutto il contenuto che riguarda la schermata degli highscores.
 *
 * @param classifica Classifica degli highscores.
 */
void stampaHighscores (Classifica classifica);

/*
 * Stampa sul display tutto il contenuto che riguarda la schermata del menù impostazioni.
 *
 * @param menu_impostazioni Menu delle impostazioni.
 * @param impostazioni Impostazioni da mostrare.
 * @param redraw_lampeggio Valore booleano che indica se è necessario mostrare o no gli elementi che necessitano di un effetto lampeggiante.
 */
void stampaImpostazioni (Menu menu_impostazioni, Impostazioni impostazioni, bool redraw_lampeggio);

/*
 * Stampa sul display tutto il contenuto che riguarda la schermata del menù di pausa.
 *
 * @param menu_pausa Menu di pausa.
 * @param redraw_lampeggio Valore booleano che indica se è necessario mostrare o no gli elementi che necessitano di un effetto lampeggiante.
 */
void stampaMenuPausa (Menu menu_pausa, bool redraw_lampeggio);

/*
 * Stampa sul display tutto il contenuto che riguarda la schermata del menù principale.
 *
 * @param menu_principale Menu principale.
 * @param partita_salvata Valore booleano che indica se è presente una partita salvata o me no.
 * @param colore_alieni Colore con il quale mostrare gli alieni.
 * @param redraw_lampeggio Valore booleano che indica se è necessario mostrare o no gli elementi che necessitano di un effetto lampeggiante.
 */
void stampaMenuPrincipale (Menu menu_principale, bool partita_salvata, colore colore_alieni, bool redraw_lampeggio);
//FINE INTERFACCIA
