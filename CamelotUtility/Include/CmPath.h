#pragma once

#include "CmPrerequisitesUtil.h"
#include <boost/filesystem.hpp>

namespace BansheeEngine
{
	/**
	 * @brief	Various string manipulations of file paths.
	 */
	class CM_UTILITY_EXPORT Path
	{
	public:
		/**
		 * @brief	Returns file extension extracted from the provided
		 * 			path, with a leading ".".
		 */
		static WString getExtension(const WString& path)
		{
			boost::filesystem3::wpath ext = boost::filesystem3::extension(boost::filesystem3::wpath(path.c_str()));
			return ext.wstring().c_str();
		}

		/**
		 * @brief	Query if a path has the specified extension. Provided
		 * 			extension must contain the leading ".".
		 */
		static bool hasExtension(const WString& path, const WString& extension)
		{
			return getExtension(path) == extension;
		}

		/**
		 * @brief	Replaces or adds an extension on a file path. Provided
		 * 			extension must contain the leading ".".
		 */
		static void replaceExtension(WString& path, const WString& newExtension)
		{
			boost::filesystem3::path internalPath = path.c_str();

			path = internalPath.replace_extension(newExtension.c_str()).c_str();
		}

		/**
		 * @brief	Returns a path that is one level higher than the provided path, unless the path
		 * 			is already at the root. Otherwise returns the initial path.
		 */
		static WString parentPath(const WString& path)
		{
			boost::filesystem3::path internalPath = path.c_str();

			return internalPath.parent_path().c_str();
		}

		/**
		 * @brief	Returns true if path child is included in path parent.
		 * 			Both paths must be canonical.
		 */
		static bool includes(const WString& child, const WString& parent)
		{
			Vector<WString>::type childPathElems = split(child);
			Vector<WString>::type parentPathElems = split(parent);

			auto iterChild = childPathElems.begin();
			auto iterParent = parentPathElems.begin();

			for(; iterParent != parentPathElems.end(); ++iterChild, ++iterParent)
			{
				if(iterChild == childPathElems.end())
					return false;

				if(!comparePathElements(*iterChild, *iterParent))
					return false;
			}

			return true;
		}

		/**
		 * @brief	Returns path relative to base.
		 */
		static WString relative(const WString& base, const WString& path)
		{
			Vector<WString>::type basePathElems = split(base);
			Vector<WString>::type pathElems = split(path);

			auto iterBase = basePathElems.begin();
			auto iterPath = pathElems.begin();

			for(; iterBase != basePathElems.end(); ++iterBase, ++iterPath)
			{
				if(!comparePathElements(*iterBase, *iterPath))
					return L"";
			}

			WString relativePath;
			for(; iterPath != pathElems.end(); ++iterPath)
			{
				relativePath = Path::combine(relativePath, *iterPath);
			}

			return relativePath;
		}

		/**
		 * @brief	Splits a path into string entries. Path separator
		 * 			may be "\" or "/". Path separator will not be included
		 * 			in the returned strings.
		 */
		static Vector<WString>::type split(const WString& path)
		{
			Vector<WString>::type splitPath;

			WString standardizedPath = standardizePath(path);
			return StringUtil::split(standardizedPath, L"/");
		}

		/**
		 * @brief	Combines two paths using the "/" path separator.
		 */
		static WString combine(const WString& base, const WString& name)
		{
			if (base.empty())
				return name;
			else
				return base + L'/' + name;
		}

		/**
		 * @brief	Compares two canonical paths and returns true if they are equal.
		 */
		static bool equals(const WString& left, const WString& right)
		{
			Vector<WString>::type leftElements = split(left);
			Vector<WString>::type rightElements = split(right);

			UINT32 idx = 0;
			for(auto& leftElem : leftElements)
			{
				if(leftElem.empty())
					continue;
				
				while(idx < (UINT32)rightElements.size() && rightElements[idx].empty())
					idx++;

				if(idx >= (UINT32)rightElements.size())
					return false; // Right path is deeper than left path

				if(!comparePathElements(leftElem, rightElements[idx]))
					return false;

				idx++;
			}

			while(idx < (UINT32)rightElements.size() && rightElements[idx].empty())
				idx++;

			if(idx < (UINT32)rightElements.size())
				return false; // Left path is deeper than right path

			return true;
		}

		/**
		 * @brief	Compares two path elements for equality. 
		 * 			
		 * @note	Should not be used for comparing entire paths. First you need to split your
		 * 			path into sub-elements using some other method and then send those sub-elements to
		 * 			this method. 
		 */
		static bool comparePathElements(const WString& left, const WString& right)
		{
			if(left.size() != right.size())
				return false;

			for(UINT32 i = 0; i < (UINT32)left.size(); i++)
			{
#if CM_PLATFORM == CM_PLATFORM_WIN32 // Compare case insensitive
				if(tolower(left[i]) != tolower(right[i]))
					return false;
#else
				assert(false); // Implement case sensitive or insensitive comparison, depending on platform
#endif
			}

			return true;
		}

		/**
		 * @brief	Extracts filename from the provided path.
		 *
		 * @param	path				Path to the file.
		 * @param	includeExtension	(optional) If true, filename extension will be included in the returned string.
		 */
		static WString getFilename(const WString& path, bool includeExtension = true)
		{
			boost::filesystem3::path internalPath = path.c_str();
			
			if(includeExtension)
				return internalPath.filename().c_str();
			else
				return internalPath.stem().c_str();
		}

		/**
		 * @brief	Method for standardizing paths - use forward slashes only, end without a slash.
		 */
		static WString standardizePath(const WString& inPath)
		{
			WString path = inPath;

			std::replace(path.begin(), path.end(), L'\\', L'/');

			while(path.length() > 0 && path.back() == L'/')
				path.pop_back();

			return path;
		}
	};
}