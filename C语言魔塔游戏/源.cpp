#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include <graphics.h>
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
 *
 */
void innerFuncAboutCheck(int nextPlayerx, int nextPlayery, int* playerXY, int step);

// 玩家在地图中的位置，以整个游戏画面左上角为坐标原点，向下为x轴正方向，向右为y轴正方向
int playerx, playery;

int isMeetNPC = false;

char str[20] = "";

// 当前是哪张地图
int mapNum = 0;

// 地图组
int mapGroup[3][13][13] = {
	{
		{ 98, 1,  15, 1,  1,  1,  1,  1, 1,  14, 0,  5,  4},
		{ 1,  1,  0,  0,  0,  0,  0,  0, 0,  14, 0,  1,  1},
		{ 0,  0,  0,  1,  1,  1,  1,  7, 0,  1,  3,  15, 1},
		{ 1,  8,  0,  1,  0,  0,  2,  0, 0,  1,  0,  1,  1},
		{ 14, 14, 0,  1,  0,  7,  1,  7, 0,  1,  0,  0,  0},
		{ 8,  1,  3,  1,  0,  1,  1,  1, 0,  1,  3,  7,  7},
		{ 0,  0,  0,  14, 0,  1,  1,  1, 0,  14, 0,  1,  1},
		{ 5,  14, 0,  14, 0,  1,  16, 1, 0,  14, 0,  1,  1},
		{ 14, 14, 0,  1,  0,  0,  0,  0, 0,  1,  3,  14, 1},
		{ 14, 14, 3,  1,  1,  1,  1,  1, 14, 1,  0,  1,  4},
		{ 0,  0,  0,  3,  0,  0,  3,  0, 0,  3,  0,  0,  0},
		{ 1,  1,  1,  11, 0,  1,  1,  7, 0,  14, 1,  1,  14},
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
		{ 1,  1,  1,  0,  15, 1,  15, 1,  1,  1,  1,  1,  7},
		{ 1,  1,  1,  0,  0,  2,  0,  0,  3,  0,  0,  3,  0},
		{ 1,  1,  1,  0,  7,  1,  7,  0,  1,  1,  0,  1,  1},
		{ 1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  0,  1,  1},
		{ 1,  98, 1,  0,  1,  17, 1,  0,  4,  1,  0,  4,  1}
	},
	
	{
		{ 8,  6,  0,  -2, 0,  1,  17, 1,  0,  8,  0,  6,  1},
		{ 1,  1,  0,  2,  0,  1,  1,  1,  0,  8,  0,  1,  1},
		{ 12, 0,  0,  2,  0,  1,  1,  1,  0,  3,  0,  0,  12},
		{ 1,  0,  -1, 2,  0,  0,  1,  0,  0,  1,  1,  0,  1},
		{ 12, -1, -1, 2,  0,  1,  1,  1,  0,  1,  1,  1,  12},
		{ 1,  0,  0,  1,  0,  1,  1,  1,  0,  1,  0,  0,  1},
		{ 1,  1,  15, 1,  0,  0,  1,  0,  0,  1,  15, 1,  1},
		{ 4,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  5},
		{ 0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0},
		{ 7,  1,  1,  11, 1,  1,  1,  1,  1,  1,  1,  3,  5},
		{ 0,  0,  3,  0,  0,  0,  3,  0,  0,  0,  3,  0,  0},
		{ 1,  1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  1,  7},
		{ 9,  1,  1,  1,  0,  97, 99, 1,  0,  1,  1,  1,  7}
	}
};

int(*map)[13] = mapGroup[mapNum];

IMAGE npc, floor, defenseGems, goblinWarrior, attackGems, yellowDoor,
yellowKey, infoBar, guardKnight, blueDoor, blueKey, wall,
lastFloor, holyWaterBottle, bladeOfLost, cross, slimeBeast,
gobblerLord, headlessWarrior, nextFloor, fightingNun, blessedShield,
automaticDefenseMagicWeapon, gameOverReal, beforeStartPic, archivePoint;

HWND hwnd;

int pictureSize = 60;

struct gameRole {
	//玩家名字
	char name[20] = "国王";
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
	initgamePicture();

	mciSendString("open bgm.mp3 alias bkmusic", NULL, 0, NULL);
	//循环播放音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);

	beforeStart();

