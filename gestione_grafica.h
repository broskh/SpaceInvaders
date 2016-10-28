/*
 * Header file contenente l'interfaccia del modulo di gestione dela grafica.
 */

//INIZIO COSTANTI GENERALI PER DISPLAY
const unsigned int LARGHEZZA_DISPLAY = 640; /**<Larghezza della finestra del gioco.*/
const unsigned int ALTEZZA_DISPLAY = 480; /**<Altezza della finestra del gioco.*/

const unsigned int MARGINE_SX_GIOCO = 30; /**<Margine sinistro del gioco.*/
const unsigned int MARGINE_DX_GIOCO = LARGHEZZA_DISPLAY - MARGINE_SX_GIOCO; /**<Margine destro del gioco.*/
const unsigned int MARGINE_SUP_GIOCO = 45; /**<Margine superiore del gioco.*/
const unsigned int MARGINE_INF_GIOCO = 470; /**<Margine inferiore del gioco.*/
const unsigned int POS_CENTRO_X = ((MARGINE_DX_GIOCO - MARGINE_SX_GIOCO) / 2) + MARGINE_SX_GIOCO; /**<Posizione centrale della del display rispetto all'asse delle x.*/
//FINE COSTANTI GENERALI PER DISPLAY

//INIZIO COSTANTI PER FONT E TESTI
const unsigned int SPAZIO_TESTO = 10; /**<Spazio fra righe di testo adiacenti.*/
const unsigned int SPAZIO_TESTO_GRANDE = 30; /**<Spazio grande fra righe di testo adiacenti.*/
const unsigned int DIMENSIONE_TITOLO = 140; /**<Dimensione del font utilizzato per il titolo.*/
const unsigned int DIMENSIONE_TESTO = 15; /**<Dimensione del font utilizzato per i testi generali.*/
//FINE COSTANTI PER FONT E TESTI

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU PRINCIPALE
const unsigned int POS_X_ESEMPIO_ALIENI = 255; /**<Posizione rispetto all'asse x dalla quale mostrare i alieni nel menù principale.*/
const unsigned int POS_X_ESEMPIO_PUNTEGGIO = 350; /**<Posizione rispetto all'asse x dalla quale mostrare i punteggi nel menù principale.*/
const unsigned int POS_Y_TITOLO_MENU_PRINCIPALE = 25; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo nel menù principale.*/
const unsigned int POS_Y_ESMEPIO_ALIENI = 200; /**<Posizione rispetto all'asse y dalla quale mostrare i alieni nel menù principale.*/
const unsigned int POS_Y_VOCI_MENU_PRINCIPALE = 340; /**<Posizione rispetto all'asse y dalla quale mostrare il menu nel menù principale.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU PRINCIPALE

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DI GIOCO
const unsigned int POS_Y_INFORMAZIONI_PARTITA = 10; /**<Posizione rispetto all'asse y dalla quale mostrare le informazioni della partita.*/
const unsigned int POS_Y_PRIMA_FILA_ONDATA = 80; /**<Posizione rispetto all'asse y dalla quale mostrare la prima fila di alieni.*/
const unsigned int POS_Y_BARRIERE = 360; /**<Posizone rispetto all'asse y dalla quale mostrare la prima barriera.*/

