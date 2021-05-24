std::stack<std::string> getTags(std::string line)
{
    std::stack<std::string> tags;
    while (line != "")
    {
        std::string tag = extractString(line, "<", ">");
        tags.push(tag);
        line = line.erase(0, tag.size());
        line = line.erase(0, line.find('<'));   
    }
    return tags;
}
// void setTags(std::stack<std::string>& tags, std::stack<std::string>& openTags, std::stack<std::string>& closeTags)
// {
// while (!tags.empty())
    // {
    //     if (tags.top().find("</"))
    //         openTags.push(tags.top());
    //     else
    //         closeTags.push(tags.top());
        
    //     tags.pop();
    // }
// }
std::stack<std::string> reverseTags(std::stack<std::string>& tags)
{
    std::stack<std::string> res;
    while (!tags.empty())
    {
        res.push(tags.top());
        tags.pop();
    }
    
    return res;
}
