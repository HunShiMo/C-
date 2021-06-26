#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

//加载游戏图片
void initgamePicture();

//显示角色信息
void setPlayer();

//初始化游戏角色
void initPlayer();

//加载游戏地图
void setMap();

//把整数转化成字符串
char* intToString(int Number);

//开始游戏
void startGame();

// 与那个怪物打
int combat(int x);

// 模拟打怪的过程
int VS(int playHP, int playATT, int playDEF, int monHP, int monATT, int monDEF);

// 保存游戏地图数据
void saveGame();

// 读取游戏地图数据
void loadGame();

void beforeStart();

//加载选项
void  startUp();

/**
 * 判断下一步的内容
 *
 * nextplayerx, nextplayery 表示下一步的坐标，
 * playerXY 表示向哪个方向移动, 
 * step 步长
 */
boolean check(int nextPlayerx, int nextPlayery, int* playerXY, int step);

/*
 * 函数 boolean check(int nextPlayerx, int nextPlayery, int* playerXY, int step) 的部分重复代码
 */
void innerFuncAboutCheck(int nextPlayerx, int nextPlayery, int* playerXY, int step);

/*
 *	重置地图
 */
void resetMapGroup();

// 玩家在地图中的位置，以整个游戏画面左上角为坐标原点，向下为x轴正方向，向右为y轴正方向
int playerx, playery;

int isMeetNPC = false;

char str[20] = "";

// 当前是哪张地图
int mapNum = 0;

// 地图组
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
	//玩家名字
	char name[20] = "希尔薇娅";
	//血量
	int HP;
	// 魔法
	int MP;
	//防御
	int DEF;
	//攻击
	int ATT;
	//等级
	int LV;
	//经验
	int EXP;
	//蓝钥匙数量
	int numBlueKey;
	//黄钥匙数量
	int numYellowKey;
} player;

//怪物属性
struct monster {
	//血量	
	int HP;
	//攻击
	int ATT;
	//防御
	int DEF;
	//经验
	int EXP;
};

//哥布林属性   
struct monster goblinWarriorProperty = { 12, 4, 0, 10 };

//近卫骑士属性
struct monster guardKnightProperty = { 12, 9, 7, 15 };

//史莱姆属性
struct monster slimeBeastProperty = { 6, 2, 0, 5 };

//吞噬者领主属性
struct monster gobblerLordProperty = { 20, 1, 5, 0 };

//真实形态
struct monster gobblerLordProperty1 = { 90, 11, 0, 50 };

//无首战士属性
struct monster headlessWarriorProperty = { 20, 10, 10, 25 };

//自动防御魔器属性
struct monster automaticDefenseMagicWeaponProperty = { 6, 20, 0, 10 };


