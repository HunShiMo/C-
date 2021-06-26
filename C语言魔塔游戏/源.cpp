#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

//������ϷͼƬ
void initgamePicture();

//��ʾ��ɫ��Ϣ
void setPlayer();

//��ʼ����Ϸ��ɫ
void initPlayer();

//������Ϸ��ͼ
void setMap();

//������ת�����ַ���
char* intToString(int Number);

//��ʼ��Ϸ
void startGame();

// ���Ǹ������
int combat(int x);

// ģ���ֵĹ���
int VS(int playHP, int playATT, int playDEF, int monHP, int monATT, int monDEF);

// ������Ϸ��ͼ����
void saveGame();

// ��ȡ��Ϸ��ͼ����
void loadGame();

void beforeStart();

//����ѡ��
void  startUp();

/**
 * �ж���һ��������
 *
 * nextplayerx, nextplayery ��ʾ��һ�������꣬
 * playerXY ��ʾ���ĸ������ƶ�, 
 * step ����
 */
boolean check(int nextPlayerx, int nextPlayery, int* playerXY, int step);

/*
 * ���� boolean check(int nextPlayerx, int nextPlayery, int* playerXY, int step) �Ĳ����ظ�����
 */
void innerFuncAboutCheck(int nextPlayerx, int nextPlayery, int* playerXY, int step);

/*
 *	���õ�ͼ
 */
void resetMapGroup();

// ����ڵ�ͼ�е�λ�ã���������Ϸ�������Ͻ�Ϊ����ԭ�㣬����Ϊx������������Ϊy��������
int playerx, playery;

int isMeetNPC = false;

char str[20] = "";

// ��ǰ�����ŵ�ͼ
int mapNum = 0;

// ��ͼ��
int mapGroup[4][13][13] = {
	{
		{ 98, 1,  15, 1,  1,  1,  1,  1, 1,  14, 0,  5,  4},
		{ 1,  1,  0,  0,  0,  0,  0,  0, 0,  14, 0,  1,  1},
		{ 0,  0,  0,  1,  1,  1,  1,  7, 0,  1,  3,  15, 1},
		{ 1,  8,  0,  1,  0,  0,  2,  0, 0,  1,  0,  1,  1},
		{ 14, 14, 0,  1,  0,  7,  1,  7, 0,  1,  0,  0,  0},
		{ 8,  1,  3,  1,  0,  1,  1,  1, 0,  1,  3,  7,  7},
		{ 0,  0,  0,  14, 0,  1,  1,  1, 0,  14, 0,  0,  0},
		{ 5,  14, 0,  14, 0,  1,  16, 1, 0,  14, 0,  1,  1},
		{ 14, 14, 0,  1,  0,  0,  0,  0, 0,  1,  3,  14, 1},
		{ 14, 14, 3,  1,  1,  1,  1,  1, 14, 1,  0,  1,  4},
		{ 0,  0,  0,  3,  0,  0,  3,  0, 0,  3,  0,  0,  0},
		{ 1,  1,  1,  11, 0,  22,  1,  7, 0,  14, 1,  1, 14},
		{ 6,  1,  1,  1,  0,  10, 99, 7, 0,  5,  1,  14, 7}
	},

	{
		{ 1,  97, 1,  0,  20, 1,  1,  0,  1,  1,  0,  1,  1},
		{ 1,  99, 1,  0,  6,  1,  1,  1,  1,  8,  0,  5,  5},
		{ 1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  0,  1,  1},
		{ 1,  1,  1,  0,  0,  2,  0,  0,  0,  3,  0,  3,  0},
		{ 1,  1,  1,  0,  11, 1,  11, 0,  7,  1,  1,  1,  1},
		{ 0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0},
		{ 7,  1,  7,  3,  1,  1,  8,  1,  1,  1,  13, 1,  6},
		{ 0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0},
		{ 22,  1,  1,  0,  15, 1,  15, 1,  1,  1,  1,  1,  7},
		{ 1,  1,  1,  0,  0,  2,  0,  0,  3,  0,  0,  3,  0},
		{ 1,  1,  1,  0,  7,  1,  7,  0,  1,  1,  0,  1,  1},
		{ 1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  0,  1,  1},
		{ 1,  98, 1,  0,  1,  21, 1,  0,  4,  1,  0,  4,  1}
	},

	{
		{ 8,  6,  0,  -2, 0,  1,  17, 1,  0,  8,  0,  6,  1},
		{ 1,  1,  0,  2,  0,  1,  1,  1,  0,  8,  0,  1,  1},
		{ 12, 0,  0,  2,  0,  1,  1,  1,  0,  3,  0,  0,  12},
		{ 1,  0,  -1, 2,  0,  0,  1,  0,  0,  1,  22,  0,  1},
		{ 12, -1, -1, 2,  0,  1,  1,  1,  0,  1,  1,  1,  12},
		{ 1,  0,  0,  1,  0,  1,  1,  1,  0,  1,  0,  0,  1},
		{ 1,  1,  15, 1,  0,  0,  1,  0,  0,  1,  15, 1,  1},
		{ 4,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  5},
		{ 0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0},
		{ 7,  1,  1,  11, 1,  1,  1,  1,  1,  1,  1,  3,  5},
		{ 0,  0,  3,  0,  0,  0,  3,  0,  0,  0,  3,  0,  0},
		{ 1,  1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  1,  7},
		{ 9,  1,  1,  1,  0,  97, 99, 1,  0,  1,  1,  1,  7}
	},
	{
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -5,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -4,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
	}

};

