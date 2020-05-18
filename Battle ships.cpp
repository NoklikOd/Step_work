#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <iomanip>

using namespace std;

struct Ship_cor {
	int x;
	int y;
};

bool add_shoot = false;
const int N = 10;
int Ships_id = 1;
int Ship[N+1] = { 0 };
int Ships_id_user = 1;
int Ship_user[N+1] = { 0 };

int** set_ships(int** map, int n);
bool chek_direction_ship(int** map, int n, int pal, Ship_cor ship, bool borders, int& direction);
void print_map_and_ships(int** map, int** mapUser, int n);
int** set_ships_User(int** map, int** mapUser, int n);
int** shoot_in_ship(int** map, int n, int** mapUser);
int** shoot_in_ship_pc_step(int** mapUser, int &firstHitx, int &firstHity,bool &for_dir, short &check_add_shoot_first_hit);
Ship_cor Direct(int direction, Ship_cor ship);
bool progressing(int Ships_id, int Ships_id_user,short &winer);


Ship_cor Direct(int direction, Ship_cor ship)
{
	
	switch (direction)
	{
	case 0:
	{
		ship.x++;
		break;
	}
	case 1:
	{
		ship.y++;
		break;
	}
	case 2:
	{
		ship.x--;
		break;
	}
	case 3:
	{
		ship.y--;
		break;
	}
	}
	return ship;
}
void print_map_and_ships(int** map, int** mapUser, int n)
{
	cout << setw(23) << "PC" << setw(62) << "User" << endl;
	cout << " ";
	for (int i = 0; i < n; i++)
	{
		cout << setw(4) << i + 1;
	}
	cout << setw(20);
	cout << " ";
	for (int i = 0; i < n; i++)
	{
		cout << setw(4) << i + 1;
	}


	cout << endl << "   ";
	for (int k = 0; k < n; k++)
	{
		cout << "----";
	}
	cout << setw(20);
	cout << "   ";
	for (int k = 0; k < n; k++)
	{
		cout << "----";
	}
	cout << endl;



	for (int i = 0; i < n; i++)
	{
		cout << setw(2) << i + 1;
		for (int j = 0; j < n; j++)
		{

			if (map[i][j] == 0)
			{
				cout << setw(3) << "|   ";//pustaya yacheika
			}
			if (map[i][j] >=1)
			{
				cout << setw(3) << "| O ";//korabl//////////////////////////////////////////open
			}
			if (map[i][j] ==-1)
			{
				cout << setw(3) << "| X ";//popal
			}
			if (map[i][j] == -9)
			{
				cout << setw(3) << "| + ";//ne popal
			}
			
			if (j == n - 1)
			{
				cout << "|";
			}

		}
		cout << setw(20) << i + 1;
		for (int j = 0; j < n; j++)
		{

			if (mapUser[i][j] == 0)
			{
				cout << setw(3) << "|   ";
			}
			if (mapUser[i][j] >=1)
			{
				cout << setw(3) << "| O ";
			}
			if (mapUser[i][j] == -1)
			{
				cout << setw(3) << "| X ";

			}
			if (mapUser[i][j] == -9)
			{
				cout << setw(3) << "| + ";//ne popal karta user
			}
			
			if (j == n - 1)
			{
				cout << "|";
			}

		}
		cout << endl << "   ";
		for (int k = 0; k < n; k++)
		{
			cout << "----";
		}
		cout << setw(20);
		cout << "   ";
		for (int k = 0; k < n; k++)
		{
			cout << "----";
		}
		cout << endl;

	}
}
bool progressing(int Ships_id, int Ships_id_user,short &winer)
{
	if (Ships_id == 1)
	{
		winer = 1;
		return false;
	}
	if (Ships_id_user == 1)
	{
		winer = 2;
		return false;
	}
	return true;
}
bool chek_direction_ship(int** map, int n, int pal, Ship_cor ship, bool borders, int& direction)
{
	
	borders = true; //borders - границы 		
	//проверка направления по границе
	for (int i = 0; i < pal; i++)// количество палуб
	{
		if (ship.x < 0 || ship.y < 0 || ship.x >= 9 || ship.y >= 9)
		{
			borders = false;
			break;
		}
		if (ship.x > 0 && ship.y > 0)
		{
			if (map[ship.x - 1][ship.y - 1] >= 1)
			{
				borders = false;
				break;
			}
		}
		if (ship.x > 0 && ship.y < 9)
		{
			if (map[ship.x - 1][ship.y + 1] >= 1)
			{
				borders = false;
				break;
			}
		}
		if (ship.x > 0)
		{
			if (map[ship.x - 1][ship.y] >= 1)
			{
				borders = false;
				break;
			}
		}
		if (ship.x < 9 && ship.y>0)
		{
			if (map[ship.x + 1][ship.y - 1] >= 1)
			{
				borders = false;
				break;
			}
		}
		if (ship.x < 9 && ship.y < 9)
		{
			if (map[ship.x + 1][ship.y + 1] >= 1)
			{
				borders = false;
				break;
			}
		}
		if (ship.x < 9)
		{
			if (map[ship.x + 1][ship.y]>= 1)
			{
				borders = false;
				break;
			}
		}
		if (ship.y > 0)
		{
			if (map[ship.x][ship.y - 1]>= 1)
			{
				borders = false;
				break;
			}
		}
		if (ship.y < 9)
		{
			if (map[ship.x][ship.y + 1] >= 1)
			{
				borders = false;
				break;
			}
		}
		if (map[ship.x][ship.y] >= 1)
		{
			borders = false;
			break;
		}
		ship = Direct(direction, ship);
	}
	return borders;
}
int** set_ships(int** map, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			map[i][j] = 0;
		}
	}
	Ship_cor ship;
	int direction;//napravlenie
	int ships = 0;	//vse korabli
	int pal = 4;	//kol palub
	int shipPal = 1;	//kol korablya
	int palShips = 0;
	while (ships < 10)
	{
		while (palShips < shipPal)
		{
			ship.x = rand() % n;
			ship.y = rand() % n;
			int x = ship.x;
			int y = ship.y;
			bool borders = true; //borders - границы
			direction = rand() % 4;
			borders = chek_direction_ship(map, N, pal, ship, borders, direction);
			if (borders == true)
			{
				palShips++;
				ships++;
				ship.x = x;
				ship.y = y;
				for (int i = 0; i < pal; i++)
				{
					map[ship.x][ship.y] = Ships_id;					
					ship = Direct(direction, ship);
				}
				Ship[Ships_id] = pal;
				Ships_id++;
			}
		}
		palShips = 0;
		shipPal++;
		if (pal == 0 || shipPal > 4)
		{
			break;
		}
		pal--;
	}
	return map;
}


