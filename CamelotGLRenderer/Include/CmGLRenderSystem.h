/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

Copyright (c) 2000-2011 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __GLRenderSystem_H__
#define __GLRenderSystem_H__

#include "CmGLPrerequisites.h"
#include "CmRenderSystem.h"
#include "CmGLHardwareBufferManager.h"
#include "CmGLGpuProgramManager.h"
#include "CmGLSLProgramFactory.h"
#include "CmCgProgramFactory.h"
#include "CmVector4.h"

namespace BansheeEngine {
    /**
      Implementation of GL as a rendering system.
     */
    class CM_RSGL_EXPORT GLRenderSystem : public RenderSystem
    {
    public:
        GLRenderSystem();
        ~GLRenderSystem();

		/**
		 * @copydoc RenderSystem::getName()
		 */
        const String& getName(void) const;

		/**
		 * @copydoc RenderSystem::getShadingLanguageName()
		 */
		const String& getShadingLanguageName() const;

		/**
		 * @copydoc RenderSystem::setRenderTarget()
		 */
        void setRenderTarget(RenderTargetPtr target);

        /**
		 * @copydoc RenderSystem::setVertexBuffers()
		 */
		void setVertexBuffers(UINT32 index, VertexBufferPtr* buffers, UINT32 numBuffers);

		/**
		 * @copydoc RenderSystem::setIndexBuffer()
		 */
		void setIndexBuffer(const IndexBufferPtr& buffer);

		/**
		 * @copydoc RenderSystem::setVertexDeclaration()
		 */
		void setVertexDeclaration(VertexDeclarationPtr vertexDeclaration);

		/**
		 * @copydoc RenderSystem::setDrawOperation()
		 */
		void setDrawOperation(DrawOperationType op);

        /**
		 * @copydoc RenderSystem::setScissorRect()
		 */
        void setScissorRect(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom);

		/**
		 * @copydoc RenderSystem::setTexture()
		 */
        void setTexture(GpuProgramType gptype, UINT16 unit, bool enabled, const TexturePtr &tex);
        
		/**
		 * @copydoc RenderSystem::setSamplerState()
		 */
		void setSamplerState(GpuProgramType gptype, UINT16 unit, const SamplerStatePtr& state);

		/**
		 * @copydoc RenderSystem::setBlendState()
		 */
		void setBlendState(const BlendStatePtr& blendState);

		/**
		 * @copydoc RenderSystem::setRasterizerState()
		 */
		void setRasterizerState(const RasterizerStatePtr& rasterizerState);

		/**
		 * @copydoc RenderSystem::setDepthStencilState()
		 */
		void setDepthStencilState(const DepthStencilStatePtr& depthStencilState, UINT32 stencilRefValue);

		/**
		 * @copydoc RenderSystem::setViewport()
		 */
        void setViewport(const ViewportPtr& vp);

		/**
		 * @copydoc RenderSystem::bindGpuProgram()
		 */
		void bindGpuProgram(HGpuProgram prg);

		/**
		 * @copydoc RenderSystem::unbindGpuProgram()
		 */
		void unbindGpuProgram(GpuProgramType gptype);

		/**
		 * @copydoc RenderSystem::bindGpuParams()
		 */
		void bindGpuParams(GpuProgramType gptype, BindableGpuParams& params);

		/**
		 * @copydoc RenderSystem::beginFrame()
		 */
        void beginFrame(void);

		/**
		 * @copydoc RenderSystem::endFrame()
		 */
        void endFrame(void);

		/**
		 * @copydoc RenderSystem::draw()
		 */
		void draw(UINT32 vertexOffset, UINT32 vertexCount);

		/**
		 * @copydoc RenderSystem::drawIndexed()
		 */
		void drawIndexed(UINT32 startIndex, UINT32 indexCount, UINT32 vertexOffset, UINT32 vertexCount);

		/**
		 * @copydoc RenderSystem::clearRenderTarget()
		 */
		void clearRenderTarget(UINT32 buffers, const Color& color = Color::Black, float depth = 1.0f, UINT16 stencil = 0);

		/**
		 * @copydoc RenderSystem::clearViewport()
		 */
		void clearViewport(UINT32 buffers, const Color& color = Color::Black, float depth = 1.0f, UINT16 stencil = 0);

        /**
		 * @copydoc RenderSystem::getColorVertexElementType()
		 */
        VertexElementType getColorVertexElementType(void) const;

