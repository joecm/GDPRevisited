#include "../include/XmlManager.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>

XmlManager::XmlManager()
{
    try
    {
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch(const xercesc::XMLException& toCatch)
    {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Error durante la inicialización! :\n" << message << "\n";
		xercesc::XMLString::release(&message);
		return;
    }
    parser=new xercesc::XercesDOMParser();
    parser->setValidationScheme(xercesc::XercesDOMParser::Val_Always);
    
    xmlDoc=nullptr;
    elementRoot= nullptr;
}

XmlManager::~XmlManager()
{
    xercesc::XMLPlatformUtils::Terminate();
}

char* XmlManager::getAttributeValue(xercesc::DOMNode* node, const XMLCh* attributeTag)
{
    // Acceder a los nodos hijos por sus nombres
    xercesc::DOMNamedNodeMap* attributes = node->getAttributes();
    xercesc::DOMNode* attributeNameNode = attributes->getNamedItem(attributeTag);
    char* attributeValue = NULL;
    attributeValue = xercesc::XMLString::transcode(attributeNameNode->getNodeValue());
    return attributeValue;
}

char* XmlManager::getNodeValue(xercesc::DOMNode*node)
{
    char* nodeValue = NULL;
    nodeValue = xercesc::XMLString::transcode(node->getFirstChild()->getNodeValue());
    return nodeValue;
}

void XmlManager::initParser(const char* xmlPath)
{
    // Parsing xml file
    try
    {
        parser->parse(xmlPath);
    }
    catch(const xercesc::XMLException& toCatch)
    {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
		std::cout << "Excepción capturada: \n"
		<< message << "\n";
		xercesc::XMLString::release(&message);
    }
    
    catch (const xercesc::DOMException& toCatch) {
		char* message = xercesc::XMLString::transcode(toCatch.msg);
		std::cout << "Excepción capturada: \n"
		<< message << "\n";
		xercesc::XMLString::release(&message);
	}
	catch (...) {
		std::cout << "Excepción no esperada.\n" ;
		return;
	}

    try
    {
        // Obtener el elemento raiz del documento
        xmlDoc= parser->getDocument();
        elementRoot = xmlDoc->getDocumentElement();
        if (!elementRoot)
        {
            throw(std::runtime_error("Documento XML vacío."));
        }
    }
    catch(xercesc::XMLException& e)
    {
        char* message = xercesc::XMLString::transcode(e.getMessage());
        std::ostringstream errBuf;
        errBuf << "Error 'parseando': " << message << std::flush;
        xercesc::XMLString::release(&message);
        return;
    }
}

void XmlManager::releaseParser()
{
    delete parser;
}

