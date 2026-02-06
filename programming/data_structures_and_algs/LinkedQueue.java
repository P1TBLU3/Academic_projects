public class LinkedQueue <E> implements Queue<E> {
	private Node<E> top;
	private Node<E>	tail;
	private int size;

	public LinkedQueue() {
		this.top=null;
		this.tail=null;
		this.size=0;
	}
	public boolean isEmpty() {
		return size==0;
	}
	public int size() {
		return size;
	}
	public void enqueue(E info) {
		Node<E> tmp= new Node<E>(info,null);
		if(isEmpty()) {
			top=tmp;
			tail=tmp;
		}else {
			tail.setNext(tmp);
			tail=tmp;
		}
		size++;
	}
	public E front() {
		if(isEmpty()) {
			return null;
		}else {
			return top.getInfo();
		}
	}
	public E dequeue() {
		if(isEmpty()) {
			return null;
		}else {
			E result= top.getInfo();
			top=top.getNext();
			size--;
			if(size==0) {
				tail=null;
			}
			return result;
		}
	}
}
