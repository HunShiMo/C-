#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include <graphics.h>
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
 *
 */
void innerFuncAboutCheck(int nextPlayerx, int nextPlayery, int* playerXY, int step);

// ����ڵ�ͼ�е�λ�ã���������Ϸ�������Ͻ�Ϊ����ԭ�㣬����Ϊx������������Ϊy��������
int playerx, playery;

int isMeetNPC = false;

char str[20] = "";

// ��ǰ�����ŵ�ͼ
int mapNum = 0;

// ��ͼ��
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
	//�������
	char name[20] = "����";
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
	initgamePicture();

	mciSendString("open bgm.mp3 alias bkmusic", NULL, 0, NULL);
	//ѭ����������
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
 * ��ʾ��ɫ��Ϣ
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
	loadimage(&beforeStartPic, "��������.jpg");
	loadimage(&archivePoint, "�浵��.png", pictureSize, pictureSize);
}

/*
 * ��ʼ����Ϸ��ɫ
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
				putimage(j * pictureSize, i * pictureSize, &gobblerLord);
				break;
				/*case 18://��ƭ��̬
					putimage(j * pictureSize, i * pictureSize, &gobblerLord);
					break;
				case 19://��ʵ��̬
					putimage(j * pictureSize, i * pictureSize, &gobblerLord);
					break;*/

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
		MessageBox(hwnd, "�������ֽ��", "npc", MB_YESNO);
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
		MessageBox(hwnd, "�����������������Ƿ񹥻���", "��ʾ", MB_YESNO);
		// ��ʱ�޸ĵ��ǵ����������
		map[0][6] = 1;
		map[2][5] = 18;
		break;

	case 18:
		ID = MessageBox(hwnd, "�����������������Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			//MessageBox(hwnd, "�������Ҳ��µĴ��ͽ�绹�����õ�", "gobblerLord", MB_YESNO);

			MessageBox(hwnd, "��Ӯ�˿��߰�", "gobblerLord", MB_YESNO);
			map[2][6] = 19;
			map[0][6] = 1;
		}
		break;
	case 19:
		ID = MessageBox(hwnd, "�����������������Ƿ񹥻���", "��ʾ", MB_YESNO);
		if (ID == IDYES)
		{
			map[2][5] = 1;
			map[2][6] = 19;
			MessageBox(hwnd, "���� ��ô������", "gobblerLord", MB_YESNO);
			if (VS(player.HP, player.ATT, player.DEF, gobblerLordProperty1.HP, gobblerLordProperty1.ATT, gobblerLordProperty1.DEF)) {
				player.EXP += gobblerLordProperty.EXP;
				return 1;
			}
		}
		break;

	case 20:
		MessageBox(hwnd, "�����ˣ�������һ����Կ�ף���˵����Ľṹ�ǶԳƵ�", "npc", MB_OK);
		isMeetNPC = true;
		return 1;
		break;

	case 22:
		ID = MessageBox(hwnd, "������Ϸ��", "����", MB_YESNO);
		if (ID == IDYES) {
			///
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
 * ������Ϸ��ͼ����
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

	switch (map[nextPlayerx][nextPlayery]) {
		case -2:
			gameOver();
			break;
			//��һ���ǵذ�
		case 1:
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
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

			//����ҩˮ
		case 8:
			player.HP += 200;
			innerFuncAboutCheck(nextPlayerx, nextPlayery, playerXY, step);
			break;
		case 9:
			player.HP += 500;
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

			//����ˮ��
			//��ˮ��+2����
			//��ˮ��+2����
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

			// ����������
		case 17:
			combat(map[nextPlayerx][nextPlayery]);
			mapNum--;
			isTeleportationDoor = true;
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
					break;
				case 2:
					playerx = 12;
					playery = 6;
			}
			map[playerx][playery] = 99;
			flag = false;
		}

		// ���µ�ͼ
		setMap();

		// ������ʾ��ɫ��Ϣ
		setPlayer(); 
	}
}
