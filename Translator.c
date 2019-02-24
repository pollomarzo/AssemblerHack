#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//SYMBOOL TABLE
typedef struct symbol_table{
    char instruction[20];
    char special[20];
    int num;
} symbol;

//COMMAND
//Le informazioni di un comando vm
typedef struct command{
    char instr[2000];
    char type[2000];
    int number;
} command;

//SEARCH SYMBOL
//ricerca simbolo nella symbol table
symbol* search_symbol (char* symb, symbol* s){
    for (;strcmp(s->instruction, "END_OF_SYMBOL_TABLE") != 0; s++){         //finchè non arrivo alla fine del array
        if (strcmp(s->instruction, symb) == 0)                              //Se instruction corrisponde allora ritorna numero
            break;
    }
    return s;                                                        //ritorna num negativo (non ho trovato la stringa)
}

//POP
//costruisce la stringa dei comandi 'pop'
void pop_cmd (int numero, char* segment, char istruzione[200], symbol *st){
    char num[7];
    symbol *tipo;
    
    sprintf(num, "%d", numero);
    tipo = search_symbol(segment, st);
    
    switch(tipo->num){
        case 1:                                       //LOCAL
        case 2:                                       //ARGUMENT
        case 3:                                       //THAT
        case 4:                                       //THIS
        case 5: {                                     //TEMP
            strcat(istruzione, "@");
            strcat(istruzione, tipo->special);
            strcat(istruzione, "\nD=M\n@");
            strcat(istruzione, num);
            strcat(istruzione, "\nD=D+A\n");
        }break;
            
        case 6: {                                     //POINTER
            strcat(istruzione, "@");
            if (strcmp(num, "0") == 0)
                strcat(istruzione, "THIS");
            else
                strcat(istruzione, "THAT");
            strcat(istruzione, "\nD=A\n");
        }break;
            
        case 7: {                                     //STATIC
            strcat(istruzione, "@");
            strcat(istruzione, tipo->special);
            strcat(istruzione, "_");
            strcat(istruzione, num);
            strcat(istruzione, "\nD=A\n");
        }break;
            
    }
    
    strcat(istruzione, "@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n");
}

