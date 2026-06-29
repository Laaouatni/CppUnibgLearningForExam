#include <iostream>
#include <cstring>

const int SUCCESS = NULL; // NULL è 0
const int ERROR = -1;

struct VERBALE {
  char codice[16];
  char dataVerbalizzazione[11];
  char dataAppelloEsame[11];
  char dataSuperamentoEsame[11];
  char codiceInsegnamento[11];
  char nomeDocente[51];
  char matricolaStudente[8];
  int voto;
}

struct NODO {
  VERBALE dato;
  NODO* next;
};

void insTesta(NODO* &head, VERBALE dato) {
  NODO* t = new NODO;

  bool isRamPiena = (t == NULL);
  if(isRamPiena) return ERROR;

  t->head = head;
  t->dato = dato;

  head = t;

  return SUCCESS;
}

/* void calcolaConteggi(NODO *lista, char* listaInsegnamenti, int conteggi[], int size) {
  for(NODO *p = lista; p != NULL; p = p->next) {
    char* thisListaInsegnamento = p->dato.codiceInsegnamento;
    for(int i=0; i<size; i++) {
      char* thisForInsegnamento = listaInsegnamenti[i];
      bool isFound = strcmp(thisListaInsegnamento, thisForInsegnamento) == 0;
      if(!isFound) continue;

      conteggi[i]++;
    }
  }
}

int indexMinIns(int conteggi[], int size) {
  int minValue = conteggi[0];
  int minIndex = 0;

  for(int i=1; i<size; i++) {
    const int thisConteggio = conteggi[i];
    bool isSmaller = thisConteggio < minValue;

    if(!isSmaller) continue;

    minValue = thisConteggio;
    minIndex = i;
  }

  return minIndex;
}

 */