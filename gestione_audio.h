/*
 * Header file contenente l'interfaccia del modulo di gestione dell'audio.
 */

//INIZIO COSTANTI PER VELOCITA' AUDIO
const float VELOCITA_SOTTOFONDO_ONDATA_MIN = 0.9;
const float VELOCITA_SOTTOFONDO_ONDATA_MAX = 1.55;
//FINE COSTANTI PER VELOCITA AUDIO

//INIZIO COSTANTI PER FILE
const char FILE_MUSICA_PRINCIPALE [] = "Sounds/principale.wav"; /**<Percorso del file contenente la musica principale.*/
const char FILE_MUSICA_SOTTOFONDO_ONDATA [] = "Sounds/sottofondo_ondata.wav";
const char FILE_SUONO_ESPLOSIONE_CARRO_ARMATO [] = "Sounds/esplosione_carro_armato.wav";
const char FILE_SUONO_ESPLOSIONE_ALIENO [] = "Sounds/esplosione_alieno.wav";
const char FILE_SUONO_ESPLOSIONE_NAVICELLA_MISTERIOSA [] = "Sounds/esplosione_navicella_misteriosa.wav";
const char FILE_SUONO_SPARO_CARRO_ARMATO [] = "Sounds/sparo_carro_armato.wav";
const char FILE_SUONO_NAVICELLA_MISTERIOSA [] = "Sounds/navicella_misteriosa.wav";
//FINE COSTANTI PER FILE

//INIZIO INTERFACCIA

void inizializzaAudio ();

void distruggiAudio ();

void avviaMusicaPrincipale ();

void fermaMusicaPrincipale ();

void avviaMusicaOndata ();

void fermaMusicaOndata ();

void avviaSuonoNavicellaMisteriosa ();

void fermaSuonoNavicellaMisteriosa ();

void avviaSuonoSparoCarroArmato ();

void avviaSuonoEsplosioneCarroArmato ();

void avviaSuonoEsplosioneAlieno ();

void avviaSuonoEsplosioneNavicellaMisteriosa ();

void modificaVelocitaMusicaOndata (unsigned int percentuale_velocita_ondata);
//FINE INTERFACCIA