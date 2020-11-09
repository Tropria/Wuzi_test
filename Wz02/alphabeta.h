#ifndef INCLUDE_ALPHA_BETA_H
#define INCLUDE_ALPHA_BETA_H

#include <iostream>
#include <limits.h>

#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b
#define BLACK 2
#define WHITE 1

class TreeNode {
public:
    int board[15][15];
    int x_last;
    int y_last;
    int curColor;
    int x_next;
    int y_next;
    TreeNode() {
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                board[j][i] = 0;
            }
        }
    }
    TreeNode(int bor[15][15], int curC) {
        curColor = curC;
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                board[j][i] = bor[j][i];
            }
        }
    }
    TreeNode(int bor[15][15], int curC, int y, int x) {
        x_last = x;
        y_last = y;
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                board[j][i] = bor[j][i];
            }
        }
        board[y][x] = curC;
        curColor = curC;
    }
    ~TreeNode() {
    }
    void copyBoardFromNode(TreeNode* another) {
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                board[j][i] = another->board[j][i];
            }
        }
    }
    //复制另一个节点
    void copyFromNode(TreeNode* another) {
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                board[j][i] = another->board[j][i];
            }
        }
        x_last = another->x_last;
        y_last = another->y_last;
        curColor = another->curColor;
    }
};


//以该点为目标，向右 右下 下 左下 遍历是否存在5连
int checkIsFive(const int a[15][15], int x, int y);
//以该点为目标，向右 右下 下 左下 遍历是否存在4活
int checkIsFourAlive(const int a[15][15], int x, int y);

//判断(x1,y1) (x2,y2)两点是否在同一直线上
bool isOnSameLine(int x1, int y1, int x2, int y2);


//估分函数 TODO
int evaluation_0(const TreeNode* tn);
//alpha-beta pruning 
//TODO

#define DEPTH 3
int alphabeta(TreeNode* tn, int depth, int a, int b, int curColor);

int main_old();

#endif