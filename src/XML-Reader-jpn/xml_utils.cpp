#include "xml_utils.h"

const char* getTextFromChildElemWithAttribute(XMLElement* parent, const char* childElemName,
	const char* attrName, const char* attrValue) {
	XMLElement* childElem = parent->FirstChildElement(childElemName);
	while (childElem) {
		if (childElem->Attribute(attrName, attrValue)) {
			return childElem->GetText();
		}
		childElem = childElem->NextSiblingElement(childElemName);
	}
	return NULL;
}