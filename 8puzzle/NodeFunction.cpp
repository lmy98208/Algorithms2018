#include "NodeFunction.h"
#include <algorithm>//sort头文件

#define MAXDEP 5
/*输出节点*/
void CNode::printNode()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout <<"\t"<< nine[i][j];
		cout << endl;
	}
}
/*匹配节点*/
bool CNode::matchNode(CNode & node1, CNode & node2)
{
	int i, j;
	bool result = true;
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			if (node1.nine[i][j] != node2.nine[i][j])
			{
				result = false;
				break;
			}

		}
	return result;
}
/*判重*/
bool CNode::isExist(deque<CNode> &openStack, vector<CNode>& closedList, CNode &node)
{
	bool result = false;
	deque<CNode>::iterator qit = openStack.begin();
	vector<CNode>::iterator vit = closedList.begin();
	CNode temp;
	while (qit != openStack.end())
	{
		if (temp.matchNode(*qit++, node))
		{
			result = true;
			break;
		}
	}
	while (vit != closedList.end())
	{
		if (temp.matchNode(*vit++, node))
		{
			result = true;
			break;
		}
	}

	return result;
}
/*获取启发值，深度+与目标节点不同的数字个数*/
int CNode::getHeuristic(CNode& node, CNode &des)
{
	int i, j;
	int result = 0;
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			if (node.nine[i][j] != des.nine[i][j])
				result++;
		}
	return result+node.dep;
}
/*判断能找到路径*/
bool CNode::existSolution(CNode & start, CNode & end)
{
	bool result = false;
	int i, j, count1 = 0, count2 = 0;
	int a[3 * 3];
	int b[3 * 3];
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			if (start.nine[i][j] != 0)
				a[count1++] = start.nine[i][j];
			if (end.nine[i][j] != 0)
				b[count2++] = end.nine[i][j];
		}
	int rsum = 0, tsum = 0;
	for (i = 0; i<8; i++)
		for (j = 0; j<i; j++)
		{
			if (a[j]<a[i])
				rsum++;
			if (b[j]<b[i])
				tsum++;
		}
	if (rsum % 2 == tsum % 2)
		result = true;
	return result;
}