int mapGroupCopy[4][13][13] = {
	{
		{ 98, 1,  15, 1,  1,  1,  1,  1, 1,  14, 0,  5,  4},
		{ 1,  1,  0,  0,  0,  0,  0,  0, 0,  14, 0,  1,  1},
		{ 0,  0,  0,  1,  1,  1,  1,  7, 0,  1,  3,  15, 1},
		{ 1,  8,  0,  1,  0,  0,  2,  0, 0,  1,  0,  1,  1},
		{ 14, 14, 0,  1,  0,  7,  1,  7, 0,  1,  0,  0,  0},
		{ 8,  1,  3,  1,  0,  1,  1,  1, 0,  1,  3,  7,  7},
		{ 0,  0,  0,  14, 0,  1,  1,  1, 0,  14, 0,  0,  0},
		{ 5,  14, 0,  14, 0,  1,  16, 1, 0,  14, 0,  1,  1},
		{ 14, 14, 0,  1,  0,  0,  0,  0, 0,  1,  3,  14, 1},
		{ 14, 14, 3,  1,  1,  1,  1,  1, 14, 1,  0,  1,  4},
		{ 0,  0,  0,  3,  0,  0,  3,  0, 0,  3,  0,  0,  0},
		{ 1,  1,  1,  11, 0,  22,  1,  7, 0,  14, 1,  1, 14},
		{ 6,  1,  1,  1,  0,  10, 99, 7, 0,  5,  1,  14, 7}
	},

	{
		{ 1,  97, 1,  0,  20, 1,  1,  0,  1,  1,  0,  1,  1},
		{ 1,  99, 1,  0,  6,  1,  1,  1,  1,  8,  0,  5,  5},
		{ 1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  0,  1,  1},
		{ 1,  1,  1,  0,  0,  2,  0,  0,  0,  3,  0,  3,  0},
		{ 1,  1,  1,  0,  11, 1,  11, 0,  7,  1,  1,  1,  1},
		{ 0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0},
		{ 7,  1,  7,  3,  1,  1,  8,  1,  1,  1,  13, 1,  6},
		{ 0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0},
		{ 22,  1,  1,  0,  15, 1,  15, 1,  1,  1,  1,  1,  7},
		{ 1,  1,  1,  0,  0,  2,  0,  0,  3,  0,  0,  3,  0},
		{ 1,  1,  1,  0,  7,  1,  7,  0,  1,  1,  0,  1,  1},
		{ 1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  0,  1,  1},
		{ 1,  98, 1,  0,  1,  21, 1,  0,  4,  1,  0,  4,  1}
	},

	{
		{ 8,  6,  0,  -2, 0,  1,  17, 1,  0,  8,  0,  6,  1},
		{ 1,  1,  0,  2,  0,  1,  1,  1,  0,  8,  0,  1,  1},
		{ 12, 0,  0,  2,  0,  1,  1,  1,  0,  3,  0,  0,  12},
		{ 1,  0,  -1, 2,  0,  0,  1,  0,  0,  1,  22,  0,  1},
		{ 12, -1, -1, 2,  0,  1,  1,  1,  0,  1,  1,  1,  12},
		{ 1,  0,  0,  1,  0,  1,  1,  1,  0,  1,  0,  0,  1},
		{ 1,  1,  15, 1,  0,  0,  1,  0,  0,  1,  15, 1,  1},
		{ 4,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  5},
		{ 0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0},
		{ 7,  1,  1,  11, 1,  1,  1,  1,  1,  1,  1,  3,  5},
		{ 0,  0,  3,  0,  0,  0,  3,  0,  0,  0,  3,  0,  0},
		{ 1,  1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  1,  7},
		{ 9,  1,  1,  1,  0,  97, 99, 1,  0,  1,  1,  1,  7}
	},
	{
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -5,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -4,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
		{-3,  -3,  -3,  0,  0,  -6,  -6,  -6,  0,  0,  -3,  -3,-3},
	}

};

