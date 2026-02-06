public class LBSTree<E> implements BSTree<E> {
	private LBSNode<E> root;

	public LBSTree(E info, Comparable key ) {
		if(key==null && info==null) {
			root=null;
		}else {
			root=new LBSNode<E>(key,info,new LBSTree<E>(),new LBSTree<E>());
		}
	}
	public LBSTree() {
		this.root=null;
	}
	public boolean isEmpty() {
		return root==null;
	}
	public E getInfo(){
		if(isEmpty()) {
			return null;
		}else {
			return root.getInfo();		
		}
	}
	public BSTree<E> getLeft(){
		if(isEmpty()) {
			return null;
		}else {
			return root.getLeft();		
		}
	}
	public BSTree<E> getRight(){
		if(isEmpty()) {
			return null;
		}else {
			return root.getRight();		
		}
	}
	public Comparable getKey() {
		if(isEmpty()) {
			return null;
		}else {
			return root.getKey();
		}
	}
	public void insert(Comparable key, E info) {
		if(isEmpty()) {
			root=new LBSNode<E>(key,info,new LBSTree<E>(),new LBSTree<E>());
		}else {
			if(key.compareTo(getKey())<0){
				root.getLeft().insert(key, info);
			}else if(key.compareTo(getKey())>0) {
				root.getRight().insert(key, info);
			}else {
				root.setInfo(info);
			}
		}
	}
	public BSTree<E> search(Comparable key) {
		if(isEmpty()) {
			return null;
		}else {
			if(key.compareTo(getKey())<0) {
				return root.getLeft().search(key);
			}else if(key.compareTo(getKey())>0) {
				return root.getRight().search(key);
			}else {
				return this;
			}
		}
	}
	public String toStringPreOrder() {
		if(isEmpty()) {
			return "";
		}else {
			return ""+root.getInfo()+" "+root.getLeft().toStringPreOrder()+" "+root.getRight().toStringPreOrder();
		}
	}
	public String toStringInOrder() {
		if(isEmpty()) {
			return "";
		}else {
			return ""+root.getLeft().toStringInOrder()+" "+root.getInfo()+" "+root.getRight().toStringInOrder();
		}
	}
	public String toStringPostOrder() {
		if(isEmpty()) {
			return "";
		}else {
			return  root.getLeft().toStringPostOrder()+" "+root.getRight().toStringPostOrder()+" "+root.getInfo();
		}
	}
	public String toString() {
		return toStringPreOrder();
	}
}
