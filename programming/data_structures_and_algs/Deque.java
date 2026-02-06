public interface Deque<E> {
	public boolean isEmpty();
	public int size();
	public E first();
	public E last();
	public void insertFirst(E info);
	public void insertLast( E info);
	public E removeFirst();
	public E removeLast();

}
