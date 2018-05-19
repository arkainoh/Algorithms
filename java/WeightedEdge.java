class WeightedEdge implements Comparable<WeightedEdge>{
	private int u, v, w;

	public WeightedEdge(int u, int v, int w) {
		this.u = u;
		this.v = v;
		this.w = w;
	}
	
	public int from() {
		return u;
	}

	public int to() {
		return v;
	}

	public int getW() {
		return w;
	}

	@Override
	public int compareTo(WeightedEdge o) {
		return w - o.getW();
	}
	
	public String toString() {
		return "(" + u + ")-" + w + "->(" + v + ")";
	}
}