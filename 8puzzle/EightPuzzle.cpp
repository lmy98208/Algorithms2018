#include"NodeFunction.h"
#include<ctime>

using namespace std;
int main()
{
	/*
	利用deque既能用作队列又能用作栈的属性
	open栈/深度dfs
	open队列/广度bfs+启发
	*/
	deque<CNode> openList;
	vector<CNode> closedList;//closed列表
	int i, j;	
	clock_t start, end;//计算时间
	CNode initilNode, targetNode;//初始节点和目标节点
	cout << "请输入初始节点状态:";
	
	//双循环给初始节点initiNode赋值
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			cin >> initilNode.nine[i][j];
			if (0 == initilNode.nine[i][j])
			{
				initilNode.i = i;
				initilNode.j = j;
			}
		}
	initilNode.parent = -1;//初始节点为根节点，没有父节点
	initilNode.dep = 0;//初始节点深度为0


	cout << "请输入目标节点状态:";
	//双循环给目标节点targetNode赋值
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			cin >> targetNode.nine[i][j];
			//并记录空白格所在的行和列
			if (0 == targetNode.nine[i][j])
			{
				targetNode.i = i;
				targetNode.j = j;
			}
		}
	targetNode.parent = -1;
	bool flag = true;
	double endtime = 0.0;

	cout << "\n***************宽度优先：***************" << endl;
	start = clock();
	if (initilNode.existSolution(initilNode, targetNode))
		flag = initilNode.findSolution(initilNode, targetNode, openList, closedList, "bfs");
	end = clock();
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	initilNode.printSolution(flag, closedList);//打印过程
	cout << "time:" << endtime * 1000 << "ms" << endl;
	cout << "open:" << openList.size() << "\tclosed:" << closedList.size();

	openList.clear();
	closedList.clear();//清空

	cout << "\n***************深度优先：***************" << endl;
	start = clock();
	flag=initilNode.findSolution(initilNode,targetNode,openList,closedList,"dfs");
	end = clock();
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	initilNode.printSolution(flag,closedList);//打印过程
	cout << "time:" << endtime * 1000 << "ms" << endl;
	cout <<"open:"<< openList.size()<<"\tclosed:" << closedList.size();

	openList.clear();
	closedList.clear();//清空

	cout << "\n***************启发算法：***************" << endl;
	start = clock();
	if (initilNode.existSolution(initilNode, targetNode))
		flag = initilNode.findSolution(initilNode, targetNode, openList, closedList,"heuristic");
	end = clock();
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	initilNode.printSolution(flag, closedList);//打印过程
	cout << "time:" << endtime * 1000 << "ms" << endl;
	cout << "open:" << openList.size() << "\tclosed:" << closedList.size() << endl;
	
	return 0;

}