int main()
{
	initPlayer();
	hwnd = initgraph(pictureSize * 14, pictureSize * 13);
	SetWindowTextA(hwnd, "Deos occidere");
	initgamePicture();

	mciSendString("open bgm.mp3 alias bkmusic", NULL, 0, NULL);
	//循环播放音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);

	while (!playerDie) {
		//加载玩家选项
		startUp();
		// 玩家退出游戏
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
	
	closegraph();//关闭
	return 0;
}

/*
*
*   加载玩家选项
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
	setbkmode(TRANSPARENT);         //设置文字背景混合模式，一般使用文字背景色前都会加上
	bool start = false;
	char ch;
	setcolor(GREEN);
	rectangle(145, 450/*左边y*/, 450 + 75, 525/*右边y*/);
	settextstyle(75, 0, "楷体");
	while (!start) {
		while (!start) {
			setcolor(YELLOW);
			outtextxy(150, 450, "继续游戏");//输出“继续游戏”文字
			outtextxy(150, 530, "开始新游戏");//输出“开始新游戏”文字
			outtextxy(150, 610, "退出游戏");//输出“退出游戏”文字

			setcolor(GREEN);
			
			ch = _getch();
			switch (ch)
			{
			case ' ':
				clearrectangle(145, 450, 450 + 75, 525);
				clearrectangle(145, 450 + 80, 450 + 75, 525 + 80);
				clearrectangle(145, 450 + 80 * 2, 450 + 75, 525 + 80 * 2);
				rectangle(145, 450 + 80 * (i )/*左边y*/, 450 + 75, 525 + 80 * (i )/*右边y*/);
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
			// 继续游戏
		case 1:
			loadGame();
			 //MessageBox(hwnd, "继续游戏", "hah", MB_OK);
			break;

			//开始新游戏
		case 2:
			resetMapGroup();
			 //MessageBox(hwnd, "开始游戏", "hah", MB_OK);
			break;

			// 结束游戏
		case 0:
			if (MessageBox(hwnd, "确定退出游戏", "提示", MB_YESNO) == IDYES) {
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
 * 显示角色信息
 */
void setPlayer() {
	setcolor(WHITE);
	settextstyle(13, 0, "宋体");
	putimage(60 * 13, 0, &infoBar);
	outtextxy(60 * 13 + 5, 103, player.name);

	settextstyle(20, 0, "宋体");
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
 * 加载游戏图片到内存中
 */
void initgamePicture() {
	loadimage(&npc, "npc.png", pictureSize, pictureSize);
	loadimage(&floor, "地板.png", pictureSize, pictureSize);
	loadimage(&defenseGems, "防御宝石.png", pictureSize, pictureSize);
	loadimage(&goblinWarrior, "哥布林战士.png", pictureSize, pictureSize);
	loadimage(&attackGems, "攻击宝石.png", pictureSize, pictureSize);
	loadimage(&yellowDoor, "黄门.png", pictureSize, pictureSize);
	loadimage(&yellowKey, "黄钥匙.png", pictureSize, pictureSize);
	loadimage(&infoBar, "角色信息栏.png");
	loadimage(&guardKnight, "近卫骑士.png", pictureSize, pictureSize);
	loadimage(&blueDoor, "蓝门.png", pictureSize, pictureSize);
	loadimage(&blueKey, "蓝钥匙.png", pictureSize, pictureSize);
	loadimage(&wall, "墙面.png", pictureSize, pictureSize);
	loadimage(&lastFloor, "上一层.png", pictureSize, pictureSize);
	loadimage(&holyWaterBottle, "圣水瓶.png", pictureSize, pictureSize);
	loadimage(&bladeOfLost, "失落之剑.png", pictureSize, pictureSize);
	loadimage(&cross, "十字架.png", pictureSize, pictureSize);
	loadimage(&slimeBeast, "史莱姆兽.png", pictureSize, pictureSize);
	loadimage(&gobblerLord, "吞噬者领主.png", pictureSize, pictureSize);
	loadimage(&headlessWarrior, "无首武士.png", pictureSize, pictureSize);
	loadimage(&nextFloor, "下一层.png", pictureSize, pictureSize);
	loadimage(&fightingNun, "战斗修女.png", pictureSize, pictureSize);
	loadimage(&blessedShield, "祝福之盾.png", pictureSize, pictureSize);
	loadimage(&automaticDefenseMagicWeapon, "自动防御魔器.png", pictureSize, pictureSize);
	loadimage(&gameOverReal, "真结局.png");
	loadimage(&beforeStartPic, "开场介绍.png");
	loadimage(&archivePoint, "存档点.png", pictureSize, pictureSize);
	loadimage(&water, "水面.png", pictureSize, pictureSize);
	loadimage(&greendoor, "传送阵假结局.png", pictureSize, pictureSize);
	loadimage(&Startup, "开场界面.png");
	loadimage(&fightingNun0, "战斗修女0.png", pictureSize, pictureSize);
	loadimage(&redfloor, "红地板.png", pictureSize, pictureSize);
	loadimage(&fightingNun_0, "战斗修女_0.png", pictureSize, pictureSize);
}

/*
 * 初始化游戏角色
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

	// 以整个游戏画面左上角为坐标原点，向下为x轴正方向，向右为y轴正方向
	// 玩家初始坐标(11,8)
	playerx = 12;
	playery = 6;
}

/*
 * 整数转换为字符
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
 *加载游戏地图
 */
void setMap() {
	// 高
	for (int i = 0; i < 13; i++) {
		// 宽
		for (int j = 0; j < 13; j++) {
			switch (map[i][j]) {

				//传送第四层
			case -7:
				putimage(j * pictureSize, i * pictureSize, &greendoor);
				break;
				//水面
			case -3:
				putimage(j * pictureSize, i * pictureSize, &water);
				break;


				//墙 
			case -1:
			case 0:
				putimage(j * pictureSize, i * pictureSize, &wall);          
				break;

				//地板
			case -2:
			case 1:
				putimage(j * pictureSize, i * pictureSize, &floor);        
				break;

				//红地板//第四层触发机制
			case -4:
			case -5:
			case -6:
			case -8:
				putimage(j * pictureSize, i * pictureSize, &redfloor);
				break;

				//蓝门
			case 2:
				putimage(j * pictureSize, i * pictureSize, &blueDoor);     
				break;

				//黄门
			case 3:
				putimage(j * pictureSize, i * pictureSize, &yellowDoor);    
				break;

				//防御宝石
			case 4:
				putimage(j * pictureSize, i * pictureSize, &defenseGems);         
				break;

				//攻击宝石
			case 5:
				putimage(j * pictureSize, i * pictureSize, &attackGems);          
				break;

				//蓝钥匙
			case 6:
				putimage(j * pictureSize, i * pictureSize, &blueKey);       
				break;

				//黄钥匙
			case 7:
				putimage(j * pictureSize, i * pictureSize, &yellowKey);     
				break;

				//圣水
			case 8:
				putimage(j * pictureSize, i * pictureSize, &holyWaterBottle);          
				break;

				//十字架
			case 9:
				putimage(j * pictureSize, i * pictureSize, &cross);         
				break;

				//npc 一层的那个
			case 10:
				putimage(j * pictureSize, i * pictureSize, &npc);        
				break;

				//自动防御魔器
			case 11:
				putimage(j * pictureSize, i * pictureSize, &automaticDefenseMagicWeapon);     
				break;

				//近卫骑士
			case 12:
				putimage(j * pictureSize, i * pictureSize, &guardKnight);      
				break;

				//无首武士
			case 13:
				putimage(j * pictureSize, i * pictureSize, &headlessWarrior);        
				break;

				//史莱姆兽
			case 14:
				putimage(j * pictureSize, i * pictureSize, &slimeBeast);      
				break;

				//哥布林战士
			case 15:
				putimage(j * pictureSize, i * pictureSize, &goblinWarrior);        
				break;

				//失落之剑
			case 16:
				putimage(j * pictureSize, i * pictureSize, &bladeOfLost);        
				break;

				// 吞噬者领主
			case 17:
			case 18:
			case 19:
				putimage(j * pictureSize, i * pictureSize, &gobblerLord);
				break;

			case 21:
				putimage(j * pictureSize, i * pictureSize, &blessedShield);
				break;

				// npc 二层的那个
			case 20:
				putimage(j * pictureSize, i * pictureSize, &npc);
				break;

				// 存档点
			case 22:
				putimage(j * pictureSize, i * pictureSize, &archivePoint);
				break;

				//上一层
			case 97:
				putimage(j * pictureSize, i * pictureSize, &lastFloor);
				break;

				//下一关
			case 98:
				putimage(j * pictureSize, i * pictureSize, &nextFloor);         
				break;

				//玩家
			case 99:
				putimage(j * pictureSize, i * pictureSize, &fightingNun);          
				break;

				//玩家
			case 100:
				putimage(j * pictureSize, i * pictureSize, &fightingNun_0);
				break;
			}
		}
	}
}


/*
 * 遇到怪物时弹出对话框
 */
int combat(int x) {
	int ID;
	switch (x) {
	case 10:
		MessageBox(hwnd, "我在你的命运征途中预见了三种结局", "NPC", MB_YESNO);
		return 1;
		break;
	case 11:
		ID = MessageBox(hwnd, "遇到自动防御魔器，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, automaticDefenseMagicWeaponProperty.HP, automaticDefenseMagicWeaponProperty.ATT, automaticDefenseMagicWeaponProperty.DEF)) {
				player.EXP += automaticDefenseMagicWeaponProperty.EXP;
				return 1;
			}
		}
		break;
	case 12:
		ID = MessageBox(hwnd, "遇到近卫骑士，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, guardKnightProperty.HP, guardKnightProperty.ATT, guardKnightProperty.DEF)) {
				player.EXP += guardKnightProperty.EXP;
				return 1;
			}
		}
		break;
	case 13:
		ID = MessageBox(hwnd, "遇到无首武士，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, headlessWarriorProperty.HP, headlessWarriorProperty.ATT, headlessWarriorProperty.DEF)) {
				player.EXP += headlessWarriorProperty.EXP;
				return 1;
			}
		}
		break;
	case 14:
		ID = MessageBox(hwnd, "遇到史莱姆兽，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, slimeBeastProperty.HP, slimeBeastProperty.ATT, slimeBeastProperty.DEF)) {
				player.EXP += slimeBeastProperty.EXP;
				return 1;
			}
		}
		break;
	case 15:
		ID = MessageBox(hwnd, "遇到哥布林战士，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			if (VS(player.HP, player.ATT, player.DEF, goblinWarriorProperty.HP, goblinWarriorProperty.ATT, goblinWarriorProperty.DEF)) {
				player.EXP += goblinWarriorProperty.EXP;
				return 1;
			}
		}
		break;

	case 17:
		MessageBox(hwnd, "遇到吞噬者领主，是否攻击？", "提示", MB_OK);
		MessageBox(hwnd, "看来，我布下的传送结界还是有用的，进监狱去吧！！！", "gobblerLord", MB_OK);
		map[3][6] = 2;
		map[6][6] = 2;
		map[0][6] = 18;
		//	map[0][6] = 18;
		break;

	case 18:
		ID = MessageBox(hwnd, "遇到吞噬者领主，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			MessageBox(hwnd, "你赢了快走吧,向着你的左前方", "吞噬者领主", MB_OK);
			map[2][6] = 19;
			map[0][6] = 1;

		}
		break;
	case 19:
		ID = MessageBox(hwnd, "遇到吞噬者领主，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			//map[2][1] = 1;
			map[2][6] = 19;

			MessageBox(hwnd, "蠢货 怎么还不走，那你就去死吧", "吞噬者领主", MB_OK);
			if (VS(player.HP, player.ATT, player.DEF, gobblerLordProperty1.HP, gobblerLordProperty1.ATT, gobblerLordProperty1.DEF)) {
				player.EXP += gobblerLordProperty.EXP;
				return 1;
			}
		}
		break;

	case 20:
		MessageBox(hwnd, "你醒了，我留了一把蓝钥匙，听说顶层的结构是对称的", "NPC", MB_OK);
		isMeetNPC = true;
		return 1;
		break;

	case 21:
		ID = MessageBox(hwnd, "遇到吞噬者领主，是否攻击？", "提示", MB_YESNO);
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
 * 读取游戏地图数据
 */
void loadGame() {
	FILE* fp = NULL;
	int num = 0;
	int count = 0;
	int i = 0;//加载的地图信息
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
 * 保存游戏地图数据
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

	// 保存玩家信息
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
 * 计算战斗是否胜利
 */
int VS(int playHP, int playATT, int playDEF, int monHP, int monATT, int monDEF)
{
	// 玩家攻击力小于等于怪物防御力，无法破防，要么陷入死循环，要么被打死
	if (playATT <= monDEF) {
		MessageBox(hwnd, "打不死", "提示", MB_YESNO);
		return 0;
	}
	// 玩家攻击力大于怪物防御力，且防御力大于怪物攻击力，则怪物必死，玩家不掉血
	else if (monATT <= playDEF){
		return 1;
	}
	// 玩家攻击力大于怪物防御力，且怪物攻击力大于玩家防御力，看谁血厚
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
		MessageBox(hwnd, "打不过", "提示", MB_YESNO);
		return 0;
	}
}

/*
 * 函数 boolean check(int nextPlayerx, int nextPlayery, int* playerXY, int step) 的部分重复代码
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
 * 判断下一步的内容
 * 
 * nextplayerx, nextplayery 表示下一步的坐标，
 * 
 * playerXY 表示上下走向， 左右走向， step 为-1，表示向上或者向右走
 */
boolean check(int nextPlayerx, int nextPlayery, int* playerXY, int step) {
	int isTeleportationDoor = false;
	int choiceResult = 0;

	switch (map[nextPlayerx][nextPlayery]) {
		case -2:
			gameOver();
			break;

		case -4:
			MessageBox(hwnd, "浪涛轻轻拍打着海岸，表现出一片祥和", "提示", MB_OK);
			MessageBox(hwnd, "我...真的胜利了吗？", "艾尔薇娅", MB_OK);
			map[nextPlayerx][nextPlayery] = 100;
			//innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			map[playerx][playery] = -6;
			*playerXY += step;
			break;

		case -5:
			MessageBox(hwnd, "突然，吞噬者领主背后一击，您已阵亡，请重新探索你的旅途", "提示", MB_OK);
			map[nextPlayerx][nextPlayery] = 100;
			//innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			map[playerx][playery] = -6;
			*playerXY += step;
			playerDie = true;
			break;

			//下一步是地板
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

			//下一步是蓝钥匙
		case 6:
			player.numBlueKey++;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//下一步是黄钥匙
		case 7:
			player.numYellowKey++;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//下一步是怪物
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

			//祝福之盾
		case 21:
			player.DEF += 5;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//存档
		case 22:
			choiceResult = MessageBox(hwnd, "这是魔镜，可以将你的状态写入镜内，下次再来时只需要从你熟悉的那个入口进来就好了，请问你是否存档", "NPC", MB_YESNO);
			if (choiceResult == IDYES) {
				saveGame();
			}
			break;

			//圣水和十字架
		case 8:
			player.HP += 10;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;
		case 9:
			player.HP += 20;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//红蓝门
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

			//红蓝宝石
			//红水晶+1攻击
			//蓝水晶+1防御
		case 4:
			player.DEF += 1;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;
		case 5:
			player.ATT += 1;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			//失落之剑
		case 16:
			player.ATT += 5;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			// 吞噬者领主
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
			//map[0][5] = -7;//领主被打死后仍可以向下一层
			if (combat(map[nextPlayerx][nextPlayery]) == 1) {
				mapGroup[3][3][6] = -8;
				innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			}
			break;

			// 进入到下一关
		case 98:
			isTeleportationDoor = true;
			mapNum++;
			map[playerx][playery] = 1;
			break;

			// 进入到上一关
		case 97:
			isTeleportationDoor = true;
			mapNum--;
			map[playerx][playery] = 1;
			break;
	}

	return isTeleportationDoor;
}

/*
 * 开始游戏
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

			// esc键
		case 27:
			if (MessageBox(hwnd, "确定返回开始菜单？别忘了保存游戏", "提示", MB_YESNO) == IDYES) {
				playerDie = true; 
				return;
			}
		}

		// 玩家要进入上一层或者下一层了，需要切换地图了
		if (flag) {
			map = mapGroup[mapNum];
			// 根据所要前往的地图，重新定位玩家的位置
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
					//	loadimage(&fightingNun0, "战斗修女1.png", pictureSize, pictureSize);
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

		// 更新地图
		setMap();

		// 更新显示角色信息
		setPlayer(); 
	}
}
