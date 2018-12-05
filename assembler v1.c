#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_command {
  char command_type;
  char symbol[20];
  char dest[20];
  char comp[20];
  char jump[20];
} command;

void remove_space(char *d, const char *s) {
  for (; *s; ++s) {
    if (*s != ' ')
      *d++ = *s;
  }

  *d = *s;
}

void remove_comment(char str[20]) {
  char c = '/';
  int i=0;
  while (i < 20) {
    if (str[i] == c)
      str[i] = '\0';
    i = i + 1;
  }
}

command *parser(char *str) {
  char nospace[19];
  remove_space(nospace, str);
  //puts(nospace);
  nospace[18] = '\n';
  remove_comment(nospace);
  puts(nospace);
  command *current_parse = malloc(sizeof(command));
  current_parse->command_type = 'a';
  strcpy(current_parse->symbol, nospace);
  return current_parse;
}

int main(int argc, char **argv) {
  FILE *filein;
  command *current;
  char instr[20]={'\0'};
  filein = fopen(argv[1], "r");
  fgets(instr, 18, filein);
  //instr[19]='\0';
  current = parser(instr);
  //puts(current->command_type);
 // puts(current->symbol);
  return 0;
}