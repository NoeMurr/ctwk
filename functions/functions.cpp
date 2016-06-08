/* 
 * file di implementazione del file header functions.h
 */

#include "functions.h"

size_t file_size(FILE* fp){
    // funzione che ritorna la dimensione del file.
    // il file deve essere gia stato aperto.
    size_t size;
    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    
    return size;   
}

void initializeTable (table grid[], int cols){
    // la funzione inizializzera i valori di:
    // key = '';
    // numberOfRows = 0;
    // tutti gli elementi di column = '';
    
    for (int i = 0; i<cols;i++){
        grid[i].key = '\0';
        grid[i].numberOfRows = 0;
        for (int j = 0; j<MAX_ROWS;j++)
            grid[i].column[j] = '\0';
    }
    return;
}

void tableSort(table gridToSort[], int cols){
    /* si sceglie di utilizzare l'insertion sort per ordinare anche le lettere uguali nell'ordine in cui erano disposte inizialmente */
    table value;
    int j = 0;
    for(int i = 1;i<cols;i++){
        value = gridToSort[i];
        j = i-1;
        while(j >= 0 && gridToSort[j].key > value.key){
            gridToSort[j+1] = gridToSort[j];
            j--;
        }
        gridToSort[j+1] = value;
    }
}

void sortTableWithKey(table grid[],table newGrid[],char key[],int cols){
    
    // riempimento delle chiavi.
    for(int i = 0;i<cols;i++)
        newGrid[i].key = key[i];
    
    for(int i = 0;i<cols;i++){
        for(int j = 0; j<cols;j++){
            if(grid[i].key == newGrid[j].key){
                    newGrid[j] = grid[i];
            
                while(grid[i+1].key == grid[i].key){
                    for(int k = j+1;k<cols;k++){
                        if(grid[i+1].key == newGrid[k].key){
                            newGrid[k] = grid[i+1];
                            j = k;
                            break;
                        }
                    }
                    i++;
                }
                break;
            }
        }
    }
}

long int cycles_counter(FILE * inFile){
    // memorizza la dimensione in byte del file:
    size_t size = file_size(inFile);
    
    // divide la dimensione del file per il numero massimo di byte cifrati in una volta
    // arrotondando per eccesso ottenenendo così il numero di cicli.
    long int numberOfCycles = ceil(long(size) / MAX_BYTE);
    
    return numberOfCycles;
}

bool cript(FILE* inFile,FILE* outFile,char key[],int cols){
    // dichiarazione ed inizializzazione della griglia
//    cout << "\nInizio cifratura del file. L'operazione potrebbe richiedere alcuni minuti.\n";
    table grid[cols];
  
    /*
     * il file deve essere criptato un kilobyte alla volta quindi: 
     * creo un buffer in grado di contenere 1024 byte. 
     * finche il file non è finito: 
     *      leggo 1024 byte dal file;
     *      li inserisco byte per byte nella tabella;
     *      ordino la tabella;
     *      estraggo i byte e li scrivo sul file criptato.
     */
    
    // riempimento delle colonne
    int count = 0;
    
    char buff[MAX_BYTE];
    int n = 0;
    
    // calcoli per la barra di avanzamento.
    const long int CYCLES_PER_ASTERISKS = ceil(cycles_counter(inFile) / 10);
    int cyclesCounter = 0;
    int perCent = 0;
    while(!feof(inFile)){
        
        // cifratura vera e propria
        if(!(n = fread(&buff[0],sizeof(char),MAX_BYTE,inFile)))
            break;
        else{
            // barra di avanzamento
            cyclesCounter++;
            if(cyclesCounter == CYCLES_PER_ASTERISKS){
                cyclesCounter = 0;
                perCent++;
                for(int i = 0; i< (ASTERISKS_INCREASE * perCent);i++){
                    cout << "*";
                }
                cout << perCent * 10<< "%\n";
            }
            
            // inizializzo la tabella in modo da svuotarla dai byte
            // precedenti.
            initializeTable(grid, cols);
            for(int i = 0;i<cols;i++)
                grid[i].key = key[i];

            int i = 0;
            int row = 0, col = 0;
            while(i < n){
                grid[col].column[row] = buff[i];
                grid[col].numberOfRows++;
                col++;
                i++;
                if(col == cols){
                    col = 0;
                    row++;
                }
            }  
            // ordino la tabella;
            tableSort(grid,cols);
            // inserisco i dati nel file di output;
            for(int i = 0;i<cols;i++){
                for (int j =0;j<grid[i].numberOfRows;j++){
                    if(!fwrite(&grid[i].column[j],sizeof(grid[i].column[j]),1,outFile)){
                        cout << "error encryption failed\n";
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool decript(FILE* inFile,FILE* outFile,char key[],int cols){
//    cout << "\nInizio decifratura del file. L'operazione potrebbe richiedere alcuni minuti.\n";
    // dichiarazione ed inizializzazione della griglia
    table grid[cols];
    initializeTable(grid, cols);
    
    /*
     * Il file deve essere decriptato un kilobyte alla volta quindi:
     * 
     */

    /* riempimento della tabella */

    // riempimento delle chiavi.
    for(int i = 0;i<cols;i++)
        grid[i].key = key[i];
        
    char buff[MAX_BYTE];
    int n = 0;
    
     // calcoli per la barra di avanzamento.
    const int CYCLES_PER_ASTERISKS = ceil(cycles_counter(inFile) / 10);
    int cyclesCounter = 0;
    int perCent = 0;
    
    while(!feof(inFile)){
         // barra di avanzamento
        cyclesCounter++;
        if(cyclesCounter == CYCLES_PER_ASTERISKS){
            cyclesCounter = 0;
            perCent++;
            for(int i = 0; i< (ASTERISKS_INCREASE * perCent);i++){
                cout << "*";
            }
            cout << perCent * 10<< "%\n";
        }
        
        // decifratura vera e propria;
        if(!(n = fread(&buff[0],sizeof(char),MAX_BYTE,inFile))){
            break;
        }
        
        // inizializzo la tabella per eliminare altri byte gia presenti.
        initializeTable(grid, cols);
        for(int i = 0;i<cols;i++)
            grid[i].key = key[i];
        
        int col = 0;
        for(int i = 0;i<n;i++){
            if(col >= cols){
                col = 0;
            }
            grid[col].numberOfRows++;
            col++;
        }
        
        // ordino la tabella.
        tableSort(grid, cols);
        
        //inserisco i dati nella tabella.
        col = 0;
        int row = 0;
        for(int j = 0;j<n;j++){
            if(row >= grid[col].numberOfRows){
                    row = 0;
                    col++;
                }
                grid[col].column[row] = buff[j];
                row++;
        }
        table newGrid[cols];
        initializeTable(newGrid, cols);
        sortTableWithKey(grid,newGrid,key,cols);
        
        for(int i = 0;i<newGrid[0].numberOfRows;i++){
            for(int j = 0;j<cols;j++){
                if(i < newGrid[j].numberOfRows){
                    buff[0] = newGrid[j].column[i];
                    fwrite(&buff[0],sizeof(char),1,outFile);
                }
            }
        }
    }
    return true;
}