public interface Queue<E> {
	int size();
	boolean isEmpty();
	E front();
	E dequeue();
	void enqueue(E info);
}
