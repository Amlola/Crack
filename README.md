# Исследование на уязвимости и взлом *.com файла

## Используемые инструменты:
+ IDA
+ Turbo Debugger
+ Makefile

## Виды взлома и их корректность
1) Взлом через переполнение буфера ввода:
   + Взлом должен быть выполнен без изменения исходного файла.
   + При запуске файла программы пользователь получает сообщение: `Hello, enter your password: `.
   + После ввода пароля, программа должна вывести сообщение: `Right password!`.
   + При наличии хеш-функции нельзя делать ее "reverse". Тем самым, получая верный пароль.
    
2) Взлом при помощи модификации бинарного файла:
   + Должна быть написана программа, которая подменяет нужный участый кода.
   + При запуске модифицированного бинарного файла должно быть получено сообщение: `Right password!`.

## Взлом через переполнение буфера ввода
После дизассемблировании исходного файла с помощью `IDA` был произведен поэтапный анализ функций программы. Первое, на что было обращено внимание, - это функция, содержащая в себе только вызовы других процедур. С высокой степенью вероятности она является главной в программе.

![main](/img/main.png)

Проанализировав код, первой вызываемой процедуры, было замечено, что используются 9 и 10 функция 21 прерывания. Первая из них выводит сообщение `Hello, enter your password: `. А вторая записывает пароль, введенный пользователем, в буффер.

![main](/img/first_func.png)

Воспользовавшись `Turbo Debugger`, я обнаружил, что под сам пароль выделено 10 байт. За ними лежит строка `canary` и еще один байт памяти. Строка `canary` является "канарейкой" в данной программе. При переполнении буффера ввода нужно обязательно ввести данную строку, иначе произойдет проверка и взлома не будет.

![main](/img/td.png)

Этот байт (выделено желтым) используется в фуннкции, которая сначала сравнивает его с 0, и в зависимости от результат печатает сообщение. Я предположил, что
это флаг активации. Изначально он равен 0. Если хеш, вычисленный программой, совпадает с правильным, в этот байт записывается 1. Из этого, я сделал вывод, что достаточно при вводе пароля переполнить буффер, учитывая канарейки, "затереть" флаг активации.

![main](/img/activate_flag.png)

Попробуем ввести пароль `1111111111canary1`. Как видно из картинки, взлом произведен успешно.

![main](/img/vzlom.png)

## Взлом с изменением исходного файла
При анализе остальных процедур программы, было замечено, что в одной функции имеются две проверки. По результам которых, либо происходит `jmp` на метку выхода из процедуры, либо изменения флага активации. Как было замечено раньше, в программе используется `canary` и хеш-функция. Я предположил, что как раз именно две эти проверки и происходят.

![main](/img/jmp.png)

В результате была написана программа, которая подменяет эти `jmp` (за `nop` данные участки кода). Также с использованием библиотеки `TxLib.h` была добавлена графика. В результате любой пароль, введеный пользователем, являлся правильным.

![main](/img/vzlom2.png)

![main](/img/picture.png)

## Для использования данного проекта склонируйте репозиторий в свою рабочую папку командой:
```bash
    git clone https://github.com/amlola/Crack.git
```