int** set_ships_User(int** map, int** mapUser, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mapUser[i][j] = 0;
		}
	}
	Ship_cor ship;
	int direction;//napravlenie
	int ships = 0;	//vse korabli
	int pal = 4;	//kol palub
	int shipPal = 1;	//kol korablya
	int palShips = 0;
	while (ships < 10)
	{

		while (palShips < shipPal)
		{
			print_map_and_ships(map, mapUser, n);

			cout << "Введите горизонталь для начальной точки \" " << pal << " \" палубного корабля ";
			cin >> ship.y;
			ship.y--;
			cout << "Введите вертикаль для начальной точки \" " << pal << " \" палубного корабля ";
			cin >> ship.x;
			ship.x--;
			if (pal > 1)
			{
				cout << "Введите координату направления роста корабля" << endl
					<< "0- В низ" << endl
					<< "1- В право" << endl
					<< "2- В верх" << endl
					<< "3- В лево" << endl;
				cin >> direction;
			}
			int x = ship.x;
			int y = ship.y;
			bool borders = true; //borders - границы
			borders = chek_direction_ship/*_user*/(mapUser, n, pal, ship, borders, direction);
			if (borders == false)
			{
				cout << "Введено не верно! Повторите попытку." << endl;
			}
			if (borders == true)
			{
				palShips++;
				ships++;
				ship.x = x;
				ship.y = y;
				for (int i = 0; i < pal; i++)
				{
					mapUser[ship.x][ship.y] = Ships_id_user;
					ship = Direct(direction, ship);
				}
				Ship_user[Ships_id_user] = pal;
				Ships_id_user++;
			}
			system("cls");
		}
		palShips = 0;
		shipPal++;
		if (pal == 0 || shipPal > 4)
		{
			break;
		}
		pal--;
	}
	return mapUser;
}

