#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

//void addedge(vector<int> adj[], int u, in v)


struct vert;

struct edge;

struct edge{
    int cost;
    string dest;
    vert *linked;
};

struct vert{
    string hole;
    bool hasRabbit;
    vector <edge> adj;
};


class graph{
    
private:
    
    vector <vert> Verticies;
    vector <string> lines;
    vector <edge*> housekeep;
    void getData(string file){
        lines.clear();
        string line;
        ifstream gfile;
        gfile.open(file);
        if (gfile.is_open()){
            while (getline(gfile, line))
            {
                lines.push_back(line);
            }
            gfile.close();
        }
    }
    
    void addvertex(string line){
        stringstream ss(line);
        vector <string> temp;
        while (ss.good()){
            string substr;
            getline(ss, substr, ',');
            temp.push_back(substr);
        }
        vert v;
        v.hole = temp[0];
        v.hasRabbit = stoi(temp[1]);
        Verticies.push_back(v);
    }
    
    void stitchgraph(string line){
        stringstream ss(line);
        vector <string> temp;
        int current;
        edge *node = new edge;
        while (ss.good()){
            string substr;
            getline(ss, substr, ',');
            temp.push_back(substr);
        }
        for(int i =0; i < Verticies.size(); i++){
            if (Verticies[i].hole == temp[0]){
                current = i;
            }
            if (Verticies[i].hole == temp[1]){
                node->linked = &Verticies[i];
                node->dest = temp[1];
            }
        }
        node->cost = stoi(temp[2]);
        housekeep.push_back(node);
    
        Verticies[current].adj.push_back(*node);
    }
    
    
public:
    
    graph(){
        
    }
    
    ~graph(){
        for (int i = 0; i < housekeep.size(); i++){
            housekeep[i] = nullptr;
            delete housekeep[i];
        }
    }
    
    vector <edge> head;
    void buildgraph(){
        getData("graph.txt");
        for(int i =0; i < lines.size(); i++){
            addvertex(lines[i]);}
        getData("cost.txt");
        for(int i =0; i < lines.size(); i++){
            stitchgraph(lines[i]);}
        
        
        head = Verticies[0].adj;
    }
};

int main()
{
    //There are 9 holes, A-H;
    //Each hole has a name which is stored in string hole.
    //Each hole has a boolian that telles if there is a rabbit stored in bool hasRabbit
    //Each hole has a vector of adjacent edges.
    //Each edge has a cost that is stored in int cost. Each edge will have a linked pointer to the connecting hole stored in *linked
    //Edges are one way entities but the graph is bidirectional.
    //To make things simpler what hole a particular edge leads to is stored in string dest.
    //find rabbit. keep track of your path. Keep track of your path costs.
    //You may use any library.
    
    graph g;
    
    g.buildgraph();
    
    cout << "current hole: " << g.head[0].linked->adj[0].linked->hole << "; next hole cost: " << g.head[0].cost <<"; next hole name: " << g.head[0].dest << endl;
    
    return 0;
}
