public class DLNode<E> {
private E info;
private DLNode<E> prev;
private DLNode<E> next;


public DLNode(E info, DLNode<E> prev, DLNode<E> next){
	this.info=info;
	this.prev=prev;
	this.next=next;
}
public DLNode(E info) {this(info,null,null);}
public DLNode() {this(null,null,null);}
public DLNode<E> getNext(){return this.next;}
public void setNext(DLNode<E> next){this.next=next;}
public DLNode<E> getPrev(){return this.prev;}
public void setPrev(DLNode<E> prev){this.prev=prev;}
public E getInfo(){return this.info;}
public void setInfo(E info){this.info=info;}
}