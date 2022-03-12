#pragma once
#include"global.h"

class CGameLogic
{
public:
	void InitMap(int anMap[][4]);
	bool IsLink(int anMap[][4], Vertex v1, Vertex v2);  //判断顶点v1与v2是否连通
	void Clear(int anMap[][4], Vertex v1, Vertex v2);   //当V1与v2连通时，将其顶点的值设为空
	bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);   //行号相同，判断横向是否连通
	bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);
	bool LineX(int anMap[][4], int nRow, int nCol1, int nCol2);
	bool LineY(int anMap[][4], int nRow1, int nRow2, int nCol);
	bool OneCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	bool TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	CGameLogic::CGameLogic(void);   //构造函数
	int GetVexPath(Vertex avPath[4]);   //通过参数返回路径
protected:
	Vertex m_avPath[4];   //保存在进行连接判断时所经过的顶点
	int m_nVexNum;   //顶点数

	void AddVertex(Vertex v);   //添加一个路径顶点
	void DeleteVertex();   //取出一个顶点

};

