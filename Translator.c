#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 //#include "stack.h"
// #include "command.h"


/*
PROBLEMS: NONE
situazione:
  -> Push costant <numero> implementato correttamente.
  -> Creazione di una simbol table. Per ogni istruzione verrà aggiunta una funzione che ritornerà la stringa costruita
  -> Se possibile continuare facendo add, or, etc..
  -> Per utilizzare le operazioni aritmetiche bisogna mettere i valori pushati nella stack, è essenziale formarla sennò
      non si può capire a che numeri si riferiscono i comandi                   IMPORTANTE
  -> Domani prova ad implementare la parte dei commandi aritmetici, copia da <push>. Essenzialmente sfrutta il fatto che
      gli array vengono sempre passati per riferimento.
  -> Scusami se modifico il tuo codice, da oggi non lo farò più. Prossima volta ti consiglierò il modo in cui lo implementerei io :)
  -> Più si rendono le cose automatihe più situazioni complesse rende inoffensive!
  -> Buon lavoro a domani ;)

-> Cose da fare:
  ~> implementazione stack
  ~> MAIN.c:
    => fileIn and fileOut (PAOLO)                 DONE
    => ciclo fgets                                DONE
    => remove comments and remove spaces          DONE
    => implement <push>                           DONE
    => aggiungere la stack                        IMPORTANTE
    => implementare arithmetic/boolean commands
    => implementare pop command
  ~> STACK.c:
    => push (DAVID)                               DONE
*/

//=======
//const char push[] = "push\0", pull[] = "pull\0", con[] = "constant\0",
  //     loc[] = "local\0", arg[] = "argument\0", sta[] = "static\0",
    //   pushconstantx[] = "D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

//typedef char[15] instruction;

typedef struct symbol_table{
  char instruction[20];
  int num;
} symbol;

typedef struct command{
  char instr[200];
  char type[200];
  int number;
} command;

void counter(int *n){
  *n = *n + 1;
}

