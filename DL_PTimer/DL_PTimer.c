#include "DL_PTimer.h"

//Функции запуска таймера, параметры интуитивны
void DL_pTimStart(DL_PTimer* ptimer, uint32_t ms)
{
	ptimer->time_counter = ms;  //Загружаем временной интервал в счетчик таймера
	ptimer->count_enable = 1;  //Разрешаем счёт
}
void DL_pTimStartSec(DL_PTimer* ptimer, uint32_t sec, uint32_t ms)
{
	ptimer->time_counter = sec * 1000 + ms;
	ptimer->count_enable = 1;
}
void DL_pTimStartMin(DL_PTimer* ptimer, uint32_t min, uint32_t sec, uint32_t ms)
{
	ptimer->time_counter = min * 60 * 1000 + sec * 1000 + ms;
	ptimer->count_enable = 1;
}
void DL_pTimStartHour(DL_PTimer* ptimer, uint32_t hour, uint32_t min, uint32_t sec, uint32_t ms)
{
	ptimer->time_counter = hour * 60 * 60 * 1000 + min * 60 * 1000 + sec * 1000 + ms;
	ptimer->count_enable = 1;
}
void DL_pTimStartDay(DL_PTimer* ptimer, uint32_t day, uint32_t hour, uint32_t min, uint32_t sec, uint32_t ms)
{
	ptimer->time_counter = day * 24 * 60 * 60 * 1000 + hour * 60 * 60 * 1000 + min * 60 * 1000 + sec * 1000 + ms;
	ptimer->count_enable = 1;
}
void DL_pTimStop(DL_PTimer* ptimer)  //Функция остановки и сброса таймера
{
	ptimer->time_counter = 0;  //Сброс счетчика
	ptimer->count_enable = 0;  //Запрет счёта
}
void DL_pTimPause(DL_PTimer* ptimer)  //Функция остановки таймера без сброса
{
	ptimer->count_enable = 0;  //Запретить счёт
}
void DL_pTimResume(DL_PTimer* ptimer)  //Функция возобновления счета таймера
{
	ptimer->count_enable = 1;  //Разрешить счет
}

void DL_pTimForcedExpiration(DL_PTimer* ptimer)  //Функция для принудительного истекания таймера
{
	ptimer->time_counter = 0;  //Сброс счётчика
	ptimer->count_enable = 1;  //Разрешить счёт
}

uint8_t DL_pTimExpired(DL_PTimer* ptimer)  //Функция проверки состояния счетчика
{
	static uint32_t tick = 0;
	if(HAL_GetTick() - tick > 0)  //Вызывается 1 раз в миллисекунду
	{
		tick = HAL_GetTick();

		if(ptimer->count_enable)  //Если счёт разрешен
		{
			if(ptimer->time_counter > 0)  //Если таймер не истек
				ptimer->time_counter--;  //Декремент счётчика
			else  //Если таймер истёк
			{
				ptimer->count_enable = 0;  //Запрет счёта
				return 1;  //Таймер истек, возврат 1
			}
		}
	}
	return 0;  //Таймер не истек, возврат 0
}