		/**
		 * @copydoc RenderSystem::getHorizontalTexelOffset()
		 */
        float getHorizontalTexelOffset(void);

		/**
		 * @copydoc RenderSystem::getVerticalTexelOffset()
		 */
        float getVerticalTexelOffset(void);

		/**
		 * @copydoc RenderSystem::getMinimumDepthInputValue()
		 */
        float getMinimumDepthInputValue(void);

		 /**
		 * @copydoc RenderSystem::getMaximumDepthInputValue()
		 */
        float getMaximumDepthInputValue(void);

		/**
		 * @copydoc RenderSystem::convertProjectionMatrix()
		 */
        void convertProjectionMatrix(const Matrix4& matrix,
            Matrix4& dest, bool forGpuProgram = false);

		/************************************************************************/
		/* 				Internal use by OpenGL RenderSystem only                */
		/************************************************************************/

		bool isContextInitialized() const { return mGLInitialised; }

		GLContext* getMainContext() const { return mMainContext; } 
		GLSupport* getGLSupport() const { return mGLSupport; }

    private:
		// Scissor test
		UINT32 mScissorTop, mScissorBottom, mScissorLeft, mScissorRight;
		UINT32 mViewportLeft, mViewportTop, mViewportWidth, mViewportHeight;

		UINT32 mStencilReadMask;
		UINT32 mStencilWriteMask;
		UINT32 mStencilRefValue;
		CompareFunction mStencilCompareFront;
		CompareFunction mStencilCompareBack;

        /// View matrix to set world against
        Matrix4 mViewMatrix;

        /// Last min & mip filtering options, so we can combine them
        FilterOptions mMinFilter;
        FilterOptions mMipFilter;

        /// Holds texture type settings for every stage
        UINT32	mNumTextureTypes;
        GLenum* mTextureTypes;

        void initInputDevices(void);
        void processInputDevices(void);

        void makeGLMatrix(GLfloat gl_matrix[16], const Matrix4& m);
 
        GLint getBlendMode(BlendFactor ogreBlend) const;
		GLint getTextureAddressingMode(TextureAddressingMode tam) const;
		void initializeContext(GLContext* primary);

		/** See
          RenderSystem
         */
		virtual RenderSystemCapabilities* createRenderSystemCapabilities() const;
        /** See
          RenderSystem
         */
		void initialiseFromRenderSystemCapabilities(RenderSystemCapabilities* caps);

        /// Store last depth write state
        bool mDepthWrite;
		/// Store last colour write state
		bool mColorWrite[4];

        GLint convertCompareFunction(CompareFunction func) const;
        GLint convertStencilOp(StencilOperation op, bool invert = false) const;

		/// Internal method for anisotropy validation
		GLfloat _getCurrentAnisotropy(UINT16 unit);
		
        /// GL support class, used for creating windows etc.
        GLSupport* mGLSupport;

        /// Check if the GL system has already been initialised
        bool mGLInitialised;

		GLSLProgramFactory* mGLSLProgramFactory;
		CgProgramFactory* mCgProgramFactory;
		GLSLProgramPipelineManager* mProgramPipelineManager;

        GLuint getCombinedMinMipFilter(void) const;

        GLSLGpuProgramPtr mCurrentVertexProgram;
        GLSLGpuProgramPtr mCurrentFragmentProgram;
		GLSLGpuProgramPtr mCurrentGeometryProgram;
		GLSLGpuProgramPtr mCurrentHullProgram;
		GLSLGpuProgramPtr mCurrentDomainProgram;

		const GLSLProgramPipeline* mActivePipeline;

		UINT32 mFragmentTexOffset;
		UINT32 mVertexTexOffset;
		UINT32 mGeometryTexOffset;

		UINT32 mFragmentUBOffset;
		UINT32 mVertexUBOffset;
		UINT32 mGeometryUBOffset;
		UINT32 mHullUBOffset;
		UINT32 mDomainUBOffset;
		UINT32 mComputeUBOffset;

		UnorderedMap<UINT32, VertexBufferPtr>::type mBoundVertexBuffers;
		VertexDeclarationPtr mBoundVertexDeclaration;
		IndexBufferPtr mBoundIndexBuffer;
		DrawOperationType mCurrentDrawOperation;

        GLContext *mMainContext;
        GLContext *mCurrentContext;

