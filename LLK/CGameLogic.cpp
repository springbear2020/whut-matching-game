#include "pch.h"
#include "CGameLogic.h"
#include"CGameDlg.h"

CGameLogic::CGameLogic(void)
{
	m_nVexNum = 0;
}

//初始化游戏地图
void CGameLogic::InitMap(CGraph &g)
{
	int anTemp[4][4] = { 2,0,1,3, 2,2,1,3,2,1,0,0,1,3,0,3 };
	
	//初始化顶点
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g.AddVertex(anTemp[i][j]);
		}
	}

	//初始化边
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			UpdateArc(g, i, j);
		}
	}
}

//判断是否连线
bool CGameLogic::IsLink(CGraph& g, Vertex v1, Vertex v2)
{
	return false;
}

//消子
void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{

}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}

void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}

//生成图边数组
void CGameLogic::UpdateArc(CGraph& g, int nRow, int nCol)
{
	int nV1Index = nRow * 4 + nCol;

	if (nCol > 0)
	{
		int nV2Index = nV1Index - 1;
		//判断与左边相邻的是否有关系
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//判断与左边相邻的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < 3)
	{
		int nV2Index = nV1Index + 1;
		//判断与右边相邻的是否有关系
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//判断与右边相邻的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0)
	{
		int nV2Index = nV1Index - 4;
		//判断与正上方的是否有关系
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//判断与正上方的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < 3)
	{
		int nV2Index = nV1Index + 4;
		//判断与正下方的是否有关系
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//判断与正下方的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}