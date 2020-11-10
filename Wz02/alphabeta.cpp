#include "alphabeta.h"
#include <iostream>
#include <cstdlib>
#include <limits.h>

//以该点为目标，向右 右下 下 左下 遍历是否存在5连
int checkIsFive(const int a[15][15], int x, int y) {
    int o = a[y][x];//锟斤拷前锟斤拷锟斤拷
    //锟斤拷锟斤拷欠锟斤拷呛锟給r锟斤拷
    if (o != 1 && o != 2) return 0;
    int j = y, i = x;
    //锟斤拷锟揭硷拷锟?
    j = y; i = x + 1;
    for (; i < x + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++i;
    }
    if (i == x + 5) return o;
    //锟斤拷锟斤拷
    j = y + 1; i = x;
    for (; j < y + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++j;
    }
    if (j == y + 5) return o;
    //锟斤拷锟斤拷锟铰硷拷锟?
    j = y + 1; i = x + 1;
    for (; i < x + 5 && j < y + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++j; ++i;
    }
    if (i == x + 5) return o;
    //锟斤拷锟斤拷锟铰硷拷锟?
    j = y + 1; i = x - 1;
    for (; i > x - 5 && j < y + 5 && i >= 0 && j < 15; ) {
        if (a[j][i] != o) break;
        ++j; --i;
    }
    if (j == y + 5) return o;
    return 0;
}
//以该点为目标，向右 右下 下 左下 遍历是否存在4活
int checkIsFourAlive(const int a[15][15], int x, int y) {
    int m = a[y][x];//锟斤拷前锟斤拷锟斤拷
    int temp;
    //锟斤拷锟斤拷欠锟斤拷呛锟給r锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟轿?锟斤拷锟斤拷锟斤拷要0锟斤拷始0锟斤拷锟斤拷锟斤拷
    if (m == 1 || m == 2) return 0;
    int j = y, i = x;
    //锟斤拷锟揭硷拷锟?
    j = y; i = x + 1;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (i = i + 1; i < x + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++i;
    }
    if (i == x + 5 && i < 15 && a[j][i] == 0) return temp;
    //锟斤拷锟斤拷
    j = y + 1; i = x;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (j = j + 1; j < y + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++j;
    }
    if (j == y + 5 && j < 15 && a[j][i] == 0) return temp;
    //锟斤拷锟斤拷锟铰硷拷锟?
    j = y + 1; i = x + 1;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (j = j + 1, i = i + 1; i < x + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++j; ++i;
    }
    if (i == x + 5 && j < 15 && i < 15 && a[j][i] == 0) return temp;
    //锟斤拷锟斤拷锟铰硷拷锟?
    j = y + 1; i = x - 1;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (j = j + 1, i = i - 1; i > x - 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++j; --i;
    }
    if (j == y + 5 && j < 15 && i >= 0 && a[j][i] == 0) return temp;
    return 0;
}

//判断(x1,y1) (x2,y2)两点是否在同一直线上
bool isOnSameLine(int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) {//垂直水平方向
        return true;
    }
    //斜对角线方向
    if ((x1 - x2) == (y1 - y2) || (x1 - x2) == (y2 - y1)) {
        return true;
    }
    return false;
}


//估分函数 TODO
int evaluation_0(const TreeNode* tn) {
    int score = 0;
    int curColor = tn->curColor;
    //在tn最后落子为中心的9*9方格内评分
    int y_min = MIN(tn->y_last - 4, 0);
    int y_max = MAX(tn->y_last + 4, 14);
    int x_min = MIN(tn->x_last - 4, 0);
    int x_max = MAX(tn->x_last + 4, 14);
    for (int y = y_min; y <= y_max; ++y) {
        for (int x = x_min; x <= x_max; ++x) {
            int winColor = checkIsFive(tn->board, x, y);
            if (winColor == WHITE)
                return 10000;
            if (winColor == BLACK)
                return -10000;
            // int winColor2 = checkIsFourAlive(tn->board, x, y);
            // if (winColor2 == WHITE)
            //     return INT_MAX;
            // if (winColor2 == BLACK)
            //     return INT_MIN;

            // if (tn->board[y][x] == 1) {
            //     ++score;
            // }
            // if (tn->board[y][x] == 2) {
            //     --score;
            // }
            //对与（y_last, x_last）相同直线上的棋子增加权重
            if (tn->board[y][x] != 0 && isOnSameLine(tn->x_last, tn->y_last, x, y)) {
                if (curColor == 1) { 
                    score += 1;
                    /*score += 15-abs(x - tn->x_last); 
                    score += 15-abs(y - tn->y_last);*/
                    continue; 
                }
                if (curColor == 2) { 
                    score -= 1;
                    /*score -= 15-abs(x - tn->x_last);
                    score -= 15-abs(y - tn->y_last);*/
                    continue; 
                }

                // //两者都为white，则倾向白 +1
                // if (tn->board[y][x] == 1 && curColor == 1) { score += 1; continue; }
                // //遍历到为黑，原点为白
                // if (tn->board[y][x] == 2 && curColor == 1) { score += 1; continue; }
                // //两者都为black，则倾向于黑， -1
                // if (tn->board[y][x] == 2 && curColor == 2) { score -= 1; continue; }
                // //遍历到为白，原点为黑
                // if (tn->board[y][x] == 1 && curColor == 2) { score -= 1; continue; }
            }
        }
    }

    return score;
}
//alpha-beta pruning 
//TODO

