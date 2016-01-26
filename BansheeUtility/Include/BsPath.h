#pragma once

#include "BsPrerequisitesUtil.h"
#include "BsUtil.h"

namespace BansheeEngine
{
	/**
	 * @brief	Class for storing and manipulating file paths. Paths may be parsed
	 *			from and to raw strings according to various platform specific path
	 *			types.
	 *
	 * @note	In order to allow the system to easily distinguish between file and directory
	 *			paths, try to ensure that all directory paths end with a separator (\ or / depending
	 *			on platform). System won't fail if you don't but it will be easier to misuse.
	 */
	class BS_UTILITY_EXPORT Path
	{
	public:
		enum class PathType
		{
			Windows,
			Unix,
			Default
		};

	public:
		Path();

		/**
		 * @brief	Constructs a path by parsing the provided path string. 
		 *			Throws exception if provided path is not valid.
		 *
		 * @param	type	If set to default path will be parsed according to the
		 *					rules of the platform the application is being compiled to.
		 *					Otherwise it will be parsed according to provided type.
		 */
		Path(const WString& pathStr, PathType type = PathType::Default);

		/**
		 * @brief	Constructs a path by parsing the provided path string.
		 *			Throws exception if provided path is not valid.
		 *
		 * @param	type	If set to default path will be parsed according to the
		 *					rules of the platform the application is being compiled to.
		 *					Otherwise it will be parsed according to provided type.
		 */
		Path(const String& pathStr, PathType type = PathType::Default);

		/**
		 * @brief	Constructs a path by parsing the provided path null terminated string.
		 *			Throws exception if provided path is not valid.
		 *
		 * @param	type	If set to default path will be parsed according to the
		 *					rules of the platform the application is being compiled to.
		 *					Otherwise it will be parsed according to provided type.
		 */
		Path(wchar_t* pathStr, PathType type = PathType::Default);

		/**
		 * @brief	Constructs a path by parsing the provided path null terminated string.
		 *			Throws exception if provided path is not valid.
		 *
		 * @param	type	If set to default path will be parsed according to the
		 *					rules of the platform the application is being compiled to.
		 *					Otherwise it will be parsed according to provided type.
		 */
		Path(const char* pathStr, PathType type = PathType::Default);
		Path(const Path& other);

		/**
		 * @brief	Assigns a path by parsing the provided path string. Path will be 
		 *			parsed according to the rules of the platform the application is 
		 *			being compiled to.
		 */
		Path& operator= (const WString& pathStr);

		/**
		 * @brief	Assigns a path by parsing the provided path string. Path will be
		 *			parsed according to the rules of the platform the application is
		 *			being compiled to.
		 */
		Path& operator= (const String& pathStr);

		/**
		 * @brief	Assigns a path by parsing the provided path null terminated string. 
		 *			Path will be parsed according to the rules of the platform the 
		 *			application is being compiled to.
		 */
		Path& operator= (const wchar_t* pathStr);

		/**
		 * @brief	Assigns a path by parsing the provided path null terminated string.
		 *			Path will be parsed according to the rules of the platform the
		 *			application is being compiled to.
		 */
		Path& operator= (const char* pathStr);

		Path& operator= (const Path& path);

		/**
		 * @brief	Compares two paths and returns true if they match. Comparison is
		 *			case insensitive and paths will be compared as-is, without canonization.
		 */
		bool operator== (const Path& path) const { return equals(path); }

		/**
		 * @brief	Compares two paths and returns true if they don't match. Comparison is
		 *			case insensitive and paths will be compared as-is, without canonization.
		 */
		bool operator!= (const Path& path) const { return !equals(path); }

		/**
		* @brief	Gets a directory name with the specified index from the path.
		*/
		const WString& operator[] (UINT32 idx) const { return getWDirectory(idx); }

		/**
		 * @brief	Swap internal data with another Path object.
		 */
		void swap(Path& path);

		/**
		 * @brief	Create a path from another Path object.
		 */
		void assign(const Path& path);

