class Graph{
    private:
        void operator = (const Graph&) {}
        Graph (const Graph&) {}
    public:
        Graph() {}
        virtual ~Graph(){}

        virtual void Init(int n) = 0;
        virtual int n() = 0;
        virtual int e() = 0;

        virtual int first(int v) = 0;
        virtual int next(int v,int w) =0;

        virtual void setEdge(int v1, int v2,int wght) = 0;
        virtual void delEdge(int v1, int v2) = 0;

        virtual bool isEdge(int i,int j) = 0;

        virtual int weight(int v1,int v2) = 0;

        virtual int getMark(int v) = 0;
        virtual void setMark(int v,int val) = 0;
};
