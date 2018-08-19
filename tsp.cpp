#include <bits/stdc++.h>
using namespace std;


#define N 1005
#define ll long long
#define INF 1000000000000


int n;
int x[N],y[N];
pair<int,int>coordinates[N];
double dist[N][N];

void show(vector<int>res)
{
    cout << endl;
    for(int p = 0;  p < res.size(); p++){
        cout << res[p] << " ";
    }
    cout<< endl<<endl;
}

double calc(int point1,int point2)
{
    int x1 = coordinates[point1].first;
    int y1 = coordinates[point1].second;

    int x2 = coordinates[point2].first;
    int y2 = coordinates[point2].second;

    double d = sqrt(1.0*(x1-x2)*(x1-x2) + 1.0*(y1-y2)*(y1-y2));
    return d;
}


double distanceCalc(vector<int>curRoute)
{
    double dis = 0.0;
    //cout << curRoute.size() << endl;
    //show(curRoute);
    for(int j = 0; j < curRoute.size() - 1; j++){
        dis += dist[curRoute[j]][curRoute[j+1]];

    }
    //cout << "uu"<< endl;

    return dis;
}




///Construction heuristics

///(A)Nearest Neighbour


vector<int> solve(vector<int>nearestNeighbourTsp,int u,int cnt,bool *vis)
{
    //cout <<"first " << u << endl;
    //show(nearestNeighbourTsp);
    if(cnt == n){

        nearestNeighbourTsp.push_back(1);
        return nearestNeighbourTsp;
    }

    //nearestNeighbourTsp.push_back(u);
    vis[u] = true;

    double mn = INF;
    int nxtVertex = u;

    for(int v = 1;  v <= n; v++){
        if(u != v && vis[v] == false){
            //cout << v << endl;
            if(dist[u][v] < mn ){
                mn = dist[u][v];
                nxtVertex = v;
            }
        }
    }
    nearestNeighbourTsp.push_back(nxtVertex);
    return solve(nearestNeighbourTsp,nxtVertex,cnt+1,vis);

}

vector<int>nearestNeighbourSolve()
{

    vector<int>nearestNeighbourTsp;
    bool vis[n+1];
    for(int i = 1; i <= n; i++) vis[i] = false;
    nearestNeighbourTsp.push_back(1);
    return solve(nearestNeighbourTsp,1,1,vis);
}


///(B)Insertion Heuristic

///(B1)Nearest Insertion



vector<int> nearestInsertionSolve()
{

    bool *vis = new bool[n+1];


    vector<int>subGraph;
    int cntNodes = 0;
    double mn = INF;
    int v = 1;
    cntNodes++;

    ///initialization
    for(int i = 1; i <= n;i++){
        vis[i] = false;
    }

    vis[1] = true;

    if(cntNodes == n){
        subGraph.push_back(1);
        return subGraph;
    }

    for(int j = 2; j <= n; j++){
        if(dist[1][j] < mn){
            mn = dist[1][j];
            v = j;
        }
    }

    subGraph.push_back(1);
    subGraph.push_back(v);
    subGraph.push_back(1);
    vis[v] = true;

    cntNodes++;

    if(cntNodes == n) return subGraph;

    //show(subGraph);

    while(cntNodes < n){
        vector<int>nodeR,nodeJ;
        for(int r = 1; r <= n; r++){
            if(vis[r] == false){
                nodeR.push_back(r);
            }
        }

        for(int j = 1; j <= n; j++){
            if(vis[j] == true){
                nodeJ.push_back(j);
            }
        }

        //cout << "r nodes" << endl;
        //show(nodeR);
        //cout << "j nodes" << endl;
        //show(nodeJ);

        ///finding node r and j

        mn = INF;
        int r = 1,j = 1;

        for(int rr : nodeR){
            for(int jj : nodeJ){
                if(dist[rr][jj] < mn){
                    mn = dist[rr][jj];
                    r = rr;
                    j = jj;
                }
            }
        }

        ///finding arc(i,j)
        mn = INF;
        int i = 1;
        for(int pos = 0; pos < subGraph.size() - 1; pos++){
            if(subGraph[pos] == j){
                if(j == 1){
                    int ii = subGraph[pos+1];
                    if(dist[ii][r] + dist[r][j] - dist[ii][j] < mn){
                        i = ii;
                        mn = dist[ii][r] + dist[r][j] - dist[ii][j];
                    }


                    ii = subGraph[n-1];
                    if(dist[ii][r] + dist[r][j] - dist[ii][j] < mn){
                        i = ii;
                        mn = dist[ii][r] + dist[r][j] - dist[ii][j];
                    }
                }
                else{
                    int ii = subGraph[pos-1];
                    if(dist[ii][r] + dist[r][j] - dist[ii][j] < mn){
                        i = ii;
                        mn = dist[ii][r] + dist[r][j] - dist[ii][j];
                    }

                    ii = subGraph[pos+1];
                    if(dist[ii][r] + dist[r][j] - dist[ii][j] < mn){
                        i = ii;
                        mn = dist[ii][r] + dist[r][j] - dist[ii][j];
                    }
                }
            }
        }

        ///inserting
        vector<int>::iterator it = subGraph.begin();
        for(int pos = 0; pos < subGraph.size() - 1; pos++){
            int ii = subGraph[pos];
            int jj = subGraph[pos+1];
            if((i == ii && j == jj) || (j == ii && i == jj)){
                ///insert
                int ind = pos + 1;
                subGraph.insert(it+ind,r);
                cntNodes++;
                vis[r] = true;
                break;
            }
        }

        //show(subGraph);



    }

    return subGraph;

}