int** shoot_in_ship(int** map, int n,int** mapUser)
{

	bool step = true;
	while (step == true)
	{
		Ship_cor ship;
		cout << endl << endl << "Введите удар по вертикали: ";
		cin >> ship.x;
		cout << "Введите удар по горизонтали: ";
		cin >> ship.y;
		ship.x -= 1;
		ship.y -= 1;

		if (ship.x > 9 || ship.y > 9)
		{
			cout << "Не верно" << endl;
			Sleep(500);
			system("cls");
			print_map_and_ships(map, mapUser, n);
			continue;
		}
		if (map[ship.x][ship.y] <0)
		{
			cout << "Не верно" << endl;
		}
		if (map[ship.x][ship.y] == 0)
		{
			map[ship.x][ship.y] = -9;
			cout << "Не попал" << endl;
			step = false;
		}
		if (map[ship.x][ship.y] >=1)
		{
			Ship[map[ship.x][ship.y]]--;
			if (Ship[map[ship.x][ship.y]] <=0)
			{			
				cout << "Убит !" << endl;
			}
			else
			{
				cout << "YA RANIL" << endl;
				cout << "Ранил !" << endl;
			}
			map[ship.x][ship.y] = -1;
			Ships_id--;
		}
		Sleep(1000);
		system("cls");
		print_map_and_ships(map,mapUser, n);
	}
	cout << "MOI YDAR" << endl;
	Sleep(400);
	return map;
}

