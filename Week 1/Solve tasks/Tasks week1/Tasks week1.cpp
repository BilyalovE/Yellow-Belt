#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <locale.h>
#include <map>
#include <limits>
#include <tuple>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;

class Matrix {
public:
	vector <vector <int>> m;
	Matrix() : rows(0), cols(0) {}
	Matrix(const int num_rows, const int num_cols) {
		if (rows < 0 || cols < 0) {
			string str = "Неправильные размеры матрицы!";
			throw out_of_range(str);
		}
		else {
			rows = num_rows;
			cols = num_cols;
		}
	}

	void Reset(const int num_rows, const int num_cols) {
		m.resize(num_rows, vector <int>(num_cols, 0));
		rows = num_rows;
		cols = num_cols;
	}

	int at(const int num_rows, const int num_cols) const {
		if (num_rows > rows || num_cols > cols) {
			string str = "неправильные размеры матрицы!";
			throw out_of_range(str);
		}
		else {
			return m[num_rows - 1][num_cols - 1];
		}
	}

	int& At(const int num_rows, const int num_cols) {
		if (num_rows > rows || num_cols > cols) {
			string str = "Неправильные размеры матрицы!";
			throw out_of_range(str);
		}
		else {
			return m[num_rows - 1][num_cols - 1];
		}
	};

	int GetNumRows() const { return rows; }
	int GetNumColumns() const { return cols; }

	void PrintMatrix() const {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				cout << m[i][j] << " ";
			}
			cout << "\n";
		}
	}

	void SetMatrix() {
		Reset(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				cin >> m[i][j];
			}
		}
	}

private:
	int rows, cols;
};

