#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
int gameOver;
enum Smjer { UP, DOWN, LEFT, RIGHT };
Smjer smjer;
int HighScores[3] = { 0,0,0 };

class snake
{
private:
	const int poljeX = 40;
	const int poljeY = 20;
	int x, y;
	int hranaX, hranaY;
	int ascii, score;
	int duzina = 1;
private:
	struct Koordinate
	{
		int repX;
		int repY;
	}rep;
	vector<Koordinate> r;
	void Rep()
	{
		rep.repX = x;
		rep.repY = y;
		r.push_back(rep);
		if (r.size() > duzina)
		{
			r.erase(r.begin());
		}
	}
public:
	int key,diff;
	void random()
	{
		hranaX = rand() % 37 + 2;
		hranaY = rand() % 17 + 2;
	}
	void start()
	{
		x = poljeX / 2;
		y = poljeY / 2;
		random();
		gameOver = 0;
		score = 0;
		smjer = UP;
		Ucitaj();
	}
	void pozicija()
	{
		if (x > 39)
		{
			x = 1;
		}
		else if (x < 1)
		{
			x = 39;
		}
		else if (y > 19)
		{
			y = 1;
		}
		else if (y < 1)
		{
			y = 19;
		}
	}
	void polje()
	{
		pozicija();
		Rep();
		system("cls");
		for (int Yosa = 0; Yosa < poljeY; Yosa++)
		{
			for (int Xosa = 0; Xosa < poljeX; Xosa++)
			{
				if (Yosa == 0 || Yosa == poljeY - 1 || Xosa == 0 || Xosa == poljeX - 1)
				{
					cout << "#";
				}
				else if (Yosa == y && Xosa == x)
				{
					cout << "O";
				}
				else if (Xosa == hranaX && Yosa == hranaY)
				{
					cout << "X";
				}
				else
				{
					bool print = false;
					for (size_t i = 0; i < r.size(); i++)
					{
						if (r.at(i).repX == Xosa && r.at(i).repY == Yosa)
						{
							cout << "o";
							print = true;
						}
					}
					if (!print)
						cout << " ";
					
				}
			}
			cout << endl;
		}
		cout << "Score: " << score << endl;
	}
	void input()                    // a = 97, w = 119, s = 115, d = 100, ESC = 27
	{
		if (_kbhit())
		{
			ascii = _getch();
			switch (ascii)
			{
			case 97:
				if (smjer != RIGHT) 
				{
					smjer = LEFT;
				}
				break;
			case 119:
				if (smjer != DOWN)
				{
					smjer = UP;
				}
				break;
			case 115:
				if (smjer != UP)
				{
					smjer = DOWN;
				}
				break;
			case 100:
				if (smjer != LEFT)
				{
					smjer = RIGHT;
				}
				break;
			case 27: 
				system("cls");
				gameOver = 1;
				cout << "GAME OVER!";
				cout << endl;
				High_Scores();
				break;
			default:
				cout << "Pogresna Tipka";
				break;
			}
		}
	}
	void logika()
	{
		switch (smjer)
		{
		case LEFT:
			x--;
			break;
		case UP:
			y--;
			break;
		case RIGHT:
			x++;
			break;
		case DOWN:
			y++;
			break;
		}

		if (x == hranaX && y == hranaY)
		{
			random();
			score += 10;
			duzina++;
		}

		for (size_t i = 0; i < r.size(); i++)
		{
			if (x == r.at(i).repX && y == r.at(i).repY)
			{
				gameOver = true;
				system("cls");
				cout << "GAME OVER!" << endl;
				cout << endl;
				High_Scores();
			}
		}
	}
	void High_Scores()
	{
		int HighScores_temp[3];
		for (int i = 0; i < 3; i++)
		{
			HighScores_temp[i] = HighScores[i];
		}

		for (int i = 0; i < 3; i++)
		{
			if (score > HighScores[i])
			{
				HighScores[i] = score;
				if (i == 0)
				{
					if (HighScores_temp[i] > HighScores_temp[i + 1])
					{
						HighScores[i + 1] = HighScores_temp[i];
						if (HighScores_temp[i+1] > HighScores_temp[i + 2])
						{
							HighScores[i + 2] = HighScores_temp[i + 1];
						}
					}
				}
				else if (i == 1)
				{
					if (HighScores_temp[i + 1] > HighScores_temp[i + 2])
					{
						HighScores[i + 2] = HighScores_temp[i + 1];
					}
				}
				cout << "Score: " << HighScores[i];
				Spremi();
				break;
			}
		}
	}
	void Spremi()
	{
		ofstream output;
		output.open("rezultati.txt");
		output << HighScores[0] << "|" << HighScores[1] << "|" << HighScores[2] << endl;
	}
	void Ucitaj()
	{
		ifstream input;
		input.open("rezultati.txt");
		string cell;
		int temp = 0;
		while (!input.eof())
		{
			getline(input, cell, '|');
			if (temp == 0)
			{
				HighScores[temp] = atoi(cell.c_str());
				temp++;
			}
			else if (temp == 1)
			{
				HighScores[temp] = atoi(cell.c_str());
				temp++;
			}
			else if (temp == 2)
			{
				HighScores[temp] = atoi(cell.c_str());
				temp = 0;
			}
		}
	}
};

void New_Game(snake snake)						//w = 119, s = 115	
{
	system("cls");
	cout << "Select Difficulty( W / S ): " << endl;
	cout << "1.EASY " << endl;
	cout << "2.MEDIUM " << endl;
	cout << "3.HARD " << endl;
	cin >> snake.key;

	if (snake.key == 1)
		snake.diff = 100;
	else if (snake.key == 2)
		snake.diff = 70;
	else if (snake.key == 3)
		snake.diff = 35;
	else
		snake.diff = 70;

	snake.start();
	while (gameOver == 0)
	{
		snake.polje();
		snake.input();
		snake.logika();
		Sleep(snake.diff);
	}
}

void Scores(snake snake)
{
	cout << "=================" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << "." << HighScores[i] << endl;
	}
}

int main()
{
	srand(time(NULL));
	snake snake;
	int n;
	snake.Ucitaj();
	cout << "Controls: W - A - S - D" << endl;
	cout << "=======================" << endl;
	do {
		cout << endl;
		cout << "1.New Game" << endl;
		cout << "2.High Scores" << endl;
		cout << "0.EXIT" << endl;
		cin >> n;
		system("cls");
		if (n == 1)
		{
			New_Game(snake);
		}
		else if (n == 2)
		{
			Scores(snake);
		}
	} while (n != 0);
}