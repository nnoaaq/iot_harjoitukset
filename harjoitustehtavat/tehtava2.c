/*
Kirjoita C-kielellä ohjelma, joka lukee Pico:lla terminaalista käyttäjän anta-
mat kaksi kokonaislukua, ja suorittaa niille käyttäjän haluaman aritmeettisen
operaation (yhteen-, vähennys-, kerto-, jakolasku tai jakojäännös).
Ohjelman tulee raportoida käyttäjän virheistä (numerot, joita ei voida käyt-
tää, virheelliset laskuoperaatiot, tyhjä syöte) omavalintaisilla virheilmoituksilla.
Virheellinen syöte ei saa kaataa ohjelmaa.
Ohjelman lopettamiseen on kirjoitettava vapaavalintainen komento.
*/

#include <stdio.h>
#include <string.h>
int main()
{

    int a, b;
    char operation;
    char buffer[50];
    while (true)
    {

        // LUETAAN KOKO RIVI
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            // LUKEMINEN EPÄONNISTUI
            break;
        }

        if (buffer[0] == '\n')
        {
            // PELKÄSTÄÄN ENTER
            printf("Virheellinen syöte (tyhjä) kirjoita \"q\" lopettaaksesi ohjelman\n");
            continue;
        }
        if (strncmp(buffer, "q", 1) == 0)
        {
            // q-PAINETTU
            printf("Ohjelma lopetetaan.\n");
            break;
        }
        if (sscanf(buffer, "%d %c %d", &a, &operation, &b) == 3)
        {

            // KAIKKI LÖYTYY
            switch (operation)
            {
            case '+':
                printf("%d\n", (a + b));
                break;
            case '-':
                printf("%d\n", (a - b));
                break;
            case '*':
                printf("%d\n", (a * b));
                break;
            case '/':
                if (b == 0)
                {
                    printf("Nollalla ei voi jakaa.\n");
                    break;
                }
                printf("%d\n", (a / b));
                break;
            case '%':
                if (b == 0)
                {
                    printf("Nollalla ei voi jakaa.\n");
                    break;
                }
                printf("%d\n", (a % b));
                break;
            default:
                printf("Tarkista operaattori.\n");
                break;
            }
        }
        else
        {
            // JOKU ARGUMENTEISTA JÄI UUPUMAAN
            printf("Virheellinen syöte (puuttuvia argumentteja)\n");
        }
    }
    return 0;
}