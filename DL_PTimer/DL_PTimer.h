#ifndef DL_PTIMER_H
#define DL_PTIMER_H

#include <stdarg.h>
#include "stm32f1xx_hal.h"  //Здесь должна быть библ. HAL для Вашего МК

typedef struct
{
	uint32_t time_counter;  //Счетчик для таймера
	uint8_t count_enable;  //Флаг разрешения счета

	uint32_t tick;  //Тикер
}DL_PTimer;

void DL_pTimStart(DL_PTimer* ptimer, const char* format, ...);  //Форматная функция запуска таймера
void DL_pTimStartMS(DL_PTimer* ptimer, uint32_t ms);  //Функция запуска таймера в миллисекундах
void DL_pTimStop(DL_PTimer* ptimer);  //Функция для остановки и сброса таймера

void DL_pTimPause(DL_PTimer* ptimer);  //Функция для остановки таймера без сброса
void DL_pTimResume(DL_PTimer* ptimer);  //Функция для запуска таймера без обновления счетчика

void DL_pTimForcedExpiration(DL_PTimer* ptimer);  //Функция принудительного истекания таймера

uint8_t DL_pTimExpired(DL_PTimer* ptimer);  //Функция проверки состояния таймера

uint32_t DL_pTimGetTimeLeft(DL_PTimer* ptimer);  //Функция возврата оставшегося времени

#endif
