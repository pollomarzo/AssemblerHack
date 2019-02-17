#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "stack.h"
// #include "command.h"


/*
last commit: Changed last section filler. Should be ok

PROBLEMS: non sono sicuro di come funzioni fprintf. stampa "per mille" invece che @
          fai un run e vedrai l'errore. quando copio, viene "pushàN" non so perché
Expected solution: boh

situazione: abbiamo instr, type e number in una struttura. se instr è push bisogna attivare
            una funzione che "metta sullo stack" che chiameremo "push" e non restituisce nulla
                                  '-> @10;D=A;@SP;A=M;M=D;@SP;M=M+1;
            se instr è add bisogna attivare la funzione add che scriva la somma dei due ultimi
            valori sullo stack
            e così via. facciamo funzioni diverse? intanto faccio push

-> Cose da fare:
  ~> implementazione stack
  ~> MAIN.c:
    => fileIn and fileOut (PAOLO)
    => ciclo fgets
    => remove comments and remove spaces
  ~> STACK.c:
    => push (DAVID)                              DONE
*/

//=======
const char push[] = "push\0", pull[] = "pull\0", con[] = "constant\0",
       loc[] = "local\0", arg[] = "argument\0", sta[] = "static\0",
       pushconstantx[] = "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

typedef struct command{
  char instr[200];
  char type[200];
  int number;
} command;

//REMOVE SPACES AND TABS
//remove excessive spaces and tabs

void remove_strings (char *nospace){
  for(;*nospace != ' ' && *nospace != '\t'; nospace++) {}
}

void remove_space (const char* nospace, char *s){
  while(*nospace == ' ' || *nospace == '\t')
    *s = 5;

  *s = *nospace;
  printf("NOSPACE IN RS: %s\n", nospace);
}

//FILL
//fill a string without tabs and spaces
void fill (const char *nospace, char *copier){
  int i = 0;
  for(;*nospace != ' ' && *nospace != '\t' && *nospace != '\0'; nospace++)
    *copier++ = *nospace;                                                      //move forward until end of space and tab
}

//REMOVE COMMENTS
//rimuove i commenti
void remove_comment(char str[200]) {
  char c = '/';
  int i=0;
  while (i < 200) {
    if (str[i] == c)
      str[i] = '\0';
    i = i + 1;
  }
}

void write(FILE *fileout, command *current, const char task[]){
  //printf("@%d\n%s", current->number, pushconstantx);
  if(!strcmp(task,con)){
    fprintf(fileout, "@%d\n%s", current->number, pushconstantx);
    printf("@%d\n%s", current->number, pushconstantx);
  }
}

void execute(FILE *fileout, command *current){
  int memory[16];                                     //we'll put the memory address in here (static 0)
                                                      //                                             ^in questo caso 0.
  printf("entrato in execute: \n");
  printf("%s\n", current->instr);
  if(!strcmp(current->instr, push)){
    printf("primo strcmp confermato");
    if(!strcmp(current->type, con)){
      printf("secondo strcmp confermato");
      write(fileout, current, con);
    }
    else if(!strcmp(current->type, sta)){
//  strcpy(memory,mem_access(current->num))
    }

  }
}

//FILLER
//
void filler(char* nospace, command* current_parse){        //written like this so that "  push \t   constant \t\t 9   " creates no problem
  int i = 0, j = 0, length_string = 0;
  char numero[20]={'\0'};                                 //empty string
  int instr = 0, type = 0, num = 0;
  char clean[200]={'\0'};                                 //empty cleaning string
  char word[20] = {'\0'};
  //printf("%s", nospace);

  //you can either way put '\0' to initialize it
  //Inizialing command variables        TODO: create a methods to do it
  strcpy(current_parse->instr, "\0");                           //initialize correctly to avoid problems
  strcpy(current_parse->type, "\0");
  current_parse->number = -1;                               //I hope I'm allowed to do this
//printf("%s", "ciaooo sono prima dei loop");

  //DAVID TRY
  //ho reso tutto algoritmo
  for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
  fill(nospace, current_parse->instr);          //coping the instruction
  for(;*nospace != ' ' && *nospace != '\t' && *nospace != '\0'; nospace++){}

  for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
  fill(nospace, current_parse->type);           //coping the type
  for(;*nospace != ' ' && *nospace != '\t' && *nospace != '\0'; nospace++){}

  for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
  if(*nospace!='\0'){                                             //è l'unico carattere che può esserci a questo punto. \n? sarebbe dopo questo
    fill(nospace, numero);                                        //copying the number
    j = atoi(numero);
    current_parse->number = j;
  }
  /*
  fill(nospace, numero);                                        //coping the number
  j = atoi(numero);
  if(j)                                                //if numbero is a number
    current_parse->number = j;                                  //coping the number
  */
  printf("INSTR: %s\n", current_parse->instr);
  printf("TYPE: %s\n", current_parse->type);
  printf("NUMBER: %d\n", current_parse->number);
    /*current_parse->instr[j] = nospace[i];                                 //placing it inside of struct as instr
    printf("%s\n", current_parse->instr);
    j++;
    i++;
    instr = 1;                                                            //acts as boolean value in case in case I forgot something
  //  printf("%s", "ciaooo sono nel loop instr");
  }
  if(instr) nospace[i]='\0';
  //printf("%s", current_parse->instr);
  j = 0;
remove_space(nospace);
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



  //cycle to erase excessive spaces and  tabs
  i = remove_space(nospace, i);
  /*while((nospace[i]==' ' || nospace[i] == '\t') && nospace[i]!='\0'){
   // printf("%s", "ciaooo sono nel loop che cerca il primo buco");
  i++;                                                      //move forward until end of space and tab
}

  while((nospace[i]!=' ' && nospace[i] != '\t') && nospace[i]!='\0') {    //copy until tab is found
    current_parse->instr[j] = nospace[i];                                 //placing it inside of struct as instr
    printf("%s\n", current_parse->instr);
    j++;
    i++;
    instr = 1;                                                            //acts as boolean value in case in case I forgot something
  //  printf("%s", "ciaooo sono nel loop instr");
  }
  if(instr) nospace[i]='\0';
  //printf("%s", current_parse->instr);
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
  */
}

//PARSER
//prepara le variabili e l'istruzione da tradurre
command *parser(char *c){
  char nospace[200];

  //remove_space(nospace, c);                             //rimuove gli spazi
  remove_comment(c);                                      //rimuove i commenti
  //printf("%s", c);
  strcpy(nospace,c);
  command *current_parse = malloc(sizeof(command));       //istanzio uno spazio pari a 'command'
  command *trash = malloc(sizeof(command));               //istanzio una nuova variabile in caso sia un comando inutile
  trash->instr[0]='\0';
  trash->type[0]='\0';

  filler(nospace, current_parse);                         //
  return current_parse;                                   //ritorno il puntatore
}

int main(int argc, char **argv){
  FILE *filein, *fileout;

  filein = fopen(argv[1], "r");     //assegnazione del file di input
  fileout = fopen(argv[2], "w");    //assegnazione del file di output

  command *current;
  char instr[200]={'\0'};           //riga in questione

  while(fgets(instr, sizeof(instr), filein)!=NULL){         //while ci sono righe di grandezza massima 'instr' nel file 'filein'. Se ci sono assegnarle alla variabile (instr).
    printf("CURRENT INSTRUCTION: %s\n", instr);
    current = parser(instr);
    //fprintf(fileout, "%c%d",  "@", current->number);
    //printf("%s", "arrivato a prima di execute");
    //execute (fileout, current);
  }
  return 0;
}
