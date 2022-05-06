#include <iostream>

#include "html_builder.h"

using namespace HTML;

int main()
{
    // Build the document
    // Note: the <!DOCTYPE> tag is builtin, as well as the <html> tag
    HTMLBuilder builder;


    // Create head tag and populate it
    Element head(true, false, "head");

    // Add meta charset tag
    head.addChild(
        Element(false, false, "meta")
            .addAttribute("charset", "utf-8")
    );

    // Add title tag that looks like: <title>Example Page | HTML Builder</title>
    head.addChild(
        Element(true, false, "title")
            .addChild(Element("Example Page | HTML Builder"))
    );

    // Add the head to the document
    builder.addTag(head);


    // Create the body tag and populate it
    Element body(true, false, "body");

    // Add a header with an id of "welcome-header"
    body.addChild(
        Element(true, false, "h1")
            .addAttribute("id", "welcome-header")
            .addChild(Element("Welcome to the HTML Builder!"))
    );

    // Add a paragraph with an id of "welcome-paragraph", and red text
    // As you can see here, you can add an inline tag for something such as <em></em>...
    body.addChild(
        Element(true, false, "p")
            .addAttribute("id", "welcome-paragraph")
            .addAttribute("style", "color: red")
            .addChild(Element("This is a paragraph. A "))
            .addChild(Element(true, true, "em")
                .addChild(Element("RED")))
            .addChild(Element(" paragraph."))
    );

    // ... or you can inject the tag directly into the text.
    body.addChild(
        Element(true, false, "p")
            .addAttribute("id", "welcome-paragraph-2")
            .addChild(Element("The word strong is <strong>strong</strong>."))
    );

    // Add a list with an id of "welcome-list"
    body.addChild(
        Element(true, false, "ul")
            .addAttribute("id", "welcome-list")
            .addChild(Element(true, false, "li")
                .addChild(Element("List item 1")))
            .addChild(Element(true, false, "li")
                .addChild(Element("List item 2")))
            .addChild(Element(true, false, "li")
                .addChild(Element("List item 3")))
    );

    // Add the body tag to the document
    builder.addTag(body);

    // The HTML document is now complete! It can be printed, written to a file, whatever you desire.

    // Print the document
    std::cout << builder.toString() << std::endl;
}