#pragma once

//定义顶点结构体
typedef struct tagVertex
{
	int row;   //行
	int col;   //列
	int info;   //信息类
}Vertex;

#define BLANK -1
#define MAX_VERTEX_NUM 16   //顶点的个数
#define MAX_ROW 4	  //初始行数
#define MAX_COL 4	  //初始列数


 