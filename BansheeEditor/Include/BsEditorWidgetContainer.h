#pragma once

#include "BsEditorPrerequisites.h"
#include <boost/signal.hpp>

namespace BansheeEngine
{
	class BS_ED_EXPORT EditorWidgetContainer
	{
	public:
		EditorWidgetContainer(GUIWidget* parent, RenderWindow* renderWindow, EditorWindow* parentEditorWindow);
		virtual ~EditorWidgetContainer();

		void add(EditorWidgetBase& widget);
		void remove(EditorWidgetBase& widget);
		void insert(UINT32 idx, EditorWidgetBase& widget);
		bool contains(EditorWidgetBase& widget);

		void setSize(UINT32 width, UINT32 height);
		void setPosition(INT32 x, INT32 y);

		UINT32 getNumWidgets() const { return (UINT32)mWidgets.size(); }
		EditorWidgetBase* getWidget(UINT32 idx) const;
		GUIWidget& getParentWidget() const { return *mParent; }
		EditorWindow* getParentWindow() const { return mParentWindow; }

		RectI getContentBounds() const;
		Vector<RectI>::type getDraggableAreas() const;

		void _notifyWidgetDestroyed(EditorWidgetBase* widget);

		boost::signal<void()> onWidgetClosed;
	private:
		EditorWindow* mParentWindow;
		GUITabbedTitleBar* mTitleBar;
		GUIArea* mTitleBarArea;
		GUIWidget* mParent;
		INT32 mX, mY;
		UINT32 mWidth, mHeight;
		UnorderedMap<UINT32, EditorWidgetBase*>::type mWidgets;
		INT32 mActiveWidget;

		static const UINT32 TitleBarHeight;

		void removeInternal(EditorWidgetBase& widget);

		void setActiveWidget(UINT32 idx);
		void tabActivated(UINT32 idx);
		void tabClosed(UINT32 idx);
		void tabDraggedOff(UINT32 idx);
		void tabDraggedOn(UINT32 idx);

		static void tabDroppedCallback(bool wasDragProcessed);
	};
}