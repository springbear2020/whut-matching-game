#pragma once // 为了防止头文件被重复包含

typedef struct tagVertex
{
	int row;  // 行
	int col;  // 列
	int info; // 信息类
} Vertex;

#define BLANK -1
#define MAX_ROW 10		   // 初始行数
#define MAX_COL 12		   // 初始列数
#define MAX_VERTEX_NUM 120 // 顶点数
#define MAX_PIC_NUM 10	   // 图片花色
#define REPEAT_NUM 12	   // 每种花色图片个数
#define MAP_TOP 50		   // 游戏地图左上角纵坐标
#define MAP_LEFT 50		   // 游戏地图左上角横坐标
#define PIC_HEIGHT 40	   // 游戏地图高度
#define PIC_WIDTH 40	   // 游戏地图宽度

#define PLAY_TIMER_ID 1 // 计时器的编号

#define GAME_LOSE -1   // 失败
#define GAME_SUCCESS 0 // 获胜
#define GAME_PLAY 1	   // 游戏正在进行