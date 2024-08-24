/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   100


/* The devicetree node identifier for the "led0" alias. */



/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */

static const struct gpio_dt_spec led = 
	GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static const struct gpio_dt_spec led_a = 
	GPIO_DT_SPEC_GET(DT_ALIAS(leda), gpios);

static const struct gpio_dt_spec led_b = 
	GPIO_DT_SPEC_GET(DT_ALIAS(ledb), gpios);

static const struct gpio_dt_spec led_c = 
	GPIO_DT_SPEC_GET(DT_ALIAS(ledc), gpios);

static const struct gpio_dt_spec led_d = 
	GPIO_DT_SPEC_GET(DT_ALIAS(ledd), gpios);

static const struct gpio_dt_spec led_e = 
	GPIO_DT_SPEC_GET(DT_ALIAS(lede), gpios);

static const struct gpio_dt_spec led_f = 
	GPIO_DT_SPEC_GET(DT_ALIAS(ledf), gpios);

static const struct gpio_dt_spec led_g = 
	GPIO_DT_SPEC_GET(DT_ALIAS(ledg), gpios);


static const struct gpio_dt_spec button = 
	GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

int vetor[16] = {
	0b0111111,
    0b0000110,
    0b1011011,
    0b1001111,
    0b1100110,
    0b1101101,
    0b1111101,
    0b0000111,
    0b1111111,
    0b1101111,
	0b1110111,
	0b1111100,
	0b0111001,
	0b1011110,
	0b1111001,
	0b1110001,
};

enum Estado {
	BOTAO_N_PRESSIONADO,
	BOTAO_PRESSIONADO
};

void trocarEstado(int contador){
	int posicao = vetor[contador];
	gpio_pin_set_dt(&led_a, (posicao >> 0) & 1); 
    gpio_pin_set_dt(&led_b, (posicao >> 1) & 1); 
    gpio_pin_set_dt(&led_c, (posicao >> 2) & 1); 
    gpio_pin_set_dt(&led_d, (posicao >> 3) & 1); 
    gpio_pin_set_dt(&led_e, (posicao >> 4) & 1); 
    gpio_pin_set_dt(&led_f, (posicao >> 5) & 1); 
    gpio_pin_set_dt(&led_g, (posicao >> 6) & 1); 
}


int main(void)
{
	int ret;
	int ret_button;
	enum Estado estado_atual = BOTAO_N_PRESSIONADO;
	int contador = 0;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	if (!gpio_is_ready_dt(&led_a)) {
		return 0;
	}
	if (!gpio_is_ready_dt(&led_b)) {
		return 0;
	}
	
	if (!gpio_is_ready_dt(&led_c)) {
		return 0;
	}
	if (!gpio_is_ready_dt(&led_d)) {
		return 0;
	}
	if (!gpio_is_ready_dt(&led_e)) {
		return 0;
	}
	if (!gpio_is_ready_dt(&led_f)) {
		return 0;
	}
	if (!gpio_is_ready_dt(&led_g)) {
		return 0;
	}

	if(!gpio_is_ready_dt(&button)){
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_a, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_configure_dt(&led_b, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_c, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_configure_dt(&led_d, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_configure_dt(&led_e, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_configure_dt(&led_f, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_configure_dt(&led_g, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret_button = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if(ret <0){
		return 0;
	}


	while (1) {

		switch(estado_atual){
			case BOTAO_N_PRESSIONADO:
				trocarEstado(contador);
				if(gpio_pin_get_dt(&button)){
					estado_atual = BOTAO_PRESSIONADO;
					if(contador < 16){
						contador += 1;	
					}
					if(contador >= 16){
						contador = 0;
					}
					break;
				}	
			case BOTAO_PRESSIONADO:
				if(!gpio_pin_get_dt(&button)){
					estado_atual = BOTAO_N_PRESSIONADO;
					k_msleep(SLEEP_TIME_MS);
					break;
				}	
		}

	}
	return 0;
}
