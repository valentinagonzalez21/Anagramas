#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wrappers.h"
#include "anagramas-hash.h"

int
main(int argc, char *argv[])
{
    FILE *fp;
    char word[MAXWORD], key[MAXWORD];
    unsigned int h;
    struct hashnode *anagrams[HASHSIZE] = { NULL };
    struct hashnode *hn;
    struct listnode *p;

    if (argc == 1) {
        fprintf(stderr, "Uso:\n  %s -a|--all\n  %s palabra [palabra ...]\n",
                        argv[0],  argv[0]);
        exit(1);
    }

    fp = fopen_or_exit(DICT, "r");

    while (fgetword_normalizada (fp, word, MAXWORD) != NULL) {
        strcpy(key, word);
        sort_word(key);
        h = hash(key) % HASHSIZE;
        anagrams[h] = hash_insert_word(anagrams[h], key, word);
        /* DEBUG
        if (strcmp(word, "padre") == 0 || h == 1977 ) {
            printf("se insertó %s con clave %s en hash %u\n", word, key, h);
            for (hn=anagrams[h]; hn != NULL; hn = hn->next) {
                printf("key=%s, hn->key=%s\n", key, hn->key);
            }
        }
        */
    }

    if (argc > 1 && (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--all") == 0) ) {
        // -a o --all
        for (int i=0; i<HASHSIZE; i++) {
            print_anagrams(anagrams[i]);
            /*
            // recorre array de hash
            for (hn=anagrams[i]; hn != NULL; hn = hn->next) {
                // recorre colisiones (claves con el mismo hash)
                if (hn->wlist->qty > 1) {
                    // si una clave tiene varias palabras en la lista
                    printf("Clave %s, %d palabras: ", hn->key, hn->wlist->qty);
                    for (p = hn->wlist->first; p != NULL; p = p->next) {
                        printf("%s%c", p->word, p->next != NULL ? ',' : '\n');
                    }
                }
            }
            */
        }
    } else {    // no es opción -a/--all sino una lista de palabras
        while (--argc > 0) {
            strcpy(key, *++argv);
            sort_word(key);
            h = hash(key) % HASHSIZE;
            /* DEBUG
            if (strcmp(*argv, "padre") == 0 || h == 1977 ) printf("se buscó %s con clave %s en hash %u\n", *argv, key, h);
            */
            for (hn=anagrams[h]; hn != NULL && strcmp(key, hn->key) != 0; hn = hn->next) {
            /* DEBUG
            for (hn=anagrams[h]; hn != NULL; hn = hn->next) { // DEBUG
                printf("key=%s, hn->key=%s\n", key, hn->key);
            */
                ;   // recorre las claves que tienen el mismo hash
            }
            if (hn == NULL) {                   // Clave no encontrada
                printf("Palabra %s no existe en diccionario.\n", *argv);
            } else {                            // Clave encontrada
                for (p=hn->wlist->first; p!=NULL && strcmp(*argv, p->word) != 0; p=p->next) {
                    ;                           // busco si la palabra buscada está en la lista
                }
                if (p != NULL) {                // la palabra estaba
                    if (hn->wlist->qty > 1) {   // y hay anagramas !
                        printf("Clave %s, %d palabras: ", hn->key, hn->wlist->qty);
                        for (p = hn->wlist->first; p != NULL; p = p->next) {
                            printf("%s%c", p->word, p->next != NULL ? ',' : '\n');
                        }
                    } else {                    // No hay anagramas para esa palabra
                        printf("Palabra %s no tiene anagramas.\n", *argv);
                    }
                } else {                        // la palabra no estaba
                    printf("Palabra %s no existe en diccionario.\n", *argv);
                }
            }
        }
    }

    exit(0);
}