		/**
		 * @brief	Constructs a path by parsing the provided path string.
		 *			Throws exception if provided path is not valid.
		 *
		 * @param	type	If set to default path will be parsed according to the
		 *					rules of the platform the application is being compiled to.
		 *					Otherwise it will be parsed according to provided type.
		 */
		void assign(const WString& pathStr, PathType type = PathType::Default);

		/**
		 * @brief	Constructs a path by parsing the provided path string.
		 *			Throws exception if provided path is not valid.
		 *
		 * @param	type	If set to default path will be parsed according to the
		 *					rules of the platform the application is being compiled to.
		 *					Otherwise it will be parsed according to provided type.
		 */
		void assign(const String& pathStr, PathType type = PathType::Default);

		/**
		 * @brief	Constructs a path by parsing the provided path null terminated string.
		 *			Throws exception if provided path is not valid.
		 *
		 * @param	type	If set to default path will be parsed according to the
		 *					rules of the platform the application is being compiled to.
		 *					Otherwise it will be parsed according to provided type.
		 */
		void assign(const wchar_t* pathStr, PathType type = PathType::Default);

		/**
		 * @brief	Constructs a path by parsing the provided path null terminated string.
		 *			Throws exception if provided path is not valid.
		 *
		 * @param	type	If set to default path will be parsed according to the
		 *					rules of the platform the application is being compiled to.
		 *					Otherwise it will be parsed according to provided type.
		 */
		void assign(const char* pathStr, PathType type = PathType::Default);

		/**
		 * @brief	Converts the path in a string according to platform path rules.
		 *
		 * @type	If set to default path will be parsed according to the
		 *			rules of the platform the application is being compiled to.
		 *			Otherwise it will be parsed according to provided type.
		 */
		WString toWString(PathType type = PathType::Default) const;

		/**
		 * @brief	Converts the path in a string according to platform path rules.
		 *
		 * @type	If set to default path will be parsed according to the
		 *			rules of the platform the application is being compiled to.
		 *			Otherwise it will be parsed according to provided type.
		 */
		String toString(PathType type = PathType::Default) const;

		/**
		 * @brief	Checks is the path a directory (contains no file-name).
		 */
		bool isDirectory() const { return mFilename.empty(); }

		/**
		 * @brief	Checks does the path point to a file.
		 */
		bool isFile() const { return !mFilename.empty(); }

		/**
		 * @brief	Checks is the contained path absolute.
		 */
		bool isAbsolute() const { return mIsAbsolute; }

		/**
		 * @brief	Returns parent path. If current path points to a file
		 *			the parent path will be the folder where the file is located.
		 *			Or if it contains a directory the parent will be the parent directory.
		 *			If no parent exists, same path will be returned.
		 */
		Path getParent() const;

		/**
		 * @brief	Returns an absolute path by appending the current path to the provided base.
		 *			If path was already absolute no changes are made and copy of current path
		 *			is returned.
		 *			If base is not absolute, then the returned path will be made relative to base,
		 *			but will not be absolute.
		 */
		Path getAbsolute(const Path& base) const;

		/**
		 * @brief	Returns a relative path by making the current path relative to the provided base.
		 *			Base must be a part of the current path. If base is not a part
		 *			of the path no changes are made and a copy of the current path
		 *			is returned.
		 */
		Path getRelative(const Path& base) const;

		/**
		 * @brief	Returns the path as a path to directory. If path was pointing
		 *			to a file, the filename is removed, otherwise no changes are made
		 *			and exact copy is returned.
		 */
		Path getDirectory() const;

		/**
		 * @brief	Makes the path the parent of the current path. If current path points to a file
		 *			the parent path will be the folder where the file is located.
		 *			Or if it contains a directory the parent will be the parent directory.
		 *			If no parent exists, same path will be returned.
		 */
		Path& makeParent();

		/**
		 * @brief	Makes the current path absolute by appending it to base.
		 *			If path was already absolute no changes are made and copy of current path
		 *			is returned.
		 *			If base is not absolute, then the returned path will be made relative to base,
		 *			but will not be absolute.
		 */
		Path& makeAbsolute(const Path& base);

		/**
		 * @brief	Makes the current path relative to the provided base.
		 *			Base must be a part of the current path. If base is not a part
		 *			of the path no changes are made and a copy of the current path
		 *			is returned.
		 */
		Path& makeRelative(const Path& base);