int(*map)[13] = mapGroup[mapNum];

IMAGE npc, floor, defenseGems, goblinWarrior, attackGems, yellowDoor,
yellowKey, infoBar, guardKnight, blueDoor, blueKey, wall,
lastFloor, holyWaterBottle, bladeOfLost, cross, slimeBeast,
gobblerLord, headlessWarrior, nextFloor, fightingNun, blessedShield,
automaticDefenseMagicWeapon, gameOverReal, beforeStartPic, archivePoint,
water, redfloor, fightingNun0, greendoor, Startup, fightingNun_0;

HWND hwnd;

int FLAG = 0;
int pictureSize = 60;
boolean playerDie = false;

struct gameRole {
	//�������
	char name[20] = "ϣ��ޱ�";
	//Ѫ��
	int HP;
	// ħ��
	int MP;
	//����
	int DEF;
	//����
	int ATT;
	//�ȼ�
	int LV;
	//����
	int EXP;
	//��Կ������
	int numBlueKey;
	//��Կ������
	int numYellowKey;
} player;

//��������
struct monster {
	//Ѫ��	
	int HP;
	//����
	int ATT;
	//����
	int DEF;
	//����
	int EXP;
};

//�粼������   
struct monster goblinWarriorProperty = { 12, 4, 0, 10 };

//������ʿ����
struct monster guardKnightProperty = { 12, 9, 7, 15 };

//ʷ��ķ����
struct monster slimeBeastProperty = { 6, 2, 0, 5 };

//��������������
struct monster gobblerLordProperty = { 20, 1, 5, 0 };

//��ʵ��̬
struct monster gobblerLordProperty1 = { 90, 11, 0, 50 };

//����սʿ����
struct monster headlessWarriorProperty = { 20, 10, 10, 25 };

//�Զ�����ħ������
struct monster automaticDefenseMagicWeaponProperty = { 6, 20, 0, 10 };


int main()
{
	initPlayer();
	hwnd = initgraph(pictureSize * 14, pictureSize * 13);
	SetWindowTextA(hwnd, "Deos occidere");
	initgamePicture();

	mciSendString("open bgm.mp3 alias bkmusic", NULL, 0, NULL);
	//ѭ����������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);

	while (!playerDie) {
		//�������ѡ��
		startUp();
		// ����˳���Ϸ
		if (playerDie) {
			break;
		}
		beforeStart();

		while (!playerDie) {
			setMap();
			setPlayer();
			startGame();
		}
		playerDie = false;
	}
	
	closegraph();//�ر�
	return 0;
}

/*
*
*   �������ѡ��
*	450      525
*	450+80 525+80
*	450+80*2   525+80*2
*
*/

void startUp()
{
	int i = 1;
	setcolor(YELLOW);
	putimage(0, 0, &Startup);
	setbkmode(TRANSPARENT);         //�������ֱ������ģʽ��һ��ʹ�����ֱ���ɫǰ�������
	bool start = false;
	char ch;
	setcolor(GREEN);
	rectangle(145, 450/*���y*/, 450 + 75, 525/*�ұ�y*/);
	settextstyle(75, 0, "����");
	while (!start) {
		while (!start) {
			setcolor(YELLOW);
			outtextxy(150, 450, "������Ϸ");//�����������Ϸ������
			outtextxy(150, 530, "��ʼ����Ϸ");//�������ʼ����Ϸ������
			outtextxy(150, 610, "�˳���Ϸ");//������˳���Ϸ������

			setcolor(GREEN);
			
			ch = _getch();
			switch (ch)
			{
			case ' ':
				clearrectangle(145, 450, 450 + 75, 525);
				clearrectangle(145, 450 + 80, 450 + 75, 525 + 80);
				clearrectangle(145, 450 + 80 * 2, 450 + 75, 525 + 80 * 2);
				rectangle(145, 450 + 80 * (i )/*���y*/, 450 + 75, 525 + 80 * (i )/*�ұ�y*/);
				i++;
				if (i == 3)
				{
					i = 0;
				}
				start = false;
				break;
			case 13:
				start = true;
			}
		}
		switch (i) {
			// ������Ϸ
		case 1:
			loadGame();
			 //MessageBox(hwnd, "������Ϸ", "hah", MB_OK);
			break;

			//��ʼ����Ϸ
		case 2:
			resetMapGroup();
			 //MessageBox(hwnd, "��ʼ��Ϸ", "hah", MB_OK);
			break;

			// ������Ϸ
		case 0:
			if (MessageBox(hwnd, "ȷ���˳���Ϸ", "��ʾ", MB_YESNO) == IDYES) {
				playerDie = true;
			}
			else {
				start = false;
			}

			break;
		}
	}
	
	//_getch();
}


