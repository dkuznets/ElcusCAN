#include <initguid.h>

#ifndef __PUBLIC_H__
#define __PUBLIC_H__

/** \mainpage Библиотека для работы с платами CAN-200PCI и CAN-200PCIe
 *
 * Библиотека функций предназначена для предоставления доступа к ресурсам плат серии CAN-200PCI и CAN-200PCIe.
 *
 * \par Условия работы
 *
 * Установленное оборудование:
 * \li IBM PC совместимый компьютер Pentium II или выше
 *
 * Программное обеспечение:
 * \li Microsoft Visual Studio 2012 (с установленной Visual C++)
 * \li Microsoft Windows SDK v7.1
 *
 * Поддерживаемые операционные системы:
 * \li Windows XP (x86)
 * \li Windows Vista (x86)
 * \li Windows Vista (x64)
 * \li Windows 7 (x86)
 * \li Windows 7 (x64)
 * \li Windows 8 (x86)
 * \li Windows 8 (x64)
 *
 * Поддерживаемые платы:
 * \li CAN-200PCI
 * \li CAN-200PCIe
 *
 * Платы серии CAN-200 содержат два полностью независимых CAN-канала.
 * Каждый CAN-канал построен на  CAN-контроллере PCA82C200 фирмы Philips.
 * Этот CAN-контроллер поддерживает на аппаратном уровне обмен данными по протоколу CAN 2.0 part A.
 * В 2002 году CAN-контроллер PCA82C200 снят с производства и в качестве его замены на платы серии CAN-200
 * устанавливается CAN-контроллер SJA1000, поддерживающий (в режиме #PeliCAN) обмен данными по протоколу CAN 2.0 part B active.
 * Этот CAN-контроллер имеет два режима функционирования: #BasicCAN и #PeliCAN.
 * \li Режим #BasicCAN является режимом, обеспечивающим совместимость с CAN-контроллером PCA82C200.
 * В этом режиме возможен обмен только стандартными кадрами (с 11-битным идентификатором).
 * \li Режим #PeliCAN является режимом, обеспечивающим более гибкую настройку CAN-контроллера, удобный мониторинг CAN-сети
 * и предоставляет возможность обмена кадрами с расширенным идентификатором (29-битным). 
 *
 * \note
 * Данный драйвер не обеспечивает бинарную совместимость с более ранними драйверами плат CAN-200 (драйвер CAN200.sys версии 06/29/2005,0.0.1.04).
 * Для обеспечения совместимости с ранее разработанным программным обеспечением данная библиотека имеет набор
 * функцию повторяющий соответствующий набор функций старого драйвера.
 * Для использования этих функций необходимо раскомментировать строку 
 * \code
 * //#define __USE__OLD_CAN200_FUNCTIONS__
 * \endcode
 * в файле can200-api.h.
 *
 * \par Основы использования библиотеки
 * 1. Проверить наличие и количество установленных в компьютере плат CAN-200PCI и CAN-200PCIe
 * \code
 * int result;
 * int count;
 * result = CAN200_GetNumberDevice(&count);
 * if (CAN200_OK != result)
 * {
 *		// Обработка ошибки
 * }
 * if (0 == count)
 * {
 *		// Нет установленных плат
 * }
 * \endcode
 * 2. Открыть требуемую плату для работы
 * \code
 * HANDLE hCan;
 * hCan = CAN200_Open(0);
 * if (INVALID_HANDLE_VALUE == hCan)
 * {
 *		// Обработка ошибки
 * }
 * \endcode
 * 3. Установить требуемую скорость и режим обмена по шине CAN
 * \code
 * result = CAN200_SetWorkMode(hCan, CAN_CHANNEL_1, PeliCAN);
 * if (CAN200_OK != result)
 * {
 *		// Обработка ошибки
 * }
 * result = CAN200_SetCANSpeed(hCan, CAN_CHANNEL_1, CAN_SPEED_1000);
 * if (CAN200_OK != result)
 * {
 *		// Обработка ошибки
 * }
 * \endcode
 * 4. Разрешить необходимые прерывания
 * \code
 * // Разрешаем прерывания по приему кадра
 * result = CAN200_SetInterruptSource(hCan, CAN_CHANNEL_1, 0x01);
 * if (CAN200_OK != result)
 * {
 *		// Обработка ошибки
 * }
 * \endcode
 * 5. Установить фильтр для приема кадров
 * \code
 * // Разрешаем прием всех кадров
 * pFilter_t filter;
 * filter.Filter[0] = filter.Filter[1] = filter.Filter[2] = filter.Filter[3] = 0xff;
 * filter.Mask[0] = filter.Mask[1] = filter.Mask[2] = filter.Mask[3] = 0xff;
 * filter.Mode = 0;
 * result = CAN200_P_SetInputFilter(hCan, CAN_CHANNEL_1, filter);
 * if (CAN200_OK != result)
 * {
 *		// Обработка ошибки
 * }
 * \endcode
 * 6. Разрешить работу выходных формирователей 
 * \code
 * // Разрешаем работы выходных формирователей
 * result = CAN200_SetDriverMode(hCan, CAN_CHANNEL_1, 0x1B);
 * if (CAN200_OK != result)
 * {
 *		// Обработка ошибки
 * }
 * \endcode
 * 7. С использованием функций
 * \code
 * CAN200_GetStatus, CAN200_SetCommand, CAN200_SetTxBuffer, CAN200_DefEvent, CAN200_GetEventData, CAN200_GetRxBuffer
 * \endcode
 * организовать прием и выдачу CAN кадров.
 * 8. После окончания работы закрыть плату
 * \code
 * result = CAN200_Close(hCan);
 * if (CAN200_OK != result)
 * {
 *		// Обработка ошибки
 * }
 * \endcode
 * \file public.h
 * \brief Файл содержит описание структур данных и констант для работы с платами CAN-200.
 * \warning Файл подключается автоматически при подключении файла can200-api.h
 */

