#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define KNOWN_RESISTANCE 220        // TUNNETUN "ETU"_VASTUKSEN OHMIT
#define CALIBRATED_TEMPERATURE 22   // TODETTU LÄMPÖTILA
#define CALIBRATED_RESISTANCE 331.5 // TODETTU VASTUS
#define MEASUREMENTS 10000          // MITTAUSTEN LUKUMÄÄRÄ

int main()
{
    stdio_init_all();    // STDIO - KÄYTTÖÖN
    adc_init();          // ADC - KÄYTTÖÖN
    adc_gpio_init(26);   // GPIO26 - PINNIIN KYTKETTY MITTAUSPISTE
    adc_select_input(0); // ADC0

    while (true)
    {
        const float conversionFactor = 3.3f / (1 << 12); // SYÖTTÖJÄNNITE / 4096¨
        float measuredVolts = 0.0f;
        // KERÄTÄÄN x-MÄÄRÄ MITTAUKSIA JA LASKETAAN KESKIARVO
        for (int i = 0; i < MEASUREMENTS; i++)
        {
            measuredVolts += adc_read() * conversionFactor;
        }
        // OTETAAN X-MÄÄRÄSTÄ MITTAUKSIA KESKIARVO
        float volt = measuredVolts / MEASUREMENTS;
        // MUUNNETAAN MITATTU JÄNNITE "SENSORIN" VASTUKSEKSI TUNNETUN (SARJAAN KYTKETTY) VASTUKSEN AVULLA
        float resistance = KNOWN_RESISTANCE * volt / (3.3 - volt);

        // MUUNNETAAN LASKETTU VASTUS LÄMPÖTILAKSI
        float temperature = CALIBRATED_TEMPERATURE + (resistance - CALIBRATED_RESISTANCE) / (0.00393 * CALIBRATED_RESISTANCE);

        printf("Mitattu jännite (V) %f\n", volt);
        printf("Mitattu vastus (Ω) %f  \n", resistance);
        printf("Mitattu lämpötila (°C) %.1f \n", temperature);
        printf("-----------------------------------------\n\n");
        sleep_ms(5000);
    }

    return 0;
}