#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
// #include "command.h"


/*
PROBLEMS: Never tested filler
Expected solution: prova a vedere se va e fa quel che dovrebbe. mi pare dovrebbe andare

-> Cose da fare:
  ~> implementazione stack
  ~> MAIN.c:
    => fileIn and fileOut (PAOLO)
    => ciclo fgets
    => remove comments and remove spaces
  ~> STACK.c:
    => push
*/

typedef struct command{
  char instr[200];
  char type[200];
  int number;
} command;

//REMOVE COMMENTS
//rimuove i commenti
void remove_comment(char str[200]) {
  char c = '/';
  int i=0;
  while (i < 20) {
    if (str[i] == c)
      str[i] = '\0';
    i = i + 1;
  }
}

void filler(char* nospace, command* current_parse){   //written like this so that "  push '\t'   constant '\t''\t' 9   " creates no problem
  int i = 0, j = 0;
  char numero[20]={'\0'};                                 //={'\0'} this should make lines 60-61 useless but not sure
  int instr = 0, type = 0, num = 0;


  current_parse->instr[0] = '\0';                           //initialize correctly to avoid problems
  current_parse->type[0] = '\0';
  current_parse->number = -1;                               //I hope I'm allowed to do this
  printf("%s", "ciaooo sono prima dei loop");
  while((nospace[i]==' ' || nospace[i] == '\t') && nospace[i]!='\0'){
   // printf("%s", "ciaooo sono nel loop che cerca il primo buco");
  i++;  //move forward until end of space and tab
  }
  while((nospace[i]!=' ' && nospace[i] != '\t') && nospace[i]!='\0') {    //copy until tab is found
    current_parse->instr[j] = nospace[i];                                 //placing it inside of struct as instr
    j++;
    i++;
    instr = 1;                                                            //acts as boolean value in case in case I forgot something
  //  printf("%s", "ciaooo sono nel loop instr");
  }
  j = 0;

  while((nospace[i]==' ' || nospace[i] == '\t') && nospace[i]!='\0') i++; //move forward until end of space and tab
  while((nospace[i]!=' ' && nospace[i] != '\t') && nospace[i]!='\0') {
    current_parse->type[j] = nospace[i];                                  //placing it inside of struct as type
    j++;
    i++;
    type = 1;                                                             //acts as boolean value in case in case I forgot something
 // printf("%s", "ciaooo sono nel loop type");
  }
  j = 0;

  while((nospace[i]==' ' || nospace[i] == '\t') && nospace[i]!='\0') i++; //move forward until end of space and tab
  while((nospace[i]!=' ' && nospace[i] != '\t') && nospace[i]!='\0') {
    numero[j] = nospace[i];                                               //saving it for conversion
    j++;
    i++;
    num = 1;                                                              //needed to know it atoi is necessary
 // printf("%s", "ciaooo sono nel loop numero");
  }
  if (num == 1){
    j = 0;
    while (numero[j] >= '0' && numero[j] <= '9') j++;                     // I don't trust atoi so this is just to make sure
    numero[j] = '\0';                                                     //juuuuust to make sure.... ._.
    current_parse->number=atoi(numero);
  }
  printf("%d", current_parse->number);
}


command *parser(char *c){
  char nospace[200];

//remove_space(nospace, c);                               //rimuove gli spazi
  remove_comment(c);                                //rimuove i commenti
  strcpy(nospace,c);
  command *current_parse = malloc(sizeof(command));       //istanzio uno spazio pari a 'command'
  command *trash = malloc(sizeof(command));               //istanzio una nuova variabile in caso sia un comando inutile
  trash->instr[0]='\0';
  trash->type[0]='\0';

  filler(nospace, current_parse);
  return current_parse;                                             //ritorno il puntatore
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
    fprintf(fileout, "%c%d",  "@", current->number);
  }
  return 0;
}