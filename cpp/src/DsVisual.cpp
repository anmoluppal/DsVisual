//
// Created by Anmol Uppal on 17/10/18.
//

#include <fstream>
#include <DsVisual.h>
#include <sstream>

#include "../include/DsVisual.h"

const std::string DsVisual::EXT_PNG = "png";
const std::string DsVisual::EXT_SVG = "svg";

void DsVisual::visualize(BinaryTreeNode *rootNode, const char *outFilePath) {
    std::string dotRepr = "digraph BinaryTree {";
    dotRepr += "\n";

    FILE *outFile = fopen(outFilePath, "w");
    if (!outFile) {
        throw std::runtime_error("Output File path invalid.");
    }

    FileExt outFileExt = getFileExtension(outFilePath);
    if (unknown == outFileExt) {
        throw std::runtime_error("Output format not supported, Try `.png`, `.svg`");
    }

    // start BFS iteration and rendering.
    std::queue<BinaryTreeNode *> nodeList;

    nodeList.push(const_cast<BinaryTreeNode *&&>(rootNode));

    uint8_t numNodeTraversed = 0;
    while (!nodeList.empty() && numNodeTraversed < MAX_NODES_TRAVERSE) {
        auto avlTreeNode = nodeList.front();
        dotRepr += getNodeRepr(avlTreeNode) + "\n";

        BinaryTreeNode *leftNode = avlTreeNode->getLeft();
        BinaryTreeNode *rightNode = avlTreeNode->getRight();

        if (nullptr != leftNode) {
            dotRepr += getLinkRepr(avlTreeNode, leftNode) + "\n";
            nodeList.push(reinterpret_cast<BinaryTreeNode *&&>(leftNode));
        }

        if (nullptr != rightNode) {
            dotRepr += getLinkRepr(avlTreeNode, rightNode) + "\n";
            nodeList.push(reinterpret_cast<BinaryTreeNode *&&>(rightNode));
        }

        nodeList.pop();
        numNodeTraversed++;
    }

    dotRepr += "\n";
    dotRepr += "}";

    renderDotFile(dotRepr, outFilePath, outFileExt);
}

void DsVisual::visualize(NAryTreeNode *rootNode, const char *outFilePath) {
    std::string dotRepr = "digraph NAryTreeNode {";
    dotRepr += "\n";

    FILE *outFile = fopen(outFilePath, "w");
    if (!outFile) {
        throw std::runtime_error("Output File path invalid.");
    }

    FileExt outFileExt = getFileExtension(outFilePath);
    if (unknown == outFileExt) {
        throw std::runtime_error("Output format not supported, Try `.png`, `.svg`");
    }

    // start BFS iteration and rendering.
    std::queue<NAryTreeNode *> nodeList;

    nodeList.push(const_cast<NAryTreeNode *&&>(rootNode));

    uint8_t numNodeTraversed = 0;
    while(!nodeList.empty() && numNodeTraversed < MAX_NODES_TRAVERSE) {
        NAryTreeNode *nAryTreeNode = nodeList.front();
        dotRepr += getNodeRepr(nAryTreeNode) + "\n";

        std::vector<NAryTreeNode *> children = nAryTreeNode->getChildren();

        for (NAryTreeNode *child: children) {
            dotRepr += getLinkRepr(nAryTreeNode, child) + "\n";
            nodeList.push(child);
        }

        nodeList.pop();
        numNodeTraversed++;
    }

    dotRepr += "\n";
    dotRepr += "}";

    renderDotFile(dotRepr, outFilePath, outFileExt);
}

std::string DsVisual::getNodeRepr(const BinaryTreeNode *node) {
    std::string label = node->getData();

    if (node->getHeight() != -1) {
        label += "\nHeight: " + std::to_string(node->getHeight());
    }

    std::string color = "black";
    if (!node->isNodeBlack()) {
        color = "red";
    }

    label = "\"" + label + "\"";
    return "  node_" + getNodeName(node) + " [label = " + label + " color = " + color + "];";
}

std::string DsVisual::getLinkRepr(const BinaryTreeNode *parent, const BinaryTreeNode *child) {
    return "  node_" + getNodeName(parent) + " -> " + "node_" + getNodeName(child) + ";";
}

std::string DsVisual::getNodeRepr(const NAryTreeNode *node) {
    std::string internalRepr;
    for (const std::string &s:node->getData()) {
        internalRepr += (s + " | ");
    }
    internalRepr = "\"" + internalRepr.substr(0, internalRepr.size() - 3) + "\"";

    return "  node_" + getNodeName(node) + " [shape = record label = " + internalRepr + "];";
}

std::string DsVisual::getLinkRepr(const NAryTreeNode *parent, const NAryTreeNode *child) {
    return "  node_" + getNodeName(parent) + " -> " + "node_" + getNodeName(child) + ";";
}

FileExt DsVisual::getFileExtension(const std::string &filePath) {
    size_t position = filePath.find_last_of('.');
    if (position == std::string::npos) {
        return unknown;
    }

    std::string fileExtension = filePath.substr(++position);

    if (fileExtension == EXT_PNG)   { return png; }
    if (fileExtension == EXT_SVG)   { return svg; }

    return unknown;
}

std::string DsVisual::toString(const FileExt fileExt) {
    switch (fileExt) {
        case png:
            return EXT_PNG;
        case svg:
            return EXT_SVG;
        case unknown:
            return "";
    }
    return "";
}

std::string DsVisual::getNodeName(const void *address) {
    std::stringstream ss;
    ss << address;
    return ss.str();
}

void DsVisual::renderDotFile(const std::string &dotRepr, const char *outFilePath, const FileExt &ext) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    std::string tmpDotFilePath = std::tmpnam(nullptr);
#pragma clang diagnostic pop

    std::ofstream tmpOutStream(tmpDotFilePath);
    if (!tmpOutStream.good()) {
        throw std::runtime_error("Unable to create temporary `dot` file.");
    }

    tmpOutStream << dotRepr;
    tmpOutStream.close();

    std::string cmd = "dot -o" + std::string(outFilePath) + " " +
                      "-T" + toString(ext) + " "+
                      tmpDotFilePath;

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() not found.");
    }

    pclose(pipe);
}
