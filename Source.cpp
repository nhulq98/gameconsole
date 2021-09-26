#include<iostream>
#include<Windows.h>
#include<time.h>
#include<string>
void XePlayer(int, int);
using namespace std;
 
// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);

}
// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

char map[50][50];

void XoaXeChuongNgai(int x, int y)
{
	map[x][y] = ' ';
	map[x][y - 1] = ' '; // ben trai than xe
	map[x][y + 1] = ' '; // ben phai than xe
	map[x - 1][y - 1] = ' '; // banh xe phia tren ben trai
	map[x + 1][y - 1] = ' '; // banh xe phia tren ben phai
	map[x - 1][y + 1] = ' '; // banh xe phia duoi ben trai
	map[x + 1][y + 1] = ' '; // banh xe phia duoi ben phai
}

void VeDuongDua()
{
	for(int i = 0; i < 40; i++)
	{
		map[i][0] = '|';
		map[i][39] = '|';
		if(i % 2 == 0)
		{
			map[i][19] = '|';
		}
		else
		{
			map[i][0] = '|';
			map[i][39] = '|';
			map[i][19] = ' ';

		}
		
		for(int j = i + 1; j < 39 && j != 19; j++)
		{
			map[i][j] = ' ';
		}
	
	}
}
void VeDuongDua2()
{

	for(int i = 0; i < 40; i++)
	{
		map[i][0] = '|';
		map[i][39] = '|';
		if(i % 2 != 0)
		{
			map[i][19] = '|';
		}
		else
		{
			map[i][0] = '|';
			map[i][39] = '|';
			map[i][19] = ' ';

		}
		for(int j = i + 1; j < 39 && j != 19; j++)
		{
			map[i][j] = ' ';
			
		}
	
	}
}

void InDuongDua()
{
	for(int i = 0; i < 30; i++)
	{
		cout << "\t\t\t\t\t";
		for(int j = 0; j < 40; j++)
		{			
			//=====IN duong dua======
			if(j == 0 || j == 39)
			{
				textcolor(191);// màu da trời nhạt
				map[i][j] = ' '; // cho mat đi mấy dấu gạch gạch ở 2 bên đường
				cout << map[i][j];
				textcolor(7);
			}
			/*else if(j == 19)
			{
				textcolor(4);
				cout << map[i][j];
				map[i][j] = ' ';
				textcolor(7);
			}*/
			//======IN XE PLAYER======
			else if(map[i][j] == 'N' ||map[i][j] == 'H' || map[i][j] == 'U' || map[i][j] == 'x')
			{
				textcolor(10);// màu xanh lá cây
				cout << map[i][j];
				textcolor(7);
			}
			//=========IN XE CHUONG NGAI============
			else if(map[i][j] == '!')
			{
				textcolor(192);// màu xanh lá cây
				//map[i][j] = ' ';
				cout << map[i][j];
				textcolor(7);
			}
			// nhung ky tu khong phai la xe
			else 
			{	
				cout << map[i][j]; // in ra khoảng trắng
			}		
		}
		cout << endl;
		
	}
	
}

void XePlayer(int x, int y)
{
	map[x][y] = 'H';
	map[x][y - 1] = 'N'; // ben trai than xe
	map[x][y + 1] = 'U'; // ben phai than xe
	map[x - 1][y - 1] = 'x'; // banh xe phia tren ben trai
	map[x + 1][y - 1] = 'x'; // banh xe phia tren ben phai
	map[x - 1][y + 1] = 'x'; // banh xe phia duoi ben trai
	map[x + 1][y + 1] = 'x'; // banh xe phia duoi ben phai
}

void XeChuongNgai(int x, int y)
{

	//map[x][y] = 'x'; // chop chu v
	//map[x - 1][y - 1] = 'x'; // ben trai chinh giua chu v
	//map[x - 2][y - 2] = 'x'; // ben trai ngoai cung chu v
	//map[x - 1][y + 1] = 'x'; // banh phai chinh giua chu v
	//map[x - 2][y + 2] = 'x'; // ben phai ngoai cung chu v

	map[x][y] = '!';
	map[x][y - 1] = '!'; // ben trai than xe
	map[x][y + 1] = '!'; // ben phai than xe
	map[x - 1][y - 1] = '!'; // banh xe phia tren ben trai
	map[x + 1][y - 1] = '!'; // banh xe phia tren ben phai
	map[x - 1][y + 1] = '!'; // banh xe phia duoi ben trai
	map[x + 1][y + 1] = '!'; // banh xe phia duoi ben phai

}