void resetMapGroup() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			for (int k = 0; k < 13; k++) {
				mapGroup[i][j][k] = mapGroupCopy[i][j][k];
			}
		}
	}

	map = mapGroup[0];
	mapNum = 0;
	initPlayer();
}

void beforeStart() {
	putimage(0,0,&beforeStartPic);
	char ch;
	boolean start = false;
	while (!start) {
		ch = _getch();
		switch (ch) {
		case 'h':
		case 'H':
			start = true;
			break;
		default:
			start = false;
		}
	}
}

/*
 * ��ʾ��ɫ��Ϣ
 */
void setPlayer() {
	setcolor(WHITE);
	settextstyle(13, 0, "����");
	putimage(60 * 13, 0, &infoBar);
	outtextxy(60 * 13 + 5, 103, player.name);

	settextstyle(20, 0, "����");
	outtextxy(60 * 13 + 12, 180, intToString(player.LV));
	outtextxy(60 * 13 + 12, 235, intToString(player.EXP));
	outtextxy(60 * 13 + 12, 363, intToString(player.HP));
	outtextxy(60 * 13 + 12, 419, intToString(player.MP));
	outtextxy(60 * 13 + 12, 517, intToString(player.ATT));
	outtextxy(60 * 13 + 12, 567, intToString(player.DEF));
	outtextxy(60 * 13 + 12, 689, intToString(player.numYellowKey));
	outtextxy(60 * 13 + 12, 759, intToString(player.numBlueKey));
}

/*
 * ������ϷͼƬ���ڴ���
 */
void initgamePicture() {
	loadimage(&npc, "npc.png", pictureSize, pictureSize);
	loadimage(&floor, "�ذ�.png", pictureSize, pictureSize);
	loadimage(&defenseGems, "������ʯ.png", pictureSize, pictureSize);
	loadimage(&goblinWarrior, "�粼��սʿ.png", pictureSize, pictureSize);
	loadimage(&attackGems, "������ʯ.png", pictureSize, pictureSize);
	loadimage(&yellowDoor, "����.png", pictureSize, pictureSize);
	loadimage(&yellowKey, "��Կ��.png", pictureSize, pictureSize);
	loadimage(&infoBar, "��ɫ��Ϣ��.png");
	loadimage(&guardKnight, "������ʿ.png", pictureSize, pictureSize);
	loadimage(&blueDoor, "����.png", pictureSize, pictureSize);
	loadimage(&blueKey, "��Կ��.png", pictureSize, pictureSize);
	loadimage(&wall, "ǽ��.png", pictureSize, pictureSize);
	loadimage(&lastFloor, "��һ��.png", pictureSize, pictureSize);
	loadimage(&holyWaterBottle, "ʥˮƿ.png", pictureSize, pictureSize);
	loadimage(&bladeOfLost, "ʧ��֮��.png", pictureSize, pictureSize);
	loadimage(&cross, "ʮ�ּ�.png", pictureSize, pictureSize);
	loadimage(&slimeBeast, "ʷ��ķ��.png", pictureSize, pictureSize);
	loadimage(&gobblerLord, "����������.png", pictureSize, pictureSize);
	loadimage(&headlessWarrior, "������ʿ.png", pictureSize, pictureSize);
	loadimage(&nextFloor, "��һ��.png", pictureSize, pictureSize);
	loadimage(&fightingNun, "ս����Ů.png", pictureSize, pictureSize);
	loadimage(&blessedShield, "ף��֮��.png", pictureSize, pictureSize);
	loadimage(&automaticDefenseMagicWeapon, "�Զ�����ħ��.png", pictureSize, pictureSize);
	loadimage(&gameOverReal, "����.png");
	loadimage(&beforeStartPic, "��������.png");
	loadimage(&archivePoint, "�浵��.png", pictureSize, pictureSize);
	loadimage(&water, "ˮ��.png", pictureSize, pictureSize);
	loadimage(&greendoor, "������ٽ��.png", pictureSize, pictureSize);
	loadimage(&Startup, "��������.png");
	loadimage(&fightingNun0, "ս����Ů0.png", pictureSize, pictureSize);
	loadimage(&redfloor, "��ذ�.png", pictureSize, pictureSize);
	loadimage(&fightingNun_0, "ս����Ů_0.png", pictureSize, pictureSize);
}

/*
 * ��ʼ����Ϸ��ɫ
 */