//PUSH
//costruisce la stringa dei comandi 'push'
void push_cmd (int numero, char* tipo, char istruzione[200]){
  //char istruzione[200] = "@\0";
  //char *f = istruzione;
  char num[7];
  sprintf(num, "%d", numero);

  switch(tipo[0]){
    case 'c':{
      strcat(istruzione, "@");
      strcat(istruzione, num);
      strcat(istruzione, "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    }break;

    default:{
      istruzione[0] = '\0';
      printf("ERROR!\n");
    }
  }

  printf("ISTR: %s\n", istruzione);

  //return *f;
}

//SEARCH SYMBOL
//ricerca simbolo nella symbol table
int search_symbol (char* symb, symbol* s){
  for (;strcmp(s->instruction, "END_OF_SYMBOL_TABLE") != 0; s++){         //finchè non arrivo alla fine del array
    printf("simbolo: %s\n", symb);
    printf("table: %s\n", s->instruction);
    if (strcmp(s->instruction, symb) == 0)                              //Se instruction corrisponde allora ritorna numero
      return s->num;
  }

  return -1;                                                        //ritorna num negativo (non ho trovato la stringa)
}

//ADD SYMBOL
//aggiunge i simboli alla symbol table
void add_symbol (char* nospace, int n, symbol* s){
  strcpy(s->instruction, nospace);                                //copio instruction
  s->num = n;                                            //copio il numero
}

//INIZIALIZE SYMBOL TABLE
//inizializza la symbol table
void inizialize_symbol_table(symbol* st){
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
    if (str[i] == c || str[i] == '\n')
      str[i] = '\0';
    i = i + 1;
  }
}

//WRITE
//it writes the string on <fileout>
void write(FILE *fileout, command *current, const char task[]){
  //printf("@%d\n%s", current->number, pushconstantx);
  /*if(!strcmp(task,con)){
    fprintf(fileout, "@%d\n%s", current->number, pushconstantx);
    printf("@%d\n%s", current->number, pushconstantx);
  }*/
}

//EXECUTE
//riconosce il tipo di istruzione e lo traduce
void execute(FILE *fileout, command *current, symbol *st, int *n){
  int tipo = -1;
  char num[6] = "\0";
  char memory[17];                                     //we'll put the memory address in here (static 0)
                                                      //                                             ^in questo caso 0.
  char istruzione[200] = "\0";

  printf("entrato in execute: %s\n", current->instr);
  tipo = search_symbol(current->instr, st);

  printf("TIPO: %d\n", tipo);

  switch (tipo) {
    case 0:{                          //ADD
      strcat(istruzione, "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=D+M\n@SP\nM=M+1\n");
    }break;

    case 1:{                          //SUB
      strcat(istruzione, "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=D-M\n@SP\nM=M+1\n");
    }break;

    case 2:{                          //NEG
      strcat(istruzione, "@SP\nM=M-1\nM=-M\n@SP\nM=M+1\n");
    }break;

    case 3:{                          //EQ
      sprintf(num, "%d", *n);
      strcat(istruzione, "@SP\nAM=M-1\nD=M\n@SP\nAM=M-1\nD=M-D\n@EQ_if_");
      strcat(istruzione, num);
      strcat(istruzione, "\nD;JEQ\nD=0\n@EQ_end_");
      strcat(istruzione, num);
      strcat(istruzione, "\n0;JMP\n(EQ_if_");
      strcat(istruzione, num);
      strcat(istruzione, ")\nD=-1\n(EQ_end_");
      strcat(istruzione, num);
      strcat(istruzione, ")\n@SP\nA=M-1\nM=D\n");
    }break;

    case 4:{                          //GT
      sprintf(num, "%d", *n);
      strcat(istruzione, "@SP\nAM=M-1\nD=M\n@SP\nAM=M-1\nD=M-D\n@GT_if_");
      strcat(istruzione, num);
      strcat(istruzione, "\nD;JGT\nD=0\n@GT_end_");
      strcat(istruzione, num);
      strcat(istruzione, "\n0;JMP\n(GT_if_");
      strcat(istruzione, num);
      strcat(istruzione, ")\nD=-1\n(GT_end_");
      strcat(istruzione, num);
      strcat(istruzione, ")\n@SP\nA=M-1\nM=D\n");
    }break;

    case 5:{                          //LT
      sprintf(num, "%d", *n);
      strcat(istruzione, "@SP\nAM=M-1\nD=M\n@SP\nAM=M-1\nD=M-D\n@LT_if_");
      strcat(istruzione, num);
      strcat(istruzione, "\nD;JLT\nD=0\n@LT_end_");
      strcat(istruzione, num);
      strcat(istruzione, "\n0;JMP\n(LT_if_");
      strcat(istruzione, num);
      strcat(istruzione, ")\nD=-1\n(LT_end_");
      strcat(istruzione, num);
      strcat(istruzione, ")\n@SP\nA=M-1\nM=D\n");
    }break;

    case 6:{                          //AND
      strcat(istruzione, "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=D&M\n@SP\nM=M+1\n");
    }break;

    case 7:{                          //OR
      strcat(istruzione, "@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nM=D|M\n@SP\nM=M+1\n");
    }break;

    case 8:{                          //NOT
      strcat(istruzione, "@SP\nM=M-1\nM=!M\n@SP\nM=M+1\n");
    }break;

    case 10:{
      push_cmd(current->number, current->type, istruzione);
    }break;

    case -1:
    default: printf("ERROR!\n");
  }

  fprintf(fileout, "%s", istruzione);
  printf("ISTRUZIONE: %s\n", istruzione);

  /*if(!strcmp(current->instr, push)){
    printf("primo strcmp confermato");
    if(!strcmp(current->type, con)){
      printf("secondo strcmp confermato");
      write(fileout, current, con);
    }
    else if(!strcmp(current->type, sta)){
      //  strcpy(memory,mem_access(current->num))
    }

  }*/
}

//FILLER
//
void filler(char* nospace, command* current_parse/*, Stack *s*/){        //written like this so that "  push \t   constant \t\t 9   " creates no problem
  int i = 0, j = 0, length_string = 0;
  char numero[20]={'\0'};                                 //empty string
  int instr = 0, type = 0, num = -2000;
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
  printf("NUMERO: %s\n", numero);
  if (numero[0] >= '0' && numero[0] <= '9'){                      //controllo che sia un numero non negativo
    j = atoi(numero);
    if(j >= 0)                                                //if numero is a number
      current_parse->number = j;                                  //coping the number

    //push(s, current_parse->number);
  }
  /*

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
command *parser(char *c/*, Stack *s*/){
  char nospace[200];

  //remove_space(nospace, c);                             //rimuove gli spazi
  remove_comment(c);                                      //rimuove i commenti
  //printf("%s", c);
  strcpy(nospace,c);
  command *current_parse = malloc(sizeof(command));       //istanzio uno spazio pari a 'command'
  command *trash = malloc(sizeof(command));               //istanzio una nuova variabile in caso sia un comando inutile
  trash->instr[0]='\0';
  trash->type[0]='\0';

  //TODO: controllo che non sia una stringa vuota, se si può fare
  filler(nospace, current_parse/*, s*/);                         //
  return current_parse;                                   //ritorno il puntatore
}

int main(int argc, char **argv){
  FILE *filein, *fileout;
  command *current;
  symbol table[30];
  int n = 0;
  //Stack *stack;
  char instr[200]="\0";           //riga in questione


  filein = fopen(argv[1], "r");     //assegnazione del file di input
  fileout = fopen(argv[2], "w");    //assegnazione del file di output
  inizialize_symbol_table(table);   //inizializza la symbol table
  fprintf(fileout, "%s", "@256\nD=A\n@SP\nM=D\n");
  //init(stack);                          //inizializza la stack


  while(fgets(instr, sizeof(instr), filein)!=NULL){         //while ci sono righe di grandezza massima 'instr' nel file 'filein'. Se ci sono assegnarle alla variabile (instr).
    printf("CURRENT INSTRUCTION: %s\n", instr);
    current = parser(instr/*, stack*/);
    //fprintf(fileout, "%c%d",  "@", current->number);
    //printf("%s", "arrivato a prima di execute");
    execute (fileout, current, table, &n);

    n++;
  }
  return 0;
}
