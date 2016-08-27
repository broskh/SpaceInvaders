/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

//INIZIO INTERFACCIA

const unsigned int LARGHEZZA_DISPLAY = 640; /**<Larghezza della finestra del gioco.*/
const unsigned int ALTEZZA_DISPLAY = 480; /**<Altezza della finestra del gioco.*/
const unsigned int FPS = 60;  /**<FPS del gioco.*/
const char MENU [] [15] = {"Gioca", "Carica partita", "Opzioni", "Highscores"}; /**Voci del munù iniziale*/
const char FONT_FILE [] = "space_invaders.ttf"; /**File contenente il font utilizzato.*/
const unsigned int CENTRO_ORIZ = LARGHEZZA_DISPLAY / 2;
const unsigned int SPAZIO_TESTO = 10;

/**
 * Mostra il menù principale e ne gestisce il contenuto.
 */
void menuPrincipale ();

//FINE INTERFACCIA