///(B2)Cheapest Insertion

vector<int> cheapestInsertionSolve()
{

    bool *vis = new bool[n+1];


    vector<int>subGraph;
    int cntNodes = 0;
    double mn = INF;
    int v = 1;
    cntNodes++;

    ///initialization
    for(int i = 1; i <= n;i++){
        vis[i] = false;
    }

    vis[1] = true;

    if(cntNodes == n){
        subGraph.push_back(1);
        return subGraph;
    }

    for(int j = 2; j <= n; j++){
        if(dist[1][j] < mn){
            mn = dist[1][j];
            v = j;
        }
    }

    subGraph.push_back(1);
    subGraph.push_back(v);
    subGraph.push_back(1);
    vis[v] = true;

    cntNodes++;

    if(cntNodes == n) return subGraph;

    //show(subGraph);

    while(cntNodes < n){
        //cout << "aa" <<endl;
        vector<int>nodeR;
        for(int r = 1; r <= n; r++){
            if(vis[r] == false){
                nodeR.push_back(r);
            }
        }

        //cout << "r nodes" << endl;
        //show(nodeR);



        ///finding arc(i,r,j)
        mn = INF;
        int i = 1,j = 1,r = 1;
        for(int p = 0; p < nodeR.size();p++){
            int rr = nodeR[p];
            for(int pos = 0; pos < subGraph.size() - 1; pos++){
                int ii = subGraph[pos];
                int jj = subGraph[pos+1];
                if(dist[ii][rr] + dist[rr][jj] - dist[ii][jj] < mn){
                    mn = dist[ii][rr] + dist[rr][jj] - dist[ii][jj];
                    i = ii;
                    j = jj;
                    r = rr;
                }
            }
        }


        ///inserting
        vector<int>::iterator it = subGraph.begin();
        for(int pos = 0; pos < subGraph.size() - 1; pos++){
            int ii = subGraph[pos];
            int jj = subGraph[pos+1];
            if(i == ii && j == jj){
                ///insert
                //cout << "yes"<< endl;
                int ind = pos + 1;
                subGraph.insert(it+ind,r);
                cntNodes++;
                vis[r] = true;
                break;
            }
        }

        //cout << "after insertion" << endl;
        //show(subGraph);



    }

    return subGraph;

}


///(C)Improvement Heuristic
///(C1) 2-opt heuristic

vector<int>twoOptSwap(vector<int>curRoute,int i,int k)
{
    vector<int>newRoute;
    for(int j = 0; j <= i - 1; j++){
        newRoute.push_back(curRoute[j]);
    }

    for(int j = k; j >= i;j--){
        newRoute.push_back(curRoute[j]);
    }

    for(int j = k+1; j <= n; j++){
        newRoute.push_back(curRoute[j]);
    }

    return newRoute;

}