istream& operator>>(istream& stream, Matrix& matrix) {
	int num_rows, num_cols;
	stream >> num_rows >> num_cols;
	try {
		Matrix new_matrix(num_rows, num_cols);
		new_matrix.SetMatrix();
		matrix = new_matrix;
	}
	catch (exception ex) {
		cout << ex.what() << endl;
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Matrix matrix) {
	cout << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	matrix.PrintMatrix();
	return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
		for (int i = 0; i < lhs.GetNumRows(); ++i) {
			for (int j = 0; j < lhs.GetNumColumns(); ++j) {
				if (lhs.m[i][j] == rhs.m[i][j]) {
					continue;
				}
				else {
					return false;
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
		Matrix sum_m;
		sum_m.Reset(lhs.GetNumRows(), lhs.GetNumColumns());
		for (int i = 0; i < lhs.GetNumRows(); ++i) {
			for (int j = 0; j < lhs.GetNumColumns(); ++j) {
				sum_m.m[i][j] = lhs.m[i][j] + rhs.m[i][j];
			}
		}
		return sum_m;
	}
	else {
		string str = "Матрицы имеют разный размер!";
		throw invalid_argument(str);
	}
}

TEST(Week_1, Task_1) {
	setlocale(LC_ALL, "Russian ");
	Matrix m_one;
	Matrix m_two;
	cin >> m_one;
	cout << endl;
	//cin >> m_two;
	int a = m_one.At(3, 5);
	cout << a << endl;
}

/*
* Задание по программированию: Средняя температура — 2
Решите задачу «Средняя температура» в других ограничениях на входные данные.

Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.

Гарантируется, что среднее арифметическое значений температуры является целым числом.

Формат ввода
Вводится число N, затем N целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день. Гарантируется, что N не превышает миллиона (10^6), а значения температуры, измеряющиеся в миллионных долях градусов по Цельсию, лежат в диапазоне от −10^8 до 10^8. Проверять соблюдение этих ограничений не нужно: вы можете ориентироваться на них при выборе наиболее подходящих типов для переменных.

Формат вывода
Первое число K — количество дней, значение температуры в которых выше среднего арифметического. Затем K целых чисел — номера этих дней.

Пример
Ввод
5
5 4 1 -2 7
Вывод
3
0 1 4
*/
TEST(Week_1, Task_2) {
	int N;
	cin >> N;
	vector<int16_t> temp(N);
	int64_t sum = 0;
	for (size_t i = 0; i < N; ++i) {
		;
		cin >> temp[i];
		sum += temp[i];
	}
	int avg = sum / static_cast<int>(temp.size());
	vector<size_t> num_index;
	for (size_t index = 0; index < temp.size(); ++index) {
		if (temp[index] > avg) {
			num_index.push_back(index);
		}
	}
	size_t K = num_index.size();
	cout << K << endl;
	for (size_t index : num_index) {
		cout << index << " ";
	}
	cout << "\n";
}



/*
Задание по программированию: Масса блоков
Вычислите суммарную массу имеющих форму прямоугольного параллелепипеда бетонных блоков одинаковой плотности, но разного размера.

Указание
Считайте, что размеры блоков измеряются в сантиметрах, плотность — в граммах на кубический сантиметр, а итоговая масса — в граммах. Таким образом, массу блока можно вычислять как простое произведение плотности на объём.

Формат ввода
В первой строке вводятся два целых положительных числа: количество блоков N и плотность каждого блока R. Каждая из следующих N строк содержит три целых положительных числа W, H, D — размеры очередного блока.

Гарантируется, что:

количество блоков N не превосходит 10^5;
плотность блоков R не превосходит 100;
размеры блоков W, H, D не превосходят 10^4.
Пример
Ввод
2 14
1 2 3
30 40 50
Вывод
840084*/
TEST(Week_1, Task_3) {
	int N;
	int R;
	cin >> N >> R;
	int W, H, D;
	uint64_t sum_m = 0;
	while (N) {
		cin >> W >> H >> D;
		sum_m += static_cast<int64_t>(W) * H * D * R;
		--N;
	}
	cout << sum_m << endl;
}

/*
Тренировочное задание по программированию: База регионов
Имеется база регионов, представленная вектором структур Region:

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
Здесь Lang — идентификатор языка:

enum class Lang {
  DE, FR, IT
};
Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и определяющую,
какое максимальное количество повторов она содержит. Две записи (объекты типа Region) считаются различными,
если они отличаются хотя бы одним полем.

int FindMaxRepetitionCount(const vector<Region>& regions);
Если все записи уникальны, считайте максимальное количество повторов равным 1. Если записи отсутствуют, верните 0.
Гарантируется, что типа int достаточно для хранения ответа.

Пример кода
int main() {
  cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  },
  }) << endl;

  cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Toulouse",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  31
	  },
  }) << endl;

  return 0;
}
Вывод
3
1
Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией функции FindMaxRepetitionCount,
а также дополнительных функций, если это необходим. Этот файл не должен содержать типы Lang и Region.
В противном случае вы получите ошибку компиляции.
*/

enum class Lang {
	DE, FR, IT
};
struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

int FindMaxRepetitionCount(const vector<Region>& regions) {
	if (regions.size() != 0) {
		vector <tuple<string, string, map<Lang, string>, int64_t>> list_tuple;
		for (const auto& reg : regions) {
			list_tuple.push_back(make_tuple(reg.std_name, reg.parent_std_name, reg.names,
				reg.population));
		}
		vector<int> repetitionCount(regions.size(), 1);
		for (size_t i = 0; i < list_tuple.size() - 1; ++i) {
			for (size_t j = i + 1; j < list_tuple.size(); ++j) {
				if (list_tuple[i] == list_tuple[j]) {
					++repetitionCount[i];
				}
			}
		}
		if (*max_element(begin(repetitionCount), end(repetitionCount)) == 1) {
			return 1;
		}
		else {
			return *max_element(begin(repetitionCount), end(repetitionCount));
		}
	}
	else {
		return 0;
	}
}


TEST(Week_1, Task_4) {
	cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  },
		}) << endl;

	cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Toulouse",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			31
		},
		}) << endl;
}

