vector<int> adj[N][2];

char vis[N][2];

void dfs(int u, int id, vector<int> &order){
    vis[u][id] = 1;
    for(auto i: adj[u][id]){
        if(!vis[i][id]) dfs(i,id, order);
    }
    order.pb(u);
}


void test(){
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a][0].pb(b);
        adj[b][1].pb(a);
    }

    vector<int> order;
    for(int i = 1; i <= n; i++) if(!vis[i][0]) dfs(i,0,order);
    reverse(all(order));

    vector<int> color(n + 1, -1);

    vector<vector<int>> comps;
    int col = 1;
    for(auto i: order){
        if(!vis[i][1]){
            vector<int> comp;
            dfs(i,1,comp);

            comps.pb(comp); // todos os caras dessa componente são fortemente conectados.
            // int pai = *min_element(all(comp));
            for(auto j: comp) color[j] = col;
            col++;
        }
    }

    vector<vector<int>> comprimido(comps.size() + 1);

    for(int i = 1; i <= n; i++){
        for(auto j: adj[i][1]){
            if(color[i] != color[j]) comprimido[color[i]].pb(color[j]); // add arrestas de cada componente pra cada componente, a quantidade de arrestas não precisa ser unica, mas nunca há ciclos.
        }
    }
    cout << col - 1 << '\n';
    for(int i = 1; i <= n; i++) cout << color[i] << ' ';
    cout << '\n';

}
