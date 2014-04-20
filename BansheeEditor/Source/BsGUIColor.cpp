#include "BsGUIColor.h"
#include "BsImageSprite.h"
#include "BsGUIWidget.h"
#include "BsGUISkin.h"
#include "BsSpriteTexture.h"
#include "BsGUILayoutOptions.h"
#include "BsGUIMouseEvent.h"
#include "BsGUIHelper.h"
#include "BsBuiltinResources.h"
#include "CmTexture.h"

namespace BansheeEngine
{
	const float GUIColor::ALPHA_SPLIT_POSITION = 0.75f;

	GUIColor::GUIColor(const String& styleName, const GUILayoutOptions& layoutOptions)
		:GUIElement(styleName, layoutOptions), mColorSprite(nullptr), mAlphaSprite(nullptr)
	{
		mColorSprite = cm_new<ImageSprite, PoolAlloc>();
		mAlphaSprite = cm_new<ImageSprite, PoolAlloc>();

		mColorImageDesc.texture = BuiltinResources::instance().getWhiteSpriteTexture().getInternalPtr();
		mAlphaImageDesc.texture = BuiltinResources::instance().getWhiteSpriteTexture().getInternalPtr();
	}

	GUIColor::~GUIColor()
	{
		cm_delete<PoolAlloc>(mColorSprite);
		cm_delete<PoolAlloc>(mAlphaSprite);
	}

	const String& GUIColor::getGUITypeName()
	{
		static String name = "Color";
		return name;
	}

	GUIColor* GUIColor::create(const String& styleName)
	{
		return new (cm_alloc<GUIColor, PoolAlloc>()) GUIColor(getStyleName<GUIColor>(styleName), GUILayoutOptions::create());
	}

	GUIColor* GUIColor::create(const GUIOptions& layoutOptions, const String& styleName)
	{
		return new (cm_alloc<GUIColor, PoolAlloc>()) GUIColor(getStyleName<GUIColor>(styleName), GUILayoutOptions::create(layoutOptions));
	}

	void GUIColor::setColor(const Color& color)
	{
		mColor = color;

		mColorImageDesc.color = mColor;
		mColorImageDesc.color.a = 1.0f;

		mAlphaImageDesc.color = Color::White * mColor.a;
		mAlphaImageDesc.color.a = 1.0f;

		markContentAsDirty();
	}

	UINT32 GUIColor::getNumRenderElements() const
	{
		UINT32 numElements = mColorSprite->getNumRenderElements();
		numElements += mAlphaSprite->getNumRenderElements();

		return numElements;
	}

	const GUIMaterialInfo& GUIColor::getMaterial(UINT32 renderElementIdx) const
	{
		UINT32 alphaSpriteIdx = mColorSprite->getNumRenderElements();

		if(renderElementIdx >= alphaSpriteIdx)
			return mAlphaSprite->getMaterial(alphaSpriteIdx - renderElementIdx);
		else
			return mColorSprite->getMaterial(renderElementIdx);
	}

	UINT32 GUIColor::getNumQuads(UINT32 renderElementIdx) const
	{
		UINT32 alphaSpriteIdx = mColorSprite->getNumRenderElements();

		UINT32 numQuads = 0;
		if(renderElementIdx >= alphaSpriteIdx)
			numQuads = mAlphaSprite->getNumQuads(alphaSpriteIdx - renderElementIdx);
		else
			numQuads = mColorSprite->getNumQuads(renderElementIdx);

		return numQuads;
	}

	void GUIColor::updateRenderElementsInternal()
	{		
		mColorImageDesc.width = (UINT32)(mWidth * ALPHA_SPLIT_POSITION);
		mColorImageDesc.height = mHeight;

		mAlphaImageDesc.width = mWidth - mColorImageDesc.width;
		mAlphaImageDesc.height = mHeight;

		mColorSprite->update(mColorImageDesc);
		mAlphaSprite->update(mAlphaImageDesc);

		GUIElement::updateRenderElementsInternal();
	}

	void GUIColor::updateClippedBounds()
	{
		mClippedBounds = RectI(0, 0, mWidth, mHeight);

		if(mClipRect.width > 0 && mClipRect.height > 0)
			mClippedBounds.clip(mClipRect);

		mClippedBounds.x += mOffset.x;
		mClippedBounds.y += mOffset.y;
	}

	Vector2I GUIColor::_getOptimalSize() const
	{
		return GUIHelper::calcOptimalContentsSize(Vector2I(80, 10), *_getStyle(), _getLayoutOptions()); // Arbitrary size
	}

	void GUIColor::fillBuffer(UINT8* vertices, UINT8* uv, UINT32* indices, UINT32 startingQuad, UINT32 maxNumQuads, 
		UINT32 vertexStride, UINT32 indexStride, UINT32 renderElementIdx) const
	{
		UINT32 alphaSpriteIdx = mColorSprite->getNumRenderElements();

		if(renderElementIdx < alphaSpriteIdx)
		{
			mColorSprite->fillBuffer(vertices, uv, indices, startingQuad, maxNumQuads, 
				vertexStride, indexStride, renderElementIdx, mOffset, mClipRect);

			return;
		}
		else if(renderElementIdx >= alphaSpriteIdx)
		{
			Vector2I alphaOffset = mOffset;
			UINT32 xOffset = (UINT32)(mWidth * ALPHA_SPLIT_POSITION);
			alphaOffset.x += xOffset;

			RectI alphaClipRect = mClipRect;
			alphaClipRect.x -= xOffset;

			mAlphaSprite->fillBuffer(vertices, uv, indices, startingQuad, maxNumQuads, 
				vertexStride, indexStride, alphaSpriteIdx - renderElementIdx, alphaOffset, alphaClipRect);
		}
	}

	bool GUIColor::mouseEvent(const GUIMouseEvent& ev)
	{
		if(ev.getType() == GUIMouseEventType::MouseUp)
		{
			// TODO

			return true;
		}

		return false;
	}
}