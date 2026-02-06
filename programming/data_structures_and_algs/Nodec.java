public class Nodec<E> {
		private E info;
		private Nodec<E> next;
		private Integer key;

		public Nodec(E info, Integer key, Nodec<E> next) {
			this.info=info;
			this.next=next;
			this.key=key;
		}
		public Nodec(E info, Integer key) {
			this(info,key,null);
		}
		public Nodec() {
			this(null,null,null);
		}
		public E getInfo() {
			return this.info;
		}
		public Integer getKey(){
			return this.key;
		}
		public void setKey(Integer key){
			this.key=key;
		}
		public Nodec<E> getNext(){
			return this.next;
		}
		public void setNext(Nodec<E> next) {
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
