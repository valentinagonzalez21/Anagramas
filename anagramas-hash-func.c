//COPIADO DE anagramas-hash.h ; segun consigna las funciones que tenemos que hacer

#define MAXWORD     32
#define HASHSIZE    10457   // un número primo lejano a una potencia de 2
#define DICT        "/usr/share/dict/spanish"
/*
 * fgetword_normalizada: lee una palabra en español de un archivo, la normaliza
 * (saca tildes y eñes y las convierte en vocales y enes)
 * retorna NULL si no hay más palabras
 */
extern char *fgetword_normalizada (FILE *fp, char *word, int maxword);  // ESTA NO HAY QUE HACERLA

/*
 * fgetword_lower_alpha_normal: similar a fgetword_normalizada pero retorna word
 * que tiene solamente minúsculas, eliminando cualquier carácter no alfabético
 */
extern char *fgetword_lower_alpha_normal(FILE *fp, char *word, int maxword); // ESTA TAMPOCO
    // invoca a fgetword_normalizada, convierte word a una palabra
    // que tiene solamente minúsculas, eliminando cualquier carácter no alfabético
    // retorna NULL si no hay más palabras

struct list {               // lista enlazada simple
    int qty;                // cantidad de elementos de la lista
    struct listnode *first, *last;  // punteros al nodo comienzo y nodo final
};

struct hashnode {           // nodo de una lista enlazada simple
    char *key;              // clave asociada a este nodo
    struct list *wlist;     // lista de palabras asociadas a esta clave
    struct hashnode *next;  // siguiente de la lista o NULL si es el último
};

struct listnode {           // nodo de una lista enlazada simple
    char *word;             // palabra asociada a este nodo
    struct listnode *next;  // siguiente de la lista o NULL si es el último
};


struct hashnode *anagrams[HASHSIZE];

extern struct list *list_create(void){
    // crea una lista vacía, retorna puntero a la misma
    struct list *lista;
    lista = malloc(sizeof (struct list));
    return lista;
};
    

extern struct list *list_insert_last_word(struct list *l, char *word){
    // inserta una palabra al final de la lista l, retorna el puntero a la lista
    // si la lista es NULL, crea una nueva
    struct listnode *nuevoNode;
    nuevoNode = malloc(sizeof (struct listnode));   // cambiar por malloc_or_exit del wrapper
    nuevoNode->word = strdup(word);
    nuevoNode->next = NULL; //no se pq no le gusta el null, no se si con 0 estaría bien igual REVISAR
    if((l->first) == NULL){ 
        struct list *lista = list_create();
        lista->first = nuevoNode;
        lista->qty = 1;
        lista->last = nuevoNode;
        return lista;
    }else{
        l->last->next = nuevoNode;//al puntero al ultimo le agrego el puntero al siguiente
        l->last = nuevoNode;//cambio mi puntero al último a mi nuevo nodo que agregué
        (l->qty)++;//aumento la cantidad de la lista
        return l;
    }
};

extern struct hashnode *hash_insert_word(struct hashnode *node, char *key, char *word);
    // busca key en el hash (y si no encuentra inserta key al inicio en lista simple)
    // luego agrega palabra al final de la lista de anagramas asociadas a la key
    // retorna siempre el primero de la lista: node si key estaba o el nuevo nodo si se insertó

/*
    if(node == NULL){           // para esa posicion en el hash todavia no hay nada
                                // segun def de hash(), el numero es unico, asi que solo tengo que buscar 
                                // en el hashnode que me pasan (en main pasan anagrams[h])
        node->key = strdup(key);
        node->wlist = list_insert_last_word(, word);
        // ?? node->next

    
    } else {
        if(node->             
    }
*/


extern unsigned int hash(char *str);        // ESTA TAMPOCO; ESTA EN hash.c
    // genera un número único (grande) asociado al string

// ordena EN EL LUGAR la palabra 'word' según código ASCII en forma ascendente
extern char *sort_word(char *word) {
    // BUBBLESORT
    length = strlen(word);
    for(int i = 0; i < (length - 1); i++){        // hago una comparacion menos que el largo, porque el ultimo elemento no tengo con quien comparar
         for (j = 0; j < length - i - 1; j++) {    // el - 1 es porque no puede el elemento compararse con si mismo 
            if (strcmp(*word, *(word + 1)) > 0) {        // strcmp compara en ASCII - si el caracter es mayor al siguiente, cambio
                int temp = *word;
                *word = *(word + 1);
                *(word + 1) = temp;
            }
         }
    }

    return word;
}
    
// escribe (printf) la lista de anagramas para ese hashnode
// TODO: probar
extern void print_anagrams(struct hashnode *hn){
    int quantity = hn->wlist->qty;
    if(quantity == 0){
        printf("No hay anagramas.");
        return;
    }

    printf("Anagramas: ")
    struct listnode *list_pointer = hn->wlist->first;

    for(int = 0; i < quantity; i++){
        printf("%s, ", list_pointer->word);
        list_pointer = list_pointer->next;
    }
}

