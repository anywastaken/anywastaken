#include <stack>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

using namespace std;

//поиск в глубину
void dfs(int** mas, int n, stack<int>& fool, bool* visited)
{
	int top = fool.top();
	visited[top] = true;
	fool.pop();

	for (int j = 0; j < n; j++)
	{
		if (mas[top][j] == 1 && !visited[j])
		{
			fool.push(j);
		}
	}


	if (!fool.empty())
	{
		dfs(mas, n, fool, visited);
	}
}

//проверка посещаемости
bool cond(bool* visited, int n, int& start)
{
	for (int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			start = i;
			return false;
		}
	}
	return true;
}

int main()
{
	//ввод данных
	setlocale(LC_ALL, "RU");
	int n;
	cout << "Введите колличество вершин графа:" << endl;
	cin >> n;
	int** mas = new int* [n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mas[j][i] = 0;
		}
	}
	cin.ignore();
	vector<vector<int>> spis(n);
	cout << "Список смежности:" << endl;
	for (int i = 0; i < n; i++) {
		cout << "Соседи вершины " << i+1 << ": ";
		string line;
		getline(cin, line); 
		stringstream ss(line);
		int neighbor;
		while (ss >> neighbor) {
			spis[i].push_back(neighbor);
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < spis[i].size(); j++)
		{
			mas[i][spis[i][j]-1] = 1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (mas[i][j] == 1)
			{
				mas[j][i] = 1;
			}

		}

	}
	
	//определение кол-ва компонент связности
	stack<int> fool;
	int start = 0;

	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
	{
		visited[i] = false;
	}

	int comp = 0;

	while (!cond(visited, n, start))
	{
		fool.push(start);
		comp++;
		dfs(mas, n, fool, visited);
	}
	int sres = comp;

	cout << "\nРезультат: ";

	//сравнение с удаленной вершиной
	for (int k = 0; k < n; k++)
	{
		start = 0;
		int** nmas = new int* [n - 1];
		for (int i = 0; i < n - 1; i++)
		{
			nmas[i] = new int[n - 1];
		}
		for (int i = 0; i < n; i++)
		{
			if (i != k)
			{
				for (int j = 0; j < n; j++)
				{
					if (j != k)
					{
						nmas[i - (i > k)][j - (j > k)] = mas[i][j];

					}
				}
			}
		}

		//граф без вершины
		for (int i = 0; i < n - 1; i++)
		{
			visited[i] = false;
		}

		//определение кол-ва компонент связности
		comp = 0;
		while (!cond(visited, n - 1, start))
		{
			fool.push(start);
			comp++;
			dfs(nmas, n - 1, fool, visited);
		}

		//сравнение
		if (sres < comp)
		{

			cout << k + 1 << " ";
		}

		for (int i = 0; i < n - 1; i++)
		{
			delete[]nmas[i];
		}
		delete[]nmas;
	}

	delete[]visited;


	for (int i = 0; i < n; i++)
	{
		delete[]mas[i];
	}
	delete[]mas;

	return 0;
}
