#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "stack.h"
// #include "command.h"


/*
PROBLEMS:
situazione:
  -> Creazione di una simbol table. Per ogni di istruzione verrà aggiunta una funzione che ritornerà la stringa costruita
  -> Se possibile continuare facendo add, or, etc..

-> Cose da fare:
  ~> implementazione stack
  ~> MAIN.c:
    => fileIn and fileOut (PAOLO)                 DONE
    => ciclo fgets                                DONE
    => remove comments and remove spaces          DONE
    => implementare arithmetic/boolean commands
    => implementare pop command
  ~> STACK.c:
    => push (DAVID)                               DONE
*/

//=======
const char push[] = "push\0", pull[] = "pull\0", con[] = "constant\0",
       loc[] = "local\0", arg[] = "argument\0", sta[] = "static\0",
       pushconstantx[] = "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

//typedef char[15] instruction;

typedef symbol_table{
  char instruction[20];
  int num;
} table;

typedef struct command{
  char instr[200];
  char type[200];
  int number;
} command;


//SEARCH SYMBOL
//ricerca simbolo nella symbol table
int search_symbol (char* symbol, symb* s){
for (;strcmp(s->label, "END_OF_SYMBOL_TABLE") != 0; s++){         //finchè non arrivo alla fine del array
  if (strcmp(s->label, symbol) == 0)                              //Se label corrisponde allora ritorna numero
    return s->number;
}

return -1;                                                        //ritorna num negativo (non ho trovato la stringa)
}

//ADD SYMBOL
//aggiunge i simboli alla symbol table
void add_symbol (char* nospace, int num, symb* s){
  strcpy(s->label, nospace);                                //copio label
  s->number = num;                                            //copio il numero
}

//INIZIALIZE SYMBOL TABLE
//inizializza la symbol table
symb* inizialize_symbol_table(symb* st){
add_symbol ("add", 0, st++);
add_symbol ("sub", 1, st++);
add_symbol ("neg", 2, st++);
add_symbol ("eq", 3, st++);
add_symbol ("gt", 4, st++);
add_symbol ("lt", 5, st++);
add_symbol ("and", 6, st++);
add_symbol ("or", 7, st++);
add_symbol ("not", 8, st++);
add_symbol ("pop", 9, st++);
add_symbol ("push", 10, st++);
add_symbol ("label", 11, st++);
add_symbol ("goto", 12, st++);
add_symbol ("if-goto", 13, st++);
add_symbol ("function", 14, st++);
add_symbol ("call", 15, st++);
add_symbol ("return", 16, st++);
add_symbol ("static", 0, st++);
add_symbol ("local", 1, st++);
add_symbol ("argument", 2, st++);
add_symbol ("constant", 3, st++);
add_symbol ("END_OF_SYMBOL_TABLE", 4, st++);

return st;
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
  fill(nospace, numero);                                        //coping the number
  j = atoi(numero);
  if(j)                                                //if numbero is a number
    current_parse->number = j;                                  //coping the number

  printf("INSTR: %s\n", current_parse->instr);
  printf("TYPE: %s\n", current_parse->type);
  printf("NUMBER: %d\n", current_parse->number);

  //PAOLO TRY
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
    execute (fileout, current);
  }
  return 0;
}