/**
 * \example test-read.cpp
 */
/**
 * \example test-write.cpp
 */

/**
 * \defgroup Speed Стандартные значения скорости обмена по шине CAN
 */

/**
 * \defgroup Status Статус завершения операции
 */

/**
 * \defgroup Mode Режимы работы каналов плат
 */

/**
 * \defgroup PeliCAN Функции для работы с платой в режиме PeliCAN
 */

/**
 * \defgroup BasicCAN Функции для работы с платой в режиме BasicCAN
 */
 
#pragma pack(1)
/**
 * \struct TCAN_VPDData
 * \brief Описание платы

 * Поля структуры содержат информацию о плате серии CAN200
 */
typedef struct
{
	/**
	 * \brief Имя платы
	 *
	 * Строка вида CAN-200PCI(e) vX.Y, где vX.Y – номер версии платы
	 */
	char   szName[128];
	/**
	 * \brief Серийный номер платы
	 */
	char   szSN[10];
	/**
	 * \brief Базовый адрес первого канала
	 */
	USHORT wPorts1;
	/**
	 * \brief Базовый адрес второго канала
	 */
	USHORT wPorts2;
	/**
	 * \brief Номер вектора прерывания
	 */
	USHORT wIRQ;
} TCAN_VPDData, *pTCAN_VPDData;
#pragma pack()

#pragma pack(1)
/**
 * \struct RX_TX_Buffer
 * \brief Принятый/выдаваемый CAN кадр
 *
 * Поля структуры содержат информацию кадра принятого или выдаваемого платой CAN200
 */
typedef struct
{
	/**
	 * \brief Формат кадра
	 *
	 * #BasicCAN - стандартный кадр
	 *
	 * #PeliCAN - расширенный кадр
	 */
	unsigned short FF;
	/**
	 * \brief Стандартный идентификатор
	 *
	 * 11-ти битный идентификатор принятого кадра (действителен только при #FF = #BasicCAN)
	 */
	unsigned short sID;         /* стандартный идентификатор (11 бит) */
	/**
	 * \brief Расширенный идентификатор
	 *
	 * 29-ти битный идентификатор принятого кадра (действителен только при #FF = #PeliCAN)
	 */
	unsigned long  extID;
	/**
	 * \brief Значение бита RTR (0 или 1)
	 */
	unsigned short RTR;         /* RTR - бит                          */
	/**
	 * \brief Количество принятых/выдаваемых байт данных (0-8)
	 */
	unsigned short DLC;
	/**
	 * \brief Выдаваемые/принимаемые данные (от 0 до 8 байт)
	 *
	 * Реальное количество принимаемых/выдаваемых данных определяется полем #DLC
	 */
	unsigned short DataByte[8];
} RX_TX_Buffer, *pRX_TX_Buffer;
#pragma pack()

