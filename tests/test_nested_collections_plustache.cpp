#include <string>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include <plustache/plustache.hpp>

// The fixture for testing class Foo.
class NestedCollectionsTest : public ::testing::Test
{
 protected:
    NestedCollectionsTest()
    {
    }

    virtual ~NestedCollectionsTest()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};

TEST_F(NestedCollectionsTest, TestCollectionMultiLine)
{
    Plustache::Context ctx;
    ctx.add("me", "Daniel");
    
    Plustache::Object tom;
    tom["name"] = "Tom";
    tom["work"] = "Accounting";
    Plustache::Collection tomHobbies;
    tomHobbies.push_back("golf");
    tomHobbies.push_back("knitting");
    tom["hobbies"] = tomHobbies;
    ctx.add("people", tom);
    
    Plustache::Object jerry;
    jerry["name"] = "Jerry";
    jerry["work"] = "Magic";
    Plustache::Collection jerryHobbies;
    jerryHobbies.push_back("golf");
    jerryHobbies.push_back("knitting");
    jerry["hobbies"] = jerryHobbies;
    ctx.add("people", jerry);

    std::string tmplate =
R"---tmplate---(
Hi! I am {{me}}.
{{#people}}
Hello, {{me}}; I am {{name}}, and I do {{work}}.
{{/people}}

*crickets*
)---tmplate---";

    std::string expected =
R"---expected---(
Hi! I am Daniel.
Hello, Daniel; I am Tom, and I do Accounting.
Hello, Daniel; I am Jerry, and I do Magic.

*crickets*
)---expected---";

    Plustache::template_t t;
    std::string actual = t.render(tmplate, ctx);
    
    EXPECT_EQ(expected, actual);
}

TEST_F(NestedCollectionsTest, TestCollectionMultiLineConditionals)
{
    Plustache::Context ctx;
    ctx.add("me", "Daniel");
    
    Plustache::Object tom;
    tom["name"] = "Tom";
    tom["work"] = "Accounting";
    tom["surprise"] = "false";
    ctx.add("people", tom);
    
    Plustache::Object jerry;
    jerry["name"] = "Jerry";
    jerry["work"] = "Magic";
    jerry["surprise"] = "true";
    ctx.add("people", jerry);

    std::string tmplate =
R"---tmplate---(
Hi! I am {{me}}.
{{#people}}
Hello, {{me}}; I am {{name}}, and I do {{work}}.
{{#surprise}}
*{{name}} disappears in a flash of light and smoke*
{{/surprise}}
{{/people}}

*crickets*
)---tmplate---";

    std::string expected =
R"---expected---(
Hi! I am Daniel.
Hello, Daniel; I am Tom, and I do Accounting.
Hello, Daniel; I am Jerry, and I do Magic.
*Jerry disappears in a flash of light and smoke*

*crickets*
)---expected---";

    Plustache::template_t t;
    std::string actual = t.render(tmplate, ctx);
    
    EXPECT_EQ(expected, actual);
}
