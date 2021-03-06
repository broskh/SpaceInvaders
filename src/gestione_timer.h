/*
 * Header file contenente l'interfaccia del modulo per la gestione dei timer.
 */

//INIZIO COSTANTI PER VARI TIMER
const float FREQUENZA_ANIMAZIONE = 4; /**<Frequenza dell'animazione.*/
const float FREQUENZA_COMPARSA_NAVICELLA_MISTERIOSA = 0.3; /**<Frequenza della possibile comparsa della navicella misteriosa.*/
const float FREQUENZA_COMPARSA_SPARO_ALIENI = 0.75; /**<Frequenza di creazione degli spari alieni.*/
const float FPS_GIOCO = 60; /**<FPS del gioco.*/
const float FREQUENZA_LAMPEGGIO_MENU = 3.5; /**<Frequenza dell'effetto lampeggiante.*/
const float FREQUENZA_SPOSTAMENTO_CARRO_ARMATO = 115; /**<Frequenza dello spostamento del carro armato.*/
const float FREQUENZA_SPOSTAMENTO_NAVICELLA_MISTERIOSA = 150; /**<Frequenza dello spostamento della navicella misteriosa.*/
const float FREQUENZA_SPOSTAMENTO_ONDATA_MAX = 130; /**<Frequenza massima del movimento dell'ondata.*/
const float FREQUENZA_SPOSTAMENTO_ONDATA_MIN = 60; /**<Frequenza minima del movimento dell'ondata.*/
const float FREQUENZA_SPOSTAMENTO_SPARI = 200; /**<Frequenza dello spostamento degli spari.*/
//FINE COSTANTI PER VARI TIMER

//INIZIO INTERFACCIA
/**
 * Aggiorna la velocità prendendo in considerazione la frequenza {@link FREQUENZA_SPOSTAMENTO_ONDATA_MAX massima} e {@link FREQUENZA_SPOSTAMENTO_ONDATA_MIN minima} di spostamento e la percentuale di velocità degli alieni.
 *
 * @param percentuale_velocita_alieni Percentuale di velocità degli alieni.
 */
void aggiornaVelocitaSpostamentoOndata (unsigned int percentuale_velocita_alieni);

/**
 * Avvia il timer che gestisce la frequenza di animazione.
 */
void avviaTimerAnimazione ();

/**
 * Avvia il timer che gestisce la frequenza di comparsa della navicella misteriosa.
 */
void avviaTimerComparsaNavicellaMisteriosa ();

/**
 * Avvia il timer che gestisce la frequenza di comparsa dello sparo alieno.
 */
void avviaTimerComparsaSparoAlieni ();

/**
 * Avvia il timer che gestisce la frequenza per realizzare l'effetto di lampeggio.
 */
void avviaTimerEffettoLampeggio ();

/**
 * Avvia il timer che gestisce il frame rate dell'intero gioco.
 */
void avviaTimerFps ();

/**
 * Avvia il timer che gestisce la frequenza di spostamento del carro armato.
 */
void avviaTimerSpostamentoCarroArmato ();

/**
 * Avvia il timer che gestisce la frequenza di spostamento dell'ondata di alieni.
 */
void avviaTimerSpostamentoOndata ();

/**
 * Avvia il timer che gestisce la frequenza di spostamento della navicella misteriosa.
 */
void avviaTimerSpostamentoNavicellaMisteriosa ();

/**
 * Avvia il timer che gestisce la frequenza di spostamento degli spari.
 */
void avviaTimerSpostamentoSpari ();

/**
 * Procedura di distruzione del modulo per la gestione dei timer.
 * Si occupa di deallocare correttamente la memoria alloccata in fase di inizializzazione del modulo.
 */
void distruggiTimer ();

/**
 * Ferma il timer che gestisce la frequenza di animazione.
 */
void fermaTimerAnimazione ();

/**
 * Ferma il timer che gestisce la frequenza di comparsa della navicella misteriosa.
 */
void fermaTimerComparsaNavicellaMisteriosa ();

