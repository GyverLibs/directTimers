#include <directTimers.h>
/* пример генерации меандра на таймере 1*/
/* формула для расчета предела счета для генерации меандра приведена в шпаргалке README */
/* unsigned int top = (8000000/freqency)-1;  где top- предел счета, на который мы настроим таймер, freqency - желаемая частота меандра */
/* максимальная частота меандра - 8мгц */

// сгенерируем меандр с частотой 100кгц на двух каналах таймера 1 с возможностью смещения фазы 0...180 градусов относительно друг друга
// соотв для частоты 100 кгц >>> top = (8000000/100000)-1; >>> top = 79;

void setup() {
  pinMode(9, OUTPUT);
  TIMER1_setClock(PRESCALER_1); //установим максимальную частоту таймера
  TIMER1_setMode(CTC_MODE); // включим сброс по совпадению, происходит при совпадении счетного регистра со значением заданым TIMER1_COMPA_setValue();
  TIMER1_COMPA_mode(TOGGLE_PIN); // инвертирование состояние ноги при совпадении
  TIMER1_COMPB_mode(TOGGLE_PIN); // инвертирование состояние ноги при совпадении
  TIMER1_COMPA_setValue(79); //в режиме CTC_MODE задает предел счета и соотв частоту событий, на этом моменте уже начнется генерация меандра на канале А
}

void loop() {
  byte value = map(analogRead(A0), 0, 1023, 0, 79); // преобразуем значение с потенциометра в установленный нами диапазон 0...79
  /* 0...79 в данном случае эквивалентно сдвигу фазы на  0...180 градусов */
  TIMER1_COMPB_setValue(value);  // изменяя значение от 0 до 79 мы можем сдвигать меандр на канале В относительно первого на 0...180 градусов
}