#pragma pack(1)
/**
 * \struct TEventData
 * \brief Информация о причине установки события
 *
 * Структура используется для получения информации об установленном событии
 */
typedef struct
{
	/**
	 * \brief Принятый кадр
	 *
	 * Поля структуры содержат действительные значения только при #IntrID = 1
	 */
	RX_TX_Buffer rxtxbuf;
	/**
	 * \brief Причина установки события
	 *
	 * Содержимое регистра идентификации прерывания CAN-контроллера канала
	 */
	UCHAR        IntrID;
} TEventData, *pTEventData;
#pragma pack()

#pragma pack(1)
/**
 * \struct bFilter_t
 * \brief Фильтр приема кадров для режима #BasicCAN
 */
typedef struct
{
	/**
	 * \brief Идентификатор входного фильтра
	 */
	USHORT Code;
	/**
	 * \brief Маска входного фильтра
	 */
	USHORT Mask;
} bFilter_t, *pbFilter_t;
#pragma pack()

#pragma pack(1)
/**
 * \struct pFilter_t
 * \brief Фильтр приема кадров для режима #PeliCAN
 */
typedef struct
{
	/**
	 * \brief Идентификатор входного фильтра
	 */
	USHORT Filter[4];
	/**
	 * \brief Маска входного фильтра
	 */
	USHORT Mask[4];
	/**
	 * \brief Режим функционирования входного фильтра
	 *
	 * 0 - одиночный фильтр
	 *
	 * 1 - двойной фильтр
	 */
	USHORT Mode;
} pFilter_t, *ppFilter_t;
#pragma pack()

/* Давим предупреждение warning C4214: нестандартное расширение: типы битовых полей, отличные от int */
#pragma warning(push)
#pragma warning(disable:4214)

#pragma pack(1)
/**
 * \union CAN_status_t
 * \brief Структура описывающая статус платы
 */
typedef union
{
	struct
	{
		/**
		 * \brief Состояние буфера приема
		 *
		 * 0 - буфер приема пуст
		 *
		 * 1 - буфер приема содержит принятое сообщение
		 */
		unsigned char rbs			: 1;
		/**
		 * \brief Переполнение приемного буфера
		 *
		 * 0 - переполнения приёмного буфера нет
		 *
		 * 1 - произошло переполнение приёмного буфера
		 */
		unsigned char dos			: 1;
		/**
		 * \brief Доступность буфера передачи
		 *
		 * 0 - буфер передачи не доступен
		 *
		 * 1 - буфер передачи доступен
		 */
		unsigned char tbs			: 1;
		/**
		 * \brief Завершенность передачи
		 *
		 * 0 - последняя передача была не завершена
		 *
		 * 1 - последняя передача успешно завершена
		 */
		unsigned char tcs			: 1;
		/**
		 * \brief Состояние приёма
		 *
		 * 0 - приема данных нет
		 *
		 * 1 - CAN-контроллер принимает данные
		 */
		unsigned char rs			: 1;
		/**
		 * \brief Состояние передачи
		 *
		 * 0 - передачи данных нет
		 *
		 * 1 - CAN-контроллер передает данные
		 */
		unsigned char ts			: 1;
		/**
		 * \brief Наличие ошибок
		 *
		 * 0 - ни один из счётчиков ошибок не достиг предельного значения
		 *
		 * 1 - по крайней мере один из счётчиков ошибок достиг предельного значения
		 */
		unsigned char es			: 1;
		/**
		 * \brief Состояние шины
		 *
		 * 0 - канал участвует в работе CAN–шины
		 *
		 * 1 - канал отключен от CAN–шины
		 */
		unsigned char bs			: 1;
	} bit;
	unsigned char byte;
} CAN_status_t, *pCAN_status_t;
#pragma pack()

#pragma pack(1)
/**
 * \union CAN_interrupt_t
 * \brief Структура описывающая разрешение/запрет прерываний
 */