void initPlayer()
{
	player.LV = 0;
	player.ATT = 2;
	player.DEF = 0;
	player.numBlueKey = 0;
	player.numYellowKey = 0;
	player.HP = 20;
	player.MP = 0;
	player.EXP = 0;

	// ��������Ϸ�������Ͻ�Ϊ����ԭ�㣬����Ϊx������������Ϊy��������
	// ��ҳ�ʼ����(11,8)
	playerx = 12;
	playery = 6;
}

/*
 * ����ת��Ϊ�ַ�
 */
char* intToString(int Number) {
	int len = 0;

	if (Number == 0) {
		str[0] = '0';
		len++;
	}
	while (Number)
	{
		str[len++] = Number % 10 + '0';
		Number /= 10;
	}
	for (int i = 0; i < len / 2; i++) {
		char t = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = t;
	}
	str[len] = '\0';
	return str;
}

/*
 *������Ϸ��ͼ
 */
void setMap() {
	// ��
	for (int i = 0; i < 13; i++) {
		// ��
		for (int j = 0; j < 13; j++) {
			switch (map[i][j]) {

				//���͵��Ĳ�
			case -7:
				putimage(j * pictureSize, i * pictureSize, &greendoor);
				break;
				//ˮ��
			case -3:
				putimage(j * pictureSize, i * pictureSize, &water);
				break;


				//ǽ 
			case -1:
			case 0:
				putimage(j * pictureSize, i * pictureSize, &wall);          
				break;

				//�ذ�
			case -2:
			case 1:
				putimage(j * pictureSize, i * pictureSize, &floor);        
				break;

				//��ذ�//���Ĳ㴥������
			case -4:
			case -5:
			case -6:
			case -8:
				putimage(j * pictureSize, i * pictureSize, &redfloor);
				break;

				//����
			case 2:
				putimage(j * pictureSize, i * pictureSize, &blueDoor);     
				break;

				//����
			case 3:
				putimage(j * pictureSize, i * pictureSize, &yellowDoor);    
				break;

				//������ʯ
			case 4:
				putimage(j * pictureSize, i * pictureSize, &defenseGems);         
				break;

				//������ʯ
			case 5:
				putimage(j * pictureSize, i * pictureSize, &attackGems);          
				break;

				//��Կ��
			case 6:
				putimage(j * pictureSize, i * pictureSize, &blueKey);       
				break;

				//��Կ��
			case 7:
				putimage(j * pictureSize, i * pictureSize, &yellowKey);     
				break;

				//ʥˮ
			case 8:
				putimage(j * pictureSize, i * pictureSize, &holyWaterBottle);          
				break;

				//ʮ�ּ�
			case 9:
				putimage(j * pictureSize, i * pictureSize, &cross);         
				break;

				//npc һ����Ǹ�
			case 10:
				putimage(j * pictureSize, i * pictureSize, &npc);        
				break;

				//�Զ�����ħ��
			case 11:
				putimage(j * pictureSize, i * pictureSize, &automaticDefenseMagicWeapon);     
				break;

				//������ʿ
			case 12:
				putimage(j * pictureSize, i * pictureSize, &guardKnight);      
				break;

				//������ʿ
			case 13:
				putimage(j * pictureSize, i * pictureSize, &headlessWarrior);        
				break;

				//ʷ��ķ��
			case 14:
				putimage(j * pictureSize, i * pictureSize, &slimeBeast);      
				break;

				//�粼��սʿ
			case 15:
				putimage(j * pictureSize, i * pictureSize, &goblinWarrior);        
				break;

				//ʧ��֮��
			case 16:
				putimage(j * pictureSize, i * pictureSize, &bladeOfLost);        
				break;

				// ����������
			case 17:
			case 18:
			case 19:
				putimage(j * pictureSize, i * pictureSize, &gobblerLord);
				break;

			case 21:
				putimage(j * pictureSize, i * pictureSize, &blessedShield);
				break;

				// npc ������Ǹ�
			case 20:
				putimage(j * pictureSize, i * pictureSize, &npc);
				break;

				// �浵��
			case 22:
				putimage(j * pictureSize, i * pictureSize, &archivePoint);
				break;

				//��һ��
			case 97:
				putimage(j * pictureSize, i * pictureSize, &lastFloor);
				break;

				//��һ��
			case 98:
				putimage(j * pictureSize, i * pictureSize, &nextFloor);         
				break;

				//���
			case 99:
				putimage(j * pictureSize, i * pictureSize, &fightingNun);          
				break;

				//���
			case 100:
				putimage(j * pictureSize, i * pictureSize, &fightingNun_0);
				break;
			}
		}
	}
}


/*
 * ��������ʱ�����Ի���
 */
