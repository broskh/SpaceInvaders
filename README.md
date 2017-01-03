# Space Invaders
## Introduzione
Riproduzione del celebre videogioco *Space Invaders* che mantiene inalterate tutte le caratteristiche di base del gioco originale.

Il giocatore quindi dovrà controllare un carro armato con il quale avrà il compito di abbattere, finchè avrà vite a disposizione, le ondate di alieni che ripetutamente si avvicineranno.

## Descrizione del gioco
### Menù principale
Il gioco è dotato di un menù principale, dal quale è possibile accedere alle varie schermate.

![Space Invaders - Menù principale](http://imgur.com/ohHFaJy.png)
> Per muoversi fra le voci di menù è necessario utilizzare *freccia su* e *freccia giù*, mentre per accedere all'area selezionata è sufficiente premere *enter*.

###Gioca
Si tratta della schermata dalla quale è possibile dilettarsi col gioco vero e proprio.

Il giocatore, ad inizio partita, ha a disposizione tre barriere. Ogni qualvolta esse vengono colpite dagli alieni o dal carro armato, tenderanno prima a sgretolarsi, e infine a distruggersi.

Man mano che gli alieni vengono colpiti, a seconda del tipo di alieno distrutto, il giocatore ha un incremento del proprio punteggio. Nel momento in cui un'intera ondata viene distrutta, ne ricompare subito un'altra.

Inoltre, ad intervalli di tempo casuali compare una navicella misteriosa. Se essa viene colpita il giocatore viene premiato con un incremento rilevante e casuale del punteggio.

![Space Invaders - Gioca](http://imgur.com/2EChJ08.png)
> È necessario utilizzare *freccia destra* e *freccia sinistra* per muovere il carro armato, mentre con *barra spaziatrice* è possibile sparare.
> Durante una partita è possibile mettere il gioco in pausa premendo *esc*.

###Menù di pausa
Da questo menù il giocatore può continuare, abbandonare o salvare la partita.
Se viene scelto di salvare la partita il giocatore viene riportato al menù principale e la voce che consente di caricare la partita sarà abilitata. Tramite quella voce di menù potrà appunto ricominciare la partita dall'esatto punto nel quale era stata precedentemente interrotta.

![Space Invaders - Menù di pausa](http://imgur.com/o1t5O36.png)
> Per muoversi fra le voci è necessario utilizzare *freccia su* e *freccia giù*, mentre per scegliere un'operazione è sufficiente premere *enter*.

###Fine partita
Al termine della partita, se è stato ottenuto un punteggio degno di essere inserito nella classifica degli highscores, è possibile digitare un nome di massimo tre lettere e salvarlo.

![Space Invaders - Fine partita](http://imgur.com/pXCDXam.png)
> Premendo *enter* viene salvato il punteggio e si torna al menù principale.

###Opzioni
Attraverso le impostazioni è possibile abilitare o meno la musica e gli effetti audio. Inoltre è possibile modificare la grafica cromatica degli alieni e impostare il numero di vite con le quali si intende iniziare le partite.

![Space Invaders - Menù delle impostazioni](http://imgur.com/HPXLMAP.png)
> Usando *freccia su* e *freccia giù* è possibile muoversi fra i vari campi delle impostazioni. Con *freccia destra* e *freccia sinistra* è possibile modificare il valore selezionato. Con *r* vengono ripristinati i valori di default. Premendo *enter* le modifiche vengono salvate e si torna al menù principale.

###Highscores
Dal menù principale è inoltre possibile visualizzare la classifica dei dieci migliori punteggi raggiunti e il nome dei giocatori che hanno raggiunto tali risultati.

![Space Invaders - Highscores](http://imgur.com/Rv0TCdn.png)
> Premendo *enter* si torna al menù principale.

##Requisiti
Un requisito fondamentale per la compilazione del codice è la libreria grafica *allegro*.
Per informazioni riguardanti l'installazione di questa libreria è sufficiente seguire le istruzioni riportate [qui](https://wiki.allegro.cc/index.php?title=Getting_Started).

##Come installarlo
Per poter installare il gioco su distruibuzioni basate su debian è sufficiente seguire questi semplici passi:
- Scaricare da github l'archivio .zip.
- Estrarre il contenuto dell'archivio appena scaricato.
- Entrare con un terminale all'interno della directory.
- Digitare sul terminale `cd src`.
- Digitare sul terminale `make depend`.
- Digitare sul terminale `make`. In questo modo avremo compilato e generato l'eseguibile *SpaceInvaders*.

Infine per giocare, sempre dall'interno della cartella, è sufficiente digitare da console `./SpaceInvaders`.

> Testato su *Ubuntu 16.04.1 64bit*.

##Altre opzioni di make
È possibile utilizzare make con altre opzioni per ottenere risultati differenti:
- `make clean` per eliminare tutti i file generati in fase di compilazione.
- `make cleanAll` per eliminare tutti i file generati in fase di compilazione e i vari file di salvataggio e configurazione.
- `make debug` per compilare il codice in modalità debug (viene abilitato anche un tracing a console).
- `make debugExtended` per compilare il codice in modalità debug (viene abilitato anche un tracing esteso a console).
- `make depend` per generare il file *dependencies* che contiene le dipendenze (non presenti nelle directory di default del sistema) dei file da compilare.
- `make noAsserts` per compilare il codice disabilitando le asserts.

##Documentazione
La documentazione in formato HTML è presente all'interno della cartella *doc/html/*. Aprendo il file *index.html* è possibile navigarla liberamente tramite qualsiasi browser.

> Documentazione generata automaticamente con Doxygen.

##Referenze
- La musica e gli effetti audio provengono da: (http://www.classicgaming.cc/classics/space-invaders/sounds) e (http://downloads.khinsider.com/game-soundtracks/album/space-invaders-gbc-gb-).
- Il font utilizzato per il titolo nel menù principale proviene da: (http://www.fontspace.com/dustbust/invaders).
- Il font utilizzato per tutto il testo del gioco proviene da: (http://it.fonts2u.com/space-invaders-regular.carattere).
- Per scaricare l'eseguibile pre-compilato per sistemi Windows cliccare [qui](https://drive.google.com/drive/folders/0ByFVa3igbMKoaF9xdnh0cTBrdU0?usp=sharing).