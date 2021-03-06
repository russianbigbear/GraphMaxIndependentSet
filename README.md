## Поиск наибольшего максимального независимого множества

### Задание 
Найти наибольшее максимальное независимое множество.

### Алгоритм
В начале сформируем файл ввода “input.txt”. Который в начале можно отредактировать.
* Первая строчка в файле – это количество вершин в графе.
* В матрице смежности 0 означает отсутствие ребра {I, j}, а цифра больше 1 – наличие {I, j}.

По желанию выводим граф, используя GraphViz. <br/>
Для удобства, переведем наш массив в векторную форму. Создадим вектор хранящий результат и вызовем алгоритма поиска максимального независимого множества.<br/>
<br/>
В цикле для каждой вершины мы находим независимые множества и сравниваем их размер пока не найдем максимальное из них.<br/>
Независимы множества мы находим рекурсивно, вызывая одну и ту же функцию.
1. В начале мы передаем в функцию первую точку(Index) независимого множества (далее н.м.), матрицу смежности, вектор пометок, и вектор результата.
2. Далее создаём временные два вектора пометок и вектор результата (они пригодятся в работе). 
3. Переходим к работе поиска. Заносим начальную вершину в вектор результата. 
4. Далее формируем временный вектор пометок, который заполняем, использую функцию проверки смежности вершин. 
5. В неё мы подаем Index, матрицу смежности, вектор пометок. Данная функция заполняет переданный массив пометок,
в соответствии с правилом, проходя по циклу от 0 до N (количество вершин): “если есть ребро из вершины Index с концом i или вершина i равна Index,
то в массиве пометок used[i] = 1». После данная функция возвращает сформированный по правилу вектор пометок. 
6. Теперь идём по массиву пометок полученному ранее и если I’ая вершина равна 0, то вызываем функцию вновь.
Так же возможен случай, когда не только I’ая вершина равна 0, но и вершина I + 1, I + 2 и т.д.
Тогда у нас может быть другая комбинация вершин (другое независимое множество), поэтому если такое случается,
то мы дополнительно формируем независимое множество для другой вершины, а потом для I’ой.
7. Теперь рекурсивно выходим из функции и если полученное н.м. больше чем вектор с начальной точкой, то возвращаем его,
иначе возвращаем начальный вектор результата, созданный в начале работы функции.
8. После того как мы нашли независимые множества для каждой точки от 0 до N и среди них нашли максимальное, мы его возвращаем в главную программу.
9. Теперь заносим результат в файл, используя ранее полученное независимое множество.

По желанию выводим или нет текстовый файл с результатом.

