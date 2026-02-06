public class DLDeque<E> implements Deque<E> {
	private int size;
	private DLNode<E> top;
	private DLNode<E> tail;
	public DLDeque() {
		this.top= new DLNode<E>(null,null,null);
		this.tail=new DLNode<E>(null,top,null);
		top.setNext(tail);
		this.size=0;
	}
	public int size() {
		return this.size;
	}
	public boolean isEmpty() {
		return size==0;
	}
	public E first() {
		if(isEmpty()) {return null;}
		return top.getNext().getInfo();
	}
	public E last() {
		if(isEmpty()) {return null;}
		return tail.getPrev().getInfo();
	}
	public void insertFirst(E info) {
		DLNode<E> a=top.getNext();
		DLNode<E> tmp= new DLNode<E>(info,top,a);
		a.setPrev(tmp);
		top.setNext(tmp);
		size++;
	}
	public void insertLast(E info) {
		DLNode<E> b=tail.getPrev();
		DLNode<E> tmp= new DLNode<E>(info,b,tail);
		b.setNext(tmp);
		tail.setPrev(tmp);
		size++;
	}
	public E removeFirst() {
		if(isEmpty()) {
			return null;
		}else {
			DLNode<E> a=top.getNext();
			E result=a.getInfo();
			DLNode<E> b=a.getNext();
			top.setNext(b);
			b.setPrev(top);
			size--;
			return result;
		}
	}
	public E removeLast() {
		if(isEmpty()) {
			return null;
		}else {
			DLNode<E> a=tail.getPrev();
			E result=a.getInfo();
			DLNode<E> b=a.getPrev();
			b.setNext(tail);
			tail.setPrev(b);
			size--;
			return result;
		}
	}
}
