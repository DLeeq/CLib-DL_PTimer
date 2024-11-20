#ifndef DL_PTIMER_H
#define DL_PTIMER_H

#include "stm32f1xx_hal.h"  //Здесь должна быть библ. HAL для Вашего МК

typedef struct
{
	uint32_t time_counter;  //Счетчик для таймера
	uint8_t count_enable;  //Флаг разрешения счета
}DL_PTimer;

//Функции запуска таймера, параметры интуитивны
void DL_pTimStart(DL_PTimer* ptimer, uint32_t ms);
void DL_pTimStartSec(DL_PTimer* ptimer, uint32_t sec, uint32_t ms);
void DL_pTimStartMin(DL_PTimer* ptimer, uint32_t min, uint32_t sec, uint32_t ms);
void DL_pTimStartHour(DL_PTimer* ptimer, uint32_t hour, uint32_t min, uint32_t sec, uint32_t ms);
void DL_pTimStartDay(DL_PTimer* ptimer, uint32_t day, uint32_t hour, uint32_t min, uint32_t sec, uint32_t ms);

void DL_pTimStop(DL_PTimer* ptimer);  //Функция для остановки и сброса таймера

void DL_pTimPause(DL_PTimer* ptimer);  //Функция для остановки таймера без сброса
void DL_pTimResume(DL_PTimer* ptimer);  //Функция для запуска таймера без обновления счетчика

void DL_pTimForcedExpiration(DL_PTimer* ptimer);  //Функция принудительного истекания таймера

uint8_t DL_pTimExpired(DL_PTimer* ptimer);  //Функция проверки состояния таймера

#endif
