import java.util.Scanner;
import java.io.File;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;

public class Main {

    private static class compareNodes implements Comparator<Node>
    {
        @Override
        public int compare(Node x, Node y)
        {
            if (x.getCost() > y.getCost()) {
                return 1;
            }
            else if (x.getCost() < y.getCost()) {
                return -1;
            }
            else if(x.getTime() > y.getTime()){
                return 1;
            }
            else if(x.getTime() < y.getTime()){
                return -1;
            }
            else {
                return 0;
            }
        }
    }

    private static class dijkGraph {

        private ArrayList<ArrayList<Node>> graph;
        int vertices;

        private dijkGraph(){

        }

        private dijkGraph(int vertices) {
            this.graph = new ArrayList<ArrayList<Node>>(vertices);
            this.vertices = vertices;

            populate(vertices);
        }

        private void populate(int vertices) {
            populateTradeOffs(vertices, graph);
        }

        private void append(int vertex, Node edge) {
            graph.get(vertex).add(edge);
        }

        private ArrayList<Node> getEdgeList(int vertex) {
            return graph.get(vertex);
        }

        public void print(){
            for(int i = 0; i < vertices; i++){
                System.out.print(i + " : ");
                printEdges(i);
                System.out.println(" ");
            }
        }

        private void printEdges(int i) {
            for (int j = 0; j < graph.get(i).size(); j++){
                System.out.print(graph.get(i).get(j).getEdge() + " ");
            }
        }
    }

    private static class Node{
        private int edge, cost, time;

        private Node(int edge, int cost, int time) {
            this.edge = edge;
            this.cost = cost;
            this.time = time;
        }

        private int getEdge() {
            return edge;
        }

        private int getCost() {
            return cost;
        }

        private int getTime() {
            return time;
        }

        private void setCost(int cost) {
            this.cost = cost;
        }

        private void setTime(int time) {
            this.time = time;
        }
    }
    private static void getTradeoffCurves(dijkGraph dijkGraph, int vertices, int src, int dest){
        ArrayList<ArrayList<Node>> analyzeVerts = new ArrayList<ArrayList<Node>>(vertices);
        populateTradeOffs(vertices, analyzeVerts);

        Comparator<Node> nodeComparer = new compareNodes();
        PriorityQueue<Node> minHeap = new PriorityQueue<Node>(vertices, nodeComparer);

        Node source = new Node(src, 0, 0);
        analyzeVerts.get(src).add(source);
        ArrayList<Node> srcEdgeList = dijkGraph.getEdgeList(src);

        addMinHeap(minHeap, srcEdgeList);

        while(!minHeap.isEmpty()){
            Node minNode = minHeap.remove();
            int minEdge = minNode.getEdge();

            ArrayList<Node> tradeoffCurve = analyzeVerts.get(minEdge);
            int lastTradeoff = tradeoffCurve.size() - 1;
            if(tradeoffCurve.isEmpty()){
                analyzeVerts.get(minEdge).add(minNode);
            }
            else{
                if(tradeoffCurve.get(lastTradeoff).getCost() < minNode.getCost()){
                    if(tradeoffCurve.get(lastTradeoff).getTime() > minNode.getTime()){
                        analyzeVerts.get(minEdge).add(minNode);
                    }
                }
            }
            analyzeTradeOff(dijkGraph, minHeap, minNode, minEdge);

        }

        printTC(dest, analyzeVerts);

    }

    private static void printTC(int dest, ArrayList<ArrayList<Node>> analyzeVerts) {
        for(Node tradeOff:  analyzeVerts.get(dest)){
            System.out.println(tradeOff.getCost() + " " + tradeOff.getTime());
        }
    }

    private static void analyzeTradeOff(dijkGraph dijkGraph, PriorityQueue<Node> minHeap, Node minNode, int minEdge) {
        ArrayList<Node> minEdgeNeighbors = dijkGraph.getEdgeList(minEdge);
        for(int i = 0; i < minEdgeNeighbors.size(); i++){
            int originalCost = minEdgeNeighbors.get(i).getCost();
            int originalTime = minEdgeNeighbors.get(i).getTime();
            int edgeId = minEdgeNeighbors.get(i).getEdge();
            Node neighbor = new Node(edgeId, originalCost, originalTime);

            neighbor.setCost(originalCost + minNode.getCost());
            neighbor.setTime(originalTime + minNode.getTime());

            minHeap.add(neighbor);
        }
    }

    private static void addMinHeap(PriorityQueue<Node> minHeap, ArrayList<Node> srcEdgeList) {
        for(int i = 0; i < srcEdgeList.size(); i++){
            minHeap.add(srcEdgeList.get(i));
        }
    }

    private static void populateTradeOffs(int vertices, ArrayList<ArrayList<Node>> tradeoffLists) {
        for(int i = 0; i < vertices; i++){
            ArrayList<Node> edgeList = new ArrayList<Node>();
            tradeoffLists.add(i, edgeList);
        }
    }
    int V;
    int minDistance(int dist[], Boolean sptSet[])
    {
        int min = Integer.MAX_VALUE, min_index=-1;

        for (int v = 0; v < V; v++)
            if (sptSet[v] == false && dist[v] <= min)
            {
                min = dist[v];
                min_index = v;
            }

        return min_index;
    }

    void printSolution(int dist[], int n)
    {
        System.out.println("Vertex   Distance from Source");
        for (int i = 0; i < V; i++)
            System.out.println(i+" \t\t "+dist[i]);
    }

    public static void dijkstra2(dijkGraph dijkGraph, int V, int src, int dest){

        int dist[] = new int[V];
        Boolean sptSet[] = new Boolean[V];
    }
    void dijkstra(int graph[][], int src)
    {
        int dist[] = new int[V];
        Boolean sptSet[] = new Boolean[V];

        for (int i = 0; i < V; i++)
        {
            dist[i] = Integer.MAX_VALUE;
            sptSet[i] = false;
        }
        dist[src] = 0;

        for (int count = 0; count < V-1; count++)
        {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            for (int v = 0; v < V; v++)

                if (!sptSet[v] && graph[u][v]!=0 &&
                        dist[u] != Integer.MAX_VALUE &&
                        dist[u]+graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
        }

        printSolution(dist, V);
    }


    public static void main (String args[]) {

        if(args.length != 3) {
            System.out.println("Insufficient arguments. Needs <N> <T> <FILE> (No '<' )). Will not conduct program.");
            System.exit(0);
        }

        int n = Integer.parseInt(args[0]);
        int sum = Integer.parseInt(args[1]);
        File file = new File(args[2]);

        dijkGraph dijkGraph = new dijkGraph();
        int vertices = 0;

        try {

            Scanner sc = new Scanner(System.in);
            sc = new Scanner(file);
            vertices = sc.nextInt();
            System.out.println(vertices);
            dijkGraph = new dijkGraph(vertices);

            while (sc.hasNextLine() && sc.hasNextInt()) {
                int vertex = sc.nextInt();
                int edge = sc.nextInt();
                int cost = sc.nextInt();
                int time = sc.nextInt();
                Node node = new Node(edge, cost, time);
                dijkGraph.append(vertex, node);
            }
            sc.close();

        } catch (Exception ex) {
            ex.printStackTrace();
            System.out.println("No file found");
        }

        //        dijkGraph.print();

        getTradeoffCurves(dijkGraph, vertices, n, sum);
        //dijkstra2(dijkGraph, verts, n, sum)

    }
}