//PUSH
//costruisce la stringa dei comandi 'push'
void push_cmd (int numero, char* segment, char istruzione[2000], symbol *st){    char num[7];
    symbol *tipo;
    
    tipo = search_symbol(segment, st);
    
    sprintf(num, "%d", numero);
    
    switch(tipo->num){
        case 0:{                                      //COSTANT
            strcat(istruzione, "@");
            strcat(istruzione, num);
            strcat(istruzione, "\nD=A\n");
        }break;
            
        case 1:                                       //LOCAL
        case 2:                                       //ARGUMENT
        case 3:                                       //THAT
        case 4:                                       //THIS
        case 5: {                                     //TEMP
            strcat(istruzione, "@");
            strcat(istruzione, tipo->special);
            strcat(istruzione, "\nD=M\n@");
            strcat(istruzione, num);
            strcat(istruzione, "\nA=D+A\nD=M\n");;
        }break;
            
        case 6: {                                     //POINTER
            strcat(istruzione, "@");
            if (strcmp(num, "0") == 0)
                strcat(istruzione, "THIS");
            else
                strcat(istruzione, "THAT");
            strcat(istruzione, "\nD=M\n");
        }break;
            
        case 7: {                                     //STATIC
            strcat(istruzione, "@");
            strcat(istruzione, tipo->special);
            strcat(istruzione, "_");
            strcat(istruzione, num);
            strcat(istruzione, "\nD=M\n");
        }break;
            
        default:{
            istruzione[0] = '\0';
        }
    }
    
    strcat(istruzione, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
}

//ARITHEMTIC
//costruisce la stringa dei comandi aritmetici
void arithmetic (char istruzione[2000], char* s1, char* t, char* s2){
    strcat(istruzione, s1);
    strcat(istruzione, t);
    strcat(istruzione, s2);
}


//FUNCTIONDEF
//costruisce la definizione di una funzione
void function(char istruzione[2000], command *current){
    strcat(istruzione, "(");
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
//definisce il richiamo delle funzioni
void call(char istruzione[2000], command *current, int *n){
    char c[4] = "\0\0\0\0";
    char p[4] = "\0\0\0\0";
    sprintf(p, "%d", current->number);
    sprintf(c, "%d", *n);
    strcpy(istruzione, "@SP\nD=M\n@R13\nM=D\n@RETURN-");
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
//descrive la stringa del ritorno da funzione
void funcreturn(char istruzione[2000]){
    strcat(istruzione, "@LCL\nD=M\n@5\nA=D-A\nD=M\n@R13\nM=D\n@SP\nA=M-1\nD=M\n@ARG\nA=M\nM=D\nD=A+1\n@SP\nM=D\n@LCL\nAM=M-1\nD=M\n@THAT\nM=D\n@LCL\nAM=M-1\nD=M\n@THIS\nM=D\n@LCL\nAM=M-1\nD=M\n@ARG\nM=D\n@LCL\nA=M-1\nD=M\n@LCL\nM=D\n@R13\nA=M\n0;JMP\n\0");
}

//BOOLEAN
//costruisce la stringa dei comandi booleani
void boolean (char istruzione[2000], char* s, int* n){
    char num[6] = "\0";
    sprintf(num, "%d", *n);                                 //conversione in stringa
    
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
void inizialize_symbol_table(symbol* st, char* currFileName){
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
    add_symbol ("constant", "\0", 0, st++);
    add_symbol ("local", "LCL", 1, st++);
    add_symbol ("argument", "ARG", 2, st++);
    add_symbol ("that", "THAT", 3, st++);
    add_symbol ("this", "THIS", 4, st++);
    add_symbol ("temp", "R5", 5, st++);
    add_symbol ("pointer", "\0", 6, st++);
    add_symbol ("static", currFileName, 7, st++);
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
void remove_comment(char str[2000]) {
    char c = '/';
    int i=0;
    while (i < 2000) {
        if (str[i] == c || str[i] == '\n' || str[i] == '\r')
            str[i] = '\0';
        i = i + 1;
    }
}

//EXECUTE
//riconosce il tipo di istruzione e lo traduce
void execute(FILE *fileout, command *current, symbol *st, int *n){
    symbol *tipo;
    char num[6] = "\0";
    char istruzione[2000] = "\0";
    
    tipo = search_symbol(current->instr, st);
    
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
            
        case 3:{                    //POP
            pop_cmd(current->number, current->type, istruzione, st);
        }break;
            
        case 4:{                    //PUSH
            push_cmd(current->number, current->type, istruzione, st);
        }break;
            
        case 5:{                    //LABEL
            strcat(istruzione, "(");
            strcat(istruzione, current->type);
            strcat(istruzione, ")\n");
        }break;
            
        case 6:{                    //GOTO
            strcat(istruzione, "@");
            strcat(istruzione, current->type);
            strcat(istruzione, "\n");
            strcat(istruzione, "0;JMP\n");
        }break;
            
        case 7:{                    //IF-GOTO
            strcat(istruzione, "@SP\n");
            strcat(istruzione, "AM=M-1\n");
            strcat(istruzione, "D=M\n");
            strcat(istruzione, "@");
            strcat(istruzione, current->type);
            strcat(istruzione, "\n");
            strcat(istruzione, "D;JNE\n");
        }break;
            
        case 8:{                    //FUNCTION
            function(istruzione, current);
        }break;
            
        case 9:{                    //CALL
            call(istruzione, current, n);
        }break;
            
        case 10:{                   //RETURN
            funcreturn(istruzione);
        }break;
            
        case -1:
        default: printf("ERROR!\n");
    }
    
    fprintf(fileout, "%s", istruzione);
}

//FILLER
void filler(char* nospace, command* current_parse){        //written like this so that "  push \t   constant \t\t 9   " creates no problem
    int J = 0;
    char numero[20]={'\0'};                                 //empty str
    char word[20] = {'\0'};
    
    memset(current_parse->instr, 0, 2000);
    memset(current_parse->type, 0, 2000);
    
    //Inizialing command variables
    strcpy(current_parse->instr, "\0");                           //initialize correctly to avoid problems
    strcpy(current_parse->type, "\0");
    current_parse->number = -1;                               //I hope I'm allowed to do this

    for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
    fill(nospace, current_parse->instr);          //copying the instruction
    for(;*nospace != ' ' && *nospace != '\t' && *nospace != '\0'; nospace++){}
    
    for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
    fill(nospace, current_parse->type);           //copying the type
    for(;*nospace != ' ' && *nospace != '\t' && *nospace != '\0'; nospace++){}
    
    for(;*nospace == ' ' || *nospace == '\t'; nospace++){}                                        //removing extra spaces
    fill(nospace, numero);                                        //copying the number
    if (numero[0] >= '0' && numero[0] <= '9'){                      //controllo che sia un numero non negativo
        j = atoi(numero);
        if(j >= 0)                                                //if numero is a number
            current_parse->number = j;                                  //coping the number
    }
    
}

//PARSER
//prepara le variabili e l'istruzione da tradurre
command *parser(char *c){
    char nospace[2000];
    
    remove_comment(c);                                      //rimuove i commenti
    strcpy(nospace,c);
    command *current_parse = malloc(sizeof(command));       //istanzio uno spazio pari a 'command'
    command *trash = malloc(sizeof(command));               //istanzio una nuova variabile in caso sia un comando inutile
    trash->instr[0]='\0';
    trash->type[0]='\0';
    
    filler(nospace, current_parse);
    return current_parse;                                   //ritorno il puntatore
}

int main(int argc, char **argv){
    FILE *filein, *fileout;
    command *current;
    symbol table[30];
    int n = 0;
    //Stack *stack;
    char instr[2000]="\0";           //riga in questione
    
    
    filein = fopen(argv[1], "r");     //assegnazione del file di input
    fileout = fopen(argv[2], "w");    //assegnazione del file di output
    inizialize_symbol_table(table, argv[1]);   //inizializza la symbol table
    fprintf(fileout, "%s", "@256\nD=A\n@SP\nM=D\n");
    while(fgets(instr, sizeof(instr), filein)!=NULL){         //while ci sono righe di grandezza massima 'instr' nel file 'filein'. Se ci sono assegnarle alla variabile (instr).
        current = parser(instr/*, stack*/);
        execute (fileout, current, table, &n);

        n++;
    }
    return 0;
}
