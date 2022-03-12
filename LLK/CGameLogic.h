#pragma once
#include"global.h"
#include"CGraph.h"

class CGameLogic
{
public:
	CGameLogic(void);   //构造函数

protected:
	Vertex m_avPath[MAX_VERTEX_NUM];   //保存在进行连接判断时所经过的顶点
	int m_anPath[MAX_VERTEX_NUM];   //保存连通路径的顶点索引
	int m_nVexNum;   //顶点数
	int m_nCorner;   //连接路径数组m_anPath中的拐点数

public:

	void InitMap(CGraph& g);
	void Clear(CGraph& g, Vertex v1, Vertex v2);   //当V1与v2连通时，将其顶点的值设为空
	bool IsLink(CGraph& g, Vertex v1, Vertex v2);  //判断顶点v1与v2是否连通
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);   //通过参数返回路径
	void UpdateArc(CGraph& g, int nRow, int nCol);   //判断游戏地图中nRow行，nCol列的顶点与它上下左右的顶点是否有边，如果有边，则更新图结构，并返回
	void PushVertex(int nV);
	void PopVertex();
	bool SearchPath(CGraph& g, int nV0, int nV1);   //采用深度优先搜索，判断V1在图g中是否连通
	bool IsExsit(int nVi);   //判断索引为nVi的顶点是否保存到连通数组m_anPath中
	bool IsCorner(void);   //判断连接路径数组中，连续三个顶点是否构成一个拐点
	bool IsBlank(CGraph& g);   //判断图g中所有的顶点是否为空
	bool SearchValidPath(CGraph& g);   //查找一对可以消除的图片
	void ResertGraph(CGraph& g);   //对图结构g钟的顶点进行重排，并更新顶点的关系
};

