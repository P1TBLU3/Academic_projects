public class ArrayQueue<E> implements Queue<E> {
	private E[] info;
	private int capacity;
	private int top;
	private int tail;

	public ArrayQueue(int capacity) {
		this.capacity=capacity;
		this.info= (E[]) new Object[capacity];
		this.top=0;
		this.tail=-1;
	}
	public boolean isEmpty() {
		return tail<top;
	}
	public int size() {
		if(isEmpty()) {
			return 0;
		}else {
			return tail-top+1;
		}
	}
	public E front() {
		if(isEmpty()) {
			return null;
		}else {
			return this.info[top];
		}
	}
	private void compact() {
		if(top==0) {return;}
		int n=size();
		for(int i=0;i<n;i++) {
			info[i]=info[top+i];
		}
		for(int i=n;i<capacity;i++) {
			info[i]=null;
		}
		top=0;
		tail=n-1;
	}
	public void enqueue(E info) {
		if(tail==capacity-1) {
			if(top>0) {
				compact();
			}else {
				System.out.println("NO");
				return;
			}
		}
		tail++;
		this.info[tail]=info;
	}
	public E dequeue() {
		if(isEmpty()) {
			return null;
		}else {
			E result= this.info[top];
			this.info[top]=null;
			top++;
			if(isEmpty()) {
				top=0;
				tail=-1;
			}
			return result;
		}
	}
}
