public class Node<E> {
	private E info;
	private Node<E> next;
	
	public Node(E info, Node<E> next) {
		this.info=info;
		this.next=next;
	}
	public Node(E info) {
		this(info,null);
	}
	public Node() {
		this(null,null);
	}
	public E getInfo() {
		return this.info;
	}
	public Node<E> getNext(){
		return this.next;
	}
	public void setNext(Node<E> next) {
		this.next= next;
	}
	public void setInfo(E info) {
		this.info=info;
	}
	public String toString() {
		if(getInfo()==null) {
			return null;
		}else {
			return ""+ getInfo();
		}
		
	}

}