		Vector<GLuint>::type mBoundAttributes; // Only full between begin/endDraw calls
		bool mDrawCallInProgress;

		UINT16 mActiveTextureUnit;

	protected:
		/**
		 * @copydoc	RenderSystem::initialize_internal().
		 */
		void initialize_internal(AsyncOp& asyncOp);

		/**
		 * @copydoc	RenderSystem::destroy_internal().
		 */
        void destroy_internal(void);

		void setClipPlanesImpl(const PlaneList& clipPlanes);
		bool activateGLTextureUnit(UINT16 unit);

        /** See
          RenderSystem
         */
        String getErrorDescription(long errorNumber) const;

		/** See
          RenderSystem
         */
        void setClipPlane (UINT16 index, float A, float B, float C, float D);
        /** See
          RenderSystem
         */
        void enableClipPlane (UINT16 index, bool enable);

		/************************************************************************/
		/* 								Sampler states                     		*/
		/************************************************************************/

		/** Sets the texture addressing mode for a texture unit.*/
        void setTextureAddressingMode(UINT16 stage, const UVWAddressingMode& uvw);

		/** Sets the texture border color for a texture unit.*/
        void setTextureBorderColor(UINT16 stage, const Color& color);

		/** Sets the mipmap bias value for a given texture unit.
		@remarks
		This allows you to adjust the mipmap calculation up or down for a
		given texture unit. Negative values force a larger mipmap to be used, 
		positive values force a smaller mipmap to be used. Units are in numbers
		of levels, so +1 forces the mipmaps to one smaller level.
		@note Only does something if render system has capability RSC_MIPMAP_LOD_BIAS.
		*/
		void setTextureMipmapBias(UINT16 unit, float bias);

		/** Sets a single filter for a given texture unit.
		@param unit The texture unit to set the filtering options for
		@param ftype The filter type
		@param filter The filter to be used
		*/
        void setTextureFiltering(UINT16 unit, FilterType ftype, FilterOptions filter);

		/** Sets the maximal anisotropy for the specified texture unit.*/
		void setTextureAnisotropy(UINT16 unit, unsigned int maxAnisotropy);

		/************************************************************************/
		/* 								Blend states                      		*/
		/************************************************************************/

		/** Sets the global blending factors for combining subsequent renders with the existing frame contents.
		The result of the blending operation is:</p>
		<p align="center">final = (texture * sourceFactor) + (pixel * destFactor)</p>
		Each of the factors is specified as one of a number of options, as specified in the SceneBlendFactor
		enumerated type.
		By changing the operation you can change addition between the source and destination pixels to a different operator.
		@param sourceFactor The source factor in the above calculation, i.e. multiplied by the texture colour components.
		@param destFactor The destination factor in the above calculation, i.e. multiplied by the pixel colour components.
		@param op The blend operation mode for combining pixels
		*/
		void setSceneBlending( BlendFactor sourceFactor, BlendFactor destFactor, BlendOperation op );

		/** Sets the global blending factors for combining subsequent renders with the existing frame contents.
		The result of the blending operation is:</p>
		<p align="center">final = (texture * sourceFactor) + (pixel * destFactor)</p>
		Each of the factors is specified as one of a number of options, as specified in the SceneBlendFactor
		enumerated type.
		@param sourceFactor The source factor in the above calculation, i.e. multiplied by the texture colour components.
		@param destFactor The destination factor in the above calculation, i.e. multiplied by the pixel colour components.
		@param sourceFactorAlpha The source factor in the above calculation for the alpha channel, i.e. multiplied by the texture alpha components.
		@param destFactorAlpha The destination factor in the above calculation for the alpha channel, i.e. multiplied by the pixel alpha components.
		@param op The blend operation mode for combining pixels
		@param alphaOp The blend operation mode for combining pixel alpha values
		*/
		void setSceneBlending( BlendFactor sourceFactor, BlendFactor destFactor, BlendFactor sourceFactorAlpha, 
			BlendFactor destFactorAlpha, BlendOperation op, BlendOperation alphaOp );

		/** Sets the global alpha rejection approach for future renders.
		By default images are rendered regardless of texture alpha. This method lets you change that.
		@param func The comparison function which must pass for a pixel to be written.
		@param val The value to compare each pixels alpha value to (0-255)
		*/
		void setAlphaTest(CompareFunction func, unsigned char value);

		/**
		 * @brief	Enable alpha coverage if supported.
		 */
		void setAlphaToCoverage(bool enabled);

