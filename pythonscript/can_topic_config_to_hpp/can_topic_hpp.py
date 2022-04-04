import os
import sys
import json
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"


def toHpp(up_config,down_config,hppConfig):
    ucr = open(up_config,'r')
    upJsConfig =  json.load(ucr)

    dcr = open(down_config,'r')
    downJsConfig =  json.load(dcr)
    contents = []
    contents.append('#pragma once')
    contents.append('#include <string>')
    contents.append('#include <unordered_map>')
    contents.append('')
    contents.append('namespace fds\n\
{')

    contents.append('    std::unordered_map<std::string,std::string> getSigNameTopic()\n\
    {\n\
        static std::unordered_map<std::string,std::string> content;\n\
        if(!content.empty()) return content;')
    for sig in upJsConfig:
        contents.append('        content[\"{}\"] = \"{}\";'.format(sig,upJsConfig[sig]))
    contents.append('        return content;')
    contents.append('    }\n')

    contents.append('    std::unordered_map<std::string,std::string> getTopicSigName()\n\
    {\n\
        static std::unordered_map<std::string,std::string> content;\n\
        if(!content.empty()) return content;')

    for sig in downJsConfig:
        contents.append('        content[\"{}\"] = \"{}\";'.format(sig,downJsConfig[sig]))
    contents.append('        return content;')
    contents.append('    }\n')
    
    contents.append('}')

    fw = open(hppConfig, "w")
    fw.writelines('\n'.join(contents))
    fw.close()
    ucr.close()
    dcr.close()

if __name__ == "__main__":
    toHpp(pyFileDir+"up_config.json",pyFileDir+"down_config.json",sys.argv[1])
