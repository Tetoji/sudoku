#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>     // https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9

void gotoXY(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD koords;
    koords.X = x;
    koords.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, koords);
}


int  fields(int grid[9][9], int grid2[9][9], int a)
{
    int row = 0, col = 0;
    printf("\n");
    for ( row = 0; row < 9; row++)
    {
        if(row % 3 == 0 & row != 0)
        {
            printf("  ----------------------- \n");   //Für bessere Darstellung
        }
        printf(" ");
        //Schleife für Spalten, X-Achse
        for ( col = 0; col < 9; col++)
        {
            if(col %3 == 0 && col != 0)
            {
                printf(" | ");  //Für bessere Darstellung
            }
            //Anzeigen der Zahl an der Stelle in Array
            printf(" %d", grid[row][col]);
        }
        printf("\n");
    }
}


int editing(int grid[9][9], int grid2[9][9], int a)
{
    // x = 1 Zeichen von links entfernt
    // y = 1 Zeichen von oben entfernt
    int x = 1, y = 1, c, z = 1;
    printf("\nDruecken Sie [ESC] um Editierung ihres Sudoku zu beenden.");
    gotoXY(x, y); // aufruf das der Cursor an der richtigen Stelle steht

    while (z)
    {
        c = getch();
        switch (c)
        {

        case 75: // linke Pfeiltaste
            x = (--x + 26) % 26;
            if (x == 3 || x == 6 || x == 9 || x == 12 ||
                    x == 15 || x == 18 || x == 21 || x == 24)
                x -= 2;
            if (x == 0)
                x += 25;
            break;

        case 72:  // oben Pfeiltaste
            y = (--y + 12) % 12;
            if (y == 0)
                y += 11;
            if (y == 4 || y == 8)
                y--;
            break;

        case 77: // rechte Pfeiltaste
            x = (++x + 26) % 26;
            if (x == 2 || x == 5 || x == 8 || x == 11 ||
                    x == 14 || x == 17 || x == 20 || x == 23)
                x += 2;
            if (x == 0)
                x++;
            break;

        case 80: // unten Pfeiltaste
            y = (++y + 12) % 12;
            if (y == 4 || y == 8)
                y++;
            if (y == 0)
                y++;
            break;
        case 27: // ESC zum Abbrechen
            z = 0;
            break;
        }
        gotoXY(x, y);


        //Die Nullen ersetzen mit Ziffern von 1 bis 9
        if (c == '1' || c == '2' || c == '3' || c == '4' ||
                c == '5' || c == '6' || c == '7' || c == '8' ||
                c == '9')
        {
            if (((y == 1) && ((grid2[y % 12 - 1][x / 3]) == 0)) || ((y == 2) && ((grid2[y % 12 - 1][x / 3]) == 0)) || ((y == 3) && ((grid2[y % 12 - 1][x / 3]) == 0)))  	//grid(y,x)
            {
                grid[y % 12 - 1][x / 3] = c-48; // c - 48;	//grid(x,y)
                gotoXY(0, 0);
                fields(grid,grid2,a);

            }
            if ((y == 5 && grid2[y % 12 - 2][x / 3] == 0) || (y == 6 && grid2[y % 12 - 2][x / 3] == 0) || (y == 7 && grid2[y % 12 - 2][x / 3] == 0))  	//grid(y,x)
            {
                grid[y % 12 - 2][x / 3] = c - 48;	//grid(x,y)
                gotoXY(0,0);
                fields(grid,grid2,a);
            }
            if ((y == 9 && grid2[y % 12 - 3][x / 3] == 0) || (y == 10 && grid2[y % 12 - 3][x / 3] == 0) || (y == 11 && grid2[y % 12 - 3][x / 3] == 0))  	//grid(y,x)
            {
                grid[y % 12 - 3][x / 3] = c - 48;	//grid(x,y)
                gotoXY(0,0);
                fields(grid,grid2,a);
            }
        }
    }
    return 0;
}


