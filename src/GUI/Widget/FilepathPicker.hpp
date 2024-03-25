#pragma once

#include <string>

class GUIwidget_FilepathPicker {
public:
    GUIwidget_FilepathPicker(const char* fileFilter);
    ~GUIwidget_FilepathPicker() = default;

    void                      ShowOpenfilename();
    void                      ShowSavefilename();
    inline const std::string& getFilepath() const { return m_filepath; }
    inline void               setFilepath(const std::string& filepath) { m_filepath = filepath; }

private:
    std::string m_filepath;
    const char* m_fileFilter;
};