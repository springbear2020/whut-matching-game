#include "pch.h"
#include "CGameControl.h"

//开始游戏
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}

//返回元素信息
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
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


//消子判断
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	//判断两次选中的是否是同一个点
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col)
	{
		return false;
	}

	//判断图片是否相同，如果不同则不能连通
	int	nInfo1 = m_graph.GetVertex(m_svSelFst.row * MAX_COL + m_svSelFst.col);
	int	nInfo2 = m_graph.GetVertex(m_svSelSec.row * MAX_COL + m_svSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
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

//判断是否获胜
BOOL CGameControl::IsWin(int nTime)
{
	//定义逻辑处理类
	CGameLogic logic;

	//判断游戏时间
	if (nTime <= 0)
	{
		//清除图
		m_graph.ClearGraph();
		return GAME_LOSE;
	}

	//判断是否图中所有点为空
	if (logic.IsBlank(m_graph) == true)
	{
		//清除图
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

//在地图中查找可以消除的一堆照片，返回连接路径和路径上的顶点数
bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	CGameLogic logic;

	//判断是否为空
	if (logic.IsBlank(m_graph) == true)
	{
		return false;
	}

	//查找一条有效的提示路径
	if (logic.SearchValidPath(m_graph))
	{
		//返回路径顶点
		nVexnum = logic.GetVexPath(avPath);
		return true;
	}
	return false;

}

//实现重排
void CGameControl::Resert(void)
{
	//重排图中顶点
	CGameLogic logic;
	logic.ResertGraph(m_graph);
}