/*
   ___ ___ ____ ____ ____ ____ ____ ____ ____ ___ ___ ___
  |  	_          _  __     ___      _            		|
  |    / \   _ __ | |_\ \   / (_) ___| |_ ___ _ __ 		|
  |   / _ \ | '_ \| '_ \ \ / /| |/ _ \ __/ __| '__|		|
  |  / ___ \| | | | | | \ V / | |  __/ || (__| |   		|
  |	/_/   \_\_| |_|_| |_|\_/  |_|\___|\__\___|_|   		|
  |			Coding By Anhvietcr - fb.com/anhvietcr		|
  |		Build in Code::Blocks 16.01 & Dev C++ 5.11      |
  |                Game Snaker v2.0                     |
  |_ ___ ____ ____ ____ ____ ____ ____ ____ ____ ____ __|

*/

#define _WIN32_WINNT 0x500	//using resize console

#include <windows.h>	//resize console
#include <iostream>		//cout, cin
#include <conio.h>		//getch, kbhit
#include <stdlib.h>		//rand
#include <ctime>		//time rand
#include <stdio.h>		//fflush
#include <fstream>		//file
#include <string>		//string

using namespace std;
//resize cmd
void ResizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
//color
void Textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}
// di chuyen den toa do x, y
void GotoXY(int x,int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x-1,y-1};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
//an con tro chuot
void HideCursor()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
//ve khung
void HienThi(){
	//in vien ngang
	for(int i=5; i<70; i++){
		Textcolor(10);
		GotoXY(i, 4); cout << char(205);
		GotoXY(i, 30); cout << char(205);
	}
	//in vien doc
	for(int i=5; i<30; i++){
		GotoXY(4, i); cout << char(186);
		GotoXY(70, i); cout << char(186);
	}
	//in 4 goc
		GotoXY(70,30); cout<< char(188);
		GotoXY(70,4); cout<< char(187);
		GotoXY(4,4); cout<< char(201);
		GotoXY(4,30); cout<< char(200);
}
//map[j][i] = map[hang][cot]
int maps[200][200];			//ma tran, 200 = do dai max cua snake
int x=10,y=10;				//toa do snake ban dau
int dot=10;					//dot cua snake ban dau
int savedot;				//save diem cao nhat
int dichuyen = 1;			//di chuyen ban dau
int n=1;					//khoi tao gia tri
int VTx = 10, VTy = 15;		//toa do thuc an ban dau
int mang = 3;				//mang (live) ban dau
int speed = 0;				//speed 1,2,3,4
string spe;					//text speed
char kytu;					//read char file
ifstream files;				//read file
ofstream file;				//write file

