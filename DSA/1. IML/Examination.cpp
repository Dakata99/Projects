bool isInteger(const std::string arg)
{
    for (size_t i = 0; i < arg.size(); i++)
        if (!(arg[i] >= '0' && arg[i] <= '9'))
            return false;
        
    return true;
}
bool isNumber(const std::string arg)
{
    size_t counter = 0;
    for (size_t i = 0; i < arg.size(); i++)
        if (arg[i] == '.')
            counter++;

    if (arg[0] == '.' || arg[arg.size() - 1] == '.' || counter > 1)
        return false;

    if (counter == 1)
        if (arg[0] == '-')
            return isInteger(arg.substr(1, arg.find('.'))) && isInteger(arg.substr(arg.find('.') + 1, arg.size()));
        else
            return isInteger(arg.substr(0, arg.find('.'))) && isInteger(arg.substr(arg.find('.') + 1, arg.size()));

    if(arg[0] == '-')
        return isInteger(arg.substr(1, arg.size()));

    return isInteger(arg);
}
bool checkArgument(const std::string openTag)
{
    std::string argument = extractString(openTag, '\"', '\"');
    if (argument == "ASC" || argument == "DSC" || isNumber(argument))
        return true;

    return false;
}
std::string opposite(const std::string openTag)
{
    if (openTag == "<MAP-INC")
    {
        return "</MAP-INC>";
    }
    else if (openTag == "<MAP-MLT")
    {
        return "</MAP-MLT>";
    }
    else if (openTag == "<AGG-SUM>")
    {
        return "</AGG-SUM>";
    }
    else if (openTag == "<AGG-PRO>")
    {
        return "</AGG-PRO>";
    }
    else if (openTag == "<AGG-AVG>")
    {
        return "</AGG-AVG>";
    }
    else if (openTag == "<AGG-FST>")
    {
        return "</AGG-FST>";
    }
    else if (openTag == "<AGG-LST>")
    {
        return "</AGG-LST>";
    }
    else if (openTag == "<SRT-REV>")
    {
        return "</SRT-REV>";
    }
    else if (openTag == "<STR-ORD \"ASC\">")
    {
        return "</SRT-ORD>";
    }
    else if (openTag == "<STR-ORD \"DSC\">")
    {
        return "</SRT-ORD>";
    }
    else if (openTag == "<STR-SLC")
    {
        return "</SRT-SLC>";
    }
    else if (openTag == "<STR-DST>")
    {
        return "</SRT-DST>";
    }

    return "Invalid tag!\n";
}
bool checkTag(const std::string tag)
{
    if ((tag.substr(0, tag.find(' ')) == "<MAP-INC" && checkArgument(tag)) || (tag.substr(0, tag.find(' ')) == "<MAP-MLT" && checkArgument(tag)))
    {
        return true;
    }
    else if (tag == "<AGG-SUM>" || tag == "<AGG-PRO>" || tag == "<AGG-AVG>" || tag == "<AGG-FST>" || tag == "<AGG-LST>")
    {
        return true;
    }
    else if (tag == "<SRT-REV>" || tag == "<SRT-ORD \"ASC\">" || tag == "<SRT-ORD \"DSC\">" || (tag.substr(0, tag.find(' ')) == "<SRT-SLC" && checkArgument(tag)) || tag == "<SRT-DST>")
    {
        return true;
    }
    else if (tag == "</MAP-INC>" || tag == "</MAP-MLT>")
    {
        return true;
    }
    else if (tag == "</AGG-SUM>" || tag == "</AGG-PRO>" || tag == "</AGG-AVG>" || tag == "</AGG-FST>" || tag == "</AGG-LST>")
    {
        return true;
    }
    else if (tag == "</SRT-REV>" || tag == "</SRT-ORD>" || tag == "</SRT-SLC>" || tag == "</SRT-DST>")
    {
        return true;
    }
    
    return false;
}

bool examine(std::stack<std::string> tags)
{
    static size_t index = 1;
    bool flag = true;
    while (!tags.empty())
    {
        if (!checkTag(tags.top()))
        {    
            std::cout << index++ << ". Invalid tag - " << tags.top() << std::endl; 
            flag = false;
        }

        tags.pop();
    }

    return flag;
}