vector<int>twoOptHeuristicSolve()
{

    ///feasible solution
    vector<int>exisitingRoute = nearestNeighbourSolve();

    while(true){
        bool isImproved = false;

        double curDistince = distanceCalc(exisitingRoute);

        for(int i = 1; i < n - 1; i++){
            for(int k = i + 1; k < n; k++){
                vector<int>newRoute = twoOptSwap(exisitingRoute,i,k);
                double newDistance = distanceCalc(newRoute);
                //show(newRoute);
                if(newDistance < curDistince){
                    //cout << "yes"<< endl;
                    exisitingRoute = newRoute;
                    isImproved = true;
                    break;
                }
            }
            if(isImproved){
                break;
            }
        }

        if(isImproved == false){
            break;
        }
    }

    return exisitingRoute;

}



///(C2)3-Opt Heuristic

vector<int> firstRoute(vector<int>curRoute,int i,int j,int k,int l,int m,int o)
{
    vector<int>newRoute;
    /// 1..i-j...k-l...m-o...1
    /// 1..i-k...j-m...l-o...1
    for(int p = 0; p < i; p++){
        newRoute.push_back(curRoute[p]);
    }
    newRoute.push_back(curRoute[i]);
    newRoute.push_back(curRoute[k]);

    for(int p = k - 1; p >= j + 1; p--){
        newRoute.push_back(curRoute[p]);
    }

    newRoute.push_back(curRoute[j]);
    newRoute.push_back(curRoute[m]);

    for(int p = m - 1; p >= l + 1; p--){
        newRoute.push_back(curRoute[p]);
    }

    newRoute.push_back(curRoute[l]);
    newRoute.push_back(curRoute[o]);

    for(int p = o + 1; p <= n;p++){
        newRoute.push_back(curRoute[p]);
    }


    return newRoute;


}


vector<int> secondRoute(vector<int>curRoute,int i,int j,int k,int l,int m,int o)
{
    vector<int>newRoute;
    /// 1..i-j...k-l...m-o...1
    /// 1..i-l...m-j...k-o...1
    for(int p = 0; p < i; p++){
        newRoute.push_back(curRoute[p]);
    }
    newRoute.push_back(curRoute[i]);
    newRoute.push_back(curRoute[l]);

    for(int p = l + 1; p <= m - 1; p++){
        newRoute.push_back(curRoute[p]);
    }

    newRoute.push_back(curRoute[m]);
    newRoute.push_back(curRoute[j]);

    for(int p = j + 1; p <= k - 1; p++){
        newRoute.push_back(curRoute[p]);
    }

    newRoute.push_back(curRoute[k]);
    newRoute.push_back(curRoute[o]);

    for(int p = o + 1; p <= n;p++){
        newRoute.push_back(curRoute[p]);
    }


    return newRoute;


}

vector<int> thirdRoute(vector<int>curRoute,int i,int j,int k,int l,int m,int o)
{
    vector<int>newRoute;
    /// 1..i-j...k-l...m-o...1
    /// 1..i-l...m-k...j-o...1
    for(int p = 0; p < i; p++){
        newRoute.push_back(curRoute[p]);
    }
    newRoute.push_back(curRoute[i]);
    newRoute.push_back(curRoute[l]);

    for(int p = l + 1; p <= m - 1; p++){
        newRoute.push_back(curRoute[p]);
    }

    newRoute.push_back(curRoute[m]);
    newRoute.push_back(curRoute[k]);

    for(int p = k - 1; p >= j + 1; p--){
        newRoute.push_back(curRoute[p]);
    }

    newRoute.push_back(curRoute[j]);
    newRoute.push_back(curRoute[o]);

    for(int p = o + 1; p <= n;p++){
        newRoute.push_back(curRoute[p]);
    }


    return newRoute;


}


