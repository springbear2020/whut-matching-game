#include "pch.h"
#include "CGameLogic.h"
#include"CGameDlg.h"

//初始化游戏地图
void CGameLogic::InitMap(int anMap[][4])
{
	int anTemp[4][4] = { 2,0,1,3, 2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			anMap[i][j] = anTemp[i][j];
		}
	}
}

//判断是否连线
bool CGameLogic::IsLink(int anMap[][4], Vertex v1, Vertex v2)
{
	if (anMap[v1.row][v1.col] == anMap[v2.row][v2.col]) 
	{
		return true;
	}
	return false;
}

//消子
void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2) 
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}