	loadGame();

	while (1) {
		setMap();
		setPlayer();
		startGame();
	}

	return 0;
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
	putimage(60 * 13, 0, &infoBar);
	outtextxy(60 * 13 + 12, 100, player.name);
	outtextxy(60 * 13 + 12, 180, intToString(player.LV));
	outtextxy(60 * 13 + 12, 235, intToString(player.EXP));
	outtextxy(60 * 13 + 12, 362, intToString(player.HP));
	outtextxy(60 * 13 + 12, 425, intToString(player.MP));
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
	loadimage(&beforeStartPic, "开场介绍.jpg");
	loadimage(&archivePoint, "存档点.png", pictureSize, pictureSize);
}

/*
 * 初始化游戏角色
 */
void initPlayer()
{
	player.LV = 0;
	player.ATT = 100;
	player.DEF = 100;
	player.numBlueKey = 100;
	player.numYellowKey = 100;
	player.HP = 200;
	player.MP = 100;
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
				putimage(j * pictureSize, i * pictureSize, &gobblerLord);
				break;
				/*case 18://欺骗形态
					putimage(j * pictureSize, i * pictureSize, &gobblerLord);
					break;
				case 19://真实形态
					putimage(j * pictureSize, i * pictureSize, &gobblerLord);
					break;*/

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
		MessageBox(hwnd, "你有三种结局", "npc", MB_YESNO);
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
		MessageBox(hwnd, "遇到吞噬者领主，是否攻击？", "提示", MB_YESNO);
		// 此时修改的是第三层的数据
		map[0][6] = 1;
		map[2][5] = 18;
		break;

	case 18:
		ID = MessageBox(hwnd, "遇到吞噬者领主，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			//MessageBox(hwnd, "看来，我布下的传送结界还是有用的", "gobblerLord", MB_YESNO);

			MessageBox(hwnd, "你赢了快走吧", "gobblerLord", MB_YESNO);
			map[2][6] = 19;
			map[0][6] = 1;
		}
		break;
	case 19:
		ID = MessageBox(hwnd, "遇到吞噬者领主，是否攻击？", "提示", MB_YESNO);
		if (ID == IDYES)
		{
			map[2][5] = 1;
			map[2][6] = 19;
			MessageBox(hwnd, "蠢货 怎么还不走", "gobblerLord", MB_YESNO);
			if (VS(player.HP, player.ATT, player.DEF, gobblerLordProperty1.HP, gobblerLordProperty1.ATT, gobblerLordProperty1.DEF)) {
				player.EXP += gobblerLordProperty.EXP;
				return 1;
			}
		}
		break;

	case 20:
		MessageBox(hwnd, "你醒了，我留了一把蓝钥匙，听说顶层的结构是对称的", "npc", MB_OK);
		isMeetNPC = true;
		return 1;
		break;

	case 22:
		ID = MessageBox(hwnd, "保存游戏？", "电脑", MB_YESNO);
		if (ID == IDYES) {
			///
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
	int i = 0;
	int j = 0;
	int k = 0;
	fopen_s(&fp, "archives.raymond", "r");

	if (fp == NULL) {
		printf("Failed to open the archives.raymond !\n");
		exit(1);
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
			j = 0;
		}
	}

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

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 13; j++) {
			for (int k = 0; k < 13; k++) {
				fprintf(fp, "%5d", mapGroup[i][j][k]);
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
			if (monHP < 0) {
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

	switch (map[nextPlayerx][nextPlayery]) {
		case -2:
			gameOver();
			break;
			//下一步是地板
		case 1:
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
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

			//红蓝药水
		case 8:
			player.HP += 200;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;
		case 9:
			player.HP += 500;
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

			//红蓝水晶
			//红水晶+2攻击
			//蓝水晶+2防御
		case 4:
			player.DEF += 2;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;
		case 5:
			player.ATT += 2;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

		case 16:
			player.ATT += 5;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;

			// 吞噬者领主
		case 17:
			combat(map[nextPlayerx][nextPlayery]);
			mapNum--;
			isTeleportationDoor = true;
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
					break;
				case 2:
					playerx = 12;
					playery = 6;
			}
			map[playerx][playery] = 99;
			flag = false;
		}

		// 更新地图
		setMap();

		// 更新显示角色信息
		setPlayer(); 
	}
}
