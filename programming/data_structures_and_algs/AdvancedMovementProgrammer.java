public class AdvancedMovementProgrammer {
	private DLDeque<Movement> deque;

	public AdvancedMovementProgrammer() {
		deque=new DLDeque<Movement>();
	}
	public AdvancedMovementProgrammer(DLDeque<Movement> deque) {
		this.deque=(deque==null)? new DLDeque<Movement>() : deque;
	}
	public void program(Movement m) {
		deque.insertLast(m);
	}
	public Movement next() {
		return deque.removeFirst();
	}
	public Movement peekNext() {
		return deque.first();
	}
	public int numMovements() {
		return deque.size();
	}
	public void reset() {
		deque=new DLDeque<Movement>();
	}
	public Movement undo() {
		return deque.removeLast();
	}
	public void reverseProgram() {
		LinkedStack<Movement> st=new LinkedStack<Movement>();
		while(!deque.isEmpty()) {
			st.push(deque.removeFirst());
		}
		while(!st.isEmpty()) {
			deque.insertLast(st.pop());
		}
	}
}