void DiChuyenXe(int &x, int &y, int &mang) // toa do hien tai cua cai xe
{
	/*
			trái trên cùng: 1 , 2
			trái dưới cùng: 28 , 2
			phải trên cùng: 1 , 37
			phải dưới cùng: 28 , 37
		*/
	if(x >= 1 && y > 2) // chặn ko cho dịch qua biên bên trái
	{
		if(GetAsyncKeyState(VK_LEFT))
		{
			if(map[x][y] == '!' || map[x][y - 1] =='!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' ||map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				//exit(0);
			}
			map[x][y] = ' ';
			map[x][y - 1] = ' '; // ben trai than xe
			map[x][y + 1] = ' '; // ben phai than xe
			map[x - 1][y - 1] = ' '; // banh xe phia tren ben trai
			map[x + 1][y - 1] = ' '; // banh xe phia tren ben phai
			map[x - 1][y + 1] = ' '; // banh xe phia duoi ben trai
			map[x + 1][y + 1] = ' '; // banh xe phia duoi ben phai
			XePlayer(x, y -= 1);
		}
	}
	if(y < 37) // chặn ko cho chạy qua biên bên phải
	{
		if(GetAsyncKeyState(VK_RIGHT))
		{
			if(map[x][y] == '!' || map[x][y - 1] =='!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' ||map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				//exit(0);
			}
			map[x][y] = ' ';
			map[x][y - 1] = ' '; // ben trai than xe
			map[x][y + 1] = ' '; // ben phai than xe
			map[x - 1][y - 1] = ' '; // banh xe phia tren ben trai
			map[x + 1][y - 1] = ' '; // banh xe phia tren ben phai
			map[x - 1][y + 1] = ' '; // banh xe phia duoi ben trai
			map[x + 1][y + 1] = ' '; // banh xe phia duoi ben phai
			XePlayer(x, y += 1);
		}
	}
	if(x > 1)// không cho lấn biên lên trên
	{
		if(GetAsyncKeyState(VK_UP))
		{
			
			map[x][y] = ' ';
			map[x][y - 1] = ' '; // ben trai than xe
			map[x][y + 1] = ' '; // ben phai than xe
			map[x - 1][y - 1] = ' '; // banh xe phia tren ben trai
			map[x + 1][y - 1] = ' '; // banh xe phia tren ben phai
			map[x - 1][y + 1] = ' '; // banh xe phia duoi ben trai
			map[x + 1][y + 1] = ' '; // banh xe phia duoi ben phai
			XePlayer(x -= 1, y);
		}
	}
	if(x < 28)// không cho lấn biên xuống dưới
	{
		if(GetAsyncKeyState(VK_DOWN))
		{
			map[x][y] = ' ';
			map[x][y - 1] = ' '; // ben trai than xe
			map[x][y + 1] = ' '; // ben phai than xe
			map[x - 1][y - 1] = ' '; // banh xe phia tren ben trai
			map[x + 1][y - 1] = ' '; // banh xe phia tren ben phai
			map[x - 1][y + 1] = ' '; // banh xe phia duoi ben trai
			map[x + 1][y + 1] = ' '; // banh xe phia duoi ben phai
			XePlayer(x += 1, y);
		}
	}
	

}



int main()
{

	int x = 25, y = 30, x1 = 2, x2 = 2, x3 = 2, y1 = 30, y2 = 3, y3 = 3;
	/*textcolor(12);
	cout << "\t\t\t\t\t\tChao mung ban den voi game\n";
	textcolor(14);
	cout << "\t\t\t\t\t\t----------DUA XE----------"<< endl;
	textcolor(7);*/
	int a = 0;
	int dem = 0;
	int mang = 0;
	while(true)
	{
		cout << "ngu: " << mang;
		//n++;
		a++;	// biến dùng để đếm
		dem++;
		
		if(a % 2 != 0)
		{
			VeDuongDua();
		}		
		else
		{
			VeDuongDua2();
				
		}		
		XePlayer(x, y);

		// radom
		/*
		muon random 1 so nguyen trong doan [a,b] thi dung ct sau
		srand(time(0)); // reset time
		x = a + rand() % (b - a + 1);
		*/
		// radom trong cot x[3, 36]	

		srand(time(0)); // reset time
		//y1 = 3 + rand() % (36 - 3 + 1);	
		if(y1 > 36)
		{
			y1 == 29;
		}
	
		//y2 = 3 + rand() % (36 - 3 + 1);
		
		//y3 = 3 + rand() % (36 - 3 + 1);
		XeChuongNgai(x1, y1); // xe tĩnh 1
		//XeChuongNgai(x1, y2);// xe tĩnh 2	 
		if(a % 37 == 0) // XE TĨNH
		{		
			x1 = x2 = x3 = 2;
			
		}
		// VAT PHAM
		//y = 3 + rand() % (36 - 3 + 1);
		map[x1][y2] = '$';

		if(map[x][y] == '!' || map[x][y - 1] =='!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' ||map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
		{
			mang++;
			//exit(0);
		}
		InDuongDua(); // phải add all các xe vào map rồi mới in map 
		DiChuyenXe(x, y, mang);
		XoaXeChuongNgai(x1, y1);
		map[x1][y2] = ' ';
		x1++;
		x2++;// biến dùng để xe dịch chuyển xuống
		x3++;
		XoaManHinh();	
		Sleep(0);	
	}

	system("pause");
	return 0;
}