		/**
		 * @brief	Appends another path to the end of this path.
		 */
		Path& append(const Path& path);

		/**
		 * @brief	Checks if the current path contains the provided path.
		 *			Comparison is case insensitive and paths will be compared 
		 *			as-is, without canonization.
		 */
		bool includes(const Path& child) const;

		/**
		 * @brief	Compares two paths and returns true if they match. Comparison is
		 *			case insensitive and paths will be compared as-is, without canonization.
		 */
		bool equals(const Path& other) const;

		/**
		 * @brief	Change or set the filename in the path.
		 */
		void setFilename(const WString& filename) { mFilename = filename; }

		/**
		 * @brief	Change or set the filename in the path.
		 */
		void setFilename(const String& filename) { mFilename = BansheeEngine::toWString(filename); }

		/**
		 * @brief	Change or set the base name in the path. Base name changes the
		 *			filename by changing its base to the provided value but keeping extension intact.
		 */
		void setBasename(const WString& basename);

		/**
		 * @brief	Change or set the base name in the path. Base name changes the
		 *			filename by changing its base to the provided value but keeping extension intact.
		 */
		void setBasename(const String& basename);

		/**
		 * @brief	Change or set the extension of the filename in the path.
		 */
		void setExtension(const WString& extension);

		/**
		 * @brief	Change or set the extension of the filename in the path.
		 */
		void setExtension(const String& extension);

		/**
		 * @brief	Returns a filename in the path.
		 *
		 * @param	extension	If true, returned filename will contain an extension.
		 */
		WString getWFilename(bool extension = true) const;

		/**
		 * @brief	Returns a filename in the path.
		 *
		 * @param	extension	If true, returned filename will contain an extension.
		 */
		String getFilename(bool extension = true) const;

		/**
		 * @brief	Returns file extension with the leading ".".
		 */
		WString getWExtension() const;

		/**
		 * @brief	Returns file extension with the leading ".".
		 */
		String getExtension() const;

		/**
		 * @brief	Gets the number of directories in the path.
		 */
		UINT32 getNumDirectories() const { return (UINT32)mDirectories.size(); }

		/**
		 * @brief	Gets a directory name with the specified index from the path.
		 */
		const WString& getWDirectory(UINT32 idx) const;

		/**
		* @brief	Gets a directory name with the specified index from the path.
		*/
		String getDirectory(UINT32 idx) const;

		/**
		 * @brief	Returns path device (e.g. drive, volume, etc.) if one exists in the path.
		 */
		const WString& getWDevice() const { return mDevice; }

		/**
		* @brief	Returns path device (e.g. drive, volume, etc.) if one exists in the path.
		*/
		String getDevice() const { return BansheeEngine::toString(mDevice); }

		/**
		* @brief	Returns path node (e.g. network name) if one exists in the path.
		*/
		const WString& getWNode() const { return mNode; }

		/**
		* @brief	Returns path node (e.g. network name) if one exists in the path.
		*/
		String getNode() const { return BansheeEngine::toString(mNode); }

		/**
		* @brief	Gets last element in the path, filename if it exists, otherwise the last directory.
		*			If no directories exist returns device or node.
		*
		* @param	type	Determines format of node or device, in case they are returned. When default,
		*					format for the active platform will be used, otherwise the format defined
		*					by the parameter will be used.
		*/
		WString getWTail(PathType type = PathType::Default) const;

		/**
		 * @brief	Gets last element in the path, filename if it exists, otherwise the last directory.
		 *			If no directories exist returns device or node.
		 *
		 * @param	type	Determines format of node or device, in case they are returned. When default,
		 *					format for the active platform will be used, otherwise the format defined
		 *					by the parameter will be used.
		 */
		String getTail(PathType type = PathType::Default) const;

		/**
		 * @brief	Clears the path to nothing.
		 */
		void clear();

		/**
		 * @brief	Returns true if no path has been set.
		 */
		bool isEmpty() const { return mDirectories.empty() && mFilename.empty() && mDevice.empty() && mNode.empty(); }

