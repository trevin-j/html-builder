#ifndef HTML_BUILDER_H
#define HTML_BUILDER_H

#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

namespace HTML
{
    class Element
    {
    public:
        // Construct a tag element.
        // Arguments:
        // 		requiresClosingTag: Bool representing if the tag has both opening and closing tags.
        // 		isInline: Bool representing if the tag is inline or on its own line. This is only for formatting, and doesn't affect the HTML syntax.
        // 		tagName: The type of tag.
        Element(bool requiresClosingTag, bool isInline, const std::string& tagName)
        {
            this->requiresClosingTag = requiresClosingTag;
            this->tagName = tagName;
            this->isInline = isInline;

            elementType = 0;
        }

        // Construct an element only of text. No tags.
        // This is used for putting text between 2 tags of an element.
        // For example, if you have a p tag, and you want to put text between it and the /p tag, you can use this.
        // Arguments:
        //		text: The text.
        Element(const std::string& text)
        {
            this->text = text;

            this->requiresClosingTag = false;
            this->isInline = true;

            elementType = 1;
        }


        // Add an attribute to the tag. Such as id="chapter-heading".
        // If this element is a text element, this method will be ignored.
        // Arguments:
        // 		name: The name of the attribute. E.g. id, class, style, etc.
        // 		value: The value of the attribute. The value that is in quotes in HTML.
        // Returns a reference to this Element, so that methods can be chained.
        Element& addAttribute(const std::string& name, const std::string& value)
        {
            if (elementType == 1)
                return *this;
            
            attributes.push_back(std::pair<std::string, std::string>(name, value));
            return *this;
        }

        // Add a child element to this one. This would be an element within another element, or text within this element.
        // Arguments:
        //		childElement: The child element. Can be text or a tag.
        // Returns a reference to this element, to support method chaining.
        Element& addChild(const Element& childElement)
        {
            if (!requiresClosingTag)
                throw std::logic_error("Cannot add child to a tag that does not require a closing tag");
            
            children.push_back(childElement);
            return *this;
        }

        // Recursively get a string representing this element including all its child elements, if applicable.
        //		indentLayer: The indentation layer of this element. Used in recursion to get proper indentation.
        // 		tabStyle: The style of indentation. '\t' is a tab, or you can use any number of spaces. HTMLBuilder default is 2 spaces ("  ").
        // Returns the string. This is before unnessesary whitespace is stripped by HTMLBuilder. If you want to retrieve a properly formatted full HTML document, use HTMLBuilder.toString()
        std::string getString(int indentLayer, const std::string& tabStyle) const
        {
            // In case of bare text element, simply return the text
            if (elementType == 1)
            {
                return text;
            }
            
            std::stringstream ss;
            
            if (!isInline)
            {
                ss << '\n';
                for (int i = 0; i < indentLayer; i++)
                    ss << tabStyle;
            }

            ss << '<' << tagName;
            for (auto& attribute : attributes)
            {
                ss << " " << attribute.first << "=\"" << attribute.second << "\"";
            }
            ss << '>';
            
            if (!requiresClosingTag)
            {
                if (!isInline)
                    ss << '\n';
                return ss.str();
            }
            
            for (auto& child : children)
            {
                ss << child.getString(indentLayer + 1, tabStyle);
            }

            ss << '<' << '/' << tagName << '>';
            
            if (!isInline)
            {
                ss << '\n';
                for (int i = 0; i < indentLayer-1; i++)
                    ss << tabStyle;
            }

            return ss.str();
        }

    private:
        // Vector holding all child elements in order.
        std::vector<Element> children;

        // Vector holding all attributes of the tag.		
        std::vector < std::pair<std::string, std::string>> attributes;

        // Bool representing if a closing tag is required.		
        bool requiresClosingTag;
        
        // Bool representing if the tag is inline or on its own line.
        bool isInline;

        // The type of tag.		
        std::string tagName;
        
        // 0 = tag, 1 = bare text
        int elementType;
        
        // For bare text element only
        std::string text;
    };

    // A class used for building HTML documents.
    // Add tags and child tags to build the document.
    // The document has the doctype tag builtin, as well as the html tags.
    // Supply your own head and body tags.	
    class HTMLBuilder
    {
    public:
        // Construct HTMLBuilder with default tab style of 2 spaces.
        HTMLBuilder()
        {
            tabStyle = "  ";
        }

        // Construct HTMLBuilder with a custom tab style.		
        HTMLBuilder(const std::string& tabStyle)
        {
            this->tabStyle = tabStyle;
        }
        
        // Get the full, properly formatted HTML document as a string.
        // Returns a string representing the HTML Document
        std::string toString() const
        {
            std::stringstream ss;

            ss << "<!DOCTYPE html>\n";
            ss << "<html>\n";
            
            for (const Element& tag : tags)
            {
                ss << tag.getString(1, tabStyle);
            }

            ss << "</html>";

            std::string asString = ss.str();
            stripBlankLines(asString);
            return asString;
        }

        // Add a tag to the HTML document.		
        void addTag(const Element& tag) { tags.push_back(tag); }

    private:
        // Vector containing all tags that are children of the html tag,
        // as well as their children, in order.
        std::vector<Element> tags;
        
        // The style of indentation.
        std::string tabStyle;


        // Strip all lines that have nothing other than whitespace on them from the string.
        // Modifies the original string, does not return anything.	
        // Arguments:	
        // 		str: String to remove lines from.
        void stripBlankLines(std::string& str) const
        {
            std::istringstream iss(str);
            
            std::stringstream outss;
            
            // Loop through each line in the string (using string streams)
            // For each line, if it finds a non whitespace character, it copies it to the output stringstream, and continues
            for (std::string line; std::getline(iss, line); )
            {
                bool isBlank = true;
                for (auto& ch : line)
                {
                    // If the char is empty, keep looping
                    if (ch == '\n' || ch == ' ' || ch == '\t' || ch == '\r')
                        continue;
                    // Otherwise, the line isn't blank so break
                    isBlank = false;
                    break;
                }
                if (!isBlank)
                    outss << line << '\n';
            }
            
            str = outss.str();
        }
    };
}

#endif