typedef union
{
	struct
	{
		/**
		 * \brief Прерывание по приему кадра
		 */
		unsigned char ri			: 1;
		/**
		 * \brief Прерывание после передачи кадра
		 */
		unsigned char ti			: 1;
		/**
		 * \brief Прерывание по ошибкам на шине
		 */
		unsigned char ei			: 1;
		/**
		 * \brief Прерывание при переполнении буфера приема
		 */
		unsigned char doi			: 1;
		/**
		 * \brief Прерывание при выходе из состояния "сна" (только для режима PeliCAN)
		 */
		unsigned char wui			: 1;
		/**
		 * \brief Переход в "error passive status" (только для режима PeliCAN)
		 */
		unsigned char epi			: 1;
		/**
		 * \brief Прерывание при проигрыше арбитража (только для режима PeliCAN)
		 */
		unsigned char ali			: 1;
		/**
		 * \brief Прерывание при ошибке на шине (только для режима PeliCAN)
		 */
		unsigned char bei			: 1;
	} bit;
	unsigned char byte;
} CAN_interrupt_t, *pCAN_interrupt_t; 
#pragma pack()

#pragma pack(1)
/**
 * \union CAN_command_t
 * \brief Структура описывающая команды выполняемые платой
 */
typedef union
{
	struct
	{
		/**
		 * \brief Запрос на передачу кадра из буфера передачи
		 *
		 * 1 - Кадр из буфера передачи будет передан по шине
		 */
		unsigned char trans				: 1;
		/**
		 * \brief Прервать передачу
		 *
		 * 1 - Если был запрос на передачу кадра из буфера передачи и передача еще не началась,
		 * этот запрос будет снят
		 */
		unsigned char trans_stop		: 1;
		/**
		 * \brief Освобождение буфера приема
		 *
		 * 1 - Буфер приема освобождается
		 */
		unsigned char recv_clear		: 1;
		/**
		 * \brief Сброс признака переполнения буфера приема
		 *
		 * 1 - Признак "Переполнение буфера приема" будет снят
		 */
		unsigned char recv_bit_clear	: 1;
		/**
		 * \brief Переход в режим сна
		 *
		 * 1 - Контроллер переходит в режим сна
		 */
		unsigned char sleep				: 1;
		/**
		 * \brief Зарезервированное поле
		 */
		unsigned char rsvd				: 3;
	} bit;
	unsigned char byte;
} CAN_command_t, *pCAN_command_t; 
#pragma pack()

#pragma pack(1)
/**
 * \union CAN_error_t
 * \brief Структура для кода ошибки.
 */
typedef union
{
	struct
	{
		/**
		 * \brief Сегмент
		 *
		 * b00011 - начало кадра
		 *
		 * b00010 - идентификатор: биты 28-21
		 *
		 * b00110 - идентификатор: биты 20-18
		 *
		 * b00100 - бит SRTR
		 *
		 * b00101 - бит IDE
		 *
		 * b00111 - идентификатор: биты 17-13
		 *
		 * b01111 - идентификатор: биты 12-5
		 *
		 * b01110 - идентификатор: биты 4-0
		 *
		 * b01100 - бит RTR
		 *
		 * b01101 - зарезервированный бит 1
		 *
		 * b01001 - зарезервированный бит 0
		 *
		 * b01011 - код длины данных
		 *
		 * b01010 - поле данных
		 *
		 * b01000 - CRC последовательность
		 *
		 * b11000 - разделитель CRC
		 *
		 * b11001 - интервал подтверждения
		 *
		 * b11011 - разделитель подтверждения
		 *
		 * b11010 - конец кадра
		 *
		 * b10010 - перерыв на шине
		 *
		 * b10001 - флаг активной ошибки
		 *
		 * b10110 - флаг пассивной ошибки
		 *
		 * b10011 - tolerate dominant bits
		 *
		 * b10111 - разделитель ошибки
		 *
		 * b11100 - флаг переполнения
		 */
		unsigned char seg	: 5;
		/**
		 * \brief Направление
		 *
		 * 0 - TX (ошибка в тецение выдачи)
		 *
		 * 1 - RX (ошибка в течение приема)
		 */
		unsigned char dir	: 1;
		/**
		 * \brief Код ошибки
		 *
		 * 0 - битовая ошибка
		 *
		 * 1 - ошибка формы
		 *
		 * 2 - ошибка заполнения
		 *
		 * 3 - другая ошибка
		 */
		unsigned char errc	: 2;
	} bit;
	unsigned char byte;
} CAN_error_t, *pCAN_error_t;
#pragma pack()

#pragma pack(1)
/**
 * \union CAN_arbitration_lost_capture_t
 * \brief Структура определения точки потери арбитража.
 */
