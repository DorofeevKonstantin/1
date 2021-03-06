# Matrices

## Вводное задание

_Это задание не будет проверяться, но крайне рекомендуется выполнить его, чтобы ознакомиться в упрощённом виде с основным функционалом, который вам будет необходимо реализовать в работе. Этим вы сэкономите себе время при написании самой лабораторной работы._

Имеется 2 файла с записанными в них матрицами размера 3x3:

Программа считывает матрицы в память в виде двумерных статических массивов, а затем рассчитывает и выводит результат произведения матрицы A на транспонированную матрицу B.

### Пример

#### Файл `matrix-A.txt`:

```
1 2 3
1 1 1
3 3 3
```

#### Файл `matrix-B.txt`:

```
0 0 0
1 1 1
2 2 2
```

#### Результат

```
0 6 12
0 3 6
0 9 18
```



## Основное задание

Напишите программу-калькулятор для матриц.

### Требования:

* Матрицы считываются из файлов

  * Пример матрицы в файле:

    ```
    1 2 3
    4 5 6
    7 8 9
    ```

* Размер матрицы в файле определяется программой автоматически, он не указывается пользователем и не записывается в самом файле с матрицей

- Поддерживаемые операции и баллы за них:
  - сложение двух матриц **(0.1)**
  - вычитание одной матрицы из другой **(0.1)**
  - перемножение двух матриц **(0.2)**
  - транспонирование матрицы **(0.2)**
  - нахождение определителя матрицы **(0.4)**
- Должен быть реализован интуитивно понятный пользователю текстовый либо псевдографический интерфейс в командной строке.
- Программа должна корректно завершать своё исполнение при любом сценарии использования.