#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//random edit

typedef struct s_command {
  char command_type;
  char symbol[20];
  char dest[4];
  char comp[8];
  char jump[4];
  char instruction[17];
} command;

typedef struct symbols{
  char label[50];
  int number;
} symb;

typedef struct t_symbol{
  symb symbol_table[2000];
  int length;
  int variable;
} table;

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
  if (nospace[0]=='('){                                           //if per permettere il riutilizzo della funzione
    nospace++;

    //calcolo la lunghezza per pulire adeguatamente la stringa
    int length = strlen(nospace);
    while(nospace[length - 1] != ')')
      length--;
    length--;

    strncpy(s->label, nospace, length);         //copio la label senza ')' applico -3 perché alla pos: strlen(nospace)-1 == '\0', strlen(nospace)-2 == '\n', strlen(nospace)-3 == ')'
  }
  else
    strcpy(s->label, nospace);                                //copio label

  s->number = num;                                            //copio il numero
}

//INIZIALIZE SYMBOL TABLE
//inizializza la symbol table
symb* inizialize_symbol_table(symb* st){
  add_symbol ("R0", 0, st++);
  add_symbol ("R1", 1, st++);
  add_symbol ("R2", 2, st++);
  add_symbol ("R3", 3, st++);
  add_symbol ("R4", 4, st++);
  add_symbol ("R5", 5, st++);
  add_symbol ("R6", 6, st++);
  add_symbol ("R7", 7, st++);
  add_symbol ("R8", 8, st++);
  add_symbol ("R9", 9, st++);
  add_symbol ("R10", 10, st++);
  add_symbol ("R11", 11, st++);
  add_symbol ("R12", 12, st++);
  add_symbol ("R13", 13, st++);
  add_symbol ("R14", 14, st++);
  add_symbol ("R15", 15, st++);
  add_symbol ("SCREEN", 16384, st++);
  add_symbol ("KBD", 24576, st++);
  add_symbol ("SP", 0, st++);
  add_symbol ("LCL", 1, st++);
  add_symbol ("ARG", 2, st++);
  add_symbol ("THIS", 3, st++);
  add_symbol ("THAT", 4, st++);

  return st;
}

//REMOVE SPACES
//rimuove gli spazi
void remove_space(char *d, const char *s) {
  for (; *s; ++s) {
    if (*s != ' ' && *s != '\r')
      *d++ = *s;
  }

  *d = *s;
}

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

//TRADUCI COMP
//traduce in bits le operazioni
void traduci_comp(char* nospace, command* current_parse){
  //0
  if(nospace[0]=='0')
    strcpy(current_parse->comp,"0101010");

  //1
  if(nospace[0]=='1')
    strcpy(current_parse->comp,"0111111");

  //-
  if(nospace[0]=='-') {
    if (nospace[1]=='1')
      strcpy(current_parse->comp,"0111010");
    else if (nospace[1]=='A')
      strcpy(current_parse->comp,"0110011");
    else if (nospace[1]=='D')
      strcpy(current_parse->comp,"0001111");
    else if (nospace[1]=='M')
      strcpy(current_parse->comp,"1110011");
  }

  //A
  if(nospace[0]=='A'){
    if(nospace[1]=='+') {
      if(nospace[2]=='1')
        strcpy(current_parse->comp,"0110111");
    }
    else if (nospace[1]=='-'){
      if (nospace[2]=='1')
        strcpy(current_parse->comp,"0110010");
      else if (nospace[2]=='D')
        strcpy(current_parse->comp,"0000011");
    }
    else
      strcpy(current_parse->comp,"0110000");
  }

  //D
  if(nospace[0]=='D'){
    if(nospace[1]=='+'){
        if(nospace[2]=='1'){
            strcpy(current_parse->comp,"0011111");
        }
        if(nospace[2]=='A'){
            strcpy(current_parse->comp,"0000010");
        }
        if(nospace[2]=='M'){
            strcpy(current_parse->comp,"1000010");
        }
    }
    else if(nospace[1]=='-'){
        if(nospace[2]=='1'){
            strcpy(current_parse->comp,"0001110");
        }
        if(nospace[2]=='A'){
            strcpy(current_parse->comp,"0000011");
        }
        if(nospace[2]=='M'){
            strcpy(current_parse->comp,"1010011");
        }
    }
    else if(nospace[1]=='&'){
        if(nospace[2]=='A'){
            strcpy(current_parse->comp,"0000000");
        }
        if(nospace[2]=='M'){
            strcpy(current_parse->comp,"1000000");
        }
    }
    else if(nospace[1]=='|'){
        if(nospace[2]=='A'){
            strcpy(current_parse->comp,"0010101");
        }
        if(nospace[2]=='M'){
            strcpy(current_parse->comp,"1010101");
        }
    }
    else {
        strcpy(current_parse->comp,"0001100");
    }
  }

  //!
  if(nospace[0]=='!'){
      if(nospace[1]=='D'){
          strcpy(current_parse->comp,"0001101");
      }
      if(nospace[1]=='A'){
          strcpy(current_parse->comp,"0110001");
      }
      if(nospace[1]=='M'){
          strcpy(current_parse->comp,"1110001");
      }
  }

  //M
  if(nospace[0]=='M'){
      if(nospace[1]=='+'){
          if(nospace[2]=='1'){
              strcpy(current_parse->comp,"1110111");
          }
      }
      else if(nospace[1]=='-'){
          if(nospace[2]=='1'){
              strcpy(current_parse->comp,"1110010");
          }
          if(nospace[2]=='D'){
              strcpy(current_parse->comp,"1000111");
          }
      }
      else {
          strcpy(current_parse->comp,"1110000");
      }
  }
}

