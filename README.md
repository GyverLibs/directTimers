[![Foo](https://img.shields.io/badge/Version-1.0-brightgreen.svg?style=flat-square)](#versions)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/directTimers?_x_tr_sl=ru&_x_tr_tl=en) 
[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)


# directTimers
Библиотека для расширенного ручного управления таймерами ATMega2560, ATMega328, ATMega32u4
- Функции библиотеки позволяют получить доступ ко всем возможностям и режимам работы с таймерами/счётчиками + прерывания watchdog
- Ничего не урезано и не упрощено, доступен весь описанный в даташите функционал

### Совместимость
ATMega2560, ATMega328, ATMega32u4

### Документация
К библиотеке есть [расширенная документация](https://alexgyver.ru/directTimers/)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **directTimers** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/directTimers/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
Нет

<a id="usage"></a>
## Использование
```cpp
// n - номер таймера (0, 1 или 2)
void TIMERn_COMPA_attachInterrupt(void (*isr)());
void TIMERn_COMPB_attachInterrupt(void (*isr)());
void TIMERn_COMPA_detachInterrupt(void);
void TIMERn_COMPB_detachInterrupt(void);
void TIMERn_setClock(byte clk);
void TIMERn_setMode(byte mode);
void TIMERn_COMPA_mode(byte mode);
void TIMERn_COMPB_mode(byte mode);
byte TIMERn_getCounter(void);
void TIMERn_setCounter(byte value);
void TIMERn_COMPA_setValue(byte value);
void TIMERn_COMPB_setValue(byte value);

// прерывания watchdog
void WDT_attachInterrupt(void (*isr)(),int prescaler);
void WDT_detachInterrupt(void);

/* константы для TIMERn_clock() */
STOPPED             // тактирование будет остановлено , таймер "заморожен"
EXTERNAL_FALLING    // тактирование внешним клоком до 8 мгц по спаду
EXTERNAL_RISING     // тактирование внешним клоком до 8 мгц по фронту

// делители
PRESCALER_1
PRESCALER_8
PRESCALER_32
PRESCALER_64
PRESCALER_128
PRESCALER_256
PRESCALER_1024

/* константы для настройки режима работы таймеров */
STANDARD_MODE       // таймер считает до 255 и сбрасывается в 0, (может до 511/1023 для таймера 1)
CTC_MODE            // таймер считает от 0 до числа заданного функцией TIMERn_COMPA_setValue(), после чего сбрасывается (в этот момент может вызват прерывание)
FAST_PWM_8BIT       // аппаратный шим 8 бит
FAST_PWM_9BIT       // для таймера 1
FAST_PWM_10BIT 

// шим с коррекцией
PHASECORRECT_PWM_8BIT
PHASECORRECT_PWM_9BIT
PHASECORRECT_PWM_10BIT
FAST_PWM_CUSTOM             // шим с кастомной глубиной, глубина задается TIMER0/2_COMPA_setValue() и TIMER1_setTop();
PHASECORRECT_PWM_CUSTOM     // то же самое но с коррекцией

/* константы для управления аппаратными выходами с таймеров */
DISABLE_COMP     // выход отключен от ноги, ногой можно пользоваться
NORM_PWM         // выход генерирует шим >>> +5В при сбросе таймера, 0В при совпадении
INVERT_PWM       // выход генерирует инвертированный шим >>> 0В при сбросе таймера, +5В при совпадении
TOGGLE_PIN       // выход генерирует меандр >>> инверсия состояния пина при совпадении
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
#include <directTimers.h>

/* пример генерации шим с выбранной частотой на таймере 1
  формула для рачета предела счета приведена в шпаргалке README */

/*
  Для режима FAST PWM >>> top = (Fтаймера/Fшим)-1;
  Для режима PHASECORRECT PWM >>> top = Fтаймера/(2*Fшим);
*/

// пусть частота ШИМ будет 25 кгц в режиме коррекции фазы >>> top = 8000000/25000 >>> top = 320;

void setup() {
  pinMode(9, 1); // настраиваем канал А как выход
  pinMode(10, 1); // настраиваем канал В как выход

  TIMER1_setClock(PRESCALER_1); // задаем таймеру максимальную частоту
  TIMER1_setMode(PHASECORRECT_PWM_CUSTOM); // включаем режим кастомного предела счета
  TIMER1_setTop(320); // устанавливаем предел счета 320, чтобы получить частоту 25 кгц с коррекцией фазы
  TIMER1_COMPA_mode(NORM_PWM); // настраиваем аппаратные выходы с таймера в режим ШИМ
  TIMER1_COMPB_mode(NORM_PWM);
}

void loop() {
  int dutyA = map(analogRead(A0), 0, 1023, 0, 320); // пересчитываем диапазон потенциометра в диапазон таймера 0...top >>> 0...320
  int dutyB = map(analogRead(A1), 0, 1023, 0, 320);

  TIMER1_COMPA_setValue(dutyA); // устанавливаем на выходе А заполнение потенциометром (pin 9)
  TIMER1_COMPB_setValue(dutyB); // (pin 10)
}

```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
