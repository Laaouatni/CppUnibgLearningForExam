#include <stdio.h>

const int MAXAUTO = 20;
const int BYTESIZE = 4;

unsigned int IDVEICOLI[] = {1, 3, 5, 0};
unsigned short SOSTE[] = {3, 12, 1, 2, 5, 20}; 
unsigned int MULTE[MAXAUTO*BYTESIZE];                    

int main() {
    int i = 0;
    int s = 0; 
    int m = 0; 

   
    while (IDVEICOLI[i] != 0) {
        
        unsigned short ingresso = SOSTE[s];     
        unsigned short uscita   = SOSTE[s + 1]; 
        
        int durata = uscita - ingresso;

        bool canAddMulta = durata > 5;

        
        if (canAddMulta) {
            MULTE[m] = IDVEICOLI[i]; // Salva l'ID tra i cattivi
            m++;                     // Spostati alla prossima cella di MULTE
        }

        // Vai avanti per il prossimo veicolo nel prossimo ciclo
        i++;     // Prossimo ID
        s += 2;  // Salta alla prossima coppia di soste (ingresso + uscita)
    }

    MULTE[m] = 0; // Chiudi l'array MULTE con uno 0 come richiesto

    return 0;
}