#pragma once
#include"global.h"
#include"CGameLogic.h"
class CGameControl
{
public:
	int m_anMap[4][4];   //游戏地图
	//x->col,y->row
	Vertex m_svSelFst;   //第一次选中的点(x表示列)
	Vertex m_svSelSec;
public:
	void StartGame(void);   //开始游戏
	int GetElement(int nRow, int nCol);   ///获得某行某列的图片编号
	void SetFirstPoint(int nRow, int nCol);   //设置第一个点的坐标
	void SetSecPoint(int nRow, int nCol);	  //设置第二个点的坐标									
	bool Link(Vertex avPath[2]);   //连接判断函数
};

