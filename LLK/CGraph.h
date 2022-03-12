#pragma once
//图数据结构类
class CGraph
{
public:
	CGraph();
protected:
#define MAX_VERTEX_NUM 16   //数据元素的个数
    //顶点的数据类型
	typedef int Vertices[MAX_VERTEX_NUM];
	//边的数据类型
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	Vertices m_Vertices;   //顶点数组
	AdjMatrix m_AdjMatrix;   //关系数组
	int m_nVexnum;   //顶点数量
	int m_nArcnum;   //边的数量
public:
	void InitGraph(void);   //初始化图的顶点和关系
};

 