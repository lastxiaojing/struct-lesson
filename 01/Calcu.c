#include <stack>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#define _maxn 255

using namespace std;

// 取出一个数字
int getNumber(char *input, int *i) {
	int pos = *i;
	int res = 0;
	while(input[pos] >= '0' && input[pos] <= '9') {
		res *= 10;
		res += (input[pos] - '0');
		pos += 1;
	}
	*i = pos - 1;					// 要保证下边的逻辑
	return res;
}
// 判断数字、运算符
int isNumber(char ch) {
	if(ch >= '0' && ch <= '9')
		return 1;
	return 0;
}
// now:当前符号		bef:前一个符号
int ComPri(char now, char bef) {
	// 可以清除括号, 好像没用到
	if(now == '(' && bef == ')') {
		return 2;
	}
	if(now == '(' || bef == '(') {
		return -1;
	}
	// 反括号需计算处理掉
	if(now == ')') {
		return 1;
	}
	// 处理非括号情况
	if(now == '+' || now == '-') {
		if(bef == '+' || bef == '-' || bef == '*' || bef == '/') {
			return 1;
		} else {
			return -1;
		}
	}
	if(now == '*' || now == '/') {
		if(bef == '*' || bef == '/') {
			return 1;
		} else {
			return -1;
		}
	}
}

// 计算一次		传递栈的引用
int Calculate(stack<char>&Sym, stack<int>&Dat) {
	// 该清理括号了
	if(Sym.top() == '(') {
		return 0;
	}

	// 运算逻辑处理
	int second = Dat.top();
	Dat.pop(); 
	int first = Dat.top();
	Dat.pop();

	char opera = Sym.top();
	Sym.pop();
	switch(opera) {
		case '+':
			Dat.push(first + second);
			break;
		case '-':
			Dat.push(first - second);
			break;
		case '*':
			Dat.push(first * second);
			break;
		case '/':
			Dat.push(first / second);
			break;
		default:
			break;
	}
	// 正常结束
	return 1;
}

int comp(stack<char>Sym, stack<int>Dat, char *input) {
	int len = strlen(input);
	int i, number, flag;
	char ch, top;
	i = 0;
	int lo = 1;
	while(i < len) {

		if(lo++ > 500) {
			// 出现死循环时候报警
			cout << "Dead Circulation" << endl;
			exit;
		}

		ch = input[i];
		if(isNumber(ch)) {										// 数字可以直接入栈
			number = getNumber(input, &i);
			Dat.push(number);
			i ++;
		} else {
			// 恶心的地方开始了
			if(Sym.size() == 0) {								// 第一个符号不用比较
				Sym.push(ch);
				i ++;
				continue;
			} else {
				flag = ComPri(ch, Sym.top());					// 计算当前运算符和上一个运算符的优先级
				if(flag == 2 || Sym.top() == ')') {
					// 清除括号
					Sym.pop();
					Sym.pop();
					i ++;
					continue;
				} else if(flag == -1) {
					// 优先级不够、不予计算
					Sym.push(ch);
					i ++;
					continue;
				} else {										// 计算出当前可计算的合法表达式
					// 从左向右计算
					while(Sym.size() > 0 && (ComPri(ch, Sym.top()) > 0)) {	// 这个可以单独写个函数，和下边重复了(可以优化的地方)
						if(0 == Calculate(Sym, Dat)) {
							// 该清理括号了
							break;
						} else {
							// 正常结束
						}
					}
					if(Sym.size() == 0) {
						// 容器里的已经计算完成
						i ++;
					}
					Sym.push(ch); // 把下一个符号加进去
				}
			}
		}
	}
	// 剩余表达式计算
	while(Sym.size() > 0) {
		if(0 == Calculate(Sym, Dat)) {
			// 该清理括号了
			break;
		} else {
			// 正常结束
		}
	}
	// 返回计算结果或者错误码
	return Dat.size() > 0 ? Dat.top() : -1;
}

int main() {
	char input[_maxn];			// 输入表达式
	while(cin >> input) {
		stack<char>Sym;			// 为了好看 没用
		stack<int>Dat;			// 为了好看 没用
		cout << comp(Sym, Dat, input) << endl;	
	}
	return 0;
}
