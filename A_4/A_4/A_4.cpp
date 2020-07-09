#include <iostream>
#include <fstream>
#include <locale>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

int N; // ���-�� ������
const int INF = 999; // �������������

 /*���� ����� �� �����, ��������� ��� ������ ������� � ����� ����*/
void input_matrix(ifstream &in, int **graph)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			in >> graph[i][j];
}


/* ������ ����� c ���� ����(����� � graphic.png) */
void print_graph(int **graph) {
	ofstream out;
	out.open("graphic.dot");
	out << "graph G{" << "\n";
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (graph[i][j] != 0 && i < j)
				out << i + 1 << " -- " << j + 1 << "\n";
	out << "}";
	out.close();
	system("dot -Tpng graphic.dot -o graphic.png ");
	system("graphic.png");
}

/*������� �� ������� � ��������� �����*/
void matrix_to_vector(int **graph, vector<vector<int>>& VGraph) {

	for (int i = 0; i < N; i++)
	{
		VGraph.push_back(vector<int>());
		for (int j = 0; j < N; j++)
		{
			VGraph[i].push_back(0);
			VGraph[i][j] = graph[i][j];
		}
	}
}

/*����� ���������� ��� ��������*/
/*
void rezout(vector<int> array_res)
{
	cout << "����� ������������� = " << array_res.size() << endl << "��������� ������� �� ���������: ";
	for (unsigned i = 0; i < array_res.size(); i++)
		cout << array_res[i] + 1 << " ";
	cout << endl;
}
*/

/*�������� ��������� ������*/
vector<int> set_used(int index, vector<vector<int>> graph, vector<int> used)
{
	for (int i = 0; i < N; i++)
		if (graph[index][i] == 1 || i == index)
			used[i] = 1;
	return used;
}

/*�������� ����������� ��������*/
vector<int> find_array_rec(int index, vector<vector<int>> graph, vector<int> used, vector<int> res)
{
	vector<int> tmp_used;
	vector<int> tmp_res;
	vector<int> tmp_used_add;

	res.push_back(index);
	tmp_used = set_used(index, graph, used);

	for (int i = 0; i < N; i++)
	{
		if (tmp_used[i] == 0)
		{	
			/*������ �� ������ ������� ��������*/
			for (int j = i + 1; j < N && tmp_used[j] != 1; j++)
				if (tmp_used[j] == 0) {
					tmp_used_add = tmp_used;
					for (int k = i ; k < j; k++) tmp_used_add[k] = 1;
					tmp_res = find_array_rec(j, graph, tmp_used_add, res);

					if (tmp_res.size() > res.size())
						return tmp_res;
					else
						return	res;
				}
				

			tmp_res = find_array_rec(i, graph, tmp_used, res);

			if (tmp_res.size() > res.size())
				return tmp_res;
			else
				return	res;
		}
	}
	return res;
}

/*����� ����������� ������������ ���������*/
vector<int> search_array(vector<vector<int>> graph)
{
	vector<int> used(graph.size());
	vector<int>	tmp_res;
	vector<int> empty;
	vector<int> res;

	for (int i = 0; i < N; i++)
	{
		tmp_res = find_array_rec(i, graph, used, empty);
		if (tmp_res.size() > res.size())
			res = tmp_res;
	}
	return res;
}

/*-----------------------------------------------------------------------------------------------------*/

/* �������� �������
ifs - ������� �����;
ofs - �������� �����;
*/

int main() {
	ifstream ifs;
	ofstream ofs;
	setlocale(LC_ALL, "rus");

	try {
		int ans;
		do {
			cout << "������������� ���� �����? (1-��, 0 -���)." << endl;
			cin >> ans;
			if (ans == 1) system("input.txt");
		} while (ans != 1 && ans != 0);

		ifs.open("input.txt");
		ifs >> N;

		int **graph_cost_m = new int*[N]; //�������� �������
		for (int i = 0; i < N; i++)
		{
			graph_cost_m[i] = new int[N];
			for (int j = 0; j < N; j++)
				graph_cost_m[i][j] = 0;
		}

		input_matrix(ifs, graph_cost_m);

		do {
			cout << "������� ����? (1-��, 0 -���)." << endl;
			cin >> ans;
			if (ans == 1) print_graph(graph_cost_m);
		} while (ans != 1 && ans != 0);

		vector <vector<int>> graph_cost_v;
		matrix_to_vector(graph_cost_m, graph_cost_v);

		//����� ����������� ������������ ���������
		vector<int> result;
		result = search_array(graph_cost_v);

		/*����� ���������� � ����*/
		ofs.open("output.txt");

		ofs << "����� ������������� = " << result.size() << endl << "��������� ������� �� ���������: ";
		for (unsigned i = 0; i < result.size(); i++)
			ofs << result[i] + 1 << " ";
		ofs << endl;

		ofs.close();

		do {
			cout << "������� ���������? (1-��, 0 -���)." << endl;
			cin >> ans;
			if (ans == 1) system("output.txt"); //�������� ����������
		} while (ans != 1 && ans != 0);
	}

	catch (...) {
		cout << "������ �����!";
	}

	cout << "��������� ���������." << endl;
	return 0;
}
