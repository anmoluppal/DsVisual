//
// Created by Anmol Uppal on 17/10/18.
//

#ifndef DSVISUAL_CPP_DSVISUAL_H
#define DSVISUAL_CPP_DSVISUAL_H


#include <queue>
#include <string>
#include <memory>
#include <iostream>
#include <dsElement/BinaryTreeNode.h>
#include <dsElement/NAryTreeNode.h>

enum FileExt {
    png, svg, unknown
};

class DsVisual {
public:
    static void visualize(BinaryTreeNode *node, const char *outFilePath);

    static void visualize(NAryTreeNode *node, const char *outFilePath);
private:
    static const std::string EXT_PNG;
    static const std::string EXT_SVG;
    static const int MAX_NODES_TRAVERSE = 128;

    static std::string getNodeRepr(const BinaryTreeNode *node);

    static std::string getLinkRepr(const BinaryTreeNode *parent, const BinaryTreeNode *child);

    static std::string getNodeRepr(const NAryTreeNode *node);

    static std::string getLinkRepr(const NAryTreeNode *parent, const NAryTreeNode *child);

    static FileExt getFileExtension(const std::string &filePath);

    static std::string toString(FileExt fileExt);

    static std::string getNodeName(const void *address);

    static void renderDotFile(const std::string &dotRepr, const char *outFilePath, const FileExt &ext);
};


#endif //DSVISUAL_CPP_DSVISUAL_H
