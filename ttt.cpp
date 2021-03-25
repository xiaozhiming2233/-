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
		//轮到谁走，如果_p = 1，人走
		_p = rand() % 2;
		reset();
	}
	void play()
	{
		//res为结果，初始化为平局的状态
		int res = Draw;
		while (true)
		{
			drawGrid();
			while (true)
			{
				//人走
				if (_p) getHumanMove();
				else getComputerMove();
				drawGrid();
				res = checkVictory();
				//如果当前棋局状态已经可以判断出输赢，跳出循环
				if (res != None)
				{
					break;
				}
				//计数器+1，判断下一个是谁走
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

			//输入是否还想再玩一局
			string r;
			cout << "Play agin(Y/N)?";
			cin >> r;
			if (r != "Y" && r != "y")
				return;
			//计数器++
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
		//清屏
		system("cls");
		//定义控制台屏幕初始坐标
		COORD c = { 0, 2 };
		//设置控制台光标的位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

		//棋局初始状态
		cout << " 1 | 2 | 3 " << endl;
		cout << "---+---+---" << endl;
		cout << " 4 | 5 | 6 " << endl;
		cout << "---+---+---" << endl;
		cout << " 7 | 8 | 9 " << endl<<endl<<endl;

		//棋子计数器
		int f = 0;
		for(int y = 0; y < 5; y += 2) //纵坐标
			for (int x = 1; x < 11; x += 4) //纵坐标
			{
				if (_fileld[f] != None)
				{
					//光标位置坐标
					COORD c = { x, 2 + y };
					//设置控制台光标位置
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
					//判断当前下棋的人是否为电脑，如果是电脑输出X,否则输出O
					string o = _fileld[f] == Computer ? "X" : "O";
					cout << o;
				}
				f++;
			}

		c.Y = 9;
		//
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}

	//判断当前棋局是否可以判断输赢
	int checkVictory()
	{
		//一行一列或者对角，win
		for (int i = 0; i < 8; i++)
		{
			if (_fileld[iWin[i][0]] != None && _fileld[iWin[i][0]] == _fileld[iWin[i][1]] && _fileld[iWin[i][1]] == _fileld[iWin[i][2]])
			{
				return _fileld[iWin[i][0]];
			}
		}

		//i表示棋子个数
		int i = 0; 
		for (int f = 0; f < 9; f++)
		{
			//如果当前格子有棋子
			if (_fileld[f] != None)
				i++;
		}

		//如果满了，平局
		if (i == 9)
		{
			return Draw;
		}
		return None;
	}

	//人下棋
	void getHumanMove()
	{
		int m;
		cout << "Enter your move (1-9)";
		//开始死循环
		while (true)
		{
			m = 0;
			//输入先要下的棋子的格子编号
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

	//电脑下棋
	void getComputerMove()
	{
		//定义一个电脑想要下的棋子的格子编号
		int move = 0;
		do
		{
			//随机取得一个值
			move = rand() % 9;
		} 
		while (_fileld[move] != None);
		//
		for (int i = 0; i < 8; i++)
		{
			//try1,try2,try3表示可能赢的三个格子坐标
			int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];
			//如果try1，try2已经有棋子了，而且下棋子的玩家是一样的，而且try3没有棋子
			if (_fileld[try1] != None && _fileld[try1] == _fileld[try2] && _fileld[try3] == None)
			{
				//电脑下try3
				if (_fileld[try1] == Computer)
				{
					break;
				}
			}
			//如果try1和try3已经有棋子了，而且下棋子的玩家是一样的，而且try2没有棋子
			if (_fileld[try1] != None && _fileld[try1] == _fileld[try3] && _fileld[try2] == None)
			{
				//电脑下try3
				if (_fileld[try1] == Computer)
				{
					break;
				}
			}
			//如果try2和try3已经有棋子了，并且下棋子的玩家是一样的，而且try1没有棋子
			if (_fileld[try2] != None && _fileld[try2] == _fileld[try3] && _fileld[try1] == None)
			{
				//电脑下try3
				if (_fileld[try1] == Computer)
				{
					break;
				}
			}

		}
		//将第move个格子标记为电脑下的棋子
		_fileld[move] = Computer;
	}




	//计数器，用来判断当前的玩家是谁
	int _p;

	//格子状态
	int _fileld[9];
};

int main()
{
	srand(GetTickCount());

	ttt tic;

	tic.play();

	return 0;

}