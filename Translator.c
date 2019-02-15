#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "command.h"

/*
-> Cose da fare:
  ~> implementazione stack
  ~> MAIN.c:
    => fileIn and fileOut (PAOLO)
    => ciclo fgets
    => remove comments and remove spaces
  ~> STACK.c:
    => push
-> Problemi
*/

command *parser(char *c){
  char nospace[200];

  remove_space(nospace, c);                               //rimuove gli spazi
  remove_comment(nospace);                                //rimuove i commenti
  command *current_parse = malloc(sizeof(command));       //istanzio uno spazio pari a 'command'
  command *trash = malloc(sizeof(command));               //istanzio una nuova variabile in caso sia un comando inutile
}

int main(int argc, char **argv){
  FILE *filein, *fileout;
  
  filein = fopen(argv[1], "r");     //assegnazione del file di input
  fileout = fopen(argv[2], "w");    //assegnazione del file di output
  
  command *current;
  char instr[200]={'\0'};           //riga in questione
  char clean[200];

  while(fgets(instr, sizeof(instr), filein)!=NULL){         //while ci sono righe di grandezza massima 'instr' nel file 'filein'. Se ci sono assegnarle alla variabile (instr).
    current = parser(instr);

  return 0;
}
