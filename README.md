# railway_slide_controller
Railway slide controller code

Устройство состоит из двух частей:
1. Arduini UNO
2. Специальный shield, выполняющий функцию подключения элементов управления пульта, индикации пульта и дополнительной индикации самого устройства.

Shield стыкуется с Arduino UNO и составляет единый элемент.

Элементы управления 

Описание протокола обмена данными

Виртуальный com-порт через USB
Скорость 9600 бод, 8 бит данных, 1 стоп-бит


Отправляемые данные
Устройство "пульт" передает каждые 100мс данные о состоянии кнопок и переключателей. Данные зашифрованы в 8 бит:

 Bit #     7......0  
      MSB  XXXXXXXX  LSB
           |||||||+-- кнопка Старт
           ||||||+--- состояние S1
           |||||+---- состояние S2
           ||||+----- состояние S3
           |||+------ состояние S4
           ||+------- состояние S5
           |+-------- состояние S6
           +--------- состояние S7

Пакет данных состоит из этих 8 бит и не содержит никаких стартовых данных


Принимаемые денные
