#ifndef _Node_H
#define _Node_H
#include<iostream>
#include<string>
#include<deque>
#include<vector>
#include<stack>
using namespace std;

class CNode {
public:
	int nine[3][3];//九宫格
	int parent;//父节点，根节点的父节点为-1
	int i;//空白所在行
	int j;//空白所在列
	string step;//从上一节点移动至此节点所需操作
	int dep;//节点深度
	int heuristic;//启发函数值

	void printNode();//打印节点
	bool matchNode(CNode &node1,CNode &node2);//匹配节点
	bool isExist(deque<CNode> &openStack, vector<CNode> &closedList, CNode& node);//判重，即open表closed表是否出现过此节点
	int getHeuristic(CNode &node, CNode &des);//获得启发值（深度+错误的格子）
	bool existSolution(CNode &start, CNode &end);//是否存在解决方案
	//选找解决方案
	bool findSolution(CNode &initilNode,CNode &targetNode, deque<CNode> &openList, vector<CNode> &closedList,string modu);
	void printSolution(bool flag, vector<CNode> &closedList);//打印解决方案
};

bool isLess(const CNode& node1, const CNode& node2);//比较启发值

#endif // !_Node_H