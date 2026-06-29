#include <cstring> // strcmp
#include <cstdlib> // atoi

const int SUCCESS = 0;
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
};

struct NODO {
  VERBALE dato;
  NODO* next;
};

int insTesta(NODO* &head, VERBALE dato) {
  NODO* t = new NODO;

  bool isRamPiena = (t == NULL);
  if(isRamPiena) return ERROR;

  t->next = head;
  t->dato = dato;

  head = t;

  return SUCCESS;
}

int estraiValore(char* dataString, int inizio, int len) {
  char buffer[len+1];

  for(int i=0; i<len; i++) {
    char thisChar = dataString[inizio+i];
    buffer[i] = thisChar;
  }

  buffer[len] = '\0';
  return atoi(buffer);
}

bool isMeseAnnoEqual(char *firstDate, char *secondDate) {
  int mesePrimaData = estraiValore(firstDate, 5,2);
  int meseSecondaData = estraiValore(secondDate, 5,2);
  int annoPrimaData = estraiValore(firstDate, 0, 4);
  int annoSecondaData = estraiValore(secondDate, 0,4);

  bool isStessoMese = mesePrimaData == meseSecondaData;
  bool isStessoAnno = annoPrimaData == annoSecondaData;

  return isStessoMese && isStessoAnno;
}

void contaApelliStessaData(NODO* lista, char* insegnamenti[], int conteggi[], int size) {
  for(NODO *p = lista; p != NULL; p = p->next) {
    for(int i=0; i<size; i++) {
      char* thisInsegnamento = insegnamenti[i];

      bool isSameCodice = strcmp(thisInsegnamento, p->dato.codiceInsegnamento) == 0;
      if(!isSameCodice) continue;

      bool isStessoMeseAnno = isMeseAnnoEqual(p->dato.dataVerbalizzazione, p->dato.dataAppelloEsame);
      if(!isStessoMeseAnno) continue;

      conteggi[i]++;
    }
  }
}

int trovaIndexMenoVerbali(int conteggi[], int size) {
  int minValue = ERROR;
  int minIndex = ERROR;

  for(int i=0; i<size; i++) {
    int thisConteggio = conteggi[i];
    if(thisConteggio == 0) continue;

    bool isFirstTime = minIndex == -1;
    bool isMinoreThanBefore = thisConteggio < minValue;
    
    bool canChangeValue = isFirstTime || isMinoreThanBefore;

    if(!canChangeValue) continue;
    
    minValue = thisConteggio;
    minIndex = i;
  }

  return minIndex;
}

void initArray(int paramArray[], int value, int size) {
  for(int i=0; i<size; i++) {
    paramArray[i] = value;
  }
}

NODO* copiaVerbaliDataAppelloMesiSuccessivi(NODO* listaIn, char* paramInsegnamento) {
  NODO* listaOut = NULL;

  for(NODO *p = listaIn; p != NULL; p = p->next) {
    bool hasWantedInsegnamento = strcmp(p->dato.codiceInsegnamento, paramInsegnamento) == 0;
    if(!hasWantedInsegnamento) continue;

    int meseDataAppello = estraiValore(p->dato.dataAppelloEsame, 5, 2);
    int meseDataVerbalizzazione = estraiValore(p->dato.dataVerbalizzazione, 5,2);
    int annoDataAppello = estraiValore(p->dato.dataAppelloEsame, 0, 4);
    int annoDataVerbalizzazione = estraiValore(p->dato.dataVerbalizzazione, 0, 4);

    bool isSameAnno = annoDataAppello == annoDataVerbalizzazione;
    if(!isSameAnno) continue;

    bool canInsTesta = meseDataVerbalizzazione > meseDataAppello;
    if(!canInsTesta) continue;

    if(insTesta(listaOut, p->dato) == ERROR) return NULL;
  }

  return listaOut;
}

NODO* VerbaliMeseDiverso(NODO* listaIn, char* insegnamenti[], int size) {
  if(size<=0) return NULL;

  int conteggi[size];
  initArray(conteggi, 0, size);
  contaApelliStessaData(listaIn, insegnamenti, conteggi, size);

  int indexMenoVerbali = trovaIndexMenoVerbali(conteggi, size);
  if(indexMenoVerbali == ERROR) return NULL;

  char* selectedInsegnamento = insegnamenti[indexMenoVerbali];

  NODO* listaOut = copiaVerbaliDataAppelloMesiSuccessivi(listaIn, selectedInsegnamento);
  return listaOut;
}