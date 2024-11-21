#include "DL_PTimer.h"

void DL_pTimStart(DL_PTimer* ptimer, const char* format, ...)  //Форматная функция запуска таймера
{
	ptimer->time_counter = 0;  //Сброс счетчика
	ptimer->count_enable = 1;  //Разрешить счет

	va_list args;
	va_start(args, format);

	for(int i = 0; format[i] != '\0'; i++)  //Форматный перерасчет времени в миллисекунды
	{
		switch(format[i])
		{
			case ':':
				break;
			case ' ':
				break;
			case 'd':
				ptimer->time_counter += va_arg(args, uint32_t) * 24 * 60 * 60 * 1000;
				break;
			case 'h':
				ptimer->time_counter += va_arg(args, uint32_t) * 60 * 60 * 1000;
				break;
			case 'm':
				if(format[i + 1] != 's')
					ptimer->time_counter += va_arg(args, uint32_t) * 60 * 1000;
				else
				{
					ptimer->time_counter += va_arg(args, uint32_t);
					i++;
				}
				break;
			case 's':
				ptimer->time_counter += va_arg(args, uint32_t) * 1000;
				break;
			default :
				ptimer->time_counter = 0;
				return;
		}
	}

	va_end(args);
}
void DL_pTimStartMS(DL_PTimer* ptimer, uint32_t ms) //Функция запуска таймера в миллисекундах
{
	ptimer->time_counter = ms;  //Загружаем временной интервал в счетчик таймера
	ptimer->count_enable = 1;  //Разрешаем счёт
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


uint32_t DL_pTimGetTimeLeft(DL_PTimer* ptimer)  //Функция возврата оставшегося времени
{
	return ptimer->time_counter;  //Возврат значения счетчика
}


uint8_t DL_pTimExpired(DL_PTimer* ptimer)  //Функция проверки состояния счетчика
{
	if(HAL_GetTick() - ptimer->tick > 0)  //Вызывается 1 раз в миллисекунду
	{
		ptimer->tick = HAL_GetTick();

		if(ptimer->count_enable)  //Если счёт разрешен
		{
			if(ptimer->time_counter > 0)  //Если таймер не истек
				ptimer->time_counter--;  //Декремент счётчика

			if(ptimer->time_counter == 0)  //Если таймер истёк
			{
				ptimer->count_enable = 0;  //Запрет счёта
				return 1;  //Таймер истек, возврат 1
			}
		}
	}
	return 0;  //Таймер не истек, возврат 0
}