int combat(int x) {
	int ID;
	switch (x) {
	case 10:
		MessageBox(hwnd, "�������������;��Ԥ�������ֽ��", "NPC", MB_YESNO);
		return 1;
		break;
	case 11:
		ID = MessageBox(hwnd, "�����Զ�����ħ�����Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, automaticDefenseMagicWeaponProperty.HP, automaticDefenseMagicWeaponProperty.ATT, automaticDefenseMagicWeaponProperty.DEF)) {
				player.EXP += automaticDefenseMagicWeaponProperty.EXP;
				return 1;
			}
		}
		break;
	case 12:
		ID = MessageBox(hwnd, "����������ʿ���Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, guardKnightProperty.HP, guardKnightProperty.ATT, guardKnightProperty.DEF)) {
				player.EXP += guardKnightProperty.EXP;
				return 1;
			}
		}
		break;
	case 13:
		ID = MessageBox(hwnd, "����������ʿ���Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, headlessWarriorProperty.HP, headlessWarriorProperty.ATT, headlessWarriorProperty.DEF)) {
				player.EXP += headlessWarriorProperty.EXP;
				return 1;
			}
		}
		break;
	case 14:
		ID = MessageBox(hwnd, "����ʷ��ķ�ޣ��Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, slimeBeastProperty.HP, slimeBeastProperty.ATT, slimeBeastProperty.DEF)) {
				player.EXP += slimeBeastProperty.EXP;
				return 1;
			}
		}
		break;
	case 15:
		ID = MessageBox(hwnd, "�����粼��սʿ���Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, goblinWarriorProperty.HP, goblinWarriorProperty.ATT, goblinWarriorProperty.DEF)) {
				player.EXP += goblinWarriorProperty.EXP;
				return 1;
			}
		}
		break;

	case 17:
		MessageBox(hwnd, "�����������������Ƿ񹥻���", "��ʾ", MB_OK);
		MessageBox(hwnd, "�������Ҳ��µĴ��ͽ�绹�����õģ�������ȥ�ɣ�����", "gobblerLord", MB_OK);
		map[3][6] = 2;
		map[6][6] = 2;
		map[0][6] = 18;
		//	map[0][6] = 18;
		break;

	case 18:
		ID = MessageBox(hwnd, "�����������������Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			MessageBox(hwnd, "��Ӯ�˿��߰�,���������ǰ��", "����������", MB_OK);
			map[2][6] = 19;
			map[0][6] = 1;

		}
		break;
	case 19:
		ID = MessageBox(hwnd, "�����������������Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			//map[2][1] = 1;
			map[2][6] = 19;

			MessageBox(hwnd, "���� ��ô�����ߣ������ȥ����", "����������", MB_OK);
			if (VS(player.HP, player.ATT, player.DEF, gobblerLordProperty1.HP, gobblerLordProperty1.ATT, gobblerLordProperty1.DEF)) {
				player.EXP += gobblerLordProperty.EXP;
				return 1;
			}
		}
		break;

	case 20:
		MessageBox(hwnd, "�����ˣ�������һ����Կ�ף���˵����Ľṹ�ǶԳƵ�", "NPC", MB_OK);
		isMeetNPC = true;
		return 1;
		break;

	case 21:
		ID = MessageBox(hwnd, "�����������������Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, gobblerLordProperty.HP, gobblerLordProperty.ATT, gobblerLordProperty.DEF)) {
				player.EXP += gobblerLordProperty.EXP;
				return 1;
			}
		}
		break;

	}
	return 0;
}

/*
 * ��ȡ��Ϸ��ͼ����
 */
void loadGame() {
	FILE* fp = NULL;
	int num = 0;
	int count = 0;
	int i = 0;//���صĵ�ͼ��Ϣ
	int j = 0;
	int k = 0;
	int flag[4] = { 0,0,0,0 };
	fopen_s(&fp, "archives.raymond", "r");

	int meetNPC = 0;

	if (fp == NULL) {
		printf("Failed to open the archives.raymond !\n");
		exit(1);
	}
	int result = fscanf_s(fp, "%s%d%d%d%d%d%d%d%d%d%d", player.name, 20, &(player.HP), &player.MP, &player.DEF, &player.ATT, &player.LV, &player.EXP, &player.numBlueKey, &player.numYellowKey, &mapNum, &meetNPC);
	if (result == EOF) {
		return;
	}
	if (meetNPC == 1) {
		isMeetNPC = true;
	}
	else {
		isMeetNPC = false;
	}
	while ((fscanf_s(fp, "%d", &num)) != EOF) {
		mapGroup[i][j][k] = num;
		k++;
		if (k == 13) {
			j++;
			k = 0;
		}
		if (j == 13) {
			i++;
			flag[i] = i;
			j = 0;
		}
	}

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			mapGroup[3][i][j] = mapGroupCopy[3][i][j];
		}
	}

	switch (mapNum)
	{
	case 1:
		playerx = 1;
		playery = 1;
		break;
	case 0:
	case 2:
	case 3:
		playerx = 12;
		playery = 6;
		break;
	}

	map = mapGroup[mapNum];

	/*map = mapGroup[0];
	mapNum = 0;
	playerx = 12;
	playery = 6;*/

	fclose(fp);
}


