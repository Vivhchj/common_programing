/*
连通区域（Connected Component）一般是指图像中具有相同像素值且位置相邻的像素点组成的图像区域。
每个像素点有8个邻接点，包括了上下左右和对角线的像素点。如果点a与b邻接，称之为a与b连通。如果域A与B连通，B与C连通，则A与C也连通。
试找出一个二值矩阵的所有连通域（8邻接），并给出每个连通域的面积（邻接点的个数）和重心。
*/

#include<iostream>
#include<iomanip>
#include<vector>
#include<tuple>
 
using namespace std;
 
//查找每个点的连通域
void hasConGraph(int row, int col, int rows, int cols, vector<vector<int> > &map, vector<pair<int, int>> &vp){
    if(map[row][col]!=1){
        return ;
    }
    //遍历到的邻接点赋值为2
    map[row][col] = 2;
    //将邻接点坐标加入vp
    vp.push_back(make_pair(row, col));
    //8个邻接方向
    vector<vector<int> > d{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    for(int i = 0; i<d.size(); ++i){
        //对未越界的坐标进行判断
        if(row+d[i][0]>=0 && row+d[i][0]<rows && col+d[i][1]>=0 && col+d[i][1]<cols){
            hasConGraph(row+d[i][0], col+d[i][1], rows, cols, map, vp);
        }
    }
    return ;
}

//计算每个连通域的元素个数、重心坐标
tuple<int, float, float> calCore(vector<pair<int , int>> &vp){
    if(vp.empty()){
        return make_tuple(-1, -1., -1.);
    }
    float row_sum = 0., col_sum = 0.;
    for(auto p : vp){
        row_sum += p.first;
        col_sum += p.second;
    }
    return make_tuple(vp.size(), col_sum/vp.size(), row_sum/vp.size());
}
 
int main(){
    int rows, cols, temp;
    cin >> rows >> cols;
    vector<vector<int> > map;
    vector<int> line;
    //输入
    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < cols; ++col){
            cin >> temp;
            line.push_back(temp);
        }
        map.push_back(line);
        line.clear();
    }
    //用pair<>存储坐标，vector<pair>存储每个连通域的所有坐标
    vector<pair<int , int >> vp;
    //用tuple<>存储每个连通域的元素个数int，重心纵横坐标float,float，vector<tuple>存储整个要输出的结果
    vector<tuple<int , float , float>> cores;
    //遍历矩阵map&回溯法寻找连通域
    for(int row = 0; row<rows; ++row){
        for(int col = 0; col<cols; ++col){
            if(map[row][col]==1){
                //从[row][col]寻找连通域
                hasConGraph(row, col, rows, cols, map, vp);
                //计算每个连通域vp需要输出的信息
                cores.push_back(calCore(vp));
                vp.clear();
            }
        }
    }
    //输出
    cout << cores.size() << endl;
    //tuple类型数据的输出，get<i>(tuplename)
    for(auto c : cores){
        cout << get<0>(c) << ' ' << fixed << setprecision(2) << get<1>(c) << ' ' << get<2>(c) << endl;
    }
    return 0;
}
