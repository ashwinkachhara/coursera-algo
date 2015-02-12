#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <ctime>
using namespace std;

void printGraph(vector<vector<int>> &graph, vector<bool> merged){
	cout << "Graph:" << endl;
	for (int i=1; i< graph.size(); i++){
		if (!merged[i]){
			cout << i << " edges:";
			for (auto it = graph[i].begin(); it!=graph[i].end(); it++)
				cout << " " << *it;
			 cout << endl;
		}
			
	}
}

void getGraph(string filename, vector<vector<int>> &graph){
	ifstream myfile (filename);

	string line;

	if (myfile.is_open()){
		int i = 1;
		while (getline(myfile, line)){
			//cout << "line " << i<< endl;
			int j = 0;
			//cout << line[j] << endl;
			while(!isspace(line[j])){
				//cout << j << endl;
				j++;

			}

			j++;
			//cout << j << endl;
			for (; j < line.length();){
				string substr("");
				//cout << substr << endl;
				while((!isspace(line[j])) && j < line.size()){
					//cout << "j " << j << endl;
					substr+=line[j];
					j++;

				}
				
				//cout << "j " << j <<" here " <<  substr << "r" << substr.empty()<< endl;
				if (!substr.empty()){
					
					graph[i].push_back(stoi(substr));
					
				}
				
				if (j < line.size()) j++;
				
			}
			//cout << "here2" << endl;
			//if (i == 199) break; 
			i++;
			//cout << "here3 " << i << endl;
		}
	}
	
	myfile.close();
}

void graphContract(vector<vector<int>> &graph, vector<bool> &merged, int vert1, int vert2){
	auto edgelist1 = graph[vert1];
	auto edgelist2 = graph[vert2];
	
	sort(edgelist1.begin(), edgelist1.end());
	sort(edgelist2.begin(), edgelist2.end());
	//~ 
	//~ cout << "edgelist1";
	//~ for (auto it = edgelist1.begin(); it!=edgelist1.end(); it++){
		//~ cout << " " << *it;
	//~ }
	//~ cout << endl;
	//~ cout << "edgelist2";
	//~ for (auto it = edgelist2.begin(); it!=edgelist2.end(); it++){
		//~ cout << " " << *it;
	//~ }
	//~ cout << endl;
	
	int vert = (vert1 < vert2)? vert1: vert2;
	
	vector<int> v (edgelist1.size()+edgelist2.size());
	
	auto it1 = merge(edgelist1.begin(), edgelist1.end(), edgelist2.begin(), edgelist2.end(), v.begin());
	
	v.resize(it1 - v.begin());
	//~ cout << "mergedV " <<vert1 << " ";
	//~ for (auto it = v.begin(); it!=v.end(); it++){
		//~ cout << " " << *it;
	//~ }
	//~ cout << endl;
	
	if (vert1 > vert2){
		int temp = vert2;
		vert2 = vert1;
		vert1 = temp;
	}
		
	graph[vert1] = v;
	//graph.clear(graph.begin()+vert2);
	merged[vert2] = true;
	graph[vert1].erase(remove(graph[vert1].begin(), graph[vert1].end(), vert1),graph[vert1].end());
	graph[vert1].erase(remove(graph[vert1].begin(), graph[vert1].end(), vert2),graph[vert1].end());
	for (int i=1; i<graph.size(); i++){
		if (!merged[i] && i!=vert1){
			//cout << "checking " << i <<" vert1 " <<vert1<< endl;
			//graph[i].erase(remove(graph[i].begin(), graph[i].end(), vert1), graph[i].end());
			vector<int>::iterator vert2it;
			vert2it = find(graph[i].begin(), graph[i].end(), vert2);
			//cout << "found " << *vert2it << " at index " << vert2it-graph[i].begin()<< endl;
			while (vert2it != graph[i].end()){
				//cout << "here" << endl;
				*vert2it = vert1;
				
				vert2it = find(vert2it, graph[i].end(), vert2);
				
			}
			//cout << *vert2it << endl;
		

		}
	}
	
	//~ cout << "merged " <<vert1 << " ";
	//~ for (auto it = graph[vert1].begin(); it!=graph[vert1].end(); it++){
		//~ cout << " " << *it;
	//~ }
	//~ cout << endl;
	
	
	
	
}

int findMinCut(vector<vector<int>> &graph){
	auto graphCopy = graph;
	
	int N = (graph.size()-1);//105437;
	N = N*N*N*log(N);
	N = N+1;
	int mincut = N;
	while (N>0){
		
		vector<bool> merged(graph.size(), false);
		graphCopy = graph;
		srand(time(NULL));
		N--;
		int graphSize = graph.size()-1;
		while (graphSize > 2){
			int v1 = rand()%(graphCopy.size()-1)+1;
			while(merged[v1]){
				v1 = rand()%(graphCopy.size()-1)+1;
			}
			int v2 = graphCopy[v1][rand()%(graphCopy[v1].size())];
			while(merged[v2]){
				v2 = graphCopy[v1][rand()%(graphCopy[v1].size())];
			}
			//cout << " vertices " << v1 << " " << v2 << endl;
			graphContract(graphCopy, merged, v1, v2);
			graphSize--;
			//printGraph(graphCopy, merged);
			//cout << "graphsize " <<graphSize << endl; 
		}
		int cut;
		for (int ind =1; ind<graphCopy.size(); ind++){
			if (!merged[ind]){
				cut = graphCopy[ind].size();
				//cout << "thisCut "<< cut << endl;
				break;
			}
		}
		
		mincut = (cut < mincut) ? cut: mincut;
		
		if (N%10==0) cout << "N " << N << " mincut: " << mincut << endl;
	}
	
	return mincut;

}

int main(){
	vector<vector<int>> graph(8+1);
	vector<bool> mergedT(8+1, false);
	getGraph("kargertest.txt", graph);
	graph.shrink_to_fit();
	//cout << graph[199].back() << endl;
	//graphContract(graph, 1, 2);
	//printGraph(graph, mergedT);
	cout << findMinCut(graph) << endl;
	

}
