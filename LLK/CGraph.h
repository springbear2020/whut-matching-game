#pragma once
#include"global.h"
//图数据结构类
class CGraph
{
public:
	CGraph();
	
	typedef int Vertices[MAX_VERTEX_NUM];   //顶点的数据类型
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   	//边的数据类型

protected:
	Vertices m_Vertices;   //顶点数组
	AdjMatrix m_AdjMatrix;   //关系数组

	int m_nVexnum;   //顶点数量
	int m_nArcnum;   //边的数量

public:
	void InitGraph(void);   //初始化图的顶点和关系
	int AddVertex(int nInfo);   //将顶点info加入到顶点数组中
	void AddArc(int nV1Index, int nV2Index);  //添加nV1Index与nV2Index的关系
	int GetVertex(int ninfo);   //获取顶i的那数组中索引为nIndex的顶点
	bool GetArc(int nV1Index, int nV2Index);   //获得两个顶点的弧信息
	void UpdateVertex(int nIndex, int Info);   //将图顶点数组中索引号为nIndex的顶点的值更新为info 
	int GetVexnum(void);   //获取顶点数组中的顶点数
	void ClearGraph();   //将图中顶点和边还原为初始状态
	void ChangeVertex(int nIndex1, int nIndex2);   //调换两个点的位置

};

 