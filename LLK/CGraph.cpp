#include "pch.h"
#include "CGraph.h"

//构造函数
CGraph::CGraph()
{
	InitGraph();   //初始化图
}

//图结构的初始化，-1：没有图片 0：没有关系
void CGraph::InitGraph()
{
	m_nArcnum = 0;
	m_nVexnum = 0;

	//初始化顶点与边的信息
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//初始化顶点
		m_Vertices[i] = -1;
		
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			//初始化边
			m_AdjMatrix[i][j] = 0;
		}
	}
}