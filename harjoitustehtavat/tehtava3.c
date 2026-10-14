/*
Laajenna edellisen tehtävänannon ohjelmaa siten, että ohjelma tallentaa vi-
imeisimmät 10 operaatiota, ja tulostaa komentohistorian käyttäjän syöttäessä
valitun komennon. Komento h tulostaa historian, komento c tyhjentää historian.
Komentohistoria on tulostettava rivinumeroin tyyliteltynä, komento !numero
(esim. !2) toistaa historiassa kyseisellä rivinumerolla olevan laskun
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main()
{

    int a, b;
    char operation;
    char buffer[50];
    char **history = malloc(10 * sizeof(char *));
    int history_count = 0;
    while (1)
    {
        fgets(buffer, sizeof(buffer), stdin); // LUETAAN BUFFERIIN SYÖTTEESTÄ KOKO RIVI
        if (buffer[0] == '!')
        {
            // HALUTAAN HAKEA HISTORIASTA LASKU UUDELLEEN LASKETTAVAKSI
            int history_line;
            if (sscanf(buffer + 1, "%d", &history_line) == 1)
            {
                if (history_line >= 1 && history_line <= history_count)
                {
                    // OLLAAN 1 - HISTORIAN PITUUS VÄLILLÄ
                    strcpy(buffer, history[history_line - 1]); // LUETAAN BUFFERIIN TÄMÄ MERKKIJONO
                }
                else
                {
                    printf("Numeroa ei löytynyt komentohistoriasta\n");
                    continue;
                }
            }
        }
        if (buffer[0] == 'c')
        {
            // TYHJENNETÄÄN HISTORIA
            for (int i = 0; i < history_count; i++)
            {
                free(history[i]);
            }
            history_count = 0;
            continue;
        }
        if (buffer[0] == 'h')
        {
            // TULOSTETAAN HISTORIA
            if (history_count == 0)
            {
                printf("Komentohistoria on tyhjä\n");
            }
            else
            {
                printf("Komentohistoria:\n");
                for (int i = 0; i < history_count; i++)
                {
                    // HISTORIAN KAIKKI LASKUT
                    printf("%d: %s\n", i + 1, history[i]);
                }
            }
            continue;
        }
        if (buffer[0] == '\n')
        {
            // PELKKÄ ENTER
            printf("Virheellinen syöte (tyhjä) kirjoita \"q\" lopettaaksesi ohjelman\n");
            continue;
        };
        if (buffer[0] == 'q')
        {
            // LOPETUSKÄSKY
            printf("Lopetetaan ohjelma.\n");
            break;
        }
        // if (sscanf(buffer, "%d %c %d", &a, &operation, &b) == 3)
        if (sscanf(buffer, "%d %c %d", &a, &operation, &b) == 3)
        {
            int calculation_error = 0;
            // KAKSI LUKUA JA OPERAATTORI LÖYTYNYT
            switch (operation)
            {
            case '+':
                printf("%d\n", a + b);
                break;
            case '-':
                printf("%d\n", a - b);
                break;
            case '/':
                if (b == 0)
                {
                    printf("Nollalla ei voi jakaa.\n");
                    break;
                }
                printf("%d\n", a / b);
                break;
            case '*':
                printf("%d\n", a * b);
                break;
            case '%':
                if (b == 0)
                {
                    printf("Nollalla ei voi jakaa.\n");
                    break;
                }
                printf("%d\n", a % b);
                break;
            default:
                printf("Tätä operaattoria ei tueta.\n");
                calculation_error = 1;
                break;
            }
            if (calculation_error == 0)
            {
                // TALLENNETAAN LASKU HISTORIAAN
                char calculation_string[50];
                // LUODAAN MERKKIJONO LASKUSTA, ESIM 10 + 10
                snprintf(calculation_string, sizeof(calculation_string), "%d %c %d", a, operation, b);
                if (history_count < 10)
                {
                    // VIELÄ ON TILAA TALLENTAA
                    // TALLENNETAAN MERKKIJONO HISTORIAAN
                    // VARATAAN MUISTIA ENSIN
                    history[history_count] = malloc(50 * sizeof(char));
                    strcpy(history[history_count], calculation_string);
                    history_count++;
                }
                else
                {
                    // TILAA PITÄÄ VAPAUTTAA HISTORIASTA
                    free(history[0]); // VANHIN SAA LUVAN LÄHTEÄ
                    // SIIRRETÄÄN LOPUT YLÖSPÄIN INDEKSISSÄ
                    for (int i = 0; i < 9; i++)
                    {
                        history[i] = history[i + 1];
                    }
                    history[9] = malloc(50 * sizeof(char));
                    strcpy(history[9], calculation_string);
                }
            }
        }
        else
        {
            // TARVITTAVA LUKU TAI OPERAATTORI PUUTTUU
            printf("Virheellinen syöte (puuttuvia argumentteja)\n");
        }
    }
    return 0;
}