		/** Sets whether or not colour buffer writing is enabled, and for which channels. 
		@remarks
		For some advanced effects, you may wish to turn off the writing of certain colour
		channels, or even all of the colour channels so that only the depth buffer is updated
		in a rendering pass. However, the chances are that you really want to use this option
		through the Material class.
		@param red, green, blue, alpha Whether writing is enabled for each of the 4 colour channels. */
		void setColorBufferWriteEnabled(bool red, bool green, bool blue, bool alpha);

		/************************************************************************/
		/* 								Rasterizer states                  		*/
		/************************************************************************/

		/** Sets the culling mode for the render system based on the 'vertex winding'.
		A typical way for the rendering engine to cull triangles is based on the
		'vertex winding' of triangles. Vertex winding refers to the direction in
		which the vertices are passed or indexed to in the rendering operation as viewed
		from the camera, and will wither be clockwise or anticlockwise (that's 'counterclockwise' for
		you Americans out there ;) The default is CULL_CLOCKWISE i.e. that only triangles whose vertices
		are passed/indexed in anticlockwise order are rendered - this is a common approach and is used in 3D studio models
		for example. You can alter this culling mode if you wish but it is not advised unless you know what you are doing.
		You may wish to use the CULL_NONE option for mesh data that you cull yourself where the vertex
		winding is uncertain.
		*/
		void setCullingMode(CullingMode mode);

		/** Sets how to rasterise triangles, as points, wireframe or solid polys. */
		void setPolygonMode(PolygonMode level);

		/** Sets the depth bias, NB you should use the Material version of this. 
		@remarks
		When polygons are coplanar, you can get problems with 'depth fighting' where
		the pixels from the two polys compete for the same screen pixel. This is particularly
		a problem for decals (polys attached to another surface to represent details such as
		bulletholes etc.).
		@par
		A way to combat this problem is to use a depth bias to adjust the depth buffer value
		used for the decal such that it is slightly higher than the true value, ensuring that
		the decal appears on top.
		@note
		The final bias value is a combination of a constant bias and a bias proportional
		to the maximum depth slope of the polygon being rendered. The final bias
		is constantBias + slopeScaleBias * maxslope. Slope scale biasing is
		generally preferable but is not available on older hardware.
		@param constantBias The constant bias value, expressed as a value in 
		homogeneous depth coordinates.
		@param slopeScaleBias The bias value which is factored by the maximum slope
		of the polygon, see the description above. This is not supported by all
		cards.

		*/
		void setDepthBias(float constantBias, float slopeScaleBias);

		/**
		* @brief	Scissor test allows you to 'mask off' rendering in all but a given rectangular area
		* 			identified by the rectangle set by setScissorRect().
		*/
		void setScissorTestEnable(bool enable);

		/************************************************************************/
		/* 						Depth stencil state                      		*/
		/************************************************************************/
		
		/** Sets the mode of operation for depth buffer tests from this point onwards.
		Sometimes you may wish to alter the behaviour of the depth buffer to achieve
		special effects. Because it's unlikely that you'll set these options for an entire frame,
		but rather use them to tweak settings between rendering objects, this is an internal
		method (indicated by the '_' prefix) which will be used by a SceneManager implementation
		rather than directly from the client application.
		If this method is never called the settings are automatically the same as the default parameters.
		@param depthTest If true, the depth buffer is tested for each pixel and the frame buffer is only updated
		if the depth function test succeeds. If false, no test is performed and pixels are always written.
		@param depthWrite If true, the depth buffer is updated with the depth of the new pixel if the depth test succeeds.
		If false, the depth buffer is left unchanged even if a new pixel is written.
		@param depthFunction Sets the function required for the depth test.
		*/
		void setDepthBufferParams(bool depthTest = true, bool depthWrite = true, CompareFunction depthFunction = CMPF_LESS_EQUAL);

		/** Sets whether or not the depth buffer check is performed before a pixel write.
		@param enabled If true, the depth buffer is tested for each pixel and the frame buffer is only updated
		if the depth function test succeeds. If false, no test is performed and pixels are always written.
		*/
		void setDepthBufferCheckEnabled(bool enabled = true);

		/** Sets whether or not the depth buffer is updated after a pixel write.
		@param enabled If true, the depth buffer is updated with the depth of the new pixel if the depth test succeeds.
		If false, the depth buffer is left unchanged even if a new pixel is written.
		*/
		void setDepthBufferWriteEnabled(bool enabled = true);

