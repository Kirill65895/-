#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");

	srand(time(0));

	system("title Змейка");
	system("mode con cols=70 lines=31");
	MoveWindow(GetConsoleWindow(), 500, 150, 380, 550, true); 

	const int width = 50, height = 30; 
	const int maxLenSnake = 50; 

	int coordX[maxLenSnake]; 
	int coordY[maxLenSnake]; 
	int startLen = 1;

	coordX[0] = width / 2; 
	coordY[0] = height / 2; 

	int dx = 1, dy = 0; 
	int X_apple; 
	int Y_apple; 
	do 
	{
		X_apple = rand() % (width - 2) + 1;
		Y_apple = rand() % (height - 2) + 1;
	} while (X_apple != coordX[startLen - 1] && Y_apple != coordY[startLen - 1]);

	//Скорость змейки; чем меньше значение, тем быстрее змейка!
	int sleep_time = 170;

	char snake = 'S'; 
	char apple = 'O'; 
	char head = 1; 

	COORD c; 
	HANDLE LineOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO Cursor = { sizeof(Cursor), false }; 

	SetConsoleCursorInfo(LineOutput, &Cursor);

	SetConsoleTextAttribute(LineOutput, 4);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			char s;
			if (x == 0 && y == 0)
				s = '#';
			else if (x == 0 && y == height - 1)
				s = '#';
			else if (y == 0 && x == width - 1) 
				s = '#'; 
			else if (y == height - 1 && x == width - 1) 
				s = '#'; 
			else if (y == 0 || y == height - 1) 
				s = '#';
			else if (x == 0 || x == width - 1) 
				s = '#'; 
			else s = ' '; 
			cout << s; 
		}
		cout << "\n";
	}
	//Яблоко
	c.X = X_apple; 
	c.Y = Y_apple;
	SetConsoleCursorPosition(LineOutput, c); 
	SetConsoleTextAttribute(LineOutput, 12); 
	cout << apple; 
	//Змейка
	c.X = coordX[0]; 
	c.Y = coordY[0];
	SetConsoleCursorPosition(LineOutput, c); 
	SetConsoleTextAttribute(LineOutput, 10); 
	cout << head; 
	//Наш ход
	bool state = true; 
	do 
	{
		Sleep(sleep_time);
		if (_kbhit()) 
		{
			int k = _getch();
			if (k == 0 || k == 224) // если первый код - вспомогательный, считываем второй код
				k = _getch();
			switch (k) 
			{
			case 's': 
				dy = 1; 
				dx = 0; 
				break;
			case 'w':
				dy = -1; 
				dx = 0;
				break;
			case 'a':
				dy = 0;
				dx = -1;
				break;
			case 'd': 
				dy = 0;
				dx = 1;
				break;
			case 27: // ESC
				state = false;
				break;
			}
		}

		int X = coordX[startLen - 1] + dx; 
		int Y = coordY[startLen - 1] + dy;

		if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) {
			state = false;
		}
		else if (X == X_apple && Y == Y_apple) {
			//Съел яблоко
			c.X = coordX[startLen - 1]; 
			c.Y = coordY[startLen - 1];
			SetConsoleCursorPosition(LineOutput, c); 
			cout << snake; 
			//Рост змейки
			startLen++; 
			c.X = coordX[startLen - 1] = X; 
			c.Y = coordY[startLen - 1] = Y;
			SetConsoleCursorPosition(LineOutput, c); 
			cout << head; 

			if (startLen == maxLenSnake)
			{
				break; 
			}
			int i; 
			//Ошибка позиции яблока
			do {
				X_apple = rand() % (width - 2) + 1; 
				Y_apple = rand() % (height - 2) + 1;
				i = 0; 
				for (; i < startLen; i++) 
					if (X_apple == coordX[i] && Y_apple == coordY[i]) 
						break; 
			} while (i < startLen); 
			//Позиция яблока
			c.X = X_apple; 
			c.Y = Y_apple;
			SetConsoleCursorPosition(LineOutput, c);
			SetConsoleTextAttribute(LineOutput, 12); 
			cout << apple; 
			SetConsoleTextAttribute(LineOutput, 10); 
		}
		//Столкновение змейки 
		else 
		{
			int i = 1; 
			for (; i < startLen; i++)
				if (X == coordX[i] && Y == coordY[i]) 
					break;
			if (i < startLen) 
				break;
			else 
			{
				c.X = coordX[0]; 
				c.Y = coordY[0];
				SetConsoleCursorPosition(LineOutput, c);
				cout << ' '; 
				//Если змейка увеличилась
				if (startLen > 1) 
				{
					c.X = coordX[startLen - 1]; 
					c.Y = coordY[startLen - 1];
					SetConsoleCursorPosition(LineOutput, c);  
					putchar(snake); 
				}
				//Движение звеньев змейки
				for (int i = 0; i < startLen - 1; i++) 
				{
					coordX[i] = coordX[i + 1]; 
					coordY[i] = coordY[i + 1];
				}
				//Движение головы змейки
				c.X = coordX[startLen - 1] = X; 
				c.Y = coordY[startLen - 1] = Y;
				SetConsoleCursorPosition(LineOutput, c); 
				cout << head; 
			}
		}
	} 
	while (state);
	system("cls");
	cout << "Игра окончена!\n"; 
}