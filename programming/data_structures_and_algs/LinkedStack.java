public class LinkedStack<E> implements Stack<E> {
	private Node<E> top;
	private int size;

	public LinkedStack() {
		top=null;
		size=0;
	}
	public int size() {
		return size;
	}
	public boolean isEmpty() {
		return size==0;
	}
	public void push(E info) {
		top=new Node<E>(info,top);
		size++;
	}
	public E top() {
		if(isEmpty()) {
			return null;
		}else {
			return top.getInfo();
		}
	}
	public E pop() {
		if(isEmpty()) {
			return null;
		}else {
			E result=top.getInfo();
			top=top.getNext();
			size--;
			return result;
		}
	}
}
