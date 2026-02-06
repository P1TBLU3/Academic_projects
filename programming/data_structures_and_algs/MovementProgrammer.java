public class MovementProgrammer {
	private LinkedQueue<Movement> queue;
	public MovementProgrammer(LinkedQueue<Movement> queue) {
		this.queue=queue;
	}
	public MovementProgrammer() {
		queue= new LinkedQueue<Movement>();
	}
	public void program(Movement m) {
		queue.enqueue(m);
	}
	public Movement next() {
		return queue.dequeue();
	}
	public int numMovements() {
		return queue.size();
	}
	public void reset() {
		queue= new LinkedQueue<Movement>();
	}
}
