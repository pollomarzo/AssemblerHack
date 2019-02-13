#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct s_command {
  char command_type;
  char symbol[20];
  char dest[4];
  char comp[8];
  char jump[4];
  char instruction[17];
} command;

/*typedef struct t_symbol{
  char label[30];
  int number;
} symbol_table;

void add_symbol (char *nospace, int riga, symbol_table table){

}*/

void remove_space(char *d, const char *s) {
  for (; *s; ++s) {
    if (*s != ' ')
      *d++ = *s;
  }

  *d = *s;
}

void remove_comment(char str[200]) {
  char c = '/';
  int i=0;
  while (i < 20) {
    if (str[i] == c)
      str[i] = '\0';
    i = i + 1;
  }
}

void traduci_comp(char *nospace, command *current_parse){
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

void traduci_dest(char *nospace, command *current_parse){
    /*if(nospace[0] == 'n'  && nospace[1]== 'u' && nospace[2] == 'l' && nospace[3] == 'l'){     non può esserci la scritta "null"
      strcpy(current_parse->dest, "000");
    }*/
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



    /*
    if(nospace[0]=='M'){
        if(nospace[1] == 'D'){
            strcpy(current_parse->dest,"011");
        }
        else {
            strcpy(current_parse->dest,"001");
        }
    }

    if(nospace[0]=='D'){
        strcpy(current_parse->dest,"010");
    }

    if(nospace[0]=='A'){
        if(nospace[1]=='M'){
            if(nospace[2]=='D'){
                strcpy(current_parse->dest,"111");
            }
            else {
                strcpy(current_parse->dest,"101");
            }
        }
        else if(nospace[1]=='D'){
            strcpy(current_parse->dest,"110");
        }
        else{
            strcpy(current_parse->dest,"100");
        }
    }*/
}

void traduci_jump(char *nospace, command *current_parse){
  /*if(nospace[0] == 'n'  && nospace[1]== 'u' && nospace[2] == 'l' && nospace[3] == 'l'){     non può esserci la scritta "null"
    strcpy(current_parse->jump, "000");
  }*/

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

int isin(char *c, const char d){
  while(*c!='\0'){
    if( *c==d) return 1;
    else c++;
  }
  return 0;
}

//TRASLATE C
//assemblaggio c-istr                       CHANGE
void translate(char *nospace, command *current_parse){
  //char x='\0'; //if x=d only dest and comp; if x=j only comp and j; if x=l dest,comp,jump

  int dj = isin(nospace, '=') + isin(nospace, ';') * 10;      //se d -> 1; se j -> 10; se d&j -> 11;          CHANGE
                                                              //comp sempre presente

  /*if (isin(nospace,'=')&&(1-isin(nospace,';')))
    x='d';
  else if ((1-(isin(nospace, '='))) && (isin(nospace, ';')))
    x='j';
  else if ((isin(nospace, '=')) && (isin(nospace, ';')))
    x='l';*/

  char y[4]={'1','1','1','\0'};                   //i 3 bit identificativi della c-instr
  strcpy(current_parse->dest,"000");              //considero inizialmente NULL
  strcpy(current_parse->jump,"000");              //considero inizialmente NULL

  /*if(x=='d') {
    traduci_dest(nospace,current_parse);
    while(*nospace!='=') nospace++;
    nospace++;
    traduci_comp(nospace,current_parse);

    }

  if(x=='j') {
    traduci_comp(nospace,current_parse);
    while(*nospace!=';') nospace++;
    nospace++;
    traduci_jump(nospace,current_parse);
  }

  if(x=='l') {
    traduci_dest(nospace,current_parse);
    while(*nospace!='=') nospace++;
    nospace++;
    traduci_comp(nospace,current_parse);

    while(*nospace!=';') nospace++;
    nospace++;
    traduci_jump(nospace,current_parse);
  }*/

  //CHANGE
  if(dj%10) {                                  //Se dest presente
    traduci_dest(nospace,current_parse);      //traduzione dest
    while(*nospace!='='){
      printf("%c", nospace[0]);
      nospace++;           //mi sposto fino alla parte comp
    }
    nospace++;
    printf("\n");
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
  printf("Comp: %s\n", current_parse->comp);
  strcat(current_parse->instruction, current_parse->comp);
  printf("Dest: %s\n", current_parse->dest);
  strcat(current_parse->instruction, current_parse->dest);
  printf("Jump: %s\n", current_parse->jump);
  strcat(current_parse->instruction, current_parse->jump);

  current_parse->instruction[16]='\0';
}

//TRANSLATE A
//traduzione in A-instr                     CHANGE
void translateA(command *p){
    char x[17];                                           //variabile temporanea in cui salvo l'istruzione booleano
    int b=0;                                              //booleano

    if(!(p->symbol[0]>='0' && p->symbol[0]<='9'))         //segnalo se è numero o simbolo (1 = simbolo, 0 = numero)
      b=1;

    /*
    Serve per capire se è un simbolo o un numero.
    while(i<strlen(p->symbol)){
        if(p->symbol[i]>='0' && p->symbol[i]<='9'){
        } else b=1;
        i = i +1;
    }
    */

    //se numero
    if (b==0) {
      int i = 15;
      int n = atoi(p->symbol);
      //calcolo valore binario e salvo in x
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
    }
    else{
      //TODO: se simbolo (Cerco in symbol table)
    }

    strcpy(p->instruction, x);      //copio nell'istruzione vera e propria
}

//FILLER
//serve per comprendere se un comando è A-instr, C-instr o Etichetta e agisce di conseguenza.
command *filler(char *nospace, command* current_parse){
  //capisco quale dellle 3 possibilità è
  if (nospace[0]=='@')
    current_parse->command_type = 'A';
  else if (nospace[0]=='(')
    current_parse->command_type = 'L';
  else
    current_parse->command_type = 'C'; //TODO: insert error message if nospace[0] isnt known (don't need to know it 'cause the control has already been made by the translater)

  //applico
  if (current_parse->command_type=='A') {
      strcpy(current_parse->symbol,++nospace);        //copio l'istr. senza il @ (prima incremento poi copio)
      translateA(current_parse);                      //traduco in comando A
  }
  else if (current_parse->command_type=='C')
    translate(nospace,current_parse);                 //traduco in comando C
  else if (current_parse->command_type=='L') {}       //non faccio nulla
}

//PARSER
//sequenza di istruzioni generali per l'assemblaggio del istruzione in binario
command *parser(char *str) {
  char nospace[200];                                      //istruzione hack
  command *current_parse = malloc(sizeof(command));       //istanzio uno spazio pari a 'command'
  command *trash = malloc(sizeof(command));               //istanzio una nuova variabile in caso sia un comando inutile
                                                          //TODO: vedere se si può evitare l'utilizzo di trash utilizzando una unica variaibile

  trash->instruction[0]='c';                              //Assegno a trash 'c' per identificarlo come commento
  remove_space(nospace, str);                             //rimuove gli spazi
  remove_comment(nospace);                                //rimuove i commenti
  if (nospace[1]=='\0'||nospace[1]=='\n')                 //se l'istr è un commento o riga vuota ritorno trash          CHANGE
    return trash;
                                                          //TODO: non eliminare un commento solo perché presente in una riga.
  //fputs(nospace);
  filler(nospace,current_parse);                          //Vero e proprio assemblaggio del comando hack
  return current_parse;                                   //ritorno l'istruzione binaria
}

//MAIN
int main(int argc, char **argv) {
  FILE *filein, *fileout;           //file di input e output
  command *current;                 //puntatore del comando in questione
  char instr[200]={'\0'};           //riga in questione
  symbol_table st[100];             //symbol table TODO: deve diventare una lista per occupare meno spazio in memoria
                                    //TODO: implementare la lista

  filein = fopen(argv[1], "r");     //assegnazione del file di input
  fileout = fopen(argv[2], "w");    //assegnazione del file di output


  /*int riga = 0:
  while(fgets(instr, sizeof(instr), filein)!=NULL){         //while ci sono righe di grandezza massima 'instr' nel file 'filein'. Se ci sono assegnarle alla variabile (instr).
    if (instr[0]=='(')
      add_simbol(++instr, riga, st);

    riga++;
  }*/

  //SECONDA PASSATA
  //while con fgets e le righe in una lista
  while(fgets(instr, sizeof(instr), filein)!=NULL){         //while ci sono righe di grandezza massima 'instr' nel file 'filein'. Se ci sono assegnarle alla variabile (instr).
      //printf("%s\n", instr);
      current = parser(instr);                              //traduco l'istruzione in binario
      /*if (instr[0] == '\n')
        printf("%s\n", "/n");
      else if (instr[0] == '\0')
        printf("%s\n", "/0");
      else
        printf("first: %c\n", instr[0]);*/
      if (current->instruction[0]!='c'){                    //controllo che l'istruzione non sia un commento
        fprintf(fileout, "%s\n", current->instruction);       //scrivo l'istruzione nel file di output
      }
      //fprintf(fileout, "%s", current->instruction);
      //fprintf(fileout, "%c", '\n');
  }

  fclose(filein);                                           //chiudo file di input
  fclose(fileout);                                          //chiudo file di output
  return (0);
}
