public class LBTree<E> implements BTree<E> {
    private BNODE<E> root;

    public LBTree() {
        this.root = null;
    }

    public LBTree(E info) {
        this.root = new BNODE<E>(info, new LBTree<E>(), new LBTree<E>());
    }

    private LBTree(BNODE<E> root) {
        this.root = root;
    }

    public boolean isEmpty() {
        return root == null;
    }

    public int size() {
        if (isEmpty()) {
            return 0;
        }
        int leftSize = 0;
        int rightSize = 0;
        try {
            leftSize = getLeft().size();
            rightSize = getRight().size();
        } catch (BTreeException e) {
            leftSize = 0;
            rightSize = 0;
        }
        return 1 + leftSize + rightSize;
    }

    public int height() {
        if (isEmpty()) {
            return -1;
        }
        int lh = -1;
        int rh = -1;
        try {
            lh = getLeft().height();
            rh = getRight().height();
        } catch (BTreeException e) {
            lh = -1;
            rh = -1;
        }
        return 1 + (lh > rh ? lh : rh);
    }

    public E getInfo() throws BTreeException {
        if (isEmpty()) {
            throw new BTreeException("Empty tree");
        }
        return root.getInfo();
    }

    public BTree<E> getLeft() throws BTreeException {
        if (isEmpty()) {
            throw new BTreeException("Empty tree");
        }
        BTree<E> t = root.getLeft();
        return t == null ? new LBTree<E>() : t;
    }

    public BTree<E> getRight() throws BTreeException {
        if (isEmpty()) {
            throw new BTreeException("Empty tree");
        }
        BTree<E> t = root.getRight();
        return t == null ? new LBTree<E>() : t;
    }

    public void insert(BTree<E> tree, int side) throws BTreeException {
        if (isEmpty()) {
            throw new BTreeException("Cannot insert into an empty tree");
        }
        if (tree == null) {
            throw new BTreeException("Null subtree");
        }
        if (side != LEFT && side != RIGHT) {
            throw new BTreeException("Invalid side");
        }
        if (side == LEFT) {
            root.setLeft(tree);
        } else {
            root.setRight(tree);
        }
    }

    public BTree<E> extract(int side) throws BTreeException {
        if (isEmpty()) {
            throw new BTreeException("Cannot extract from an empty tree");
        }
        if (side != LEFT && side != RIGHT) {
            throw new BTreeException("Invalid side");
        }
        BTree<E> result;
        if (side == LEFT) {
            result = root.getLeft();
            root.setLeft(new LBTree<E>());
        } else {
            result = root.getRight();
            root.setRight(new LBTree<E>());
        }
        return result == null ? new LBTree<E>() : result;
    }

    public String toStringPreOrder() {
        StringBuilder sb = new StringBuilder();
        buildPreOrder(sb);
        return sb.toString().trim();
    }

    private void buildPreOrder(StringBuilder sb) {
        if (isEmpty()) {
            return;
        }
        sb.append(root.getInfo()).append(' ');
        try {
            ((LBTree<E>) getLeft()).buildPreOrder(sb);
            ((LBTree<E>) getRight()).buildPreOrder(sb);
        } catch (Exception e) {
        }
    }

    public String toStringInOrder() {
        StringBuilder sb = new StringBuilder();
        buildInOrder(sb);
        return sb.toString().trim();
    }

    private void buildInOrder(StringBuilder sb) {
        if (isEmpty()) {
            return;
        }
        try {
            ((LBTree<E>) getLeft()).buildInOrder(sb);
        } catch (Exception e) {
        }
        sb.append(root.getInfo()).append(' ');
        try {
            ((LBTree<E>) getRight()).buildInOrder(sb);
        } catch (Exception e) {
        }
    }

    public String toStringPostOrder() {
        StringBuilder sb = new StringBuilder();
        buildPostOrder(sb);
        return sb.toString().trim();
    }

    private void buildPostOrder(StringBuilder sb) {
        if (isEmpty()) {
            return;
        }
        try {
            ((LBTree<E>) getLeft()).buildPostOrder(sb);
            ((LBTree<E>) getRight()).buildPostOrder(sb);
        } catch (Exception e) {
        }
        sb.append(root.getInfo()).append(' ');
    }

    public String toString() {
        return toStringPreOrder();
    }

    public boolean equals(BTree<E> tree) {
        if (tree == null) {
            return false;
        }
        if (isEmpty()) {
            return tree.isEmpty();
        }
        if (tree.isEmpty()) {
            return false;
        }
        try {
            if (!getInfo().equals(tree.getInfo())) {
                return false;
            }
            return ((LBTree<E>) getLeft()).equals(tree.getLeft()) && ((LBTree<E>) getRight()).equals(tree.getRight());
        } catch (BTreeException e) {
            return false;
        }
    }

    public boolean find(BTree<E> tree) {
        if (tree == null) {
            return false;
        }
        if (equals(tree)) {
            return true;
        }
        if (isEmpty()) {
            return false;
        }
        try {
            return ((LBTree<E>) getLeft()).find(tree) || ((LBTree<E>) getRight()).find(tree);
        } catch (BTreeException e) {
            return false;
        }
    }
}
