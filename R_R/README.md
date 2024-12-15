# Отчет по расчетной работе по дисциплине ПиОИвИС.

### Цель:
Ознакомиться с основами теории графов, способами представления графов, базовыми алгоритмами для работы с разными видами графов.
### Условие задания:
Найти множество всех вершин графа удаление которых приведёт к увеличению количества компонентов связности
### Базовые понятия:
- Граф - совокупность двух множеств множества самих объектов, называемого множеством вершин, и множества их парных связей, называемого множеством рёбер.
- Неориентированный граф - граф, в котором все ребра являются звеньями, то есть порядок двух концов ребра графа не существенен.
- Компонент связности(слабый) - множемство всех связанных вершин графа.

### Алгоритм решения:
Подсчитать количество всязанных в компоненты вершин и сравнить с количеством компонентов после удаления каждой из вершин по очереди.

#### Небольшой алгоритм:
1. Перевести граф в неориентированный.
2. Подсчитать количество компонентов связности с помощью поиска в глубину.
3. Удалить каждую из вершин графа по очереди.
4. Сравнить с изначальным количеством компонентов.
5. Вывести результат.
### Пример матрицы смежности:
0 1 0 1 0
0 0 1 0 0
0 0 0 0 1
0 1 1 1 0
1 0 0 0 0

### Тест 1:

### Тест 2:

### Тест 3:



### Вывод:
В результате выполнения данной работы были получены следующие практические навыки:
- изучены основы теории графов
- изучены способы представления графов
- изучены базовые алгоритмы для работы с графами