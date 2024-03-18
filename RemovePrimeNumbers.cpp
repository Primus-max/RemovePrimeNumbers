// Написать функцию, которая получает указатель на динамический массив и его размер.Функция
// должна удалить из массива все простые числа и вернуть
// указатель на новый динамический массив.

#include <iostream>
#include <random>
#include <windows.h>
using namespace std;

// Заполнение массив
template<typename T>
void FillArray(T* arr, int size);

// Печать массива
template<typename T>
void PrintArray(T* arr, int size);

// Динамическое выделение памяти для массива
template<typename T>
T* AllocateMemory(T size);

// Очистка памяти
template<typename T>
void ClearMemory(T* arr);

// Подсчёт кол-ва простых чисел
template <typename T>
int CalcNewMemory(T* arr, int size);

// Проверка на простое число
template<typename T>
bool IsPrime(T number);

 // Удаление простых чисел
template<typename T>
T* RemovePrimeNumbers(T* arr, int& size);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int size;
	cout << "Какой размер у массива ? ";
	cin >> size;
	int* Array = AllocateMemory<int>(size);

	FillArray(Array, size);
	cout << "Заполненный массив " << endl;
	PrintArray(Array, size);

	cout << "Массив без целых чисел " << endl;
	int* removedPrimeNumbers = RemovePrimeNumbers<int>(Array, size);
	PrintArray(removedPrimeNumbers, size);
}


template<typename T>
void FillArray(T* arr, int size) {
	random_device random;
	for (T* i = arr; i < arr + size; i++)
		*i = random() % (100 + 50) - 50;
}

template<typename T>
void PrintArray(T* arr, int size) {
	for (int* i = arr; i < arr + size; i++)	
		cout << "[ " << *i << "] " << " ";	

	cout << endl;
}

template<typename T>
T* AllocateMemory(T size) {
	T* newArray = new int[size];
	return newArray;
}

template<typename T>
void ClearMemory(T* arr) { delete[] arr; };

template<typename T>
bool IsPrime(T number) {
	if (number <= 1)
		return false;

	T absNumber = abs(number); // Модуль числа
	for (T i = 2; i * i <= absNumber; ++i) {
		if (absNumber % i == 0)
			return false;
	}
	return true;
}

// Немного смухлевал и использовал []
template <typename T>
int CalcNewMemory(T* arr, int size) {
	int count = 0;
	for (int i = 0; i < size; ++i) {
		if (IsPrime(arr[i]))
			++count;
	}
	return count;
}

template<typename T>
T* RemovePrimeNumbers(T* arr, int& size) {
	if (arr == nullptr)
		return nullptr;

	int newSize = CalcNewMemory(arr, size);
	T* newArr = AllocateMemory<T>(size - newSize);
	if (newArr == nullptr)
		return nullptr;

	// Здесь тоже смухлевал, использовал [], иначе заблудился
	int newIndex = 0;
	for (int i = 0; i < size; ++i) {
		if (!IsPrime(arr[i])) {
			newArr[newIndex] = arr[i];
			++newIndex;
		}
	}

	size -= newSize;
	ClearMemory(arr); 
	return newArr; 
}
