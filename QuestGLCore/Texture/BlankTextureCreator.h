#pragma once
#include "QuestGLCore/OpenGLTypes/OpenGLFunctionResolution.h"
#include "QuestGLCore/Texture/BlankTextureCreator.h"
#include "QuestGLCore/Texture/BlankTextureEnum.h"
#include "QuestUtility/Include/Logger.h"
#include <memory>
#include <glad/glad.h>

namespace QuestGLCore::Texture {

	template<GLenum TextureType>
	class BlankTextureCreator {

	public:
		BlankTextureCreator() = default;
		virtual ~BlankTextureCreator() = default;
		BlankTextureCreator(const BlankTextureCreator& source) = delete;
		BlankTextureCreator(BlankTextureCreator&& source) = delete;
		BlankTextureCreator& operator=(const BlankTextureCreator& rhs) = delete;
		BlankTextureCreator& operator=(BlankTextureCreator&& rhs) = delete;

		[[nodiscard]] TextureHandle generate_texture(const int width, const int height) const {
			TextureHandle handle{ TextureType };
			handle.bind();
			set_parameters();
			load_texture(width, height);
			handle.unbind();
			return handle;
		}

		void rescale_texture(const TextureHandle& handle, const int width, const int height) const {
			handle.bind();
			load_texture(width, height);
			handle.unbind();
		}

	protected:
		virtual void set_parameters() const = 0;
		virtual void load_texture(const int width, const int height) const = 0;
	};

	// =========================== Blank Texture Types ===========================

	// ========== Standard ========== 
	template<GLenum TextureType>
	class RGBALinearBLankTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		RGBALinearBLankTextureCreator()
			:BlankTextureCreator<TextureType>() {
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
	};
	
	template<GLenum TextureType>
	class RGBANearestBLankTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		RGBANearestBLankTextureCreator()
			:BlankTextureCreator<TextureType>() {
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
	};

	// ============ HD16F ============
	template<GLenum TextureType>
	class RGBA16FLinearBlankTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		RGBA16FLinearBlankTextureCreator()
			:BlankTextureCreator<TextureType>() {
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
	};

	template<GLenum TextureType>
	class RGBA16FNearestBlankTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		RGBA16FNearestBlankTextureCreator()
			:BlankTextureCreator<TextureType>() {
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
	};

	// ============ HD32F ============
	template<GLenum TextureType>
	class RGBA32FLinearBlankTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		RGBA32FLinearBlankTextureCreator()
			:BlankTextureCreator<TextureType>(){
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
	};

	template<GLenum TextureType>
	class RGBA32FNearestBlankTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		RGBA32FNearestBlankTextureCreator()
			:BlankTextureCreator<TextureType>() {
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
	};

	template<GLenum TextureType>
	class BlankTextureFactory {
	public:
		static std::unique_ptr<BlankTextureCreator<TextureType>> create_blank_texture_creator(const BlankTextureEnum blank_texture_type) {

			std::unique_ptr<BlankTextureCreator<TextureType>> creator{ nullptr };
			switch (blank_texture_type) {
			case BlankTextureEnum::RGBA_LINEAR: {
				creator = std::make_unique<RGBALinearBLankTextureCreator<TextureType>>();
				break;
			}
			case BlankTextureEnum::RGBA_NEAREST: {
				creator = std::make_unique<RGBANearestBLankTextureCreator<TextureType>>();
				break;
			}
			case BlankTextureEnum::RGBA16F_LINEAR: {
				creator = std::make_unique<RGBA16FLinearBlankTextureCreator<TextureType>>();
				break;
			}
			case BlankTextureEnum::RGBA16F_NEAREST: {
				creator = std::make_unique<RGBA16FNearestBlankTextureCreator<TextureType>>();
				break;
			}
			case BlankTextureEnum::RGBA32F_LINEAR: {
				creator = std::make_unique<RGBA32FLinearBlankTextureCreator<TextureType>>();
				break;
			}
			case BlankTextureEnum::RGBA32F_NEAREST: {
				creator = std::make_unique<RGBA32FNearestBlankTextureCreator<TextureType>>();
				break;
			}
			default:
				QUEST_FATAL("Invalid Blank Texture Type! There is not option in the static function 'get_texture_creator' for creating this texture creator type! Please update the switch statment!")
				break;
			}

			return creator;
		}
	};

} // namespace QuestGLCore::Texture