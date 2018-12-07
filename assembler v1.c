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
      if(nospace[2]=='1') strcpy(current_parse->comp,"1110111");
    }
    else if (nospace[1]=='-'){
      if (nospace[2]=='1') strcpy(current_parse->comp,"1110010");
      else if (nospace[2]=='D') strcpy(current_parse->comp,"1000011");
    }
    else strcpy(current_parse->comp,"1110000");
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
            strcpy(current_parse->comp,"00001110");
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
  while(c!=NULL){
    if( *c==d) return 1;
    else c++;
  }
  return 0;
}

void translate(char *nospace, command *current_parse){
  char x='\0'; //if x=d only dest and comp; if x=j only comp and j; if x=l dest,comp,jump
  if (isin(nospace,'=')&&(!isin(nospace,';'))) x='d';
  else if (!(isin(nospace, '=')) && (isin(nospace, ';'))) x='j';
  else if ((isin(nospace, '=')) && (isin(nospace, ';'))) x='l';
  
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

}

command *filler(char *nospace, command* current_parse){
  int i = 1;
  //puts(current_parse->comp);
  if (nospace[0]=='@') current_parse->command_type = 'A';
  else if (nospace[0]=='(') current_parse->command_type = 'L';
  else current_parse->command_type = 'C'; //TODO: insert error message if nospace[0] isnt known
  
  if (current_parse->command_type=='A') strcpy(current_parse->symbol,++nospace); //{while(nospace[i]!='\0') current_parse->symbol=nospace[i]; i++;}
  else if (current_parse->command_type=='C') translate(nospace,current_parse);
  else if (current_parse->command_type=='L') {}
}

command *parser(char *str) {
  char nospace[20];
  command *current_parse = malloc(sizeof(command));
  remove_space(nospace, str);
  //puts(nospace);
  nospace[18] = '\n';
  remove_comment(nospace);
  //fputs(nospace);
  filler(nospace,current_parse);
  puts(current_parse->symbol);
  return current_parse;
}

int main(int argc, char **argv) {
  FILE *filein;
  command *current;
  char instr[20]={'\0'};
  filein = fopen(argv[1], "r");
  //while con fgets e le righe in una lista
  fgets(instr, 20, filein);
  current = parser(instr);
  return 0;
}