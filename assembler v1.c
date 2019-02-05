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
  if(nospace[0]=='0') strcpy(current_parse->comp,"0101010");
  if(nospace[0]=='1') strcpy(current_parse->comp,"0111111");
  if(nospace[0]=='-') {
    if (nospace[1]=='1') strcpy(current_parse->comp,"0111010");
    else if (nospace[1]=='A') strcpy(current_parse->comp,"0110011");
    else if (nospace[1]=='D') strcpy(current_parse->comp,"0001111");
    else if (nospace[1]=='M') strcpy(current_parse->comp,"1110011");
  }
  if(nospace[0]=='A'){
    if(nospace[1]=='+') {
      if(nospace[2]=='1') strcpy(current_parse->comp,"0110111");
    }
    else if (nospace[1]=='-'){
      if (nospace[2]=='1') strcpy(current_parse->comp,"0110010");
      else if (nospace[2]=='D') strcpy(current_parse->comp,"0000011");
    }
    else strcpy(current_parse->comp,"0110000");
  }
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
    }else if(nospace[1]=='-'){
        if(nospace[2]=='1'){
            strcpy(current_parse->comp,"0001110");
        }
        if(nospace[2]=='A'){
            strcpy(current_parse->comp,"0000011");
        }
        if(nospace[2]=='M'){
            strcpy(current_parse->comp,"1010011");
        }
    }else if(nospace[1]=='&'){
        if(nospace[2]=='A'){
            strcpy(current_parse->comp,"0000000");
        }
        if(nospace[2]=='M'){
            strcpy(current_parse->comp,"1000000");
        }
    }else if(nospace[1]=='|'){
        if(nospace[2]=='A'){
            strcpy(current_parse->comp,"0010101");
        }
        if(nospace[2]=='M'){
            strcpy(current_parse->comp,"1010101");
        }
    } else {
        strcpy(current_parse->comp,"0001100");
    }
}
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
if(nospace[0]=='M'){
    if(nospace[1]=='+'){
        if(nospace[2]=='1'){
            strcpy(current_parse->comp,"1110111");
        }
    }else if(nospace[1]=='-'){
        if(nospace[2]=='1'){
            strcpy(current_parse->comp,"1110010");
        }
        if(nospace[2]=='D'){
            strcpy(current_parse->comp,"1000111");
        }
    }else {
        strcpy(current_parse->comp,"1110000");
    }
}
}

void traduci_dest(char *nospace, command *current_parse){
if(nospace[0] == 'n'  && nospace[1]== 'u' && nospace[2] == 'l' && nospace[3] == 'l'){
    strcpy(current_parse->dest, "000");
}
if(nospace[0]=='M'){
    if(nospace[1] == 'D'){
        strcpy(current_parse->dest,"011");
    } else {
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
        } else {
            strcpy(current_parse->dest,"101");
        }
    } else if(nospace[1]=='D'){
        strcpy(current_parse->dest,"110");
    } else{
        strcpy(current_parse->dest,"100");
    }
}
}

void traduci_jump(char *nospace, command *current_parse){
  if(nospace[0] == 'n'  && nospace[1]== 'u' && nospace[2] == 'l' && nospace[3] == 'l'){
    strcpy(current_parse->jump, "000");
  }
  if(nospace[0] == 'J'){
    if(nospace[1]=='G'){
        if(nospace[2]=='T'){
            strcpy(current_parse->jump,"001");
        } else {
            strcpy(current_parse->jump,"011");
        }
    } else if(nospace[1] == 'E'){
        strcpy(current_parse->jump,"010");
    } else if(nospace[1] == 'L'){
        if(nospace[2] == 'E'){
            strcpy(current_parse->jump,"110");
        } else {
            strcpy(current_parse->jump,"100");
        }
    } else if(nospace[1] == 'M'){
        strcpy(current_parse->jump,"111");
    } else {
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

void translate(char *nospace, command *current_parse){

  char x='\0'; //if x=d only dest and comp; if x=j only comp and j; if x=l dest,comp,jump
  if (isin(nospace,'=')&&(1-isin(nospace,';'))) x='d';
  else if ((1-(isin(nospace, '='))) && (isin(nospace, ';'))) x='j';
  else if ((isin(nospace, '=')) && (isin(nospace, ';'))) x='l';
  
  char y[4]={'1','1','1','\0'};
  strcpy(current_parse->dest,"000");
  strcpy(current_parse->jump,"000");

  if(x=='d') {
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
  }
  strcat(current_parse->instruction, y);
  strcat(current_parse->instruction, current_parse->comp);
  strcat(current_parse->instruction, current_parse->dest);
  strcat(current_parse->instruction, current_parse->jump);
  current_parse->instruction[16]='\0';
  
}

void translateA(command *p){
    char x[17];
    int i=15;
    int b=0;
    while(i<strlen(p->symbol)){
        if(p->symbol[i]>='0' && p->symbol[i]<='9'){
        } else b=1;
        i = i +1;
    }
    if (b==0) {
      
      int n = atoi(p->symbol);
      while (n > 0)
      {
        if (n % 2 == 0)
          x[i] = '0';
        else
          x[i] = '1';
        n = n / 2;
        i--;
        }
        while(i>0){
            x[i] = '0';
            i--;
        }
        x[i]='0';
    }
    strcpy(p->instruction, x);
}

command *filler(char *nospace, command* current_parse){
  int i = 1;
  if (nospace[0]=='@') current_parse->command_type = 'A';
  else if (nospace[0]=='(') current_parse->command_type = 'L';
  else current_parse->command_type = 'C'; //TODO: insert error message if nospace[0] isnt known
  
  if (current_parse->command_type=='A') {
      strcpy(current_parse->symbol,++nospace);
      translateA(current_parse);
  }
  else if (current_parse->command_type=='C') translate(nospace,current_parse);
  else if (current_parse->command_type=='L') {}
}

command *parser(char *str) {
  char nospace[200];
  command *current_parse = malloc(sizeof(command));
  command *trash = malloc(sizeof(command));
  trash->instruction[0]='c';
  remove_space(nospace, str);
  remove_comment(nospace);
  if (nospace[0]=='\0'||nospace[0]=='\n') return trash;
  //fputs(nospace);
  filler(nospace,current_parse);
  return current_parse;
}

int main(int argc, char **argv) {
  FILE *filein, *fileout;
  command *current;
  char instr[200]={'\0'};
  filein = fopen(argv[1], "r");
  fileout = fopen(argv[2], "w");
  while(fgets(instr, sizeof(instr), filein)!=NULL){
      current = parser(instr);
      if (current->instruction[0]!='c'){
      fprintf(fileout, "%s\n", current->instruction);
      }
      //fprintf(fileout, "%s", current->instruction);
      //fprintf(fileout, "%c", '\n');
  }
  fclose(filein);
  fclose(fileout);
  return (0);
}