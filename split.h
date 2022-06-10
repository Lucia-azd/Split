#ifndef SPLIT_H_
#define SPLIT_H_

/**
 * Recibe un string y un separador y devuelve un vector dinámico que contenga
 * los substrings delimitados por el separador. Al final del vector debe haber
 * un string NULL para saber que es el final del mismo.
 *
 */
char** split(const char* string, char separador);

#endif // SPLIT_H_
