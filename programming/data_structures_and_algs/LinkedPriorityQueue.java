public class LinkedPriorityQueue <E> implements Queue<E> {
	private Nodec<E> top;
	private Nodec<E> tail;
	private int size;

	public LinkedPriorityQueue() {
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
		enqueue(info,0);
	}
	public void enqueue(E info, Integer key) {
		Nodec<E> tmp= new Nodec<E>(info,key,null);
		if(isEmpty()) {
			top=tmp;
			tail=tmp;
			size=1;
			return;
		}
		if(key.compareTo(top.getKey())<0) {
			tmp.setNext(top);
			top=tmp;
			size++;
			return;
		}
		Nodec<E> a=top;
		while(a.getNext()!=null && key.compareTo(a.getNext().getKey())>=0) {
			a=a.getNext();
		}
		tmp.setNext(a.getNext());
		a.setNext(tmp);
		if(tmp.getNext()==null) {
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
