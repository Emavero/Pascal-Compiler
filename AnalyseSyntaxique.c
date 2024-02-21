#include <stdio.h>
#include <stdlib.h>
#include<C:\Users\preem\OneDrive\Documents\AnalyseSyntaxique\AnalyseSyntaxique.h>



///////////////////////////////////DEFINITION DE TOUS LES FONCTIONS//////////////////////////////////////

//FONCTION POUR LIRE LE CARACTERE  SUIVANT DU FICHIER
void Lire_Car() {
    Car_Cour = fgetc(fichier);
    if (Car_Cour == '\n')
    ligne++;
}

// FONCTION POUR LIRE UN MOT (IDENTICATEUR OU MOT-CLE)
void Lire_mot(){
    char mot[20];
    int indice=0;

    mot[indice++]=Car_Cour;
    Lire_Car();
    while(isalpha(Car_Cour) || isdigit(Car_Cour)){
        mot[indice++]=Car_Cour;
        Lire_Car();
    }
mot[indice] = '\0';

 if (strcmp(mot, "program") == 0)  {SYM_COUR.CODE = PROGRAM_TOKEN;}
 else {
    if  (strcmp(mot, "const") == 0) {SYM_COUR.CODE = CONST_TOKEN;}
 else { if  (strcmp(mot, "var") == 0) SYM_COUR.CODE = VAR_TOKEN;
 else { if  (strcmp(mot, "Begin") == 0) SYM_COUR.CODE = BEGIN_TOKEN;
 else { if (strcmp(mot, "read") == 0) SYM_COUR.CODE = READ_TOKEN;
 else { if  (strcmp(mot, "while") == 0) SYM_COUR.CODE = WHILE_TOKEN;
 else { if (strcmp(mot, "do") == 0) SYM_COUR.CODE = DO_TOKEN;
else  { if (strcmp(mot, "end") == 0) SYM_COUR.CODE = END_TOKEN;
else  { if  (strcmp(mot, "write") == 0) SYM_COUR.CODE = WRITE_TOKEN;
else{SYM_COUR.CODE=ID_TOKEN;}}}}}}}}}

 strcpy(SYM_COUR.Nom, mot);
 SYM_COUR.ligne = ligne;

}

// FONCTION POUR LIRE UN NOMBRE
void Lire_nombre(){
    char nombre[20];
    int indice=0;

    nombre[indice++]=Car_Cour;
    Lire_Car();
    while(isalpha(Car_Cour)){
        nombre[indice++]=Car_Cour;
        Lire_Car();
    }

    nombre[indice] = '\0';
    SYM_COUR.CODE = NUM_TOKEN;
    strcpy(SYM_COUR.Nom, nombre);
    SYM_COUR.ligne = ligne;
}

//FONCTION POUR PASSER AU SYMBOLE SUIVANT
void Sym_Suiv(){

while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t') {
        if (Car_Cour == '\n')
        ligne++;
        Lire_Car();
    }

//TRAITEMENT SELON LES CATEGORIES

