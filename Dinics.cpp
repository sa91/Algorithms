// INPUT:
//- graph, constructed using AddEdge()
//- source and sink
// OUTPUT:
//- maximum flow value
//- To obtain actual flow values,look at edges with capacity>0
//   (zero capacity edges are residual edges).
struct Edge {
  int from,to,cap,flow,index;
  Edge(int from,int to,int cap,int flow,int index):
    from(from),to(to),cap(cap),flow(flow),index(index){}
  LL rcap(){return cap-flow;}
};
struct Dinic{
  int N;
  vector<vector<Edge>>G;
  vector<vector<Edge*>>Lf;
  vector<int>layer,Q;
  Dinic(int N):N(N),G(N),Q(N){}
  void AddEdge(int from,int to,int cap){
    if(from==to)return;
    G[from].PB(Edge(from,to,cap,0,G[to].size()));
    G[to].PB(Edge(to,from,0,0,G[from].size()-1));
  }
  LL BlockingFlow(int s,int t){
    layer.clear();layer.resize(N,-1);layer[s]=0;
    Lf.clear();Lf.resize(N);int head=0,tail=0;Q[tail++]=s;
    while(head<tail){
      int x=Q[head++];
      for(int i=0;i<G[x].size();i++){
        Edge &e=G[x][i];if(e.rcap()<=0)continue;
        if(layer[e.to]==-1)
          layer[e.to]=layer[e.from]+1,Q[tail++]=e.to;
        if(layer[e.to]>layer[e.from])
          Lf[e.from].push_back(&e);
      }
    }
    if(layer[t]==-1)return 0;
    LL totflow = 0;vector<Edge *> P;
    while(!Lf[s].empty()){
      int curr=P.empty()?s:P.back()->to;
      if(curr==t){ // Augment
        LL amt=P.front()->rcap();
        for(int i=0;i<P.size();++i)
          amt = min(amt, P[i]->rcap());
        totflow += amt;
        for (int i=P.size()-1;i>=0;--i){
          P[i]->flow+=amt;
          G[P[i]->to][P[i]->index].flow-=amt;
          if(P[i]->rcap()<=0)
            Lf[P[i]->from].pop_back(),P.resize(i);
        }
      }else if(Lf[curr].empty()){// Retreat
        P.pop_back();
        for(int i=0;i<N;++i)
          for(int j=0;j<Lf[i].size();++j)
            if(Lf[i][j]->to==curr)
              Lf[i].erase(Lf[i].begin() + j);
      }else P.push_back(Lf[curr].back());
    }return totflow;
  }
  LL GetMaxFlow(int s,int t){
    LL ans=0;
    while(LL flow=BlockingFlow(s, t))ans+=flow;
    return ans;
  }
};
