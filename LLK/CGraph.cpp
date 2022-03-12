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

//添加顶点
int CGraph::AddVertex(int nInfo)
{
	if (m_nVexnum > MAX_VERTEX_NUM)
	{
		return 0;
	}
	m_Vertices[m_nVexnum] = nInfo;
	m_nVexnum++;
	return m_nVexnum;
}

//添加两个索引顶点的边
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

//根据索引，从顶点数组中取出相应的顶点
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

int CGraph::GetVexnum(void)
{
	return m_nVexnum;
}

void CGraph::UpdateVertex(int nIndex, int nInfo)
{
	m_Vertices[nIndex] = nInfo;
}

void CGraph::ClearGraph()
{
	InitGraph();
}