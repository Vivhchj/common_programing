/*
输入 ：
第1行项目个数 n
后n行：n个项目各自需要的时间ti
后面1行 :关联数目m
面m行：每行都是两个数 qi，hi，项目qi完成了之后，项目hi才能进行
*/

//题意：一个项目可能受多个其他项目约束，不受约束的可以并行进行
//思路：先并行进行所有不受约束的项目，待每个项目运行结束的瞬间，移除其所有约束
#include<iostream>
#include<vector>
using namespace std;

//判断proj的所有项目是否全部完成
bool isFinish(vector<vector<int> > &proj){
    for(auto p : proj){
        if(p[0]!=0){
            return false;
        }
    } 
    return true;
}

int main(){
    int n, m;
    cin >> n;
    //两维，分别表示项目运行时间和所受限制数
    vector<vector<int> > proj(n);
    int t;
    for(int i=0; i<n; ++i){
        cin >> t;
        proj[i].push_back(t);
        proj[i].push_back(0);
    }
    cin >> m;
    //存储每个项目所限制的项目列表
    vector<vector<int> > bind(n);
    int pre, aft;
    for(int i = 0; i<m; ++i){
        cin >> pre >> aft;
        bind[pre].push_back(aft);
        ++proj[aft][1];
    }
    //随单位时间进行迭代
    int run_time = 0;
    //temp用于记录每次运行完的项目，等到运行项目时间更新完毕后，用于更新proj[][1]
    vector<int> temp;
    while(!isFinish(proj)){
        //所有正在执行的项目剩余运行时间-1
        for(int i = 0; i<n; ++i){
            if(proj[i][1]==0 && proj[i][0]>0){
                --proj[i][0];
                //如果该项目执行结束，将受限项目计入缓存，待所有执行项目更新结束，更新受限项目的状态
                if(proj[i][0]==0){
                    temp.push_back(i);
                }
            }
        }
        //根据缓存的结束项目更新受限项目的状态
        for(auto temp_p : temp){
            for(auto free_p : bind[temp_p]){
                --proj[free_p][i];
            }
        }
        ++run_time;
    }
    cout << run_time << endl;
    return 0;
}

