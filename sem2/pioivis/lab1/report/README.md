# Лабораторная работа №1

## Вариант 12

Условие:
> Таблица Юнга. Вставка элемента в таблицу. Удаление элемента из таблицы.

**Тема** - таблицы Юнга.

**Цель лабораторной работы** - разработка библиотеки для работы с таблицами Юнга.

**Задача лабораторной работы** - научиться работать со структурами и классами (в данном случае - при помощи C++).

## Определения, используемые при выполнении лабораторной работы

**Таблица Юнга** (далее в тексте "таблица") - структура данных, представляющая собой конечный набор ячеек или клеток, выровненных по левой границе, каждая из которых заполнена натуральными числами. В т.н. стандартной таблице Юнга длина каждой строки не больше предыдущей, числа возрастают в каждой строке и каждом столбце и при этом каждое число встречается в таблице ровно один раз.

## Описание класса *jungtable*

1. Необходимые для работы встроенные библиотеки C++:
	- *iostream* - ввод/вывод в консоль
	- *vector* - вектора, т.е. динамические массивы
	- *iomanip* - библиотека, в которой содержится модификатор setw
2. Класс *jungtable* реализован в виде двумерного вектора целых чисел, или же vector\<vector\<int\>\>.
3. Методы, используемые в классе *jungtable*:
<details>
<summary> *push* - добавление элемента в таблицу Юнга.</summary>

</details>
<details>
<summary> *delete* - удаление элемента из таблицы Юнга. </summary>

</details>
<details>
<summary> *print* - вывод таблицы Юнга на консоль. </summary>
	
</details>
		
## Тесты

1. Тест на добавление элементов
```
TEST(jungtableTest, PushTest) {
    jungtable table;

    EXPECT_EQ(table.push(5), 0);  // Успешное добавление 5
    EXPECT_EQ(table.push(3), 0);  // Добавление 3
    EXPECT_EQ(table.push(7), 0);  // Добавление 7
    EXPECT_EQ(table.push(5), 404); // Повторное добавление 5 должно вернуть 404
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

    EXPECT_EQ(table.del(1, 1), 404); // Неверный индекс
    EXPECT_EQ(table.del(1, 2), 404);
    EXPECT_EQ(table.del(2, 1), 404);
    EXPECT_EQ(table.del(2, 2), 0);
    std::vector<std::vector<int>> expected = { { 3, 15 }, { 5 }, { 10 } };
    EXPECT_EQ(table.body, expected);
    EXPECT_EQ(table.del(3, 1), 0); // Удаление первого элемента 
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
    EXPECT_TRUE(table.body.empty());  // Должно быть пусто в начале
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
