/* 
 * File:   functions.h
 * Author: noemurr
 *
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H



#endif	/* FUNCTIONS_H */

#include <iostream>
#include <stdio.h>
#include <math.h>

#define END_SUCCESS 0;
#define END_FAILED -1;
using namespace std;

/* costanti necessarie */
const int MAX_BYTE = 1024; // numero massimo di byte criptabili in una volta.
const int MAX_ROWS = 1024; // numero massimo di righe per ogni colonna

const int MAX_COLS = 200; // numero massimo di colonne della tabella 
                         // nonchè numero massimo di caratteri della parola chiave.

const int MAX_ASTERISKS = 30; // numero massimo di asterischi per la barra di avanzamento
const int ASTERISKS_INCREASE = MAX_ASTERISKS / 10; //numero di asterischi da stampare.

/* dichiarazione delle strutture necessarie al programma */
struct table{
    // dati
    char key;
    char column[MAX_ROWS];
    int numberOfRows;
};
/* fine dichiarazione delle strutturre */

/* prototipizzazione delle funzioni necessarie */
size_t file_size(FILE* fp); // la funzione restituisce come dati la 
                         // dimensione in byte di un file (passato come parametro)
                         // attenzione il file deve essere gia stato aperto.

void tableSort(table gridToSort[], int cols); // ordina un array di table secondo l'ordine alfabetico
                                    // della chiave.

void initializeTable(table grid[], int cols); // inizializza i valori delle griglie per evitare 
                                    // che questi contengano valori casuali

void sortTableWithKey(table grid[],table newGrid[],char key[],int cols); // funzione che ordina la chiave come 
                                                                         // è stata inserita dall'utente.

long int cycles_counter(FILE *inFile); // la funzione calcola i cicli che saranno necessari
                                  // per la cifratura o la decifratura del file.

bool cript(FILE* inFile,FILE* outFile,char key[],int cols); // funzione che cripta il file.

bool decript(FILE* inFile,FILE* outFile,char key[],int cols); // funzione che decripta il file.
/* fine dei prototipi delle funzioni necessarie */