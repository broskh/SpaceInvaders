/*
 * Header file contenente l'interfaccia del modulo di gestione degli highscores.
 */

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <fstream>
#include <iostream>

using namespace std;

//INIZIO COSTANTI PER ALIENI
const unsigned int PUNTEGGIO_ALIENO_3 = 10; /**<Punteggio attribuito al alieno 3.*/
const unsigned int PUNTEGGIO_ALIENO_2 = 20; /**<Punteggio attribuito al alieno 2.*/
const unsigned int PUNTEGGIO_ALIENO_1 = 30; /**<Punteggio attribuito al alieno 1.*/
const unsigned int PUNTEGGIO_NAVICELLA_MAX = 500; /**<Punteggio massimo attribuito alla navicella.*/
const unsigned int PUNTEGGIO_NAVICELLA_MIN = 100; /**<Punteggio minimo attribuito alla navicella.*/
//FINE COSTANTI PER ALIENI

//INIZIO COSTANTI E COSTANTI DI GIOCO
const unsigned int PROBABILITA_COMPARSA_NAVICELLA = 15; /**<Probabilità percentuale di comparsa della navicella misteriosa.*/
const unsigned int DIMENSIONE_LATO_UNITA_BARRIERA = 4; /**<Lunghezza in pixel di ogni unità costituente le barriere.*/
const unsigned int LARGHEZZA_PIXEL_BARRIERA = DIMENSIONE_LATO_UNITA_BARRIERA * LARG_BARRIERA; /**<Larghezza in pixel di una singola barriera.*/
const unsigned int PESO_SPOSTAMENTO_CARRO_ARMATO = 6; /**<Peso dello spostamento laterale del carro armato.*/
const unsigned int MAX_SPOSTAMENTO_ONDATA = 4; /**<Peso massimo dello spostamento laterale dell'ondata aliena.*/
const unsigned int RIP_ANIMAZIONE_ESPLOSIONE_CARRO = 2; /**<Numero di ripetizioni dell'animazione di esplosione del carro.*/
//FINE COSTANTI E COSTANTI DI GIOCO

//INIZIO COSTANTI PER FILE
const char FILE_SALVATAGGIO_PARTITA [] = "partita.sav"; /**<Percorso del file contenente la partita salvata.*/
//FINE COSTANTI PER FILE


//INIZIO COSTANTI GENERALI PER DISPLAY
extern const unsigned int ALTEZZA_DISPLAY; /**<Altezza della finestra del gioco.*/
extern const unsigned int LARGHEZZA_DISPLAY; /**<Larghezza della finestra del gioco.*/

extern const unsigned int MARGINE_SUP_GIOCO; /**<Margine superiore del gioco.*/
extern const unsigned int MARGINE_INF_GIOCO; /**<Margine inferiore del gioco.*/
extern const unsigned int MARGINE_SX_GIOCO; /**<Margine sinistro del gioco.*/
extern const unsigned int MARGINE_DX_GIOCO; /**<Margine destro del gioco.*/
extern const unsigned int POS_CENTRO_X; /**<Posizione centrale della del display rispetto all'asse delle x.*/
//FINE COSTANTI GENERALI PER DISPLAY

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DI GIOCO
extern const unsigned int POS_X_PRIMA_BARRIERA; /**<Posizione rispetto all'asse x della prima barriera.*/
extern const unsigned int POS_Y_BARRIERE; /**<Posizone rispetto all'asse y dalla quale mostrare la prima barriera.*/
extern const unsigned int DISTANZA_BARRIERE; /**<Distanza in pixel fra le barriere.*/

