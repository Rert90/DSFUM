#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Coduri butoane
const int BTN_NONE   = 0;
const int BTN_RIGHT  = 1;
const int BTN_UP     = 2;
const int BTN_DOWN   = 3;
const int BTN_LEFT   = 4;
const int BTN_SELECT = 5;

// Structura unui produs
struct Produs {
  String nume;
  float pret;
  int stoc;
  int inCos;
};

// Catalog
const int NR_PRODUSE = 5;
Produs produse[NR_PRODUSE] = {
  {"Paine",   5.50, 10, 0},
  {"Lapte",   7.00,  8, 0},
  {"Cafea",  22.50,  5, 0},
  {"Ciocolata", 6.00, 12, 0},
  {"Branza", 39.00, 10, 0}
};

int indexCurent = 0;
bool ecranCheckout = false;

unsigned long ultimulClick = 0;
const unsigned long DEBOUNCE_DELAY = 220;

// Functie care citeste valoarea analogica de pe A0 si identifica butonul
int citesteButon() {
  int val = analogRead(A0);
  if (val > 1000) return BTN_NONE;
  if (val < 60)   return BTN_RIGHT;
  if (val < 200)  return BTN_UP;
  if (val < 400)  return BTN_DOWN;
  if (val < 600)  return BTN_LEFT;
  if (val < 800)  return BTN_SELECT;
  return BTN_NONE;
}

void setup() {
  lcd.begin(16, 2);
  actualizeazaEcran();
}

void loop() {
  if (millis() - ultimulClick < DEBOUNCE_DELAY) {
    return;
  }

  int buton = citesteButon();
  if (buton == BTN_NONE) {
    return;
  }

  ultimulClick = millis();

  // 1. UP  Produs anterior
  if (buton == BTN_UP) {
    if (!ecranCheckout) {
      indexCurent = (indexCurent - 1 + NR_PRODUSE) % NR_PRODUSE;
      actualizeazaEcran();
    }
  }

  // 2. DOWN  Produs urmator
  else if (buton == BTN_DOWN) {
    if (!ecranCheckout) {
      indexCurent = (indexCurent + 1) % NR_PRODUSE;
      actualizeazaEcran();
    }
  }

  // 3. LEFT  Scoate 1 bucata din cos
  else if (buton == BTN_LEFT) {
    if (!ecranCheckout && produse[indexCurent].inCos > 0) {
      produse[indexCurent].inCos--;
      actualizeazaEcran();
    }
  }

  // 4. RIGHT  Adauga 1 bucata in cos
  else if (buton == BTN_RIGHT) {
    if (!ecranCheckout && produse[indexCurent].inCos < produse[indexCurent].stoc) {
      produse[indexCurent].inCos++;
      actualizeazaEcran();
    }
  }

  // 5. SELECT  Afiseaza totalul si scade stocul / Revine la produse
  else if (buton == BTN_SELECT) {
    if (!ecranCheckout) {
      ecranCheckout = true;
      actualizeazaEcran();
      finalizeazaTranzactia();
    } else {
      ecranCheckout = false;
      indexCurent = 0;
      actualizeazaEcran();
    }
  }
}

void actualizeazaEcran() {
  lcd.clear();

  if (!ecranCheckout) {
    // RANDUL 1: Nume produs si Pret
    lcd.setCursor(0, 0);
    lcd.print(produse[indexCurent].nume);
    lcd.print(" ");
    lcd.print(produse[indexCurent].pret, 1);
    lcd.print("L");

    // RANDUL 2: Stoc si Cantitate in cos
    lcd.setCursor(0, 1);
    lcd.print("Stoc:");
    lcd.print(produse[indexCurent].stoc);
    
    lcd.setCursor(9, 1);
    lcd.print("Cos:");
    lcd.print(produse[indexCurent].inCos);
  } else {
    // ECRAN FINALIZARE
    float total = calculeazaTotal();
    
    lcd.setCursor(0, 0);
    lcd.print("TOTAL DE PLATA:");
    
    lcd.setCursor(0, 1);
    lcd.print(total, 2);
    lcd.print(" LEI  [OK]");
  }
}

float calculeazaTotal() {
  float suma = 0;
  for (int i = 0; i < NR_PRODUSE; i++) {
    suma += produse[i].inCos * produse[i].pret;
  }
  return suma;
}

void finalizeazaTranzactia() {
  for (int i = 0; i < NR_PRODUSE; i++) {
    produse[i].stoc -= produse[i].inCos;
    produse[i].inCos = 0;
  }
}