int solvable(int sudoku[9][9])
{
    //sehr unschoen geschriebene funktion zum Pruefen eines Arrays
    int issolvable = 1;
    int value;
    int amount = 0;
    int row = 0;
    int column = 0;

    //Zaehlt von 1-9 und prüft nach der Anzahl der doppelten
    for(value = 1; value < 9; value++)
    {
        //geht von links nach rechts durch die einzelnen Zeilen
        for(row = 0; row < 9; row++)
        {
            for(column = 0; column < 9; column++)
            {
                if(sudoku[row][column]== value)
                {
                    amount++;
                    if(amount > 1)
                    {
                        issolvable = 0;
                    }
                }
            }
            //amount muss Zwischen den Zeilen Zurueckgesetzt werden
            amount = 0;
        }

        //geht von oben nach unten durch die einzelnen Zeilen
        for(column = 0; column < 9; column++)
        {
            for(row = 0; row < 9; row++)
            {
                if(sudoku[row][column] == value)
                {
                    amount++;
                    if(amount > 1)
                    {
                        issolvable = 0;
                    }
                }
            }
            //amount muss Zwischen den Spalten Zurueckgesetzt werden
            amount = 0;
        }


        //muss 1 mal fuer jede Box durchlaufen
        int i;
        int startcol = 0;
        int startrow = 0;
        for(i = 0; i < 9; i++)
        {

            //geht 3*3 Kaestchen fuer 3*3 Kaestchen durch das Array
            //legt startrow und startcol fest
            switch (i)
            {
            case 1:
                startcol = 3;
                break;

            case 2:
                startcol = 6;
                break;

            case 3:
                startcol = 0;
                startrow = 3;
                break;

            case 4:
                startcol = 3;
                break;

            case 5:
                startcol = 6;
                break;

            case 6:
                startcol = 0;
                startrow = 6;
                break;

            case 7:
                startcol = 3;
                break;

            case 8:
                startcol = 6;
                break;

            }

            for (row = 0; row < 3; row++)
            {
                //printf("\nrow = %d", (row+startrow)); // zum Testen
                for (column = 0; column < 3; column++)
                {
                    //printf(" col = %d", (column+startcol)); // zum Testen
                    if (sudoku[row+startrow][column+startcol] == value)
                    {
                        amount++;
                        if(amount > 1)
                        {
                            issolvable = 0;
                        }
                    }
                }
            }
            //printf("\n"); zum Testen
            //amount muss Zwischen den Kaechstchen Zurueckgesetzt werden
            amount = 0;
        }
    }

    return(issolvable);
}

int everythingfilled (int sudoku[9][9])
{
    int r;
    int c;
    int solved = 1;
    for(r = 0; r < 9; r++)
    {
        for(c = 0; c < 9; c++)
        {
            if(sudoku[r][c] == 0)
            {
                solved = 0;
            }
        }
    }
    return(solved);
}


time_t begin, end;  //Um die Zeit zu messen

int seconds = 0;
int minute = 0;
int hour = 0;
int input;

int game(int input)
{
    printf("\n\n Errate die richtige Zahl zwischen 0 und 100\n\n");

    do
    {
        printf("Zahl: ");
        scanf("%d", &input);

        if(input < 0 || input > 100)
        {
            printf("\n !!Bitte geben Sie eine gueltige Zahl ein!! \n\n");
        }
    }
    while (input!= 69);     //Richtige Zahl die zu erraten ist

    printf("\nGlueckwunsch, die richtige Zahl ist 69!\n\n");
}

int timeCount(time_t elapsed)    //Funktionen um die Sekunden, Minuten und Stunden zu errechnen
{
    if(elapsed > 59) //Minuten rechnen
    {
        minute = elapsed / 60;
        seconds = elapsed % 60;    //Rest Sekunden
    }

    if(minute > 59) //Stunden rechnen
    {
        hour = minute / 60;
        minute = minute % 60;   //Rest Minuten
    }
}

