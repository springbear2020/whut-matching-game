#include "pch.h"
#include "CGameControl.h"

//开始游戏
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}

//设置第一个点
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}

//设置第二个点
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}

//返回元素信息
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * 4 + nCol);
}

//消子判断
bool CGameControl::Link(Vertex avPath[4], int& nVexnum)
{
	//判断两次选中的是否是同一个点
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col)
	{
		return false;
	}

	//判断图片是否相同
	if (m_graph.GetVertex(m_svSelFst.row * 4 + m_svSelFst.col) != m_graph.GetVertex(m_svSelSec.row * 4 + m_svSelSec.col))
	{
		return false;
	}

	//判断是否连通
	CGameLogic logic;
	if (logic.IsLink(m_graph, m_svSelFst, m_svSelSec))
	{
		//消子
		logic.Clear(m_graph, m_svSelFst, m_svSelSec);

		//返回路径顶点
		nVexnum = logic.GetVexPath(avPath);
		return true;
	} 
	return false;
}