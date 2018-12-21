//
// Created by Anmol Uppal on 2018-12-08.
//

#ifndef DSVISUAL_BINARYTREENODE_H
#define DSVISUAL_BINARYTREENODE_H

#include <string>

class BinaryTreeNode {
public:
    virtual std::string getData() const = 0;

    virtual BinaryTreeNode *getRight() const = 0;

    virtual BinaryTreeNode *getLeft() const = 0;

    virtual int getHeight() const {
        return -1;
    }

    virtual bool isNodeBlack() const {
        return true;
    }
};

#endif //DSVISUAL_BINARYTREENODE_H
