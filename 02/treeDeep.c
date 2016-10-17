#include <stdio.h>
#include <stdlib.h>

#define _maxn 10

// 节点结构
typedef struct _node {
	int id;			// 当前节点ID
	int depth;		// 当前深度
	int childNumber;	// 孩子节点数目
	struct _node *next[_maxn];	// 存储所有孩子
} Node;

// 自定义创建节点
void _malloc(Node **node) {
	(*node) = (Node *)malloc(sizeof(Node));
	(*node)->depth = -1;
	(*node)->id = -1;
	(*node)->childNumber = 0;
	int i = 0;
	for(i = 0; i < _maxn; i ++) {
		(*node)->next[i] = NULL;
	}
}
// 自定义释放节点
void _free(Node **node) {
	free(*node);
}
// 初始化变量
void initial(Node **idx, Node **rtx) {
	int i;
	for(i = 0; i < 127; i ++) {
		idx[i] = NULL;
	}
	(*rtx) = NULL;
}
// 构造跟节点
void build_parent(int id, Node **idx, Node **rtx) {
	if(idx[id] == NULL) {
		if((*rtx) == NULL) {
			_malloc(rtx);
			(*rtx)->depth = 1;
			(*rtx)->id = id;

			idx[id] = *rtx;
		}
	}
}
// 构造孩子节点
void build_child(int pid, int cid, Node **idx) {
	Node *parent = idx[pid];
	_malloc(&(parent->next[parent->childNumber]));
	parent->childNumber ++;
	parent->next[parent->childNumber - 1]->depth = parent->depth + 1;
	parent->next[parent->childNumber - 1]->id = cid;

	idx[cid] = parent->next[parent->childNumber - 1];
}
// 摧毁树
void destroy(Node **rt) {
	if((*rt) != NULL) {
		int i;
		for(i = 0; i < (*rt)->childNumber; i ++) {
			destroy(&((*rt)->next[i]));
		}
	}
	free((*rt));
}
// 展示树结构 测试用
// 可以用来求树深度，不想重复写代码，所以用了下边取巧的办法
void show(Node **rt) {
	if((*rt) != NULL) {
		printf("rt = %d ", (*rt)->id);
		printf("childs: ");
		int i;
		for(i = 0; i < (*rt)->childNumber; i ++) {
			printf("%d[%d] ", (*rt)->next[i]->id, (*rt)->next[i]->depth);
		}
		puts("");
		for(i = 0; i < (*rt)->childNumber; i ++) {
			show(&((*rt)->next[i]));
		}
	}
}

int main() {
	Node *idx[127];							// 存储各个节点地址
	int line;								// 题目输入
	Node *rtx;								// 树根
	while(scanf("%d", &line) != EOF) {
		initial(idx, &rtx);					// 初始化变量
		int i, j, cnt, par, chi;
		for(i = 0; i < line; i ++) {
			scanf("%d", &par);
			build_parent(par, idx, &rtx);	// 构造父亲节点
			
			scanf("%d", &cnt);
			for(j = 0; j < cnt; j ++) {
				scanf("%d", &chi);			
				build_child(par, chi, idx);	// 构造孩子节点
			}
		}

		// 有些取巧，原因是不想写重复代码
		i = 0;
		int depth = 0;
		while(idx[i] != NULL) {
			if(depth < idx[i]->depth) {
				depth = idx[i]->depth;
			}
			i += 1;
		}
		printf("%d\n", depth);

//		show(&rtx);
		destroy(&rtx);						// 释放空间，避免内存泄漏
	}
	return 0;
}
