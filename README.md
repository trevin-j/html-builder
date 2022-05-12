# html-builder

A header-only C++ library for building a simple HTML document.

See main.cpp in the src directory for an example.


## Installation

Installation is simple, just include the header file in your project!

```cpp
#include "html_builder.h"
```


## Compiling example

### If you know what you're doing:

Use CMake to generate the buildsystem for compiling the example project.

### Otherwise:

Just create a new project in your favorite IDE, add the `main.cpp` and `html_builder.h` files, and compile it.


## Usage

This library comes with 2 classes: `HTMLBuilder` and `Element`. Both reside under the `HTML` namespace. You will need to use both classes to create your HTML document.


### Creating a document

```cpp
#include "html_builder.h"

int main()
{
    HTML::HTMLBuilder builder;
}
```

Optionally, you may specify the style of indentation like so:

```cpp
HTML::HTMLBuilder builder("    ");
```
...or...
```cpp
HTML::HTMLBuilder builder('\t');
```

You may use as many tabs or spaces as you desire. You may use any other character if that is your wish, but you are held responsible if the output is not valid HTML.

When a document is created, it automatically adds the `<!DOCTYPE html>` tag, as well as the `<html>` and `</html>` tags.


### Adding elements and attributes

The suggested way of adding elements is to create the element objects for head and body and then add them to the document via `builder.addTag()`. This way you don't have to cram everything together.

There are 2 types of elements: regular tags, and bare text. Bare text is simply text that is not enclosed in a tag. Its intended use is to be the child of a tag such as `<p>` or `<h1>`. 

To create a regular tag, you may use the following syntax:

```cpp
HTML::Element(bool requiresClosingTag, bool isInline, const std::string& tagName);
```

Where `requiresClosingTag` is a boolean that determines whether the tag should be closed with a `</tagName>` tag. `isInline` is a boolean that determines whether the tag should be rendered as an inline tag, like `<em>` or any other tag that is not a block tag. And `tagName` is the name of the tag, such as `p` or `h1`.

To create a bare text element, you may use the following syntax:

```cpp
HTML::Element(const std::string& text);
```

The `text` parameter is the text that will be rendered.

For many HTML tags, you need to add attributes to the tag. For example, to add a `class` attribute with a value of `my-class` to a tag, you may use the following syntax:

```cpp
HTML::Element div(true, true, "div");

div.addAttribute("class", "my-class");
```

The methods of the `Element` class also support method chaining. This allows us to be more concise when adding attributes or child elements.

```cpp
div.addAttribute("class", "my-class").addAttribute("id", "my-id");
```

To add child tags, use the `HTML::Element::addChild()` method.

```cpp
div.addChild
(
    HTML::Element(true, false, "p")
        .addAttribute("class", "normal-paragraph")

        // Add text to the paragraph
        .addChild(HTML::Element("This is a normal paragraph."))
)
.addChild
(
    HTML::Element(true, false, "p")
        .addAttribute("class", "important-paragraph")
        .addChild(HTML::Element("This is an important paragraph."))
);
```

### Retrieving HTML output

Get a string containing the whole HTML document, fully formatted, and without extra whitespace by `HTML::HTMLBuilder::toString()`.
