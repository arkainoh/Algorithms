import java.util.ArrayList;
import java.util.Arrays;

public class UndirectedGraph {
	private int V, E;
	private ArrayList<Integer>[] adj;
	
	public UndirectedGraph(int V) {
		this.V = V;
		adj = new ArrayList[V];
		for(int i = 0; i < V; i++)
			adj[i] = new ArrayList<Integer>();
	}
	
	public Iterable<Integer> adj(int v) {
		return adj[v];
	}
	
	public void addEdge(int u, int v) {
		E++;
		adj[u].add(v);
		adj[v].add(u);
	}

	public int V() {
		return V;
	}

	public int E() {
		return E;
	}

	@Override
	public String toString() {
		return "UndirectedGraph [" + Arrays.toString(adj) + "]";
	}
}
