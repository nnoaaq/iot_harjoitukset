#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_PIN 22

int count = 0;

absolute_time_t last_pressed_time = 0;
void callback_function(uint gpio, uint32_t event_mask)
{
    // CALLBACK-FUNKTIO JOKA AJETAAN KUN GPIO TUNNISTAA "GPIO_IRQ_EDGE_FALL"
    // OLTAVA OIKEA GPIO_PIN JA EVENT_MASK ON VASTATTAVA
    if (gpio != BUTTON_PIN || !(event_mask & GPIO_IRQ_EDGE_FALL))
    {
        return;
    }

    // TARKISTETAAN ONKO VIIME PAINALLUKSESTA KULUNUT TARPEEKSI AIKAA
    absolute_time_t time_now = get_absolute_time();
    // LAITTOMAN PITKÄ EROTUS-AIKA ESTÄÄ WOKWI SIMULAATION TUPLAPAINALLUKSEN
    // TOSI-ELÄMÄSSÄ PITÄISI RIITTÄÄ PIENEMPIKIN....
    if (gpio_get(gpio) == 0 && absolute_time_diff_us(last_pressed_time, time_now) > 200000)
    {
        count++;
        printf("Painiketta painettu yhteensä %u kertaa.\n", count);
        last_pressed_time = time_now;
    }
}

void setup()
{
    stdio_init_all();
    gpio_init(BUTTON_PIN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_set_input_hysteresis_enabled(BUTTON_PIN, true);                                         // "This is enabled on all GPIOs by default" << MUTTA KIRJOITETAAN NYT SILTI
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, callback_function); // AJETAAN OMA FUKTIO KUN KYSEINEN PINNI HAVAITSEE TIPPUVAN REUNAN
    printf("Setup ajettu.\n");
}

int main()
{
    setup();
    while (true)
    {
        sleep_ms(2000);
    }
    return 0;
}