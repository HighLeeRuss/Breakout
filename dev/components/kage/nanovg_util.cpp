#include "..\..\sdk\include\kage\nanovg_util.h"
////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "nanovg_util.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "kage/nanovg_gl.h"

NVGcontext* nvgInit()
{
	glfwInit();
	glewInit();
	NVGcontext *vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

	nvgCreateFont(vg, "font", "data/bluehigh.ttf");
	return vg;
}

void nvgBeginFrame(NVGcontext* ctx, const kf::Vec2i& size, float devicePixelRatio)
{
	nvgBeginFrame(ctx, size.x, size.y, devicePixelRatio);
}

void nvgTranslate(NVGcontext* ctx, const kf::Vec2& offset)
{
	nvgTranslate(ctx, offset.x, offset.y);
}

void nvgScale(NVGcontext* ctx, const kf::Vec2& scale)
{
	nvgScale(ctx, scale.x, scale.y);
}

void nvgTransformTranslate(float* dst, const kf::Vec2& offset)
{
	nvgTransformTranslate(dst, offset.x, offset.y);
}

void nvgTransformScale(float* dst, const kf::Vec2& scale)
{
	nvgTransformScale(dst, scale.x, scale.y);
}

kf::Vec2 nvgTransformPoint(const float* xform, const kf::Vec2& source)
{
	kf::Vec2 temp;
	nvgTransformPoint(&temp.x, &temp.y, xform, source.x, source.y);
	return temp;
}

int nvgCreateImageRGBA(NVGcontext* ctx, const kf::Vec2i& size, int imageFlags, const unsigned char* data)
{
	return nvgCreateImageRGBA(ctx,size.x,size.y,imageFlags,data);
}

kf::Vec2i nvgImageSize(NVGcontext* ctx, int image)
{
	kf::Vec2i temp;
	nvgImageSize(ctx, image, &temp.x, &temp.y);
	return temp;
}

NVGpaint nvgLinearGradient(NVGcontext* ctx, const kf::Vec2& start, const kf::Vec2& end, NVGcolor icol, NVGcolor ocol)
{
	return nvgLinearGradient(ctx, start.x, start.y, end.x, end.y, icol, ocol);
}

NVGpaint nvgBoxGradient(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size, float r, float f, NVGcolor icol, NVGcolor ocol)
{
	return nvgBoxGradient(ctx, pos.x, pos.y, size.x, size.y, r, f, icol, ocol);
}

NVGpaint nvgRadialGradient(NVGcontext* ctx, const kf::Vec2& centre, float inr, float outr, NVGcolor icol, NVGcolor ocol)
{
	return nvgRadialGradient(ctx, centre.x, centre.y, inr, outr, icol, ocol);
}

NVGpaint nvgImagePattern(NVGcontext* ctx, const kf::Vec2& o, const kf::Vec2& e, float angle, int image, float alpha)
{

	return nvgImagePattern(ctx, o.x, o.y, e.x, e.y, angle, image, alpha);
}

void nvgScissor(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size)
{
	nvgScissor(ctx, pos.x, pos.y, size.x, size.y);
}

void nvgIntersectScissor(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size)
{
	nvgIntersectScissor(ctx, pos.x, pos.y, size.x, size.y);
}

void nvgMoveTo(NVGcontext* ctx, const kf::Vec2& pos)
{
	nvgMoveTo(ctx, pos.x, pos.y);
}

void nvgLineTo(NVGcontext* ctx, const kf::Vec2& pos)
{
	nvgLineTo(ctx, pos.x, pos.y);
}

void nvgBezierTo(NVGcontext* ctx, const kf::Vec2& c1, const kf::Vec2& c2, const kf::Vec2& pos)
{
	nvgBezierTo(ctx, c1.x, c1.y, c2.x, c2.y, pos.x, pos.y);
}

void nvgQuadTo(NVGcontext* ctx, const kf::Vec2& c, const kf::Vec2& pos)
{
	nvgQuadTo(ctx, c.x, c.y, pos.x, pos.y);
}

void nvgArcTo(NVGcontext* ctx, const kf::Vec2& pos1, const kf::Vec2& pos2, float radius)
{
	nvgArcTo(ctx, pos1.x, pos2.y, pos2.x, pos2.y, radius);
}

void nvgArc(NVGcontext* ctx, const kf::Vec2& centre, float r, float a0, float a1, int dir)
{
	nvgArc(ctx, centre.x, centre.y, r, a0, a1, dir);
}

void nvgRect(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size)
{
	nvgRect(ctx, pos.x, pos.y, size.x, size.y);
}

void nvgRoundedRect(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size, float r)
{
	nvgRoundedRect(ctx, pos.x, pos.y, size.x, size.y, r);
}

void nvgRoundedRectVarying(NVGcontext* ctx, const kf::Vec2& pos, const kf::Vec2& size, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft)
{
	nvgRoundedRectVarying(ctx, pos.x, pos.y, size.x, size.y, radTopLeft, radTopRight, radBottomRight, radBottomLeft);
}

void nvgEllipse(NVGcontext* ctx, const kf::Vec2& centre, const kf::Vec2& radius)
{
	nvgEllipse(ctx, centre.x, centre.y, radius.x, radius.y);
}

void nvgCircle(NVGcontext* ctx, const kf::Vec2& centre, float r)
{
	nvgCircle(ctx, centre.x, centre.y, r);
}

float nvgText(NVGcontext* ctx, const kf::Vec2& pos, const char* string, const char* end)
{
	return nvgText(ctx, pos.x, pos.y, string, end);
}

void nvgTextBox(NVGcontext* ctx, const kf::Vec2& pos, float breakRowWidth, const char* string, const char* end)
{
	nvgTextBox(ctx, pos.x, pos.y, breakRowWidth, string, end);
}

float nvgTextBounds(NVGcontext* ctx, const kf::Vec2& pos, const char* string, const char* end, float* bounds)
{
	return nvgTextBounds(ctx, pos.x, pos.y, string, end, bounds);
}

void nvgTextBoxBounds(NVGcontext* ctx, const kf::Vec2& pos, float breakRowWidth, const char* string, const char* end, float* bounds)
{
	nvgTextBoxBounds(ctx, pos.x, pos.y, breakRowWidth, string, end, bounds);
}

int nvgTextGlyphPositions(NVGcontext* ctx, const kf::Vec2& pos, const char* string, const char* end, NVGglyphPosition* positions, int maxPositions)
{
	return nvgTextGlyphPositions(ctx, pos.x, pos.y, string, end, positions, maxPositions);
}

void nvgTranslate(NVGcontext* ctx, const kf::Vec2i& offset)
{
	nvgTranslate(ctx, offset.x, offset.y);
}
