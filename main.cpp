#include "stdafx.h"
#include "Header.h"

//void SetColor(ConsoleColor text, ConsoleColor background)
//{
//	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
//}
void SetColorText(ConsoleColor text){
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | text));
}
void SetColorBg( ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | 15));
}

void SetPosition(short x, short y){
	COORD position;                                     // Объявление необходимой структуры
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Получение дескриптора устройства стандартного вывода

	position.X = y;                //столбец                    // Установка координаты X
	position.Y = x;              //строка                      // Установка координаты Y

	SetConsoleCursorPosition(hConsole, position);
}


void PrintCol(ConsoleColor background){
	SetColorBg(background);
	cout << " ";
}
void randomEda(short *coordI, short *coordJ, short kolZ, short &edaI, short &edaJ){
		bool p;//не совпадает с координатами змейки
		short k1 = edaI, k2 = edaJ;
		do 
		{
			p = true;
			edaI = rand() % (n - 1);
			edaJ = rand() % (m - 1);
			//проверка на совпадение с координатами змейки
			for (short i = 0; i < kolZ&&p; ++i)
				if (coordI[i] == edaI&&coordJ[i] == edaJ)
					p = false;//совпало с координатами змейки
		} while ((k1 == edaI&&k2 == edaJ)||!p);//или совпадает с едой или совпадает со змейкой
		
}
void DrawPole(short *coordI, short *coordJ, short edaI, short edaJ){
	SetColorText(Green);
	/*Верхняя грань*/
	cout << (char)218;
	for (short i = 0; i < m ; ++i)
		cout << (char)196;
	cout << (char)191 << endl;
	/*------------------------------*/

	/*Основная часть*/
	for (short i = 0; i < n; ++i)
	{
		cout << (char)179;
		for (short j = 0; j < m; ++j)
			 cout << " ";
		cout << (char)179 << endl;
	}
	/*-------------*/
	/*Прорисовка змейки и пищи*/
	
	SetPosition(coordI[0] + 1, coordJ[0] + 1);
	PrintCol(Yellow);
	
	SetPosition(edaI + 1, edaJ + 1);
	PrintCol(LightGray);

	/*Нижняя грань*/
	SetPosition(n+1, 0);
	SetColorText(Green);
	cout << (char)192;
	for (short i = 0; i < m ; ++i)
		cout << (char)196;
	cout << (char)217 << endl;
	/*------------------------------*/

}
short Move(short side, short *coordI, short *coordJ, short &kolZ, short &edaI, short &edaJ){
	short  lastI = coordI[0], lastJ = coordJ[0], s; //s - переменная-пустой стакан

	switch (side){
	case Left:
		if (coordJ[0] > 0)   --coordJ[0];
		else return 1;
		break;
	case Top:
		if (coordI[0] > 0)   --coordI[0];
		else return 1;
		break;
	case Right:
		if (coordJ[0] < m - 1) ++coordJ[0];
		else return 1;
		break;
	case Bottom:
		if (coordI[0] < n - 1) ++coordI[0];
		else return 1;
		break;
	}
	/*проверка на сьедание пищи*/
	//short newI, newJ;
	if (coordI[0] == edaI&&coordJ[0] == edaJ) {
		
		//увеличение змейки на 1
		if (coordI[kolZ - 1] == coordI[kolZ - 2]){
			coordI[kolZ] = coordI[kolZ - 1];
			if (side==Left) 
				coordJ[kolZ] = coordJ[kolZ - 1]+1;
			else 
				coordJ[kolZ] = coordJ[kolZ - 1] - 1;
		}
		else{
			coordJ[kolZ] = coordJ[kolZ - 1];
			if (side == Top)
				coordI[kolZ] = coordI[kolZ - 1] + 1;
			else
				coordI[kolZ] = coordI[kolZ - 1] - 1;
		}
		++kolZ;
		//Рисуем голову позиции еды
			SetPosition(edaI + 1, edaJ + 1);
			PrintCol( Yellow);
		//Рисуем старое место головы в зел цвет.
			SetPosition(lastI + 1, lastJ + 1);
			PrintCol( Green);
		//
		randomEda(coordI, coordJ, kolZ, edaI, edaJ);
		/*рисуем новую пищу на экран*/
			SetPosition(edaI + 1, edaJ + 1);
			PrintCol(LightGray);
		/**/
	}
	else {
		/*проверка на сьедане самого себя*/
		for (int i = 3; i < kolZ; i += 2)
			if (coordI[0] == coordI[i] && coordJ[0] == coordJ[i]){
				switch (side){
				case Left:
					++coordJ[0];
					break;
				case Top:
					++coordI[0];
					break;
				case Right:
					--coordJ[0];
					break;
				case Bottom:
					--coordI[0];
					break;
				}
				return 1;
			}
			/*рисуем пробел на месте последней ячейки змеи*/
			SetPosition(lastI + 1, lastJ + 1);
			PrintCol(Black);
			/**/
			if (kolZ != 1){
				/*рисуем пробел на месте последней ячейки змеи*/
				SetPosition(coordI[kolZ - 1] + 1, coordJ[kolZ - 1] + 1);
				PrintCol( Black);
				/**/
				//Рисуем старое место головы в зел цвет.
				SetPosition(lastI + 1, lastJ + 1);
				PrintCol(Green);
				//
			}
			//Рисуем новое место головы.
			SetPosition(coordI[0] + 1, coordJ[0] + 1);
			PrintCol(Yellow);
			//
	}
		/*-----*/
		/**/
		for (int i = 1; i<kolZ; ++i){
			s = lastI;
			lastI = coordI[i];
			coordI[i] = s;
			s = lastJ;
			lastJ = coordJ[i];
			coordJ[i] = s;
		}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{/*
	if (_getch() == 224) cout<<"tou\n";
	cout << _getch() << " _ " << _getch() << endl;
	*/

	srand(time(0));
	short sumb1, sumb2, resGo = 0, edaI = 4, edaJ = 4, direction = Right, vvodCh, kolZ = 1, newKolZ, startI = 7, startY = 5, dellay = 200;
	short *coordI = new short[n*m-1];
	short *coordJ = new short[n*m - 1];

	
	SetPosition(0, 0);

	for (short i = 0; i < kolZ; ++i)
	{
		coordI[i] = startI-i;
		coordJ[i] = startY-1;
	}
		
	DrawPole(coordI, coordJ, edaI, edaJ);
	while (resGo == 0){
		SetPosition(22, 0);
		SetColorBg(Black);
			cout << kolZ << endl;
		if (_kbhit()){
			vvodCh = _getch();
			if (vvodCh == 224){
				switch (_getch()){
				case 75: if (direction == Top || direction == Bottom){
							 resGo = Move(Left, coordI, coordJ, kolZ, edaI, edaJ);
							 direction = Left;
				}
						 break;
				case 72: if (direction == Left || direction == Right){
							 resGo = Move(Top, coordI, coordJ, kolZ, edaI, edaJ);
							 direction = Top;
				}
						 break;
				case 77: if (direction == Top || direction == Bottom){
							 resGo = Move(Right, coordI, coordJ, kolZ, edaI, edaJ);
							 direction = Right;
				}
						 break;
				case 80: if (direction == Left || direction == Right){
							 resGo = Move(Bottom, coordI, coordJ, kolZ, edaI, edaJ);
							 direction = Bottom;
				}
						 break;
				}
			}
			else if (vvodCh == 32){
				SetColorBg(Black);
				cout << "Pause\n";
				system("pause");
			}
		}
		else {
			resGo = Move(direction, coordI, coordJ, kolZ, edaI, edaJ);
		}
			Sleep(dellay);
		//resGo = Move(direction, coordI, coordJ, kolZ);
			
	}
	SetColorBg(Black);
	if (resGo){
		cout << "Game Over!" << endl;
	}
	delete[] coordI;
	delete[] coordJ;


	system("pause");
	return 0;
}

