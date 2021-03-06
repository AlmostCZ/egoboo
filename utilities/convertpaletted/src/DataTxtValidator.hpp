#pragma once

#include "Tool.hpp"

namespace Tools {

using namespace Standard;

/**
 * @brief Validate <c>data.txt</c> files.
 */
struct DataTxtValidator : public Editor::Tool {

public:
    /**
     * @brief Construct this tool.
     */
    DataTxtValidator();

    /**
     * @brief Destruct this tool.
     */
    virtual ~DataTxtValidator();

    /** @copydoc Tool::run */
    void run(const std::vector<std::shared_ptr<CommandLine::Option>>& arguments) override;

    /** @copydoc Tool:getHelp */
    const std::string& getHelp() const override;

private:
    void validate(const std::string& pathname);

}; // struct DataTxtValidator

struct DataTxtValidatorFactory : Editor::ToolFactory {
    Editor::Tool *create() noexcept override {
        try {
            return new DataTxtValidator();
        } catch (...) {
            return nullptr;
        }
    }
}; // struct DataTxtValidatorFactory


} // namespace Tools
