#include <stdio.h>
#include <stdlib.h>

// 双向循环链表节点
typedef struct Node {
    struct Node * pre;
    struct Node * next;
    int value;
}_node;

// 定义malloc
void _malloc(_node ** node) {
    (*node) = (_node *)malloc(sizeof(_node));
    (*node)->pre = NULL;
    (*node)->next = NULL;
    (*node)->value = -1;
}

// 定义free
void _free(_node ** node) {
    free(*node);
}

// 展示双向链表  测试用
void display(_node ** head, int _size) {
    int i;
    _node * per = (*head);
    for(i = 1; i <= _size; i ++) {
        printf("%d -> ", per->value);
        per = per->next;
    }
    printf("\n");
}

// 创建双向链表
void create(_node ** head, int * _size) {
    int i;
    int size = (*_size);
    _node * per = NULL;
    _node * pes = NULL;
    for(i = 1; i <= size; i ++) {

        if(i == 1) {// 头需要处理一下 初始化一些必要变量
            _malloc(&per);
            per->value = i;
            (*head) = per;
            pes = per;
        } else {// 其他节点统一操作
            _malloc(&(per->next));
            per = per->next;

            per->value = i;
            per->pre = pes;

            pes->next = per;
            pes = pes->next;
        }
    }
    // 最后头尾连接一下
    per->next = (*head);
    (*head)->pre = per;
}

// 一轮游戏杀死一个
void kill_one(_node ** head, int * _size, int goal) {
    if( (*_size) < 1  ) {
        return ;

    }
    (*_size) -= 1;
    _node * per = (*head);
    while( -- goal > 0 ) {// 寻找被杀死的节点
        per = per->next;
    }

    // 为什么这么做,好好去理解一下指针(不做叙述)
    per = per->pre;
    _node * tmp1 = per;
    _node * tmp2 = per->next;
    _node * tmp3 = tmp2->next;
    per = tmp3;

    tmp1->next = tmp3;
    tmp3->pre = tmp1;
    _free(&tmp2);// 杀死该节点代表的人

    (*head) = per;// 双向循环链表 任何一个节点都可以为头
}

// 进行游戏
void kill(_node ** head, int * _size, int goal) {
    // 剩一个人时候结束游戏
    while((*_size) > 1) {
        display(head, (*_size));
        kill_one(head, _size, goal);
    }
}

int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF) {
        _node * root = NULL;
        int goal = m;
        int _size = n;
        create(&root, &_size);
        // display(&root, _size);
        kill(&root, &_size, goal);
        printf("%d\n", root->value);


        _free(&root);
    }
}
