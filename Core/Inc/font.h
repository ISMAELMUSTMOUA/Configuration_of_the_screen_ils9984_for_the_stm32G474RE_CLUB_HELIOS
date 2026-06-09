/*
 * font.h
 *
 * Created on: Apr 5, 2026
 * Author: Acer
 */

#ifndef INC_FONT_H_
#define INC_FONT_H_

#include <stdint.h>
#include <stdio.h> // Necesario para el sprintf
#include "main.h"  // Necesario para los pines del TFT y HAL_Delay
#include "stm32g474xx.h" // Necesario para los registros de GPIO y SPI y FDCAN


	// Handle de SPI periférico usado por la pantalla (definido por HAL en main.c)
	extern SPI_HandleTypeDef hspi1;

	// ====================================================================
	// 1. DECLARACIONES DE DATOS GRÁFICOS (extern)
	// ====================================================================
	// Indica al compilador que estas estructuras existen en font.c sin duplicar memoria
	extern const uint8_t Font5x7[295];
	extern const uint16_t club_helios_565[];

	// ====================================================================
	// 2. PROTOTIPOS DE FUNCIONES DE PANTALLA Y ENTRADAS
	// ====================================================================
	void botton_init(void);
	uint8_t Leer_Botones(void);

	// ====================================================================
	// 3. PROTOTIPOS DE LAS FUNCIONES DE LA PANTALLA (ILI9488)
	// ====================================================================
	void ILI9488_SendCommand(uint8_t cmd);
	void ILI9488_SendData(uint8_t data);
	void ILI9488_Init(void);
	void ILI9488_FillScreen(uint8_t r, uint8_t g, uint8_t b);
	void ILI9488_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t r, uint8_t g, uint8_t b); 
	void ILI9488_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t* image_array);
	void ILI9488_DrawColorBars(void);
	void ILI9488_DrawChar(uint16_t x, uint16_t y, char c, uint8_t r, uint8_t g, uint8_t b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t size);
	void ILI9488_DrawString(uint16_t x, uint16_t y, char* str, uint8_t r, uint8_t g, uint8_t b, uint8_t br, uint8_t bg, uint8_t bb, uint8_t size);

	// ====================================================================
	// 4. PROTOTIPOS DE LAS PANTALLAS DEL COCHE
	// ====================================================================
	void Helios_DrawRules_Static(void);
	void Helios_DrawDashboard_Static(void);

	void Helios_UpdateTelemetry(int speed, int battery_percent, uint8_t is_eco_mode,
	                            int temp, int pre, int rpm, float volt, float amp,
	                            int eta_h, int eta_m, uint8_t force_redraw );

	void Helios_Draw_Intermitente(uint8_t lado, uint8_t estado);
	void Helios_DrawDashboard_Static(void);
	// ====================================================================
	// 5. ESTRUCTURAS DE TELEMETRÍA CAN Y PROTOTIPOS FDCAN
	// ====================================================================
	typedef struct {
		float battery_voltage;   
		float battery_current;   
		uint8_t soc_bateria;     
		float pt100_temp;        
		uint16_t motor_rpm;      
		uint8_t velocidad;       
	} TelemetryData_t;

	// Variable global compartida
	extern TelemetryData_t v_telemetry;
	
	// Prototipos de funciones FDCAN
	void FDCAN_BareMetal_Init(void);
	void FDCAN_CheckAndReceive(void);
								
#endif /* INC_FONT_H_ */