// Задание по программированию: Трекер задач

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

void operator+=(TasksInfo& lhs, TasksInfo& rhs) {
	for (const auto& [task_status, num] : lhs) {
		lhs[task_status] += rhs[task_status];
	}
}

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return test.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		++inform_on_status_tasks[person][TaskStatus::NEW];
		++test[person][TaskStatus::NEW];
	}


	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
  		inform_on_status_tasks[person][TaskStatus::IN_PROGRESS];
		inform_on_status_tasks[person][TaskStatus::TESTING];
		inform_on_status_tasks[person][TaskStatus::DONE];
		inform_on_status_tasks[person] += updated_status_tasks[person];
		updated_status_tasks.clear();
		int num_uncompleted_tasks = 0;
		for (const auto& [task_status, num_tasks] : inform_on_status_tasks[person]) {
			if (task_status != TaskStatus::DONE) {
				num_uncompleted_tasks += num_tasks;
			}
		}
		int tasks_in_new_status = 0;
 		for (const auto& [task_status, num_tasks] : inform_on_status_tasks[person]) {
			if (task_count > num_uncompleted_tasks) {
				task_count = num_uncompleted_tasks;
			}
			if (task_count > 0) { 
				if (task_status != TaskStatus::DONE) {
					if (task_count < num_tasks) {
						inform_on_status_tasks[person][task_status] -= task_count;
						updated_status_tasks[person][static_cast<TaskStatus>(static_cast<int>(task_status) + 1)] = task_count;
						task_count = 0;
					}
					else {
						tasks_in_new_status = num_tasks;
						updated_status_tasks[person][static_cast<TaskStatus>(static_cast<int>(task_status) + 1)] = tasks_in_new_status;
						inform_on_status_tasks[person][task_status] = 0;
						task_count -= tasks_in_new_status;
					}
				}
				else {
					break;
				}
			}
		}
		for (const auto& [task_status, num_tasks] : inform_on_status_tasks[person]) {
			if (inform_on_status_tasks[person].count(task_status) == 0) {
				inform_on_status_tasks[person].erase(task_status);
			}
			if (updated_status_tasks[person].count(task_status) == 0) {
				updated_status_tasks[person].erase(task_status);
			}
		}
		test[person] = inform_on_status_tasks[person];
		test[person] += updated_status_tasks[person];
		return tie(updated_status_tasks[person], inform_on_status_tasks[person]);
	}



private:
	map<string, TasksInfo> inform_on_status_tasks, updated_status_tasks, test;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

TEST(Week_1, Task_5) {
	TeamTasks tasks;
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << "\n";
	cout << "\n";
	cout << "\n";
	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	cout << "\n";
	tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	cout << "\n";
}

/*
* Задание по программированию: Всё в квадрат
Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров. Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:

для vector элементы нужно возвести в квадрат;
для map в квадрат нужно возвести только значения, но не ключи;
для pair в квадрат нужно возвести каждый элемент пары.
// Пример вызова функции
vector<int> v = {1, 2, 3};
cout << "vector:";
for (int x : Sqr(v)) {
  cout << ' ' << x;
}
cout << endl;

map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
};
cout << "map of pairs:" << endl;
for (const auto& x : Sqr(map_of_pairs)) {
  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}
Код выше должен вывести

vector: 1 4 9
map of pairs:
4 4 4
7 16 9
Функция должна корректно работать не только для контейнеров, состоящих из чисел, но и для составных объектов, например, векторов словарей пар чисел.

Для успешной сдачи решения необходимо сделать предварительное объявление шаблонных функций перед всеми шаблонными функциями.

Пример предварительного объявления шаблонной функции

// Предварительное объявление шаблонных функций
template<typename T> T FuncA(T x);
template<typename T> void FuncB(T x);

// Объявляем шаблонные функции
template <typename T>
T FuncA(T x) { /*...*/ //}

