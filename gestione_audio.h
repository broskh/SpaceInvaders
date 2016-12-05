/*
 * Header file contenente l'interfaccia del modulo per la gestione dell'audio.
 */

//INIZIO COSTANTI PER VELOCITA' AUDIO
const float VELOCITA_SOTTOFONDO_ONDATA_MIN = 0.8; /**<Velocità minima utilizzata per la musica di sottofondo all'ondata aliena in movimento.*/
const float VELOCITA_SOTTOFONDO_ONDATA_MAX = 1.55; /**<Velocità massima utilizzata per la musica di sottofondo all'ondata aliena in movimento.*/
//FINE COSTANTI PER VELOCITA AUDIO

//INIZIO COSTANTI PER FILE
const char FILE_MUSICA_PRINCIPALE [] = "Sounds/principale.wav"; /**<Percorso del file contenente la musica principale.*/
const char FILE_MUSICA_SOTTOFONDO_ONDATA [] = "Sounds/sottofondo_ondata.wav"; /**<Percorso del file contenente la musica di sottofondo all'ondata aliena in movimento.*/
const char FILE_SUONO_ESPLOSIONE_CARRO_ARMATO [] = "Sounds/esplosione_carro_armato.wav"; /**<Percorso del file contenente il suono dell'esplosione del carro armato.*/
const char FILE_SUONO_ESPLOSIONE_ALIENO [] = "Sounds/esplosione_alieno.wav"; /**<Percorso del file contenente il suono dell'esplosione di un alieno.*/
const char FILE_SUONO_ESPLOSIONE_NAVICELLA_MISTERIOSA [] = "Sounds/esplosione_navicella_misteriosa.wav"; /**<Percorso del file contenente il suono dell'esplosione della navicella misteriosa.*/
const char FILE_SUONO_SPARO_CARRO_ARMATO [] = "Sounds/sparo_carro_armato.wav"; /**<Percorso del file contenente il suono dello sparo del carro armato.*/
const char FILE_SUONO_NAVICELLA_MISTERIOSA [] = "Sounds/navicella_misteriosa.wav"; /**<Percorso del file contenente il suono della navicella misteriosa in movimento.*/
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA
/**
 * Avvia la musica di sottofondo all'ondata di alieni in movimento.
 */
void avviaMusicaOndata ();

/**
 * Avvia la musica principale.
 */
void avviaMusicaPrincipale ();

/**
 * Esegue il suono dell'esplosione di un alieno.
 */
void avviaSuonoEsplosioneAlieno ();

/**
 * Esegue il suono dell'esplosione del carro armato.
 */
void avviaSuonoEsplosioneCarroArmato ();

/**
 * Esegue il suono dell'esplosione della navicella misteriosa.
 */
void avviaSuonoEsplosioneNavicellaMisteriosa ();

/**
 * Avvia il suono della navicella misteriosa in movimento.
 */
void avviaSuonoNavicellaMisteriosa ();

/**
 * Esegue il suono dello sparo del carro armato.
 */
void avviaSuonoSparoCarroArmato ();

/**
 * Procedura di distruzione del modulo per la gestione dell'audio.
 * 
 * Si occupa di deallocare correttamente la memoria alloccata in fase di inizializzazione del modulo.
 */
void distruggiAudio ();

/**
 * Ferma la musica di sottofondo all'ondata di alieni in movimento.
 */
void fermaMusicaOndata ();

/**
 * Ferma la musica principale.
 */
void fermaMusicaPrincipale ();

/**
 * Ferma il suono della navicella misteriosa in movimento.
 */
void fermaSuonoNavicellaMisteriosa ();

/**
 * Procedura di inizializzazione del modulo per la gestione dell'audio.
 * 
 * Si occupa di inizializzare correttamente tutte le variabili necessarie e di seguire i metodi di inizializzazione di determinate librerie "Allegro".
 */
void inizializzaAudio ();

/**
 * Modifica la velocità della musica di sottofondo all'ondata di alieni in movimento.
 *
 * La modifica viene effettuata sulla base della {@link VELOCITA_SOTTOFONDO_ONDATA_MIN velocità minima}
 * e della {@link VELOCITA_SOTTOFONDO_ONDATA_MAX velocità massima} indicate.
 *
 * @param percentuale_velocita_ondata Percentuale della velocità che si vuole impostare.
 */
void modificaVelocitaMusicaOndata (unsigned int percentuale_velocita_ondata);
//FINE INTERFACCIA