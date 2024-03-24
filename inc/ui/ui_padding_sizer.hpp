/**
 * @file
 * @brief Объект layout, который будет автоматически менять размер виджетов
 * @author https://github.com/Greggot/
 */

#pragma once
#include <wx/sizer.h>
#include <wx/window.h>

namespace ui {

/// @brief Объект layout, который будет автоматически менять размер виджетов
class Padding_sizer : public wxBoxSizer {
public:
    Padding_sizer(int pad, const std::vector<wxWindow*>& elements = {}, wxOrientation ori = wxHORIZONTAL):
        wxBoxSizer(ori), pad(pad)
    {
        Init(elements);
    }

    Padding_sizer(int pad, const std::vector<wxSizer*>& elements = {}, wxOrientation ori = wxHORIZONTAL):
        wxBoxSizer(ori), pad(pad)
    {
        Init(elements);
    }

    Padding_sizer(int pad, wxOrientation ori = wxHORIZONTAL):
        wxBoxSizer(ori), pad(pad)
    {
        AddSpacer(pad);
    }

    template <class UI_t>
    void AddStatic(UI_t win)
    {
        Add(win, 0);
        AddSpacer(pad);
    }

    template <class UI_t>
    void AddNonStretched(UI_t win)
    {
        Add(win, 0, wxEXPAND);
        AddSpacer(pad);
    }

    template <class UI_t>
    void AddStretched(UI_t win)
    {
        Add(win, 1, wxEXPAND);
        AddSpacer(pad);
    }

private:
    int pad;

    template <class UI_t>
    void Init(const std::vector<UI_t>& elements)
    {
        AddSpacer(pad);
        if (elements.size() == 0)
            return;

        AddStatic(*elements.begin());
        if (elements.size() == 1)
            return;

        for (auto win = elements.begin() + 1; win != elements.end(); ++win)
            AddStretched(*win);
    }
};

} // namespace ui
