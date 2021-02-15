////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_NANOVG_UTIL_HEADER
#define KAGE_NANOVG_UTIL_HEADER
#include <GL/glew.h>
//#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include "kage/nanovg.h"
#include "kf/kf_vector.h"

NVGcontext* nvgInit();

void nvgBeginFrame(NVGcontext* ctx, const kf::Vec2i& size, float devicePixelRatio);
void nvgTranslate(NVGcontext* ctx, const kf::Vec2& offset);
void nvgScale(NVGcontext* ctx, const kf::Vec2& scale);
void nvgTransformTranslate(float* dst, const kf::Vec2& offset);
void nvgTransformScale(float* dst, const kf::Vec2& scale);
kf::Vec2 nvgTransformPoint(const float* xform, const kf::Vec2& source);
int nvgCreateImageRGBA(NVGcontext* ctx, const kf::Vec2i& size, int imageFlags, const unsigned char* data);
kf::Vec2i nvgImageSize(NVGcontext* ctx, int image);
NVGpaint nvgLinearGradient(NVGcontext* ctx, const kf::Vec2& start, const kf::Vec2& end, NVGcolor icol, NVGcolor ocol);
NVGpaint nvgBoxGradient(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size, float r, float f, NVGcolor icol, NVGcolor ocol);
NVGpaint nvgRadialGradient(NVGcontext* ctx, const kf::Vec2& centre, float inr, float outr, NVGcolor icol, NVGcolor ocol);
NVGpaint nvgImagePattern(NVGcontext* ctx, const kf::Vec2& o, const kf::Vec2& e, float angle, int image, float alpha);
void nvgScissor(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size);
void nvgIntersectScissor(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size);
void nvgMoveTo(NVGcontext* ctx, const kf::Vec2& pos);
void nvgLineTo(NVGcontext* ctx, const kf::Vec2& pos);
void nvgBezierTo(NVGcontext* ctx, const kf::Vec2& c1, const kf::Vec2& c2, const kf::Vec2& pos);
void nvgQuadTo(NVGcontext* ctx, const kf::Vec2& c, const kf::Vec2& pos);
void nvgArcTo(NVGcontext* ctx, const kf::Vec2& pos1, const kf::Vec2& pos2, float radius);
void nvgArc(NVGcontext* ctx, const kf::Vec2& centre, float r, float a0, float a1, int dir);
void nvgRect(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size);
void nvgRoundedRect(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size, float r);
void nvgRoundedRectVarying(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft);
void nvgEllipse(NVGcontext* ctx, const kf::Vec2& centre, const kf::Vec2& radius);
void nvgCircle(NVGcontext* ctx, const kf::Vec2& centre, float r);
float nvgText(NVGcontext* ctx, const kf::Vec2& pos, const char* string, const char* end);
void nvgTextBox(NVGcontext* ctx, const kf::Vec2& pos, float breakRowWidth, const char* string, const char* end);
float nvgTextBounds(NVGcontext* ctx, const kf::Vec2& pos, const char* string, const char* end, float* bounds);
void nvgTextBoxBounds(NVGcontext* ctx, const kf::Vec2& pos, float breakRowWidth, const char* string, const char* end, float* bounds);
int nvgTextGlyphPositions(NVGcontext* ctx, const kf::Vec2& pos, const char* string, const char* end, NVGglyphPosition* positions, int maxPositions);

















#endif
