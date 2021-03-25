#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

//mode
enum players { Computer, Human, Draw, None};
//win chance
const int iWin[8][3] = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };

class ttt
{
public:
	ttt()
	{
		//�ֵ�˭�ߣ����_p = 1������
		_p = rand() % 2;
		reset();
	}
	void play()
	{
		//resΪ�������ʼ��Ϊƽ�ֵ�״̬
		int res = Draw;
		while (true)
		{
			drawGrid();
			while (true)
			{
				//����
				if (_p) getHumanMove();
				else getComputerMove();
				drawGrid();
				res = checkVictory();
				//�����ǰ���״̬�Ѿ������жϳ���Ӯ������ѭ��
				if (res != None)
				{
					break;
				}
				//������+1���ж���һ����˭��
				++_p %= 2;
			}
			//
			if (res == Human)
			{
				cout << "HUMAN WIN";
			}
			else if (res == Computer)
			{
				cout << "COMPUTER WIN";
			}
			else
			{
				cout << "WIN WIN";
			}
			cout << endl << endl;

			//�����Ƿ�������һ��
			string r;
			cout << "Play agin(Y/N)?";
			cin >> r;
			if (r != "Y" && r != "y")
				return;
			//������++
			++_p %= 2;
			reset();
		}
		
	}

private:
	void reset()
	{
		for (int x = 0; x < 9; x++)
			_fileld[x] = None;
			
	}

	void drawGrid()
	{
		//����
		system("cls");
		//�������̨��Ļ��ʼ����
		COORD c = { 0, 2 };
		//���ÿ���̨����λ��
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

		//��ֳ�ʼ״̬
		cout << " 1 | 2 | 3 " << endl;
		cout << "---+---+---" << endl;
		cout << " 4 | 5 | 6 " << endl;
		cout << "---+---+---" << endl;
		cout << " 7 | 8 | 9 " << endl<<endl<<endl;

		//���Ӽ�����
		int f = 0;
		for(int y = 0; y < 5; y += 2) //������
			for (int x = 1; x < 11; x += 4) //������
			{
				if (_fileld[f] != None)
				{
					//���λ������
					COORD c = { x, 2 + y };
					//���ÿ���̨���λ��
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
					//�жϵ�ǰ��������Ƿ�Ϊ���ԣ�����ǵ������X,�������O
					string o = _fileld[f] == Computer ? "X" : "O";
					cout << o;
				}
				f++;
			}

		c.Y = 9;
		//
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}

	//�жϵ�ǰ����Ƿ�����ж���Ӯ
	int checkVictory()
	{
		//һ��һ�л��߶Խǣ�win
		for (int i = 0; i < 8; i++)
		{
			if (_fileld[iWin[i][0]] != None && _fileld[iWin[i][0]] == _fileld[iWin[i][1]] && _fileld[iWin[i][1]] == _fileld[iWin[i][2]])
			{
				return _fileld[iWin[i][0]];
			}
		}

		//i��ʾ���Ӹ���
		int i = 0; 
		for (int f = 0; f < 9; f++)
		{
			//�����ǰ����������
			if (_fileld[f] != None)
				i++;
		}

		//������ˣ�ƽ��
		if (i == 9)
		{
			return Draw;
		}
		return None;
	}

	//������
	void getHumanMove()
	{
		int m;
		cout << "Enter your move (1-9)";
		//��ʼ��ѭ��
		while (true)
		{
			m = 0;
			//������Ҫ�µ����ӵĸ��ӱ��
			cin >> m;
			if (_fileld[m - 1] != None)
				cout << "Invalid move. Try agin!" << endl;
			//else
			else
			{
				break;
			}
		}
		_fileld[m - 1] = Human;
	}

	//��������
	void getComputerMove()
	{
		//����һ��������Ҫ�µ����ӵĸ��ӱ��
		int move = 0;
		do
		{
			//���ȡ��һ��ֵ
			move = rand() % 9;
		} 
		while (_fileld[move] != None);
		//
		for (int i = 0; i < 8; i++)
		{
			//try1,try2,try3��ʾ����Ӯ��������������
			int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];
			//���try1��try2�Ѿ��������ˣ����������ӵ������һ���ģ�����try3û������
			if (_fileld[try1] != None && _fileld[try1] == _fileld[try2] && _fileld[try3] == None)
			{
				//������try3
				if (_fileld[try1] == Computer)
				{
					break;
				}
			}
			//���try1��try3�Ѿ��������ˣ����������ӵ������һ���ģ�����try2û������
			if (_fileld[try1] != None && _fileld[try1] == _fileld[try3] && _fileld[try2] == None)
			{
				//������try3
				if (_fileld[try1] == Computer)
				{
					break;
				}
			}
			//���try2��try3�Ѿ��������ˣ����������ӵ������һ���ģ�����try1û������
			if (_fileld[try2] != None && _fileld[try2] == _fileld[try3] && _fileld[try1] == None)
			{
				//������try3
				if (_fileld[try1] == Computer)
				{
					break;
				}
			}

		}
		//����move�����ӱ��Ϊ�����µ�����
		_fileld[move] = Computer;
	}




	//�������������жϵ�ǰ�������˭
	int _p;

	//����״̬
	int _fileld[9];
};

int main()
{
	srand(GetTickCount());

	ttt tic;

	tic.play();

	return 0;

}