int alphabeta(TreeNode* tn, int depth, int a, int b, int curColor) {

    if (depth == 0) { //or terminated point
        return evaluation_0(tn);
    }
    TreeNode curBoard;
    if (curColor == WHITE) {//maxPlayer
        //保存父棋盘
        curBoard.copyFromNode(tn);
        int v = INT_MIN;
        bool isStop = false;
        for (int j = 0; j < 15; ++j) {
            for (int i = 0; i < 15; ++i) {
                if (tn->board[j][i] != 0) continue;
                TreeNode* child = new TreeNode(tn->board, WHITE, j, i);
                // v = MAX(v, alphabeta(child, depth+1, a, b, tn->curColor^1));
                int tval = alphabeta(child, depth - 1, a, b, BLACK);//落完子后，交换至BLACK继续进行剪枝
                //if (j == 2 && i == 3) cout << "(2,3)" << tval << endl;
                //if (j == 1 && i == 3) cout << "(1,3)" << tval << endl;
                if (tval > v) {
                    v = tval;
                    curBoard.copyFromNode(child);
                    if (depth == DEPTH) {//如果当前更新的即父节点（刚进入alphabeta剪枝）
                        //更新tn的x_next和y_next
                        tn->x_next = i;
                        tn->y_next = j;
                    }
                }
                delete child;
                a = MAX(a, v);
                if (a >= b) {
                    isStop = true;
                    break;
                }
            }
            if (isStop) break;
        }
        //所有子节点遍历结束后，更新父节点
        tn->copyFromNode(&curBoard);
        // cout<<"curDepth "<<depth<<" Board[1][4] "<<tn->board[1][4]<<endl;
        return v;
    }
    else {
        curBoard.copyFromNode(tn);
        int v = INT_MAX;
        bool isStop = false;
        for (int j = 0; j < 15; ++j) {
            for (int i = 0; i < 15; ++i) {
                if (tn->board[j][i] != 0) continue;
                TreeNode* child = new TreeNode(tn->board, BLACK, j, i);
                // v = MIN(v, alphabeta(child, depth+1, a, b, tn->curColor^1));
                int tval = alphabeta(child, depth - 1, a, b, WHITE);
                if (tval < v) {
                    v = tval;
                    curBoard.copyFromNode(child);
                    if (depth == DEPTH) {//如果当前更新的即父节点（刚进入alphabeta剪枝）
                        //更新tn的x_next和y_next
                        tn->x_next = i;
                        tn->y_next = j;
                    }
                }
                delete child;
                b = MIN(b, v);
                if (a >= b) {
                    isStop = true;
                    break;
                }
            }
            if (isStop) break;
        }
        tn->copyFromNode(&curBoard);
        // cout<<"curDepth "<<depth<<" Board[1][4] "<<tn->board[1][4]<<endl;
        return v;
    }
}

int main_old() {
    int board[15][15] = {
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,2,0,0, 2,2,0,0,0, 0,0,0,0,0},
        {0,0,0,0,1, 1,0,0,0,0, 0,0,0,0,0},
        {0,0,1,1,2, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},

        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},

        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
    };

    TreeNode* root = new TreeNode(board, BLACK, 1, 4);
    int res = alphabeta(root, 2, INT_MIN, INT_MAX, WHITE);

    /* for (int j = 0; j < 15; ++j) {
         if (j % 5 == 0) cout << endl;

         for (int i = 0; i < 15; ++i) {
             if (i % 5 == 0) cout << " ";
             cout << root->board[j][i] << " ";
         }

         cout << endl;
     }*/

     //cout<<"---------------------"<<res<<"---------------------"<<endl;
    return 0;
}
