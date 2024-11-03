#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>


class XmlManager
{
public:
    XmlManager();
    ~XmlManager();
    XmlManager(const XmlManager&) = delete;
    XmlManager& operator= (const XmlManager&) = delete;
    char* getAttributeValue(xercesc::DOMNode* node, const XMLCh* attributeName);
    char* getNodeValue(xercesc::DOMNode*node);
    
protected:
    void initParser(const char* xmlPath);
    xercesc::XercesDOMParser* parser;
    xercesc::DOMDocument* xmlDoc;
    xercesc::DOMElement* elementRoot;
    void releaseParser();

};

#endif