#include "DataTxtValidator.hpp"

#include "Filters.hpp"

namespace Tools {

using namespace Standard;
using namespace CommandLine;

DataTxtValidator::DataTxtValidator()
    : Editor::Tool("DataTxtValidator") {}

DataTxtValidator::~DataTxtValidator() {}

void DataTxtValidator::run(const std::vector<std::shared_ptr<Option>>& arguments) {
    if (arguments.size() < 1) {
        StringBuffer sb;
        sb << "wrong number of arguments" << EndOfLine;
        throw RuntimeError(sb.str());
    }

    std::deque<std::string> queue;
    RegexFilter filter("^(?:.*" REGEX_DIRSEP ")?data\\.txt");
    /// @todo Do *not* assume the path is relative. Ensure that it is absolute by a system function.
    for (const auto& argument : arguments) {
        if (argument->getType() != Option::Type::UnnamedValue) {
            StringBuffer sb;
            sb << "unrecognized argument" << EndOfLine;
            throw std::runtime_error(sb.str());
        }
        auto pathnameArgument = std::static_pointer_cast<UnnamedValue>(argument);
        queue.emplace_back(FileSystem::sanitize(pathnameArgument->getValue()));
    }
    while (!queue.empty()) {
        std::string path = queue[0];
        queue.pop_front();
        switch (FileSystem::stat(path)) {
            case FileSystem::PathStat::File:
                if (filter(path)) {
                    validate(path);
                }
                break;
            case FileSystem::PathStat::Directory:
                FileSystem::recurDir(path, queue);
                break;
            case FileSystem::PathStat::Failure:
                break; // stat complains
            default:
            {
                StringBuffer sb;
                sb << "skipping '" << path << "' - not a file or directory" << EndOfLine;
                std::cerr << sb.str();
            }
        }
    }
}

const std::string& DataTxtValidator::getHelp() const {
    static const std::string help = "usage: ego-tools --tool=DataTxtValidator <directories>\n";
    return help;
}

void DataTxtValidator::validate(const std::string& pathname) {
}

} // namespace Tools
