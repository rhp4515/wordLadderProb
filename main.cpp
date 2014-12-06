//
//  main.cpp
//  wordLadder
//
//  Created by hraman on 12/6/14.
//  Copyright (c) 2014 hraman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

class Vertex;

class Edge
{
private:
    Vertex* origin;
    Vertex* destination;
public:
    Edge(Vertex *org, Vertex *dest)
    {
        origin = org;
        destination = dest;
    }
    
    Vertex* getOrigin() {return origin;}
    Vertex* getDestination() {return destination;}
};


class Vertex
{
private:
    string name;
    vector<Edge> edges;
    bool visited = false;
public:
    Vertex(string id)
    {
        name = id;
    }
    
    void addEdge(Vertex *v)
    {
        Edge newEdge(this, v);
        edges.push_back(newEdge);
    }
    
    void setVisited(bool value = false){
        visited = value;
    }
    
    bool isVisited(){
        return visited;
    }
    
    void printEdges()
    {
        cout << name << ":" << endl;
        for (int i = 0; i < edges.size(); i++)
        {
            Edge e = edges[i];
            cout << e.getDestination()->getName() << "\t";
        }
        cout << endl;
    }
    
    string getName() {return name;}
    vector<Edge> getEdges() {return edges;}
};


class Graph
{
private:
    vector<Vertex*> vertices;

public:
    Graph() {}
    
    void insert(Vertex *v)
    {
        vertices.push_back(v);
    }
    
    void printGraph()
    {
        for (int i = 0; i < vertices.size(); i++)
            vertices[i]->printEdges();
    }
    
    Vertex getVertex(string str){
        Vertex *tV = nullptr;
        for (int i = 0; i < vertices.size(); i++){
            if(!str.compare(vertices[i]->getName())){
                tV = vertices[i];
            }
        }
        return *tV;
    }
    
    int bfs(string src, string dest){
        list<Vertex> queue;
        int count = 0;
        
        Vertex sV = getVertex(src);
        Vertex dV = getVertex(dest);
        
        sV.setVisited(true);
        
        queue.push_back(sV);
        
        vector<Edge>::iterator it;
        vector<Edge> adjVertices;
        
        while(!queue.empty()){
            sV = queue.front();
            
            cout << count<< " "<<sV.getName() << " \n";
            if(sV.getName() == dV.getName()){
                return count;
            }
            count++;
            queue.pop_front();
            adjVertices = sV.getEdges();
            for(vector<Edge>::size_type i = 0; i < adjVertices.size(); i++){
                if(!adjVertices[i].getDestination()->isVisited()){
                    adjVertices[i].getDestination()->setVisited(true);
                    queue.push_back(*adjVertices[i].getDestination());
                }
            }
            
        }
        return count;
    }
};

bool compareWords(string w1, string w2){
    int len = (int)w1.length();
    int temp = 0;
    for(int x = 0; x < len; x++){
        if(w1[x] == w2[x]){
            temp++;
        }
    }
    if(temp == len-1){
        return true;
    }
    return false;
}

vector<Vertex> initVertices(vector<string> words){
    vector<Vertex> Vs;
    int len = (int) words.size();
    for (int t = 0; t < len; t++){
        Vertex *x = new Vertex(words[t]);
        Vs.push_back(*x);
    }
    return Vs;
}

void createGraph(vector<string> words, Graph *wGraph){
    string w1, w2;
    vector<Vertex> V = initVertices(words);
    
    for(vector<Vertex>::size_type i = 0; i != V.size(); i++){
        w1 = V[i].getName();
        for(vector<Vertex>::size_type j = 0; j != V.size(); j++){
            w2 = V[j].getName();
            if(compareWords(w1,w2)){
                //cout << w1 << "\t" << w2 <<endl;
                Vertex *vp = &V[j];
                V[i].addEdge(vp);
            }
        }
        wGraph->insert(&V[i]);
    }
    //wGraph->printGraph();
    cout<<"Num Steps  "<<wGraph->bfs("bunter","custer");
    return ;
}

bool checkInput(vector<string> words, string input){
    bool present = false;
    if(input == "exit"){
        exit(0);
    }
    for(int z = 0; z < words.size(); z++){
        if(!words[z].compare(input)){
            present = true;
        }
    }
    if(!present){
        cout<< "\n****Please provide a word from the given list****\n";
    }
    return present;
}

int main() {
    string line;
    ifstream myfile;
    vector<string> words;
    string src, dest;
    Graph *mGraph = new Graph;
    int numSteps;
    myfile.open("/Users/hraman/Documents/wordLadder/wordLadder/wl.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            words.push_back(line);
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open the file";
    }
    
    createGraph(words, mGraph);
    /*while(true){
        do{
            cout<<"\nEnter the start word: ";
            cin>>src;
        }while(!checkInput(words,src));
        
        do{
            cout<<"\nEnter the end word: ";
            cin>>dest;
        }while(!checkInput(words,dest));
        
        numSteps = mGraph.bfs(src,dest);
        
        cout<< "\nNum Steps:"<<numSteps;
        if(numSteps == src.length()){
            cout<<"\n----Possible----\n";
        }
        else{
            cout<<"\n----Not Possible----\n";
        }
        
    }*/
    //mGraph->printGraph();
    //numSteps = mGraph->bfs("bunter","custer");
    //cout<< "\nNum Steps:"<<numSteps;
        
    return 0;
}