const unsigned int DISTANZA_ASSI_COL_ALIENI = 40; /**<Distanza fra gli assi delle colonne di alieni.*/
const unsigned int DISTANZA_FILE_ALIENI = 35; /**<Distamza fra le file di alieni.*/
const unsigned int DISTANZA_BARRIERE = 64; /**<Distanza in pixel fra le barriere.*/ //(LARGHEZZA_DISPLAY - (DIMENSIONE_LATO_UNITA_BARRIERA * LARG_BARRIERA * N_BARRIERE)) / (N_BARRIERE + 1);
const unsigned int POS_X_PRIMA_BARRIERA = DISTANZA_BARRIERE; /**<Posizione rispetto all'asse x della prima barriera.*/
const unsigned int POS_X_PRIMO_ASSE_ALIENI = POS_CENTRO_X - (DISTANZA_ASSI_COL_ALIENI * (N_COL_ALIENI - 1) / 2); /**<Posizone rispetto all'asse x nella quale è presente il primo asse delle colonne di alieni.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DI GIOCO

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU IMPOSTAZIONI
const unsigned int POS_X_VOCI_IMPOSTAZIONI = 95; /**<Posizione rispetto all'asse x dalla quale mostrare  il contenuto.*/
const unsigned int POS_X_VALORI_IMPOSTAZIONI = 295; /**<Posizione rispetto all'asse x dalla quale mostrare i valori dei vari campi impostazioni.*/
const unsigned int POS_Y_TITOLO_IMPOSTAZIONI = 60; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo.*/
const unsigned int POS_Y_IMPOSTAZIONI = 105; /**<Posizione rispetto all'asse y dalla quale mostrare l'elenco delle impostazioni.*/
const unsigned int POS_Y_INDICAZIONI_IMPOSTAZIONI = 310; /**<Posizione rispetto all'asse y dalla quale mostrare il premi enter.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU IMPOSTAZIONI

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DEGLI HIGHSCORES
const unsigned int POS_X_NUMERAZIONE_PUNTEGGI = 250; /**<Posizione rispetto all'asse x dalla quale mostrare il contenuto.*/
const unsigned int POS_X_NOMI_PUNTEGGI = 280; /**<Posizione rispetto all'asse x dalla quale mostrare i nomi dei punteggi.*/
const unsigned int POS_X_VALORI_PUNTEGGI = 330; /**<Posizione rispetto all'asse x dalla quale mostrare i valori dei punteggi.*/
const unsigned int POS_Y_HIGHSCORES_TITOLO = 60; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo.*/
const unsigned int POS_Y_ELENCO_PUNTEGGI = 90; /**<Posizione rispetto all'asse y dalla quale mostrare i punteggi.*/
const unsigned int POS_Y_INDICAZIONI_HIGHSCORES = 410; /**<Posizione rispetto all'asse y dalla quale mostrare il premi enter.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DEGLI HIGHSCORES

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU DI PAUSA
const unsigned int POS_Y_VOCI_PAUSA = 220; /**<Posizione rispetto all'asse y dalla quale mostrare il menu di pausa.*/
const unsigned int POS_Y_TITOLO_PAUSA = 100; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo del menù di pausa.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU DI PAUSA

//INIZIO COSTANTI GENERICHE DI GIOCO
const int RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_CARRO = 2;
const int RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_ALIENI = 1;
const unsigned int N_STATI_SPRITE = 2;
const unsigned int N_TIPI_ALIENI = 3;
//FINE COSTANTI GENERICHE DI GIOCO

//INIZIO COSTANTI PER FILE
const char FILE_FONT_TESTO [] = "Fonts/space_invaders.ttf"; /**<File contenente il font utilizzato per i testi.*/
const char FILE_FONT_TITOLO [] = "Fonts/dustbust_invaders.ttf"; /**<File contenente il font utilizzato per il titolo nel menù principale del gioco.*/
const char FILE_BARRIERA [] = "Images/barriera.png";
const char FILE_SPARO_ALIENI_1 [] = "Images/sparo_alieni_1.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x pari.*/
const char FILE_SPARO_ALIENI_2 [] = "Images/sparo_alieni_2.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x dispari.*/
const char FILE_CARRO_ARMATO [] ="Images/carro_armato.png";
const char FILE_SPARO_CARRO [] ="Images/sparo_carro.png";
const char FILE_NAVICELLA_MISTERIOSA [] ="Images/navicella_misteriosa.png";
const char FILE_ALIENO_TIPO_1 [] ="Images/alieno1.png";
const char FILE_ALIENO_TIPO_2 [] ="Images/alieno2.png";
const char FILE_ALIENO_TIPO_3 [] ="Images/alieno3.png";
const char FILE_ESPLOSIONE_CARRO [] = "Images/esplosione_carro.png";
const char FILE_ESPLOSIONE_ALIENO [] = "Images/esplosione_alieno.png";
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA
ALLEGRO_DISPLAY * inizializzaGrafica ();
void distruggiGrafica ();
void stampaMenuPrincipale (Menu menu_principale, bool redraw_lampeggio, bool partita_salvata);
void stampaGioca (Partita partita, bool animazione);
void stampaImpostazioni (Impostazioni impostazioni, Menu menu_impostazioni, bool redraw_lampeggio);
void stampaHighscores (Punteggio highscores [], int n_highscores);
void stampaMenuPausa (Menu menu_pausa, bool redraw_lampeggio);
void stampaFinePartita (SpaceInvaders generale, int posizione_punteggio_attuale, bool redraw_lampeggio);
unsigned int altezzaCarroArmato ();
unsigned int larghezzaCarroArmato ();
unsigned int altezzaNavicellaMisteriosa ();
unsigned int larghezzaNavicellaMisteriosa ();
unsigned int altezzaSparoAlienoAttuale (unsigned int pos_x_sparo);
unsigned int larghezzaSparoAlienoAttuale (unsigned int pos_x_sparo);
unsigned int altezzaSparoCarroArmato ();
unsigned int larghezzaSparoCarroArmato ();
unsigned int altezzaAlieni ();
unsigned int larghezzaAlieno1 ();
unsigned int larghezzaAlieno2 ();
unsigned int larghezzaAlieno3 ();
unsigned int larghezzaLatoUnitaBarriera ();
//FINE INTERFACCIA