void SaveScore(){	//luu diem vao file
	file.open("data/save.txt", ios::out);
	if(!file){cout<<"Khong doc duoc file...";}
	file << dot-2;
	file.close();
}
void LoadScore(){	//load diem ra man hinh
	files.open("data/save.txt", ios::out);
		if (!files){cout << "File khong ton tai..";}
	files >> savedot;
}
void DieuKien(){		//tang dot len khi di chuyen dot dau tien
	maps[n][0] = x;
	maps[n][1] = y;
	n++;
	if(n == dot) n=1;
}
void Speed(){
	if(speed == -35 ){
		spe = "Max Speed ";
		GotoXY(1,3); Textcolor(2); cout << "Speed: ";
		GotoXY(8,3); Textcolor(10); cout << spe;
	}
	if(speed == -20 ){
		spe = "Nhanh     ";
		GotoXY(1,3); Textcolor(2); cout << "Speed: ";
		GotoXY(8,3); Textcolor(10); cout << spe;
	}
	if(speed == 0 ){
		spe = "Trung Binh";
		GotoXY(1,3); Textcolor(2); cout << "Speed: ";
		GotoXY(8,3); Textcolor(10); cout << spe;
	}
	if(speed == 50 ){
		spe = "Cham      ";
		GotoXY(1,3); Textcolor(2); cout << "Speed: ";
		GotoXY(8,3); Textcolor(10); cout << spe;
	}

}
void DieuKhien(){	//in dot ra khi di chuyen
	for (int i=1; i<dot; i++){
		//fix bug
		if(maps[i][0] == 0 && maps[i][1]==0){
			cout << " ";
		}else{	//in ra man hinh
		GotoXY(maps[i][0], maps[i][1]);
		Textcolor(10);
		cout << char(169);
		}
	}
	// in diem ra man hinh
	GotoXY(1,1); Textcolor(2); cout << "Scores: ";
	GotoXY(1,2); Textcolor(2); cout << "Live: ";
	GotoXY(9,1); Textcolor(10); cout << dot-2;
	GotoXY(9,2); Textcolor(10); cout << mang;
	GotoXY(53,2); Textcolor(2); cout << "(" << VTx << "," << VTy << ") ";
	GotoXY(53,3); Textcolor(2); cout << "(" << x << "," << y << ") ";
	Speed();
}
void XoaDauVet(){	//xoa toa do khi di chuyen
		GotoXY(maps[n][0], maps[n][1]);
		cout << " ";
}
void CheckColor(){	//in phim bam
	if (dichuyen == 1){
		Textcolor(172);
		cout << "D";
			GotoXY(35,3);Textcolor(10);cout << "A";
			GotoXY(37,3);Textcolor(10);cout << "S";
			GotoXY(37,2);Textcolor(10);cout << "W";
	}
	else if (dichuyen == 2){
		Textcolor(172);
		cout << "A";
			GotoXY(39,3);Textcolor(10);cout << "D";
			GotoXY(37,3);Textcolor(10);cout << "S";
			GotoXY(37,2);Textcolor(10);cout << "W";
	}
	else if (dichuyen == 3){
		Textcolor(172);
		cout << "S";
			GotoXY(35,3);Textcolor(10);cout << "A";
			GotoXY(39,3);Textcolor(10);cout << "D";
			GotoXY(37,2);Textcolor(10);cout << "W";
	}
	else if (dichuyen == 4){
		Textcolor(172);
		cout << "W";
			GotoXY(35,3);Textcolor(10);cout << "A";
			GotoXY(37,3);Textcolor(10);cout << "S";
			GotoXY(39,3);Textcolor(10);cout << "D";
	}
}
void KeyBoard(){
	//kbhit bat key cham, khong nen su dung kbhit
	//else if --> fix bug eat me --> khong linh hoat
	if(GetAsyncKeyState(0x44))//D
		{
		if(dichuyen != 2)
			dichuyen = 1;
		}
	else if(GetAsyncKeyState(0x41))//A
		{
		if(dichuyen !=1)
			dichuyen = 2;
		}
	else if(GetAsyncKeyState(0x53))//S
		{
		if (dichuyen !=4)
			dichuyen = 3;
		}
	else if(GetAsyncKeyState(0x57)) //W
		{
		if(dichuyen != 3)
			dichuyen = 4;
		}
	//speed game
	if(GetAsyncKeyState(0x31)) //1
		speed = -35;
	if(GetAsyncKeyState(0x32)) //2
		speed = -20;
	if(GetAsyncKeyState(0x33)) //3
		speed = 0;
	if(GetAsyncKeyState(0x34)) //4
		speed = 50;
	//xu ly di chuyen
	if(dichuyen == 1){
		x++;
		GotoXY(30,1);
		cout << "                ";
		GotoXY(39,3); CheckColor();
	}
	if(dichuyen == 2){
		x--;
		GotoXY(30,1);
		cout << "                ";
		GotoXY(35,3); CheckColor();
	}
	if(dichuyen == 3){
		y++;
		GotoXY(30,1);
		cout << "                ";
		GotoXY(37,3); CheckColor();
	}
	if(dichuyen == 4){
		y--;
		GotoXY(30,1);
		cout << "                ";
		GotoXY(37,2); CheckColor();
	}
}
void VicTim(){
	if(x == VTx && y == VTy){	// snake cham vao thuc an
		//tang mang (live) khi an 20 thuc an
		if ((dot%20) == 0){
			mang+=1;
		}
		PlaySound("data/eat.wav", NULL, SND_ASYNC);
		Sleep(0);
		dot++;
		VTx = rand()%60+5;
		VTy = rand()%20+5;
		GotoXY(VTx, VTy);
		Textcolor(12);
		cout << char(4);
	}
	//fix bug khi toa do thuc an = toa do cua than snake
	for (int i=1; i<dot; i++){
		if(maps[i][0] == VTx && maps[i][1]== VTy){
			dot+=0;	//khong tang diem
			VTx = rand()%60+5;
			VTy = rand()%20+5;
			GotoXY(VTx, VTy); Textcolor(12);
			cout << char(4);
		}
	}
}
void XuLy(){
	if(MessageBox(NULL,"Nhan OK Play lai...", "YOU DIE", MB_OKCANCEL) == IDOK){
		if(dot > savedot){SaveScore();}
		GotoXY(25,25); Textcolor(12);
		cout << "Nhan Enter de bo qua...";
		system("Snake.exe");
		exit(1);
	}else{
		if(dot > savedot){
			if(MessageBox(NULL,"Diem cao!!\nBan co muon luu diem cua minh?", "Save Scores", MB_YESNO) == IDYES){
			SaveScore();
			exit(1);
			}else{
			files.close();	//loadscore()
			exit(1);
			}
		}else{
			if(MessageBox(NULL,"Diem cua ban chua phai la cao nhat", "YOU LOSE", MB_OK) == IDOK){
			files.close();
			exit(1);
			}
		}
	}
}
void GameOver(){		//xu ly thua game
	//xu ly cham bien --> die
	if(x <= 4 || x >= 70 || y <= 4 || y >= 30){
		mang = 0;
		GotoXY(50,30); Textcolor(12);
		cout << "Coding by Anhvietcr";
		GotoXY(20,14); Textcolor(14);
		cout << "Game Over, Nhan phim bat ky...\n\n\n\n\n\n\n\n\n\n\n\n\n";
		XuLy();
	}
	//cham vao than snake --> -1 live
	for (int i = 1; i<dot; i++){
		if(x == maps[i][0] && y == maps[i][1]){
			mang -= 1;
			if (mang < 0){
				GotoXY(20,14); Textcolor(14);
				cout << "Game Over, Nhan phim bat ky...\n\n\n\n\n\n\n\n\n\n\n\n\n";
				XuLy();
			}
		}
	}
}
void MainGame(){
	GotoXY(5,31); Textcolor(2);
	cout << "Thay doi toc do, nhan:";
	GotoXY(28,31); Textcolor(10);
	cout << "[1] [2] [3] [4]";
	GotoXY(50,1); Textcolor(2); cout << "Scores Max: ";
	GotoXY(62,1); Textcolor(10); cout << savedot;
	GotoXY(50,2); Textcolor(12); cout << char(4);
	GotoXY(50,3); Textcolor(10); cout << char(169);
	GotoXY(5,32);
		Textcolor(10); cout << "20 ";
		Textcolor(12); cout << char(4);
		Textcolor(10); cout << " +1 ";
		Textcolor(2); cout << "Live";
	while(1){
		DieuKien();
		DieuKhien();
		XoaDauVet();
		VicTim();
		KeyBoard();
		GameOver();
		Sleep(50+speed);
	}
}
void menu(){
	if(GetAsyncKeyState(VK_SPACE)){
		system("cls");
		HienThi();
		GotoXY(VTx,VTy);Textcolor(12);
		cout << char(4);
		LoadScore();
		MainGame(); //check = 1;
	}
}
void Intro(){
		//intro.txt
		GotoXY(18,10); Textcolor(10);
		files.open("data/intro.txt", ios::out);
		if (files.fail()){cout << "File khong ton tai..";}
		if (!files.eof()){
			while(!files.eof()){
				kytu = files.get();
				Sleep(10);
				cout << kytu;
				if(kbhit()){
					if(_getch() == VK_RETURN){
						files.close();
						system("cls");
						HienThi();
						GotoXY(VTx,VTy);Textcolor(12);
						cout << char(4);
						LoadScore();
						MainGame(); //check = 1;
					}
				}
			}
		}
		HienThi();
		files.close();
		//start.txt
		GotoXY(25,25); Textcolor(10);
		files.open("data/start.txt", ios::out);
		if (files.fail()){cout << "File khong ton tai..";}
		while(!files.eof()){
			kytu = files.get();
			Sleep(50);
			cout << kytu;
		}
		files.close();
}
int main(){
	SetConsoleTitle("Game Snaker v2.0");	//title game
	ResizeConsole(630,530);					//resize cmd
	HideCursor();							//hide mouse control
	srand(time(0));							//rand time
	Intro();								//ve intro game
	while(1){
		menu();
	}
	system("pause>null");
}
/*
Game Snaker v2.0 la 1 Open Source, Coding by Anhvietcr.
Vui long ton trong thong tin tac gia khi chinh sua ma nguon Game.!
Cam on ban da quan tam. Chuc thanh cong.!
_[_Anhvietcr_]_
*/