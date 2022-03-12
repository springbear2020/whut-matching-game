#pragma once
#include"global.h"
#include"CGraph.h"

class CGameLogic
{
public:
	CGameLogic::CGameLogic(void);   //构造函数

	void InitMap(CGraph& g);
	void Clear(CGraph& g, Vertex v1, Vertex v2);   //当V1与v2连通时，将其顶点的值设为空
	bool IsLink(CGraph& g, Vertex v1, Vertex v2);  //判断顶点v1与v2是否连通
	int GetVexPath(Vertex avPath[4]);   //通过参数返回路径
	void PushVertex(Vertex v);
	void PopVertex();

protected:
	Vertex m_avPath[4];   //保存在进行连接判断时所经过的顶点
	int m_nVexNum;   //顶点数

	void UpdateArc(CGraph& g, int nRow, int nCol);   //判断游戏地图中nRow行，nCol列的顶点与它上下左右的顶点是否有边，如果有边，则更新图结构，并返回
	void AddVertex(Vertex v);   //添加一个路径顶点
	void DeleteVertex();   //取出一个顶点

};