/*
 * ������Ϸ��ͼ����
 */
void saveGame() {
	FILE* fp = NULL;
	fopen_s(&fp, "archives.raymond", "w");

	if (fp == NULL) {
		printf("Failed to open the archives.raymond !\n");
		exit(1);
	}

	int meetNPC = 0;

	if (isMeetNPC) {
		meetNPC = 1;
	}

	// ���������Ϣ
	fprintf(fp, "%20s%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d\n", player.name, player.HP, player.MP, player.DEF, player.ATT, player.LV, player.EXP, player.numBlueKey, player.numYellowKey, mapNum, meetNPC);

	//mapGroup[0][12][6] = -99;
	//mapGroup[1][1][1] = -99;
	//mapGroup[2][12][6] = -99;

	int tempNum = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 13; j++) {
			for (int k = 0; k < 13; k++) {
				tempNum = mapGroup[i][j][k];
				if (mapGroup[i][j][k] == 99) {
					tempNum = 1;
				}
				if ((i == 0 && j == 12 && k == 6)||(i == 1 && j == 1 && k == 1)||(i == 2 && j == 12 && k == 6)) {
					tempNum = 99;
				}
				fprintf(fp, "%5d", tempNum);
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "\n\n");
	}

	fclose(fp);

}

/*
 * ����ս���Ƿ�ʤ��
 */
int VS(int playHP, int playATT, int playDEF, int monHP, int monATT, int monDEF)
{
	// ��ҹ�����С�ڵ��ڹ�����������޷��Ʒ���Ҫô������ѭ����Ҫô������
	if (playATT <= monDEF) {
		MessageBox(hwnd, "����", "��ʾ", MB_YESNO);
		return 0;
	}
	// ��ҹ��������ڹ�����������ҷ��������ڹ��﹥������������������Ҳ���Ѫ
	else if (monATT <= playDEF){
		return 1;
	}
	// ��ҹ��������ڹ�����������ҹ��﹥����������ҷ���������˭Ѫ��
	else {
		while (playHP > 0 || monHP > 0) {
			monHP -= (playATT - monDEF);
			if (monHP <= 0) {
				break;
			}
			playHP -= (monATT - playDEF);
		}
	}
	if (playHP > 0) {
		player.HP = playHP;
		return 1;
	}
	else {
		MessageBox(hwnd, "�򲻹�", "��ʾ", MB_YESNO);
		return 0;
	}
}

/*
 * ���� boolean check(int nextPlayerx, int nextPlayery, int* playerXY, int step) �Ĳ����ظ�����
 */
void innerFuncAboutCheck(int nextPlayerx, int nextPlayery, int* playerXY, int step) {
	map[nextPlayerx][nextPlayery] = 99;
	map[playerx][playery] = 1;
	*playerXY += step;
}

void gameOver() {
	putimage(0, 0, &gameOverReal);
	_getch();
}

/*
 * �ж���һ��������
 * 
 * nextplayerx, nextplayery ��ʾ��һ�������꣬
 * 
 * playerXY ��ʾ�������� �������� step Ϊ-1����ʾ���ϻ���������
 */