/**
 * Ferma il timer che gestisce la frequenza di comparsa dello sparo alieno.
 */
void fermaTimerComparsaSparoAlieni ();

/**
 * Ferma il timer che gestisce la frequenza per realizzare l'effetto di lampeggio.
 */
void fermaTimerEffettoLampeggio ();

/**
 * Ferma il timer che gestisce il frame rate dell'intero gioco.
 */
void fermaTimerFps ();

/**
 * Ferma il timer che gestisce la frequenza di spostamento del carro armato.
 */
void fermaTimerSpostamentoCarroArmato ();

/**
 * Ferma il timer che gestisce la frequenza di spostamento dell'ondata di alieni.
 */
void fermaTimerSpostamentoOndata ();

/**
 * Ferma il timer che gestisce la frequenza di spostamento della navicella misteriosa.
 */
void fermaTimerSpostamentoNavicellaMisteriosa ();

/**
 * Ferma il timer che gestisce la frequenza di spostamento degli spari.
 */
void fermaTimerSpostamentoSpari ();

/**
 * Procedura di inizializzazione del modulo per la gestione dei timer.
 * Si occupa di inizializzare correttamente tutte le variabili necessarie e di eseguire i metodi di inizializzazione di determinate librerie "Allegro".
 * 
 * @return "true" se il modulo è stato correttamente inizializzato, "false" altrimenti.
 */
bool inizializzaTimer (ALLEGRO_EVENT_QUEUE *coda);

/**
 * Restituisce il puntatore al timer che gestisce la frequenza di animazione.
 * 
 * @return il puntatore al timer che gestisce la frequenza di animazione.
 */
ALLEGRO_TIMER * timerAnimazione ();

/**
 * Restituisce il puntatore al timer che gestisce la frequenza di comparsa della navicella misteriosa.
 * 
 * @return il puntatore al timer che gestisce la frequenza di comparsa della navicella misteriosa.
 */
ALLEGRO_TIMER * timerComparsaNavicellaMisteriosa ();

/**
 * Restituisce il puntatore al timer che gestisce la frequenza di comparsa dello sparo alieno.
 * 
 * @return il puntatore al timer che gestisce la frequenza di comparsa dello sparo alieno.
 */
ALLEGRO_TIMER * timerComparsaSparoAlieni ();

/**
 * Restituisce il puntatore al timer che gestisce la frequenza per realizzare l'effetto di lampeggio.
 * 
 * @return il puntatore al timer che gestisce la frequenza per realizzare l'effetto di lampeggio.
 */
ALLEGRO_TIMER * timerEffettoLampeggio ();

/**
 * Restituisce il puntatore al timer che gestisce il frame rate dell'intero gioco.
 * 
 * @return il puntatore al timer che gestisce il frame rate dell'intero gioco.
 */
ALLEGRO_TIMER * timerFps ();

/**
 * Restituisce il puntatore al timer che gestisce la frequenza di spostamento del carro armato.
 * 
 * @return il puntatore al timer che gestisce la frequenza di spostamento del carro armato.
 */
ALLEGRO_TIMER * timerSpostamentoCarroArmato ();

/**
 * Restituisce il puntatore al timer che gestisce la frequenza di spostamento dell'ondata di alieni.
 * 
 * @return il puntatore al timer che gestisce la frequenza di spostamento dell'ondata di alieni.
 */
ALLEGRO_TIMER * timerSpostamentoOndata ();

/**
 * Restituisce il puntatore al timer che gestisce la frequenza di spostamento della navicella misteriosa.
 * 
 * @return il puntatore al timer che gestisce la frequenza di spostamento della navicella misteriosa.
 */
ALLEGRO_TIMER * timerSpostamentoNavicellaMisteriosa ();

/**
 * Restituisce il puntatore al timer che gestisce la frequenza di spostamento degli spari.
 * 
 * @return il puntatore al timer che gestisce la frequenza di spostamento degli spari.
 */
ALLEGRO_TIMER * timerSpostamentoSpari ();
//FINE INTERFACCIA