bool CNode::findSolution(CNode &initilNode, CNode &targetNode, deque<CNode> &openList, vector<CNode> &closedList,string modu)
{
	int parent = -1;//parent指示父节点下标
	bool flag = false;//结果标志
	openList.push_back(initilNode);//初始节点入栈、队列
									//以下求解
	CNode temp;
	while ((!openList.empty()) && (!flag))//当open表不为空或没有找到目标节点时
	{
		if (modu == "dfs") {//深度优先时，open表当栈用
			temp = openList.back();//open表中节点赋给临时节点temp
			openList.pop_back();//栈顶节点出站
		}
		//广度优先和启发时，open表当队列用	
		else if (modu == "bfs" || modu == "heuristic") {//广度优先和启发时，open表当队列用
			temp = openList.front();//取启发值最小的节点
			openList.pop_front();
		}

		closedList.push_back(temp);//temp压入close表中
		parent = closedList.size() - 1;

		if (temp.matchNode(temp, targetNode))//判断临时节点temp和目标节点targetNode是否一致
		{
			flag = true;//一致则将结果标志设为true
			break;//跳出循环
		}

		//当深度优先时深度不大于最大深度 或 广度优先 或 启发时
		if ((modu=="dfs"&&temp.dep < MAXDEP)||modu=="bfs"||modu=="heuristic")
		{
			if (temp.j>0)//空白格所在列不为0，向左移动
			{
				CNode left = temp;
				left.nine[temp.i][temp.j] = left.nine[temp.i][temp.j - 1];
				left.nine[temp.i][temp.j - 1] = 0;//元素交换
				left.parent = parent;
				left.i = temp.i;
				left.j = temp.j - 1;
				left.step = "左";
				if (!temp.isExist(openList, closedList, left))//判断节点是否存在
				{
					if (modu == "heuristic") {//启发模式时 需要计算深度和启发值
						left.dep++;
						left.heuristic = getHeuristic(left, targetNode);
					}
					else if (modu=="dfs")//深度优先时，记录深度
						left.dep++;//可扩展的节点深度+1
					openList.push_back(left);//三个模式都要压入open表
				}			
			}
			if (temp.i>0)//空白格所在行不为0，向上移动
			{
				CNode up = temp;
				up.nine[temp.i][temp.j] = up.nine[temp.i - 1][temp.j];
				up.nine[temp.i - 1][temp.j] = 0;//元素交换
				up.parent = parent;
				up.i = temp.i - 1;
				up.j = temp.j;
				up.step = "上";
				if (!temp.isExist(openList, closedList, up))//判断节点是否存在
				{
					if (modu == "heuristic") {//启发模式时 需要计算深度和启发值
						up.dep++;
						up.heuristic = getHeuristic(up, targetNode);
					}
					else if (modu == "dfs")//深度优先时，记录深度
						up.dep++;//可扩展的节点深度+1
					openList.push_back(up);//三个模式都要压入open表
				}
			}
			if (temp.j<2)//空白格所在行不为2，向右移动
			{
				CNode right = temp;
				right.nine[temp.i][temp.j] = right.nine[temp.i][temp.j + 1];
				right.nine[temp.i][temp.j + 1] = 0;
				right.parent = parent;
				right.i = temp.i;
				right.j = temp.j + 1;
				right.step = "右";
				if (!temp.isExist(openList, closedList, right))//判断节点是否存在
				{
					if (modu == "heuristic") {//启发模式时 需要计算深度和启发值
						right.dep++;
						right.heuristic = getHeuristic(right, targetNode);
					}
					else if (modu == "dfs")//深度优先时，记录深度
						right.dep++;//可扩展的节点深度+1
					openList.push_back(right);//压入open表
				}	
			}
			if (temp.i < 2)//空白格所在行不为2，向下移动
			{
				CNode down = temp;
				down.nine[temp.i][temp.j] = down.nine[temp.i + 1][temp.j];
				down.nine[temp.i + 1][temp.j] = 0;
				down.parent = parent;
				down.i = temp.i + 1;
				down.j = temp.j;
				down.step = "下";
				if (!temp.isExist(openList, closedList, down))//判断节点是否存在
				{
					if (modu == "heuristic") {//启发模式时 需要计算深度和启发值
						down.dep++;
						down.heuristic = getHeuristic(down, targetNode);
					}
					else if (modu == "dfs")//深度优先时，记录深度
						down.dep++;//可扩展的节点深度+1
					openList.push_back(down);//压入open表
				}
			}
			if(modu=="heuristic")//启发模式下，将队列按按照启发值的大小从小到大排队
				sort(openList.begin(), openList.end(), isLess);//排序,调整队列
		}
	}
	return flag;
}

void CNode::printSolution(bool flag, vector<CNode> &closedList)
{
	stack<CNode> movepath;
	if (!flag)//无法获得目标节点
	{
		cout << "无法从初始节点移动至目标节点" << endl;
	}
	else//可以移动至目标节点，问题有解
	{
		CNode last = closedList.back();//从最后节点沿父指针向上找
		while (last.parent != -1)
		{
			movepath.push(last);//先进后出
			last = closedList[last.parent];
		}
		cout << "目标可解,移动步骤如下:" << endl;
		string step;
		cout << "步数：" << movepath.size() << endl;
		while (!movepath.empty())
		{
			step = movepath.top().step;
			//movepath.top().printNode();
			cout << step ;
			movepath.pop();
		}
		cout << endl;
	}
}

bool isLess(const CNode & node1, const CNode & node2)
{
	return node1.heuristic<node2.heuristic;
}