#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

typedef unsigned int unt;
using namespace std;

int main()
{
	//vector <pair <string, int>> dict;
	ifstream in(".\\as-caida20071105.txt");
	string line;

	/* "Правильный" алгоритм расходует слишком много времени, т.к. каждая операция проверки вхождения ноды занимает O(len)
	По данному алгоритму, сначала выясняем максимальный id ноды, далее заполняем количество соединений в vector[node_id]
	Такой будет потреблять куда больше памяти, но быть может это не критично.*/

	unt max_size = 0;
	while (getline(in, line)) {
		// Строчка с "Nodes:" не даёт корректной информации о максимальном id ноды, к сожалению.
		if (line[0] != '#')
		{
			stringstream str(line);
			for (int i = 0; i < 2; i++)
			{
				unt tmp;
				str >> tmp;
				if (tmp > max_size) max_size = tmp;
			}
		}
	}
	
	in.clear();
	in.seekg(0);

	vector <unt> nodes(++max_size);
	while (getline(in, line)) {
		if (line[0] != '#') 
		{
			stringstream str(line);
			for (int i = 0; i < 2; i++)
			{
				unt tmp;
				str >> tmp;
				nodes[tmp]++;
			}
		}
	}
	
	in.close();

	/* Недостаток такого алгоритма - сортировка значений невозможна, т.к. индекс часть данных.
	Требуется кастомная функция нахождения N максимумов.*/

	const unt N = 10;
	vector <pair <unt, unt>> mxs(N, { 0, 0 });
	
	for (unt i = 0; i < max_size; i++) {
		for (unt j = 0; j < N; j++) 
		{
			if (nodes[i] > mxs[j].second)
			{
				for (unt k = N - 1; k > j; k--)
					mxs[k] = mxs[k - 1];
				mxs[j] = { i, nodes[i] };
				break;
			}
		}
	}

	for (int i = 0; i < N; i++)
		cout << "Node #" << mxs[i].first << ", connections: " << mxs[i].second << endl;
	
}