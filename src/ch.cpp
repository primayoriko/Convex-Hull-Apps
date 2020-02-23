// g++ ch.cpp -o ch -I/usr/include/python2.7 -lpython2.7

#include <bits/stdc++.h>
#include "mpl/matplotlibcpp.h"
using namespace std;
using namespace std::chrono;

namespace plt = matplotlibcpp;

typedef struct{
    double x;
    double y;
} Point;

bool operator < (const Point &a, const Point &b){
    if(a.x < b.x) return true;
    else if(a.x == b.x && a.y < b.y) return true;
    else return false;
}

void cntABC(double x1, double y1, double x2, double y2, double *a, double *b, double *c){
    *a = y2 - y1;
    *b = x1 - x2;
    *c = x1*y2 - y1*x2;
}

int lineValue(double a, double b, double x, double y, double c){
    double  t = (a*x + b*y - c);
    return ((t > 0)? 1 : ((t < 0)? -1 : 0));
}

bool borderLine(double a, double b, double c, int N, int r, int q, Point p[]){
    int i = 0; int t = -999; bool flg = true;
    do{
        if(i != r && i != q){
            if(t == -999) t = lineValue(a,b, p[i].x, p[i].y, c);
            else{
                if (t != lineValue(a,b, p[i].x, p[i].y, c)) return false;
            }
        }
        i++;
    } while (i < N && flg);
    return true;
}

void traversal(int k, int N, bool vis[], Point pnt[], vector<double> *x, vector<double> *y){
    double a, b, c;
    for(int i=0; i< N ; i++){   
        cntABC(pnt[k].x, pnt[k].y, pnt[i].x, pnt[i].y, &a, &b, &c);
        if(i != k && !vis[i] && borderLine(a, b, c, N, k, i, pnt)){
            if(!vis[k]){
                x->push_back(pnt[k].x); y->push_back(pnt[k].y);
                vis[k] = true; 
            }
            vis[i] = true;
            x->push_back(pnt[i].x); y->push_back(pnt[i].y);
            traversal(i, N, vis, pnt, x, y);
        }
    }
}

void convexHull(int N, bool vis[], Point pnt[], vector<double> *x, vector<double> *y, vector<double> *xn, vector<double> *yn){
    for(int i=0; i<N; i++){
        if(!vis[i]){
            traversal(i, N, vis, pnt, x, y);
        }
    }
    for(int i=0; i<N; i++){
        if(!vis[i]){
            xn->push_back(pnt[i].x); yn->push_back(pnt[i].y);
        }
    }
}

void showRes(vector<double> x, vector<double> y){
    printf("[");
    for(int i=0; i < x.size()-1; i++){
        printf("(%.2f, %.2f)", x.at(i), y.at(i));
        if(i < x.size()- 2) printf(", ");
    }
    printf("]\n");
}

void showImg(string imgName, string title, vector<double> x, vector<double> y, vector<double> xn, vector<double> yn, double pntSize){
    plt::plot(x, y);
    plt::scatter(xn, yn, pntSize);
    plt::title(title);
    plt::save(imgName);
    plt::show();
}

void CHProg(){
    int M;
    printf("Convex Hull Finder\n\nMenu:\n 1. Input Terminal\n 2. Input File (input.txt)\n\n");
    cout<<"Mode Input : ";
    cin>>M; cout<<endl;

    if(M == 2) freopen("input.txt", "r", stdin);
    int N;
    if(M == 1)cout<<"Masukkan banyak titik : ";
    cin>>N; cout<<endl;

    if(N < 2){
        if(M == 1) cout<<"Error! Silahkan masukkan bilangan integer lebih besar dari satu!";
    } 
    else{
        Point points[N];
        for (int i=0;i<N;i++){
            double a,b;
            if(M == 1) cout<<"Masukkan pair titik ke-"<<i+1<<" : ";
            cin>>a>>b;
            Point pnt;
            pnt.x = a;
            pnt.y = b;
            points[i] = pnt;
        }
        if(M == 2) fclose(stdin);

        bool vis[N];
        memset(vis, 0, sizeof(vis));
        vector<double> x; vector<double> y;
        vector<double> xn; vector<double> yn;
        
        clock_t begins = clock();
        convexHull(N, vis, points, &x, &y, &xn, &yn);
        x.push_back(x[0]); y.push_back(y[0]);
        clock_t ends = clock();
        double dur = (double)(ends-begins)/(double)CLOCKS_PER_SEC;

        cout<<"\nTime elapsed: "<< fixed << dur << setprecision(6);
        cout<<" s"<<endl;
        showRes(x, y);
        showImg("CH.png", "Convex Hull Graph", x, y, xn, yn, 3.5);
    }
}

void LGProg(){
    int N;
    cout<<"Masukan banyak titik untuk di generate : ";
    cin>>N; printf("\n");

    srand(time(0));
    set <Point> pnt;
    while(pnt.size() < N){
        int s1 = (rand()%2 == 0)? 1 : -1; int s2 = (rand()%2 == 0)? 1 : -1;
        s1 *= (rand()%20); s2 *= (rand()%20);
        Point p; p.x = (double)s1/2; p.y = (double)s2/2;
        pnt.insert(p);
    }

    int M;
    printf("Pilih mode output:\n\nMenu:\n 1. Terminal\n 2. File (input.txt)\n\n");
    cout<<"Select mode number : ";
    cin>>M; printf("\n");

    if(M == 2) freopen("input.txt", "w", stdout);
    set <Point> :: iterator i;
    if(M == 2) cout<<pnt.size()<<endl;
    for(i = pnt.begin(); i!=pnt.end(); ++i){
        cout<< i->x <<' '<< i->y <<endl;
    }
    if(M == 2){
        fclose(stdout);
        cout<<"Finished!!"<<endl;
    } 
}

int main(){
    int M;
    printf("Welcome!!\nSelect Our Program:\n\nMenu:\n 1. Convex Hull Finder\n 2. N-Point Generator\n\n");
    cout<<"Select mode number: ";
    cin>>M; printf("\n");

    if(M == 1) CHProg();
    else if (M == 2) LGProg();
    else cout<<"Input Invalid!!\n";
}