typedef union
{
	struct
	{
		/**
		 * \brief Точка потери арбитража
		 *
		 * b00000 - бит 1 идентификатора
		 *
		 * b00001 - бит 2 идентификатора
		 *
		 * b00010 - бит 3 идентификатора
		 *
		 * b00011 - бит 4 идентификатора
		 *
		 * b00100 - бит 5 идентификатора
		 *
		 * b00101 - бит 6 идентификатора
		 *
		 * b00110 - бит 7 идентификатора
		 *
		 * b00111 - бит 8 идентификатора
		 *
		 * b01000 - бит 9 идентификатора
		 *
		 * b01001 - бит 10 идентификатора
		 *
		 * b01010 - бит 11 идентификатора
		 *
		 * b01011 - бит SRTR (бит RTR для кадров со стандартным идентификатором)
		 *
		 * b01100 - бит IDE
		 *
		 * b01101 - бит 12 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b01110 - бит 13 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b01111 - бит 14 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b10000 - бит 15 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b10001 - бит 16 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b10010 - бит 17 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b10011 - бит 18 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b10100 - бит 19 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b10101 - бит 20 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b10110 - бит 21 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b10111 - бит 22 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b11000 - бит 23 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b11001 - бит 24 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b11010 - бит 25 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b11011 - бит 26 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b11100 - бит 27 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b11101 - бит 28 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b11110 - бит 29 идентификатора (только для кадров с расширенным идентификатором)
		 *
		 * b11111 - бит RTR (только для кадров с расширенным идентификатором)
		 */
		unsigned char alc	: 5;
		/**
		 * \brief Зарезервировано
		 */
		unsigned char rsvd	: 3;
	} bit;
	unsigned char byte;
} CAN_arbitration_lost_capture_t, *pCAN_arbitration_lost_capture_t;
#pragma pack()
#pragma warning(pop)

/** \cond */
#pragma pack(1)
//
// Структура запроса
//
typedef struct
{
	union CommandData_t
	{
		USHORT       Mode;
		unsigned int Speed;
		USHORT       Interrupt;
		RX_TX_Buffer Buffer;
		USHORT       Command;
		USHORT       Counter;
		bFilter_t    bFilter;
		pFilter_t    pFilter;
		HANDLE       Event;
		void *_ptr64 Event64;
		USHORT       Data[2];
	} CommandData;
	USHORT Channel;
} IoctlReq_t, *pIoctlReq_t;
#pragma pack()

#pragma pack(1)
//
// Структура ответа
//
typedef struct
{
	int Status;
	union
	{
		USHORT       Mode;
		unsigned int Speed;
		USHORT       Status;
		RX_TX_Buffer Buffer;
		USHORT       Counter;
		USHORT       Error;
		bFilter_t    bFilter;
		pFilter_t    pFilter;
		TEventData   EventData;
		USHORT       Data;
		USHORT       Mask;
		int          OverCounter;
	} Data;
} IoctlRes_t, *pIoctlRes_t;
#pragma pack()
/** \endcond */

/**
 * \addtogroup Status
 * \{
 */
#define CAN200_OK			0	///< Операция завершена успешно
#define CAN200_ERR_PARM		-1	///< Ошибка входных параметров
#define CAN200_ERR_SYS		-2	///< Системная ошибка
#define CAN200_ERR_MODE		-3	///< Режим работы не соответствует требуемому
#define CAN200_ERR_BUSY		-4	///< Буфер выдачи занят
/** \} */

#define NUM_CHANNEL			2	///< Количество каналов на плате

#define CAN_CHANNEL_1		1	///<Первый канал платы
#define CAN_CHANNEL_2		2	///<Второй канал платы

/** \cond */
//
// Максимальное количество плат.
//
#define MAX_CAN_NUMBER		10
/** \endcond */

/**
 * \addtogroup Mode
 * \{
 */
#define BasicCAN			0	///< Основной режим
#define PeliCAN				1	///< Расширенный режим
/** \} */

/**
 * \addtogroup Speed
 * \{
 */
