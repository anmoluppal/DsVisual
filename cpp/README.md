## Build
```sh
$ mkdir build && cd build
$ cmake ..
$ make && make install
```

Link the `DsVisual` library in your project and include
`DsVisual/visualize/DsVisual.h` file.

## Integrating with your code.

Suppose you are building AVL Tree implementation as:

```cpp
class MyAvlTree{
    class MyNode: public AvlTreeNode {
        int data;
        // ...

        std::string getData() const override { return std::to_string(data); }

        AvlTreeNode* getLeft() const override { return left; }

        AvlTreeNode* getRight() const override { return right; }
    }

public:
    void insert(int data);
    // ...

    AvlTreeNode* getRoot() { return root; }

}
```

Now in your `main.cpp`, visualize the DS as:

```cpp
int main() {
    AvlTree binTree;
    std::vector<uint32_t> values = {4, 3, 5, 7, 8, 10, 6, 2, 9, 1, 11, 12};
    for (uint32_t v:values) {
        binTree.insert(v);
    }

    DsVisual::visualize(binTree.getRoot(), "/path/to/debug.png");
}
```