		/**
		* @brief	Compares two path elements (i.e. filenames, directory names, etc.)
		*/
		static bool comparePathElem(const WString& left, const WString& right);

		static const Path BLANK;
	private:
		/**
		* @brief	Constructs a path by parsing the provided raw string data.
		*			Throws exception if provided path is not valid.
		*
		* @param	type	If set to default path will be parsed according to the
		*					rules of the platform the application is being compiled to.
		*					Otherwise it will be parsed according to provided type.
		*/
		void assign(const wchar_t* pathStr, UINT32 numChars, PathType type = PathType::Default);

		/**
		* @brief	Constructs a path by parsing the provided raw string data.
		*			Throws exception if provided path is not valid.
		*
		* @param	type	If set to default path will be parsed according to the
		*					rules of the platform the application is being compiled to.
		*					Otherwise it will be parsed according to provided type.
		*/
		void assign(const char* pathStr, UINT32 numChars, PathType type = PathType::Default);

		/**
		 * @brief	Parses a Windows path and stores the parsed data internally.
		 *			Throws an exception if parsing fails.
		 */
		template<class T>
		void parseWindows(const T* pathStr, UINT32 numChars)
		{
			clear();

			UINT32 idx = 0;
			BasicStringStream<T> tempStream;

			if (idx < numChars)
			{
				if (pathStr[idx] == '\\' || pathStr[idx] == '/')
				{
					mIsAbsolute = true;
					idx++;
				}
			}

			if (idx < numChars)
			{
				// Path starts with a node, a drive letter or is relative
				if (mIsAbsolute && pathStr[idx] == '\\' || pathStr[idx] == '/') // Node
				{
					idx++;

					tempStream.str(BasicString<T>());
					tempStream.clear();
					while (idx < numChars && pathStr[idx] != '\\' && pathStr[idx] != '/')
						tempStream << pathStr[idx++];

					setNode(tempStream.str());

					if (idx < numChars)
						idx++;
				}
				else // A drive letter or not absolute
				{
					T drive = pathStr[idx];
					idx++;

					if (idx < numChars && pathStr[idx] == ':')
					{
						if (mIsAbsolute || !((drive >= 'a' && drive <= 'z') || (drive >= 'A' && drive <= 'Z')))
							throwInvalidPathException(BasicString<T>(pathStr, numChars));

						mIsAbsolute = true;
						setDevice(BansheeEngine::toWString(drive));

						idx++;

						if (idx >= numChars || (pathStr[idx] != '\\' && pathStr[idx] != '/'))
							throwInvalidPathException(BasicString<T>(pathStr, numChars));

						idx++;
					}
					else
						idx--;
				}

				while (idx < numChars)
				{
					tempStream.str(BasicString<T>());
					tempStream.clear();
					while (idx < numChars && pathStr[idx] != '\\' && pathStr[idx] != '/')
					{
						tempStream << pathStr[idx];
						idx++;
					}

					if (idx < numChars)
						pushDirectory(tempStream.str());
					else
						setFilename(tempStream.str());

					idx++;
				}
			}
		}

		/**
		* @brief	Parses a Unix path and stores the parsed data internally.
		*			Throws an exception if parsing fails.
		*/
		template<class T>
		void parseUnix(const T* pathStr, UINT32 numChars)
		{
			clear();

			UINT32 idx = 0;
			BasicStringStream<T> tempStream;

			if (idx < numChars)
			{
				if (pathStr[idx] == '/')
				{
					mIsAbsolute = true;
					idx++;
				}
				else if (pathStr[idx] == '~')
				{
					idx++;
					if (idx >= numChars || pathStr[idx] == '/')
					{
						pushDirectory(BansheeEngine::toWString('~'));
						mIsAbsolute = true;
					}
					else
						idx--;
				}

				while (idx < numChars)
				{
					tempStream.str(BasicString<T>());
					tempStream.clear();
					while (idx < numChars && pathStr[idx] != '/')
					{
						tempStream << pathStr[idx];
						idx++;
					}

					if (idx < numChars)
					{
						if (mDirectories.empty())
						{
							BasicString<T> deviceStr = tempStream.str();
							if (!deviceStr.empty() && *(deviceStr.rbegin()) == ':')
							{
								setDevice(deviceStr.substr(0, deviceStr.length() - 1));
								mIsAbsolute = true;
							}
							else
							{
								pushDirectory(deviceStr);
							}
						}
						else
						{
							pushDirectory(tempStream.str());
						}
					}
					else
					{
						setFilename(tempStream.str());
					}

					idx++;
				}
			}
		}

