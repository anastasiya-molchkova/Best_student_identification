/* На первом курсе M = 40 студентов. Каждый из них в понедельник получает оценку по программированию, 
во вторник — оценку по математике, в среду — по физике в пределах от 2 до 5 каждая. 
Всего в году N = 35 недель. 
Лучшим считается студент, который наибольшее количество недель продержался без троек (т.е. получал не ниже 4). 
Сформируйте три целых массива нужного размера. 
Задайте оценки с помощью генерации случайных чисел. 
Найдите лучшего студента. */

#include <iostream>
#include <array>
#include <cstdlib>   // для функций выбора случайного числа srand() и rand()
#include <ctime>     // чтобы в randomize опираться на время запуска программы

typedef unsigned short mark;  // mark - псевдоним типа

class Student_marks
{
private:
    // общая для всех студентов константа количества недель, за которые выставляются оценки:
    static const unsigned short number_of_weeks = 35;

    // три массива оценок за все недели:
    std::array<mark, number_of_weeks> programming;
    std::array<mark, number_of_weeks> math;
    std::array<mark, number_of_weeks> physics;

    // метод генерации случайной оценки:
    mark getRandomMark(mark min = 2, mark max = 5)
    {
        static const double fraction = 1.0 / static_cast<double>(RAND_MAX + 1.0);
        return static_cast<mark>(rand() * fraction * (max - min + 1) + min);
    }
public:
    // конструктор класса генерирует оценки студента за все недели:
    Student_marks()
    {
        for (unsigned i = 0; i < number_of_weeks; ++i)
        {
            programming[i] = getRandomMark();
            math[i]        = getRandomMark();
            physics[i]     = getRandomMark();
        }
    }

    // метод получает количество недель без плохих оценок
    unsigned get_weeks_without_bad_marks()
    {
        unsigned good_weeks{ 0 };
        // неделя хорошая, если по всем трём предметам у студента 4 или 5
        for (unsigned i = 0; i < number_of_weeks; ++i)
            if ((programming[i] > 3) && (math[i] > 3) && (physics[i] > 3))
                ++good_weeks;
        return good_weeks;
    }
};

int main()
{
    setlocale(LC_CTYPE, "rus");  // для вывода сообщений пользователю на кириллице

    // аналог randomize с привязкой ко времени запуска:
    srand(static_cast<unsigned int>(time(0)));
    rand();

    const unsigned number_of_students{ 40 };
    // заводим массив с количеством хороших недель для студентов
    std::array<unsigned, number_of_students> good_weeks_for_student{};
    // заполняем массив: для этого генерируем оценки для каждого студента
    for (unsigned i = 0; i < number_of_students; ++i)
    {
        Student_marks one_student;
        good_weeks_for_student[i] = one_student.get_weeks_without_bad_marks();
    }

    // для вычисления лучшего студента сначала лучшим полагаем первого в массиве (с индексом 0):
    unsigned index_of_the_best_student{ 0 };
    unsigned best_result = good_weeks_for_student[0];
    // проверяем результаты остальных студентов, сравнивая с лучшим:
    for (unsigned i = 1; i < number_of_students; ++i)
        if (good_weeks_for_student[i] > best_result)
        {
            index_of_the_best_student = i;
            best_result = good_weeks_for_student[i];
        }

    std::cout << "Лучшим является студент с номером " << (index_of_the_best_student+1) /* прибавляем 1, чтобы не было нулевого студента*/
              << ", у него " << best_result << " недель без плохих оценок.\n";
    
    return 0;
}