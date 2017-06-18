class UF {
public:
    int *id, *sz;
    UF(int n) {
        id = new int[n];
        sz = new int[n];

        for (int i = 0; i < n; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    int root(int i) {
        while (i != id[i]) {
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

    bool find(int p, int q) {
        return root(p) == root(q);
    }

    void unite(int p, int q) {
        int i = root(p);
        int j = root(q);
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        }
        else {
            id[j] = i;
            sz[i] += sz[j];
        }
    }

    ~UF() {
        delete [] id, sz;
    }

};