//TRADUCI DEST
//traduce in bits i destinatari
void traduci_dest(char* nospace, command* current_parse){
    int pos = 0;

    if(nospace[pos]=='A'){
      current_parse->dest[0] = '1';
      pos++;
    }

    if(nospace[pos]=='M'){
        current_parse->dest[2] = '1';
        pos++;
    }

    if(nospace[pos]=='D')
        current_parse->dest[1] = '1';
}

//TRADUCI JUMP
//traduzione in bits dei jump                 TODO:ottimizzazione
void traduci_jump(char* nospace, command* current_parse){

  if(nospace[0] == 'J'){
    if(nospace[1]=='G'){
        if(nospace[2]=='T'){
            strcpy(current_parse->jump,"001");
        }
        else {
            strcpy(current_parse->jump,"011");
        }
    }
    else if(nospace[1] == 'E'){
        strcpy(current_parse->jump,"010");
    }
    else if(nospace[1] == 'L'){
        if(nospace[2] == 'E'){
            strcpy(current_parse->jump,"110");
        } else {
            strcpy(current_parse->jump,"100");
        }
    }
    else if(nospace[1] == 'M'){
        strcpy(current_parse->jump,"111");
    }
    else {
        strcpy(current_parse->jump,"101");
    }
  }
}

//ISIN
//controllo presenza carattere in una stringa
int isin(char* c, const char d){
  while(*c!='\0'){
    if( *c==d) return 1;
    else c++;
  }
  return 0;
}

//TRASLATE C
//assemblaggio c-istr                       CHANGE
void translate(char* nospace, command* current_parse){
  int dj = isin(nospace, '=') + isin(nospace, ';') * 10;      //se d -> 1; se j -> 10; se d&j -> 11;          CHANGE
                                                              //comp sempre presente

  char y[4]={'1','1','1','\0'};                   //i 3 bit identificativi della c-instr
  strcpy(current_parse->dest,"000");              //considero inizialmente NULL
  strcpy(current_parse->jump,"000");              //considero inizialmente NULL

  //CHANGE
  if(dj%10) {                                  //Se dest presente
    traduci_dest(nospace,current_parse);      //traduzione dest
    while(*nospace!='=')
      nospace++;           //mi sposto fino alla parte comp
    nospace++;
  }

  traduci_comp(nospace,current_parse);        //traduzione comp

  if(dj/10) {                                  //Se jump presente
    while(*nospace!=';')
      nospace++;           //mi sposto fino alla parte jump
    nospace++;
    traduci_jump(nospace,current_parse);      //traduco jump
  }

  //assemblo l'istruzione
  strcat(current_parse->instruction, y);
  strcat(current_parse->instruction, current_parse->comp);
  strcat(current_parse->instruction, current_parse->dest);
  strcat(current_parse->instruction, current_parse->jump);

  current_parse->instruction[16]='\0';          //pulisco la stringa
}

//TRANSLATE A
//traduzione in A-instr
void translateA(FILE *fileout, command* p, table* t){
    char x[17];                                           //variabile temporanea in cui salvo l'istruzione binaria
    int b=0;                                              //booleano

    if(!(p->symbol[0]>='0' && p->symbol[0]<='9'))         //segnalo se è numero o simbolo (1 = simbolo, 0 = numero)
      b=1;

    int n = -1;
    if (b==0)
      n = atoi(p->symbol);              //se numero
    else{
      n = search_symbol(p->symbol, t->symbol_table);      //se simbolo

      //Se variabile
      if (n == -1){
        add_symbol (p->symbol, t->variable, &t->symbol_table[t->length]);         //aggiunta variabile

        n = t->variable;                                                          //trovo il numero corrispondente
        t->variable++;
        t->length++;

        add_symbol("END_OF_SYMBOL_TABLE", -1, &t->symbol_table[t->length]);
      }
    }

    //calcolo valore binario e salvo in x
    int i = 15;
    while (n > 0)
    {
      if (n % 2 == 0)
      x[i] = '0';
      else
      x[i] = '1';
      n = n / 2;
      i--;
    }

    //aggiungo gli zeri
    while(i>0){
      x[i] = '0';
      i--;
    }

    x[i]='0';
    x[16] = '\0';                   //pulisco stringa

    strcpy(p->instruction, x);      //copio nell'istruzione vera e propria
}

