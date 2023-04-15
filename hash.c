// una función que devuelve un número (el 'hash'), a partir de un string
unsigned int
hash(char *str)
{
    unsigned int hash = 5381;
    char c;

    while ( (c = *str++) != '\0')
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
