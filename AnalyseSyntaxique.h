
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <AnalyseLexical.h>


// Déclaration des fonctions
void Erreur(Erreurs code);
void Test_Symbole(CODES_LEX cl, Erreurs COD_ERR);
void PROGRAM();
void BLOCK();
void CONSTS();
void VARS();
void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void COND();
void EXPR();
void TERM();
void FACT();
void REPETER();
void POUR();
void CAS();
void Lire_Car();
void Lire_mot();
void Lire_nombre();
void Sym_Suiv();