boolean check(int nextPlayerx, int nextPlayery, int* playerXY, int step) {
	int isTeleportationDoor = false;
	int choiceResult = 0;

	switch (map[nextPlayerx][nextPlayery]) {
		case -2:
			gameOver();
			break;

		case -4:
			MessageBox(hwnd, "���������Ĵ��ź��������ֳ�һƬ���", "��ʾ", MB_OK);
			MessageBox(hwnd, "��...���ʤ������", "����ޱ�", MB_OK);
			map[nextPlayerx][nextPlayery] = 100;
			//innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			map[playerx][playery] = -6;
			*playerXY += step;
			break;

		case -5:
			MessageBox(hwnd, "ͻȻ����������������һ��������������������̽�������;", "��ʾ", MB_OK);
			map[nextPlayerx][nextPlayery] = 100;
			//innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			map[playerx][playery] = -6;
			*playerXY += step;
			playerDie = true;
			break;

			//��һ���ǵذ�
		case 1:
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

		case -6:
			map[nextPlayerx][nextPlayery] = 100;
			map[playerx][playery] = -6;
			*playerXY += step;
			break;

		case -1:
			if (isMeetNPC) {
				innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			}			
			break;

			//��һ������Կ��
		case 6:
			player.numBlueKey++;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//��һ���ǻ�Կ��
		case 7:
			player.numYellowKey++;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//��һ���ǹ���
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 20:
			if (combat(map[nextPlayerx][nextPlayery]) == 1) {
				innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			}
			break;

			//ף��֮��
		case 21:
			player.DEF += 5;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//�浵
		case 22:
			choiceResult = MessageBox(hwnd, "����ħ�������Խ����״̬д�뾵�ڣ��´�����ʱֻ��Ҫ������Ϥ���Ǹ���ڽ����ͺ��ˣ��������Ƿ�浵", "NPC", MB_YESNO);
			if (choiceResult == IDYES) {
				saveGame();
			}
			break;

			//ʥˮ��ʮ�ּ�
		case 8:
			player.HP += 10;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;
		case 9:
			player.HP += 20;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//������
		case 2:
			if (player.numBlueKey) {
				player.numBlueKey--;
				innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			}
			break;
		case 3:
			if (player.numYellowKey) {
				player.numYellowKey--;
				innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			}
			break;

			//������ʯ
			//��ˮ��+1����
			//��ˮ��+1����
		case 4:
			player.DEF += 1;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;
		case 5:
			player.ATT += 1;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//ʧ��֮��
		case 16:
			player.ATT += 5;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			// ����������
		case 17:
			map[playerx][playery] = 1;
			combat(map[nextPlayerx][nextPlayery]);
			FLAG = 1;
			isTeleportationDoor = true;
			mapNum--;
			break;

		case 18:
			map[0][5] = -7;
			combat(map[nextPlayerx][nextPlayery]);
			break;

		case -7:
			mapNum++;
			isTeleportationDoor = true;
			map[playerx][playery] = 1;
			break;

		case 19:
			//map[0][5] = -7;//�������������Կ�������һ��
			if (combat(map[nextPlayerx][nextPlayery]) == 1) {
				mapGroup[3][3][6] = -8;
				innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			}
			break;

			// ���뵽��һ��
		case 98:
			isTeleportationDoor = true;
			mapNum++;
			map[playerx][playery] = 1;
			break;

			// ���뵽��һ��
		case 97:
			isTeleportationDoor = true;
			mapNum--;
			map[playerx][playery] = 1;
			break;
	}

	return isTeleportationDoor;
}

/*
 * ��ʼ��Ϸ
 */
void startGame()
{
	boolean member = false;
	boolean flag = false;
	while (1) {
		char ch = _getch();
		switch (ch) {
		case 'w':
		case 'W':
		case 72:
			if (playerx -1 == -1) {
				break;
			}
			flag = check(playerx - 1, playery, &playerx, -1);
			break;
		case 's':
		case 'S':
		case 80:
			if (playerx + 1 == 13) {
				break;
			}
			flag = check(playerx + 1, playery, &playerx, 1);
			break;
		case 'a':
		case 'A':
		case 75:
			if (playery - 1 == -1) {
				break;
			}
			flag = check(playerx, playery - 1, &playery, -1);
			break;
		case 'd':
		case 'D':
		case 77:
			if (playery + 1 == 13) {
				break;
			}
			flag = check(playerx, playery + 1, &playery, 1);
			break;

			// esc��
		case 27:
			if (MessageBox(hwnd, "ȷ�����ؿ�ʼ�˵��������˱�����Ϸ", "��ʾ", MB_YESNO) == IDYES) {
				playerDie = true; 
				return;
			}
		}

		// ���Ҫ������һ�������һ���ˣ���Ҫ�л���ͼ��
		if (flag) {
			map = mapGroup[mapNum];
			// ������Ҫǰ���ĵ�ͼ�����¶�λ��ҵ�λ��
			switch (mapNum) {
				case 0:
					playerx = 0;
					playery = 1;
					break;
				case 1:
					playerx = 1;
					playery = 1;
					if (FLAG)
					{
						playerx = 0;
						playery = 5;
						FLAG = 0;
					}
					break;
				case 2:
					playerx = 12;
					playery = 6;
					break;
				case 3:
					member = true;
					playerx = 12;
					playery = 6;
					//	loadimage(&fightingNun0, "ս����Ů1.png", pictureSize, pictureSize);
					break;
			}
			map[playerx][playery] = 99;
			if (member)
			{
				map[playerx][playery] = 100;
				member = false;
			}
			flag = false;
		}

		// ���µ�ͼ
		setMap();

		// ������ʾ��ɫ��Ϣ
		setPlayer(); 
	}
}