//рабочий вариант
int** shoot_in_ship_pc_step(int** mapUser, int &firstHitx, int &firstHity,bool &for_dir,short & check_add_shoot_first_hit)
{
	Ship_cor ship={ 0,0 };// иначе Warning и вылетает ошибка
	int direction = 9;
	bool chek_step = true;

	while (chek_step == true)
	{
		
		if (add_shoot == false)
		{
			ship.x = rand() % 9;
			ship.y = rand() % 9;

			if (mapUser[ship.x][ship.y] < 0)
			{
				chek_step = true;
			}
			if (mapUser[ship.x][ship.y] == 0)
			{
				mapUser[ship.x][ship.y] = -9;
				cout << "ПК Промахнулся." << endl;
				chek_step = false;
			}
			
			if (mapUser[ship.x][ship.y] >= 1)
			{
				Ship[mapUser[ship.x][ship.y]]--;
				if (Ship[mapUser[ship.x][ship.y]] <= 0)
				{
					chek_step = true;
					add_shoot = false;
					cout << "Убит !" << endl;
				}
				else
				{
					chek_step = true;
					firstHitx = ship.x;
					firstHity = ship.y;
					add_shoot = true;
					for_dir = true;
					cout << "PC RANIL" << endl;
					cout << "Ранил !" << endl;
				}
				mapUser[ship.x][ship.y] = -1;
				Ships_id_user--;
			}
			//первый выстрел совершен, если попадание то...
			//если корабль убит к примеру одно палубный, выходим в цикл СНЕК и совершаем второй случаиный выстрел
			//в случае если корабль ранен, запоминаем координаты попадания Х и У 
			//говорим что дополнительный удар ТРУ и заходим в иф доп удар тру
		}	

		if (add_shoot == true)
		{			
			if (check_add_shoot_first_hit == 1)
			{
				ship.x = firstHitx;
				ship.y = firstHity;
				check_add_shoot_first_hit = 0;
			}
			
			while (for_dir == true)
			{
				if (ship.x > 9 || ship.x < 0 || ship.y>9 || ship.y < 0)
				{
					ship.x = firstHitx;
					ship.y = firstHity;
					break;
				}
				cout << "FOR_DIR" << endl;
	
				if (ship.x < 9 && mapUser[ship.x + 1][ship.y] >= 1)
				{
					direction = 0;
					for_dir = false;
					cout << "if 1" << endl;
				}

				else if (ship.y < 9 && mapUser[ship.x][ship.y + 1] >= 1)
				{
					direction = 1;
					for_dir = false;
					cout << "if 2" << endl;
				}
				else if (ship.x > 0 && mapUser[ship.x - 1][ship.y] >= 1)
				{
					direction = 2;
					for_dir = false;
					cout << "if 3" << endl;
				}
				else if (ship.y > 0 && mapUser[ship.x][ship.y - 1] >= 1)
				{
					direction = 3;
					for_dir = false;
					cout << "if 4" << endl;
				}
				else {}				
			}

			ship = Direct(direction,ship);
			//после проверки направления пробуем делать удар
			cout << "POSLE SWITCH I DIR" << endl;

			if (mapUser[ship.x][ship.y]< 0)
			{
				add_shoot = true;
				for_dir = true;
			}
			if (mapUser[ship.x][ship.y] >= 1/*&&add_shoot==true*/)
			{
				cout << "BOI" << endl;
				Ship[mapUser[ship.x][ship.y]]--;
				if (Ship[mapUser[ship.x][ship.y]] <= 0)
				{
					cout << "ПК Убит !" << endl;
					chek_step = true;
					add_shoot = false;
					for_dir = false;					
				}
				else
				{
					cout << "ПК Ранил !" << endl;
					chek_step = true;// проверка 
					add_shoot = true;
					for_dir = false;
				}
				mapUser[ship.x][ship.y] = -1;
				Ships_id_user--;
			}
		
			cout << "IFI YBIT ILI RANEN PERED PROMAHOM" << endl;
			if (mapUser[ship.x][ship.y] == 0)
			{
				mapUser[ship.x][ship.y] = -9;//-9 промах
				cout << "ПК Промахнулся." << endl;
				check_add_shoot_first_hit= 1;
				chek_step = false;
				add_shoot = true;
				for_dir = true;
			}
		}
		cout << "KONEC CIKLA CHEK_STEP" << endl;
	}
	cout << "PC GOTOV" << endl;
	Sleep(400);
	return mapUser;
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned)time(0));
	

	int** map = new int* [N];
	for (int i = 0; i < N; i++)
	{
		map[i] = new int[N];
	}

	int** mapUser = new int* [N];
	for (int i = 0; i < N; i++)
	{
		mapUser[i] = new int[N];
	}
	
	int firstHitx = 0;
	int firstHity = 0;
	short winer;
	bool progres = true;
	bool for_dir = true;
	short check_add_shoot_first_hit = 0;

	map = set_ships(map, N);

	mapUser = set_ships(mapUser, N);/*set_ships_User(mapUser, mapUser, N);*/
		
	while (progres == true)
	{
		print_map_and_ships(map, mapUser, N);
		shoot_in_ship(map, N,mapUser);
		shoot_in_ship_pc_step(mapUser, firstHitx,firstHity,for_dir, check_add_shoot_first_hit);		
		system("cls");
		progres=progressing(Ships_id,Ships_id_user,winer);
	}
	if (winer==1)
	{
		cout << "Выиграл Пользователь!" << endl;
	}
	if (winer==2)
	{
		cout << "Выиграл компьтер!" << endl;
	}
	cout << "Игра окончена!" << endl;
	for (int j = 0; j < N; j++)
	{
		delete[] map[j];
	}
	delete[] map;
	return 0;
}