//TRAITEMENT DES MOTS
if(isalpha(Car_Cour))  Lire_mot();
else{
//TRAITEMENT DES NOMBRES
if(isdigit(Car_Cour)) Lire_nombre();
else{
     switch (Car_Cour) {
            // TRAITEMENT DES CARACTERES SPECIAUX
            case ';': SYM_COUR.CODE = PV_TOKEN;strcpy(SYM_COUR.Nom, ";");Lire_Car(); break;
            case '.': SYM_COUR.CODE = PT_TOKEN; strcpy(SYM_COUR.Nom, ".");Lire_Car() ; break;
            case '+': SYM_COUR.CODE = PLUS_TOKEN; strcpy(SYM_COUR.Nom, "+"); Lire_Car(); break;
            case '-': SYM_COUR.CODE = MOINS_TOKEN; strcpy(SYM_COUR.Nom, "-");  Lire_Car(); break;
            case '*': SYM_COUR.CODE = MULT_TOKEN; strcpy(SYM_COUR.Nom, "*");Lire_Car(); break;
            case '/': SYM_COUR.CODE = DIV_TOKEN; strcpy(SYM_COUR.Nom, "/");Lire_Car(); break;
            case ',': SYM_COUR.CODE = VIR_TOKEN; strcpy(SYM_COUR.Nom, ",");Lire_Car(); break;
            case '=': Lire_Car();
                      if (Car_Cour == '=') {
                          SYM_COUR.CODE = EG_TOKEN;
                          strcpy(SYM_COUR.Nom, "==");
                          Lire_Car();
                      } else {
                          SYM_COUR.CODE = AFF_TOKEN;
                          strcpy(SYM_COUR.Nom, "=");
                      }
                      break;
            case ':': Lire_Car();
                          if (Car_Cour == '=') {
                          SYM_COUR.CODE = AFF_TOKEN;
                          strcpy(SYM_COUR.Nom, ":=");
                          Lire_Car();
                      } else {
                          SYM_COUR.CODE = ERREUR_TOKEN;
                          strcpy(SYM_COUR.Nom, "erreur");
                      }
                      break;
            case '<': Lire_Car();
                      if (Car_Cour == '=') {
                          SYM_COUR.CODE = INFEG_TOKEN;
                          strcpy(SYM_COUR.Nom, "<=");
                          Lire_Car();
                      } else {
                          SYM_COUR.CODE = INF_TOKEN;
                          strcpy(SYM_COUR.Nom, "<");
                      }
                      break;
            case '>': Lire_Car();
                      if (Car_Cour == '=') {
                          SYM_COUR.CODE = SUPEG_TOKEN;
                          strcpy(SYM_COUR.Nom, ">=");
                          Lire_Car();
                      } else {
                          SYM_COUR.CODE = SUP_TOKEN;
                          strcpy(SYM_COUR.Nom, ">");
                      }
                      break;
            case '(': SYM_COUR.CODE = PO_TOKEN;strcpy(SYM_COUR.Nom, "(");Lire_Car(); break;
            case ')': SYM_COUR.CODE = PF_TOKEN;strcpy(SYM_COUR.Nom, ")");Lire_Car(); break;
            case EOF: SYM_COUR.CODE = FIN_TOKEN;strcpy(SYM_COUR.Nom, "endF"); break;
            default: SYM_COUR.CODE = ERREUR_TOKEN;strcpy(SYM_COUR.Nom, "erreur");Lire_Car(); break;
        }
}
}
}



//FONCTION POUR LES ERREURS
void Erreur(Erreurs code)
{
    printf("Erreur: %d\n", code);
    printf("Token: %d\n", SYM_COUR.CODE);
    printf("Nom: %s\n", SYM_COUR.Nom);
    printf("Ligne: %d\n", SYM_COUR.ligne = ligne);

    exit(EXIT_FAILURE);
}

//FONCTION POUR TESTER LES ERREURS

void Test_Symbole(CODES_LEX cl, Erreurs  COD_ERR)
{
    if (SYM_COUR.CODE == cl)
    {
        Sym_Suiv();
    }
    else
        Erreur(COD_ERR);
}

// PROGRAM::= program ID ; BLOCK .
void PROGRAM (){

    Test_Symbole(PROGRAM_TOKEN,PROGRAM_ERREUR);
    Test_Symbole(ID_TOKEN,ID_ERREUR);
    Test_Symbole(PV_TOKEN,PV_ERREUR);
    BLOCK();
    Test_Symbole(PT_TOKEN,PT_ERREUR);
}

//BLOCK ::= CONSTS VARS INSTS
void BLOCK(){

  CONSTS();
  VARS();
  INSTS();

  }

//CONSTS ::= const ID = NUM ; { ID = NUM ; } | e
void CONSTS(){

   switch(SYM_COUR.CODE)
   {
   case CONST_TOKEN:
   Sym_Suiv();
   Test_Symbole(ID_TOKEN,ID_ERREUR);
   Test_Symbole(AFF_TOKEN,AFF_ERREUR);
   Test_Symbole(NUM_TOKEN,NUM_ERREUR);
   Test_Symbole(NUM_TOKEN, NUM_ERREUR);
   Test_Symbole(PV_TOKEN,PV_ERREUR);
   while(SYM_COUR.CODE==ID_TOKEN)
   {
       Sym_Suiv();
        Test_Symbole(AFF_TOKEN,AFF_ERREUR);
        Test_Symbole(NUM_TOKEN,NUM_ERREUR);
        Test_Symbole(NUM_TOKEN, NUM_ERREUR);
        Test_Symbole(PV_TOKEN,PV_ERREUR);

   }
   break;
   case VAR_TOKEN : break;

   case BEGIN_TOKEN: break;

   default : Erreur(CONST_VAR_BEGIN_ERR); break;
   }
}

