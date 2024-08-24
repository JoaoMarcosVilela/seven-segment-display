/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */


/* The devicetree node identifier for the "led0" alias. 
#define LED0_NODE DT_ALIAS(led0)*/

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 static const struct gpio_dt_spec ledb = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
 */
static const struct gpio_dt_spec leda = GPIO_DT_SPEC_GET(DT_ALIAS(leda), gpios);
static const struct gpio_dt_spec ledb = GPIO_DT_SPEC_GET(DT_ALIAS(ledb), gpios);
static const struct gpio_dt_spec ledc = GPIO_DT_SPEC_GET(DT_ALIAS(ledc), gpios);
static const struct gpio_dt_spec ledd = GPIO_DT_SPEC_GET(DT_ALIAS(ledd), gpios);
static const struct gpio_dt_spec lede = GPIO_DT_SPEC_GET(DT_ALIAS(lede), gpios);
static const struct gpio_dt_spec ledf = GPIO_DT_SPEC_GET(DT_ALIAS(ledf), gpios);
static const struct gpio_dt_spec ledg = GPIO_DT_SPEC_GET(DT_ALIAS(ledg), gpios);

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);





static int contador_botao = 0;



void configurar_seguimentos(int contador) {
    static const uint8_t segment_map[16] = {
        0b00111111, 
        0b00000110, 
        0b01011011, 
        0b01001111, 
        0b01100110, 
        0b01101101, 
        0b01111101, 
        0b00000111, 
        0b01111111, 
        0b01101111, 
		0b01110111, 
		0b01111100, 
		0b00111001, 
		0b01011110, 
		0b01111001, 
		0b01110001,
    };

    
    uint8_t byte = segment_map[contador];

    
    gpio_pin_set_dt(&leda, (byte >> 0) & 1); 
    gpio_pin_set_dt(&ledb, (byte >> 1) & 1); 
    gpio_pin_set_dt(&ledc, (byte >> 2) & 1); 
    gpio_pin_set_dt(&ledd, (byte >> 3) & 1); 
    gpio_pin_set_dt(&lede, (byte >> 4) & 1); 
    gpio_pin_set_dt(&ledf, (byte >> 5) & 1); 
    gpio_pin_set_dt(&ledg, (byte >> 6) & 1); 
}

void verificador_botao(void) {
    if (gpio_pin_get_dt(&button)) {
        contador_botao++;
        while (gpio_pin_get_dt(&button)) {
            k_msleep(100);
        }
    }
}



int main(void)
{
	int ret;

	if (!gpio_is_ready_dt(&leda)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&leda, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

		if (!gpio_is_ready_dt(&ledb)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&ledb, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

		if (!gpio_is_ready_dt(&ledc)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&ledc, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

		if (!gpio_is_ready_dt(&ledd)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&ledd, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}
		if (!gpio_is_ready_dt(&lede)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&lede, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

		if (!gpio_is_ready_dt(&ledf)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&ledf, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	
	}
		if (!gpio_is_ready_dt(&ledg)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&ledg, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

	if (!gpio_is_ready_dt(&button)) {
        return 0;
    }

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret < 0) {
        return 0;
    }


	while (1) {
		if(contador_botao == 16){
			contador_botao = 0;
		}
		printk("Valor do contador: %d\n", contador_botao);
		configurar_seguimentos(contador_botao);
    	verificador_botao();
        
	   


	}

	return 0;
}