vector<int> fourthRoute(vector<int>curRoute,int i,int j,int k,int l,int m,int o)
{
    vector<int>newRoute;
    /// 1..i-j...k-l...m-o...1
    /// 1..i-m...l-j...k-o...1
    for(int p = 0; p < i; p++){
        newRoute.push_back(curRoute[p]);
    }
    newRoute.push_back(curRoute[i]);
    newRoute.push_back(curRoute[m]);

    for(int p = m - 1; p >= l + 1; p--){
        newRoute.push_back(curRoute[p]);
    }

    newRoute.push_back(curRoute[l]);
    newRoute.push_back(curRoute[j]);

    for(int p = j + 1; p <= k - 1; p++){
        newRoute.push_back(curRoute[p]);
    }

    newRoute.push_back(curRoute[k]);
    newRoute.push_back(curRoute[o]);

    for(int p = o + 1; p <= n;p++){
        newRoute.push_back(curRoute[p]);
    }


    return newRoute;


}

vector<int>threeOptHeuristicSolve()
{

    vector<int>existingRoute = nearestNeighbourSolve();


    while(true){
        //cout << "aa"<< endl;
        bool isImproved = false;

        double curDistance = distanceCalc(existingRoute);

        for(int i = 1; i < n-5; i++){
            for(int k = i + 2; k < n-3; k++){
                for(int m = k + 2; m < n - 1; m++){
                    //cout << "haha"<< endl;
                    vector<int>route1 = firstRoute(existingRoute,i,i+1,k,k+1,m,m+1);
                    vector<int>route2 = secondRoute(existingRoute,i,i+1,k,k+1,m,m+1);
                    vector<int>route3 = thirdRoute(existingRoute,i,i+1,k,k+1,m,m+1);
                    vector<int>route4 = fourthRoute(existingRoute,i,i+1,k,k+1,m,m+1);

                    double d1 = distanceCalc(route1);
                    //cout << "d1"<< endl;
                    double d2 = distanceCalc(route2);
                    double d3 = distanceCalc(route3);
                    double d4 = distanceCalc(route4);


                    if(d1 < curDistance){
                        isImproved = true;
                        existingRoute = route1;
                        curDistance = d1;
                    }

                    if(d2 < curDistance){
                        isImproved = true;
                        existingRoute = route2;
                        curDistance = d2;
                    }
                    if(d3 < curDistance){
                        isImproved = true;
                        existingRoute = route3;
                        curDistance = d3;
                    }
                    if(d4 < curDistance){
                        isImproved = true;
                        existingRoute = route4;
                        curDistance = d4;
                    }

                    if(isImproved){
                        break;
                    }
                }
                if(isImproved){
                    break;
                }
            }
            if(isImproved){
                break;
            }
        }

        if(isImproved == false) break;
    }

    return existingRoute;
}


int main()
{
    FILE *input = freopen("1405029_input.txt","r",stdin);
    FILE *output = freopen("1405029_output.txt","w",stdout);

    cin >> n;

    for(int i = 1; i <= n;i++){
        int u,v;
        cin >> u >> v;
        coordinates[i] = {u,v};
    }

    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            dist[i][j] = calc(i,j);
            dist[j][i] = calc(j,i);
        }
    }

    /*cout << endl;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl<< endl;*/

    vector<int>ans1 = nearestNeighbourSolve();
    vector<int>ans2 = nearestInsertionSolve();
    vector<int>ans3 = cheapestInsertionSolve();
    vector<int>ans4 = twoOptHeuristicSolve();
    vector<int>ans5 = threeOptHeuristicSolve();




    cout << "Nearest Neighbour Heuristic TSP :" << endl;
    show(ans1);
    cout << "Total distance : " << distanceCalc(ans1) << endl << endl;

    cout << "Nearest Insertion Heuristic TSP :" << endl;
    show(ans2);
    cout << "Total distance : " << distanceCalc(ans2) << endl << endl;

    cout << "Cheapest Insertion Heuristic TSP :" << endl;
    show(ans3);
    cout << "Total distance : " << distanceCalc(ans3) << endl << endl;

    cout << "2-Opt Heuristic TSP :" << endl;
    show(ans4);
    cout << "Total distance : " << distanceCalc(ans4) << endl << endl;

    cout << "3-Opt Heuristic TSP :" << endl;
    show(ans5);
    cout << "Total distance : " << distanceCalc(ans5) << endl << endl;

    fclose(output);
    fclose(input);



    return 0;
}


/*
15
1 3
6 7
6 8
10 12
15 16
5 9
9 1
3 9
13 18
20 23
11 17
24 11
21 13
25 19
8 23
*/

















