#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <AnalyseLexical.h>


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


// Fonction pour afficher le code d'un symbole
const char * AfficherToken(CODES_LEX code) {
    switch (code) {
        case EG_TOKEN: return "EG_TOKEN";
        case ID_TOKEN: return "ID_TOKEN";
        case PROGRAM_TOKEN: return "PROGRAM_TOKEN";
        case CONST_TOKEN: return "CONST_TOKEN";
        case VAR_TOKEN: return "VAR_TOKEN";
        case BEGIN_TOKEN: return "BEGIN_TOKEN";
        case END_TOKEN: return "END_TOKEN";
        case IF_TOKEN: return "IF_TOKEN";
        case THEN_TOKEN: return "THEN_TOKEN";
        case WHILE_TOKEN: return "WHILE_TOKEN";
        case DO_TOKEN: return "DO_TOKEN";
        case READ_TOKEN: return "READ_TOKEN";
        case WRITE_TOKEN: return "WRITE_TOKEN";
        case PV_TOKEN: return "PV_TOKEN";
        case PT_TOKEN: return "PT_TOKEN";
        case PLUS_TOKEN: return "PLUS_TOKEN";
        case MOINS_TOKEN: return "MOINS_TOKEN";
        case MULT_TOKEN: return "MULT_TOKEN";
        case DIV_TOKEN: return "DIV_TOKEN";
        case VIR_TOKEN: return "VIR_TOKEN";
        case AFF_TOKEN: return "AFF_TOKEN";
        case INF_TOKEN: return "INF_TOKEN";
        case INFEG_TOKEN: return "INFEG_TOKEN";
        case SUP_TOKEN: return "SUP_TOKEN";
        case SUPEG_TOKEN: return "SUPEG_TOKEN";
        case DIFF_TOKEN: return "DIFF_TOKEN";
        case PO_TOKEN: return "PO_TOKEN";
        case PF_TOKEN: return "PF_TOKEN";
        case FIN_TOKEN: return "FIN_TOKEN";
        case NUM_TOKEN: return "NUM_TOKEN";
        case ERREUR_TOKEN: return "ERREUR_TOKEN";
        case EOF_TOKEN: return "EOF_TOKEN";
        default: return "UNKNOWN_TOKEN";
    }
}

int main() {
    fichier = fopen("C:/Users/preem/OneDrive/Bureau/program.p", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    Lire_Car();
    printf("---------------------------Analyse Lexical--------------------------:\n");
    do {
        Sym_Suiv();
        if (SYM_COUR.CODE != FIN_TOKEN && SYM_COUR.CODE != EOF_TOKEN) {
            printf("%s\t  %s\t\t  Ligne: %d\t\n", AfficherToken(SYM_COUR.CODE), SYM_COUR.Nom, SYM_COUR.ligne);
        }
    } while (SYM_COUR.CODE != FIN_TOKEN && SYM_COUR.CODE != EOF_TOKEN);

    fclose(fichier);

    return 0;
}