//VARS ::= var ID { , ID } ; | e
void VARS(){

    switch(SYM_COUR.CODE){
      case VAR_TOKEN : Sym_Suiv();
      Test_Symbole(ID_TOKEN,ID_ERREUR);

      while(SYM_COUR.CODE==VIR_TOKEN){
        Sym_Suiv();
        Test_Symbole(ID_TOKEN,ID_ERREUR);
      }
      Test_Symbole(PV_TOKEN,PV_ERREUR); break;

      case BEGIN_TOKEN : break;

      default :Erreur(VAR_BEGIN_ERR);

   }

  }


//INSTS ::= begin INST { ; INST } end
void INSTS(){

  Test_Symbole(BEGIN_TOKEN,BEGIN_ERREUR);
  INST();

  while(SYM_COUR.CODE==PV_TOKEN){
    Sym_Suiv();
    INST();
  }
  Test_Symbole(END_TOKEN,END_ERREUR);

  }


//INST ::= INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
void INST(){

    switch(SYM_COUR.CODE){

    case BEGIN_TOKEN :  INST(); break;

    case ID_TOKEN : AFFEC(); break;

    case IF_TOKEN : SI();break;

    case WHILE_TOKEN : TANTQUE();break;

    case WRITE_TOKEN : ECRIRE();break;

    case READ_TOKEN : LIRE(); break;

    case END_TOKEN : break;

    default:Erreur(INST_ERR); break;

    }
}

//AFFEC ::= ID := EXPR
void AFFEC(){

Test_Symbole(ID_TOKEN,ID_ERREUR);
Test_Symbole(AFF_TOKEN,AFF_ERREUR);
EXPR();

}

//SI ::= if COND then INST
void SI(){
Test_Symbole(IF_TOKEN,IF_ERREUR);
COND();
Test_Symbole(THEN_TOKEN,THEN_ERREUR);
INST();

}

//TANTQUE::= while COND do INST
void TANTQUE(){

Test_Symbole(WHILE_TOKEN,WHILE_ERREUR);
COND();
Test_Symbole(DO_TOKEN,DO_ERREUR);
INST();
}


//ECRIRE ::= write ( EXPR { , EXPR } )
void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN, WRITE_ERREUR);
    Test_Symbole(PO_TOKEN, PO_ERREUR);
    EXPR();

    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        EXPR();
    }

    Test_Symbole(PF_TOKEN, PF_ERREUR);
}

//LIRE ::= read ( ID { , ID } )
void LIRE()
{
    Test_Symbole(READ_TOKEN, READ_ERREUR);
    Test_Symbole(PO_TOKEN, PO_ERREUR);
    Test_Symbole(ID_TOKEN, ID_ERREUR);

    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERREUR);
    }

    Test_Symbole(PF_TOKEN, PF_ERREUR);
}


//COND ::= EXPR [= | <> | < | > | <= | >=] EXPR
void COND()
{
    EXPR();

     switch (SYM_COUR.CODE)
    {
    case AFF_TOKEN: Test_Symbole(AFF_TOKEN, AFF_ERREUR);break;

    case DIFF_TOKEN: Test_Symbole(DIFF_TOKEN,DIFF_ERREUR);break;

    case INF_TOKEN: Test_Symbole(INF_TOKEN,INF_ERREUR);break;

    case SUP_TOKEN: Test_Symbole(SUP_TOKEN,SUP_ERREUR);break;

    case INFEG_TOKEN: Test_Symbole(INFEG_TOKEN,INFEG_ERREUR);break;

    case SUPEG_TOKEN: Test_Symbole(SUPEG_TOKEN,SUPEG_ERREUR);break;

    default :Erreur(COND_ERR) ; break ;
    }

    EXPR();
}


