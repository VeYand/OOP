#include <map>
#include <string>

#ifndef EXPANDTEMPLATE_SRC_EXPANDTEMPLATE_H
#define EXPANDTEMPLATE_SRC_EXPANDTEMPLATE_H

using Replacement = std::map<std::string, std::string>;

std::string ExpandTemplate(const std::string& basicString, const Replacement& params);

#endif // EXPANDTEMPLATE_SRC_EXPANDTEMPLATE_H

