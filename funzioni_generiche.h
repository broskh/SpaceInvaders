/*
 * File header del modulo per l'utilizzo di funzioni generiche.
 */

//INIZIO INTERFACCIA

/*
 * Stabilisce qual'è il valore precedente a quello passato come parametro facendo passi indietro pari al peso e
 * ponendo attenzione a non andare al di sotto del valore minimo.
 *
 * @param n Valore da analizzare.
 * @param peso Peso di ogni passo indietro nel range.
 * @param min Valore minimo.
 *
 * @return il valore precedente.
 */
int precInRange (int n, int peso, int min);

/*
 * Stabilisce qual'è il valore precedente a quello passato come parametro ponendo attenzione a non andare al di sotto
 * del valore minimo.
 *
 * @param n Valore da analizzare.
 * @param min Valore minimo.
 *
 * @return il valore precedente.
 */
int precInRange (int n, int min);

/*
 * Stabilisce qual'è il valore successivo a quello passato come parametro facendo passi avanti pari al peso e
 * ponendo attenzione a non andare al di sopra del valore massimo.
 *
 * @param n Valore da analizzare.
 * @param peso Peso di ogni passo avanti nel range.
 * @param max Valore massimo.
 *
 * @return il valore successivo.
 */
int sucInRange (int n, int peso, int max);

/*
 * Stabilisce qual'è il valore successivo a quello passato come parametro ponendo attenzione a non andare al di sopra
 * del valore massimo.
 *
 * @param n Valore da analizzare.
 * @param max Valore massimo.
 *
 * @return il valore successivo.
 */
int sucInRange (int n, int max);

/*
 * Stabilisce qual'è il valore precedente a quello passato come parametro supponendo che prima del valore minimo
 * ci sia il valore massimo. Si tratta quindi del valore precedente in un circuito che va dal valore minimo al valore massimo.
 *
 * @param n Valore da analizzare.
 * @param min Valore minimo.
 * @param max Valore massimo.
 *
 * @return il valore precedente del circuito.
 */
int precInRangeCircuito (int n, int min, int max);

/*
 * Stabilisce qual'è il valore successivo a quello passato come parametro supponendo che dopo al valore massimo
 * ci sia il valore minimo. Si tratta quindi del valore successivo in un circuito che va dal valore minimo al valore massimo.
 *
 * @param n Valore da analizzare.
 * @param min Valore minimo.
 * @param max Valore massimo.
 *
 * @return il valore successivo del circuito.
 */
int sucInRangeCircuito (int n, int min, int max);
//FINE INTERFACCIA