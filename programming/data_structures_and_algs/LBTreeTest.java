
public class LBTreeTest {

    static BTree<String> A, B, C, D, E, F, G, H, I, J, K;
    static BTree<String> A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2;

    // A
    // / \
    // / \
    // B E
    // / / \
    // C F G
    // \ / \
    // D H I
    // / \
    // J K
    static void buildTestTree() {
        A = new LBTree<String>(new String("A"));
        B = new LBTree<String>(new String("B"));
        C = new LBTree<String>(new String("C"));
        D = new LBTree<String>(new String("D"));
        E = new LBTree<String>(new String("E"));
        F = new LBTree<String>(new String("F"));
        G = new LBTree<String>(new String("G"));
        H = new LBTree<String>(new String("H"));
        I = new LBTree<String>(new String("I"));
        J = new LBTree<String>(new String("J"));
        K = new LBTree<String>(new String("K"));
        try {
            I.insert(J, LBTree.LEFT);
            I.insert(K, LBTree.RIGHT);
            G.insert(H, LBTree.LEFT);
            G.insert(I, LBTree.RIGHT);
            E.insert(F, LBTree.LEFT);
            E.insert(G, LBTree.RIGHT);
            C.insert(D, LBTree.RIGHT);
            B.insert(C, LBTree.LEFT);
            A.insert(B, LBTree.LEFT);
            A.insert(E, LBTree.RIGHT);
        } catch (Exception e) {
            e.printStackTrace();
        }

        A2 = new LBTree<String>(new String("A"));
        B2 = new LBTree<String>(new String("B"));
        C2 = new LBTree<String>(new String("C"));
        D2 = new LBTree<String>(new String("D"));
        E2 = new LBTree<String>(new String("E"));
        F2 = new LBTree<String>(new String("F"));
        G2 = new LBTree<String>(new String("G"));
        H2 = new LBTree<String>(new String("H"));
        I2 = new LBTree<String>(new String("I"));
        J2 = new LBTree<String>(new String("J"));
        K2 = new LBTree<String>(new String("K"));
        try {
            I2.insert(J2, LBTree.LEFT);
            I2.insert(K2, LBTree.RIGHT);
            G2.insert(H2, LBTree.LEFT);
            G2.insert(I2, LBTree.RIGHT);
            E2.insert(F2, LBTree.LEFT);
            E2.insert(G2, LBTree.RIGHT);
            C2.insert(D2, LBTree.RIGHT);
            B2.insert(C2, LBTree.LEFT);
            A2.insert(B2, LBTree.LEFT);
            A2.insert(E2, LBTree.RIGHT);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static boolean testIsEmpty() {
        System.out.print("testing isEmpty: ");

        BTree<String> empty = new LBTree<String>();
        if (!empty.isEmpty()) {
            System.out.println("ERROR, isEmpty() returns false on an empty tree");
            return false;
        }

        BTree<String> notEmpty = new LBTree<String>("test");
        if (notEmpty.isEmpty()) {
            System.out.println("ERROR, isEmpty() returns true on an non-empty tree");
            return false;
        }
        System.out.println("OK");
        return true;
    }

    static boolean testGetInfo() {
        System.out.print("testing getInfo: ");

        BTree<String> empty = new LBTree<String>();
        try {
            empty.getInfo();
            System.out.println("ERROR, getInfo on an empty tree does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        BTree<String> tree = new LBTree<String>(new String("test"));
        try {
            String info = tree.getInfo();
            if (!info.equals(new String("test"))) {
                System.out.println("ERROR: bat info returned, was \"" + info + "\" but should be \"test\"");
                return false;
            }
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testInsert() {
        System.out.print("testing insert: ");

        BTree<String> empty = new LBTree<String>();
        BTree<String> tree = new LBTree<String>("test");
        try {
            empty.insert(tree, BTree.LEFT);
            System.out.println("ERROR, insert on an empty tree does not throw an BTreeException");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, insert on an empty tree throws an incorrect exception:");
            e.printStackTrace();
            return false;
        }
        try {
            empty.insert(tree, BTree.RIGHT);
            System.out.println("ERROR, insert on an empty tree does not throw an BTreeException");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, insert on an empty tree throws an incorrect exception:");
            e.printStackTrace();
            return false;
        }

        BTree<String> a = new LBTree<String>(new String("a"));
        BTree<String> b = new LBTree<String>(new String("b"));
        BTree<String> c = new LBTree<String>(new String("c"));
        try {
            a.insert(b, BTree.LEFT);
            a.insert(c, BTree.RIGHT);
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        // insert again
        try {
            a.insert(b, BTree.LEFT);
            a.insert(c, BTree.RIGHT);
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        // and again with different values
        try {
            a.insert(c, BTree.LEFT);
            a.insert(b, BTree.RIGHT);
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        // test wrong side values
        a = new LBTree<String>(new String("a"));
        b = new LBTree<String>(new String("b"));
        try {
            a.insert(b, -20);
            System.out.println("ERROR, inserting in side -20 does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        try {
            a.insert(b, 3);
            System.out.println("ERROR, inserting in side 3 does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testGetLeft() {
        System.out.print("testing getLeft: ");

        BTree<String> empty = new LBTree<String>();
        try {
            empty.getLeft();
            System.out.println("ERROR, getLeft() on an empty tree does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        buildTestTree();
        BTree<String> tree;
        try {
            tree = E.getLeft();
            if (tree != F) {
                System.out.println("ERROR, bad return value from E.getLeft()");
                return false;
            }
            tree = H.getLeft();
            if (!tree.isEmpty()) {
                System.out.println("ERROR, bad return value from H.getLeft()");
                return false;
            }
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testGetRight() {
        System.out.print("testing getRight: ");

        BTree<String> empty = new LBTree<String>();
        try {
            empty.getRight();
            System.out.println("ERROR, getRight() on an empty tree does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        buildTestTree();
        BTree<String> tree;
        try {
            tree = E.getRight();
            if (tree != G) {
                System.out.println("ERROR, bad return value from E.getRight()");
                return false;
            }
            tree = H.getRight();
            if (!tree.isEmpty()) {
                System.out.println("ERROR, bad return value from H.getRight()");
                return false;
            }
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testExtract() {
        System.out.print("testing extract: ");

        BTree<String> empty = new LBTree<String>();
        BTree<String> tree;
        try {
            tree = empty.extract(BTree.LEFT);
            System.out.println("ERROR, extract(LEFT) on an empty tree does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }
        try {
            tree = empty.extract(BTree.RIGHT);
            System.out.println("ERROR, extract(LEFT) on an empty tree does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        // test wrong side values
        buildTestTree();
        try {
            tree = A.extract(-20);
            System.out.println("ERROR, extract from side -20 does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        try {
            tree = A.extract(3);
            System.out.println("ERROR, extract from side 3 does not throw an exception");
            return false;
        } catch (BTreeException e) {
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        // test correct extraction
        buildTestTree();
        try {
            tree = K.extract(BTree.LEFT);
            if (!tree.isEmpty()) {
                System.out.println("ERROR, bad return value from K.extract(LEFT)");
                return false;
            }
            tree = K.extract(BTree.RIGHT);
            if (!tree.isEmpty()) {
                System.out.println("ERROR, bad return value from K.extract(RIGHT)");
                return false;
            }

            tree = E.extract(BTree.LEFT);
            if (tree != F) {
                System.out.println("ERROR, bad return value from E.extract(LEFT)");
                return false;
            }
            if (!E.getLeft().isEmpty()) {
                System.out.println("ERROR, left is not empty after extract(LEFT)");
                return false;
            }

            tree = E.extract(BTree.RIGHT);
            if (tree != G) {
                System.out.println("ERROR, bad return value from E.extract(LEFT)");
                return false;
            }
            if (!E.getRight().isEmpty()) {
                System.out.println("ERROR, right is not empty after extract(RIGHT)");
                return false;
            }
        } catch (Exception e) {
            System.out.println("ERROR, exception caught:");
            e.printStackTrace();
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testToStringPreOrder() {
        System.out.print("testing toStringPreOrder: ");

        BTree<String> empty = new LBTree<String>();
        String str = empty.toStringPreOrder();
        String desired = "";
        if (!str.trim().equals(desired)) {
            System.out.println(
                    "ERROR, bad empty.toStringPreOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        buildTestTree();
        str = K.toStringPreOrder();
        desired = "K";
        if (!str.trim().equals(desired)) {
            System.out.println("ERROR, bad K.toStringPreOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        buildTestTree();
        str = A.toStringPreOrder();
        desired = "A B C D E F G H I J K";
        if (!str.trim().equals(desired)) {
            System.out.println("ERROR, bad K.toStringPreOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testToStringInOrder() {
        System.out.print("testing toStringInOrder: ");

        BTree<String> empty = new LBTree<String>();
        String str = empty.toStringInOrder();
        String desired = "";
        if (!str.trim().equals(desired)) {
            System.out.println(
                    "ERROR, bad empty.toStringInOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        buildTestTree();
        str = K.toStringInOrder();
        desired = "K";
        if (!str.trim().equals(desired)) {
            System.out.println("ERROR, bad K.toStringInOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        buildTestTree();
        str = A.toStringInOrder();
        desired = "C D B A F E H G J I K";
        if (!str.trim().equals(desired)) {
            System.out.println("ERROR, bad K.toStringInOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testToStringPostOrder() {
        System.out.print("testing toStringPostOrder: ");

        BTree<String> empty = new LBTree<String>();
        String str = empty.toStringPostOrder();
        String desired = "";
        if (!str.trim().equals(desired)) {
            System.out.println(
                    "ERROR, bad empty.toStringPostOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        buildTestTree();
        str = K.toStringPostOrder();
        desired = "K";
        if (!str.trim().equals(desired)) {
            System.out
                    .println("ERROR, bad K.toStringPostOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        buildTestTree();
        str = A.toStringPostOrder();
        desired = "D C B F H J K I G E A";
        if (!str.trim().equals(desired)) {
            System.out
                    .println("ERROR, bad K.toStringPostOrder(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testToString() {
        System.out.print("testing toString: ");

        BTree<String> empty = new LBTree<String>();
        String str = empty.toString();
        String desired = "";
        if (!str.trim().equals(desired)) {
            System.out.println("ERROR, bad empty.toString(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        buildTestTree();
        str = K.toString();
        desired = "K";
        if (!str.trim().equals(desired)) {
            System.out.println("ERROR, bad K.toString(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        buildTestTree();
        str = A.toString();
        desired = "A B C D E F G H I J K";
        if (!str.trim().equals(desired)) {
            System.out.println("ERROR, bad K.toString(), was\"" + str + "\" but should be \"" + desired + "\"");
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testSize() {
        System.out.print("testing size: ");

        BTree<String> empty = new LBTree<String>();
        int size = empty.size();
        int desired = 0;
        if (size != desired) {
            System.out.println("ERROR, bad empty.size(), was " + size + " but should be " + desired);
            return false;
        }

        buildTestTree();
        size = J.size();
        desired = 1;
        if (size != desired) {
            System.out.println("ERROR, bad J.size(), was " + size + " but should be " + desired);
            return false;
        }

        buildTestTree();
        size = I.size();
        desired = 3;
        if (size != desired) {
            System.out.println("ERROR, bad I.size(), was " + size + " but should be " + desired);
            return false;
        }

        buildTestTree();
        size = B.size();
        desired = 3;
        if (size != desired) {
            System.out.println("ERROR, bad B.size(), was " + size + " but should be " + desired);
            return false;
        }

        buildTestTree();
        size = A.size();
        desired = 11;
        if (size != desired) {
            System.out.println("ERROR, bad A.size(), was " + size + " but should be " + desired);
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testHeight() {
        System.out.print("testing height: ");

        BTree<String> empty = new LBTree<String>();
        int height = empty.height();
        int desired = -1;
        if (height != desired) {
            System.out.println("ERROR, bad empty.height(), was " + height + " but should be " + desired);
            return false;
        }

        buildTestTree();
        height = J.height();
        desired = 0;
        if (height != desired) {
            System.out.println("ERROR, bad J.height(), was " + height + " but should be " + desired);
            return false;
        }

        buildTestTree();
        height = I.height();
        desired = 1;
        if (height != desired) {
            System.out.println("ERROR, bad I.height(), was " + height + " but should be " + desired);
            return false;
        }

        buildTestTree();
        height = B.height();
        desired = 2;
        if (height != desired) {
            System.out.println("ERROR, bad B.height(), was " + height + " but should be " + desired);
            return false;
        }

        buildTestTree();
        height = A.height();
        desired = 4;
        if (height != desired) {
            System.out.println("ERROR, bad A.height(), was " + height + " but should be " + desired);
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testEquals() {
        System.out.print("testing equals: ");

        BTree<String> empty1 = new LBTree<String>();
        BTree<String> empty2 = new LBTree<String>();
        if (!empty1.equals(empty1)) {
            System.out.println("ERROR, empty1 != empty1");
            return false;
        }
        if (!empty1.equals(empty2)) {
            System.out.println("ERROR, empty1 != empty2");
            return false;
        }
        buildTestTree();
        if (empty1.equals(K)) {
            System.out.println("ERROR, empty1 == K");
            return false;
        }
        if (empty1.equals(A)) {
            System.out.println("ERROR, empty1 == A");
            return false;
        }
        if (K.equals(empty1)) {
            System.out.println("ERROR, K == empty1");
            return false;
        }
        if (A.equals(empty1)) {
            System.out.println("ERROR, A == empty1");
            return false;
        }
        if (!K.equals(K)) {
            System.out.println("ERROR, K != K");
            return false;
        }
        if (K.equals(J)) {
            System.out.println("ERROR, K == J");
            return false;
        }
        if (E.equals(I)) {
            System.out.println("ERROR, E == I");
            return false;
        }
        if (!K.equals(K2)) {
            System.out.println("ERROR, K != K2");
            return false;
        }
        if (!I.equals(I2)) {
            System.out.println("ERROR, I != I2");
            return false;
        }
        if (!B.equals(B2)) {
            System.out.println("ERROR, B != B2");
            return false;
        }
        if (!A.equals(A2)) {
            System.out.println("ERROR, A != A2");
            return false;
        }

        System.out.println("OK");
        return true;
    }

    static boolean testFind() {
        System.out.print("testing find: ");

        BTree<String> empty1 = new LBTree<String>();
        BTree<String> empty2 = new LBTree<String>();
        if (!empty1.find(empty1)) {
            System.out.println("ERROR, ! empty1.find(empty1)");
            return false;
        }
        if (!empty1.find(empty2)) {
            System.out.println("ERROR, ! empty1.find(empty2)");
            return false;
        }
        buildTestTree();
        if (empty1.find(K)) {
            System.out.println("ERROR, empty1.find(K)");
            return false;
        }
        if (empty1.find(A)) {
            System.out.println("ERROR, empty1.find(A)");
            return false;
        }
        if (!K.find(empty1)) {
            System.out.println("ERROR, ! K.find(empty1)");
            return false;
        }
        if (!A.find(empty1)) {
            System.out.println("ERROR, ! A.find(empty1)");
            return false;
        }
        if (!K.find(K)) {
            System.out.println("ERROR, ! K.find(K)");
            return false;
        }
        if (K.find(J)) {
            System.out.println("ERROR, K.find(J)");
            return false;
        }
        if (!E.find(I)) {
            System.out.println("ERROR, ! E.find(I)");
            return false;
        }
        if (!K.find(K2)) {
            System.out.println("ERROR, ! K.find(K2)");
            return false;
        }
        if (!I.find(I2)) {
            System.out.println("ERROR, ! I.find(I2)");
            return false;
        }
        if (!B.find(B2)) {
            System.out.println("ERROR, ! B.find(B2)");
            return false;
        }
        if (!A.find(A2)) {
            System.out.println("ERROR, ! A.find(A2)");
            return false;
        }
        if (!A.find(G2)) {
            System.out.println("ERROR, ! A.find(A2)");
            return false;
        }

        // remove H2
        try {
            G.extract(BTree.LEFT);
        } catch (Exception e) {
            System.out.println("ERROR, caught exception:");
            e.printStackTrace();
            return false;
        }
        if (A.find(G2)) {
            System.out.println("ERROR, A.find(G2) after extracting H2");
            return false;
        }
        if (A.find(E2)) {
            System.out.println("ERROR, A.find(E2) after extracting H2");
            return false;
        }
        if (!A.find(I2)) {
            System.out.println("ERROR, ! A.find(E2) after extracting H2");
            return false;
        }

        System.out.println("OK");
        return true;
    }

    public static void main(String args[]) {

        testIsEmpty();
        testGetInfo();
        testInsert();
        testGetLeft();
        testGetRight();
        testExtract();
        testToStringPreOrder();
        testToStringInOrder();
        testToStringPostOrder();
        testToString();
        testSize();
        testHeight();
        testEquals();
        testFind();
    }
}