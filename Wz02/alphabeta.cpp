#include "alphabeta.h"
#include <iostream>
#include <cstdlib>
#include <limits.h>

//�Ըõ�ΪĿ�꣬���� ���� �� ���� �����Ƿ����5��
int checkIsFive(const int a[15][15], int x, int y) {
    int o = a[y][x];//��ǰ����
    //����Ƿ��Ǻ�or��
    if (o != 1 && o != 2) return 0;
    int j = y, i = x;
    //���Ҽ��?
    j = y; i = x + 1;
    for (; i < x + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++i;
    }
    if (i == x + 5) return o;
    //����
    j = y + 1; i = x;
    for (; j < y + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++j;
    }
    if (j == y + 5) return o;
    //�����¼��?
    j = y + 1; i = x + 1;
    for (; i < x + 5 && j < y + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++j; ++i;
    }
    if (i == x + 5) return o;
    //�����¼��?
    j = y + 1; i = x - 1;
    for (; i > x - 5 && j < y + 5 && i >= 0 && j < 15; ) {
        if (a[j][i] != o) break;
        ++j; --i;
    }
    if (j == y + 5) return o;
    return 0;
}
//�Ըõ�ΪĿ�꣬���� ���� �� ���� �����Ƿ����4��
int checkIsFourAlive(const int a[15][15], int x, int y) {
    int m = a[y][x];//��ǰ����
    int temp;
    //����Ƿ��Ǻ�or��,����������������?������Ҫ0��ʼ0������
    if (m == 1 || m == 2) return 0;
    int j = y, i = x;
    //���Ҽ��?
    j = y; i = x + 1;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (i = i + 1; i < x + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++i;
    }
    if (i == x + 5 && i < 15 && a[j][i] == 0) return temp;
    //����
    j = y + 1; i = x;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (j = j + 1; j < y + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++j;
    }
    if (j == y + 5 && j < 15 && a[j][i] == 0) return temp;
    //�����¼��?
    j = y + 1; i = x + 1;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (j = j + 1, i = i + 1; i < x + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++j; ++i;
    }
    if (i == x + 5 && j < 15 && i < 15 && a[j][i] == 0) return temp;
    //�����¼��?
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

//�ж�(x1,y1) (x2,y2)�����Ƿ���ͬһֱ����
bool isOnSameLine(int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) {//��ֱˮƽ����
        return true;
    }
    //б�Խ��߷���
    if ((x1 - x2) == (y1 - y2) || (x1 - x2) == (y2 - y1)) {
        return true;
    }
    return false;
}


//���ֺ��� TODO
int evaluation_0(const TreeNode* tn) {
    int score = 0;
    int curColor = tn->curColor;
    //��tn�������Ϊ���ĵ�9*9����������
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
            //���루y_last, x_last����ֱͬ���ϵ���������Ȩ��
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

                // //���߶�Ϊwhite��������� +1
                // if (tn->board[y][x] == 1 && curColor == 1) { score += 1; continue; }
                // //������Ϊ�ڣ�ԭ��Ϊ��
                // if (tn->board[y][x] == 2 && curColor == 1) { score += 1; continue; }
                // //���߶�Ϊblack���������ںڣ� -1
                // if (tn->board[y][x] == 2 && curColor == 2) { score -= 1; continue; }
                // //������Ϊ�ף�ԭ��Ϊ��
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
        //���游����
        curBoard.copyFromNode(tn);
        int v = INT_MIN;
        bool isStop = false;
        for (int j = 0; j < 15; ++j) {
            for (int i = 0; i < 15; ++i) {
                if (tn->board[j][i] != 0) continue;
                TreeNode* child = new TreeNode(tn->board, WHITE, j, i);
                // v = MAX(v, alphabeta(child, depth+1, a, b, tn->curColor^1));
                int tval = alphabeta(child, depth - 1, a, b, BLACK);//�����Ӻ󣬽�����BLACK�������м�֦
                //if (j == 2 && i == 3) cout << "(2,3)" << tval << endl;
                //if (j == 1 && i == 3) cout << "(1,3)" << tval << endl;
                if (tval > v) {
                    v = tval;
                    curBoard.copyFromNode(child);
                    if (depth == DEPTH) {//�����ǰ���µļ����ڵ㣨�ս���alphabeta��֦��
                        //����tn��x_next��y_next
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
        //�����ӽڵ���������󣬸��¸��ڵ�
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
                    if (depth == DEPTH) {//�����ǰ���µļ����ڵ㣨�ս���alphabeta��֦��
                        //����tn��x_next��y_next
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