//FILLER
//serve per comprendere se un comando è A-instr, C-instr o Etichetta e agisce di conseguenza.
command* filler(FILE *fileout, char* nospace, command* current_parse, table* t){
  //capisco quale dellle 3 possibilità è
  if (nospace[0]=='@')
    current_parse->command_type = 'A';              //Tipo A
  else
    current_parse->command_type = 'C';              //Tipo C

  //applico
  if (current_parse->command_type=='A') {
      strncpy(current_parse->symbol, ++nospace, strlen(nospace) - 2);        //copio l'istr. senza il @ (prima incremento poi copio)
      translateA(fileout, current_parse, t);                      //traduco in comando A
  }
  else if (current_parse->command_type=='C')
    translate(nospace,current_parse);                 //traduco in comando C
}

//PARSER
//sequenza di istruzioni generali per l'assemblaggio del istruzione in binario
command* parser(FILE *fileout, char* str, table* t) {
  char nospace[200];                                      //istruzione hack
  command *current_parse = malloc(sizeof(command));       //istanzio uno spazio pari a 'command'
  command *trash = malloc(sizeof(command));               //istanzio una nuova variabile in caso sia un comando inutile

                                                          //TODO: vedere se si può evitare l'utilizzo di trash utilizzando una unica variaibile
  trash->instruction[0]='c';                              //Assegno a trash 'c' per identificarlo come commento
  remove_space(nospace, str);                             //rimuove gli spazi
  remove_comment(nospace);                                //rimuove i commenti
  if (nospace[1]=='\0'||nospace[1]=='\n'||nospace[0]=='(')                 //se l'istr è un commento o riga vuota ritorno trash          CHANGE
    return trash;

  filler(fileout, nospace, current_parse, t);                       //Vero e proprio assemblaggio del comando hack
  return current_parse;                                   //ritorno l'istruzione binaria
}

//MAIN
int main(int argc, char **argv) {
  FILE *filein, *fileout;           //file di input e output
  command *current;                 //puntatore del comando in questione
  char instr[200]={'\0'};           //riga in questione
  table st;                         //symbol table TODO: deve diventare una lista per occupare meno spazio in memoria
                                    //TODO: implementare la lista
                                    //IMPORTANTE: L'array DEVE essere maggiore rispetto alla quantità di label del filein, altrimenti scrittura sporca
  symb *s = st.symbol_table;

  filein = fopen(argv[1], "r");     //assegnazione del file di input
  fileout = fopen(argv[2], "w");    //assegnazione del file di output

  s = inizialize_symbol_table(s);
  st.length = 23;
  st.variable = 16;

  int riga = 0;
  char nospace[200];
  while(fgets(instr, sizeof(instr), filein)!=NULL){         //while ci sono righe di grandezza massima 'instr' nel file 'filein'. Se ci sono assegnarle alla variabile (instr).
    remove_space(nospace, instr);                           //rimuove gli spazi
    remove_comment(nospace);                                //rimuove i commenti

    if (nospace[0]=='('){
      add_symbol(instr, riga, s);
      s++;                                                  //sposto alla cella successiva
      st.length++;                                          //incremento contatore lunghezza array
    }

    if (nospace[0]!='\0' && nospace[0]!='\n' && nospace[0]!='(')                 //se l'istr è un commento o riga vuota ritorno trash          CHANGE
      riga++;
  }

  add_symbol("END_OF_SYMBOL_TABLE", -1, s);

  fseek (filein, 0, SEEK_SET);                              //sposto l'offset al punto di inizio del file

  //SECONDA PASSATA
  //while con fgets e le righe in una lista
  while(fgets(instr, sizeof(instr), filein)!=NULL){           //while ci sono righe di grandezza massima 'instr' nel file 'filein'. Se ci sono assegnarle alla variabile (instr).
      current = parser(fileout, instr, &st);                  //traduco l'istruzione in binario
      if (current->instruction[0]!='c'){                      //controllo che l'istruzione non sia un commento
        current->instruction[16] = '\0';                      //pulisco da memoria sporca
        //printf("Binary: %s\n", current->instruction);
        fprintf(fileout, "%s\n", current->instruction);       //scrivo l'istruzione nel file di output
      }
  }

  fclose(filein);                                           //chiudo file di input
  fclose(fileout);                                          //chiudo file di output
  return (0);
}
