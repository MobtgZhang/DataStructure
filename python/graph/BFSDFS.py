import networkx as nx
import matplotlib.pyplot as plt
import matplotlib as mpl
mpl.rcParams['font.sans-serif'] = ['KaiTi']
mpl.rcParams['font.serif'] = ['KaiTi']
def read_data():
    list_val = []
    with open("data.txt",'r',encoding='utf-8') as file:
        while True:
            line = file.readline()
            if not line:
                break
            line = line.split()
            name1 = line[0]
            name2 = line[1]
            value = int(line[2])
            list_o = [name1,name2,value]
            list_val.append(list_o)
    return list_val
def DFS():
    list_val = read_data()
    G = nx.Graph()
    G.add_weighted_edges_from(list_val)
    visited = set()
    list_out = []
    dfs(G,'株洲',visited,list_out)
    dfs_str_line = "DFS: "
    for item in list_out[:-1]:
        dfs_str_line = dfs_str_line + item + " -> "
    dfs_str_line = dfs_str_line + list_out[-1]
    print(dfs_str_line)
def dfs(graph,value,visited,list_out):
    visited.add(value)
    list_out.append(value)
    for item in graph.neighbors(value):
        if item not in visited:
            dfs(graph,item,visited,list_out)
class Queue:
    def __init__(self):
        self.list = []
        self.rear = -1
    def EnQueue(self,value):
        self.list.append(value)
        self.rear += 1
    def DeQueue(self):
        value = self.list[0]
        del self.list[0]
        return value
    def isEmpty(self):
        return len(self.list) == 0
def bfs(graph,value,visited,list_out):
    que = Queue()
    for v in graph.nodes:
        if v not in visited:
            visited.add(v)
            list_out.append(v)
            que.EnQueue(v)
            while not que.isEmpty():
                u = que.DeQueue()
                for w in graph.neighbors(u):
                    if w not in visited:
                        visited.add(w)
                        list_out.append(w)
                        que.EnQueue(w)
def BFS():
    list_val = read_data()
    G = nx.Graph()
    G.add_weighted_edges_from(list_val)
    visited = set()
    list_out = []
    bfs(G, '株洲', visited, list_out)
    bfs_str_line = "BFS: "
    for item in list_out[:-1]:
        bfs_str_line = bfs_str_line + item + " -> "
    bfs_str_line = bfs_str_line + list_out[-1]
    print(bfs_str_line)
if __name__ == '__main__':
    BFS()
    DFS()