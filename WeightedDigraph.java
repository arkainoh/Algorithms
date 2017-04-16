import java.util.ArrayList;
import java.util.Arrays;

public class WeightedDigraph {
	private int V;
	private int E;
	private ArrayList<WeightedEdge>[] edges;

	public WeightedDigraph(int V) {
		this.V = V;
		edges = new ArrayList[V];
		for (int i = 0; i < V; i++)
			edges[i] = new ArrayList<WeightedEdge>();
	}
	
	public void addEdge(int u, int v, int w) {
		E++;
		edges[u].add(new WeightedEdge(u, v, w));
	}

	public int V() {
		return V;
	}

	public int E() {
		return E;
	}

	public Iterable<WeightedEdge> adj(int v) {
		return edges[v];
	}
	@Override
	public String toString() {
		return "WeightedDigraph [" + Arrays.toString(edges) + "]";
	}
}


