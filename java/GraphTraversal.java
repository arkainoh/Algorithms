import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Stack;

public class GraphTraversal {
	
	public static void main(String[] args) {
		BufferedReader bir = new BufferedReader(new InputStreamReader(System.in));
		try{
			String str = bir.readLine();
			System.out.println(str);
		} catch (Exception e) {
			e.printStackTrace();
		}
		/*
		WeightedDigraph g = new WeightedDigraph(5);
		g.addEdge(0, 1, 10);
		g.addEdge(0, 2, 3);
		g.addEdge(1, 2, 1);
		g.addEdge(1, 3, 2);
		g.addEdge(2, 1, 4);
		g.addEdge(2, 3, 8);
		g.addEdge(2, 4, 2);
		g.addEdge(3, 4, 7);
		g.addEdge(4, 3, 9);
		Dijkstra(g, 0);
		*/
		/*
		Bigraph g = new Bigraph(5);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(1, 2);
		g.addEdge(1, 3);
		g.addEdge(2, 3);
		g.addEdge(2, 4);
		g.addEdge(3, 4);
		DFS(g, 0);
		BFS(g, 0);
		*/
		WeightedDigraph g = new WeightedDigraph(8);
		g.addEdge(0, 1, 1);
		g.addEdge(0, 2, 1);
		g.addEdge(0, 3, 1);
		g.addEdge(1, 4, 1);
		g.addEdge(1, 6, 1);
		g.addEdge(2, 5, 1);
		g.addEdge(3, 5, 1);
		g.addEdge(4, 7, 1);
		g.addEdge(5, 7, 1);
		g.addEdge(6, 7, 1);
		
		
	}
	
	public static void DFS(UndirectedGraph g, int src) {
		Stack<Integer> st = new Stack();
		boolean[] visited = new boolean[g.V()];
		
		st.push(src);
		while(!st.isEmpty()) {
			int cp = st.pop();
			
			if(!visited[cp]) {
				visited[cp] = true;
				System.out.print(cp + " ");
				
				for(int v : g.adj(cp)) {
					if(!visited[v])	st.push(v);
				}
			}
		}
		System.out.println();
	}
	
	public static void BFS(UndirectedGraph g, int src) {
		Queue<Integer> q = new LinkedList<Integer>();
		boolean[] visited = new boolean[g.V()];
		
		q.add(src);
		while(!q.isEmpty()) {
			int cp = q.poll();
			
			if(!visited[cp]) {
				visited[cp] = true;
				System.out.print(cp + " ");
				
				for(int v : g.adj(cp)) {
					if(!visited[v]) q.add(v);
				}
			}
		}
		System.out.println();
	}
	
	public static void FloydWarshall(int[][] g) {
		int N = g.length;
		int[][] d = new int[N][N];
		
		for(int k = 0; k < N; k++) {
			for(int u = 0; u < N; u++) {
				for(int v = 0; v < N; v++) {
					if(d[u][v] > d[u][k] + d[k][v])
						d[u][v] = d[u][k] + d[k][v];
				}
			}
		}
	}
	
	public static void Dijkstra(WeightedDigraph g, int src) {
		PriorityQueue<WeightedEdge> pq = new PriorityQueue<WeightedEdge>(new Comparator<WeightedEdge>() {
			@Override
			public int compare(WeightedEdge o1, WeightedEdge o2) {
				return o1.compareTo(o2);
			}
		});
		
		int[] d = new int[g.V()];
		boolean[] visited = new boolean[g.V()];
		
		for(int i = 0; i < d.length; i++) {
			d[i] = Integer.MAX_VALUE;
			visited[i] = false;
		}
		
		d[src] = 0;
		visited[src] = true;
		for (WeightedEdge e : g.adj(src)) {
			pq.add(e);
		}
		
		while(!pq.isEmpty()) {
			WeightedEdge e = pq.poll();
			if(d[e.to()] > d[e.from()] + e.getW() && !visited[e.to()]) {
				d[e.to()] = d[e.from()] + e.getW();
				visited[e.to()] = true;
				for (WeightedEdge ee : g.adj(e.to())) {
					pq.add(ee);
				}
			}
		}
		
		for (int n : d) {
			System.out.print(n+" ");
		}
		System.out.println();
	}
}
