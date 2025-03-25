# Лабораторная работа №2

## Вариант 9

Условие:
> Реализовать программу, определяющую является ли одно, либо оба из двух исходных
множеств подмножеством или элементом другого.

**Тема** - работа с множествами.

**Цель лабораторной работы** - разработка программы для определения подмножества.

**Задача лабораторной работы** - научиться работать с множествами (в данном случае - при помощи C++).

## Определения, используемые при выполнении лабораторной работы

**Множество** – простейшая информационная конструкция и математическая структура,
позволяющая рассматривать какие-то объекты как целое, связывая их.

**Подмножество**: Неориентированное множество A называют подмножеством неориентированного множества B тогда и только тогда, когда для любого элемента х, который принадлежит множеству A, истинно A|x| принадлежит B|x|.

## Описание алгоритма
1. Необходимые для работы встроенные библиотеки C++:
	- *iostream* - ввод/вывод в консоль
	- *vector* - вектора, т.е. динамические массивы
	- *fstream* - работа с файлами
 	- *iterator* , *algorithm* - для функции sort
  	- *set* - для работы с множествами
2. Алгоритм:
Из файла получает 2 строки, проверяет их на правильность написания. Затем разбивает их на элементы, помещая эти элементы в два вектора. Далее эти вектора сравниваются для определения является ли первое множество подмножеством или элементом второго множества.
4. Функции:
<details>
<summary> *createFile* - создание файла.</summary>
	Если файл уже существует, он не будет удален.
</details>
<details>
<summary> *parse* - разбиение строки для работы с ней и перенос в вектор. </summary>
	Обычные элементы вносит в вектор, при встрече подмножеств или подкартежей вызывает функцию returnset и returntuple и полученные в их результате строки так же вносит в вектор.
</details>
<details>
<summary> *returnset* - обработка подмножества. </summary>
	Обычные элементы вносит в строку, при встрече подмножеств или подкартежей рекурсивно вызывает функцию returnset и returntuple и полученные в их результате строки так же добавляет в возвращаемое значение.
</details>
<details>
<summary> *returntuple* - обработка подкартежа. </summary>
	Обычные элементы вносит в строку, при встрече подмножеств или подкартежей рекурсивно вызывает функцию returnset и returntuple и полученные в их результате строки так же добавляет в возвращаемое значение.
</details>
<details>
<summary> *check* - функция проверки правильности входных данных. </summary>
	Проверяет наличие {} и вызывает функцию checkSet.
</details>
<details>
<summary> *checkSet* - проверка множества. </summary>
	Так же рекурсивно вызывает checkSet и checkTuple для проверки подмножеств и подкартежей.
</details>
<details>
<summary> *checkTuple* - проверка картежа. </summary>
	Так же рекурсивно вызывает checkSet и checkTuple для проверки подмножеств и подкартежей..
</details>
<details>
<summary> *iselement, isunderset* - финальнуе функции, дающие ответ на вопрос задачи. </summary>
	.
</details>
		
## Тесты

1. Тест на добавление элементов
```
TEST(jungtableTest, PushTest) {
    jungtable table;

    EXPECT_EQ(table.push(5), 0);  
    EXPECT_EQ(table.push(3), 0);  
    EXPECT_EQ(table.push(7), 0);  
    EXPECT_EQ(table.push(5), 404); 
}
```
2. Тест на удаление
```
TEST(jungtableTest, DeleteTest) {
    jungtable table;
    table.push(10);
    table.push(5);
    table.push(15);
    table.push(7);
    table.push(3);

    EXPECT_EQ(table.del(1, 1), 404); 
    EXPECT_EQ(table.del(1, 2), 404);
    EXPECT_EQ(table.del(2, 1), 404);
    EXPECT_EQ(table.del(2, 2), 0);
    std::vector<std::vector<int>> expected = { { 3, 15 }, { 5 }, { 10 } };
    EXPECT_EQ(table.body, expected);
    EXPECT_EQ(table.del(3, 1), 0); 
    expected = { { 5, 15 }, { 10 } };
    EXPECT_EQ(table.body, expected);
    EXPECT_EQ(table.del(2, 1), 0);
    EXPECT_EQ(table.del(1, 2), 0);
    EXPECT_EQ(table.del(1, 1), 0);
    expected = {  };
    EXPECT_EQ(table.body, expected);
}
```
3. Тест на сортировку элементов
```
TEST(jungtableTest, OrderTest) {
    jungtable table;
    table.push(10);
    table.push(5);
    table.push(15);
    table.push(7);
    table.push(3);

    std::vector<std::vector<int>> expected = { { 3, 7 }, { 5, 15 }, { 10 } };
    EXPECT_EQ(table.body, expected);
}
```
4. Проверка пустой таблицы
```
TEST(jungtableTest, EmptyTest) {
    jungtable table;
    EXPECT_TRUE(table.body.empty());  
}
```
5. Тест на вывод
```
TEST(jungtableTest, PrintTest) {
    jungtable table;
    table.push(8);
    table.push(2);
    table.print();
}
```


## Вывод

На C++ была создана библиотека, выполняющая основные действия с таблицами Юнга, а также программа с текстовым интерфейсом, приводящая данную библиотеку в действие.