		void setNode(const WString& node) { mNode = node; }
		void setNode(const String& node) { mNode = BansheeEngine::toWString(node); }

		void setDevice(const WString& device) { mDevice = device; }
		void setDevice(const String& device) { mDevice = BansheeEngine::toWString(device); }

		/**
		 * @brief	Build a Windows path string from internal path data.
		 */
		WString buildWindows() const;

		/**
		* @brief	Build a Unix path string from internal path data.
		*/
		WString buildUnix() const;

		/**
		 * @brief	Add new directory to the end of the path. 
		 */
		void pushDirectory(const WString& dir);

		/**
		* @brief	Add new directory to the end of the path.
		*/
		void pushDirectory(const String& dir);

		/**
		 * @brief	Helper method that throws invalid path exception. 
		 */
		void throwInvalidPathException(const WString& path) const;

		/**
		* @brief	Helper method that throws invalid path exception.
		*/
		void throwInvalidPathException(const String& path) const;
	private:
		friend struct RTTIPlainType<Path>; // For serialization
		friend struct ::std::hash<BansheeEngine::Path>;

		Vector<WString> mDirectories;
		WString mDevice;
		WString mFilename;
		WString mNode;
		bool mIsAbsolute;
	};

	/**
	* @brief	RTTIPlainType specialization for Path that allows paths be serialized as
	* 			value types.
	*
	* @see		RTTIPlainType
	*/
	template<> struct RTTIPlainType<Path>
	{
		enum { id = TID_Path }; enum { hasDynamicSize = 1 };

		static void toMemory(const Path& data, char* memory)
		{
			UINT32 size = getDynamicSize(data);
			memcpy(memory, &size, sizeof(UINT32));
			memory += sizeof(UINT32);

			memory = rttiWriteElem(data.mDevice, memory);
			memory = rttiWriteElem(data.mNode, memory);
			memory = rttiWriteElem(data.mFilename, memory);
			memory = rttiWriteElem(data.mIsAbsolute, memory);
			memory = rttiWriteElem(data.mDirectories, memory);
		}

		static UINT32 fromMemory(Path& data, char* memory)
		{
			UINT32 size;
			memcpy(&size, memory, sizeof(UINT32));
			memory += sizeof(UINT32);

			memory = rttiReadElem(data.mDevice, memory);
			memory = rttiReadElem(data.mNode, memory);
			memory = rttiReadElem(data.mFilename, memory);
			memory = rttiReadElem(data.mIsAbsolute, memory);
			memory = rttiReadElem(data.mDirectories, memory);

			return size;
		}

		static UINT32 getDynamicSize(const Path& data)
		{
			UINT64 dataSize = rttiGetElemSize(data.mDevice) + rttiGetElemSize(data.mNode) + rttiGetElemSize(data.mFilename) +
				rttiGetElemSize(data.mIsAbsolute) + rttiGetElemSize(data.mDirectories) + sizeof(UINT32);

#if BS_DEBUG_MODE
			if (dataSize > std::numeric_limits<UINT32>::max())
			{
				__string_throwDataOverflowException();
			}
#endif

			return (UINT32)dataSize;
		}
	};
}

/**
* @brief	Hash value generator for Path.
*/
template<>
struct std::hash<BansheeEngine::Path>
{
	size_t operator()(const BansheeEngine::Path& path) const
	{
		size_t hash = 0;
		BansheeEngine::hash_combine(hash, path.mFilename);
		BansheeEngine::hash_combine(hash, path.mDevice);
		BansheeEngine::hash_combine(hash, path.mNode);

		for (auto& dir : path.mDirectories)
			BansheeEngine::hash_combine(hash, dir);

		return hash;
	}
};