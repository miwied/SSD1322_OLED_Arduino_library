/**
 ****************************************************************************************
 *
 * \file SSD1322_HW_Driver.c
 *
 * \brief Hardware dependent functions for SSD1322 OLED display.
 *
 * This file contains functions that rely on hardware of used MCU. In this example functions
 * are filled with STM32F411RE hardware implementation. To use this library on any other MCU
 * you just have to provide its hardware implementations of functions from this file and higher
 * level functions should work without modification.
 *
 * Copyright (C) 2020 Wojciech Klimek
 * MIT license:
 * https://github.com/wjklimek1/SSD1322_OLED_library
 *
 ****************************************************************************************
 */

#include "../SSD1322_OLED_lib/SSD1322_HW_Driver.h"

//====================== Constructor ========================//
SSD1322_HW_DRIVER::SSD1322_HW_DRIVER(int OLED_CS_PIN, int OLED_DC_PIN, int OLED_RESET_PIN)
	: OLED_CS(OLED_CS_PIN), OLED_DC(OLED_DC_PIN), OLED_RESET(OLED_RESET_PIN) {}

//====================== CS pin low ========================//
/**
 *  @brief Drives CS (Chip Select) pin of SPI interface low.
 *
 *  CS pin may be also signed as "SS" or "NSS"
 */
void SSD1322_HW_DRIVER::SSD1322_HW_drive_CS_low()
{
	digitalWrite(OLED_CS, LOW);
}

//====================== CS pin high ========================//
/**
 *  @brief Drives CS (Chip Select) pin of SPI interface high.
 *
 *  CS pin may be also signed as "SS" or "NSS"
 */
void SSD1322_HW_DRIVER::SSD1322_HW_drive_CS_high()
{
	digitalWrite(OLED_CS, HIGH);
}

//====================== DC pin low ========================//
/**
 *  @brief Drives DC (Data/Command) pin of OLED driver low.
 *
 *  High state is for data and low state is for command.
 */
void SSD1322_HW_DRIVER::SSD1322_HW_drive_DC_low()
{
	digitalWrite(OLED_DC, LOW);
}

//====================== DC pin high ========================//
/**
 *  @brief Drives DC (Data/Command) pin of of OLED driver high.
 *
 *  High state is for data and low state is for command.
 */
void SSD1322_HW_DRIVER::SSD1322_HW_drive_DC_high()
{
	digitalWrite(OLED_DC, HIGH);
}

//====================== RESET pin low ========================//
/**
 *  @brief Drives RESET pin of of OLED driver low.
 *
 *  Logic low on RESET resets OLED driver.
 */
void SSD1322_HW_DRIVER::SSD1322_HW_drive_RESET_low()
{
	if (OLED_RESET != -1)
	{
		digitalWrite(OLED_RESET, LOW);
	}
}

//====================== RESET pin high ========================//
/**
 *  @brief Drives RESET pin of of OLED driver high.
 *
 *  Logic low on RESET resets OLED driver.
 */
void SSD1322_HW_DRIVER::SSD1322_HW_drive_RESET_high()
{
	if (OLED_RESET != -1)
	{
		digitalWrite(OLED_RESET, HIGH);
	}
}

//====================== Send single SPI byte ========================//
/**
 *  @brief Transmits single byte through SPI interface.
 *
 *  @param[in] byte_to_transmit byte that will be transmitted through SPI interface
 */
void SSD1322_HW_DRIVER::SSD1322_HW_SPI_send_byte(uint8_t byte_to_transmit)
{
	SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
	SPI.transfer(byte_to_transmit);
	SPI.endTransaction();
}

//====================== Send array of SPI bytes ========================//
/**
 *  @brief Transmits array of bytes through SPI interface.
 *
 *  @param[in] array_to_transmit array of bytes that will be transmitted through SPI interface
 *  @param[in] array_size amount of bytes to transmit
 */
void SSD1322_HW_DRIVER::SSD1322_HW_SPI_send_array(uint8_t *array_to_transmit, uint32_t array_size)
{
	SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
	for (uint32_t i = 0; i < array_size; i++)
	{
		SPI.transfer(array_to_transmit[i]);
	}
	SPI.endTransaction();
}

//====================== Milliseconds delay ========================//
/**
 *  @brief Wait for x milliseconds.
 *
 *  NOTE: This function is only used in initialization sequence to pull reset down and high
 *  and later to wait for Vdd stabilization. It takes time ONLY on startup (around 200ms)
 *  and is NOT USED during normal operation.
 *
 *  @param[in] milliseconds time to wait
 */
void SSD1322_HW_DRIVER::SSD1322_HW_msDelay(uint32_t milliseconds)
{
	delay(milliseconds);
}