		/** Sets the comparison function for the depth buffer check.
		Advanced use only - allows you to choose the function applied to compare the depth values of
		new and existing pixels in the depth buffer. Only an issue if the deoth buffer check is enabled
		(see _setDepthBufferCheckEnabled)
		@param  func The comparison between the new depth and the existing depth which must return true
		for the new pixel to be written.
		*/
		void setDepthBufferFunction(CompareFunction func = CMPF_LESS_EQUAL);

		/** Turns stencil buffer checking on or off.
		@remarks
		Stencilling (masking off areas of the rendering target based on the stencil
		buffer) can be turned on or off using this method. By default, stencilling is
		disabled.
		*/
		void setStencilCheckEnabled(bool enabled);

		/** This method allows you to set stencil buffer operations in one call.
		@param stencilFailOp The action to perform when the stencil check fails
		@param depthFailOp The action to perform when the stencil check passes, but the
		depth buffer check still fails
		@param passOp The action to take when both the stencil and depth check pass.
		@param ccw If set to true, the stencil operations will be applied to counterclockwise
		faces. Otherwise they will be applied to clockwise faces.
		*/
		void setStencilBufferOperations(StencilOperation stencilFailOp = SOP_KEEP,
			StencilOperation depthFailOp = SOP_KEEP, StencilOperation passOp = SOP_KEEP,
			bool front = true);

		/**
		* @brief	Sets a stencil buffer comparison function. The result of this will cause one of 3 actions depending on whether the test fails,
		*		succeeds but with the depth buffer check still failing, or succeeds with the
		*		depth buffer check passing too.
		* @param mask The bitmask applied to both the stencil value and the reference value
		*		before comparison
		* @param ccw If set to true, the stencil operations will be applied to counterclockwise
		*		faces. Otherwise they will be applied to clockwise faces.
		 */
		void setStencilBufferFunc(CompareFunction func = CMPF_ALWAYS_PASS, UINT32 mask = 0xFFFFFFFF, bool front = true);

		/**
		* @brief	The bitmask applied to the stencil value before writing it to the stencil buffer.
		 */
		void setStencilBufferWriteMask(UINT32 mask = 0xFFFFFFFF);

		/**
		 * @brief	Sets a reference values used for stencil buffer comparisons. 
		 * 			Actual comparison function and stencil operations are set by setting the DepthStencilState.
		 */
		void setStencilRefValue(UINT32 refValue);

        /** One time initialization for the RenderState of a context. Things that
            only need to be set once, like the LightingModel can be defined here.
         */
        void oneTimeContextInitialization();
        /** Switch GL context, dealing with involved internal cached states too
        */
        void switchContext(GLContext *context);

		/**
		 * @brief	Checks if there are any OpenGL errors and prints them to the log.
		 */
		bool checkForErrors() const;

		/**
		 * @brief	OpenGL shares all texture slots, but the engine prefers to keep textures
		 * 			separate per-stage. This will convert texture unit that is set per stage
		 * 			into a global texture unit usable by OpenGL.
		 */
		UINT32 getGLTextureUnit(GpuProgramType gptype, UINT32 unit);

		/**
		 * @brief	OpenGL shares all buffer bindings, but the engine prefers to keep buffers
		 * 			separate per-stage. This will convert block buffer binding that is set per stage
		 * 			into a global block buffer binding usable by OpenGL.
		 */
		UINT32 getGLUniformBlockBinding(GpuProgramType gptype, UINT32 binding);

		/**
		 * @brief	Returns the OpenGL specific mode used for drawing, depending on the
		 * 			currently set draw operation;
		 */
		GLint getGLDrawMode() const;

		/**
		 * @brief	Call before doing a draw operation, this method sets everything up.
		 */
		void beginDraw();

		/**
		 * @brief	Needs to accompany every beginDraw after you are done with a single draw operation.
		 */
		void endDraw();

		void clearArea(UINT32 buffers, const Color& color = Color::Black, float depth = 1.0f, UINT16 stencil = 0, const RectI& clearArea = RectI::EMPTY);

		void setActiveProgram(GpuProgramType gptype, GLSLGpuProgramPtr program);
		GLSLGpuProgramPtr getActiveProgram(GpuProgramType gptype) const;
    };
}
#endif

