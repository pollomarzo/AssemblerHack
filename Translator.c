#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 //#include "stack.h"
// #include "command.h"


/*
LINKS:
  => https://github.com/renlijie/nand2tetris/blob/master/projects/07/Translator.java
PROBLEMS:
ACTUAL SITUATION:
  -> Push costant <numero> implementato correttamente.
  -> Add/Sub/And/etc.. implementati correttamente.
  -> Creazione di una simbol table. Per ogni tipo istruzione verrà aggiunta una funzione che ritornerà la stringa costruita
  -> Ora provo a fare il pop :)
  -> Scusami se modifico il tuo codice, da oggi non lo farò più. Prossima volta ti consiglierò il modo in cui lo implementerei io :)
  -> Più si rendono le cose automatihe più situazioni complesse rende inoffensive!
  -> Buon lavoro a domani ;)
DIFFERENCES:
  => Nella struttura symbol_table avrà char num[5]; (DAVID)

-> Cose da fare:
  ~> implementazione stack
  ~> MAIN.c:
    => fileIn and fileOut (PAOLO)                 DONE
    => ciclo fgets                                DONE
    => remove comments and remove spaces          DONE
    => implement <push>                           DONE
    => implementare arithmetic/boolean commands   DONE
    => implementare pop command           (DAVID)
    => implementare program flow command  (PAOLO)
    => implementare static, pointer       (DAVID)
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
  char special[20];
  int num;
} symbol;

typedef struct command{
  char instr[200];
  char type[200];
  int number;
} command;

//SEARCH SYMBOL
//ricerca simbolo nella symbol table
symbol* search_symbol (char* symb, symbol* s){
  for (;strcmp(s->instruction, "END_OF_SYMBOL_TABLE") != 0; s++){         //finchè non arrivo alla fine del array
    /*printf("simbolo: %s\n", symb);
    printf("table: %s\n", s->instruction);*/
    if (strcmp(s->instruction, symb) == 0)                              //Se instruction corrisponde allora ritorna numero
    break;
  }
  return s;                                                        //ritorna num negativo (non ho trovato la stringa)
}

//POP
//costruisce la stringa dei comandi 'pop'
void pop_cmd (int numero, char* segment, char istruzione[200], symbol *st){
  //char istruzione[200] = "@\0";
  //char *f = istruzione;
  char num[7];
  symbol *tipo;

  sprintf(num, "%d", numero);
  tipo = search_symbol(segment, st);
  printf("TIPO POP: %d\n", tipo->num);

  switch(tipo->num){
    case 1: {                               //LOCAL
      strcat(istruzione, "@LCL\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nD=D+A\n");
    }break;

    case 2: {                               //ARGUMENT
      strcat(istruzione, "@ARG\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nD=D+A\n");
    }break;

    case 4: {                            //THIS
      strcat(istruzione, "@THIS\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nD=D+A\n");
    }break;

    case 3: {                            //THAT
      strcat(istruzione, "@THAT\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nD=D+A\n");
    }break;

    /*case 's': {
          "@" + currFileName + "." + idx + "\n" +
          "D=A\n"
    }*/

    case 7: {                            //TEMP
      strcat(istruzione, "@R5\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nD=D+A\n");
    }
  }

  strcat(istruzione, "@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n");
  /*
  char num[7];
  sprintf(num, "%d", numero);

  switch(tipo[0]){
    case 'l':{
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

  //return *f;*/
}

