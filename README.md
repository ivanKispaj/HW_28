# HW_28
В качестве окончательного завершения модуля предлагаем вам решить итоговое задание.

## Звучит оно следующим образом:

    Доработайте алгоритм merge sort, описанный в 11 модуле, сделав его многопоточным.
    Используйте std::futurez в качестве инструмента для синхронизации результата работы потоков.
    Нужно определить независимые части алгоритма, которые могут быть распараллелены и запустить их вычисление в отдельных потоках, как это было сделано в юните 28.7.
    Потоки могут быть запущены через std::thread или std::async, но синхронизация строго через std::future. Также предусмотрите ограничение количества запускаемых потоков по примеру из юнита 28.7.


## Реализованно:
    1. при запуске сортировки, в отдельный поток запускается левая часть массива
    затем правая часть массива,
    2. Если еще есть свободные поттоки, то операция повторяется и половины запускаются в своих потоках.
    3. Если потоки исчерпаны, то дальнейшая ралота происходит в тех потоках что созданны...

## Результат:
тестовая машина:
**MacBook Pro 15 2017г intel core I7, 4 ядра 8 потоков...**

    Using counts thread: 8
    start multithreading test
    The time: 14.000000 seconds
    start one thread test:
    The time: 46.000000 seconds

**After bugfix**

    Using counts thread: 8
    start
    The time: 11.000000 seconds
    start one thread:
    The time: 48.000000 seconds