#define CAN_SPEED_USER_DEFINED(btr0, btr1)	(0xffff | (((btr0) & 0xff) << 24) | (((btr1) & 0xff) << 16))	///< Скорость определенная пользователем
#define IS_CAN_SPEED_USER_DEFINED(speed)	((0xffff == ((speed) & 0xffff)) ? 1 : 0)	///< 1 - скорость определяемая пользователем, 0 - одна из стандартных скоростей
#define CAN_SPEED_GET_BTR0(speed)	(((speed) >> 24) & 0xff)	///< Возвращает значение регсистра BTR0 для скоростей задаваемых пользователем
#define CAN_SPEED_GET_BTR1(speed)	(((speed) >> 16) & 0xff)	///< Возвращает значение регсистра BTR1 для скоростей задаваемых пользователем 
#define CAN_SPEED_1000		1000	///< Скорость 1 Mbit/sec 
#define CAN_SPEED_800		800		///< Скорость 800 kbit/sec 
#define CAN_SPEED_500		500		///< Скорость 500 kbit/sec 
#define CAN_SPEED_250		250		///< Скорость 250 kbit/sec 
#define CAN_SPEED_125		125		///< Скорость 125 kbit/sec 
#define CAN_SPEED_50		50		///< Скорость 50 kbit/sec 
#define CAN_SPEED_20		20		///< Скорость 20 kbit/sec 
#define CAN_SPEED_10		10		///< Скорость 10 kbit/sec 
/** \} */

/** \cond */
#define FILE_DEVICE_CAN200				0x8000

#define V_HardReset						0
#define V_SetWorkMode					1
#define V_GetWorkMode					2
#define V_SetDriverMode					3
#define V_SetCANSpeed					4
#define V_GetStatus						5
#define V_SetInterruptSource			6
#define V_SetTxBuffer					7
#define V_GetRxBuffer					8
#define V_SetCommand					9
#define V_B_SetInputFilter				10
#define V_P_SetRxErrorCounter			11
#define V_P_GetRxErrorCounter			12
#define V_P_SetTxErrorCounter			13
#define V_P_GetTxErrorCounter			14
#define V_P_SetErrorWarningLimit		15
#define V_P_GetErrorWarningLimit		16
#define V_P_GetArbitrationLostCapture	17
#define V_P_GetRxMessageCounter			18
#define V_P_GetErrorCode				19
#define V_P_SetInputFilter				20
#define V_DefEvent						21
#define V_GetEventData					22
#define V_GetConfig						23
#define V_GetCANSpeed					24
#define V_B_GetInputFilter				25
#define V_P_GetInputFilter				26
#define V_SetCANReg						27
#define V_GetCANReg						28
#define V_GetInterruptSource			29
#define V_GetOverCounter				30

//
// Коды ioctl.
//
#define IOCTL_CAN200PC_SetWorkMode					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_SetWorkMode,                 \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetWorkMode					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetWorkMode,                 \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_SetDriverMode				CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_SetDriverMode,               \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_HardReset					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_HardReset,                   \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_SetCANSpeed					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_SetCANSpeed,                 \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetStatus					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetStatus,                   \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetConfig					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetConfig,                   \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_SetInterruptSource			CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_SetInterruptSource,          \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_SetTxBuffer					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_SetTxBuffer,                 \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetRxBuffer					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetRxBuffer,                 \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_SetCommand					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_SetCommand,                  \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_B_SetInputFilter				CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_B_SetInputFilter,            \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_SetRxErrorCounter			CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_SetRxErrorCounter,         \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_GetRxErrorCounter			CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_GetRxErrorCounter,         \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_SetTxErrorCounter			CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_SetTxErrorCounter,         \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_GetTxErrorCounter			CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_GetTxErrorCounter,         \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_SetErrorWarningLimit		CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_SetErrorWarningLimit,      \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_GetErrorWarningLimit		CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_GetErrorWarningLimit,      \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_GetArbitrationLostCapture	CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_GetArbitrationLostCapture, \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_GetRxMessageCounter		CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_GetRxMessageCounter,       \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_GetErrorCode				CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_GetErrorCode,              \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_SetInputFilter				CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_SetInputFilter,            \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetCANSpeed					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetCANSpeed,                 \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_B_GetInputFilter				CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_B_GetInputFilter,            \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_DefEvent						CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_DefEvent,                    \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetEventData					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetEventData,                \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_P_GetInputFilter				CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_P_GetInputFilter,            \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_SetCANReg					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_SetCANReg,                   \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetCANReg					CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetCANReg,                   \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetInterruptSource			CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetInterruptSource,          \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
#define IOCTL_CAN200PC_GetOverCounter				CTL_CODE(FILE_DEVICE_CAN200,               \
														0x800 + V_GetOverCounter,		       \
														METHOD_BUFFERED,                       \
														FILE_ANY_ACCESS)
/** \endcond */

#endif /* __PUBLIC_H__ */