//PUSH
//costruisce la stringa dei comandi 'push'
void push_cmd (int numero, char* segment, char istruzione[200], symbol *st){
  //char istruzione[200] = "@\0";
  //char *f = istruzione;
  char num[7];
  symbol *tipo;

  tipo = search_symbol(segment, st);
  printf("TIPO POP: %d\n", tipo->num);

  sprintf(num, "%d", numero);

  switch(tipo->num){
    case 5:{
      strcat(istruzione, "@");
      strcat(istruzione, num);
      strcat(istruzione, "\nD=A\n");
    }break;

    case 1: {
      strcat(istruzione, "@LCL\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nA=D+A\nD=M\n");;
    }break;

    case 2: {
      strcat(istruzione, "@ARG\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nA=D+A\nD=M\n");;
    }break;

    case 3: {
      strcat(istruzione, "@THAT\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nA=D+A\nD=M\n");;
    }break;

    case 4: {
      strcat(istruzione, "@THIS\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nA=D+A\nD=M\n");;
    }break;

    case 7: {
      strcat(istruzione, "@R5\nD=M\n@");
      strcat(istruzione, num);
      strcat(istruzione, "\nA=D+A\nD=M\n");;
    }break;

    default:{
      istruzione[0] = '\0';
      printf("ERROR!\n");
    }
  }
  strcat(istruzione, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");

  printf("ISTR: %s\n", istruzione);

  //return *f;
}

//ARITHEMTIC
//costruisce la stringa dei comandi aritmetici
/*void arithmetic (char istruzione[200], int* n){
  strcat(istruzione, "@SP\nAM=M-1\nD=M\n@SP\nAM=M-1\nM=M");
  switch(*n){
    case 0: strcat(istruzione, "+");break;
    case 1: strcat(istruzione, "-");break;
    case 2: strcat(istruzione, "&");break;
    case 3: strcat(istruzione, "|");break;
    default: strcat(istruzione, "ERROR!");
  }
  strcat(istruzione, "D\n@SP\nM=M+1\n");
}*/
void arithmetic (char istruzione[200], char* s1, char* t, char* s2){
  strcat(istruzione, s1);
  strcat(istruzione, t);
  strcat(istruzione, s2);
}

//FINDNAME
void find_name(command *current){
  while(command->type != '\0' && command->type != '\n' && command->type != '.' && command->type != ' '){
    command->type++;
  }
  if (command->type == '.') command->type++;
}

//FUNCTIONDEF
void function(char istruzione[200], command *current){
  strcpy(istruzione, '(');
  strcat(istruzione, current->type);
  strcat(istruzione, ")\n@SP\nA=M\n");
  int i = 0;
  while(i < current->number){
    i = i + 1;
    strcat(istruzione, "M=0\nA=A+1\n");
  }
  strcat(istruzione, "D=A\n@SP\nM=D\n");
}

//FUNCTIONCALL
void call(char istruzione[200], command *current, int *n){
  char c[4] = "\0\0\0\0";
  char p[4] = "\0\0\0\0";
  sprintf(p, "%d", current->number);
  sprintf(c, "%d", *n);
  // SP -> R13
  strcpy(istruzione, "@SP\nD=M\n@R13\nM=D\n@RETURN-");
  // @RET -> *SP
  strcat(istruzione, c);
  strcat(istruzione, "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n@LCL\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n@ARG\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n@R13\nD=M\n@");
  strcat(istruzione, p);
  strcat(istruzione, "\nD=D-A\n@ARG\nM=D\n@SP\nD=M\n@LCL\nM=D\n@");
  strcat(istruzione, current->type);
  strcat(istruzione, "\n0;JMP\n(RETURN-");
  strcat(istruzione, c);
  strcat(istruzione, ")\n");
}

//FUNCRETURN
void funcreturn(char istruzione[200]){
  strcat(istruzione, "@LCL\nD=M\n@5\nA=D-A\nD=M\n@R13\nM=D\n@SP\nA=M-1\nD=M\n@ARG\nA=M\nM=D\nD=A+1\n@SP\nM=D\n@LCL\nAM=M-1\nD=M\n@THAT\nM=D\n@LCL\nAM=M-1\nD=M\n@THIS\nM=D\n@LCL\nAM=M-1\nD=M\n@ARG\nM=D\n@LCL\nA=M-1\nD=M\n@LCL\nM=D\n@R13\nA=M\n0;JMP\n\0");
}

//BOOLEAN
//costruisce la stringa dei comandi booleani
void boolean (char istruzione[200], char* s, int* n){
  char num[6] = "\0";
  sprintf(num, "%d", *n);
  strcat(istruzione, "@SP\nAM=M-1\nD=M\n@SP\nAM=M-1\nD=M-D\n@");
  strcat(istruzione, s);
  strcat(istruzione, "_if_");
  strcat(istruzione, num);
  strcat(istruzione, "\nD;J");
  strcat(istruzione, s);
  strcat(istruzione, "\nD=0\n@");
  strcat(istruzione, s);
  strcat(istruzione, "_end_");
  strcat(istruzione, num);
  strcat(istruzione, "\n0;JMP\n(");
  strcat(istruzione, s);
  strcat(istruzione, "_if_");
  strcat(istruzione, num);
  strcat(istruzione, ")\nD=-1\n(");
  strcat(istruzione, s);
  strcat(istruzione, "_end_");
  strcat(istruzione, num);
  strcat(istruzione, ")\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
}

//ADD SYMBOL
//aggiunge i simboli alla symbol table
void add_symbol (char* nospace, char* spec, int n, symbol* s){
  strcpy(s->instruction, nospace);                                //copio instruction
  strcpy(s->special, spec);                                //copio instruction
  s->num = n;                                            //copio il numero
}

//INIZIALIZE SYMBOL TABLE
//inizializza la symbol table
void inizialize_symbol_table(symbol* st){
  add_symbol ("add", "+", 0, st++);
  add_symbol ("sub", "-", 0, st++);
  add_symbol ("and", "&", 0, st++);
  add_symbol ("or", "|", 0, st++);
  add_symbol ("not", "!", 1, st++);
  add_symbol ("neg", "-", 1, st++);
  add_symbol ("eq", "EQ", 2, st++);
  add_symbol ("gt", "GT", 2, st++);
  add_symbol ("lt", "LT", 2, st++);
  add_symbol ("pop", "\0", 9, st++);
  add_symbol ("push", "\0", 10, st++);
  add_symbol ("label", "\0", 11, st++);
  add_symbol ("goto", "\0", 12, st++);
  add_symbol ("if-goto", "\0", 13, st++);
  add_symbol ("function", "\0", 14, st++);
  add_symbol ("call", "\0", 15, st++);
  add_symbol ("return", "\0", 16, st++);
  add_symbol ("static", "\0", 0, st++);                     //TODO: find a way for static
  add_symbol ("local", "LCL", 1, st++);
  add_symbol ("argument", "ARG", 2, st++);
  add_symbol ("that", "THAT", 3, st++);
  add_symbol ("this", "THIS", 4, st++);
  add_symbol ("constant", "\0", 5, st++);
  add_symbol ("pointer", "\0", 6, st++);
  add_symbol ("temp", "\0", 7, st++);
  add_symbol ("END_OF_SYMBOL_TABLE", "\0", -1, st++);
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
    if (str[i] == c || str[i] == '\n' || str[i] == '\r')
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
  symbol *tipo;
  char num[6] = "\0";
  char memory[17];                                     //we'll put the memory address in here (static 0)
                                                      //                                             ^in questo caso 0.
  char istruzione[200] = "\0";

  printf("entrato in execute: %s\n", current->instr);
  tipo = search_symbol(current->instr, st);

  printf("TIPO: %d\n", tipo->num);

  switch (tipo->num) {
    case 0:{                  //ADD, SUB, AND, OR
      arithmetic(istruzione, "@SP\nAM=M-1\nD=M\n@SP\nAM=M-1\nM=M", tipo->special, "D\n@SP\nM=M+1\n");
    }break;

    case 1:{                  //NEG, NOT
      arithmetic(istruzione, "@SP\nAM=M-1\nM=", tipo->special, "M\n@SP\nM=M+1\n");
    }break;

    case 2:{                          //EQ, GT, LT
      boolean(istruzione, tipo->special, n);
    }break;

    case 9:{
      pop_cmd(current->number, current->type, istruzione, st);
    }break;

    case 10:{
      push_cmd(current->number, current->type, istruzione, st);
    }break;

    case 11:{
      strcat(istruzione, "(");
      strcat(istruzione, current->type);
      strcat(istruzione, ")");
    }

    case 12:{
      strcat(istruzione, "@");
      strcat(istruzione, current->type);
      strcat(istruzione, "\n");
      strcat(istruzione, "0;JMP\n");
    }

    case 13:{
      strcat(istruzione, "@SP\n");
      strcat(istruzione, "AM=M-1\n");
      strcat(istruzione, "D=M\n");
      strcat(istruzione, "@");
      strcat(istruzione, current->type);
      strcat(istruzione, "\n");
      strcat(istruzione, "D;JNE\n");
    }

    case 14:{
      find_name(current);
      function(istruzione, current);
    }

    case 15:{
      call(istruzione, current, n);
    }

    case 16:{
      funcreturn(istruzione);
    }

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

  memset(current_parse->instr, 0, 200);
  memset(current_parse->type, 0, 200);
  //you can either way put '\0' to initialize it
  //Inizialing command variables        TODO: create a methods to do it
  strcpy(current_parse->instr, "\0");                           //initialize correctly to avoid problems
  strcpy(current_parse->type, "\0");
  current_parse->number = -1;                               //I hope I'm allowed to do this
  //printf("%s", "ciaooo sono prima dei loop");

  //DAVID TRY
  //ho reso tutto algoritmo
  for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
  fill(nospace, current_parse->instr);          //copying the instruction
  for(;*nospace != ' ' && *nospace != '\t' && *nospace != '\0'; nospace++){}

  for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
  fill(nospace, current_parse->type);           //copying the type
  for(;*nospace != ' ' && *nospace != '\t' && *nospace != '\0'; nospace++){}

  for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
  fill(nospace, numero);                                        //copying the number
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
  fprintf(fileout, "%s", "@1015\nD=A\n@LCL\nM=D\n");
  fprintf(fileout, "%s", "@1527\nD=A\n@ARG\nM=D\n");
  fprintf(fileout, "%s", "@3000\nD=A\n@THIS\nM=D\n");
  fprintf(fileout, "%s", "@3010\nD=A\n@THAT\nM=D\n");
  fprintf(fileout, "%s", "@5\nD=A\n@R5\nM=D\n");
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