int timePrint(time_t elapsed)
{
    if(elapsed < 59)        //Wird benötigt um alles unter einer Minute darzustellen
    {
        if(elapsed > 9)    //Für die korrekte Umrahmung
        {
            printf("Gebrauchte Zeit:        | %ld Std : %ld Min : %ld Sec |\n", hour, minute, elapsed);
        }
        else if(elapsed > 9 && minute > 9)
        {
            printf("Gebrauchte Zeit:        | %ld Std : %ld Min : %ld Sec |\n", hour, minute, elapsed);
        }
        else
        {
            printf("Gebrauchte Zeit:        | %ld Std : %ld Min : %ld Sec |\n", hour, minute, elapsed);
        }
    }

    else    //Wird benötigt um alles über einer Minute darzustellen
    {
        if(seconds > 9)       //Für die korrekte Umrahmung
        {
            printf("Gebrauchte Zeit:        | %ld Std : %ld Min : %ld Sec |\n", hour, minute, seconds);
        }
        else if(elapsed > 9 && minute > 9)
        {
            printf("Gebrauchte Zeit:        | %ld Std : %ld Min : %ld Sec |\n", hour, minute, elapsed);
        }
        else
        {
            printf("Gebrauchte Zeit:        | %ld Std : %ld Min : %ld Sec |\n", hour, minute, seconds);
        }
    }
}


int main()
{
    //Deklarieren des Sudokugrids
    int maxanz = 81;
    int grid[9][9] =
    {
        5, 0, 4, 6, 0, 8, 9, 0, 0,
        6, 7, 0, 0, 0, 0, 0, 0, 0,
        0, 9, 8, 0, 0, 0, 0, 6, 7,
        0, 0, 9, 0, 6, 0, 0, 2, 0,
        4, 0, 0, 8, 5, 3, 0, 0, 1,
        0, 1, 0, 0, 2, 0, 8, 0, 0,
        9, 6, 0, 0, 0, 0, 2, 8, 0,
        0, 0, 0, 0, 0, 0, 0, 3, 5,
        0, 0, 5, 2, 0, 6, 1, 0, 0
    };
    //um die Zahlen zu überschreiben
    int grid2[9][9] =
    {
        5, 0, 4, 6, 0, 8, 9, 0, 0,
        6, 7, 0, 0, 0, 0, 0, 0, 0,
        0, 9, 8, 0, 0, 0, 0, 6, 7,
        0, 0, 9, 0, 6, 0, 0, 2, 0,
        4, 0, 0, 8, 5, 3, 0, 0, 1,
        0, 1, 0, 0, 2, 0, 8, 0, 0,
        9, 6, 0, 0, 0, 0, 2, 8, 0,
        0, 0, 0, 0, 0, 0, 0, 3, 5,
        0, 0, 5, 2, 0, 6, 1, 0, 0
    };

    int sudoku[9][9] =
    {
        { 5, 3, 4, 6, 7, 8, 9, 1, 2 },
        { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
        { 1, 9, 8, 3, 4, 2, 5, 6, 7 },
        { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
        { 4, 2, 6, 8, 5, 3, 7, 9, 1 },
        { 7, 1, 3, 9, 2, 4, 8, 5, 6 },
        { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
        { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
        { 3, 4, 5, 2, 8, 6, 1, 7, 9 }
    };

    printf("---------------------SUDOKU----------------------\n");
    printf("Created by Paulina, Uwe, Brit, Tetje and Abdullah\n\n");
    printf("              Press any key to continue");
    getch();             
    system("clear");        //*nix
    system("cls");          //windows

    time(&begin);   //Anfang des Counters

    fields(grid,grid2,maxanz);
    editing(grid, grid2, maxanz);

    time(&end);     //Stop der Erfassung der Zeit
    time_t elapsed = end - begin;
    timeCount(elapsed);  //Funktion um die Minuten und Stunden zu berechnen
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    timePrint(elapsed);

    if (solvable(sudoku) == solvable(grid))
        printf("\nSolvable");
    else
        printf("\nUnsolvable");
    if (solvable(sudoku) == solvable(sudoku) && everythingfilled(sudoku) == everythingfilled(grid) )
    {
        printf("\nCongratulations you solved it!!");
    }
    else
        printf("You didnt fill it entirely or Made a mistake!");


    printf("\n\n______________________________________________________________________\n");

    return 0;
}