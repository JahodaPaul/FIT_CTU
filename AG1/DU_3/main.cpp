#include <iostream>

#define ll long long int

using namespace std;

struct PathInGraph{
    void init(int to,ll cost, int _index){
        first = to;
        second = cost;
        index = _index;
    }
    int first; //to
    ll second; //lenght
    int index; //index
};

struct arrayOfPathInGraph{
    PathInGraph * arr;
    int limit;
    int current;
    void Init(){
        arr = NULL;
        limit = 2;
        current = 0;
        arr = (PathInGraph*)realloc(arr,sizeof(PathInGraph) * limit);
    }
    void push_back(PathInGraph p){
        if(current == limit){
            limit *= 2;
            arr = (PathInGraph*)realloc(arr,sizeof(PathInGraph) * limit);
        }
        arr[current] = p;
        current++;
    }
};

struct arrayOfInts{
    int * arr;
    int limit;
    int current;
    void Init(){
        arr = NULL;
        limit = 2;
        current = 0;
        arr = (int*)realloc(arr,sizeof(int) * limit);
    }
    void push_back(int p){
        if(current == limit){
            limit *= 2;
            arr = (int*)realloc(arr,sizeof(int) * limit);
        }
        arr[current] = p;
        current++;
    }
};

struct Path{
    void init(int to,int from, int _index){
        first = to;
        second = from;
        index = _index;
    }
    int first;//to
    int second;//from
    int index;//index
};

struct structForSpanningTreeStruct{
    Path * arr;
    int limit;
    int current;
    void Init(){
        arr = NULL;
        limit = 2;
        current = 0;
        arr = (Path*)realloc(arr,sizeof(Path) * limit);
    }
    void push_back(Path p){
        if(current == limit){
            limit *= 2;
            arr = (Path*)realloc(arr,sizeof(Path) * limit);
        }
        arr[current] = p;
        current++;
    }
};

struct pairForHeap{
    ll first;
    Path second;
    void make_pair(ll f,Path s){
        first = f;
        second = s;
    }
};

// min heap
struct Heap{
    pairForHeap * arr;
    int limit;
    int current;
    void Init(){
        arr = NULL;
        limit = 2;
        current = 0;
        arr = (pairForHeap*)realloc(arr,sizeof(pairForHeap) * limit);
    }
    pairForHeap top(){
        return arr[0];
    }
    void pop(){
        current--;
        if(current == 0){
            return;
        }
        pairForHeap tmp = arr[0];
        arr[0] = arr[current];
        arr[current] = tmp;

        int curr = 0;
        int lastIndex = current - 1;
        //bubble down
        while(true){
            int future = (curr+1)*2;
            int change;
            if(lastIndex<future){
                if(lastIndex>=future-1){
                    change = future-1;
                }
                else{
                    break;
                }
            }
            else{
                if(arr[future].first < arr[future-1].first){
                    change = future;
                }
                else{
                    change = future-1;
                }
            }
            if(arr[change].first < arr[curr].first){
                pairForHeap tmp2 = arr[change];
                arr[change] = arr[curr];
                arr[curr] = tmp2;
                curr = change;
            }
            else{
                break;
            }
        }
    }
    void push(pairForHeap p){
        if(current == limit){
            limit *= 2;
            arr = (pairForHeap*)realloc(arr,sizeof(pairForHeap) * limit);
        }
        arr[current] = p;
        current++;
        int parent = current - 1;
        int curr = parent;
        if(curr == 0){
            return;
        }
        //bubble upwards
        parent = ((curr+1)/2) - 1;
        while(arr[parent].first > arr[curr].first){
            pairForHeap tmp = arr[parent];
            arr[parent] = arr[curr];
            arr[curr] = tmp;
            curr = parent;
            if(curr == 0){
                break;
            }
            parent = ((curr+1)/2) - 1;
        }
    }
    bool empty(){
        if(!current){
            return true;
        }
        return false;
    }
};

int n,nOfPath;
int visited[100002];
//to, lenght
arrayOfPathInGraph graph[100002];

