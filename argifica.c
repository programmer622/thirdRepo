#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

/*
**  "Emprestado" do servidor de news inn-1.5.1
**  Parse a string into a NULL-terminated array of words; return number
**  of words.  If argvp isn't NULL, it and what it points to will be
**  DISPOSE'd.
*/
int
Argify(line, argvp)
    char                *line;
    char                ***argvp;
{
    register char       **argv;
    register char       *p;
    register int        i;

    if (*argvp != NULL) {
        free(*argvp[0]);
        free(*argvp);
    }

    /*  Copy the line, which we will split up. */
    while (isblank(*line))
        line++;
    i = strlen(line);
    p = (char *) malloc(sizeof(char) * (i + 1));
    if (!p) {
      fprintf(stderr, "Funcao Argify: faltou memoria.\n");
      exit(1);
    }
    (void)strcpy(p, line);

    /* Allocate worst-case amount of space. */
    *argvp = argv = (char **) malloc(sizeof(char *) * (i + 2));
    if (!argv) {
      fprintf(stderr, "Funcao Argify: faltou memoria.\n");
      exit(1);
    }
    for (; *p; ) {
        /* Mark start of this word, find its end. */
        for (*argv++ = p; *p && !isblank(*p); )
            p++;
        if (*p == '\0')
            break;

        /* Nip off word, skip whitespace. */
        for (*p++ = '\0'; isblank(*p); )
            p++;
    }
    *argv = NULL;
    return argv - *argvp;
}
