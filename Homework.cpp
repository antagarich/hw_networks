/* Домашнее задание по курсу "Сети и телекоммуникации"
Вариант №11
Информационный вектор: 1011010001
Код: Ц[15,11]
Способность кода: Со
Корнуков Никита, ИУ5-53 */

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

using namespace std;

//функция нахождения остатка
bitset<15> division(bitset<15> dividend, bitset<5> divisor)
{
	for (int i = 10; i >= 0; i--)
	{
		if (dividend[4+i] != 0)
		{
			for (int j = 4; j >= 0; j--)
				dividend[j+i] = dividend[j+i] ^ divisor[j];
		}
	}
	return dividend;
}

//Функция кодирования
bitset<15> get_vect(bitset<11> previous_vect,bitset<5> divisor_vect)
{
	bitset<15> vect = 0;
	bitset<15> remainder = 0;

	for (int i = 11; i < 15; i++)
		vect[i] = previous_vect[i-4];

	remainder = division(vect,divisor_vect);
	for(int i=0; i<4; i++) vect[i]=divisor_vect[i];
	return vect;
}

//Функция проверки синдрома ошибки
void check_errors(bitset<15> vect, int error, bitset<5> divisor_vect, int** multiplicity_number)
{
	bitset<15> error_vect = error;
	int multiplicity = 0;

	for (int i = 0; i<15; i++)
	{
		if (error_vect[i])
		{
			multiplicity++;
			vect[i] = vect[i] ^ error_vect[i];
		}
	}
	multiplicity_number[0][multiplicity]++;

	//обнаружение ошибки
	if (division(vect, divisor_vect) != 0) multiplicity_number[1][multiplicity]++;

}

int main()
{
	int** multiplicity_number = new int*[2];
	for (int i = 0; i < 2; i++)
	{
		multiplicity_number[i] = new int[16];
		for (int j = 0; j < 16; j++) multiplicity_number[i][j] = 0;
	}

	bitset<11> previous_vect = 721;//1011010001
	bitset<5> divisor_vect = 19;//10011
	bitset<15> vect = 0;

	vect = get_vect(previous_vect, divisor_vect);

	for (long i = 1; i < 32768; i++)
		check_errors(vect, i, divisor_vect, multiplicity_number);
	cout << "+--------------------------+\n";
	cout << "|  i |  Cin |   No |    Co |\n";
	cout << "+--------------------------+\n";
	for (int i = 1; i < 16; i++){
		cout << "|" << setw(3) << i << " | " << setw(4) << multiplicity_number[0][i] << " | " << setw(4) << multiplicity_number[1][i] << " | " << setw(5) << setprecision(3) << (double)multiplicity_number[1][i] / (double)multiplicity_number[0][i] << " |\n";
	};
	cout << "+--------------------------+\n";
	system("pause");
	for (int i = 0; i < 2; i++)
		delete multiplicity_number[i];
	delete[] multiplicity_number;
	return 0;
} 