ll a[100002][2];

arrayOfInts g[100002];

structForSpanningTreeStruct SpanningTree;

ll f(int idx, int from, bool put){
	if(a[idx][put]==-1){
		int sum_ = 0;
		if(put){
            for(int j=0;j<g[idx].current;j++){
                auto i_ = g[idx].arr[j];
				if(i_ != from) {
                    sum_ += min(f(i_, idx, 1), f(i_, idx, 0));
                }
			}
		} else {
            for(int j=0;j<g[idx].current;j++){
                auto i_ = g[idx].arr[j];
				if(i_!=from){
                    ll k = f(i_,idx, 1);
				    sum_ += k;
				}
			}
		}
		a[idx][put] = sum_ + put;
	}
	return a[idx][put];
}

int f2(int idx, int from,int put){
    if(a[idx][put]!=-1){
        if(put){
            cout << idx << " ";
            for(int j=0;j<g[idx].current;j++){
                auto i_ = g[idx].arr[j];
                if(i_ != from) {
                    if(a[i_][0] <= a[i_][1]){
                        f2(i_,idx,0);
                    }
                    else{
                        f2(i_, idx, 1);
                    }
                }
            }
        } else {
            for(int j=0;j<g[idx].current;j++){
                auto i_ = g[idx].arr[j];
                if(i_!=from){
                    f2(i_,idx, 1);
                }
            }
        }
    }
    return 0;
}

int main() {
	ios::sync_with_stdio(0);
    SpanningTree.Init();
	while(cin>>n)
	{
        cin>>nOfPath;
        if(n==1){
            cout << "0 " << "1" << endl;
            cout << endl;
            cout << endl;
            return 0;
        }
		for(int i=0;i<=n;i++){
			graph[i].Init();
            g[i].Init();
		}
        int from,to;
        ll cost;
		for(int i=0;i<nOfPath;i++)
		{
			cin>>from>>to>>cost;
            PathInGraph p1;p1.init(to,cost,i);
            PathInGraph p2;p2.init(from,cost,i);
            graph[from].push_back(p1);
            graph[to].push_back(p2);
		}

        Heap q;q.Init();
        Path p;p.init(0,0,-1);
        pairForHeap pairForHeap1;pairForHeap1.make_pair(0,p);
		q.push(pairForHeap1);
        ll result = 0;


		while(!q.empty())
		{
			pairForHeap top = q.top();
			q.pop();
			if(!visited[top.second.first])
			{
				if(top.second.second != 0 || top.second.first != 0)
				{
                    Path p;p.init(top.second.second,top.second.first,top.second.index);
                    SpanningTree.push_back(p);
                    result += top.first;
				}

				for(int i=0;i< graph[top.second.first].current; i++)
				{
					if(!visited[graph[top.second.first].arr[i].first])
					{
                        Path path;path.init(graph[top.second.first].arr[i].first,top.second.first,graph[top.second.first].arr[i].index);
                        pairForHeap pairForHeap2;pairForHeap2.make_pair(graph[top.second.first].arr[i].second,path);
                        q.push(pairForHeap2);
					}
				}
				visited[top.second.first] = 1;
			}
		}
        for(int j=0;j<SpanningTree.current;j++){
            auto i_ = SpanningTree.arr[j];
			g[i_.first].push_back(i_.second);
			g[i_.second].push_back(i_.first);
		}

        for(int i=0;i<100002;i++){
            a[i][0] = -1;
            a[i][1] = -1;
        }
//		memset(a,-1,sizeof(a));

        ll f0 = f(0,-1,0);
        ll f1 = f(0,-1,1);
		cout << result << " " << min(f0,f1) << endl;
        for(int i=0;i<SpanningTree.current;i++){
            cout << SpanningTree.arr[i].index << " ";
        }
        cout << endl;

        if(f0<f1){
            f2(0,-1,0);
        }
        else{
            f2(0,-1,1);
        }
        cout << endl;
	}

	return 0;
}