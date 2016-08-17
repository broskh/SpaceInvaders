/*Inizio strutture dati*/

const unsigned int N_BARRIERE = 3;	//numero delle barriere presenti a partita
const unsigned int LARG_BARRIERA = ;	//inserire largezza singola barriera	//largezza della barriera
const unsigned int ALT_BARRIERA = ;	//inserire altezza singola barriera	//altezza della barriera

/* Tipo grafica per impostazioni.
 *
 * Sono presenti diverse modalità grafiche: "mono_bianco", "mono_giallo" e "mono_verde"
 * se si tratta di una grafica monocroma del colore indicato; "fasce_vert" e "fasce_oriz"
 * se i mostri sono colorati attraverso fasce adiacenti di colori differenti; e infine "misto"
 * se vogliamo che i mostri siano di colori differenti, e mai uguali per due mostri adiacenti.
 */
enum grafica {mono_bianco, mono_giallo, mono_verde, fasce_vert, fasce_oriz, misto};	//aggiungere altre mono?

/* Tipo stato per ogni quadrato che costituisce la barriera.
 *
 * Ogni quadratino costituente la barriera all'interno del gioco inizialmente sarà rappresentato
 * dallo stato "intero". La prima volta che verrà colpito esso si sgretolerà parzialmente e sarà
 * rappresentato dallo stato "parziale". Infine, quando verrà colpito per la seconda volta, il
 * suo stato diventerà "distrutto", e graficamente non sarà più visibile.
 */
enum stato {distrutto, parziale, intero};

/* Tipo stato per indicare la direzione dello zig-zag dei mostri.
 *
 * I mostri eseguono continuamentente un movimento a zig zag. Con questo tipo è possibile indicare
 * la direzione che stanno tenendo in un determinato momento.
 */
enum direzione {destra, sinistra};

/*
 * Struttura generale del gioco.
 *
 * Contiene le informazioni di tipo generali che devono essere presenti ogni volta che viene
 * avviato il gioco. Conserva le informazioni relative alle impostazioni, alla partita attuale
 * (se avviata) e il punteggio massimo raggiunto in ogni partita.
 */
struct spaceInvaders
{
	impostazioni impost_att;	/*Impostazioni attuali*/
	partita partita_att;	/*Partita attuale*/
	unsigned int max_score;	/*Punteggio massimo*/
};

/*
 * Struttura di una singola partita.
 *
 * Ogni volta che viene avviata una nuova partita questa struttura ne contiene le informazioni.
 * Conserva il punteggio che si sta accumulando, il numero di vite rimanenti, lo stato delle barriere
 * e le informazioni relative all'ondata di mostri che si sta combattendo.
 */
struct partita
{
	int punteggio;	/*Punteggio*/
	unsigned int vite_rimanenti;	/*Vite rimanenti*/
	stato barriere [AKT_BARRIERA] [LARG_BARRIERA] [N_BARRIERE];	/*Stato attuale delle barriere*/
	ondata ondata_att;	/*Ondata di mostri attuale*/
};

/*
 * Struttura di una singola ondata.
 *
 * Ogni volta che si affronta una nuova ondata questa struttura ne conserva le varie informazioni: il numero
 * di mostri non ancora abbattuti, l'indicazione di quali mostri sono vivi e quali no, e la direzione che si
 * sta seguendo nel continuo zig-zag dell'ondata
 */
struct ondata
{
	bool mostri [] [];	/*Stato mostri*/
	int mostri_rimasti;	/*Numero di mostri rimasti*/
	direzione dir_mostri;	/*Direzione dello zig-zag*/
};

/*
 * Struttura delle impostazioni.
 *
 * Conserva tutte le informazioni derivanti dal settaggio delle impostazioni. Da questa struttra quindi
 * è possibile sapere se la musica e gli effetti audio sono abilitati o meno, la modalità grafica scelta e
 * il numero delle vite iniziali.
 */
struct impostazioni
{
	bool musica;
	bool eff_audio;
	grafica mod_grafica;
	unsigned int vite_iniziali;
};