//
// Created by Anmol Uppal on 2018-12-09.
//

#ifndef DSVISUAL_NARYTREENODE_H
#define DSVISUAL_NARYTREENODE_H


#include <string>

class NAryTreeNode {
public:
    virtual std::vector<std::string> getData() const = 0;

    virtual std::vector<NAryTreeNode*> getChildren() const = 0;
};


#endif //DSVISUAL_NARYTREENODE_H
