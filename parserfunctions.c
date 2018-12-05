#include <stdio.h>
#include <string.h>


void remove_space(char *d,
                  const char *s) { //++s preicremento; s++ postincremento
  for (; *s; ++s) {
    if (*s != ' ')
      *d++ = *s;
  }
  *d = *s;
}

void remove_comment(char str[20]) {
  char c = '/';
  int i;
  while (i < 20) {
    if (str[i] == c)
      str[i] = '\0';
    i = i + 1;
  }
}

int main(int argc, char **argv) {
  FILE *filein;
  char secuencia[20];
  filein = fopen(argv[1], "r");
  fgets(secuencia,18,filein);
  char nospace[sizeof(secuencia)];

  remove_space(nospace, secuencia);

  remove_comment(nospace);

  puts(nospace); // 123456789

  return 0;
}
