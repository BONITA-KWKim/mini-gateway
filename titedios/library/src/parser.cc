#include "parser.h"

inline std::string rtrim (std::string s, const std::string& drop = " ")
{
    return s.erase(s.find_last_not_of(drop)+1);
}   

std::vector<std::pair<std::string, std::string>> parser (std::string message)
{
    /// tokenizing
    std::vector<std::string> temp_field; 
    std::vector<std::pair<std::string, std::string>> results;

    boost::split(temp_field, message, boost::is_any_of("\n")); 

    /// remove END
    temp_field.pop_back();

	for (auto const & i: temp_field) {
        //boost::algorithm::trim_right_copy_if(i, boost::is_any_of("\r"));
        rtrim(i, "\r");

        std::vector<std::string> tmp;
        boost::split(tmp, i, boost::is_any_of(":"));

        // remove abnormal data
        if (2 != tmp.size())
            continue;

        results.push_back(std::make_pair(tmp[0], tmp[1]));
    }

    return results;
}
