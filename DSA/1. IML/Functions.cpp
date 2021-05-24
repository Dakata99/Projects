

bool member(const std::vector<double> vec, const double number)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i] == number)
        {
            return true;
        }
    }
    return false;
}

void toString(const double result, std::string& data)
{
    std::stringstream s;
    s << result << " ";
    data = s.str();
}
void vectorToString(const std::vector<double> vec, std::string& data)
{
    std::stringstream s;
    for (size_t i = 0; i < vec.size(); i++)
        s << vec[i] << " ";
    
    data = s.str();
}

double AGG_SUM(const std::vector<double> vec)
{
    double result = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        result += vec[i];
    }
    return result;
}
double AGG_PRO(const std::vector<double> vec)
{
    double result = 1;
    for (size_t i = 0; i < vec.size(); i++)
    {
        result *= vec[i];
    }
    return result;
}
double AGG_AVG(const std::vector<double> vec)
{
    return AGG_SUM(vec) / vec.size();
}
std::vector<double> MAP_INC(const double inc, std::vector<double> vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] += inc;
    }
    return vec;
}
std::vector<double> MAP_MLT(const double mul, std::vector<double> vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] *= mul;
    }
    return vec;
}
std::vector<double> SRT_REV(std::vector<double> vec)
{
    std::vector<double> temp;
    for (size_t i = 0; i < vec.size(); i++)
    {
        temp.push_back(vec[vec.size() - 1 - i]);
    }
    return temp;
}
std::vector<double> SRT_ASC(const std::vector<double> vec)
{
    std::vector<double> temp = vec;

    for (size_t i = 0; i < temp.size(); i++)
        for (size_t j = i; j < temp.size(); j++)
            if (temp[i] > temp[j])
                std::swap(temp[i], temp[j]);

    return temp;
}
std::vector<double> SRT_DSC(const std::vector<double> vec)
{
    std::vector<double> temp = vec;

    for (size_t i = 0; i < temp.size(); i++)
        for (size_t j = i; j < temp.size(); j++)
            if (temp[i] < temp[j])
                std::swap(temp[i], temp[j]);

    return temp;
}
std::vector<double> SRT_SLC(const std::vector<double> vec, const size_t index)
{
    std::vector<double> temp;
    for (size_t i = 0; i < vec.size(); i++)
        if (i + 1 > index)
            temp.push_back(vec[i]);

    return temp;
}
std::vector<double> SRT_DST(const std::vector<double> vec)
{
    std::vector<double> temp;
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (!member(temp, vec[i]))
        {
            temp.push_back(vec[i]);
        }
    }
    return temp;
}
void execute(const std::string function, std::vector<double> realData, std::string& data)
{
    if (function == "<AGG-SUM>")
    {
        double result = AGG_SUM(realData);
        toString(result, data);
    }
    else if (function == "<AGG-PRO>")
    {
        double result = AGG_PRO(realData);
        toString(result, data);
    }
    else if (function == "<AGG-AVG>")
    {
        double result = AGG_AVG(realData);
        toString(result, data);
    }
    else if (function == "<AGG-FST>")
    {
        double result = realData[0];
        toString(result, data);
    }
    else if (function == "<AGG-LST>")
    {
        double result = realData[realData.size() - 1];
        toString(result, data);
    }
    else if (function.substr(0, function.find(' ')) == "<MAP-INC")
    {
        double inc = std::stod(extractString(function, '\"', '\"'));
        std::vector<double> temp = MAP_INC(inc, realData);
        
        vectorToString(temp, data);
    }
    else if (function.substr(0, function.find(' ')) == "<MAP-MLT")
    {
        double mul = std::stod(extractString(function, '\"', '\"'));
        std::vector<double> temp = MAP_MLT(mul, realData);
        
        vectorToString(temp, data);
    }
    else if (function == "<SRT-REV>")
    {
        std::vector<double> temp = SRT_REV(realData);
        vectorToString(temp, data);
    }
    else if (function == "<SRT-ORD \"ASC\">")
    {
        std::vector<double> temp = SRT_ASC(realData);
        vectorToString(temp, data);
    }
    else if (function == "<SRT-ORD \"DSC\">")
    {
        std::vector<double> temp = SRT_DSC(realData);
        vectorToString(temp, data);
    }
    else if (function.substr(0, function.find(' ')) == "<SRT-SLC")
    {
        size_t index = std::stoi(extractString(function, '\"', '\"'));
        std::vector<double> temp = SRT_SLC(realData, index);
        vectorToString(temp, data);
    }
    else if (function == "<SRT-DST>")
    {
        std::vector<double> temp = SRT_DST(realData);
        vectorToString(temp, data);
    }
}