//EXPR ::= TERM { [+ | -] TERM }
void EXPR()
{

    TERM();

    while (SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN)
    {
         switch (SYM_COUR.CODE)
    {
    case PLUS_TOKEN:Test_Symbole(PLUS_TOKEN, PLUS_ERREUR);break;

    case MOINS_TOKEN:Test_Symbole(MOINS_TOKEN, MOINS_ERREUR);break;

    default:
        Erreur(ERREUR_ERR);
        break;
    }
        TERM();
    }
}

//TERM ::= FACT { [* | /] FACT }
void TERM()
{
    FACT();

    while (SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN)
    {
        switch (SYM_COUR.CODE)
    {
    case MULT_TOKEN: Test_Symbole(MULT_TOKEN, MULT_ERREUR);break;

    case DIV_TOKEN:Test_Symbole(DIV_TOKEN, DIV_ERREUR);break;

    default:Erreur(ERREUR_ERR);break;
    }
        FACT();
    }
}

//FACT ::= ID | NUM | ( EXPR )
void FACT()
{
    switch (SYM_COUR.CODE)
    {
    case ID_TOKEN: Test_Symbole(ID_TOKEN, ID_ERREUR);break;

    case NUM_TOKEN:Test_Symbole(NUM_TOKEN, NUM_ERREUR);
    Test_Symbole(NUM_TOKEN, NUM_ERREUR);break;

    case PO_TOKEN:Test_Symbole(PO_TOKEN, PO_ERREUR);
    EXPR();
    Test_Symbole(PF_TOKEN, PF_ERREUR);
    break;

    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

//POUR ::= FOR ID DO:= NUM [INTO|DOWNTO] NUM DO INST
void POUR()
{
    Test_Symbole(FOR_TOKEN,FOR_ERREUR);
    Test_Symbole(ID_TOKEN,ID_ERREUR);
    Test_Symbole(AFF_TOKEN,AFF_ERREUR);

    switch (SYM_COUR.CODE)
    {
    case DOWNTO_TOKEN:
        Test_Symbole(DOWNTO_TOKEN,DOWNTO_ERREUR);
        break;
    case INTO_TOKEN:
        Test_Symbole(INTO_TOKEN,INTO_ERREUR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }

    Test_Symbole(NUM_TOKEN, NUM_ERREUR);
    Test_Symbole(DO_TOKEN, DO_ERREUR);
    INST();

}



//REPETER ::= REPEAT INST UNTIL COND
void REPETER(){
    Test_Symbole(REPEAT_TOKEN, REPEAT_ERREUR);
    INST();
    Test_Symbole(UNTIL_TOKEN, UNTIL_ERREUR);
    COND();
}

//CAS ::= CASE ID OF NUM : INST { NUM: INST} [ELSE INST |e] END
void CAS()
{
    Test_Symbole(CASE_TOKEN, CASE_ERR);
    Test_Symbole(ID_TOKEN, ID_ERREUR);
    Test_Symbole(OF_TOKEN, OF_ERREUR);
    Test_Symbole(NUM_TOKEN, NUM_ERREUR);
    Test_Symbole(DDOT_TOKEN, DDOT_ERR);
    INST();
     while (SYM_COUR.CODE == NUM_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(DDOT_TOKEN, DDOT_ERR);
        INST();
    }
    if (SYM_COUR.CODE == ELSE_TOKEN) {
        Sym_Suiv();
        INST();
    }

    Test_Symbole(END_TOKEN, END_ERREUR);
}

int main()
{
    fichier = fopen("C:/Users/preem/OneDrive/Bureau/program.p", "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // PREMIER_SYM();
    Lire_Car();
    Sym_Suiv();

    PROGRAM();

    printf("------------------------Analyse Syntaxique----------------------------------.\n");

    if (SYM_COUR.CODE == FIN_TOKEN)
    {
        printf("Felicitation votre programme fonctionne correctement\n");
    }
    else
    {
        printf("OUPS:Une ano a ete detecte\n");
        printf("Token: %d\n", SYM_COUR.CODE);
        printf("Nom: %s\n", SYM_COUR.Nom);
        Sym_Suiv();
    }

    fclose(fichier);

    return 0;
}