extern const unsigned int POS_X_PRIMO_ASSE_ALIENI; /**<Posizone rispetto all'asse x nella quale è presente il primo asse delle colonne di alieni.*/
extern const unsigned int POS_Y_PRIMA_FILA_ONDATA; /**<Posizione rispetto all'asse y dalla quale mostrare la prima fila di alieni.*/
extern const unsigned int DISTANZA_FILE_ALIENI; /**<Distamza fra le file di alieni.*/
extern const unsigned int DISTANZA_ASSI_COL_ALIENI; /**<Distanza fra gli assi delle colonne di alieni.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DI GIOCO

//INIZIO INTERFACCIA
void creaSparoCarroArmato (Carro &carro, const unsigned int larghezza_pixel_carro, unsigned int pos_y);

void stampa (Partita partita);

bool controlloCollisioneBarriereDaOndata (Partita &partita, unsigned int altezza_alieni, unsigned int larghezza_alieno_1, unsigned int larghezza_alieno_2, unsigned int larghezza_alieno_3);

bool controlloCollisioneNavicellaMisteriosa (Partita &partita, unsigned int altezza_navicella, unsigned int larghezza_navicella, unsigned int larghezza_sparo);

void creaNavicellaMisteriosa (Partita &partita);

void muoviNavicellaMisteriosa (Partita &partita, unsigned int larghezza_navicella);

bool controlloCollisioneCarroDaSparoAlieni (Partita &partita, unsigned int larghezza_carro, unsigned int altezza_sparo_alieni, unsigned int larghezza_sparo, unsigned int pos_y_carro);

bool controlloCollisioneBarriereDaSparoAlieni (Partita &partita, unsigned int altezza_sparo_alieni, unsigned int larghezza_sparo);

bool controlloCollisioneBarriereDaSparoCarro (Partita &partita, unsigned int larghezza_sparo);

ALLEGRO_BITMAP * sparoScelto (int pos_x, ALLEGRO_BITMAP * sparo_alieni_1, ALLEGRO_BITMAP * sparo_alieni_2);

void creaSparoAlieni (Partita &partita, unsigned int altezza_alieni, unsigned int larghezza_alieno_1, unsigned int larghezza_alieno_2, unsigned int larghezza_alieno_3);

bool controlloCollisioneCarroDaOndata (Partita &partita, unsigned int altezza_alieni, unsigned int pos_y_carro);

bool controlloCollisioneAlieni (Partita &partita, unsigned int altezza_alieni, unsigned int larghezza_alieno_1, unsigned int larghezza_alieno_2, unsigned int larghezza_alieno_3, unsigned int larghezza_sparo);

void muoviSparoAlieni (Sparo &sparo, unsigned int altezza_sparo_alieni);

void muoviAlieni(Ondata &ondata, unsigned int larghezza_colonna, unsigned int pos_y_carro);

/**
 * Stabilisce qual'è la posizione rispetto all'asse y dello sparo del carro armato in movimento.
 * 
 * @param sapro Sparo del carro armato.
 * @param limite_sup Limite superiore dello sparo del carro armato.
 */
void muoviSparoCarro (Sparo &sparo);

/**
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso destra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 */
void muoviDestraCarro (unsigned int &pos_x_carro, const unsigned int larghezza_carro);

/**
 * Stabilisce qual'è il valore di offset del carro armato che deve andare verso sinistra.
 *
 * @param offset_carro Precedente valore dell'offset del carro armato.
 */
void muoviSinistraCarro (unsigned int &pos_x_carro);

/**
 * Indica se esiste o meno una partita precedentemente salvata.
 * 
 * @param file Percorso del file dove verificare la presenza del salvataggio.
 * 
 * @return "true" se esiste una partita precedentemente salvata, "false" altrimenti.
 */
bool esisteSalvataggio ();

/**
 * Memorizza in una struttura {@link Ondata} i valori necessari per la realizzazione di una nuova ondata.
 *
 * @param ondata Struttura {@link Ondata} nella quale verranno memorizzati i valori.
 */
void nuovaOndata (Ondata &ondata);

/**
 * Memorizza in una struttura {@link Partita} i valori necessari per iniziare una nuova partita.
 *
 * @param partita Struttura {@link Partita} nella quale verranno memorizzati i valori.
 * @param impostazioni Struttura {@link Impostazioni} dal quale verranno prelevate alcune informazioni necessari per la corretta inizializzazione di una nuova partita.
 * @param pos_x_carro_armato Posizione iniziale rispetto all'asse x del carro armato.
 */
void nuovaPartita (Partita &partita, Impostazioni impostazioni, const unsigned int pos_x_carro_armato);

/**
 * Carica da un file una partita lasciata in sospeso.
 * 
 * @param salvataggio Struttura {@link partita} contenente i dati della partita caricata.
 * @param file File dal quale caricare la partita.
 * 
 * @return "false" nel caso in cui il caricamento non sia riuscito, "true" altrimenti.
 */
bool caricaPartita (Partita &salvataggio);

/**
 * Salva una partita da sospendere su un file.
 *
 * @param spaceInvaders struttura {@link SpaceInvaders} contenente tutte le informazioni relative al gioco in esecuzione.
 * @param file File nel quale salvare la partita.
 */
void salvaPartita (SpaceInvaders &spaceInvaders);

/**
 * Elimina un file di salvataggio nel caso in cui esista.
 *
 * @param file File di salvataggio da eliminare.
 * @param spaceInvaders Struttura {@link SpaceInvaders} contenente tutte le informazioni relative al gioco in esecuzione.
 * 
 * @return "true" se il file era presente ed è stato eliminato, "false" altrimenti.
 */
bool eliminaFileSalvataggio (SpaceInvaders &spaceInvaders);
//FINE INTERFACCIA