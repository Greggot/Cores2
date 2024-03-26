/**
 * @file
 * @brief  Локальный фрейм с ориентацией и сохраненной матрицей MVP
 * @author https://github.com/Greggot/
 */

#pragma once

#include "geometry/gm_types.hpp"
namespace gm {

class Frame {
public:
    matrix4& model() { return local_orientation; }
    const matrix4& model() const { return local_orientation; }
    const matrix4& mvp() const { return model_view_projection; }

    void set_view_projection(const matrix4& view_projection)
    {
        model_view_projection = view_projection * local_orientation;
    }

private:
    matrix4 local_orientation { 1.0 };
    matrix4 model_view_projection { 1.0 };
};

} // namespace gm