/*template <typename T>
void FuncB(T x) { /*...
Зачем это нужно и как это работает вы узнаете далее из наших курсов.
*/

// Предварительное объявление шаблонных функций

////Для вектора
//template <typename T> 
//vector <T> Sqr(const vector <T>& vec);
//
//
//// Для словаря
//template <typename Key, typename Value> 
//map <Key, Value> Sqr(const map <Key, Value>& m);
//
//// Для пары
//template<typename K, typename V> 
//pair<K, V> Sqr(const pair<K, V>& value);
//
//// Для простых типов
//template <typename T> T Sqr(const T);
//
//
//
//// Объявляем шаблонные функции
//// Для простых типов
//template <typename T>
//T Sqr(T x) {
//	return x * x;
//}
//
////Для вектора
//template <typename T>
//vector <T> Sqr(vector <T>& vec) {
//	vector <T> result;
//	for (const auto&  item:  vec) {
//		result.push_back(Sqr(item));
//	}
//	return result;
//}
//
//// Для пары
//template<typename K, typename V>
//pair<K, V> Sqr(const pair<K, V>& p) {
//	return { Sqr(p.first), Sqr(p.second) };
//}
//
//
//template <typename Key, typename Value>
//map<Key, Value>& Sqr(map<Key, Value>& m) {
//	map<Key, Value> result;
//	for (const auto [key, value] : m) {
//		result[key] = Sqr(value);
//	}
//	return result;
//}


// ВТОРОЙ СПОСОБ - БОЛЕЕ ПРАВИЛЬНЫЙ
template <typename T> T Sqr(T x);

template <typename T> 
vector <T> operator*(const vector<T>& v1, const vector<T>& v2);

template <typename Key, typename Value> 
pair <Key, Value> operator*(const pair<Key, Value>& p1, const pair<Key, Value>& p2);

template <typename Key, typename Value>
map <Key, Value> operator*(const map<Key, Value>& m1, const map<Key, Value>& m2);


template <typename T>
vector <T> operator*(const vector<T>& vec1, const vector<T>& vec2) {
	vector <T> result;
	for (const auto& item : vec1) {
		result.push_back(Sqr(item));
	}
	return result;
}

template<typename Key, typename Value>
pair<Key, Value> operator*(const pair<Key, Value>& p1, const pair<Key, Value>& p2) {
	Key key = p1.first * p2.first;
	Value value = p1.second * p2.second;
	return { key, value };
}

template <typename Key, typename Value>
map <Key, Value> operator*(const map<Key, Value>& m1, const map<Key, Value>& m2) {
	map <Key, Value> result;
	for (const auto& [key, value] : m1) {
		result[key] = Sqr(value);
	}
	return result;
}


template <typename T>
T Sqr(T x) {
	return x * x;
}




TEST(Week_1, Task_6) {
	// Пример вызова функции
	//vector<pair <int, double>> v = { {1, 1.1}, {2, 2.2} };

	pair <int, double> p{ 1, 1.1 };
	cout << "pair:";
	cout << ' ' << Sqr(p).second;
	cout << endl;
	vector <int> v = { 1, 2, 3 };
	cout << "vector:";
	for (const auto& x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<double, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {1.1, 3}}
	};

	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
}

/*
Задание по программированию: Ссылка на элемент
Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: map и значение ключа k.
Если элемент по ключу k в коллекции отсутствует, то функция должна бросить исключение runtime_error, 
иначе вернуть ссылку на элемент в коллекции.

Пример использования функции*/
template<typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& input_map, const KeyType key) {
	if (input_map.count(key) == 0) {
		throw runtime_error("no such key in dictionary");
	}
	return input_map.at(key);
}



TEST(Week_1, Task_7) {
	map<int, string> m = { {0, "value"} };
	try {
		string& item = GetRefStrict(m, 0);
		item = "newvalue";
		cout << m[0] << endl; // выведет newvalue
	}
	catch (exception& ex){
		cout << ex.what() << endl;
	}
	
}